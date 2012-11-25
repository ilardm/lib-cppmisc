/*
 *    Copyright (c) 2012, Ilya Arefiev <arefiev.id@gmail.com>
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are
 *    met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of the author nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include    <stdint.h>
#include    <string>

namespace ilardm {
namespace lib {
namespace cppmisc {

class Version
{
    public:
        typedef enum {
              DEVELOPMENT = 0
            , BETA
            , RELEASE
        } MODE;

    public:
        Version(const uint32_t);
        ~Version();

        const bool isCompatibleWith( const Version& ) const;
        const std::string toString() const { return versionString; };

    private:
        const uint32_t          version;
        std::string             versionString;
};

}
}
}

/* === pack ================================================================ */

#define MACROVERSION_PACK(v,m,s)        ( ((v) & (m)) << (s) )

#define MACROVERSION_M2I(m)\
    ( (m == 'd') ? 0 :\
      ((m == 'b') ? 1 :\
       (( m == 'r' ) ? 2 : 0))\
    )

#define MACROVERSION_(ma,mi,p,m)\
    (   MACROVERSION_PACK((p),  0xFF, 0 )\
      | MACROVERSION_PACK((mi), 0xFF, 8 )\
      | MACROVERSION_PACK((ma), 0xFF, 16)\
      | MACROVERSION_PACK((m),  0x03, 24)\
    )
#define MACROVERSION(ma,mi,p,m)         MACROVERSION_(ma,mi,p, MACROVERSION_M2I(m))

/* === unpack ============================================================== */

#define MACROVERSION_UNPACK(v,m,s)      ( ((v) >> (s)) & (m) )

#define MACROVERSION_MA(v)              MACROVERSION_UNPACK((v), 0xFF, 16)
#define MACROVERSION_MI(v)              MACROVERSION_UNPACK((v), 0xFF, 8 )
#define MACROVERSION_P(v)               MACROVERSION_UNPACK((v), 0xFF, 0 )
#define MACROVERSION_M(v)               MACROVERSION_UNPACK((v), 0x03, 24)

/* === naming ============================================================== */

#define MACROVERSION_NAME_FOR(c)            c ## _MACROVERSION
#define MACROVERSION_RNAME_OF_FOR(c,r)      c ## _REQUIRES_ ## r ## _MACROVERSION

#define VERSIONO_NAME_FOR(c)                c ## _VERSION
#define VERSIONO_RNAME_OF_FOR(c,r)          c ## _REQUIRES_ ## r ## _VERSION

/* === checks ============================================================== */

#define MACROVERSION_COMPATIBLE_WITH__(r,p)\
    (    MACROVERSION_MA(p) == MACROVERSION_MA(r)\
      && MACROVERSION_MI(p) >= MACROVERSION_MI(r)\
      && MACROVERSION_P(p) >= MACROVERSION_P(r)\
    )
#define MACROVERSION_COMPATIBLE_WITH_(r,p)  MACROVERSION_COMPATIBLE_WITH__(r,p)
#define MACROVERSION_COMPATIBLE_WITH(r,p)\
    MACROVERSION_COMPATIBLE_WITH_( MACROVERSION_RNAME_OF_FOR(r,p), MACROVERSION_NAME_FOR(p) )

/* === declarations && definitions ========================================= */

#define VERSIONO_DECLARE_FOR(c)             extern const ilardm::lib::cppmisc::Version VERSIONO_NAME_FOR(c)
#define VERSIONO_DEFINE_FOR(c)              const ilardm::lib::cppmisc::Version VERSIONO_NAME_FOR(c)( MACROVERSION_NAME_FOR(c) )

#define VERSIONO_RDECLARE_OF_FOR(c,r)       extern const ilardm::lib::cppmisc::Version VERSIONO_RNAME_OF_FOR(c,r)
#define VERSIONO_RDEFINE_OF_FOR(c,r)        const ilardm::lib::cppmisc::Version VERSIONO_RNAME_OF_FOR(c,r)( MACROVERSION_RNAME_OF_FOR(c,r) )
