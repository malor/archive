#ifndef __CHESSBOARDUI_HPP__
#define __CHESSBOARDUI_HPP__

#include <QWidget>

#include "ChessBoard.hpp"

class ChessBoardUi : public QWidget
{
    Q_OBJECT

public:
    ChessBoardUi(QWidget* parent = 0);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

public slots:
    void reset();
    void save();
    void load();

private:
    ChessBoard _board;
    Coord _firstTouch;

    Coord mouseToCoord(QMouseEvent* e);
};

#endif
