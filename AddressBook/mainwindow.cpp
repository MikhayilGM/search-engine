#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), add(new QPushButton("Add", this)),
      edit(new QPushButton("Edit", this)),
      bdelete(new QPushButton("Delete", this)),
      showw(new QPushButton("Show", this))
{
    this -> resize(400, 380);
    add -> resize(200, 30);
    add -> move(100,100);
    add -> show();
    QObject::connect(add, &QAbstractButton::clicked, this, &MainWindow::add_button_clicked);
    edit -> resize(200, 30);
    edit -> move(100,150);
    edit -> show();
    QObject::connect(edit, &QAbstractButton::clicked, this, &MainWindow::edit_button_clicked);
    bdelete -> resize(200, 30);
    bdelete -> move(100,200);
    bdelete -> show();
    QObject::connect(bdelete, &QAbstractButton::clicked, this, &MainWindow::delete_button_clicked);
    showw -> resize(200, 30);
    showw -> move(100,250);
    showw -> show();
    QObject::connect(showw, &QAbstractButton::clicked, this, &MainWindow::show_button_clicked);
}

MainWindow::~MainWindow()
{
    delete add;
    delete edit;
    delete bdelete;
    delete showw;
}


void MainWindow::add_button_clicked()
{
    QueryWindow* qwindow = new QueryWindow("add");
    qwindow -> show();
}

void MainWindow::edit_button_clicked()
{
    QueryWindow* qwindow = new QueryWindow("edit");
    qwindow -> show();
}

void MainWindow::delete_button_clicked()
{
    QueryWindow* qwindow = new QueryWindow("delete");
    qwindow -> show();
}

void MainWindow::show_button_clicked()
{
    QueryWindow* qwindow = new QueryWindow("show");
    qwindow -> show();
}
