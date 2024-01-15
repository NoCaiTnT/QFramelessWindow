#ifndef QFRAMELESSWINDOW_H
#define QFRAMELESSWINDOW_H

#include <QMainWindow>

#include <QWKWidgets/widgetwindowagent.h>
#include "titlebar.h"
#include "titlebarbutton.h"

#include <QTimer>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QStyle>

class QFramelessWindow : public QMainWindow{
    Q_OBJECT

public:
    QFramelessWindow(QWidget *parent = nullptr);
    ~QFramelessWindow();

    enum Theme{
        Dark,
        Light
    };

private:
    QWK::WidgetWindowAgent *window_agent_;
    TitleBar *title_bar_;

    TitleBarButton *icon_button_;
    QLabel *title_text_;
    TitleBarButton *min_button_;
    TitleBarButton *max_button_;
    TitleBarButton *close_button_;

private:
    void initTitleBar();
    void initWindow();
    void connectAll();

    static void emulateLeaveEvent(QWidget *widget);
    bool event(QEvent *event) override;

private:
    Theme theme_;

public:
    void setTitleBar(QWidget *widget);
    void setIconButton(QString path = ":/Resources/TitleBar/appIcon.png");
    void setTitleText(QString text);

    void setStyle(QString path);
    void setTheme(Theme theme);

public slots:
    void clickIconButton();
    void clickMaxButton(bool max);

};
#endif // QFRAMELESSWINDOW_H
