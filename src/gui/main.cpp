#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "ChessBoardUi.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow window;
    ChessBoardUi* cbUi = new ChessBoardUi(&window);
    window.setCentralWidget(cbUi);

    QMenu* gameMenu = window.menuBar()->addMenu("Game");

    QAction* save = gameMenu->addAction("Save");
    QObject::connect(save, SIGNAL(triggered()), cbUi, SLOT(save()));

    QAction* load = gameMenu->addAction("Load");
    QObject::connect(load, SIGNAL(triggered()), cbUi, SLOT(load()));

    QAction* reset = gameMenu->addAction("Reset");
    QObject::connect(reset, SIGNAL(triggered()), cbUi, SLOT(reset()));

    QAction* exit = gameMenu->addAction("Exit");
    QObject::connect(exit, SIGNAL(triggered()), &app, SLOT(quit()));

    window.resize(480, 480);
    window.show();

    return app.exec();
}
