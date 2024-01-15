#include "qframelesswindow.h"

QFramelessWindow::QFramelessWindow(QWidget *parent)
    : QMainWindow(parent){
    initWindow();
    resize(800,600);
}

QFramelessWindow::~QFramelessWindow() {}

void QFramelessWindow::initTitleBar(){
    title_bar_ = new TitleBar();

    icon_button_ = new TitleBarButton();
    icon_button_->setObjectName(QStringLiteral("icon_button"));
    icon_button_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    title_text_ = new QLabel();
    title_text_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    title_text_->setObjectName(QStringLiteral("win_title_label"));

    min_button_ = new TitleBarButton();
    min_button_->setObjectName(QStringLiteral("min_button"));
    min_button_->setProperty("system_button", true);
    min_button_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    max_button_ = new TitleBarButton();
    max_button_->setCheckable(true);
    max_button_->setObjectName(QStringLiteral("max_button"));
    max_button_->setProperty("system_button", true);
    max_button_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    close_button_ = new TitleBarButton();
    close_button_->setObjectName(QStringLiteral("close_button"));
    close_button_->setProperty("system_button", true);
    close_button_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    title_bar_->setTitleLabel(title_text_);
    title_bar_->setMinButton(min_button_);
    title_bar_->setMaxButton(max_button_);
    title_bar_->setCloseButton(close_button_);
    title_bar_->setHostWidget(this);

}

void QFramelessWindow::initWindow(){

    window_agent_ = new QWK::WidgetWindowAgent(this);
    window_agent_->setup(this);

    initTitleBar();

    window_agent_->setTitleBar(title_bar_);
    window_agent_->setSystemButton(QWK::WindowAgentBase::WindowIcon, icon_button_);
    window_agent_->setSystemButton(QWK::WindowAgentBase::Minimize, min_button_);
    window_agent_->setSystemButton(QWK::WindowAgentBase::Maximize, max_button_);
    window_agent_->setSystemButton(QWK::WindowAgentBase::Close, close_button_);

    setMenuWidget(title_bar_);
    theme_ = Dark;
    setTheme(theme_);

    connectAll();
}

void QFramelessWindow::connectAll(){
    connect(icon_button_, SIGNAL(clicked()), this, SLOT(clickIconButton()));
    connect(title_bar_, &TitleBar::minRequested, this, &QWidget::showMinimized);
    connect(title_bar_, SIGNAL(maxRequested(bool)), this, SLOT(clickMaxButton(bool)));
    connect(title_bar_, &TitleBar::closeRequested, this, &QWidget::close);
}

void QFramelessWindow::emulateLeaveEvent(QWidget *widget){
    Q_ASSERT(widget);
    if (!widget) {
        return;
    }
    QTimer::singleShot(0, widget, [widget]() {
        const QScreen *screen = widget->screen();
        const QPoint globalPos = QCursor::pos(screen);
        if (!QRect(widget->mapToGlobal(QPoint{0, 0}), widget->size()).contains(globalPos)) {
            QCoreApplication::postEvent(widget, new QEvent(QEvent::Leave));
            if (widget->testAttribute(Qt::WA_Hover)) {
                const QPoint localPos = widget->mapFromGlobal(globalPos);
                const QPoint scenePos = widget->window()->mapFromGlobal(globalPos);
                static constexpr const auto oldPos = QPoint{};
                const Qt::KeyboardModifiers modifiers = QGuiApplication::keyboardModifiers();
                const auto event = new QHoverEvent(QEvent::HoverLeave, scenePos, globalPos, oldPos, modifiers);
                Q_UNUSED(localPos);
                QCoreApplication::postEvent(widget, event);
            }
        }
    });
}

void QFramelessWindow::setTitleBar(QWidget *widget){
    window_agent_->setTitleBar(widget);
    setMenuWidget(widget);
}

void QFramelessWindow::setIconButton(QString path){
    QIcon icon;
    icon.addFile(path);
    icon_button_->setIcon(icon);
    icon_button_->setIconSize(QSize(18,18));
    title_bar_->setIconButton(icon_button_);
}

void QFramelessWindow::setTitleText(QString text){
    title_text_->setText(text);
}

void QFramelessWindow::setStyle(QString path){
    QFile qss(path);
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();
}

void QFramelessWindow::setTheme(Theme theme){
    theme_ = theme;
    switch(theme){
        case Dark:
            setStyle(":/StyleSheet/QFramelessWindow/dark_style.qss");
            title_bar_->setStyle(":/StyleSheet/TitleBar/dark_style.qss");
            break;
        case Light:
            setStyle(":/StyleSheet/QFramelessWindow/light_style.qss");
            title_bar_->setStyle(":/StyleSheet/TitleBar/light_style.qss");
            break;
        }
}

void QFramelessWindow::clickIconButton(){
    window_agent_->showSystemMenu(icon_button_->mapToGlobal(QPoint{0, icon_button_->height()}));
}

void QFramelessWindow::clickMaxButton(bool max){
    if (max) {
        showMaximized();
    } else {
        showNormal();
    }
}

bool QFramelessWindow::event(QEvent *event){
    switch (event->type()) {
    case QEvent::WindowActivate: {
        auto menu = menuWidget();
        menu->setProperty("bar_active", true);
        style()->polish(menu);
        break;
    }

    case QEvent::WindowDeactivate: {
        auto menu = menuWidget();
        menu->setProperty("bar_active", false);
        style()->polish(menu);
        break;
    }

    default:
        break;
    }
    return QMainWindow::event(event);
}
