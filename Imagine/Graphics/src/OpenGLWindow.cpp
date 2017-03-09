#include "Imagine/Graphics/ConfigGraphics.h"
#include "OpenGLWindow.h"

#ifdef IMAGINE_OPENGL
#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace Imagine{
static double FOVY=30.0; // Angle of view in y direction of camera
static float ZOOM_INCREMENT=1.05f; // For mouse wheel and 'A' and 'Z' keys

// Makes vector turn around axis of angle
void rotate(DoubleVector3& vector, DoubleVector3 axis, float angle) {
    double ca = cos(angle);
    double sa = sin(angle);
    DoubleVector3 cross = vector^axis;
    double dot =  axis*vector;
    vector = vector*ca + cross*sa + dot*axis*(1-ca);
}

void TrackBall::move(const QPointF& p, Mode m) {
    DoubleVector3 right = up^eye;
    right.normalize();
    QPointF delta = p-lastPos_;
    if(m==Rotate) {
        rotate(up,right,delta.y());
        rotate(eye,up,delta.x());
        rotate(eye,right,delta.y());
    } else {
        pos += (right*delta.x() - up*delta.y())*norm(eye)/5;
    }
    lastPos_ = p;
}

// ======================================================================
// OpenGLWindow implementation

OpenGLWindow::OpenGLWindow(Window win, int subWinId, int width, int height,
                           const QString& windowTitle, int x, int y,
                           QWidget *parent)
: QGLWidget(parent)
, win_(win), subWinId_(subWinId)
, mode_(FILL)
, backgroundColor(QColor::fromCmykF(0.39, 0.39, 0.0, 0.0))
, color(QColor::fromCmykF(0.40, 0.0, 1.0, 0.0))
{
    width_ = width;
    height_ = height;
    setWindowTitle(windowTitle);
    if(x!=-1 && y!=-1)
        move(x,y);
    resize(width,height);
    show();
}

void OpenGLWindow::capture(QImage* image) {
    *image = grabFrameBuffer();
}

void OpenGLWindow::setBackground(const QColor& col) {
    qglClearColor(col);
    backgroundColor = col;
    update();
}

void OpenGLWindow::centerOnMeshes() {
    centerVec.fill(0.0f);
    radius=0;
    int n=0;
    std::set<Mesh>::iterator it=mesh_.begin(), end=mesh_.end();
    for(; it != end; ++it) {
        int v=0;
        centerVec += it->sum(v);
        n += v;
    }
    if(n) {
        centerVec /= float(n);
        for(it=mesh_.begin(); it != end; ++it) {
            float v = it->spread(centerVec);
            if(radius<v)
                radius=v;
        }
    }
    m_trackBall.pos = centerVec;
    m_trackBall.up = DoubleVector3(0.0,1.0,0.0);
    m_trackBall.eye =
        DoubleVector3(0.0, 0.0, -radius/(float)sin(FOVY/2/180.0*M_PI /1.5));
}

void OpenGLWindow::addMesh(const Mesh& mesh, bool reinitCam) {
    mesh_.insert(mesh);
    if(reinitCam)
        centerOnMeshes();
    update();
}

void OpenGLWindow::removeMesh(const Mesh& mesh, bool reinitCam) {
    mesh_.erase(mesh);
    if(reinitCam)
        centerOnMeshes();
    update();
}

void OpenGLWindow::clear() {
    mesh_.clear();
    update();
}

void OpenGLWindow::setLookAt(double posX, double posY, double posZ,
                             double dirX, double dirY, double dirZ,
                             double upX, double upY, double upZ) {
    m_trackBall.pos = DoubleVector3(posX,posY,posZ);
    m_trackBall.up = DoubleVector3(upX,upY,upZ);
    m_trackBall.eye = DoubleVector3(-dirX,-dirY,-dirZ);
    update();
}

// Drawing tranparent after opaque meshes is necessary, but not sufficient,
// as a transparent mesh drawn behind another transparent mesh will be hidden.
void OpenGLWindow::displayMeshes() {
    std::set<Mesh>::iterator it=mesh_.begin(), end=mesh_.end();
    for(; it != end; ++it) // Draw opaque meshes
        if(it->getOpacity() == 1.0f)
            it->drawMesh(mode_,mode_);
    for(it=mesh_.begin(); it!=end; ++it) // Draw transparent meshes
        if(it->getOpacity() != 1.0f)
            it->drawMesh(mode_,mode_);
}

void OpenGLWindow::initializeGL() {
    qglClearColor(backgroundColor); // Set background color
    glShadeModel(GL_SMOOTH); // Enable smooth shading
    glEnable(GL_DEPTH_TEST); // For depth consistent drawing
    // Enable blending (for transparency)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    // Set up the cosmic background radiation.
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    // Set up light source 0
    GLfloat light0Pos[]      = { 0.0f, 0.0f, 10.0f, 1.0f };
    GLfloat light0SpotDir[]  = { 0.0f, 0.0f,- 1.0f, 1.0f };
    GLfloat diffuseLight0[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specularLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0SpotDir);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
    glEnable(GL_LIGHT0);
    // Set up shininess for specular rendering
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 25);
}

void OpenGLWindow::paintGL() {
    qglClearColor(backgroundColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglColor(color);
    glEnable(GL_NORMALIZE);
    glLoadIdentity();

    // Setting the lookAt
    // gluLookAt: eye, center, up
    // The following is equivalent, whithout requiring glu, to
    // gluLookAt(m_trackBall.pos.x()-m_trackBall.eye.x(),
    //           m_trackBall.pos.y()-m_trackBall.eye.y(),
    //           m_trackBall.pos.z()-m_trackBall.eye.z(),
    //           m_trackBall.pos.x(), m_trackBall.pos.y(), m_trackBall.pos.z(),
    //           m_trackBall.up.x(), m_trackBall.up.y(), m_trackBall.up.z());
    DoubleVector3 f = m_trackBall.eye / norm(m_trackBall.eye);
    DoubleVector3 up = m_trackBall.up / norm(m_trackBall.up);
    DoubleVector3 s=f^up, u=s^f;
    GLdouble M[4*4] = { // Transposed, as OpenGL expects column major matrices
        s.x(), u.x(), -f.x(), 0,
        s.y(), u.y(), -f.y(), 0,
        s.z(), u.z(), -f.z(), 0,
            0,     0,      0, 1};
    glMultMatrixd(M);
    glTranslated(m_trackBall.eye.x()-m_trackBall.pos.x(),
                 m_trackBall.eye.y()-m_trackBall.pos.y(),
                 m_trackBall.eye.z()-m_trackBall.pos.z());
    displayMeshes();
}

void OpenGLWindow::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = width/static_cast<double>(height);
    // The following is equivalent, whithout requiring glu, to
    // gluPerspective(FOVY, ratio, 0.1, 1000.0);
    const GLdouble ZNear=0.1;
    const GLdouble ZFar=1000.0;
    GLdouble fH = tan(FOVY/2 /180.0*M_PI)*ZNear, fW=fH*ratio;
    glFrustum(-fW,fW, -fH,fH, ZNear, ZFar);
    glMatrixMode(GL_MODELVIEW);
}

QPointF OpenGLWindow::pixelPosToViewPos(const QPointF& p) {
    return QPointF(2.0 * float(p.x()) / width() - 1.0,
                   1.0 - 2.0 * float(p.y()) / height());
}

void OpenGLWindow::mousePressEvent(QMouseEvent *event) {
    QGLWidget::mousePressEvent(event);
    if (event->isAccepted())
        return;
    if(event->modifiers()==Qt::ShiftModifier) {
        if(event->button()==Qt::LeftButton ||
           event->button()==Qt::RightButton) {
#if QT_VERSION < 0x050000
            m_trackBall.push(pixelPosToViewPos(event->posF()));
#else
            m_trackBall.push(pixelPosToViewPos(event->localPos()));
#endif
            event->accept();
        }
    }
    if(event->isAccepted())
        update();
    else
        emit pressedMouseButtons(event->x(), event->y(), event->button(),
                                 event->type(), event->modifiers(),
                                 win_, subWinId_);
}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent *event) {
    QGLWidget::mouseReleaseEvent(event);
    if(! event->isAccepted())
        emit pressedMouseButtons(event->x(), event->y(), event->button(),
                                 event->type(), event->modifiers(),
                                 win_, subWinId_);
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent *event) {
    QGLWidget::mouseMoveEvent(event);
    if (event->isAccepted())
        return;

    if(event->modifiers()==Qt::ShiftModifier) {
        if(event->buttons() & Qt::LeftButton) {
#if QT_VERSION < 0x050000
            m_trackBall.move(pixelPosToViewPos(event->posF()),
                             TrackBall::Rotate);
#else
            m_trackBall.move(pixelPosToViewPos(event->localPos()),
                             TrackBall::Rotate);
#endif
            event->accept();
        }
        if(event->buttons() & Qt::RightButton) {
#if QT_VERSION < 0x050000
            m_trackBall.move(pixelPosToViewPos(event->posF()),
                             TrackBall::Translate);
#else
            m_trackBall.move(pixelPosToViewPos(event->localPos()),
                             TrackBall::Translate);
#endif
            event->accept();
        }
    }
    if(event->isAccepted())
        update();
    else
        emit pressedMouseButtons(event->x(), event->y(), event->button(),
                                 event->type(), event->modifiers(),
                                 win_, subWinId_);
}

void OpenGLWindow::wheelEvent(QWheelEvent* event) {
    QGLWidget::wheelEvent(event);

    if(!event->isAccepted()) {
        if(event->delta()>0)
            m_trackBall.eye *= ZOOM_INCREMENT;
        else
            m_trackBall.eye /= ZOOM_INCREMENT;
        update();
    }
}

void OpenGLWindow::keyPressEvent(QKeyEvent* event) {
    if(event->modifiers()==Qt::ShiftModifier &&
       event->key() == 'M') { // Switch display mode
        if(mode_ == POINT) mode_=FILL;
        else if(mode_ == LINE) mode_=POINT;
        else if(mode_ == FILL) mode_=LINE;
        event->accept();
        update();
    } else if(event->modifiers()==Qt::ShiftModifier &&
              event->key() == 'A') { // Zoom in
        m_trackBall.eye *= ZOOM_INCREMENT;
        event->accept();
        update();
    } else if(event->modifiers()==Qt::ShiftModifier &&
              event->key() == 'Z') { // Zoom out
        m_trackBall.eye /= ZOOM_INCREMENT;
        event->accept();
        update();
    } else if(event->modifiers()==Qt::ShiftModifier &&
              event->key() == 'R') { // Reinit camera
       centerOnMeshes();
       event->accept();
       update();
    }else
        emit pressedKey(event->key(), event->type(), event->modifiers(),
                        win_, subWinId_);
}

void OpenGLWindow::closeEvent(QCloseEvent* event) {
    if(event->spontaneous())
        exit(0);
    emit closed();
    this->QWidget::closeEvent(event);
}

} /* namespace Imagine */

#endif
