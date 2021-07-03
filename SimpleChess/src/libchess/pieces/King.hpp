#ifndef __KING_HPP__
#define __KING_HPP__

#include "ChessPiece.hpp"

class DLL_PUBLIC King : public ChessPiece
{
public:
    King(Color col = WHITE);

    virtual bool canMove(const ChessBoard& board,
                         const Coord& from,
                         const Coord& to) const;
    virtual void save(std::ostream& os) const;

    virtual void accept(Visitor& visitor);

    static const char LABEL = 'K';
};

#endif /* __KING_HPP__ */
