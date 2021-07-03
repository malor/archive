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


#include <vector>
#include <sstream>

#include <gtest/gtest.h>

#include <fgk.hpp>
#include <core.hpp>


class AhcEmptyTree : public ::testing::Test
{
public:
    std::vector<unsigned char> code;
    huffman::FgkTree tree;
};


TEST_F(AhcEmptyTree, nyt_code_empty_tree)
{
    EXPECT_EQ(std::vector<unsigned char>(), tree.nyt_code());
}


TEST_F(AhcEmptyTree, nyt_code_after_inserting_of_one_symbol)
{
    tree.encode('a');

    EXPECT_EQ(std::vector<unsigned char>({0}), tree.nyt_code());
}


TEST_F(AhcEmptyTree, nyt_code_after_inserting_of_short_sequence)
{
    for (auto c : {'a', 'a', ' ', 'b', 'b', 'b', ' ', 'c'})
        tree.encode(c);

    EXPECT_EQ(std::vector<unsigned char>({1, 1, 0, 0}), tree.nyt_code());
}


TEST_F(AhcEmptyTree, encode_one_byte)
{
    std::vector<unsigned char> bits = {0, 1, 1, 0, 0, 0, 0, 1};
    EXPECT_EQ(bits, tree.encode('a'));
}


TEST_F(AhcEmptyTree, encode_sequence_of_repeating_bytes)
{
    code.push_back(1);

    for (int i = 0; i < 10; ++i)
        tree.encode('a');

    EXPECT_EQ(code, tree.encode('a'));
}


TEST_F(AhcEmptyTree, encode_sequence_of_different_bytes)
{
    code.push_back(1);
    code.push_back(1);
    code.push_back(1);

    for (auto c : "aa bbb c")
        if (c != '\0')
            tree.encode(c);

    EXPECT_EQ(code, tree.encode(' '));
}


TEST_F(AhcEmptyTree, sequence_containing_ff_byte)
{
    code.push_back(0);

    for (auto c : "\xaa\xaa\xff\xbb\xbb\xbb\xff\xcc\xff\xff")
        if (c != '\0')
            tree.encode(c);

    EXPECT_EQ(code, tree.encode('\xff'));
}


TEST_F(AhcEmptyTree, encode_nyt_symbol_after_encoding_of_different_bytes)
{
    // NYT code
    code.push_back(1);
    code.push_back(1);
    code.push_back(0);
    code.push_back(0);

    // 'z' byte
    code.push_back(0);
    code.push_back(1);
    code.push_back(1);
    code.push_back(1);
    code.push_back(1);
    code.push_back(0);
    code.push_back(1);
    code.push_back(0);

    for (auto c : "aa bbb c")
        if (c != '\0')
            tree.encode(c);

    EXPECT_EQ(code, tree.encode('z'));
}


TEST_F(AhcEmptyTree, encode_another_short_sequence_of_different_bytes)
{
    code.push_back(1);
    code.push_back(1);

    for (auto c : "astrachan")
        if (c != '\0')
            tree.encode(c);

    EXPECT_EQ(code, tree.encode('a'));
}


TEST_F(AhcEmptyTree, encode_longer_sequence_of_different_bytes)
{
    code.push_back(1);
    code.push_back(1);
    code.push_back(0);

    for (auto c : "e eae de eabe eae dcf")
        if (c != '\0')
            tree.encode(c);

    EXPECT_EQ(code, tree.encode('a'));
}


TEST_F(AhcEmptyTree, decode_one_byte)
{
    // 'a' byte encoded value
    std::vector<unsigned char> bits = {0, 1, 1, 0, 0, 0, 0, 1};
    std::vector<unsigned char> original = {'a'};

    EXPECT_EQ(original, tree.decode(bits));
}


TEST_F(AhcEmptyTree, decode_one_byte_with_not_enough_bits)
{
    // 'a' byte encoded value missing 1 bit
    std::vector<unsigned char> bits = {0, 1, 1, 0, 0, 0, 0};
    std::vector<unsigned char> expected = {};
    EXPECT_EQ(expected, tree.decode(bits));

    expected.push_back('a');
    EXPECT_EQ(expected, tree.decode({1}));
}


TEST_F(AhcEmptyTree, decode_repeating_sequence_of_bytes)
{
    std::vector<unsigned char> bits = {
        // first 'a' byte encoded value
        0, 1, 1, 0, 0, 0, 0, 1,
        // second 'a'
        1,
        // third 'a'
        1,
        // fourth 'a'
        1
    };
    std::vector<unsigned char> original = {'a', 'a', 'a', 'a'};

    EXPECT_EQ(original, tree.decode(bits));
}


TEST_F(AhcEmptyTree, decode_short_sequence_of_bytes)
{
    // encoded sequence "aa bbb c"
    std::vector<unsigned char> bits = {
        // first 'a'
        0, 1, 1, 0, 0, 0, 0, 1,
        // second 'a'
        1,
        // NYT
        0,
        // first ' '
        0, 0, 1, 0, 0, 0, 0, 0,
        // NYT
        0, 0,
        // first 'b'
        0, 1, 1, 0, 0, 0, 1, 0,
        // second 'b'
        0, 0, 1,
        // third 'b'
        1, 1,
        // second ' '
        1, 0, 1,
        // NYT
        1, 0, 0,
        // first 'c'
        0, 1, 1, 0, 0, 0, 1, 1
    };

    std::vector<unsigned char> original = {'a', 'a', ' ', 'b', 'b', 'b', ' ', 'c'};

    EXPECT_EQ(original, tree.decode(bits));
}


TEST_F(AhcEmptyTree, decode_short_sequence_in_chunks)
{
    // encoded sequence "aa bbb c"
    std::vector<unsigned char> bits = {
        // first 'a'
        0, 1, 1, 0, 0, 0, 0, 1,
        // second 'a'
        1,
        // NYT
        0,
        // first ' '
        0, 0, 1, 0, 0, 0, 0, 0,
        // NYT
        0, 0,
        // first 'b'
        0, 1, 1, 0, 0, 0, 1, 0,
        // second 'b'
        0, 0, 1,
        // third 'b'
        1, 1,
        // second ' '
        1, 0, 1,
        // NYT
        1, 0, 0,
        // first 'c'
        0, 1, 1, 0, 0, 0, 1, 1
    };

    std::vector<unsigned char> decoded;
    size_t CHUNK_SIZE = 7;

    for (size_t i = 0; i < bits.size(); i += CHUNK_SIZE)
    {
        std::vector<unsigned char> tmp;

        if (i + CHUNK_SIZE < bits.size())
            tmp = tree.decode(std::vector<unsigned char>(std::begin(bits) + i, std::begin(bits) + i + CHUNK_SIZE));
        else
            tmp = tree.decode(std::vector<unsigned char>(std::begin(bits) + i, std::end(bits)));

        for (auto c : tmp)
            decoded.push_back(c);
    }

    EXPECT_EQ(std::vector<unsigned char>({'a', 'a', ' ', 'b', 'b', 'b', ' ', 'c'}), decoded);
}


#ifdef BUILD_TOOLS_TESTS

TEST(compress, empty_stream)
{
    std::stringstream is("");
    std::stringstream os;
    compress(is, os);

    EXPECT_EQ(std::string(), os.str());
}


TEST(compress, very_short_stream_repeating_nyt)
{
    std::stringstream is("aa");
    std::stringstream os;
    compress(is, os);

    EXPECT_EQ(std::string("\x61\x80"), os.str());
}


TEST(compress, short_stream)
{
    std::stringstream is("aa bbb c");
    std::stringstream os;
    compress(is, os);

    EXPECT_EQ(std::string("\x61\x88\x06\x23\xd8\xc7"), os.str());
}


TEST(compress, stream_exceeding_output_buffer)
{
    std::stringstream is;
    std::stringstream os;

    // encode a sequence of 4097 'a' in a row
    is.write("a", 1);
    for (size_t i = 0; i < 4096; ++i)
        is.write("a", 1);

    // encoded value is a code of 'a' followed by 4096 one bits
    std::stringstream tmp;
    tmp.write("\x61", 1);
    for (size_t i = 0; i < 4096 / 8; ++i)
        tmp.write("\xff", 1);

    compress(is, os);
    EXPECT_EQ(tmp.str(), os.str());
}


TEST(decompress, empty_stream)
{
    std::stringstream is("");
    std::stringstream os;
    decompress(is, os);

    EXPECT_EQ(std::string(), os.str());
}


TEST(decompress, very_short_stream_repeating_nyt)
{
    std::stringstream is("\x61\x80");
    std::stringstream os;
    decompress(is, os);

    EXPECT_EQ("aa", os.str());
}


TEST(decompress, short_stream)
{
    std::stringstream is("\x61\x88\x06\x23\xd8\xc7");
    std::stringstream os;
    decompress(is, os);

    EXPECT_EQ(std::string("aa bbb c"), os.str());
}


TEST(compress_decompress, one_byte)
{
    std::stringstream is;
    is.put('a');

    std::stringstream os;
    compress(is, os);

    std::stringstream ds;
    compress(os, ds);

    EXPECT_EQ(is.str(), ds.str());
}


TEST(compress_decompress, bytes_seqs_increasing_lengths)
{
    std::stringstream is;
    for (int i = 0; i < 1024 * 64; ++i)
        is.put(i % 256);

    std::stringstream os;
    compress(is, os);

    std::stringstream ds;
    decompress(os, ds);

    EXPECT_EQ(is.str(), ds.str());
}


TEST(compress_decompress, bytes_seqs_random_values)
{
    srand(time(0));

    std::stringstream is;
    for (int i = 0; i < 1024 * 64; ++i)
        is.put(rand() % 256);

    std::stringstream os;
    compress(is, os);

    std::stringstream ds;
    decompress(os, ds);

    EXPECT_EQ(is.str(), ds.str());
}

#endif


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
