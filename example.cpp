#include "example.h"

Example::Example() {
    this->setTitleText("This is title text!");
    this->setIconButton();
    this->setTheme(QFramelessWindow::Dark);
    resize(900,700);
}
