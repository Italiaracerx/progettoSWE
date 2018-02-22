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
    GraphManager *Model;
    GraphPrinter *GraphTable;
    QPushButton* ButtonNode;
    QPushButton* ButtonArc;
    Node *First;
private slots:
    void newNode();
    void newArc();
    void addItem();
};

#endif // MAINWINDOW_H
