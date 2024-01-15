#include "titlebar.h"
#include "titlebarprivate.h"

TitleBarPrivate::TitleBarPrivate() {
    w_ = nullptr;
    auto_title_ = true;
    auto_icon_ = false;
}

TitleBarPrivate::~TitleBarPrivate() = default;

void TitleBarPrivate::initLayout() {
    Q_Q(TitleBar);
    layout_ = new QHBoxLayout();
    if (QLocale::system().textDirection() == Qt::RightToLeft) {
        layout_->setDirection(QBoxLayout::RightToLeft);
    }
    layout_->setContentsMargins(QMargins());
    layout_->setSpacing(0);
    for (int i = IconButton; i <= CloseButton; ++i) {
        insertDefaultSpace(i);
    }
    q->setLayout(layout_);
}

QWidget *TitleBarPrivate::widgetAt(int index) const{
    return layout_->itemAt(index)->widget();
}

void TitleBarPrivate::setWidgetAt(int index, QWidget *widget)
{
    auto item = layout_->takeAt(index);
    auto orgWidget = item->widget();
    if (orgWidget) {
        orgWidget->deleteLater();
    }
    delete item;
    if (!widget) {
        insertDefaultSpace(index);
    } else {
        layout_->insertWidget(index, widget);
    }
}

QWidget *TitleBarPrivate::takeWidgetAt(int index)
{
    auto item = layout_->itemAt(index);
    auto orgWidget = item->widget();
    if (orgWidget) {
        item = layout_->takeAt(index);
        delete item;
        insertDefaultSpace(index);
    }
    return orgWidget;
}

void TitleBarPrivate::insertDefaultSpace(int index)
{
    layout_->insertSpacerItem(index, new QSpacerItem(0, 0));
}

TitleBar::TitleBar(QWidget *parent) : TitleBar(*new TitleBarPrivate(), parent) {
}

TitleBar::~TitleBar() = default;

QAbstractButton *TitleBar::getIconButton() const{
    Q_D(const TitleBar);
    return static_cast<QAbstractButton *>(d->widgetAt(TitleBarPrivate::IconButton));
}

QLabel *TitleBar::getTitleLabel() const{
    Q_D(const TitleBar);
    return static_cast<QLabel *>(d->widgetAt(TitleBarPrivate::TitleLabel));
}

QAbstractButton *TitleBar::getMinButton() const{
    Q_D(const TitleBar);
    return static_cast<QAbstractButton *>(d->widgetAt(TitleBarPrivate::MinimumButton));
}

QAbstractButton *TitleBar::getMaxButton() const{
    Q_D(const TitleBar);
    return static_cast<QAbstractButton *>(d->widgetAt(TitleBarPrivate::MaximumButton));
}

QAbstractButton *TitleBar::getCloseButton() const{
    Q_D(const TitleBar);
    return static_cast<QAbstractButton *>(d->widgetAt(TitleBarPrivate::CloseButton));
}

void TitleBar::setIconButton(QAbstractButton *btn){
    Q_D(TitleBar);
    auto org = takeIconButton();
    if (org)
        org->deleteLater();
    if (!btn)
        return;
    d->setWidgetAt(TitleBarPrivate::IconButton, btn);
    if (d->auto_icon_ && d->w_)
        btn->setIcon(d->w_->windowIcon());
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
}

void TitleBar::setTitleLabel(QLabel *label){
    Q_D(TitleBar);
    auto org = takeTitleLabel();
    if (org)
        org->deleteLater();
    if (!label)
        return;
    d->setWidgetAt(TitleBarPrivate::TitleLabel, label);
    if (d->auto_title_ && d->w_)
        label->setText(d->w_->windowTitle());
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void TitleBar::setMinButton(QAbstractButton *btn){
    Q_D(TitleBar);
    auto org = takeMinButton();
    if (org)
        org->deleteLater();
    if (!btn)
        return;
    d->setWidgetAt(TitleBarPrivate::MinimumButton, btn);
    connect(btn, &QAbstractButton::clicked, this, &TitleBar::minRequested);
}

void TitleBar::setMaxButton(QAbstractButton *btn){
    Q_D(TitleBar);
    auto org = takeMaxButton();
    if (org)
        org->deleteLater();
    if (!btn)
        return;
    d->setWidgetAt(TitleBarPrivate::MaximumButton, btn);
    connect(btn, &QAbstractButton::clicked, this, &TitleBar::maxRequested);
}

void TitleBar::setCloseButton(QAbstractButton *btn){
    Q_D(TitleBar);
    auto org = takeCloseButton();
    if (org)
        org->deleteLater();
    if (!btn)
        return;
    d->setWidgetAt(TitleBarPrivate::CloseButton, btn);
    connect(btn, &QAbstractButton::clicked, this, &TitleBar::closeRequested);
}

QAbstractButton *TitleBar::takeIconButton(){
    Q_D(TitleBar);
    return static_cast<QAbstractButton *>(d->takeWidgetAt(TitleBarPrivate::IconButton));
}

QLabel *TitleBar::takeTitleLabel(){
    Q_D(TitleBar);
    return static_cast<QLabel *>(d->takeWidgetAt(TitleBarPrivate::TitleLabel));
}

QAbstractButton *TitleBar::takeMinButton(){
    Q_D(TitleBar);
    auto btn = static_cast<QAbstractButton *>(d->takeWidgetAt(TitleBarPrivate::MinimumButton));
    if (!btn) {
        return nullptr;
    }
    disconnect(btn, &QAbstractButton::clicked, this, &TitleBar::minRequested);
    return btn;
}

QAbstractButton *TitleBar::takeMaxButton(){
    Q_D(TitleBar);
    auto btn = static_cast<QAbstractButton *>(d->takeWidgetAt(TitleBarPrivate::MaximumButton));
    if (!btn) {
        return nullptr;
    }
    disconnect(btn, &QAbstractButton::clicked, this, &TitleBar::maxRequested);
    return btn;
}

QAbstractButton *TitleBar::takeCloseButton(){
    Q_D(TitleBar);
    auto btn = static_cast<QAbstractButton *>(d->takeWidgetAt(TitleBarPrivate::CloseButton));
    if (!btn) {
        return nullptr;
    }
    disconnect(btn, &QAbstractButton::clicked, this, &TitleBar::closeRequested);
    return btn;
}

QWidget *TitleBar::hostWidget() const{
    Q_D(const TitleBar);
    return d->w_;
}

void TitleBar::setHostWidget(QWidget *w){
    Q_D(TitleBar);
    QWidget *org = d->w_;
    if (org) {
        org->removeEventFilter(this);
    }
    d_ptr->w_ = w;
    if (w) {
        w->installEventFilter(this);
    }
}

bool TitleBar::titleFollowWindow() const{
    Q_D(const TitleBar);
    return d->auto_title_;
}

void TitleBar::setTitleFollowWindow(bool value){
    Q_D(TitleBar);
    d->auto_title_ = value;
}

bool TitleBar::iconFollowWindow() const{
    Q_D(const TitleBar);
    return d->auto_icon_;
}

void TitleBar::setIconFollowWindow(bool value){
    Q_D(TitleBar);
    d->auto_icon_ = value;
}

TitleBar::TitleBar(TitleBarPrivate &d, QWidget *parent) : QFrame(parent), d_ptr(&d){
    d.q_ptr = this;
    d.initLayout();
}

void TitleBar::setStyle(QString path){
    QFile qss(path);
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();
}


