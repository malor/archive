#include <cstdlib>
#include <fstream>

#include <boost/make_shared.hpp>

#include "King.hpp"

King::King(Color col)
    : ChessPiece(col)
{  }

bool King::canMove(const ChessBoard& /* board */, const Coord& from, const Coord& to) const
{
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    // TODO: check for the special first move

    return (abs(dx) == 1 && abs(dy) <= 1) || (abs(dy) == 1 && abs(dx) <= 1);
}

void King::save(std::ostream& os) const
{
    os << King::LABEL;
    ChessPiece::save(os);
}

void King::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

namespace
{
    boost::shared_ptr<ChessPiece> createKing()
    {
        return boost::make_shared<King>();
    }
    const bool registered = ChessPiece::registerCreator(King::LABEL, createKing);
}
