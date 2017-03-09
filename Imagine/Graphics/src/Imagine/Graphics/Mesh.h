// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#ifndef IMAGINE_GRAPHICS_MESH_H
#define IMAGINE_GRAPHICS_MESH_H

#include "Types.h"
#include <vector>
#include <cstdlib>

#ifdef IMAGINE_OPENGL

namespace Imagine {
    /// \addtogroup Graphics
    /// @{

    /// Mesh lighting mode.
    enum MeshColorMode
    {
        CONSTANT_COLOR,
        FACE_COLOR,
        VERTEX_COLOR,
        FACE_VALUE,
        VERTEX_VALUE
    };

    /// Mesh shading mode
    enum MeshShadingMode
    {
        FLAT_SHADING,
        SMOOTH_SHADING
    };

    /// Mesh display mode
    enum MeshFaceMode
    {
        POINT,
        LINE,
        FILL
    };

    /// Type of mesh data that holds values.
    enum MeshData
    {
        VERTEX,
        TRIANGLE,
        QUAD
    };

    // ====================================================================== //
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    class MeshInternal;         // Private
#endif

    class Mesh;
    /// Show mesh.
    /// Shows a mesh in active window (must be a 3D window). 
    /// \param M Mesh to show
    /// \param reinitCam Reset camera to view all meshes (same as SHIFT-r)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw3D()
    /// \skipline show mesh
    /// \until ...
    ///
    /// <b>IMPORTANT NOTE</b>:
    /// - A mesh does not live in a window! It can be viewed in more than
    /// one window (showMesh/hideMesh functions). 
    /// - Closing a window does not delete the meshes viewed in it
    /// - To hide the mesh later, you must keep the mesh variable.
    ///     - For instance:
    /// \code
    ///     showMesh(Mesh(...)); // Displayed, but cannot be hidden later 
    /// \endcode
    ///     This is the right thing to do:
    /// \code
    ///         Mesh S(...);
    ///         showMesh(S);
    /// \endcode
    ///     - Inside a function:
    /// \code
    ///         Mesh f() {
    ///           Mesh S(...);
    ///           showMesh(S);
    ///           return S;
    ///         }
    ///         void g() {
    ///             Mesh S=f();
    ///             ... // We can hide it later with hideMesh(S);
    ///         }
    /// \endcode
    /// - However, it is possible to hide all meshes in active window with
    /// clearWindow function
    ///
    /// Function only available if your version of Imagine++ was built
    /// with OpenGL support. The preprocessor macro IMAGINE_OPENGL indicates
    /// that, see file Imagine/Graphics/ConfigGraphics.h
    void showMesh(const Mesh& M, bool reinitCam=true);
    /// Hide mesh.
    /// Removes a mesh from active window (must be a 3D window).
    /// \param M Mesh to hide
    /// \param reinitCam Reset camera to fit all the meshes being viewed
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw3D()
    /// \skipline hide mesh
    ///
    /// Function only available if your version of Imagine++ was built
    /// with OpenGL support. The preprocessor macro IMAGINE_OPENGL indicates
    /// that, see file Imagine/Graphics/ConfigGraphics.h
    void hideMesh(const Mesh& M, bool reinitCam=true);

    /// \headerfile Imagine/Graphics.h "Imagine/Graphics.h"
    /// A mesh representing a 3D object.
    /// This can be a point cloud or a set of triangles or quadrilaterals.
    /// This class is only available if your version of Imagine++ was built
    /// with OpenGL support. The preprocessor macro IMAGINE_OPENGL indicates
    /// that, see file Imagine/Graphics/ConfigGraphics.h
    class Mesh
    {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        MeshInternal* priv;
        int *count;
        void kill();
    public:
        bool operator<(const Mesh& mesh) const; // To put them in a std::set
        void drawMesh(MeshFaceMode front=FILL, MeshFaceMode back=POINT) const;
        FloatPoint3 sum(int& nvertices) const;
        float spread(const FloatPoint3& center) const;
#endif
    public: /* constructor & destructor */
        /// Empty constructor.
        /// Use setVertices or setGeometry to fill it later.
        Mesh();
        /// Constructor (float).
        /// Constructs a mesh (float). Note: arrays are copied into the data
        /// structure, so they could be deleted after mesh creation.
        /// \param vertices array of points
        /// \param nvertices number of points
        /// \param triangles array of triangles (indices to point array, from 0
        /// to nvertices-1)
        /// \param ntriangles number of triangles
        /// \param quads array of quadrilaterals (indices to point array, from 0
        /// to nvertices-1)
        /// \param nquads number of quadrilaterals
        /// \param colorMode color mode (default=CONSTANT_COLOR)
        /// <b>NB: cannot be changed afterwards</b>
        /// \param shadingMode shading mode (default=FLAT_SHADING)
        /// <b>NB: cannot be changed afterwards</b>
        /// \param normals array of nvertices normals (computed if =0)
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline constructor (float)
        /// \until ...
        Mesh(const FloatPoint3* vertices, int nvertices,
             const Triangle* triangles=0, int ntriangles=0,
             const Quad* quads=0, int nquads=0,
             MeshColorMode colorMode=CONSTANT_COLOR,
             MeshShadingMode shadingMode=SMOOTH_SHADING,
             const FloatVector3* normals=0);
        /// Constructor (double).
        /// Constructs a mesh (double). Note: arrays are copied into the data
        /// structure, so they could be deleted after mesh creation.
        /// \param vertices array of points
        /// \param nvertices number of points
        /// \param triangles array of triangles (indices to point array, from 0
        /// to nvertices-1)
        /// \param ntriangles number of triangles
        /// \param quads array of quadrilaterals (indices to point array, from 0
        /// to nvertices-1)
        /// \param nquads number of quadrilaterals
        /// \param colorMode color mode (default=CONSTANT_COLOR)
        /// <b>NB: cannot be changed afterwards</b>
        /// \param shadingMode shading mode (default=FLAT_SHADING)
        /// <b>NB: cannot be changed afterwards</b>
        /// \param normals array of nvertices normals (computed if =0)
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline constructor (double)
        /// \until ...
        Mesh(const DoublePoint3 *vertices, int nvertices,
             const Triangle* triangles=0, int ntriangles=0,
             const Quad *quads=0, int nquads=0,
             MeshColorMode colorMode=CONSTANT_COLOR,
             MeshShadingMode shadingMode=SMOOTH_SHADING,
             const DoubleVector3* normals=0);
        /// Constructor (float vectors).
        /// Constructs a mesh.
        /// \param vertices array of points
        /// \param triangles array of triangles (indices to point array, from 0
        /// to vertices.size()-1)
        /// \param quads array of quadrilaterals (indices to point array, from 0
        /// to vertices.size()-1)
        /// \param colorMode color mode (default=CONSTANT_COLOR)
        /// <b>NB: cannot be changed afterwards</b>
        /// \param shadingMode shading mode (default=FLAT_SHADING)
        /// <b>NB: cannot be changed afterwards</b>
        /// \param normals array of vertices.size() normals (computed if =0)
        Mesh(const std::vector<FloatPoint3>& vertices,
             const std::vector<Triangle>& triangles=std::vector<Triangle>(),
             const std::vector<Quad>& quads=std::vector<Quad>(),
             MeshColorMode colorMode=CONSTANT_COLOR,
             MeshShadingMode shadingMode=SMOOTH_SHADING,
             const std::vector<FloatVector3>& normals=std::vector<FloatVector3>());
        /// Copy constructor.
        /// Shallow copy, shares data with original mesh: if you modify one,
        /// the other will also be affected.
        Mesh(const Mesh&);
        /// Destructor.
        ~Mesh();
        
        /// Read mesh from Wavefront OBJ file.
        /// See http://en.wikipedia.org/wiki/Wavefront_.obj_file
        /// Function only available if your version of Imagine++ was built
        /// with OpenGL support. The preprocessor macro IMAGINE_OPENGL indicates
        /// that, see file Imagine/Graphics/ConfigGraphics.h
        friend bool readMeshFromObjFile(Mesh& mesh,const std::string& fileName);

        /// Assignment operator.
        /// Shallow copy, shares data with original mesh: if you modify one,
        /// the other will also be affected.
        Mesh& operator=(const Mesh&);

        /// Comparison operator.
        /// Two meshes sharing the same data (through copy constructor or
        /// assignment operator) are considered equal.
        bool operator==(const Mesh& mesh) const { return (count==mesh.count); }
        /// Comparison operator.
        /// Two meshes sharing the same data (through copy constructor or
        /// assignment operator) are considered equal.
        bool operator!=(const Mesh& mesh) const { return !operator==(mesh); }

        friend void showMesh(const Mesh& M, bool reinitCam);
        friend void hideMesh(const Mesh& M, bool reinitCam);

    public: /* Accessors */
        /// Set points (float).
        /// Changes vertices positions. Mesh topology remains constant.
        /// \param vertices new positions
        /// \param normals new normals
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set points
        /// \until ...
        void setVertices(const FloatPoint3 *vertices,
                         const FloatVector3 *normals=0);
        /// Set points (double).
        /// Changes vertices positions. Mesh topology remains constant.
        /// \param vertices new positions
        /// \param normals new normals
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set points
        /// \until ...
        void setVertices(const DoublePoint3 *vertices,
                         const DoubleVector3 *normals=0);
        /// Get points.
        const std::vector<FloatPoint3>& vertices() const;
        /// Set geometry (float).
        /// Changes vertices and topology.
        /// \param vertices new vertices
        /// \param nvertices new number of vertices
        /// \param triangles new triangles
        /// \param ntriangles new number of triangles
        /// \param quads new quadrilaterals
        /// \param nquads new number of quadrilaterals
        /// \param normals new normals
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set geometry
        /// \until ...
        void setGeometry(const FloatPoint3 *vertices, int nvertices,
                         const Triangle *triangles=0, int ntriangles=0,
                         const Quad *quads=0, int nquads=0,
                         const FloatVector3 *normals=0);
        /// Set geometry (double).
        /// Changes vertices and topology.
        /// \param vertices new vertices
        /// \param nvertices new number of vertices
        /// \param triangles new triangles
        /// \param ntriangles new number of triangles
        /// \param quads new quadrilaterals
        /// \param nquads new number of quadrilaterals
        /// \param normals new normals
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set geometry
        /// \until ...
        void setGeometry(const DoublePoint3 *vertices, int nvertices,
                         const Triangle *triangles=0, int ntriangles=0,
                         const Quad *quads=0, int nquads=0,
                         const DoubleVector3 *normals=0);


        /// Set color.
        /// Sets color. Mesh should be of CONSTANT_COLOR mode
        /// \param col color
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set color
        /// \until ...
        void setColor(Color col);
        /// Set colors.
        /// Sets colors. Mesh should be of VERTEX_COLOR or FACE_COLOR mode
        /// \param data type of data to hold colors.
        /// \param col colors for each triangle or vertex
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set colors
        /// \until ...
        void setColors(MeshData data, const Color *col);
        /// Default LUT.
        /// Restore default 'rainbow' scale (VERTEX_VALUE or FACE_VALUE modes)
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline default LUT
        /// \until ...
        /// Set range.
        /// Sets range. Mesh should be of VERTEX_VALUE or FACE_VALUE mode.
        /// Values from v0 to v1 are represented by a rainbow.
        /// \param v0,v1 min and max values (default 0 and 1)
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set values
        /// \until ...
        void setRange(float v0, float v1);
        /// Set values.
        /// Sets values. Mesh should be of VERTEX_VALUE or FACE_VALUE mode.
        /// \param data type of data to hold values.
        /// \param val values for each triangle, quad or vertex
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline set values
        /// \until ...
        void setValues(MeshData data, const float *val);
        /// Default LUT.
        /// Restore default 'rainbow' scale (VERTEX_VALUE or FACE_VALUE modes)
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline default LUT
        /// \until ...
        void setDefaultLookupTable();
        /// Set LUT.
        /// Replaces default 'rainbow' scale by a new one (in VERTEX_VALUE or
        /// FACE_VALUE modes)
        /// \param col0 initial color for interpolation for a value of min range
        /// \param col1 final color for interpolation for a value of max range
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline change LUT
        /// \until ...
        void setLookupTable(Color col0, Color col1);
 
        /// Set opacity.
        /// Change mesh opacity.
        /// \param opacity (from 0=transparent to 1=opaque)
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline opacity
        void setOpacity(float opacity);
        /// Get opacity (from 0=transparent to 1=opaque).
        float getOpacity() const;

        /* Static Convenience Functions*/

        /// Arrow.
        /// Constructs an arrow. Act as a CONSTANT_COLOR mesh.
        /// \param base starting point
        /// \param shaft direction (arrow goes from base to base+shaft)
        /// \param r shaft radius
        /// \param resolution adjusts number of facets (default=32)
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline arrow
        static Mesh Arrow(const DoublePoint3 &base, const DoubleVector3 &shaft,
                          double r, int resolution=32);
        /// Cone.
        /// Constructs a cone . Act as a CONSTANT_COLOR mesh.
        /// \param base starting point
        /// \param axis axis
        /// \param r radius
        /// \param resolution adjusts number of facets (default=32)
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline cone      
        static Mesh Cone(const DoublePoint3 &base, const DoubleVector3 &axis,
                         double r, int resolution=32);
        /// Parallelepiped.
        /// Constructs a parallelepiped. Act as a CONSTANT_COLOR mesh.
        /// \param center center
        /// \param axis1,axis2,axis3 cube axes
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline parallelepiped
        static Mesh Cube(const DoublePoint3&center, const DoubleVector3&axis1,
                         const DoubleVector3&axis2, const DoubleVector3&axis3);
        /// Cylinder.
        /// Constructs a cylinder. Act as a CONSTANT_COLOR mesh.
        /// \param center center
        /// \param axis axis
        /// \param r radius
        /// \param res resolution: adjusts number of facets (default=32)
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline cylinder
        static Mesh Cylinder(const DoublePoint3 &center,
                             const DoubleVector3&axis, double r, int res=32);
        /// Parallelogram.
        /// Constructs a parallelogram. Act as a CONSTANT_COLOR mesh.
        /// \param center center
        /// \param axis1,axis2 directions
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline plane     
        static Mesh Plane(const DoublePoint3&center,
                          const DoubleVector3&axis1, const DoubleVector3&axis2);
        /// PointCloud.
        /// Constructs a point cloud. Act as a CONSTANT_COLOR mesh.
        /// \param points array of points
        /// \param n number of points
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline pointcloud
        static Mesh PointCloud(const DoublePoint3 *points, int n);
        /// PolyLine.
        /// Constructs a line through points. Act as a CONSTANT_COLOR mesh.
        /// \param points array of points
        /// \param n number of points
        /// \param closed is the line closed
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline polyline      
        static Mesh PolyLine(DoublePoint3 *points, int n, bool closed);
        /// Sphere.
        /// Constructs a sphere. Act as a CONSTANT_COLOR mesh.
        /// \param center center
        /// \param r radius
        /// \param res resolution: adjusts number of facets (default=32)
        /// \return contructed mesh
        ///
        /// \dontinclude Graphics/test/test.cpp \skip draw3D()
        /// \skipline sphere
        static Mesh Sphere(const DoublePoint3 &center, double r, int res=24);
    };

    /// @}
} /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_MESH_H */

#endif
