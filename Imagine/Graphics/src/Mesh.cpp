#include "Imagine/Graphics/ConfigGraphics.h"
#include "Imagine/Graphics/Mesh.h"
#include <numeric>
#include <sstream>

#ifdef IMAGINE_OPENGL
#include <QtOpenGL>
#endif

#include <cmath>

#ifdef IMAGINE_OPENGL
#if __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#endif

#ifdef _WIN32
#undef min
#undef max
#endif

#ifdef IMAGINE_OPENGL

namespace Imagine {

class MeshInternal {
private:
    FloatPoint3 computeTriangleNormal(int index) const;
    FloatPoint3 computeQuadNormal(int index) const;
    FloatPoint3 computeVertexNormal(int v,
                                    const std::vector<std::vector<int> >&,
                                    const std::vector<std::vector<int> >&)const;
    void computeFaceRings(std::vector<std::vector<int> >& tRings,
                          std::vector<std::vector<int> >& qRings) const;
public:
    void computeNormals();
    void setColorsFromValues();

public:
    static MeshInternal* Arrow(const DoublePoint3 &base,
                               const DoubleVector3 &shaft,
                               double r, int resolution);
    static MeshInternal* Cone(const DoublePoint3 &base,
                              const DoubleVector3 &axis,
                              double r, int resolution);
    static MeshInternal* Cube(const DoublePoint3& center,
                              const DoubleVector3& axis1,
                              const DoubleVector3& axis2,
                              const DoubleVector3& axis3);
    static MeshInternal* Cylinder(const DoublePoint3 &center,
                                  const DoubleVector3 &axis,
                                  double r, int resolution);
    static MeshInternal* Plane(const DoublePoint3& center,
                               const DoubleVector3& axis1,
                               const DoubleVector3& axis2);
    static MeshInternal* PointCloud(const DoublePoint3 *points, int n);
    static MeshInternal* PolyLine(DoublePoint3 *points, int n, bool closed);
    static MeshInternal* Sphere(const DoublePoint3& center,
                                double r, int resolution);

public:
    MeshInternal();
    MeshInternal(const FloatPoint3* vertices_, int nvertices,
                 const Triangle* triangles_, int ntriangles,
                 const Quad* quads_, int nquads,
                 MeshColorMode colorMode_,
                 MeshShadingMode shadingMode_,
                 const FloatVector3* _normals);
    MeshInternal(const DoublePoint3* vertices_, int nvertices,
                 const Triangle* triangles_, int ntriangles,
                 const Quad* quads_, int nquads,
                 MeshColorMode colorMode_,
                 MeshShadingMode shadingMode_,
                 const DoubleVector3* _normals);
    MeshInternal(const std::vector<FloatPoint3>& vertices_,
                 const std::vector<Triangle>& triangles_,
                 const std::vector<Quad>& quads_,
                 MeshColorMode colorMode_,
                 MeshShadingMode shadingMode_,
                 const std::vector<FloatVector3>& normals_);

    inline const FloatPoint3& coords(int index) const
    { return vertices[index]; }
    inline const FloatPoint3& normal(int index) const
    { return normals[index]; }
    inline const Triangle& triangle(int index) const
    { return triangles[index]; }
    inline const Quad& quad(int index) const
    { return quads[index]; }
    inline int triangleVertex(int vInd, int tIndex) const
    { return triangle(tIndex)[vInd]; }
    inline int quadVertex(int vInd, int qIndex) const
    { return quad(qIndex)[vInd]; }
    inline const FloatPoint3& triangleCoords(int vInd, int tInd) const
    { return vertices[ triangleVertex(vInd, tInd) ]; }
    inline const FloatPoint3& quadCoords(int vInd, int qInd) const
    { return vertices[ quadVertex(vInd, qInd) ]; }

    void setGeometry(const FloatPoint3* vertices_, int nvertices,
                     const Triangle* triangles_, int ntriangles,
                     const Quad* quads_, int nquads,
                     const FloatVector3 *normals_);
    void setGeometry(const DoublePoint3* vertices_, int nvertices,
                     const Triangle* triangles_, int ntriangles,
                     const Quad* quads_, int nquads,
                     const DoubleVector3 *normals_);

    void setColor(Color col);
    void setColors(MeshData data, const Color *col);
    void setDefaultLookupTable();
    void setLookupTable(Color col0, Color col1);
    void setRange(float v0, float v1);
    void setValues(MeshData data, const float *val);

    void setOpacity(float opacity_);

    void drawMesh(MeshFaceMode frontFaceMode, MeshFaceMode backFaceMode);

    friend bool readMeshFromObjFile(Mesh& mesh, const std::string& fileName);
public: /* data members */
    std::vector<FloatPoint3> vertices;
    std::vector<FloatVector3> normals;
    std::vector<Triangle> triangles;
    std::vector<Quad> quads;

    // Color of each vertex in the same order as defined in "vertices"
    // Only in CONSTANT_COLOR, VERTEX_COLOR or VERTEX_VALUE colorModes
    std::vector<Color> colors;

    // Color of each triangle in the same order as defined in "triangles"
    // Only in FACE_COLOR or FACE_VALUE colorModes
    std::vector<Color> triangleColors;

    // Color of each quad in the same order as defined in "quad"
    // Only in FACE_COLOR or FACE_VALUE colorModes
    std::vector<Color> quadColors;

    // Vertex values
    // Value of each vertex or face that determines its color in VERTEX_VALUE
    std::vector<float> vertexValues;

    // Face values
    // Value of each triangle (or quad) that determines its color in FACE_VALUE
    std::vector<float> triangleValues;
    std::vector<float> quadValues;

public: /* parameters */
    // Drawing modes
    MeshColorMode colorMode;
    MeshShadingMode shadingMode;
    float opacity;
    float minLookupRange;
    float maxLookupRange;
    Color minLookupColor;
    Color maxLookupColor;
};

FloatPoint3 MeshInternal::computeTriangleNormal(int index) const {
    FloatPoint3 u(triangleCoords(1,index));
    u -= triangleCoords(0,index);
    FloatPoint3 v(triangleCoords(2,index));
    v -= triangleCoords(0,index);
    FloatPoint3 n = u^v;
    n.normalize();
    return n;
}

FloatPoint3 MeshInternal::computeQuadNormal(int index) const {
    FloatPoint3 u(quadCoords(1,index));
    u -= quadCoords(0,index);
    FloatPoint3 v(quadCoords(2,index));
    v -= quadCoords(0,index);
    FloatPoint3 n = u^v;
    n.normalize();
    return n;
}

FloatPoint3 MeshInternal::computeVertexNormal(int v,
                        const std::vector<std::vector<int> >& triRings,
                        const std::vector<std::vector<int> >& quadRings) const {
    FloatVector3 n(0.f);
    const std::vector<int>& faceTriangleRing = triRings[v];
    const std::vector<int>& faceQuadRing = quadRings[v];
    for(size_t t=0; t<faceTriangleRing.size(); ++t)
        n += computeTriangleNormal(faceTriangleRing[t]);
    for(size_t t=0; t<faceQuadRing.size(); ++t)
        n += computeQuadNormal(faceQuadRing[t]);
    n /= static_cast<float>(faceTriangleRing.size() + faceQuadRing.size());
    n.normalize();
    return n;
}

void MeshInternal::computeFaceRings(std::vector<std::vector<int> >& tRings,
                                    std::vector<std::vector<int> >& qRings)const
{
    tRings.resize(vertices.size());
    qRings.resize(vertices.size());

    for (int t=0; t<int(triangles.size()); ++t) {
        tRings[triangleVertex(0,t)].push_back(t);
        tRings[triangleVertex(1,t)].push_back(t);
        tRings[triangleVertex(2,t)].push_back(t);
    }
    for (int q=0; q<int(quads.size()); ++q) {
        qRings[quadVertex(0,q)].push_back(q);
        qRings[quadVertex(1,q)].push_back(q);
        qRings[quadVertex(2,q)].push_back(q);
        qRings[quadVertex(3,q)].push_back(q);
    }
}

void MeshInternal::computeNormals() {
    if(vertices.empty() || (triangles.empty() && quads.empty()))
        return;

    // For each vertex, adjacent/immediate neighboring triangles/quads
    std::vector<std::vector<int> > tRings;
    std::vector<std::vector<int> > qRings;

    computeFaceRings(tRings, qRings);
    normals.resize(vertices.size());
    for(int v=0; v<int(vertices.size()); ++v)
        normals[v] = computeVertexNormal(v, tRings, qRings);
}

MeshInternal::MeshInternal() {
    colorMode = CONSTANT_COLOR;
    shadingMode = SMOOTH_SHADING;
    colors.push_back(Color(127,127,127));
    opacity = 1.0f;
}

MeshInternal::MeshInternal(const FloatPoint3* vertices_, int nvertices,
                           const Triangle* triangles_, int ntriangles,
                           const Quad* quads_, int nquads,
                           MeshColorMode colorMode_,
                           MeshShadingMode shadingMode_,
                           const FloatVector3* _normals)
: colorMode(colorMode_), shadingMode(shadingMode_)
, opacity(1.0f)
{
    setGeometry(vertices_, nvertices, triangles_, ntriangles,
                quads_, nquads, _normals);
    colors.push_back(Color(127,127,127));
    setDefaultLookupTable();
}

MeshInternal::MeshInternal(const DoublePoint3* vertices_, int nvertices,
                           const Triangle *triangles_, int ntriangles,
                           const Quad *quads_, int nquads,
                           MeshColorMode colorMode_,
                           MeshShadingMode shadingMode_,
                           const DoubleVector3* _normals)
: colorMode(colorMode_), shadingMode(shadingMode_)
, opacity(1.0f)
{
    setGeometry(vertices_, nvertices, triangles_, ntriangles,
                quads_, nquads, _normals);
    colors.push_back(Color(127,127,127));
    setDefaultLookupTable();
}

MeshInternal::MeshInternal(const std::vector<FloatPoint3>& vertices_,
                           const std::vector<Triangle>& triangles_,
                           const std::vector<Quad>& quads_,
                           MeshColorMode colorMode_,
                           MeshShadingMode shadingMode_,
                           const std::vector<FloatVector3>& normals_)
: vertices(vertices_),normals(normals_),triangles(triangles_),quads(quads_)
, colorMode(colorMode_), shadingMode(shadingMode_)
, opacity(1.0f)
{
    colors.push_back(Color(127,127,127));
    setDefaultLookupTable();
}

void MeshInternal::setGeometry(const FloatPoint3* vertices_, int nvertices,
                               const Triangle* triangles_, int ntriangles,
                               const Quad* quads_, int nquads,
                               const FloatVector3 *normals_) {
    vertices.clear();
    for(int i=0; i<nvertices; i++)
        vertices.push_back(vertices_[i]);
    triangles.clear();
    for(int i=0; i<ntriangles; i++)
        triangles.push_back(triangles_[i]);
    quads.clear();
    for(int i=0; i<nquads; i++)
        quads.push_back(quads_[i]);
    if(normals_)
        for(int i=0; i<nvertices; i++)
            normals.push_back(normals_[i]);
    else
        computeNormals();
}

void MeshInternal::setGeometry(const DoublePoint3* vertices_, int nvertices,
                               const Triangle* triangles_, int ntriangles,
                               const Quad* quads_, int nquads,
                               const DoubleVector3* normals_) {
    vertices.clear();
    for(int i=0; i<nvertices; i++)
        vertices.push_back(vertices_[i]);
    triangles.clear();
    for(int i=0; i<ntriangles; i++)
        triangles.push_back(triangles_[i]);
    quads.clear();
    for(int i=0; i<nquads; i++)
        quads.push_back(quads_[i]);
    if(normals_)
        for(int i=0; i<nvertices; i++)
            normals.push_back(normals_[i]);
    else
        computeNormals();
}

void Mesh::setGeometry(const FloatPoint3* vertices_, int nvertices,
                       const Triangle* triangles_, int ntriangles,
                       const Quad* quads_, int nquads,
                       const FloatVector3 *normals_) {
    priv->setGeometry(vertices_,nvertices,triangles_,ntriangles,quads_,nquads,
                      normals_);
}
void Mesh::setGeometry(const DoublePoint3* vertices_, int nvertices,
                       const Triangle* triangles_, int ntriangles,
                       const Quad* quads_, int nquads,
                       const DoubleVector3 *normals_) {
    priv->setGeometry(vertices_,nvertices,triangles_,ntriangles,quads_,nquads,
                      normals_);
}

void Mesh::setVertices(const FloatPoint3 *vertices_,
                       const FloatVector3 *normals_) {
    size_t nvertices = priv->vertices.size();
    priv->vertices.clear();
    for(size_t i=0; i<nvertices; i++)
        priv->vertices.push_back(vertices_[i]);
    priv->normals.clear();
    if(normals_)
        for(size_t i=0; i<nvertices; i++)
            priv->normals.push_back(normals_[i]);
    else
        priv->computeNormals();
}
void Mesh::setVertices(const DoublePoint3 *vertices_,
                       const DoubleVector3 *normals_) {
    size_t nvertices = priv->vertices.size();
    priv->vertices.clear();
    for(size_t i=0; i<nvertices; i++)
        priv->vertices.push_back(vertices_[i]);
    priv->normals.clear();
    if(normals_)
        for(size_t i=0; i<nvertices; i++)
            priv->normals.push_back(normals_[i]);
    else
        priv->computeNormals();
}
const std::vector<FloatPoint3>& Mesh::vertices() const {
    return priv->vertices;
}

void Mesh::setColor(Color col) {
    if(priv->colorMode==CONSTANT_COLOR) {
        priv->colors.clear();
        priv->colors.push_back(col);
    }
}

void Mesh::setColors(MeshData data, const Color *col) {
    if(priv->colorMode==CONSTANT_COLOR ||
       priv->colorMode==VERTEX_VALUE ||
       priv->colorMode==FACE_VALUE)
        return;
    if(priv->colorMode==VERTEX_COLOR && data!=VERTEX) {
        std::cerr << "Mesh::setColors: incorrect assignment" << std::endl;
        return;
    }
    if(priv->colorMode==FACE_COLOR && data==VERTEX) {
        std::cerr << "Mesh::setColors: incorrect assignment" << std::endl;
        return;
    }

    switch(data) {
    case VERTEX:
        if(priv->colorMode==VERTEX_COLOR) {
            priv->colors.clear();
            for(size_t i=0; i<priv->vertices.size(); i++)
                priv->colors.push_back(col[i]);
        }
        break;
    case TRIANGLE:
        if(priv->colorMode==FACE_COLOR) {
            priv->triangleColors.clear();
            for(size_t i=0; i<priv->triangles.size(); i++)
                priv->triangleColors.push_back(col[i]);
        }
        break;
    case QUAD:
        if(priv->colorMode==FACE_COLOR) {
            priv->quadColors.clear();
            for(size_t i=0; i<priv->quads.size(); i++)
                priv->quadColors.push_back(col[i]);
        }
    }
}

void MeshInternal::setDefaultLookupTable() {
    if(colorMode==VERTEX_VALUE || colorMode==FACE_VALUE) {
        minLookupColor = Color(85,85,255);
        maxLookupColor = Color(255, 0, 0);
        minLookupRange = 0.0f;
        maxLookupRange = 1.0f;
        setColorsFromValues();
    }
}
void Mesh::setDefaultLookupTable() { priv->setDefaultLookupTable(); }

void Mesh::setLookupTable(Color col0, Color col1) {
    if(priv->colorMode==VERTEX_VALUE || priv->colorMode==FACE_VALUE) {
        priv->minLookupColor = col0;
        priv->maxLookupColor = col1;
        priv->setColorsFromValues();
    }
}

void Mesh::setRange(float v0, float v1) {
    if(priv->colorMode==VERTEX_VALUE || priv->colorMode==FACE_VALUE) {
        if(v0 >= v1)
            return;
        priv->minLookupRange = v0;
        priv->maxLookupRange = v1;
    }
}

void MeshInternal::setColorsFromValues() {
    unsigned minR = std::min(minLookupColor.r(),maxLookupColor.r());
    unsigned maxR = std::max(minLookupColor.r(),maxLookupColor.r());
    unsigned minG = std::min(minLookupColor.g(),maxLookupColor.g());
    unsigned maxG = std::max(minLookupColor.g(),maxLookupColor.g());
    unsigned minB = std::min(minLookupColor.b(),maxLookupColor.b());
    unsigned maxB = std::max(minLookupColor.b(),maxLookupColor.b());
    unsigned int R,G,B;
    const float f = 1.0f/(maxLookupRange-minLookupRange);
    colors.clear();
    for(size_t i=0; i<vertexValues.size(); i++) {
        float v = vertexValues[i];
        R = (v*f)*maxR + (1-v*f)*minR;
        G = (v*f)*maxG + (1-v*f)*minG;
        B = (v*f)*maxB + (1-v*f)*minB;
        colors.push_back(Color(R, G, B));
    }
    triangleColors.clear();
    for(size_t i=0; i<triangleValues.size(); i++) {
        float v = triangleValues[i];
        R = (v*f)*maxR + (1-v*f)*minR;
        G = (v*f)*maxG + (1-v*f)*minG;
        B = (v*f)*maxB + (1-v*f)*minB;
        triangleColors.push_back(Color(R, G, B));
    }
    quadColors.clear();
    for(size_t i=0; i<quadValues.size(); i++) {
        float v = quadValues[i];
        R = (v*f)*maxR + (1-v*f)*minR;
        G = (v*f)*maxG + (1-v*f)*minG;
        B = (v*f)*maxB + (1-v*f)*minB;
        quadColors.push_back(Color(R, G, B));
    }
}

void Mesh::setValues(MeshData data, const float *val) {
    if(! (priv->colorMode==VERTEX_VALUE || priv->colorMode==FACE_VALUE))
        return;
    switch(data) {
    case VERTEX:
        priv->vertexValues.clear();
        for(size_t i=0; i<priv->vertices.size(); i++)
            priv->vertexValues.push_back(val[i]);
        break;
    case TRIANGLE:
        priv->triangleValues.clear();
        for(size_t i=0; i<priv->triangles.size(); i++)
            priv->triangleValues.push_back(val[i]);
        break;
    case QUAD:
        priv->quadValues.clear();
        for(size_t i=0; i<priv->quads.size(); i++)
            priv->quadValues.push_back(val[i]);
        break;
    }
    priv->setColorsFromValues();
}

void Mesh::setOpacity(float opacity_) {
    if(0<=opacity_ && opacity_<=1)
        priv->opacity = opacity_;
    else priv->opacity = 1.0f;
}
float Mesh::getOpacity() const { return priv->opacity; }

// static meshes given for convenience.

MeshInternal* MeshInternal::Arrow(const DoublePoint3 &base,
                                 const DoubleVector3 &shaft,
                                 double r, int resolution) {
    if(norm(shaft) - 2*r <= 0) {
        std::cerr << "Incompatible value of r: please make sure norm(shaft) - 2*r > 0" << std::endl;
        return new MeshInternal;
    }
    MeshInternal* cone = Cone(base + (1-((2*r)/norm(shaft)))*shaft,
                              ((2*r)/norm(shaft))*shaft,
                              r, resolution);
    MeshInternal* arrow = Cylinder(base + ((1 - ((2*r)/norm(shaft)))/2)*shaft,
                                   (1 - ((2*r)/norm(shaft)))*shaft,
                                   r/2, resolution);

    int n = static_cast<int>(arrow->vertices.size());
    for(size_t i=0; i<cone->vertices.size(); i++)
        arrow->vertices.push_back(cone->vertices[i]);
    for(size_t i=0; i<cone->triangles.size(); i++)
        arrow->triangles.push_back(Triangle(n+cone->triangleVertex(0,(int)i),
                                            n+cone->triangleVertex(1,(int)i),
                                            n+cone->triangleVertex(2,(int)i)));
    delete cone;
    arrow->computeNormals();
    return arrow;
}

MeshInternal* MeshInternal::Cone(const DoublePoint3 &base,
                                 const DoubleVector3 &axis,
                                 double r, int resolution) {
    MeshInternal* cone = new MeshInternal;
    FloatPoint3 point;
    double Pi = 3.14159;
    // parameters for rotation
    double axisNorm = std::sqrt(axis.x()*axis.x() + axis.y()*axis.y()+ axis.z()*axis.z());
    double xyAxisNorm = std::sqrt(axis.x()*axis.x() + axis.y()*axis.y());
    double cosTheta = axis.z() / axisNorm;
    double sinTheta = xyAxisNorm / axisNorm;
    double cosPhi = axis.x() / xyAxisNorm;
    double sinPhi = axis.y() / xyAxisNorm;
    double RyArray[9] = {cosTheta, 0., sinTheta, 0., 1., 0., -sinTheta, 0., cosTheta};
    FMatrix<double,3,3> Ry(RyArray);
    double RzArray[9] = {cosPhi, sinPhi, 0., -sinPhi, cosPhi, 0., 0., 0., 1.};
    FMatrix<double,3,3> Rz(RzArray);

    // Setting  side vertices
    for(int i=0; i<resolution; i++) {
        point.z() = 0.;
        point.x() = r*cos((2*i*Pi)/resolution);
        point.y() = r*sin((2*i*Pi)/resolution);
        // Rotation to fit to given axis
        if(xyAxisNorm != 0)
            point = Rz*(Ry*point);
        // Push back
        cone->vertices.push_back(point);
    }
    // Setting top vertex
    cone->vertices.push_back(axis);
    // Setting base vertex
    cone->vertices.push_back(FloatPoint3(0., 0., 0.));

    // Translate to fit base
    for(size_t i=0; i<cone->vertices.size(); i++)
        cone->vertices[i] += base;

    // Setting side triangles
    for(int i=0; i<resolution; i++)
        cone->triangles.push_back(Triangle((i+1)%resolution, i, resolution));

    // Setting base triangles
    for(int i=0; i<resolution; i++)
        cone->triangles.push_back(Triangle(i, (i+1)%resolution, resolution+1));

    cone->computeNormals();
    return cone;
}

MeshInternal* MeshInternal::Cube(const DoublePoint3& center,
                                 const DoubleVector3& axis1,
                                 const DoubleVector3& axis2,
                                 const DoubleVector3& axis3) {
    MeshInternal* cube = new MeshInternal;
    FloatPoint3 point = center - (axis1 / 2) - (axis2 / 2) - (axis3 / 2);

    // Setting vertices
    cube->vertices.push_back(point);
    point += axis1;
    cube->vertices.push_back(point);
    point += axis2;
    cube->vertices.push_back(point);
    point -= axis1;
    cube->vertices.push_back(point);
    point -= axis2;
    point += axis3;
    cube->vertices.push_back(point);
    point += axis1;
    cube->vertices.push_back(point);
    point += axis2;
    cube->vertices.push_back(point);
    point -= axis1;
    cube->vertices.push_back(point);

    // Setting quads
    cube->quads.push_back(Quad(3,2,1,0));
    cube->quads.push_back(Quad(4,5,6,7));
    cube->quads.push_back(Quad(0,1,5,4));
    cube->quads.push_back(Quad(1,2,6,5));
    cube->quads.push_back(Quad(2,3,7,6));
    cube->quads.push_back(Quad(3,0,4,7));

    cube->computeNormals();
    return cube;
}

MeshInternal* MeshInternal::Cylinder(const DoublePoint3 &center,
                                     const DoubleVector3 &axis,
                                     double r, int resolution) {
    MeshInternal* cylinder = new MeshInternal;
    FloatPoint3 point;
    double Pi = 3.14159;
    // parameters for rotation
    double axisNorm = std::sqrt(axis.x()*axis.x() + axis.y()*axis.y()+ axis.z()*axis.z());
    double xyAxisNorm = std::sqrt(axis.x()*axis.x() + axis.y()*axis.y());
    double cosTheta = axis.z() / axisNorm;
    double sinTheta = xyAxisNorm / axisNorm;
    double cosPhi = axis.x() / xyAxisNorm;
    double sinPhi = axis.y() / xyAxisNorm;
    double RyArray[9] = {cosTheta, 0., sinTheta, 0., 1., 0., -sinTheta, 0., cosTheta};
    FMatrix<double,3,3> Ry(RyArray);
    double RzArray[9] = {cosPhi, sinPhi, 0., -sinPhi, cosPhi, 0., 0., 0., 1.};
    FMatrix<double,3,3> Rz(RzArray);

    // Setting bottom vertices
    for(int i=0; i<resolution; i++) {
        point.z() = -axisNorm/2;
        point.x() = r*cos((2*i*Pi)/resolution);
        point.y() = r*sin((2*i*Pi)/resolution);
        // Rotation to fit to given axis
        if(xyAxisNorm != 0)
            point = Rz*(Ry*point);
        // Push back
        cylinder->vertices.push_back(point);
    }
    // Setting top vertices
    for(int i=0; i<resolution; i++) {
        point.z() = axisNorm/2;
        point.x() = r*cos((2*i*Pi)/resolution);
        point.y() = r*sin((2*i*Pi)/resolution);
        // Rotation to fit to given axis
        if(xyAxisNorm != 0)
            point = Rz*(Ry*point);
        // Push back
        cylinder->vertices.push_back(point);
    }
    // Setting center vertices
    // Bottom
    point = -FloatPoint3(0, 0, axisNorm/2);
    if(xyAxisNorm != 0)
        point = Rz*(Ry*point);
    cylinder->vertices.push_back(point);
    // Top
    point = FloatPoint3(0, 0, axisNorm/2);
    if(xyAxisNorm != 0)
        point = Rz*(Ry*point);
    cylinder->vertices.push_back(point);

    // Translate to fit center
    for(size_t i=0; i<cylinder->vertices.size(); i++)
        cylinder->vertices[i] += center;

    // Setting side triangles
    for(int i=0; i<resolution; i++)
        cylinder->quads.push_back(Quad(i, (i+1)%resolution, resolution+((i+1)%resolution), resolution+i));

    // Setting bottom/top triangles
    for(int i=0; i<resolution; i++) {
        cylinder->triangles.push_back(Triangle(2*resolution,
                                               (i+1)%resolution, i));
        cylinder->triangles.push_back(Triangle(resolution+i,
                                               resolution+((i+1)%resolution),
                                               2*resolution+1));
    }

    cylinder->computeNormals();
    return cylinder;
}

MeshInternal* MeshInternal::Plane(const DoublePoint3& center,
                                  const DoubleVector3& axis1,
                                  const DoubleVector3& axis2) {
    FloatPoint3 point;
    MeshInternal* plane = new MeshInternal;

    // Setting vertices
    point = center - ((axis1 + axis2) / 2);
    plane->vertices.push_back(point);
    point += axis1;
    plane->vertices.push_back(point);
    point += axis2;
    plane->vertices.push_back(point);
    point -= axis1;
    plane->vertices.push_back(point);
    point -= axis2;
    point -= (axis1^axis2)/1000;
    plane->vertices.push_back(point);
    point += axis1;
    plane->vertices.push_back(point);
    point += axis2;
    plane->vertices.push_back(point);
    point -= axis1;
    plane->vertices.push_back(point);
    point -= axis2;

    // Setting triangles
    plane->quads.push_back(Quad(0, 1, 2, 3));
    plane->quads.push_back(Quad(7, 6, 5, 4));

    FloatVector3 normal = (axis1^axis2).normalize();
    for(int i=0; i<4; i++)
        plane->normals.push_back(normal);
    for(int i=0; i<4; i++)
        plane->normals.push_back(-normal);

    return plane;
}

MeshInternal* MeshInternal::PointCloud(const DoublePoint3 *points, int n) {
    return new MeshInternal(points,n,0,0,0,0,CONSTANT_COLOR,SMOOTH_SHADING,0);
}

MeshInternal* MeshInternal::PolyLine(DoublePoint3 *points, int n, bool closed) {
    MeshInternal* PolyLine_ =
        new MeshInternal(points,n,0,0,0,0, CONSTANT_COLOR, SMOOTH_SHADING,0);
    if(closed)
        PolyLine_->vertices.push_back(points[0]);
    return PolyLine_;
}

MeshInternal* MeshInternal::Sphere(const DoublePoint3& center,
                                   double r, int resolution) {
    MeshInternal* sphere = new MeshInternal;
    FloatPoint3 point;
    double Pi = 3.14159;

    // Setting vertices
    for(int i=1; i<resolution; i++) {
        point.z() = center.z() + r*cos(i*Pi/resolution);
        for(int j=0; j<2*resolution; j++) {
            point.x() = center.x()+ r*sin(i*Pi/resolution)*cos(j*Pi/resolution);
            point.y() = center.y()+ r*sin(i*Pi/resolution)*sin(j*Pi/resolution);
            sphere->vertices.push_back(point);
        }
    }
    // Setting bottom/top vertex
    point = center;
    point.z() += r;
    sphere->vertices.push_back(point);
    point.z() -= 2*r;
    sphere->vertices.push_back(point);

    // Setting side quads
    for(int i=0; i<resolution-2; i++) {
        for(int j=0; j<2*resolution; j++)
            sphere->quads.push_back(Quad( 2*(i+1)*resolution + j,
                                          2*(i+1)*resolution +
                                          ((j+1)%(2*resolution)),
                                          2*i*resolution +
                                          ((j+1)%(2*resolution)),
                                          2*i*resolution + j ));
    }

    // Setting bottom/top triangles
    for(int i=0; i<2*resolution; i++) {
        sphere->triangles.push_back(Triangle( i,
                                              (i+1)%(2*resolution),
                                              2*resolution*(resolution-1)));
        sphere->triangles.push_back(Triangle( 2*resolution*(resolution-1)+1,
                                              2*resolution*(resolution-2)+
                                              ((i+1)%(2*resolution)),
                                              2*resolution*(resolution-2)+i));
    }

    // Setting normals
    for(int i=0; i<2*resolution*(resolution-1)+2; i++)
        sphere->normals.push_back((sphere->vertices[i]-center).normalize());

    return sphere;
}

inline void setMaterial(GLfloat material[4]) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material);
}

// ======================================================================
// Main mesh drawing function
void MeshInternal::drawMesh(MeshFaceMode frontFaceMode,
                            MeshFaceMode backFaceMode) {
    // Abort drawing if mesh is empty or uncomplete
    if(vertices.empty())
        return;

    // Parametrization
    GLenum mode;
    switch(frontFaceMode) {
    case POINT:
        mode = GL_POINT;
        break;
    case LINE:
        mode = GL_LINE;
        break;
    case FILL:
        mode = GL_FILL;
        break;
    }
    glPolygonMode(GL_FRONT, mode);
    switch(backFaceMode) {
    case POINT:
        mode = GL_POINT;
        break;
    case LINE:
        mode = GL_LINE;
        break;
    case FILL:
        mode = GL_FILL;
        break;
    }
    glPolygonMode(GL_BACK, mode);
    switch(shadingMode) {
    case FLAT_SHADING:
        glShadeModel(GL_FLAT);
        break;
    case SMOOTH_SHADING:
        glShadeModel(GL_SMOOTH);
        break;
    }

    int vInd;
    GLfloat material[4];
    material[3] = opacity;

    // Draw points only if mesh is a PointCloud
    if(triangles.empty() && quads.empty() &&
       frontFaceMode!=LINE && backFaceMode!=LINE) {
        if(colorMode==CONSTANT_COLOR) {
            material[0] = float(colors[0].r()) / 255.0f;
            material[1] = float(colors[0].g()) / 255.0f;
            material[2] = float(colors[0].b()) / 255.0f;
            setMaterial(material);
        }
        glBegin(GL_POINTS); {
            for(size_t i=0; i<vertices.size(); ++i) {
                if(colorMode == VERTEX_COLOR || colorMode == VERTEX_VALUE) {
                    material[0] = float(colors[i].r()) / 255.0f;
                    material[1] = float(colors[i].g()) / 255.0f;
                    material[2] = float(colors[i].b()) / 255.0f;
                    setMaterial(material);
                }
                glVertex3fv(vertices[i].data());
            }
        } glEnd();
        return;
    }

    // Draw Lines only if mesh is a PolyLine
    if(triangles.empty() && quads.empty()) {
        if(colorMode==CONSTANT_COLOR) {
            material[0] = float(colors[0].r()) / 255.0f;
            material[1] = float(colors[0].g()) / 255.0f;
            material[2] = float(colors[0].b()) / 255.0f;
            setMaterial(material);
        }
        glBegin(GL_LINES); {
            for(size_t i=0; i+1<vertices.size(); ++i) {
                // Vertex 1
                if(colorMode==VERTEX_COLOR || colorMode==VERTEX_VALUE) {
                    material[0] = float(colors[i].r()) / 255.0f;
                    material[1] = float(colors[i].g()) / 255.0f;
                    material[2] = float(colors[i].b()) / 255.0f;
                    setMaterial(material);
                }
                glVertex3fv(vertices[i].data());
                // Vertex 2
                if(colorMode==VERTEX_COLOR || colorMode==VERTEX_VALUE) {
                    material[0] = float(colors[i+1].r()) / 255.0f;
                    material[1] = float(colors[i+1].g()) / 255.0f;
                    material[2] = float(colors[i+1].b()) / 255.0f;
                    setMaterial(material);
                }
                glVertex3fv(vertices[i+1].data());
            }
        } glEnd();
        return;
    }

    // Draw triangles
    if(!triangles.empty()) {
        if(colorMode==CONSTANT_COLOR) {
            material[0] = float(colors[0].r()) / 255.0f;
            material[1] = float(colors[0].g()) / 255.0f;
            material[2] = float(colors[0].b()) / 255.0f;
            setMaterial(material);
        }
        glBegin(GL_TRIANGLES);
        for(size_t t=0; t<triangles.size(); ++t) {
            if(colorMode==FACE_COLOR || colorMode==FACE_VALUE) {
                material[0] = float(triangleColors[t].r()) / 255.0f;
                material[1] = float(triangleColors[t].g()) / 255.0f;
                material[2] = float(triangleColors[t].b()) / 255.0f;
                setMaterial(material);
            }
            for(int v=0; v<3; ++v) {
                vInd = triangleVertex(v,(int)t);
                if(colorMode==VERTEX_COLOR || colorMode==VERTEX_VALUE) {
                    material[0] = float(colors[vInd].r()) / 255.0f;
                    material[1] = float(colors[vInd].g()) / 255.0f;
                    material[2] = float(colors[vInd].b()) / 255.0f;
                    setMaterial(material);
                }
                glNormal3fv(normal(vInd).data());
                glVertex3fv(coords(vInd).data());
            }
        }
        glEnd();
    }

    // Draw quads
    if(!quads.empty()) {
        if(colorMode==CONSTANT_COLOR) {
            material[0] = float(colors[0].r()) / 255.0f;
            material[1] = float(colors[0].g()) / 255.0f;
            material[2] = float(colors[0].b()) / 255.0f;
            setMaterial(material);
        }
        glBegin(GL_QUADS);
        for(size_t q=0; q<quads.size(); ++q) {
            if(colorMode==FACE_COLOR || colorMode==FACE_VALUE) {
                material[0] = float(quadColors[q].r()) / 255.0f;
                material[1] = float(quadColors[q].g()) / 255.0f;
                material[2] = float(quadColors[q].b()) / 255.0f;
                setMaterial(material);
            }
            for(int v=0; v<4; ++v) {
                vInd = quadVertex(v,(int)q);
                if(colorMode==VERTEX_COLOR || colorMode==VERTEX_VALUE) {
                    material[0] = float(colors[vInd].r()) / 255.0f;
                    material[1] = float(colors[vInd].g()) / 255.0f;
                    material[2] = float(colors[vInd].b()) / 255.0f;
                    setMaterial(material);
                }
                glNormal3fv(normal(vInd).data());
                glVertex3fv(coords(vInd).data());
            }
        }
        glEnd();
    }
}

// ====================================================================== //
// Utility functions.

// Sum of vertex vectors, useful to compute centroid
FloatPoint3 Mesh::sum(int& nvertices) const {
    nvertices = (int)priv->vertices.size();
    FloatPoint3 s(0,0,0);
    std::vector<FloatPoint3>::const_iterator
        it =priv->vertices.begin(),
        end=priv->vertices.end();
    for(; it!=end; ++it)
        s += *it;
    return s;
}

// Max distance to point
float Mesh::spread(const FloatPoint3& center) const {
    float s=0;
    std::vector<FloatPoint3>::const_iterator
        it =priv->vertices.begin(),
        end=priv->vertices.end();
    for(; it!=end; ++it)
        s = std::max(s, maxNorm(*it-center));
    return s;
}

    // ====================================================================== //
    // I/O
    bool readMeshFromObjFile(Mesh& mesh, const std::string& fileName)
    {
        // Attempt to read file.
        std::ifstream file(fileName.c_str());
        if(!file)
        {
            std::cerr << "Error reading file!" << std::endl;
            return false;
        }
        
        // Clear the mesh data structure.
        mesh = Mesh();

        // Fill the mesh data structure.
        std::string line;
        while ( std::getline(file, line) )
        {
            std::stringstream ss;
            ss << line;
            char type;
            ss >> type;
            if(type=='v')
            {
                float x, y, z;
                ss >> x >> y >> z;
                mesh.priv->vertices.push_back(FloatPoint3(x, y, z));
            }
            if(type=='f')
            {
                int a, b, c;
                ss >> a >> b >> c;
                mesh.priv->triangles.push_back(Triangle(a-1, b-1, c-1));
            }
        }

        mesh.priv->computeNormals();
        return true;
    }

// ======================================================================
// Mesh implementation

Mesh::Mesh()
: priv(new MeshInternal), count(new int(1))
{}

Mesh::Mesh(const FloatPoint3* vertices, int nvertices,
           const Triangle* triangles, int ntriangles,
           const Quad* quads, int nquads,
           MeshColorMode colorMode,
           MeshShadingMode shadingMode,
           const FloatVector3* normals)
: priv(new MeshInternal(vertices,nvertices, triangles,ntriangles, quads,nquads,
                        colorMode, shadingMode, normals))
, count(new int(1))
{}

Mesh::Mesh(const DoublePoint3 *vertices, int nvertices,
           const Triangle* triangles, int ntriangles,
           const Quad *quads, int nquads,
           MeshColorMode colorMode,
           MeshShadingMode shadingMode,
           const DoubleVector3* normals)
: priv(new MeshInternal(vertices,nvertices, triangles,ntriangles, quads,nquads,
                        colorMode, shadingMode, normals))
, count(new int(1))
{}

Mesh::Mesh(const std::vector<FloatPoint3>& vertices,
           const std::vector<Triangle>& triangles,
           const std::vector<Quad>& quads,
           MeshColorMode colorMode,
           MeshShadingMode shadingMode,
           const std::vector<FloatVector3>& normals)
: priv(new MeshInternal(vertices,triangles,quads,colorMode,shadingMode,normals))
, count(new int(1))
{}

Mesh::Mesh(const Mesh& mesh)
: priv(mesh.priv), count(mesh.count)
{
    ++*count;
}

Mesh::~Mesh() {
    kill();
}

void Mesh::kill() {
    if(--*count == 0) {
        delete priv;
        delete count;
    }
}

Mesh& Mesh::operator=(const Mesh& mesh) {
    if(this != &mesh) {
        kill();
        priv = mesh.priv;
        count = mesh.count;
        ++*count;
    }
    return *this;
}

bool Mesh::operator<(const Mesh& mesh) const {
    return (count<mesh.count);
}

void Mesh::drawMesh(MeshFaceMode front, MeshFaceMode back) const {
    priv->drawMesh(front, back);
}

Mesh Mesh::Arrow(const DoublePoint3 &base, const DoubleVector3 &shaft,
                 double r, int resolution) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::Arrow(base,shaft,r,resolution);
    return mesh;
}

Mesh Mesh::Cone(const DoublePoint3 &base, const DoubleVector3 &axis,
                double r, int resolution) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::Cone(base,axis,r,resolution);
    return mesh;
}
Mesh Mesh::Cube(const DoublePoint3&center, const DoubleVector3&axis1,
                const DoubleVector3&axis2, const DoubleVector3&axis3) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::Cube(center,axis1,axis2,axis3);
    return mesh;
}
Mesh Mesh::Cylinder(const DoublePoint3 &center,
                    const DoubleVector3&axis, double r, int res) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::Cylinder(center,axis,r,res);
    return mesh;
}
Mesh Mesh::Plane(const DoublePoint3&center,
                 const DoubleVector3&axis1, const DoubleVector3&axis2) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::Plane(center,axis1,axis2);
    return mesh;
}
Mesh Mesh::PointCloud(const DoublePoint3 *points, int n) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::PointCloud(points,n);
    return mesh;
}
Mesh Mesh::PolyLine(DoublePoint3 *points, int n, bool closed) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::PolyLine(points,n,closed);
    return mesh;
}
Mesh Mesh::Sphere(const DoublePoint3 &center, double r, int res) {
    Mesh mesh; delete mesh.priv;
    mesh.priv = MeshInternal::Sphere(center,r,res);
    return mesh;
}

} /* namespace Imagine */

#endif
