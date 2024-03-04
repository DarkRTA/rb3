/*
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef _STLP_INTERNAL_CSTDIO
#define _STLP_INTERNAL_CSTDIO

#include _STLP_NATIVE_CPP_C_HEADER(cstdio)

namespace _STLP_STD {
using _STLP_VENDOR_STD::FILE;
using _STLP_VENDOR_STD::fpos_t;
using _STLP_VENDOR_STD::size_t;

using _STLP_VENDOR_STD::clearerr;
using _STLP_VENDOR_STD::fclose;
using _STLP_VENDOR_STD::feof;
using _STLP_VENDOR_STD::ferror;
using _STLP_VENDOR_STD::fflush;
using _STLP_VENDOR_STD::fgetc;
using _STLP_VENDOR_STD::fgetpos;
using _STLP_VENDOR_STD::fgets;
using _STLP_VENDOR_STD::fopen;
using _STLP_VENDOR_STD::fprintf;
using _STLP_VENDOR_STD::fputc;
using _STLP_VENDOR_STD::fputs;
using _STLP_VENDOR_STD::fread;
using _STLP_VENDOR_STD::freopen;
using _STLP_VENDOR_STD::fscanf;
using _STLP_VENDOR_STD::fseek;
using _STLP_VENDOR_STD::fsetpos;
using _STLP_VENDOR_STD::ftell;
using _STLP_VENDOR_STD::fwrite;

using _STLP_VENDOR_STD::getc;
using _STLP_VENDOR_STD::putc;
using _STLP_VENDOR_STD::getchar;
using _STLP_VENDOR_STD::putchar;

using _STLP_VENDOR_STD::gets;
using _STLP_VENDOR_STD::perror;
using _STLP_VENDOR_STD::printf;
using _STLP_VENDOR_STD::puts;
using _STLP_VENDOR_STD::remove;
using _STLP_VENDOR_STD::rename;
using _STLP_VENDOR_STD::rewind;
using _STLP_VENDOR_STD::setbuf;
using _STLP_VENDOR_STD::tmpfile;
using _STLP_VENDOR_STD::tmpnam;
using _STLP_VENDOR_STD::scanf;
using _STLP_VENDOR_STD::setvbuf;
using _STLP_VENDOR_STD::sprintf;
using _STLP_VENDOR_STD::sscanf;
using _STLP_VENDOR_STD::ungetc;
using _STLP_VENDOR_STD::vfprintf;
using _STLP_VENDOR_STD::vprintf;
using _STLP_VENDOR_STD::vsprintf;
using _STLP_VENDOR_STD::vsnprintf;
}

#endif /* _STLP_INTERNAL_CSTDIO */
