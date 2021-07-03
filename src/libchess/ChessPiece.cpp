#include <fstream>

#include "ChessPiece.hpp"

std::map<char, CreateChessPiece> ChessPiece::creators;

ChessPiece::ChessPiece(Color col)
    : _color(col)
{  }

ChessPiece::Color ChessPiece::color() const
{
    return _color;
}

void ChessPiece::setColor(ChessPiece::Color col)
{
    _color = col;
}

void ChessPiece::save(std::ostream& os) const
{
    os << char(_color);
}

boost::shared_ptr<ChessPiece> ChessPiece::load(std::istream& is)
{
    char label;
    is >> label;

    typedef std::map<char, CreateChessPiece>::iterator It;
    It it = ChessPiece::creators.find(label);

    boost::shared_ptr<ChessPiece> piece;
    if (it != ChessPiece::creators.end())
    {
        piece = it->second();

        char col;
        is >> col;
        piece->setColor(ChessPiece::Color(col));

        return piece;
    }

    return boost::shared_ptr<ChessPiece>();
}

bool ChessPiece::registerCreator(char label, CreateChessPiece func)
{
    typedef std::map<char, CreateChessPiece>::iterator It;
    It it = ChessPiece::creators.find(label);

    if (it != ChessPiece::creators.end())
        return false;

    ChessPiece::creators[label] = func;
    return true;
}
