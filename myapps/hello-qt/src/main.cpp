#include <qapplication.h>
#include <qpushbutton.h>

/* Simple QT Hello ****/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QPushButton button("Hello world!!",0);
    button.move(200,200);
    button.show();
    return app.exec();
}
