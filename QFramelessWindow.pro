QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include("$$PWD\qwindowkit\share\QWindowKit\qmake/QWKWidgets.pri")

INCLUDEPATH += \
    $$PWD\TitleBar \

SOURCES += \
    example.cpp \
    main.cpp \
    qframelesswindow.cpp \
    TitleBar\titlebar.cpp \
    TitleBar\titlebarbutton.cpp

HEADERS += \
    TitleBar/titlebarprivate.h \
    example.h \
    qframelesswindow.h \
    TitleBar\titlebar.h \
    TitleBar\titlebarbutton.h\
    TitleBar\titlebarbuttonprivate.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    StyleSheet.qrc
