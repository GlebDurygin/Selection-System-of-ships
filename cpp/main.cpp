#include "dialogchoosemode.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChooseMode w;
    w.show();
    return app.exec();
}
