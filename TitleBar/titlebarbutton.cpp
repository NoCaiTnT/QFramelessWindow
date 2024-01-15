#include "titlebarbutton.h"
#include "titlebarbuttonprivate.h"

TitleBarButtonPrivate::TitleBarButtonPrivate() = default;

TitleBarButtonPrivate::~TitleBarButtonPrivate() = default;

void TitleBarButtonPrivate::reloadIcon() {
    Q_Q(TitleBarButton);

    if (!q->isEnabled() && !icon_disabled_.isNull()) {
        q->setIcon(icon_disabled_);
        return;
    }

    if (q->isChecked() && !icon_checked_.isNull()) {
        q->setIcon(icon_checked_);
        return;
    }

    if (!icon_normal_.isNull()) {
        q->setIcon(icon_normal_);
    }
}

TitleBarButton::TitleBarButton(QWidget *parent) : TitleBarButton(*new TitleBarButtonPrivate(), parent){}

TitleBarButton::~TitleBarButton() = default;

QIcon TitleBarButton::iconNormal() const{
    Q_D(const TitleBarButton);
    return d->icon_normal_;
}

void TitleBarButton::setIconNormal(const QIcon &icon){
    Q_D(TitleBarButton);
    d->icon_normal_ = icon;
    d->reloadIcon();
}

QIcon TitleBarButton::iconChecked() const{
    Q_D(const TitleBarButton);
    return d->icon_checked_;
}

void TitleBarButton::setIconChecked(const QIcon &icon){
    Q_D(TitleBarButton);
    d->icon_checked_ = icon;
    d->reloadIcon();
}

QIcon TitleBarButton::iconDisabled() const{
    Q_D(const TitleBarButton);
    return d->icon_disabled_;
}

void TitleBarButton::setIconDisabled(const QIcon &icon){
    Q_D(TitleBarButton);
    d->icon_disabled_ = icon;
    d->reloadIcon();
}

void TitleBarButton::checkStateSet(){
    Q_D(TitleBarButton);
    d->reloadIcon();
}

void TitleBarButton::mouseDoubleClickEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        Q_EMIT doubleClicked();
    }
}

TitleBarButton::TitleBarButton(TitleBarButtonPrivate &d, QWidget *parent) : QPushButton(parent), d_ptr(&d){
    d.q_ptr = this;
}
