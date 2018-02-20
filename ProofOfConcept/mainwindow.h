#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QGraphicsView;
class QVBoxLayout;
class QGraphicsScene;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent,QGraphicsScene &Scene);
    ~MainWindow();

private:
    QGraphicsView *GraphTable;
};

#endif // MAINWINDOW_H
