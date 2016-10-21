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

#ifndef INDEXER
#define INDEXER


#ifdef NVCC
#define HOSTDEVICE __host__ __device__
#else
#define HOSTDEVICE
#endif

// CREDIT HOOMD-BLUE FOR THIS

//! Index a 2D array
/*! Row major mapping of 2D onto 1D
    \ingroup utils
*/
struct Index2D
    {
    public:
        //! Contstructor
        /*! \param w Width of the square 2D array
        */
        HOSTDEVICE inline Index2D(unsigned int w=0) : m_w(w), m_h(w) {}

        //! Contstructor
        /*! \param w Width of the rectangular 2D array
            \param h Height of the rectangular 2D array
        */
        HOSTDEVICE inline Index2D(unsigned int w, unsigned int h) : m_w(w), m_h(h) {}

        //! Calculate an index
        /*! \param i column index
            \param j row index
            \returns 1D array index corresponding to the 2D index (\a i, \a j) in row major order
        */
        HOSTDEVICE inline unsigned int operator()(unsigned int i, unsigned int j) const
            {
            return j*m_w + i;
            }

        //! Get the number of 1D elements stored
        /*! \returns Number of elements stored in the underlying 1D array
        */
        HOSTDEVICE inline unsigned int getNumElements() const
            {
            return m_w*m_h;
            }

        //! Get the width of the 2D array
        HOSTDEVICE inline unsigned int getW() const
            {
            return m_w;
            }

        //! Get the height of the 2D array
        HOSTDEVICE inline unsigned int getH() const
            {
            return m_h;
            }

    private:
        unsigned int m_w;   //!< Width of the 2D array
        unsigned int m_h;   //!< Height of the 2D array
    };

#undef HOSTDEVICE
#endif


