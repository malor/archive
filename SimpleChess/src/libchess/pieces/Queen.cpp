#include <cstdlib>
#include <fstream>

#include <boost/make_shared.hpp>

#include "Queen.hpp"

Queen::Queen(Color col)
    : ChessPiece(col)
{ }

bool Queen::canMove(const ChessBoard& /* board */, const Coord& from, const Coord& to) const
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    if (abs(dx) == 0 && abs(dy) == 0)
        return false;

    return (abs(dx) == abs(dy)) || (dx != 0 && dy == 0) || (dy != 0 && dx == 0);
}

void Queen::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void Queen::save(std::ostream& os) const
{
    os << Queen::LABEL;
    ChessPiece::save(os);
}

namespace
{
    boost::shared_ptr<ChessPiece> createQueen()
    {
        return boost::make_shared<Queen>();
    }
    const bool registered = ChessPiece::registerCreator(Queen::LABEL, createQueen);
}
