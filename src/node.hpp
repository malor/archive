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


#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <cstdint>

#include <vector>


namespace huffman
{
    struct TreeNode;

    struct TreeNode
    {
        int ch;
        int number;
        int64_t weight;

        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int ch_,
                 int number_,
                 int weight_ = 0,
                 TreeNode* parent_ = nullptr,
                 TreeNode* left_ = nullptr,
                 TreeNode* right_ = nullptr)
            : ch(ch_),
              number(number_),
              weight(weight_),
              parent(parent_),
              left(left_),
              right(right_)
        { }
    };

    void delete_tree(const TreeNode* root);
}

#endif /* __NODE_HPP__ */
