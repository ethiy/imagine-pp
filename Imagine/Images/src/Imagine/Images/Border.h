// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// Border access

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace Imagine {

    template <typename T, int dim> class Image;
    template <typename T> class PixelTraits;

    // Neumann border condition
    template <typename T, int dim> class NeumannBorder {
    public:
        T operator() (const Image<T,dim> &I, const Coords<dim> &p) const {
            Coords<dim> q;
            for (int i=0;i<dim;i++) {
                if (p[i]>=I.size(i)) q[i] = I.size(i)-1;
                else if (p[i]<0) q[i] = 0;
                else q[i] = p[i];
            }
            return I(q);
        }
    };

    // Dirichlet border condition
    template <typename T, int dim> class DirichletBorder {
    public:
        DirichletBorder(T out = T(0)) : _out(out) {}

        T operator() (const Image<T,dim> &I, const Coords<dim> &p) const {
            for (int i=0;i<dim;i++) {
                if (p[i]>=I.size(i)) return _out;
                if (p[i]<0) return _out;
            }
            return I(p);
        }
    protected:
        T _out;
    };

    // Mirror border condition (edge pixels are not duplicated on the border)
    template <typename T, int dim> class MirrorBorder {
    public:
        T operator() (const Image<T,dim> &I, const Coords<dim> &p) const {
            Coords<dim> q(p);
            for (int i=0;i<dim;++i) {
                if (q[i]<0) q[i] = -q[i];
                if (q[i]>=I.size(i)) {
                    q[i] = q[i]%(2*I.size(i)-2);
                    if (q[i]>=I.size(i)) q[i] = 2*I.size(i)-2-q[i];
                }
            }
            return I(q);
        }
    };


    // Inversed mirror border condition
    template <typename T, int dim> class InvMirrorBorder {
    public:
        T operator() (const Image<T,dim> &I, const Coords<dim> &p) const {
            Coords<dim> q(p), m;
            for (int i=0;i<dim;++i) {
                if (p[i]>=I.size(i)) m[i] = I.size(i)-1;
                else if (p[i]<0) m[i] = 0;
                else m[i] = p[i];
                if (q[i]<0) q[i] = -q[i];
                if (q[i]>=I.size(i)) {
                    q[i] = q[i]%(2*I.size(i)-2);
                    if (q[i]>=I.size(i)) q[i] = 2*I.size(i)-2-q[i];
                    m[i] = I.size(i)-1;
                }
            }
            return I(m)*typename PixelTraits<T>::scalar_type(2)-I(q);
        }
    };


    // TODO: PeriodicBorder

    template <typename T, int dim, class BorderCondition> inline T border(const Image<T,dim> &I, const Coords<dim> &x, const BorderCondition &bc) {
        return bc(I,x);
    }

    template <typename T, class BorderCondition> inline T border(const Image<T,1> &I, int x, const BorderCondition &bc) {
        return border(I, Coords<1>(x), bc);
    }

    template <typename T, class BorderCondition> inline T border(const Image<T,2> &I, int x, int y, const BorderCondition &bc) {
        return border(I, Coords<2>(x,y), bc);
    }

    template <typename T, class BorderCondition> inline T border(const Image<T,3> &I, int x, int y, int z, const BorderCondition &bc) {
        return border(I, Coords<3>(x,y,z), bc);
    }

}

#endif
