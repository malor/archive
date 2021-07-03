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

#ifndef __CORE_HPP__
#define __CORE_HPP__

#include <iosfwd>


void compress(std::istream& is, std::ostream& os);
void decompress(std::istream& is, std::ostream& os);

#endif /* __CORE_HPP__ */
