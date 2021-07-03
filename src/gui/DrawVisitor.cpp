#include <QSvgRenderer>
#include <QString>

#include "DrawVisitor.hpp"

#include "ChessPiece.hpp"
#include "pieces/Rook.hpp"
#include "pieces/Queen.hpp"
#include "pieces/King.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/Knight.hpp"

DrawVisitor::DrawVisitor(QPainter& painter, const QRectF& bounds)
    : _painter(painter), _bounds(bounds)
{ }

void DrawVisitor::draw(const QString& icon) const
{
    QSvgRenderer rend(icon);
    rend.render(&_painter, _bounds);
}

void DrawVisitor::visit(Rook& p) const
{
    if (p.color() == ChessPiece::WHITE)
        draw(QString::fromUtf8(":/data/pieces/rook_white.svg"));
    else
        draw(QString::fromUtf8(":/data/pieces/rook_black.svg"));
}

void DrawVisitor::visit(Pawn& p) const
{
    if (p.color() == ChessPiece::WHITE)
        draw(QString::fromUtf8(":/data/pieces/pawn_white.svg"));
    else
        draw(QString::fromUtf8(":/data/pieces/pawn_black.svg"));
}

void DrawVisitor::visit(Queen& p) const
{
    if (p.color() == ChessPiece::WHITE)
        draw(QString::fromUtf8(":/data/pieces/queen_white.svg"));
    else
        draw(QString::fromUtf8(":/data/pieces/queen_black.svg"));
}

void DrawVisitor::visit(King& p) const
{
    if (p.color() == ChessPiece::WHITE)
        draw(QString::fromUtf8(":/data/pieces/king_white.svg"));
    else
        draw(QString::fromUtf8(":/data/pieces/king_black.svg"));
}

void DrawVisitor::visit(Knight& p) const
{
    if (p.color() == ChessPiece::WHITE)
        draw(QString::fromUtf8(":/data/pieces/knight_white.svg"));
    else
        draw(QString::fromUtf8(":/data/pieces/knight_black.svg"));
}

void DrawVisitor::visit(Bishop& p) const
{
    if (p.color() == ChessPiece::WHITE)
        draw(QString::fromUtf8(":/data/pieces/bishop_white.svg"));
    else
        draw(QString::fromUtf8(":/data/pieces/bishop_black.svg"));
}
