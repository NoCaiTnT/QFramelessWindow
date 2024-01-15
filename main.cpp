#include "example.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Example e;
    e.show();
    return a.exec();
}
