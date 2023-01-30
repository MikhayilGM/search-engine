#include "querywindow.h"

EditWindow::EditWindow(std::vector<QString>& fields) : QueryWindow("edit"), replacable_fields(fields)
{

}

void EditWindow::submit_button_clicked()
{
    QFile data("data.info");
    data.open(QIODevice::ReadWrite);
    std::vector<std::vector<QString>> info;
    QTextStream out(&data);

    while(!out.atEnd())
    {
        info.push_back(split(out.readLine(), '|'));
    }

    bool edited = 0;
    for(int i = 0; i < info.size(); ++i)
    {
        if((replacable_fields[0] == "" || replacable_fields[0]  == info[i][0]) && (replacable_fields[1] == "" || replacable_fields[1]  == info[i][1]) && (replacable_fields[2] == "" || replacable_fields[2]  == info[i][2]) && (replacable_fields[3] == "" || replacable_fields[3]  == info[i][3]) && (replacable_fields[4] == "" || replacable_fields[4]  == info[i][4]))
        {
            edited = 1;
            if(name_line -> text() != "")
            {
                info[i][0] = name_line -> text();
            }
            if(mail_line -> text() != "")
            {
                info[i][1] = mail_line -> text();
            }
            if(phonenumber_line -> text() != "")
            {
                info[i][2] = phonenumber_line -> text();
            }
            if(date_line -> text() != "")
            {
                info[i][3] = date_line -> text();
            }
            if(url_line -> text() != "")
            {
                info[i][4] = url_line -> text();
            }
        }
    }

    if(edited)
    {
        data.resize(0);
        for(int i = 0; i < info.size() - 1; ++i)
        {
            out << info[i][0] << '|' << info[i][1] << '|' << info[i][2] << '|' << info[i][3] << '|' << info[i][4] << '|' << '\n';
        }
        out << info.back()[0] << '|' << info.back()[1] << '|' << info.back()[2] << '|' << info.back()[3] << '|' << info.back()[4] << '|';
    }

}
