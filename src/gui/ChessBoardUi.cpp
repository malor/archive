#include <fstream>

#include <QMouseEvent>
#include <QFileDialog>
#include <QDesktopServices>

#include "ChessBoardUi.hpp"
#include "DrawVisitor.hpp"
#include "ChessPiece.hpp"

ChessBoardUi::ChessBoardUi(QWidget* parent)
    : QWidget(parent), _firstTouch(Coord(-1, -1))
{ }

void ChessBoardUi::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // cell dimensions
    const int BOARD_SIZE = ChessBoard::SIZE;
    const float CELL_WIDTH = width() / float(BOARD_SIZE);
    const float CELL_HEIGHT = height() / float(BOARD_SIZE);

    // cell brushes
    QBrush light(QColor::fromRgb(244, 164, 96));
    QBrush dark(QColor::fromRgb(139, 69, 19));

    // redraw the board
    for (int y = 0; y < BOARD_SIZE; ++y)
    {
        for (int x = 0; x < BOARD_SIZE; ++x)
        {
            QRectF rect(x * CELL_WIDTH, (BOARD_SIZE - y - 1) * CELL_HEIGHT,
                        CELL_WIDTH, CELL_HEIGHT);

            // draw cell
            if ((x + y) % 2 == 0)
                painter.setBrush(dark);
            else
                painter.setBrush(light);
            painter.drawRect(rect);

            // draw piece
            boost::shared_ptr<ChessPiece> p = _board.get(Coord(x, y));
            if (p)
            {
                DrawVisitor v(painter, rect);
                p->accept(v);
            }
        }
    }
}

Coord ChessBoardUi::mouseToCoord(QMouseEvent* e)
{
    int x = e->x() / (this->width()  / ChessBoard::SIZE);
    int y = e->y() / (this->height() / ChessBoard::SIZE);

    return Coord(x, ChessBoard::SIZE - y - 1);
}

void ChessBoardUi::mousePressEvent(QMouseEvent* event)
{
    _firstTouch = mouseToCoord(event);
}

void ChessBoardUi::mouseReleaseEvent(QMouseEvent* event)
{
    _board.move(_firstTouch, mouseToCoord(event));
    this->repaint();
}

void ChessBoardUi::reset()
{
    _board.reset();
    this->repaint();
}

void ChessBoardUi::save()
{
    QString fileName =
         QFileDialog::getSaveFileName(this, tr("Save Game"),
                                      QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                      tr("SimpleChess Game (*.scg)"));

    if (fileName.isEmpty())
        return;

    std::ofstream os(fileName.toUtf8().data());
    _board.save(os);
}

void ChessBoardUi::load()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, tr("Open File"),
                                     QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
                                     tr("SimpleChess Game (*.scg)"));

    if (fileName.isEmpty())
        return;

    std::ifstream is(fileName.toUtf8().data());
    _board = ChessBoard(is);
    this->repaint();
}
