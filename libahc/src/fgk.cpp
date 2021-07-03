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


#include <cassert>

#include "fgk.hpp"


namespace huffman
{
    class FgkTree::FgkTreeImpl
    {
    public:
        static const size_t DLL_LOCAL BYTES_NUM = 256;
        static const size_t DLL_LOCAL MAX_NUMBER = 512;

        enum node_t {
            NYT_NODE = -1,
            INTERNAL_NODE = -2
        };

        FgkTreeImpl()
            : _nyt(new TreeNode(FgkTreeImpl::NYT_NODE, FgkTreeImpl::MAX_NUMBER)),
              _root(_nyt),
              _dcurr(_root)
        {
            for (auto& p : _nodes)
                p = nullptr;
            for (auto& p : _numbers)
                p = nullptr;

            _numbers[MAX_NUMBER] = _nyt;
        }

        ~FgkTreeImpl()
        {
            delete_tree(_root);
        }

        void update_tree(TreeNode* node)
        {
            while (node)
            {
                TreeNode* highest = highest_in_class(node);
                swap_nodes(node, highest);

                node->weight += 1;

                node = node->parent;
            }
        }

        void swap_nodes(TreeNode* a, TreeNode* b)
        {
            assert(a);
            assert(b);
            assert(a->weight == b->weight);

            if (a == _root || b == _root || a == b || a->parent == b || b->parent == a)
                return;

            if (a->parent->left == a && b->parent->left == b)
                std::swap(a->parent->left, b->parent->left);
            else if (a->parent->left == a && b->parent->right == b)
                std::swap(a->parent->left, b->parent->right);
            else if (a->parent->right == a && b->parent->left == b)
                std::swap(a->parent->right, b->parent->left);
            else if (a->parent->right == a && b->parent->right == b)
                std::swap(a->parent->right, b->parent->right);

            std::swap(_numbers[a->number], _numbers[b->number]);
            std::swap(a->number, b->number);
            std::swap(a->parent, b->parent);
        }

        TreeNode* highest_in_class(TreeNode* symb) const
        {
            TreeNode* highest = symb;
            int symb_number = symb->number;

            for (
                 size_t i = symb_number + 1;
                 i <= MAX_NUMBER && _numbers[i]->weight == symb->weight;
                 ++i
            )
            {
                highest = _numbers[i];
            }

            return highest;
        }

        void encode_existing_byte(unsigned char byte)
        {
            update_tree(_nodes[byte]);
        }

        void encode_new_byte(unsigned char byte)
        {
            _nyt->ch = INTERNAL_NODE;
            _nyt->left =  new TreeNode(NYT_NODE, _nyt->number - 2, 0, _nyt);
            _nyt->right = new TreeNode(byte, _nyt->number - 1, 0, _nyt);

            _nodes[byte] = _nyt->right;
            _numbers[_nyt->right->number] = _nyt->right;
            _numbers[_nyt->left->number] = _nyt->left;

            _nyt = _nyt->left;

            update_tree(_nodes[byte]);
        }

        std::vector<unsigned char> encode(unsigned char byte)
        {
            if (is_encoded(byte))
            {
                std::vector<unsigned char> code = symb_code(_nodes[byte]);

                encode_existing_byte(byte);

                return code;
            }
            else
            {
                // symbol code = NYT code . symbol bits value
                auto code = symb_code(_nyt);
                for (size_t i = 0; i < sizeof(byte) * 8; ++i)
                    code.push_back(bool(byte & (1 << (7 - i))));

                encode_new_byte(byte);

                return code;
            }
        }

        std::vector<unsigned char> decode(const std::vector<unsigned char>& codeseq)
        {
            std::vector<unsigned char> seq;

            std::copy(std::begin(codeseq), std::end(codeseq), std::back_inserter(_buf));

            size_t i = 0;
            while (i < _buf.size() || (!_dcurr->left && !_dcurr->right))
            {
                // first occurrence of a byte - just read next 8 bits
                if (_dcurr->ch == NYT_NODE)
                {
                    if (_buf.size() - i >= sizeof(unsigned char) * 8)
                    {
                        unsigned char orig_byte = 0;
                        for (size_t j = 0; j < sizeof(unsigned char) * 8; ++j)
                            orig_byte |= (_buf[i + j] << (7 - j));

                        seq.push_back(orig_byte);

                        // update the tree
                        encode_new_byte(orig_byte);

                        // keep processing the buffer
                        i += sizeof(unsigned char) * 8;
                        _dcurr = _root;
                    }
                    else
                    {
                        break;
                    }
                }
                // a leaf node that contains an original byte
                else if (!_dcurr->left && !_dcurr->right)
                {
                    seq.push_back(_dcurr->ch);

                    // update the tree
                    encode_existing_byte(_dcurr->ch);

                    // keep processing the buffer
                    _dcurr = _root;
                }
                // an internal node - keep processing bits from the buffer
                else
                {
                    if (_buf[i])
                        _dcurr = _dcurr->right;
                    else
                        _dcurr = _dcurr->left;

                    i++;
                }
            }

            _buf.erase(std::begin(_buf), std::begin(_buf) + i);

            return seq;
        }

        std::vector<unsigned char> symb_code(const TreeNode* symb_node) const
        {
            assert(symb_node);

            std::vector<unsigned char> code;
            code.reserve(16);

            const TreeNode* curr = symb_node;
            while (curr != _root)
            {
                code.push_back(curr->parent->right == curr);
                curr = curr->parent;
            }

            std::reverse(code.begin(), code.end());
            return code;
        }

        std::vector<unsigned char> nyt_code() const
        {
            return symb_code(_nyt);
        }

    private:
        // special node for encoding of Not-Yet-Transmitted symbols
        TreeNode* _nyt;
        // root of the Huffman tree
        TreeNode* _root;
        // pointers to leaves for fast access using a byte value as an index
        TreeNode* _nodes[BYTES_NUM];
        // pointers to nodes for fast access using a node number
        TreeNode* _numbers[MAX_NUMBER + 1];
        // buffer for storing of a sequence to decode
        std::vector<unsigned char> _buf;
        // current node pointer used when decoding a sequence
        TreeNode* _dcurr;

        inline bool is_encoded(unsigned char symb) const
        {
            return _nodes[symb];
        }
    };

    FgkTree::FgkTree()
        : _pimpl(new FgkTreeImpl)
    { }

    FgkTree::~FgkTree()
    { }

    std::vector<unsigned char> FgkTree::encode(unsigned char byte)
    {
        return _pimpl->encode(byte);
    }

    std::vector<unsigned char> FgkTree::decode(const std::vector<unsigned char>& codeseq)
    {
        return _pimpl->decode(codeseq);
    }

    std::vector<unsigned char> FgkTree::nyt_code() const
    {
        return _pimpl->nyt_code();
    }
}
