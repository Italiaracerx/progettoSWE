#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "node.h"

#include <QMainWindow>
class GraphManager;
class QVBoxLayout;
class GraphPrinter;
class QPushButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, GraphManager &Scene);
    ~MainWindow();
private:
    GraphPrinter *GraphTable;
    QPushButton* ButtonNode;
    QPushButton* ButtonArc;
    GraphManager *Model;
    Node *First;

private slots:
    void newNode();
    void newArc();
    void addItem();
};

#endif // MAINWINDOW_H
