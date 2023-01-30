#include "showwindow.h"

ShowWindow::ShowWindow(QListWidget& list)
{
    list.resize(700, 300);
    list.setParent(this);
    list.show();
}
