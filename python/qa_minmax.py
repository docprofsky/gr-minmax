#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import minmax_swig as minmax

class qa_minmax (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        veclen = 2
        src_data            = ((-1, 0), (2, -1), (-2, 0), (4, -3), (1, 0))
        expected_result_max = ((-1, 0), (2,  0), ( 2, 0), (4,  0), (4, 0))
        expected_result_min = ((-1, 0), (0, -1), (-2, 0), (4,  0), (4, 0))

        src = blocks.vector_source_f(sum(src_data, ()), False, veclen)
        mm = minmax.minmax(veclen)
        maxdst = blocks.vector_sink_f(veclen)
        mindst = blocks.vector_sink_f(veclen)
        self.tb.connect(src, mm)
        self.tb.connect((mm, 0), maxdst)
        self.tb.connect((mm, 1), mindst)
        print "running two"
        self.tb.run()
        print "finished two"
        result_max = zip(*[iter(maxdst.data())]*veclen)
        result_min = zip(*[iter(mindst.data())]*veclen)
        print "max"
        print result_max
        print "min"
        print result_min
        self.assertFloatTuplesAlmostEqual(expected_result_max, result_max, 6)
        # self.assertFloatTuplesAlmostEqual(expected_result_min, result_min, 6)


if __name__ == '__main__':
    gr_unittest.run(qa_minmax, "qa_minmax.xml")
