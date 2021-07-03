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


#ifndef __FGK_HPP__
#define __FGK_HPP__

#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))

#include <vector>
#include <algorithm>
#include <memory>

#include "node.hpp"


namespace huffman
{
    class DLL_PUBLIC FgkTree
    {
    public:
        FgkTree();
        ~FgkTree();

        /*
         * Encode a given byte and return it's code value
         */
        std::vector<unsigned char> encode(unsigned char byte);

        /*
         * Decode a given code sequence and return an original bytes sequence
         *
         * This method is designed to process data in parts. The given
         * code sequence is stored in the interal buffer and processed.
         * When there are enough bits to decode an original byte it's appended
         * to a sequence to be returned. If the given code value is not
         * enough to decode a single byte - an empty sequence is returned.
         */
        std::vector<unsigned char> decode(const std::vector<unsigned char>& codeseq);

        /*
         * Return a code of the special NYT symbol
         *
         * This can be useful in a compressor tool for terminating of a stream
         * of bits (if the number of bits is not a multiple of 8).
         */
        std::vector<unsigned char> nyt_code() const;

    private:
        class FgkTreeImpl;
        std::unique_ptr<FgkTreeImpl> _pimpl;
    };
}

#endif
