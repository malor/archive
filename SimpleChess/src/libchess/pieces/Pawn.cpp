#include <cstdlib>
#include <fstream>

#include <boost/make_shared.hpp>

#include "Pawn.hpp"
#include "ChessBoard.hpp"

Pawn::Pawn(Color col)
    : ChessPiece(col)
{ }

bool Pawn::canMove(const ChessBoard& board, const Coord& from, const Coord& to) const
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    boost::shared_ptr<ChessPiece> enemy = board.get(to);

    if (_color == WHITE)
    {
        // special move from the start position
        if (from.y == 1 && to.y == 3 && dx == 0)
            return true;

        // special attack handling
        if (enemy && enemy->color() != _color)
                return abs(dx) == 1 && dy == 1;

        return dy == 1 && dx == 0;
    }
    else
    {
        // special move from the start position
        if (from.y == 6 && to.y == 4 && dx == 0)
            return true;

        // special attack handling
        if (enemy && enemy->color() != _color)
                return abs(dx) == 1 && dy == -1;

        return dy == -1 && dx == 0;
    }
}

void Pawn::save(std::ostream& os) const
{
    os << Pawn::LABEL;
    ChessPiece::save(os);
}

void Pawn::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

namespace
{
    boost::shared_ptr<ChessPiece> createPawn()
    {
        return boost::make_shared<Pawn>();
    }
    const bool registered = ChessPiece::registerCreator(Pawn::LABEL, createPawn);
}
