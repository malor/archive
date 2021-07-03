#include <fstream>

#include <boost/make_shared.hpp>

#include "Rook.hpp"

Rook::Rook(Color col)
    : ChessPiece(col)
{  }

bool Rook::canMove(const ChessBoard& /* board */, const Coord& from, const Coord& to) const
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    return (dx != 0 && dy == 0) || (dy != 0 && dx == 0);
}

void Rook::save(std::ostream& os) const
{
    os << Rook::LABEL;
    ChessPiece::save(os);
}

void Rook::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

namespace
{
    boost::shared_ptr<ChessPiece> createRook()
    {
        return boost::make_shared<Rook>();
    }
    const bool registered = ChessPiece::registerCreator(Rook::LABEL, createRook);
}
