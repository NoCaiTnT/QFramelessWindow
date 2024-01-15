#ifndef TITLEBARPRIVATE_H
#define TITLEBARPRIVATE_H

#include "titlebar.h"
#include <QHBoxLayout>
#include <QLocale>

class TitleBarPrivate{
    Q_DECLARE_PUBLIC(TitleBar)
public:
    TitleBarPrivate();
    virtual ~TitleBarPrivate();

public:
    TitleBar *q_ptr;
    QWidget *w_;

    bool auto_title_;
    bool auto_icon_;

    enum WindowBarItem {
        IconButton,
        TitleLabel,
        MinimumButton,
        MaximumButton,
        CloseButton,
    };

    QHBoxLayout *layout_;

public:
    void initLayout();

    QWidget *widgetAt(int index) const;
    void setWidgetAt(int index, QWidget *widget);
    QWidget *takeWidgetAt(int index);
    void insertDefaultSpace(int index);

private:
    Q_DISABLE_COPY(TitleBarPrivate)
};

#endif // TITLEBARPRIVATE_H
