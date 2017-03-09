#ifndef IMAGINE_GRAPHICS_OPENGLWINDOW_H
#define IMAGINE_GRAPHICS_OPENGLWINDOW_H

#include "Imagine/Graphics/ConfigGraphics.h"

#include <set>

#ifdef IMAGINE_OPENGL
#include <QtOpenGL>
#endif

#include <QEvent>
#include <QQuaternion>
#include "Imagine/Graphics/Mesh.h"

namespace Imagine {

class TrackBall {
public:
    enum Mode { Rotate, Translate };
    TrackBall(): pos(0,0,0), eye(1,0,0), up(0,0,1) {}
    void push(const QPointF& p) { lastPos_ = p; }
    void move(const QPointF& p, Mode m);

    DoubleVector3 pos; // Point of scene at center of camera
    DoubleVector3 eye; // Where the camera is (relative to @position)
    DoubleVector3 up; // Vector pointing upward
private:
    QPointF lastPos_; // Last mouse position (coordinates in [-1,1])
};

// OpenGLWindow class
#ifdef IMAGINE_OPENGL
class OpenGLWindow : public QGLWidget {
    Q_OBJECT
public:
    OpenGLWindow(Window win, int subWinId, int width, int height,
                 const QString& windowTitle="Imagine++", int x=-1, int y=-1,
                 QWidget *parent=0);
    QSize sizeHint() { return QSize(width_,height_); }

public slots:
    void setBackground(const QColor& c);
    void addMesh(const Mesh& mesh, bool reinitCam);
    void removeMesh(const Mesh& mesh, bool reinitCam);
    void clear();
    void setLookAt(double eyeX, double eyeY, double eyeZ,
                   double centerX, double centerY, double centerZ,
                   double upX, double upY, double upZ);
    void displayMeshes();
    void centerOnMeshes();
    void allowUpdates(bool allow) { setUpdatesEnabled(allow); }
    void capture(QImage* image);

signals:
    void pressedMouseButtons(int x,int y, Qt::MouseButtons buttons,
                             QEvent::Type type, Qt::KeyboardModifiers mod,
                             Window win, int subWin);
    void pressedKey(int key, QEvent::Type type, Qt::KeyboardModifiers mod,
                    Window win, int subWin);
    void closed();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);

private:
    QPointF pixelPosToViewPos(const QPointF& p);

private:
    Window win_;
    int subWinId_;

    MeshFaceMode mode_;
    std::set<Mesh> mesh_;

    FloatPoint3 centerVec;
    float radius;
    TrackBall m_trackBall;

    QColor backgroundColor, color;
    int width_;
    int height_;
};
#endif
} /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_OPENGLWINDOW_H */
