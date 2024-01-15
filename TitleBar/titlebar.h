#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QMenuBar>
#include <QLabel>
#include <QAbstractButton>
#include <QFile>

class TitleBarPrivate;

class TitleBar : public QFrame{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TitleBar)
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

public:
    QAbstractButton *getIconButton() const;
    QLabel *getTitleLabel() const;
    QAbstractButton *getMinButton() const;
    QAbstractButton *getMaxButton() const;
    QAbstractButton *getCloseButton() const;

    void setIconButton(QAbstractButton *btn);
    void setTitleLabel(QLabel *label);
    void setMinButton(QAbstractButton *btn);
    void setMaxButton(QAbstractButton *btn);
    void setCloseButton(QAbstractButton *btn);

    QAbstractButton *takeIconButton();
    QLabel *takeTitleLabel();
    QAbstractButton *takeMinButton();
    QAbstractButton *takeMaxButton();
    QAbstractButton *takeCloseButton();

    QWidget *hostWidget() const;
    void setHostWidget(QWidget *w);

    bool titleFollowWindow() const;
    void setTitleFollowWindow(bool value);

    bool iconFollowWindow() const;
    void setIconFollowWindow(bool value);

    void setStyle(QString path);

Q_SIGNALS:
    void minRequested();
    void maxRequested(bool max = false);
    void closeRequested();

protected:
    TitleBar(TitleBarPrivate &d, QWidget *parent = nullptr);
    QScopedPointer<TitleBarPrivate> d_ptr;
};

#endif // TITLEBAR_H
