// Copyright 2015 Mark Owen
// http://www.quinapalus.com
// E-mail: qfp@quinapalus.com
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of version 2 of the GNU General Public License
// as published by the Free Software Foundation.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this file.  If not, see <http://www.gnu.org/licenses/> or
// write to the Free Software Foundation, Inc., 51 Franklin Street,
// Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef _QFPIO_H_
#define _QFPIO_H_

#ifdef __cplusplus
  extern "C" {
#endif

/** 
 * fmt is format control word:
 * b7..b0: number of significant figures
 * b15..b8: -(minimum exponent printable in F format)
 * b23..b16: maximum exponent printable in F format-1
 * b24: output positive mantissas with ' '
 * b25: output positive mantissas with '+' 
 * b26: output positive exponents with ' '
 * b27: output positive exponents with '+'
 * b28: suppress traling zeros in fraction
 * b29: fixed-point output: b7..0 give number of decimal places
 * default: 0x18060406
 * Note that if b28 is set (as it is in the default format value) the code will
 * write the trailing decimal point and zeros to the output buffer before truncating
 * the string. Thus it is essential that the output buffer is large enough to accommodate
 * these characters temporarily.
 *
 * Overall accuracy is sufficient to print all exactly-representable integers up to 10^8 correctly
 * in 0x18160408 format.
 * 
 */
#define FMT_D 0x18160404
extern void qfp_float2str(float f,char*s,unsigned int fmt);
extern int qfp_str2float(float*f,char*p,char**endptr);

#ifdef __cplusplus
  } // extern "C"
#endif
#endif
