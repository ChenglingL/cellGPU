/*

Highly Optimized Object-oriented Many-particle Dynamics -- Blue Edition
(HOOMD-blue) Open Source Software License Copyright 2009-2016 The Regents of
the University of Michigan All rights reserved.

HOOMD-blue may contain modifications ("Contributions") provided, and to which
copyright is held, by various Contributors who have granted The Regents of the
University of Michigan the right to modify and/or distribute such Contributions.

You may redistribute, use, and create derivate works of HOOMD-blue, in source
and binary forms, provided you abide by the following conditions:

* Redistributions of source code must retain the above copyright notice, this
list of conditions, and the following disclaimer both in the code and
prominently in any materials provided with the distribution.

* Redistributions in binary form must reproduce the above copyright notice, this
list of conditions, and the following disclaimer in the documentation and/or
other materials provided with the distribution.

* All publications and presentations based on HOOMD-blue, including any reports
or published results obtained, in whole or in part, with HOOMD-blue, will
acknowledge its use according to the terms posted at the time of submission on:
http://codeblue.umich.edu/hoomd-blue/citations.html

* Any electronic documents citing HOOMD-Blue will link to the HOOMD-Blue website:
http://codeblue.umich.edu/hoomd-blue/

* Apart from the above required attributions, neither the name of the copyright
holder nor the names of HOOMD-blue's contributors may be used to endorse or
promote products derived from this software without specific prior written
permission.

Disclaimer

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND/OR ANY
WARRANTIES THAT THIS SOFTWARE IS FREE OF INFRINGEMENT ARE DISCLAIMED.

IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//This file is based on GPUArray.h, from the HOOMD-Blue simulation package


#ifdef NVCC
#error This header cannot be compiled by nvcc
#endif

#ifndef GPUARRAY_H
#define GPUARRAY_H

// for vector types
//#ifdef ENABLE_CUDA
#include <cuda_runtime.h>
#include <cuda.h>
//#endif

#include <string.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <stdlib.h>
//namespace voroguppy
//{

//! Specifies where to acquire the data
struct access_location
    {
    //! The enum
    enum Enum
        {
        host,   //!< Ask to acquire the data on the host
#ifdef ENABLE_CUDA
        device  //!< Ask to acquire the data on the device
#endif
        };
    };

//! Defines where the data is currently stored
struct data_location
    {
    //! The enum
    enum Enum
        {
        host,       //!< Data was last updated on the host
#ifdef ENABLE_CUDA
        device,     //!< Data was last updated on the device
        hostdevice  //!< Data is up to date on both the host and device
#endif
        };
    };

//! Sepcify how the data is to be accessed
struct access_mode
    {
    //! The enum
    enum Enum
        {
        read,       //!< Data will be accessed read only
        readwrite,  //!< Data will be accessed for read and write
        overwrite   //!< The data is to be completely overwritten during this acquire
        };
    };

template<class T> class GPUArray;


//First, define the handle to access the data pointer that is, itself, handled by the GPUArray object
template<class T> class ArrayHandle
    {
    public:
        //! Aquires the data and sets \a m_data
        inline ArrayHandle(const GPUArray<T>& gpu_array, const access_location::Enum location = access_location::host,
                           const access_mode::Enum mode = access_mode::readwrite);
        //! Notifies the containing GPUArray that the handle has been released
        inline ~ArrayHandle();

        T* const data;          //!< Pointer to data

    private:
        const GPUArray<T>& m_gpu_array; //!< Reference to the GPUArray that owns \a data
    };




//GPUArray, a class for managing a 1d array of elements on the GPU and the CPU simultaneously. The array has a flat data pointer with some number of elements, keeping a copy on both the host and device. An ArrayHandle instance allows access to the data, which either simply returns the pointer (if the data was last changed from the same location) or first copied over and then returned.
//
template<class T> class GPUArray
    {
    public:
        //! Constructs a NULL GPUArray
        GPUArray();
        //! Constructs a 1-D GPUArray
        GPUArray(unsigned int num_elements);
        //! Frees memory
        virtual ~GPUArray();

#ifdef ENABLE_CUDA
        //! Constructs a 1-D GPUArray
        GPUArray(unsigned int num_elements, bool mapped);
#endif

        //! Copy constructor
        GPUArray(const GPUArray& from);
        //! = operator
        GPUArray& operator=(const GPUArray& rhs);

        //! Get the number of elements
        unsigned int getNumElements() const
            {
            return m_num_elements;
            }

        //! Test if the GPUArray is NULL
        bool isNull() const
            {
            return (h_data == NULL);
            }

        virtual void resize(unsigned int num_elements);


    protected:
        //! Clear memory starting from a given element
        /*! \param first The first element to clear
         */
        inline void memclear(unsigned int first=0);

        //! Acquires the data pointer for use
        inline T* acquire(const access_location::Enum location, const access_mode::Enum mode) const;


        //! Release the data pointer
        inline void release() const
            {
            m_acquired = false;
            }

    private:
        mutable unsigned int m_num_elements;            //!< Number of elements
        mutable bool m_acquired;                //!< Tracks whether the data has been acquired
        mutable data_location::Enum m_data_location;    //!< Tracks the current location of the data
#ifdef ENABLE_CUDA
        mutable bool m_mapped;                          //!< True if we are using mapped memory
#endif

    protected:
#ifdef ENABLE_CUDA
        mutable T* d_data;      //!< Pointer to allocated device memory
#endif
        mutable T* h_data;      //!< Pointer to allocated host memory



    private:
        //! Helper function to allocate memory
        inline void allocate();
        //! Helper function to free memory
        inline void deallocate();

#ifdef ENABLE_CUDA
        //! Helper function to copy memory from the device to host
        inline void memcpyDeviceToHost() const;
        //! Helper function to copy memory from the host to device
        inline void memcpyHostToDevice() const;
#endif

        //! Helper function to resize host array
        inline T* resizeHostArray(unsigned int num_elements);

        //! Helper function to resize device array
        inline T* resizeDeviceArray(unsigned int num_elements);


        // need to be frineds of all the implementations of ArrayHandle and ArrayHandleAsync
        friend class ArrayHandle<T>;
    };






//******************************************
// ArrayHandle implementation
// *****************************************

/*! \param gpu_array GPUArray host to the pointer data
    \param location Desired location to access the data
    \param mode Mode to access the data with
*/
template<class T> ArrayHandle<T>::ArrayHandle(const GPUArray<T>& gpu_array, const access_location::Enum location,
                                              const access_mode::Enum mode) :
        data(gpu_array.acquire(location, mode)), m_gpu_array(gpu_array)
    {
    }

template<class T> ArrayHandle<T>::~ArrayHandle()
    {
    //assert(m_gpu_array.m_acquired);
    m_gpu_array.m_acquired = false;
    }


//******************************************
// GPUArray implementation
// *****************************************
template<class T> GPUArray<T>::GPUArray() :
        m_num_elements(0), m_acquired(false), m_data_location(data_location::host),
#ifdef ENABLE_CUDA
        m_mapped(false),
        d_data(NULL),
#endif
        h_data(NULL)
    {
    }

template<class T> GPUArray<T>::GPUArray(unsigned int num_elements) :
        m_num_elements(num_elements), m_acquired(false), m_data_location(data_location::host),
#ifdef ENABLE_CUDA
        m_mapped(false),
        d_data(NULL),
#endif
        h_data(NULL)
    {
    // allocate and clear memory
    allocate();
    memclear();
    }


#ifdef ENABLE_CUDA
/*! \param num_elements Number of elements to allocate in the array
    \param mapped True if we are using mapped-pinned memory
*/
template<class T> GPUArray<T>::GPUArray(unsigned int num_elements, bool mapped) :
        m_num_elements(num_elements), m_acquired(false), m_data_location(data_location::host),
        m_mapped(mapped),
        d_data(NULL),
        h_data(NULL)
    {
    // allocate and clear memory
    allocate();
    memclear();
    }

#endif

template<class T> GPUArray<T>::~GPUArray()
    {
    deallocate();
    }


template<class T> GPUArray<T>::GPUArray(const GPUArray& from) : m_num_elements(from.m_num_elements), 
        m_acquired(false), m_data_location(data_location::host),
#ifdef ENABLE_CUDA
        m_mapped(from.m_mapped),
        d_data(NULL),
#endif
        h_data(NULL)
    {
    // allocate and clear new memory the same size as the data in from
    allocate();
    memclear();

    // copy over the data to the new GPUArray
    if (m_num_elements > 0)
        {
        ArrayHandle<T> h_handle(from, access_location::host, access_mode::read);
        memcpy(h_data, h_handle.data, sizeof(T)*m_num_elements);
        }
    }

template<class T> GPUArray<T>& GPUArray<T>::operator=(const GPUArray& rhs)
    {
    if (this != &rhs) // protect against invalid self-assignment
        {
        // free current memory
        deallocate();

        // copy over basic elements
        m_num_elements = rhs.m_num_elements;
#ifdef ENABLE_CUDA
        m_mapped = rhs.m_mapped;
#endif
        // initialize state variables
        m_data_location = data_location::host;

        // allocate and clear new memory the same size as the data in rhs
        allocate();
        memclear();

        // copy over the data to the new GPUArray
        if (m_num_elements > 0)
            {
            ArrayHandle<T> h_handle(rhs, access_location::host, access_mode::read);
            memcpy(h_data, h_handle.data, sizeof(T)*m_num_elements);
            }
        }

    return *this;
    }


template<class T> void GPUArray<T>::allocate()
    {
    // don't allocate anything if there are zero elements
    if (m_num_elements == 0)
        return;


    // allocate host memory
    // at minimum, alignment needs to be 32 bytes for AVX
    int retval = posix_memalign((void**)&h_data, 32, m_num_elements*sizeof(T));
    if (retval != 0)
        {
        throw std::runtime_error("Error allocating GPUArray.");
        }

#ifdef ENABLE_CUDA
    //assert(d_data == NULL);
    //if (m_exec_conf && m_exec_conf->isCUDAEnabled())
    //    {
        // register pointer for DMA
        cudaHostRegister(h_data,m_num_elements*sizeof(T), m_mapped ? cudaHostRegisterMapped : cudaHostRegisterDefault);

        // allocate and/or map host memory
        if (m_mapped)
            {
            cudaHostGetDevicePointer(&d_data, h_data, 0);
    //        CHECK_CUDA_ERROR();
            }
        else
            {
            cudaMalloc(&d_data, m_num_elements*sizeof(T));
    //        CHECK_CUDA_ERROR();
            }
    //    }
#endif
    }


template<class T> void GPUArray<T>::deallocate()
    {
    // don't do anything if there are no elements
    if (m_num_elements == 0)
        return;

    // free memory

#ifdef ENABLE_CUDA
    //if (m_exec_conf && m_exec_conf->isCUDAEnabled())
    //    {
    //    assert(d_data);
        cudaHostUnregister(h_data);
    //    CHECK_CUDA_ERROR();

        if (! m_mapped)
            {
            cudaFree(d_data);
     //       CHECK_CUDA_ERROR();
            }
     //   }
#endif

    free(h_data);

    // set pointers to NULL
    h_data = NULL;
#ifdef ENABLE_CUDA
    d_data = NULL;
#endif
    }

template<class T> void GPUArray<T>::memclear(unsigned int first)
    {
    // don't do anything if there are no elements
    if (m_num_elements == 0)
        return;

    // clear memory
    memset(h_data+first, 0, sizeof(T)*(m_num_elements-first));

#ifdef ENABLE_CUDA
    //if (m_exec_conf && m_exec_conf->isCUDAEnabled())
    //    {
    //    assert(d_data);
        if (! m_mapped) cudaMemset(d_data+first, 0, (m_num_elements-first)*sizeof(T));
    //    }
#endif
    }


#ifdef ENABLE_CUDA
/*! \post All memory on the device is copied to the host array
*/
template<class T> void GPUArray<T>::memcpyDeviceToHost() const
    {
    // don't do anything if there are no elements
    if (m_num_elements == 0)
        return;

    if (m_mapped)
        {
        // if we are using mapped pinned memory, no need to copy, only synchronize
        cudaDeviceSynchronize();
        return;
        }

        cudaMemcpy(h_data, d_data, sizeof(T)*m_num_elements, cudaMemcpyDeviceToHost);

    //    CHECK_CUDA_ERROR();
    }

/*! \post All memory on the host is copied to the device array
*/
template<class T> void GPUArray<T>::memcpyHostToDevice() const
    {
    // don't do anything if there are no elements
    if (m_num_elements == 0)
        return;

    if (m_mapped)
        {
        // if we are using mapped pinned memory, no need to copy
        // rely on CUDA's implicit synchronization
        return;
        }

        cudaMemcpy(d_data, h_data, sizeof(T)*m_num_elements, cudaMemcpyHostToDevice);

    //    CHECK_CUDA_ERROR();
    }
#endif


/*
    acquire() is the workhorse of GPUArray. It tracks the internal state variable \a data_location and
    performs all host<->device memory copies as needed during the state changes given the
    specified access mode and location where the data is to be acquired.

    acquire() cannot be directly called by the user class. Data must be accessed through ArrayHandle.
*/
template<class T> T* GPUArray<T>::acquire(const access_location::Enum location, const access_mode::Enum mode) const
    {
    m_acquired = true;

    // base case - handle acquiring a NULL GPUArray by simply returning NULL to prevent any memcpys from being attempted
    if (isNull())
        return NULL;

    // first, break down based on where the data is to be acquired
    if (location == access_location::host)
        {
        // then break down based on the current location of the data
        if (m_data_location == data_location::host)
            {
            // the state stays on the host regardles of the access mode
            return h_data;
            }
#ifdef ENABLE_CUDA
        else if (m_data_location == data_location::hostdevice)
            {
            // finally perform the action baed on the access mode requested
            if (mode == access_mode::read)  // state stays on hostdevice
                m_data_location = data_location::hostdevice;
            else if (mode == access_mode::readwrite)    // state goes to host
                m_data_location = data_location::host;
            else if (mode == access_mode::overwrite)    // state goes to host
                m_data_location = data_location::host;
            else
                {
                throw std::runtime_error("Error acquiring data");
                }

            return h_data;
            }
        else if (m_data_location == data_location::device)
            {
            // finally perform the action baed on the access mode requested
            if (mode == access_mode::read)
                {
                // need to copy data from the device to the host
                memcpyDeviceToHost();
                // state goes to hostdevice
                m_data_location = data_location::hostdevice;
                }
            else if (mode == access_mode::readwrite)
                {
                // need to copy data from the device to the host
                memcpyDeviceToHost();
                // state goes to host
                m_data_location = data_location::host;
                }
            else if (mode == access_mode::overwrite)
                {
                // no need to copy data, it will be overwritten
                // state goes to host
                m_data_location = data_location::host;
                }
            else
                {
                throw std::runtime_error("Error acquiring data");
                }

            return h_data;
            }
#endif
        else
            {
            throw std::runtime_error("Error acquiring data");
            return NULL;
            }
        }
#ifdef ENABLE_CUDA
    else if (location == access_location::device)
        {
        // check that a GPU is actually specified
        /*
        if (!m_exec_conf)
            {
            std::cerr << "Requesting device acquire, but we have no execution configuration" << std::endl;
            throw std::runtime_error("Error acquiring data");
            }
        if (!m_exec_conf->isCUDAEnabled())
            {
            m_exec_conf->msg->error() << "Requesting device acquire, but no GPU in the Execution Configuration" << std::endl;
            throw std::runtime_error("Error acquiring data");
            }
        */
        // then break down based on the current location of the data
        if (m_data_location == data_location::host)
            {
            // finally perform the action baed on the access mode requested
            if (mode == access_mode::read)
                {
                // need to copy data to the device
                memcpyHostToDevice();
                // state goes to hostdevice
                m_data_location = data_location::hostdevice;
                }
            else if (mode == access_mode::readwrite)
                {
                // need to copy data to the device
                memcpyHostToDevice();
                // state goes to device
                m_data_location = data_location::device;
                }
            else if (mode == access_mode::overwrite)
                {
                // no need to copy data to the device, it is to be overwritten
                // state goes to device
                m_data_location = data_location::device;
                }
            else
                {
                throw std::runtime_error("Error acquiring data");
                }

            return d_data;
            }
        else if (m_data_location == data_location::hostdevice)
            {
            // finally perform the action baed on the access mode requested
            if (mode == access_mode::read)  // state stays on hostdevice
                m_data_location = data_location::hostdevice;
            else if (mode == access_mode::readwrite)    // state goes to device
                m_data_location = data_location::device;
            else if (mode == access_mode::overwrite)    // state goes to device
                m_data_location = data_location::device;
            else
                {
                throw std::runtime_error("Error acquiring data");
                }
            return d_data;
            }
        else if (m_data_location == data_location::device)
            {
            // the state stays on the device regardless of the access mode
            return d_data;
            }
        else
            {
            throw std::runtime_error("Error acquiring data");
            return NULL;
            }
        }
#endif
    else
        {
        throw std::runtime_error("Error acquiring data");
        return NULL;
        }
    }

template<class T> T* GPUArray<T>::resizeHostArray(unsigned int num_elements)
    {
    // if not allocated, do nothing
    if (isNull()) return NULL;

    // allocate resized array
    T *h_tmp = NULL;

    // allocate host memory
    // at minimum, alignment needs to be 32 bytes for AVX
    int retval = posix_memalign((void**)&h_tmp, 32, num_elements*sizeof(T));
    if (retval != 0)
        {
        throw std::runtime_error("Error allocating GPUArray.");
        }

#ifdef ENABLE_CUDA
    //if (m_exec_conf && m_exec_conf->isCUDAEnabled())
    //    {
        cudaHostRegister(h_tmp, num_elements*sizeof(T), m_mapped ? cudaHostRegisterMapped : cudaHostRegisterDefault);
    //    }
#endif
    // clear memory
    memset(h_tmp, 0, sizeof(T)*num_elements);

    // copy over data
    unsigned int num_copy_elements = m_num_elements > num_elements ? num_elements : m_num_elements;
    memcpy(h_tmp, h_data, sizeof(T)*num_copy_elements);

    // free old memory location
#ifdef ENABLE_CUDA
    //if (m_exec_conf && m_exec_conf->isCUDAEnabled())
    //    {
        cudaHostUnregister(h_data);
    //    CHECK_CUDA_ERROR();
    //    }
#endif

    free(h_data);
    h_data = h_tmp;

#ifdef ENABLE_CUDA
    // update device pointer
    if (m_mapped)
        cudaHostGetDevicePointer(&d_data, h_data, 0);
#endif

    return h_data;
    }

template<class T> T* GPUArray<T>::resizeDeviceArray(unsigned int num_elements)
    {
#ifdef ENABLE_CUDA
    if (m_mapped) return NULL;

    // allocate resized array
    T *d_tmp;
    cudaMalloc(&d_tmp, num_elements*sizeof(T));
    //CHECK_CUDA_ERROR();

    //assert(d_tmp);

    // clear memory
    cudaMemset(d_tmp, 0, num_elements*sizeof(T));
    //CHECK_CUDA_ERROR();

    // copy over data
    unsigned int num_copy_elements = m_num_elements > num_elements ? num_elements : m_num_elements;
    cudaMemcpy(d_tmp, d_data, sizeof(T)*num_copy_elements,cudaMemcpyDeviceToDevice);
    //CHECK_CUDA_ERROR();

    // free old memory location
    cudaFree(d_data);
    //CHECK_CUDA_ERROR();

    d_data = d_tmp;
    return d_data;
#else
    return NULL;
#endif
    }

template<class T> void GPUArray<T>::resize(unsigned int num_elements)
    {

    // if not allocated, simply allocate
    if (isNull())
        {
        m_num_elements = num_elements;
        allocate();
        return;
        };


    resizeHostArray(num_elements);
#ifdef ENABLE_CUDA
    //if (m_exec_conf && m_exec_conf->isCUDAEnabled())
        resizeDeviceArray(num_elements);
#endif
    m_num_elements = num_elements;
    }


//};
#endif