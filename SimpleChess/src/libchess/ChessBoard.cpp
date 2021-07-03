#include <fstream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "ChessBoard.hpp"

#include "ChessPiece.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Knight.hpp"

static const int DONT_CHECK_MOVE_ORDER = -1;

class DLL_LOCAL ChessBoard::ChessBoardImpl
{
public:
    ChessBoardImpl(bool empty = false, bool moveOrder = true)
        : _curMove(ChessPiece::WHITE), _moveOrder(moveOrder)
    {
        if (!empty)
            reset();
    }

    ChessBoardImpl(std::istream& is)
    {
        char curMove;
        is >> curMove;
        _curMove = ChessPiece::Color(curMove);
        _moveOrder = (curMove == DONT_CHECK_MOVE_ORDER) ? false : true;

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
                _board[i][j] = ChessPiece::load(is);
        }
    }

    bool move(const ChessBoard& board, const Coord& from, const Coord& to)
    {
        // out of board check
        if (!isInBoard(from) || !isInBoard(to))
            return false;

        // empty coord check
        if (!_board[from.y][from.x])
            return false;

        // check players move order
        if (_moveOrder && _board[from.y][from.x]->color() != _curMove)
            return false;

        // occupied by own piece check
        if (_board[to.y][to.x] &&
            _board[to.y][to.x]->color() == _board[from.y][from.x]->color())
            return false;

        // piece movement rules check
        if (!_board[from.y][from.x]->canMove(board, from, to))
            return false;

        _board[to.y][to.x] = _board[from.y][from.x];
        _board[from.y][from.x].reset();

        if (_moveOrder)
            _curMove = (_curMove == ChessPiece::WHITE)? ChessPiece::BLACK : ChessPiece::WHITE;

        return true;
    }

    void add(const Coord& coord, const boost::shared_ptr<ChessPiece>& piece)
    {
        if (!isInBoard(coord))
            return;

        _board[coord.y][coord.x] = piece;
    }

    boost::shared_ptr<ChessPiece> get(const Coord& coord) const
    {
        if (!isInBoard(coord))
            return boost::shared_ptr<ChessPiece>();

        return _board[coord.y][coord.x];
    }

    void reset()
    {
        // delete all chesspieces
        for (int i = 2; i <= 5; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
                _board[i][j].reset();
        }

        // create pawns
        for (int i = 0; i < SIZE; ++i)
        {
            _board[1][i] = boost::make_shared<Pawn>(ChessPiece::WHITE);
            _board[6][i] = boost::make_shared<Pawn>(ChessPiece::BLACK);
        }

        // create rooks
        _board[0][0] = boost::make_shared<Rook>(ChessPiece::WHITE);
        _board[0][7] = boost::make_shared<Rook>(ChessPiece::WHITE);
        _board[7][0] = boost::make_shared<Rook>(ChessPiece::BLACK);
        _board[7][7] = boost::make_shared<Rook>(ChessPiece::BLACK);

        // create knights
        _board[0][1] = boost::make_shared<Knight>(ChessPiece::WHITE);
        _board[0][6] = boost::make_shared<Knight>(ChessPiece::WHITE);
        _board[7][1] = boost::make_shared<Knight>(ChessPiece::BLACK);
        _board[7][6] = boost::make_shared<Knight>(ChessPiece::BLACK);

        // create bishops
        _board[0][2] = boost::make_shared<Bishop>(ChessPiece::WHITE);
        _board[0][5] = boost::make_shared<Bishop>(ChessPiece::WHITE);
        _board[7][2] = boost::make_shared<Bishop>(ChessPiece::BLACK);
        _board[7][5] = boost::make_shared<Bishop>(ChessPiece::BLACK);

        // create queens
        _board[0][3] = boost::make_shared<Queen>(ChessPiece::WHITE);
        _board[7][3] = boost::make_shared<Queen>(ChessPiece::BLACK);

        // create kings
        _board[0][4] = boost::make_shared<King>(ChessPiece::WHITE);
        _board[7][4] = boost::make_shared<King>(ChessPiece::BLACK);
    }

    void save(std::ostream& os) const
    {
        if (_moveOrder)
            os << char(_curMove);
        else
            os << char(DONT_CHECK_MOVE_ORDER);

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if (_board[i][j])
                    _board[i][j]->save(os);
                else
                    os << char(0);
            }
        }
    }

private:
    boost::shared_ptr<ChessPiece> _board[SIZE][SIZE];
    ChessPiece::Color _curMove;
    bool _moveOrder;

    static bool isInBoard(const Coord& coord)
    {
        return coord.y >= 0 && coord.y < SIZE
            && coord.x >= 0 && coord.x < SIZE;
    }
};

ChessBoard::ChessBoard(bool empty, bool moveOrder)
    : _impl(new ChessBoardImpl(empty, moveOrder))
{ }

ChessBoard::ChessBoard(std::istream& is)
    : _impl(new ChessBoardImpl(is))
{ }

ChessBoard::ChessBoard(const ChessBoard& cb)
{
    *_impl = *cb._impl;
}

ChessBoard& ChessBoard::operator=(const ChessBoard& cb)
{
    if (&cb == this)
        return *this;

    *_impl = *cb._impl;

    return *this;
}

ChessBoard::~ChessBoard()
{ /* required by smart pimpl pointer */ }

void ChessBoard::add(const Coord& coord, const boost::shared_ptr<ChessPiece>& piece)
{
    _impl->add(coord, piece);
}

bool ChessBoard::move(const Coord& from, const Coord& to)
{
    return _impl->move(*this, from, to);
}

boost::shared_ptr<ChessPiece> ChessBoard::get(const Coord& coord) const
{
    return _impl->get(coord);
}

void ChessBoard::reset()
{
    _impl->reset();
}

void ChessBoard::save(std::ostream& os) const
{
    _impl->save(os);
}
