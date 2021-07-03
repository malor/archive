#include <sstream>

#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/unit_test.hpp>

#include <boost/make_shared.hpp>

#include "ChessBoard.hpp"
#include "ChessPiece.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Knight.hpp"

using namespace boost::unit_test;

void test_rook_movement()
{
    ChessBoard board(true, false);
    board.add(Coord(0, 0), boost::make_shared<Rook>(ChessPiece::WHITE));

    // inboard normal moves
    BOOST_CHECK(board.move(Coord(0, 0), Coord(0, 1)));
    BOOST_CHECK(board.move(Coord(0, 1), Coord(0, 7)));
    BOOST_CHECK(board.move(Coord(0, 7), Coord(7, 7)));
    BOOST_CHECK(board.move(Coord(7, 7), Coord(0, 7)));
    // out of board moves
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(8, 7)));
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(7, 8)));
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(7, 10)));
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(-1, 7)));
    // invalid moves
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(1, 1)));
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(4, 3)));
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(6, 6)));
    BOOST_CHECK(!board.move(Coord(0, 7), Coord(5, 2)));
}

void test_pawn_movement()
{
    ChessBoard board(true, false);
    board.add(Coord(0, 1), boost::make_shared<Pawn>(ChessPiece::WHITE));
    board.add(Coord(4, 6), boost::make_shared<Pawn>(ChessPiece::BLACK));

    // special first move
    BOOST_CHECK(board.move(Coord(0, 1), Coord(0, 3)));
    BOOST_CHECK(board.move(Coord(4, 6), Coord(4, 4)));
    // inboard normal moves
    BOOST_CHECK(board.move(Coord(0, 3), Coord(0, 4)));
    BOOST_CHECK(board.move(Coord(4, 4), Coord(4, 3)));
    // invalid moves
    BOOST_CHECK(!board.move(Coord(0, 4), Coord(-1, 4)));
    BOOST_CHECK(!board.move(Coord(0, 4), Coord(1, 4)));
    BOOST_CHECK(!board.move(Coord(0, 4), Coord(0, 6)));
    BOOST_CHECK(!board.move(Coord(0, 4), Coord(0, 3)));
    BOOST_CHECK(!board.move(Coord(0, 4), Coord(1, 5)));
    BOOST_CHECK(!board.move(Coord(0, 4), Coord(1, 3)));

    BOOST_CHECK(!board.move(Coord(4, 3), Coord(3, 3)));
    BOOST_CHECK(!board.move(Coord(4, 3), Coord(5, 3)));
    BOOST_CHECK(!board.move(Coord(4, 3), Coord(4, 4)));
    BOOST_CHECK(!board.move(Coord(4, 3), Coord(5, 4)));
    BOOST_CHECK(!board.move(Coord(4, 3), Coord(6, 4)));
    // attacking of enemies
    board.add(Coord(1, 5), boost::make_shared<Pawn>(ChessPiece::BLACK));
    board.add(Coord(0, 6), boost::make_shared<Pawn>(ChessPiece::BLACK));
    BOOST_CHECK(board.move(Coord(0, 4), Coord(1, 5)));
    BOOST_CHECK(board.move(Coord(1, 5), Coord(0, 6)));
}

void test_queen_movement()
{
    ChessBoard board(true, false);
    board.add(Coord(0, 0), boost::make_shared<Queen>(ChessPiece::WHITE));

    // inboard normal moves
    BOOST_CHECK(board.move(Coord(0, 0), Coord(7, 0)));
    BOOST_CHECK(board.move(Coord(7, 0), Coord(7, 7)));
    BOOST_CHECK(board.move(Coord(7, 7), Coord(0, 0)));
    BOOST_CHECK(board.move(Coord(0, 0), Coord(7, 7)));
    // out of board moves
    BOOST_CHECK(!board.move(Coord(7, 7), Coord(8, 8)));
    BOOST_CHECK(!board.move(Coord(7, 7), Coord(7, 12)));
    BOOST_CHECK(!board.move(Coord(7, 7), Coord(-1, 4)));
    BOOST_CHECK(!board.move(Coord(7, 7), Coord(9, 10)));
    // invalid moves
    BOOST_CHECK(!board.move(Coord(7, 7), Coord(5, 2)));
    BOOST_CHECK(!board.move(Coord(7, 7), Coord(0, 6)));
    BOOST_CHECK(!board.move(Coord(7, 7), Coord(6, 1)));
}

void test_knight_movement()
{
    ChessBoard board(true, false);
    board.add(Coord(0, 0), boost::make_shared<Knight>(ChessPiece::WHITE));

    // inboard normal moves
    BOOST_CHECK(board.move(Coord(0, 0), Coord(1, 2)));
    BOOST_CHECK(board.move(Coord(1, 2), Coord(3, 3)));
    BOOST_CHECK(board.move(Coord(3, 3), Coord(5, 2)));
    BOOST_CHECK(board.move(Coord(5, 2), Coord(7, 1)));
    // out of board moves
    BOOST_CHECK(!board.move(Coord(7, 1), Coord(8, 9)));
    BOOST_CHECK(!board.move(Coord(7, 1), Coord(7, -2)));
    // invalid moves
    BOOST_CHECK(!board.move(Coord(7, 1), Coord(7, 0)));
    BOOST_CHECK(!board.move(Coord(7, 1), Coord(7, 2)));
    BOOST_CHECK(!board.move(Coord(7, 1), Coord(0, 0)));
    BOOST_CHECK(!board.move(Coord(7, 1), Coord(7, 7)));
}

void test_bishop_movement()
{
    ChessBoard board(true, false);
    board.add(Coord(0, 0), boost::make_shared<Bishop>(ChessPiece::WHITE));

    // inboard normal moves
    BOOST_CHECK(board.move(Coord(0, 0), Coord(7, 7)));
    BOOST_CHECK(board.move(Coord(7, 7), Coord(6, 6)));
    BOOST_CHECK(board.move(Coord(6, 6), Coord(7, 5)));
    // out of board moves
    BOOST_CHECK(!board.move(Coord(7, 5), Coord(8, 4)));
    BOOST_CHECK(!board.move(Coord(7, 5), Coord(4, 8)));
    // invalid moves
    BOOST_CHECK(!board.move(Coord(7, 5), Coord(7, 7)));
    BOOST_CHECK(!board.move(Coord(7, 5), Coord(7, 0)));
    BOOST_CHECK(!board.move(Coord(7, 5), Coord(7, 6)));
}

void test_king_movement()
{
    ChessBoard board(true, false);
    board.add(Coord(0, 0), boost::make_shared<King>(ChessPiece::WHITE));

    // inboard normal moves
    BOOST_CHECK(board.move(Coord(0, 0), Coord(1, 1)));
    BOOST_CHECK(board.move(Coord(1, 1), Coord(1, 2)));
    BOOST_CHECK(board.move(Coord(1, 2), Coord(2, 2)));
    BOOST_CHECK(board.move(Coord(2, 2), Coord(1, 1)));
    BOOST_CHECK(board.move(Coord(1, 1), Coord(0, 0)));
    // out of board moves
    BOOST_CHECK(!board.move(Coord(0, 0), Coord(-1, -1)));
    BOOST_CHECK(!board.move(Coord(0, 0), Coord(1, -1)));
    BOOST_CHECK(!board.move(Coord(0, 0), Coord(-1, 0)));
    // invalid moves
    BOOST_CHECK(!board.move(Coord(0, 0), Coord(2, 2)));
    BOOST_CHECK(!board.move(Coord(0, 0), Coord(2, 0)));
    BOOST_CHECK(!board.move(Coord(0, 0), Coord(7, 7)));
}

void test_move_order()
{
    ChessBoard board(false, true);

    BOOST_CHECK(board.move(Coord(0, 1), Coord(0, 3))); // white starts
    BOOST_CHECK(board.move(Coord(5, 6), Coord(5, 5))); // black
    BOOST_CHECK(board.move(Coord(7, 1), Coord(7, 2))); // white
    BOOST_CHECK(board.move(Coord(4, 6), Coord(4, 4))); // black
    BOOST_CHECK(!board.move(Coord(3, 6), Coord(3, 4))); // black
    BOOST_CHECK(!board.move(Coord(2, 6), Coord(2, 5))); // black
    BOOST_CHECK(board.move(Coord(5, 1), Coord(5, 2)));  // white
    BOOST_CHECK(!board.move(Coord(4, 1), Coord(4, 2))); // white
    BOOST_CHECK(!board.move(Coord(3, 1), Coord(3, 2))); // white
    BOOST_CHECK(board.move(Coord(2, 6), Coord(2, 5)));  // black
    BOOST_CHECK(!board.move(Coord(3, 6), Coord(3, 4))); // black
    BOOST_CHECK(board.move(Coord(3, 1), Coord(3, 2)));  // white
}

void test_pieces_saving()
{
    ChessPiece::Color colors[] = {ChessPiece::BLACK, ChessPiece::WHITE};

    for (auto color : colors)
    {
        std::map<char, boost::shared_ptr<ChessPiece> > pieces;
        pieces['R'] = boost::make_shared<Rook>(color);
        pieces['P'] = boost::make_shared<Pawn>(color);
        pieces['Q'] = boost::make_shared<Queen>(color);
        pieces['K'] = boost::make_shared<King>(color);
        pieces['N'] = boost::make_shared<Knight>(color);
        pieces['B'] = boost::make_shared<Bishop>(color);

        for (const auto& pair : pieces)
        {
            std::stringstream s;
            pair.second->save(s);
            std::string result = s.str();

            BOOST_CHECK(result.length() == 2);
            BOOST_CHECK(result[0] == pair.first);
            BOOST_CHECK(result[1] == char(color));
        }
    }
}

void test_pieces_loading()
{
    std::stringstream s;

    const char* PIECES[] = {
            // black
            "Q\x00"
          , "K\x00"
          , "P\x00"
          , "R\x00"
          , "N\x00"
          , "B\x00"
            // white
          , "Q\x01"
          , "K\x01"
          , "P\x01"
          , "R\x01"
          , "N\x01"
          , "B\x01"
          // errors
          , "Z\x01"
          , "H\x00"
          , "\x00\x00"
    };

    for (auto p : PIECES)
        s.write(p, 2);

    // black
    boost::shared_ptr<ChessPiece> bq = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Queen*>(bq.get()) != 0);
    BOOST_CHECK(bq->color() == ChessPiece::BLACK);

    boost::shared_ptr<ChessPiece> bk = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<King*>(bk.get()) != 0);
    BOOST_CHECK(bk->color() == ChessPiece::BLACK);

    boost::shared_ptr<ChessPiece> bp = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Pawn*>(bp.get()) != 0);
    BOOST_CHECK(bp->color() == ChessPiece::BLACK);

    boost::shared_ptr<ChessPiece> br = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Rook*>(br.get()) != 0);
    BOOST_CHECK(br->color() == ChessPiece::BLACK);

    boost::shared_ptr<ChessPiece> bn = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Knight*>(bn.get()) != 0);
    BOOST_CHECK(bn->color() == ChessPiece::BLACK);

    boost::shared_ptr<ChessPiece> bb = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Bishop*>(bb.get()) != 0);
    BOOST_CHECK(bb->color() == ChessPiece::BLACK);

    // white
    boost::shared_ptr<ChessPiece> wq = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Queen*>(wq.get()) != 0);
    BOOST_CHECK(wq->color() == ChessPiece::WHITE);

    boost::shared_ptr<ChessPiece> wk = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<King*>(wk.get()) != 0);
    BOOST_CHECK(wk->color() == ChessPiece::WHITE);

    boost::shared_ptr<ChessPiece> wp = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Pawn*>(wp.get()) != 0);
    BOOST_CHECK(wp->color() == ChessPiece::WHITE);

    boost::shared_ptr<ChessPiece> wr = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Rook*>(wr.get()) != 0);
    BOOST_CHECK(wr->color() == ChessPiece::WHITE);

    boost::shared_ptr<ChessPiece> wn = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Knight*>(wn.get()) != 0);
    BOOST_CHECK(wn->color() == ChessPiece::WHITE);

    boost::shared_ptr<ChessPiece> wb = ChessPiece::load(s);
    BOOST_CHECK(dynamic_cast<Bishop*>(wb.get()) != 0);
    BOOST_CHECK(wb->color() == ChessPiece::WHITE);

    // errors
    boost::shared_ptr<ChessPiece> unknown1 = ChessPiece::load(s);
    BOOST_CHECK(!unknown1);

    boost::shared_ptr<ChessPiece> unknown2 = ChessPiece::load(s);
    BOOST_CHECK(!unknown2);

    boost::shared_ptr<ChessPiece> zero = ChessPiece::load(s);
    BOOST_CHECK(!zero);
}


bool init_function()
{
    test_suite* movement = BOOST_TEST_SUITE("movement");
    movement->add(BOOST_TEST_CASE(test_rook_movement));
    movement->add(BOOST_TEST_CASE(test_pawn_movement));
    movement->add(BOOST_TEST_CASE(test_queen_movement));
    movement->add(BOOST_TEST_CASE(test_king_movement));
    movement->add(BOOST_TEST_CASE(test_knight_movement));
    movement->add(BOOST_TEST_CASE(test_bishop_movement));
    movement->add(BOOST_TEST_CASE(test_move_order));

    test_suite* serialization = BOOST_TEST_SUITE("serialization");
    serialization->add(BOOST_TEST_CASE(test_pieces_saving));
    serialization->add(BOOST_TEST_CASE(test_pieces_loading));

    framework::master_test_suite().add(movement);
    framework::master_test_suite().add(serialization);

    return true;
}

int main(int argc, char* argv[])
{
    return unit_test_main(init_function, argc, argv);
}
