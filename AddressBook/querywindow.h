#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QListWidget>
#include <showwindow.h>


class QueryWindow : public QMainWindow
{
public:
    QueryWindow(const QString&);
    ~QueryWindow();
    void name_line_editing_finished();
    void mail_line_editing_finished();
    void phonenumber_line_editing_finished();
    void date_line_editing_finished();
    void url_line_editing_finished();
    virtual void submit_button_clicked();

protected:
    QString query;
    QLabel* name_label;
    QLineEdit* name_line;
    QLabel* mail_label;
    QLineEdit* mail_line;
    QLabel* phonenumber_label;
    QLineEdit* phonenumber_line;
    QLabel* date_label;
    QLineEdit* date_line;
    QLabel* url_label;
    QLineEdit* url_line;
    QPushButton* submit;
};

class EditWindow : public QueryWindow
{
public:
    EditWindow(std::vector<QString>&);
    void submit_button_clicked() override;
protected:
    std::vector<QString> replacable_fields;
};


std::vector<QString> split(const QString& str);
std::vector<QString> split(const QString& str, const QChar &spliter);

#endif // QUERYWINDOW_H
