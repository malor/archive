/*
 * Copyright 2012 Roman Podoliaka
 *
 * This file is part of libahc.
 *
 * libahc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libahc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libahc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <vector>
#include <fstream>

#include <fgk.hpp>


void flush_output_buffer(std::ostream& os, std::vector<unsigned char>& buf)
{
    const size_t BUFSIZE = 2048;
    std::vector<unsigned char> out_byte_buf;
    out_byte_buf.reserve(BUFSIZE);

    size_t pos = 0;
    for (; pos + 8 <= buf.size(); pos += 8)
    {
        unsigned char byte = 0;
        for (size_t i = 0; i < 8; ++i)
        {
            if (buf[pos + i])
                byte |= (1 << (7 - i));
        }

        out_byte_buf.push_back(byte);
    }

    buf.erase(std::begin(buf), std::begin(buf) + pos);
    os.write(reinterpret_cast<char*>(&out_byte_buf.front()), out_byte_buf.size());
}


void compress(std::istream& is, std::ostream& os)
{
    const size_t BUFSIZE = 512;
    unsigned char inbuf[BUFSIZE];

    std::vector<unsigned char> outbuf;
    outbuf.reserve(BUFSIZE * 8 + 64);

    huffman::FgkTree tree;

    while (is.good())
    {
        is.read(reinterpret_cast<char*>(inbuf), BUFSIZE);
        size_t bytes_read = is.gcount();

        for (size_t i = 0; i < bytes_read ; ++i)
        {
            std::vector<unsigned char> code = tree.encode(inbuf[i]);
            std::copy(std::begin(code), std::end(code), std::back_inserter(outbuf));
        }

        if (outbuf.size() >= BUFSIZE * 8)
            flush_output_buffer(os, outbuf);
    }

    if (!outbuf.empty())
    {
        if (outbuf.size() % 8 != 0)
        {
            // The number of output bits is not a multiple of 8,
            // but we can do only byte I/O, so the solution is
            // to fill the extra bits with the code of NYT symbol
            // (probably more than once for short sequences of bits).
            // The decompressor will stop processing bits at this point,
            // waiting for a 8 bit code symbol and eventually encounter an EOF.
            std::vector<unsigned char> nyt_code = tree.nyt_code();

            size_t extra_bits = 8 - outbuf.size() % 8;
            for (size_t i = 0; i < extra_bits; ++i)
                outbuf.push_back(nyt_code[i % nyt_code.size()]);
        }

        flush_output_buffer(os, outbuf);
    }
}


void decompress(std::istream& is, std::ostream& os)
{
    const size_t BUFSIZE = 512;
    unsigned char inbuf[BUFSIZE];

    huffman::FgkTree tree;

    while (is.good())
    {
        is.read(reinterpret_cast<char*>(inbuf), BUFSIZE);
        size_t bytes_read = is.gcount();

        std::vector<unsigned char> seq;
        seq.reserve(BUFSIZE * 8);

        for (size_t i = 0; i < bytes_read; ++i)
        {
            std::vector<unsigned char> code(8);
            for (size_t j = 0; j < 8; ++j)
                code[j] = bool(inbuf[i] & (1 << (7 - j)));

            std::copy(std::begin(code), std::end(code), std::back_inserter(seq));
        }

        std::vector<unsigned char> output = tree.decode(seq);
        os.write(reinterpret_cast<char*>(&output.front()), output.size());
    }
}
