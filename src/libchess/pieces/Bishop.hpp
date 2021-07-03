#ifndef __BISHOP_HPP__
#define __BISHOP_HPP__

#include "ChessPiece.hpp"

class DLL_PUBLIC Bishop : public ChessPiece
{
public:
    Bishop(Color col = WHITE);

    virtual bool canMove(const ChessBoard& board,
                         const Coord& from,
                         const Coord& to) const;
    virtual void save(std::ostream& os) const;

    virtual void accept(Visitor& visitor);

    static const char LABEL = 'B';
};

#endif /* __BISHOP_HPP__ */
