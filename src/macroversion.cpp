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

/**
 * \file    macroversion.cpp
 * \brief   Run-time version implementation
 * \author  Ilya Arefiev
 */

#include    "macroversion.h"
using ilardm::lib::cppmisc::Version;

#include    <sstream>
using std::stringstream;

#include    <iostream>
using std::clog;
using std::endl;

/** enable/disable debug output. */
#define ENABLE_DETRACE__        (0)
#include    "detrace.h"

/** Version class constructor.
 *
 * Parses passed \a _version with macroses
 * #MACROVERSION_MA, #MACROVERSION_MI, #MACROVERSION_P, #MACROVERSION_M
 * and fill versionString.
 *
 * \param _version  version bitmask built with macro #MACROVERSION
 */
Version::Version( const uint32_t _version )
    : version( _version )
{
    stringstream ss;

    ss << MACROVERSION_MA( version ) << "."
        << MACROVERSION_MI( version ) << "."
        << MACROVERSION_P( version );

    MODE m = static_cast<MODE>( MACROVERSION_M( version ) );
    if ( RELEASE != m )
    {
        ss << "-";

        switch ( m )
        {
            case DEVELOPMENT:
                ss << "devel";
                break;
            case BETA:
                ss << "beta";
                break;
            default:
                ss << "unknown";
                break;
        };
    }

    versionString = ss.str();

#if ENABLE_DETRACE__
    OTRACE(clog) << std::hex
        << "0x" << _version << " "
        << std::dec
        << "(" << versionString << ")"
        << endl;
#endif
};

/** Dummy destructor.
 *
 */
Version::~Version()
{
};

/** Version compatibility checker.
 *
 * \param _p    Version object represents existing version with
 *              which compatibility should be checked
 *
 * \see     MACROVERSION_COMPATIBLE_WITH__
 *
 * \return  \c true if compatible \n
 *          \c false otherwise
 */
const bool Version::isCompatibleWith( const Version& _p ) const
{
    const bool ret = MACROVERSION_COMPATIBLE_WITH__( version, _p.version);
#if ENABLE_DETRACE__
    OTRACE(clog) << versionString
        << ( ret ? " " : " in" )
        << "compatible with "
        << _p.versionString
        << endl;
#endif

    return ret;
};

#undef ENABLE_DETRACE__
