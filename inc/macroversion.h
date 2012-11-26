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

/**
 * \file    macroversion.h
 * \brief   Compile-time and run-time version definitions
 * \author  Ilya Arefiev
 */

#include    <stdint.h>
#include    <string>

namespace ilardm {
namespace lib {
namespace cppmisc {

/** Run-time version representation class.
 *
 * Keeps version-related data for run-time verification.
 *
 * \author  Ilya Arefiev
 */
class Version
{
    public:
        /** Development stage enum.
         * \enum    MODE
         *
         * Used to determine Version#versionString suffix
         *
         * \see     MACROVERSION_M2I
         */
        typedef enum {
              DEVELOPMENT = 0   /**< development stage. expands to '-d' suffix */
            , BETA              /**< beta stage. expands to '-b' suffix */
            , RELEASE           /**< release stage. expands to nothing */
        } MODE;

    public:
        Version(const uint32_t);
        ~Version();

        const bool isCompatibleWith( const Version& ) const;

        /** Verison#versionString getter.
         *
         * \return  \c const \c string version representation
         */
        const std::string toString() const { return versionString; };

    private:
        /** version bitmap
         *
         * \see MACROVERSION
         */
        const uint32_t          version;

        /** String representation of version.
         */
        std::string             versionString;
};

}
}
}

/* === pack ================================================================ */

/** \name   version builers
 * @{
 */

/** Helper shift-mask macro.
 *
 * \param v     value
 * \param m     mask
 * \param s     shift
 *
 * \see MACROVERSION_UNPACK
 */
#define MACROVERSION_PACK(v,m,s)        ( ((v) & (m)) << (s) )

/** Helper char to mode converter macro.
 *
 * \param m     mode chracter
 *
 * \note    default is MODE::DEVELOPMENT value
 * \see     Version::MODE
 */
#define MACROVERSION_M2I(m)\
    ( (m == 'd') ? 0 :\
      ((m == 'b') ? 1 :\
       (( m == 'r' ) ? 2 : 0))\
    )

/** Version builder macro.
 *
 * \param ma    major version number
 * \param mi    minor version number
 * \param p     patch version number
 * \param m     mode version character
 *
 * \see MACROVERSION_M2I
 */
#define MACROVERSION_(ma,mi,p,m)\
    (   MACROVERSION_PACK((p),  0xFF, 0 )\
      | MACROVERSION_PACK((mi), 0xFF, 8 )\
      | MACROVERSION_PACK((ma), 0xFF, 16)\
      | MACROVERSION_PACK((m),  0x03, 24)\
    )
/** MACROVERSION_ decorator.
 * 
 * Required to expand MACROVERSION_M2I macro
 *
 * \see MACROVERISON_
 */
#define MACROVERSION(ma,mi,p,m)         MACROVERSION_(ma,mi,p, MACROVERSION_M2I(m))

/**@}*/

/* === unpack ============================================================== */

/** \name   version parsers
 * @{
 */

/** Particular version part parser helper
 *
 * \param v     version bitmask value
 * \param m     version part mask
 * \param s     version part shift
 *
 * \see MACROVERSION_PACK
 */
#define MACROVERSION_UNPACK(v,m,s)      ( ((v) >> (s)) & (m) )

/** major version part extractor macro
 */
#define MACROVERSION_MA(v)              MACROVERSION_UNPACK((v), 0xFF, 16)
/** Minor version part extractor macro
 */
#define MACROVERSION_MI(v)              MACROVERSION_UNPACK((v), 0xFF, 8 )
/** Patch level version part extracttor macro
 */
#define MACROVERSION_P(v)               MACROVERSION_UNPACK((v), 0xFF, 0 )
/** Mode version part extratcor macro
 */
#define MACROVERSION_M(v)               MACROVERSION_UNPACK((v), 0x03, 24)

/**@}*/

/* === naming ============================================================== */

/** \name   Macro name builders
 * @{
 */

/** Build version macro name for particular \a c name.
 */
#define MACROVERSION_NAME_FOR(c)            c ## _MACROVERSION
/** Build required version macro name for particular \a c
 * and \a r names.
 *
 * \param c     name which requires \a r version
 * \param r     name which is required for \a c name
 */
#define MACROVERSION_RNAME_OF_FOR(c,r)      c ## _REQUIRES_ ## r ## _MACROVERSION

/** Build Version object name for particular \a c name
 */
#define VERSIONO_NAME_FOR(c)                c ## _VERSION
/** Build required Version object name for particular \a c
 * and \a r names.
 *
 * \param c     name which requires \a r version
 * \param r     name which is required for \a c name
 */
#define VERSIONO_RNAME_OF_FOR(c,r)          c ## _REQUIRES_ ## r ## _VERSION

/**@}*/

/* === checks ============================================================== */

/** \name   compatibility checkers macroses
 * @{
 */

/** Version compatibility checker.
 *
 * Checks if required version is compatible with required.
 * Parametres should be bitmasks built with MACROVERSION macro.
 *
 * \param r     required version
 * \param p     presentef version
 */
#define MACROVERSION_COMPATIBLE_WITH__(r,p)\
    (    MACROVERSION_MA(p) == MACROVERSION_MA(r)\
      && MACROVERSION_MI(p) >= MACROVERSION_MI(r)\
      && MACROVERSION_P(p) >= MACROVERSION_P(r)\
    )
/** MACROVERSION_COMPATIBLE_WITH__ helper macro */
#define MACROVERSION_COMPATIBLE_WITH_(r,p)  MACROVERSION_COMPATIBLE_WITH__(r,p)
/** MACROVERSION_COMPATIBLE_WITH_ helper macro
 *
 * Parametres should be version names.
 *
 * \param r     required version name
 * \param p     presented version name
 *
 * \see MACROVERSION_COMPATIBLE_WITH_
 */
#define MACROVERSION_COMPATIBLE_WITH(r,p)\
    MACROVERSION_COMPATIBLE_WITH_( MACROVERSION_RNAME_OF_FOR(r,p), MACROVERSION_NAME_FOR(p) )

/**@}*/

/* === declarations && definitions ========================================= */

/** \name   run-time Version objects declarations and definitions.
 * @{
 */

/** Declares Version object for particular \a c name.
 *
 * Object name formed with VERSIONO_NAME_FOR
 */
#define VERSIONO_DECLARE_FOR(c)             extern const ilardm::lib::cppmisc::Version VERSIONO_NAME_FOR(c)
/** Defines Version object for particular \a c name.
 *
 * Version constructor invoked with bitmask name built with
 * MACROVERSION_NAME_FOR macro.
 *
 * \see     VERSIONO_DECLARE_FOR
 */
#define VERSIONO_DEFINE_FOR(c)              const ilardm::lib::cppmisc::Version VERSIONO_NAME_FOR(c)( MACROVERSION_NAME_FOR(c) )

/** Declares required Version object for particular \a c and \a r names.
 *
 * Object name formed with VERSIONO_RNAME_OF_FOR
 */
#define VERSIONO_RDECLARE_OF_FOR(c,r)       extern const ilardm::lib::cppmisc::Version VERSIONO_RNAME_OF_FOR(c,r)
/** Defines Required Version object for particular \a c and \a r names.
 *
 * Version constructor invoked with bitmask name built with
 * MACROVERSION_RNAME_OF_FOR macro.
 *
 * \see     VERSIONO_RDECLARE_OF_FOR
 */
#define VERSIONO_RDEFINE_OF_FOR(c,r)        const ilardm::lib::cppmisc::Version VERSIONO_RNAME_OF_FOR(c,r)( MACROVERSION_RNAME_OF_FOR(c,r) )

/**@}*/
