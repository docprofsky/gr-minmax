/* -*- c++ -*- */
/*
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <limits>
#include <gnuradio/io_signature.h>
#include "minmax_impl.h"

namespace gr {
  namespace minmax {

    minmax::sptr
    minmax::make(size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new minmax_impl(vlen));
    }

    /*
     * The private constructor
     */
    minmax_impl::minmax_impl(size_t vlen)
      : gr::sync_block("minmax",
              gr::io_signature::make(1, 1, sizeof(float) * vlen),
              gr::io_signature::make(2, 2, sizeof(float) * vlen)),
              d_vlen(vlen),
              d_max(vlen, -std::numeric_limits<float>::max()),
              d_min(vlen,  std::numeric_limits<float>::max())
    {
    }

    /*
     * Our virtual destructor.
     */
    minmax_impl::~minmax_impl()
    {
    }

    int
    minmax_impl::work(int noutput_items,
      gr_vector_const_void_star &input_items,
      gr_vector_void_star &output_items)
    {
      float *iptr = (float*)input_items[0];

      float *omaxptr = (float*)output_items[0];
      float *ominptr = (float*)output_items[1];

      for(int i = 0; i < noutput_items; i++) {
        for(int j = 0; j < d_vlen; j++) {
          if(iptr[j] > d_max[j]) {
            d_max[j] = iptr[j];
          }

          if(iptr[j] < d_min[j]) {
            d_min[j] = iptr[j];
          }

          omaxptr[j] = d_max[j];
          ominptr[j] = d_min[j];
        }
        iptr += d_vlen;
        omaxptr += d_vlen;
        ominptr += d_vlen;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace minmax */
} /* namespace gr */
