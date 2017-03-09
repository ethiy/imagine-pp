// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include "AnalyzeHeader.h"
#include "Buffer.h"

namespace Imagine {
    /// \addtogroup Images
    /// @{

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Analyze type constants
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template <typename T> inline short type_Analyze() { return DT_UNKNOWN; }
    template <> inline short type_Analyze<unsigned char>() { return DT_UNSIGNED_CHAR; }
    template <> inline short type_Analyze<short>() { return DT_SIGNED_SHORT; }
    template <> inline short type_Analyze<int>() { return DT_SIGNED_INT; }
    template <> inline short type_Analyze<float>() { return DT_FLOAT; }
    template <> inline short type_Analyze<double>() { return DT_DOUBLE; }
#endif

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Load Analyze file.
    /// Loads an image from an Analyze file (medical imaging) (extensions IMG and HDR)
    /// \param I image to load
    /// \param name file name
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline Analyze tests
    /// \until ...
    template <typename T, int dim>
    inline bool loadAnalyze(Image<T,dim> &I, const std::string name) {

        // Remove extension from filename if any
        std::string noextension(name);
        std::string::size_type size = noextension.rfind('.');
        if (size != std::string::npos) noextension.resize(size);

        // Build header and data filenames and open files
        std::string dataname = noextension + ".img";
        std::string headername = noextension + ".hdr";
        std::ifstream headerfile(headername.c_str(),std::ios::binary);
        if (!headerfile.is_open()) {
            std::cerr << "Unable to open '" << headername << "'" << std::endl;
            return false;
        }
        std::ifstream datafile(dataname.c_str(),std::ios::binary);
        if (!datafile.is_open()) {
            std::cerr << "Unable to open '" << dataname << "'" << std::endl;
            return false;
        }

        // Read header
        Analyze::dsr header;
        headerfile.read((char *)(&header),sizeof(Analyze::dsr));
        headerfile.close();

        // Read image dimensions and setSize image
        int ndim = header.dime.dim[0];
        if (ndim < dim) {
            std::cerr << "Dimension mismatch" << std::endl;
            return false;
        }
        Coords<dim> dm;
        for (int i=0;i<dim;i++) dm[i] = header.dime.dim[i+1];
        I.setSize(dm);

        // Read data
        switch (header.dime.datatype) {
            case DT_UNSIGNED_CHAR : return readBuffer<unsigned char,T,dim>(I,datafile);
            case DT_SIGNED_SHORT : return readBuffer<short int,T,dim>(I,datafile);
            case DT_SIGNED_INT : return readBuffer<int,T,dim>(I,datafile);
            case DT_FLOAT : return readBuffer<float,T,dim>(I,datafile);
            case DT_DOUBLE : return readBuffer<double,T,dim>(I,datafile);
        }

        std::cerr << "Unkwnown data type" << std::endl;
        return false;
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Save Analyze file.
    /// Saves an image into an Analyze file (medical imaging) (extensions IMG and HDR)
    /// \tparam T0 output type
    /// \tparam TI image type
    /// \param I image to save
    /// \param name file name
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline Analyze tests
    /// \until ...
    template <typename TO, typename TI, int dim>
    inline bool saveAnalyze(const Image<TI,dim> &I, const std::string name) {
        short type = type_Analyze<TO>();
        if (type == DT_UNKNOWN) {
            std::cerr << "Data not handled by the Analyze format" << std::endl;
            return false;
        }

        // Remove extension from filename if any
        std::string noextension(name);
        std::string::size_type size = noextension.rfind('.');
        if (size != std::string::npos) noextension.resize(size);

        /// Build header and data filenames and open files
        std::string dataname = noextension + ".img";
        std::string headername = noextension + ".hdr";
        std::ofstream headerfile(headername.c_str(),std::ios::binary);
        if (!headerfile.is_open()) {
            std::cerr << "Unable to open '" << headername << "'" << std::endl;
            return false;
        }
        std::ofstream datafile(dataname.c_str(),std::ios::binary);
        if (!datafile.is_open()) {
            std::cerr << "Unable to open '" << dataname << "'" << std::endl;
            return false;
        }

        // Fill and write header
        Analyze::dsr header;
        memset(&header,0,sizeof(Analyze::dsr));
        header.hk.sizeof_hdr = sizeof(Analyze::dsr);
        header.hk.regular = 'r';
        header.dime.dim[0] = dim;
        for (int i=0;i<dim;i++) header.dime.dim[i+1] = I.size(i);
        header.dime.datatype = type;
        header.dime.pixdim[1] = 1.f;
        header.dime.pixdim[2] = 1.f;
        header.dime.pixdim[3] = 1.f;
        headerfile.write((const char *)(&header),sizeof(Analyze::dsr));
        headerfile.close();

        // Write the data buffer
        return writeBuffer<TO,TI,dim>(I,datafile);
    }

    ///@}
}
