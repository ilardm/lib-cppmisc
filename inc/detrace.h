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
 * \file    detrace.h
 * \brief   Debug trace macro definitions.
 * \author  Ilya Arefiev
 *
 * In order to use following macroses ENABLE_DETRACE__
 * must be defined as \c (1) \b before include of this file.
 * Also, use of following macroses must be surrounded with
 * conditional compilation macroses:
 * \code
 * #if ENABLE_DETRACE__
 * ...
 * #endif
 * \endcode
 *
 * \note    see source code for more documentation since doxygen
 *          could not generate documentation for the following macroses
 */

#if ENABLE_DETRACE__ /* ==================================================== */

/** compiler-specific function signature macro.
 */
#if defined( __GNUC__ ) /* ============================================= */
#  define FSIGN__       __PRETTY_FUNCTION__
#else /* --------------------------------------------------------------- */
#  define FSIGN__       __func__
#endif /* ============================================================== */

/** Debug trace for function use.
 *
 * \param out   any object with \c operator<<() defined
 */
#define FTRACE(out)     out << FSIGN__ << " "
/** Debug trace for objects only.
 *
 * \param out   any object with \c operator<<() defined
 */
#define OTRACE(out)     FTRACE(out) \
    << "(" << (void*)this << ") " 

#endif /* ================================================================== */
