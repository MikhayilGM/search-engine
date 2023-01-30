#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <querywindow.h>>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_button_clicked();
    void edit_button_clicked();
    void delete_button_clicked();
    void show_button_clicked();


private:
    QPushButton* add;
    QPushButton* edit;
    QPushButton* bdelete;
    QPushButton* showw;
    MainWindow *ui;
};
#endif // MAINWINDOW_H
