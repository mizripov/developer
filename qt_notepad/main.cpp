#include <QApplication>

#include "notepad.h"

//Вывести строку и столбец в statusBar как normalMessage (строка состояния положения курсора)

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Notepad notepad;
    notepad.show();
    return app.exec();
}
