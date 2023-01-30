#include "querywindow.h"

std::vector<QString> split(const QString& str)
{
    std::vector<QString> vec;
    QString tmp;

    bool smt;

    for(int i = 0; i < str.size(); i++)
    {
        smt = 1;
            if(!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9'))
            {
                if(tmp.size() != 0)
                {
                    vec.push_back(tmp);
                    tmp.clear();
                }
                smt = 0;
            }


        if(smt)
        {
            tmp.push_back(str[i]);
        }

    }

    if(tmp.size())
    {
        vec.push_back(tmp);
    }
    return vec;
}

std::vector<QString> split(const QString& str, const QChar& spliter)
{
    std::vector<QString> vec;
    QString tmp;

    for(int i = 0; i < str.size(); i++)
    {
        bool smt = 1;
            if(spliter == str[i])
            {
                if(tmp.size() != 0)
                {
                    vec.push_back(tmp);
                    tmp.clear();
                }
                smt = 0;
            }

        if(smt)
        {
            tmp.push_back(str[i]);
        }

    }

    vec.push_back(tmp);

    return vec;
}

QueryWindow::QueryWindow(const QString& entered_query) : name_label(new QLabel("Name:", this)), name_line(new QLineEdit(this)),
                             mail_label(new QLabel("E-mail:", this)), mail_line(new QLineEdit(this)),
                             phonenumber_label(new QLabel("Phone:", this)), phonenumber_line(new QLineEdit(this)),
                             date_label(new QLabel("Date:", this)), date_line(new QLineEdit(this)),
                             url_label(new QLabel("Url:", this)), url_line (new QLineEdit(this)),
                             submit(new QPushButton("Submit", this))
{
    this -> resize(350, 350);

    query = entered_query;

    name_label -> move(50, 50);
    name_label -> show();

    name_line -> move (100, 50);
    name_line -> resize(200, 30);
    name_line -> show();

    QObject::connect(name_line, &QLineEdit::editingFinished, this, &QueryWindow::name_line_editing_finished);

    mail_label -> move(50, 100);
    mail_label -> show();

    mail_line -> move (100, 100);
    mail_line -> resize(200, 30);
    mail_line -> show();

    QObject::connect(mail_line, &QLineEdit::editingFinished, this, &QueryWindow::mail_line_editing_finished);

    phonenumber_label -> move(50, 150);
    phonenumber_label -> show();

    phonenumber_line -> move (100, 150);
    phonenumber_line -> resize(200, 30);
    phonenumber_line -> show();

    QObject::connect(phonenumber_line, &QLineEdit::editingFinished, this, &QueryWindow::phonenumber_line_editing_finished);

    date_label -> move(50, 200);
    date_label -> show();

    date_line -> move (100, 200);
    date_line -> resize(200, 30);
    date_line -> show();

    QObject::connect(date_line, &QLineEdit::editingFinished, this, &QueryWindow::date_line_editing_finished);

    url_label -> move(50, 250);
    url_label -> show();

    url_line -> move (100, 250);
    url_line -> resize(200, 30);
    url_line -> show();

    QObject::connect(url_line, &QLineEdit::editingFinished, this, &QueryWindow::url_line_editing_finished);

    submit -> move(180, 300);
    submit -> resize(100, 30);
    submit -> show();

    QObject::connect(submit, &QAbstractButton::clicked, this, &QueryWindow::submit_button_clicked);

}


QueryWindow::~QueryWindow()
{
    delete name_label;
    delete name_line;
    delete mail_label;
    delete mail_line;
    delete phonenumber_label;
    delete phonenumber_line;
    delete date_label;
    delete date_line;
    delete url_label;
    delete url_line;
}

void QueryWindow::name_line_editing_finished()
{
    QString line = name_line -> text();

    if(!(line.size()))
    {
        return;
    }

    if(line[0] < 'A' || line[0] > 'Z')
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered name must start with uppercase.", QMessageBox::Ok);
        name_line -> clear();
        return;
    }

    for(int i = 1; i < line.size(); ++i)
    {
        if(line[i] < 'a' || line[i] > 'z')
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered name must contain only letters.", QMessageBox::Ok);
            name_line -> clear();
            return;
        }
    }
}

void QueryWindow::mail_line_editing_finished()
{ 
    QString line = mail_line -> text();

    if(!(line.size()))
    {
        return;
    }

    if(!(line.endsWith("@gmail.com") || line.endsWith("@mail.ru") || line.endsWith("@yahoo.com") || line.endsWith("@yandex.ru")))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered mail must ends @gmail.com, @mail.ru, @yahoo.com, @yandex.ru.", QMessageBox::Ok);
        mail_line -> clear();
        return;
    }

    if(line.startsWith("@gmail.com") || line.startsWith("@mail.ru") || line.startsWith("@yahoo.com") || line.startsWith("@yandex.ru"))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered mail must starts with nickname.", QMessageBox::Ok);
        mail_line -> clear();
        return;
    }
}

void QueryWindow::phonenumber_line_editing_finished()
{
    QString line = phonenumber_line -> text();

    if(!(line.size()))
    {
        return;
    }

    if(!(line.startsWith("+374") || line.startsWith("+7") || line.startsWith("+976") || line.startsWith("+845")))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered phone number must starts with some of these codes +374, +7, +976, +845.", QMessageBox::Ok);
        phonenumber_line -> clear();
        return;
    }

    for(int i = 2; i < line.size(); ++i)
    {
        if(line[i] < '0' || line[i] > '9')
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered phone number must contains only numbers.", QMessageBox::Ok);
            phonenumber_line -> clear();
            return;
        }
    }

}

void QueryWindow::date_line_editing_finished()
{
    if(!(date_line -> text().size()))
    {
        return;
    }
    std::vector<QString> line = split(date_line -> text());

    if(line.size() == 3)
    {
        for(int i = 0; i < line.size(); ++i)
        {
           if(line[i][0] >= 'A' && line[i][0] <= 'S')
           {
               if(line[i] == "Jan" || line[i] == "Feb" || line[i] == "Mar" || line[i] == "Apr" || line[i] == "May" || line[i] == "Jun" || line[i] == "Jul" || line[i] == "Aug" ||line[i] == "Sep" ||line[i] == "Oct" || line[i] == "Nov" || line[i] == "Dec")
               {
                   line.erase(line.begin() + i);
                   for(i = 0; i < line.size(); ++i)
                   {
                       if(line[i].size() == 4)
                       {
                           if((line[i][0] == '2' && line[i][1] == '0' && line[i][2] <= '2' && line[i][2] >= '0' && line[i][3] >= '0' && line[i][3] <= '9') || (line[i][0] == '1' && line[i][1] == '9' && line[i][2] >= '0' && line[i][2] <= '9' && line[i][3] >= '0' && line[i][3] <= '9'))
                           {
                               line.erase(line.begin() + i);
                               if(line[0].size() <= 2)
                               {
                                   if(line[0].size() == 1 && line[0][0] >= '0' && line[0][0] <= '9')
                                   {
                                       return;
                                   }
                                   else if(line[0].size() == 2 && ((line[0][0] >= '0' && line[0][0] <= '2' && line[0][1] >= '0' && line[0][0] <= '9') || ((line[0][0] == '3' && line[0][1] >= '0' && line[0][0] <= '1'))))
                                   {
                                       return;
                                   }
                               }
                           }
                       }
                   }
               }
           }

        }

        for(int i = 0; i < line.size(); ++i)
        {
           if(line[i].size() == 4)
           {
               if((line[i][0] == '2' && line[i][1] == '0' && line[i][2] <= '2' && line[i][2] >= '0' && line[i][3] >= '0' && line[i][3] <= '9') || (line[i][0] == '1' && line[i][1] == '9' && line[i][2] >= '0' && line[i][2] <= '9' && line[i][3] >= '0' && line[i][3] <= '9'))
               {
                   line.erase(line.begin() + i);
                   for(i = 0; i < line.size(); ++i)
                   {
                       if(line[i].size() <= 2)
                       {
                           if(line[i].size() == 1 && line[i][0] >= '0' && line[i][0] <= '9')
                           {
                               line.erase(line.begin() + i);
                               if(line[0].size() <= 2)
                               {
                                   if(line[0].size() == 1 && line[i][0] >= '0' && line[i][0] <= '9')
                                   {
                                       return;
                                   }
                                   else if(line[0].size() == 2 && ((line[0][0] >= '0' && line[0][0] <= '2' && line[0][1] >= '0' && line[0][1] <= '9') || ((line[0][0] == '3' && line[0][1] >= '0' && line[0][1] <= '1'))))
                                   {
                                       return;
                                   }
                               }
                           }
                           else if(line[i].size() == 2 && ((line[0][0] == '1' && line[0][1] >= '3' && line[0][1] <= '9') || (line[0][0] == '2' && line[0][1] >= '0' && line[0][1] <= '9') || (line[0][0] <= '3' && line[0][1] >= '0' && line[0][1] <= '1')))
                           {
                               line.erase(line.begin() + i);
                               if(line[0].size() == 1 && line[i][0] >= '0' && line[i][0] <= '9')
                               {
                                   return;
                               }
                               else if(line[0].size() == 2 && ((line[0][0] >= '0' && line[0][0] <= '1' && line[0][1] >= '0' && line[0][1] <= '2') || ((line[0][0] == '3' && line[0][1] >= '0' && line[0][1] <= '1'))))
                               {
                                   return;
                               }
                           }
                           else if(line[i].size() == 2 && ((line[0][0] == '0' && line[0][1] >= '0' && line[0][0] <= '9') || (line[0][0] == '1' && line[0][1] >= '0' && line[0][0] <= '2')))
                           {
                               line.erase(line.begin() + i);
                               if(line[0].size() == 1 && line[i][0] >= '0' && line[i][0] <= '9')
                               {
                                   return;
                               }
                               else if(line[0].size() == 2 && ((line[0][0] >= '0' && line[0][0] <= '2' && line[0][1] >= '0' && line[0][1] <= '9') || ((line[0][0] == '3' && line[0][1] >= '0' && line[0][1] <= '1'))))
                               {
                                   return;
                               }
                           }

                       }
                   }
               }
           }

        }
    }

    QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered date(month, day and year) must contains only numbers or month abrreviation(Jan, Feb and e.t.c.).", QMessageBox::Ok);
    date_line -> clear();
}

void QueryWindow::url_line_editing_finished()
{

    QString line = url_line -> text();

    if(!(line.size()))
    {
        return;
    }

    if(!(line.startsWith("http://")))
    {
        QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Your entered url address must starts with http://.", QMessageBox::Ok);
        url_line -> clear();
        return;
    }
}

void QueryWindow::submit_button_clicked()
{
    if(query == "add")
    {
        if(!(name_line -> text().size() && mail_line -> text().size() && phonenumber_line -> text().size() && date_line -> text().size() && url_line -> text().size()))
        {
            QMessageBox::StandardButton qMessage = QMessageBox::critical(this, "Wrong Format", "Some of your fields are empty, please fill out them.", QMessageBox::Ok);
            return;
        }

        QFile data("data.info");
        data.open(QIODevice::ReadWrite);
        std::vector<QString> info;
        QTextStream out(&data);
        if(out.readAll().size())
        {
            out << '\n';
        }
        out << name_line -> text() << "|" << mail_line -> text() << "|" << phonenumber_line -> text() << "|" << date_line -> text() << "|" << url_line -> text() << "|";
    }
    else if(query == "edit")
    {
        std::vector<QString> info;
        info.push_back(name_line->text());
        info.push_back(mail_line->text());
        info.push_back(phonenumber_line->text());
        info.push_back(date_line->text());
        info.push_back(url_line->text());

        EditWindow* e_window = new EditWindow(info);
        e_window -> show();
    }
    else if(query == "delete")
    {
        QFile data("data.info");
        data.open(QIODevice::ReadWrite);
        std::vector<std::vector<QString>> info;
        QTextStream out(&data);

        while(!out.atEnd())
        {
            info.push_back(split(out.readLine(), '|'));
        }

        bool deleted = 0;
        for(int i = 0; i < info.size(); ++i)
        {
            if((name_line -> text() == "" || name_line -> text()  == info[i][0]) && (mail_line -> text() == "" || mail_line -> text()  == info[i][1]) && (phonenumber_line -> text() == "" || phonenumber_line -> text()  == info[i][2]) && (date_line -> text() == "" || date_line -> text()  == info[i][3]) && (url_line -> text() == "" || url_line -> text()  == info[i][4]))
            {
                deleted = 1;
                info.erase(info.begin() + i);
            }
        }

        if(deleted)
        {
            data.resize(0);
            for(int i = 0; i < info.size() - 1; ++i)
            {
                out << info[i][0] << '|' << info[i][1] << '|' << info[i][2] << '|' << info[i][3] << '|' << info[i][4] << '|' << '\n';
            }
            out << info.back()[0] << '|' << info.back()[1] << '|' << info.back()[2] << '|' << info.back()[3] << '|' << info.back()[4] << '|';
        }
    }
    else if(query == "show")
    {
        QListWidget* tmp = new QListWidget();
        QFile data("data.info");
        data.open(QIODevice::ReadWrite);
        std::vector<std::vector<QString>> info;
        QTextStream out(&data);

        while(!out.atEnd())
        {
            info.push_back(split(out.readLine(), '|'));
        }

        for(int i = 0; i < info.size(); ++i)
        {
            if(!((name_line -> text() == "" || name_line -> text()  == info[i][0]) && (mail_line -> text() == "" || mail_line -> text()  == info[i][1]) && (phonenumber_line -> text() == "" || phonenumber_line -> text()  == info[i][2]) && (date_line -> text() == "" || date_line -> text()  == info[i][3]) && (url_line -> text() == "" || url_line -> text()  == info[i][4])))
            {
                info.erase(info.begin() + i);
            }
        }

        for(int i = 0; i < info.size(); ++i)
        {
            tmp -> addItem(info[i][0] + " | " + info[i][1] + " | " + info[i][2] + " | " + info[i][3] + " | " + info[i][4]);
        }


        ShowWindow* s_win = new ShowWindow(*tmp);
        s_win -> resize(400, 300);
        s_win -> show();
    }
}


