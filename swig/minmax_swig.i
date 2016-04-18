/* -*- c++ -*- */

#define MINMAX_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "minmax_swig_doc.i"

%{
#include "minmax/minmax.h"
%}


%include "minmax/minmax.h"
GR_SWIG_BLOCK_MAGIC2(minmax, minmax);
