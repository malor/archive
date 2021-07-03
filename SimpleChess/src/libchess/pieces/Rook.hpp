#ifndef __ROOK_HPP__
#define __ROOK_HPP__

#include "ChessPiece.hpp"

class DLL_PUBLIC Rook : public ChessPiece
{
public:
    Rook(Color col = WHITE);

    virtual bool canMove(const ChessBoard& board,
                         const Coord& from,
                         const Coord& to) const;
    virtual void save(std::ostream& os) const;

    virtual void accept(Visitor& visitor);

    static const char LABEL = 'R';
};

#endif /* __ROOK_HPP__ */
