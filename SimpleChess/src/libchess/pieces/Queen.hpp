#ifndef __QUEEN_HPP__
#define __QUEEN_HPP__

#include "ChessPiece.hpp"

class DLL_PUBLIC Queen : public ChessPiece
{
public:
    Queen(Color col = WHITE);

    virtual bool canMove(const ChessBoard& board,
                         const Coord& from,
                         const Coord& to) const;
    virtual void save(std::ostream& os) const;

    virtual void accept(Visitor& visitor);

    static const char LABEL = 'Q';
};

#endif /* __QUEEN_HPP__ */
