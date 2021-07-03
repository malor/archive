#ifndef __VISITOR_HPP__
#define __VISITOR_HPP__

class Rook;
class Pawn;
class Queen;
class King;
class Knight;
class Bishop;

class Visitor
{
public:
    virtual void visit(Rook&)   const = 0;
    virtual void visit(Pawn&)   const = 0;
    virtual void visit(Queen&)  const = 0;
    virtual void visit(King&)   const = 0;
    virtual void visit(Knight&) const = 0;
    virtual void visit(Bishop&) const = 0;
};

#endif /* __VISITOR_HPP__ */
