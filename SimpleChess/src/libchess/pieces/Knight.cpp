#include <cstdlib>
#include <fstream>

#include <boost/make_shared.hpp>

#include "Knight.hpp"

Knight::Knight(Color col)
    : ChessPiece(col)
{ }

bool Knight::canMove(const ChessBoard& /* board */, const Coord& from, const Coord& to) const
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    return (abs(dx) == 2 && abs(dy) == 1) || (abs(dy) == 2 && abs(dx) == 1);
}

void Knight::save(std::ostream& os) const
{
    os << Knight::LABEL;
    ChessPiece::save(os);
}

void Knight::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

namespace
{
    boost::shared_ptr<ChessPiece> createKnight()
    {
        return boost::make_shared<Knight>();
    }
    const bool registered = ChessPiece::registerCreator(Knight::LABEL, createKnight);
}
