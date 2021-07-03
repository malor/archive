#ifndef __PAWN_HPP__
#define __PAWN_HPP__

#include "ChessPiece.hpp"

class DLL_PUBLIC Pawn : public ChessPiece
{
public:
    Pawn(Color col = WHITE);

    virtual bool canMove(const ChessBoard& board,
                         const Coord& from,
                         const Coord& to) const;
    virtual void save(std::ostream& os) const;

    virtual void accept(Visitor& visitor);

    static const char LABEL = 'P';
};

#endif /* __PAWN_HPP__ */
