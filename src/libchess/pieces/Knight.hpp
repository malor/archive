#ifndef __KNIGHT_HPP__
#define __KNIGHT_HPP__

#include "ChessPiece.hpp"

class DLL_PUBLIC Knight : public ChessPiece
{
public:
    Knight(Color col = WHITE);

    virtual bool canMove(const ChessBoard& board,
                         const Coord& from,
                         const Coord& to) const;
    virtual void save(std::ostream& os) const;

    virtual void accept(Visitor& visitor);

    static const char LABEL = 'N';
};

#endif /* __KNIGHT_HPP__ */
