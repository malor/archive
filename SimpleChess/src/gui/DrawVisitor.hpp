#ifndef __DRAWVISITOR_HPP__
#define __DRAWVISITOR_HPP__

#include <QPainter>
#include <QSvgRenderer>
#include <QRectF>

#include "Visitor.hpp"

class DrawVisitor : public Visitor
{
public:
    DrawVisitor(QPainter& painter, const QRectF& bounds);

    void draw(const QString& rend) const;

    virtual void visit(Rook&)   const;
    virtual void visit(Pawn&)   const;
    virtual void visit(Queen&)  const;
    virtual void visit(King&)   const;
    virtual void visit(Knight&) const;
    virtual void visit(Bishop&) const;

private:
    QPainter& _painter;
    const QRectF& _bounds;
};

#endif /* __DRAWVISITOR_HPP__ */
