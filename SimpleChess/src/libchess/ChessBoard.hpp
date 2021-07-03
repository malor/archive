#ifndef __CHESSBOARD_HPP__
#define __CHESSBOARD_HPP__

#include <iosfwd>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "common.hpp"

class ChessPiece;

class DLL_PUBLIC ChessBoard
{
public:
    ChessBoard(bool empty = false, bool moveOrder = true);
    ChessBoard(std::istream& is);
    ChessBoard(const ChessBoard&);
    ChessBoard& operator=(const ChessBoard&);
    ~ChessBoard();

    bool move(const Coord& from, const Coord& to);
    boost::shared_ptr<ChessPiece> get(const Coord& coord) const;
    void add(const Coord& coord, const boost::shared_ptr<ChessPiece>& piece);
    void reset();

    void save(std::ostream& os) const;

    static const int SIZE = 8;

private:
    class ChessBoardImpl;
    boost::scoped_ptr<ChessBoardImpl> _impl;
};

#endif /* __CHESSBOARD_HPP__ */
