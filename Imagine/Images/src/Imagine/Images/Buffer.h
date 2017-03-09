// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// Buffered/convert read / write
    
#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace Imagine {
    template <class TI, class TO, int dim> bool readBuffer(Image<TO,dim> &I, std::istream &in) {
        size_t size = I.totalSize();
        TI *buffer = new TI[size];
        in.read((char *)buffer,size*sizeof(TI));
        for (size_t i=0;i<size;i++) I[i] = TO( buffer[i] );
        delete [] buffer;
        return true;
    }

    template <class TO, class TI, int dim> bool writeBuffer(const Image<TI,dim> &I, std::ostream &out) {
        size_t size = I.totalSize();
        TO *buffer = new TO[size];
        for (size_t i=0;i<size;i++) buffer[i] = TO( I[i] );
        out.write((char *)buffer,size*sizeof(TO));
        delete [] buffer;
        return true;
    }
}

#endif
