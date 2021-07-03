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

#include <iostream>
#include <fstream>

#include "core.hpp"


void print_usage(char* argv[])
{
    std::cerr << "Usage: "
              << argv[0]
              << " <input file name> <output file name>"
              << std::endl;
}


int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        print_usage(argv);
        return 1;
    }

    std::ifstream is(argv[1], std::ios::binary);
    std::ofstream os(argv[2], std::ios::binary | std::ios::trunc);
    decompress(is, os);

    return 0;
}
