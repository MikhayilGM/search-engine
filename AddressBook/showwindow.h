#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H

#include <QMainWindow>
#include <QListWidget>

class ShowWindow : public QMainWindow
{
public:
    ShowWindow(QListWidget&);
};

#endif // SHOWWINDOW_H
