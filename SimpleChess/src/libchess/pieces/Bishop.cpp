#include <fstream>
#include <cstdlib>

#include <boost/make_shared.hpp>

#include "Bishop.hpp"
#include "common.hpp"

Bishop::Bishop(Color col)
    : ChessPiece(col)
{ }

bool Bishop::canMove(const ChessBoard& /* board */, const Coord& from, const Coord& to) const
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    if (abs(dx) == 0 && abs(dy) == 0)
        return false;

    return abs(dx) == abs(dy);
}

void Bishop::save(std::ostream& os) const
{
    os << Bishop::LABEL;
    ChessPiece::save(os);
}

void Bishop::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

namespace
{
    boost::shared_ptr<ChessPiece> createBishop()
    {
        return boost::make_shared<Bishop>();
    }
    const bool registered = ChessPiece::registerCreator(Bishop::LABEL, createBishop);
}
