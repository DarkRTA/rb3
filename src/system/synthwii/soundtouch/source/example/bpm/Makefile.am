## Process this file with automake to create Makefile.in
##
## $Id: Makefile.am 4 2008-02-10 16:07:12Z oparviai $
##
## Copyright (C) 2003 - David W. Durham
## 
## This file is part of SoundTouch, an audio processing library for pitch/time adjustments
## 
## SoundTouch is free software; you can redistribute it and/or modify it under the
## terms of the GNU General Public License as published by the Free Software
## Foundation; either version 2 of the License, or (at your option) any later
## version.
## 
## SoundTouch is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
## A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License along with
## this program; if not, write to the Free Software Foundation, Inc., 59 Temple
## Place - Suite 330, Boston, MA  02111-1307, USA


include $(top_srcdir)/config/am_include.mk


# set to something if you want other stuff to be included in the distribution tarball
EXTRA_DIST=bpm.dsp bpm.dsw

noinst_HEADERS=PeakFinder.h

lib_LTLIBRARIES=libBPM.la
libBPM_la_SOURCES=BPMDetect.cpp PeakFinder.cpp


# other compiler flags to add
AM_CXXFLAGS=-O3 -I../../../include

# other linking flags to add
#libBPM_la_LIBADD=

