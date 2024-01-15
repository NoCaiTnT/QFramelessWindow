#ifndef TITLEBARBUTTON_H
#define TITLEBARBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class TitleBarButtonPrivate;

class TitleBarButton : public QPushButton{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TitleBarButton)
    Q_PROPERTY(QIcon icon_normal_ READ iconNormal WRITE setIconNormal FINAL)
    Q_PROPERTY(QIcon icon_checked_ READ iconChecked WRITE setIconChecked FINAL)
    Q_PROPERTY(QIcon icon_disabled_ READ iconDisabled WRITE setIconDisabled FINAL)
public:
    explicit TitleBarButton(QWidget *parent = nullptr);
    ~TitleBarButton();

public:
    QIcon iconNormal() const;
    void setIconNormal(const QIcon &icon);

    QIcon iconChecked() const;
    void setIconChecked(const QIcon &icon);

    QIcon iconDisabled() const;
    void setIconDisabled(const QIcon &icon);

Q_SIGNALS:
    void doubleClicked();

protected:
    void checkStateSet() override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

protected:
    TitleBarButton(TitleBarButtonPrivate &d, QWidget *parent = nullptr);
    QScopedPointer<TitleBarButtonPrivate> d_ptr;
};

#endif // TITLEBARBUTTON_H
