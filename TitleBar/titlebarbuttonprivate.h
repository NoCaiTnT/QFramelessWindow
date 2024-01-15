#ifndef TITLEBARBUTTONPRIVATE_H
#define TITLEBARBUTTONPRIVATE_H

#include "titlebarbutton.h"

class TitleBarButtonPrivate {
    Q_DECLARE_PUBLIC(TitleBarButton)
public:
    TitleBarButtonPrivate();
    virtual ~TitleBarButtonPrivate();

public:
    TitleBarButton *q_ptr;

    QIcon icon_normal_;
    QIcon icon_checked_;
    QIcon icon_disabled_;

public:
    void reloadIcon();
};

#endif // TITLEBARBUTTONPRIVATE_H
