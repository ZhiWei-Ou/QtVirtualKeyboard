/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyboard.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-26 13:30:52

 * @brief 
 */
#pragma once

#include "common.h"
#include "xlayout.h"

#include <QFrame>
#include <QKeyEvent>
#include <QByteArray>
#include <QJsonDocument>
#include <qpa/qplatforminputcontext.h>

NAMESPACE_KEYBOARD_BEGIN

class Keyboard : public QFrame {
    Q_OBJECT
public:
    explicit Keyboard(QPlatformInputContext *input, const QString &profile);
    virtual ~Keyboard();

    QSize DsignSize() { return m_dsize; }
    void Scale(float fixedW);
    static QSize CalRoundSize(Keyboard *d, float w, int dw = dwidth, int dh = dheight);

    QString Model() const { return m_meta->model; }
    QString Name() const { return objectName(); }

    void Show();
    void Hide();

signals:
    void ShowSignal();
    void HideSignal();

private:
    virtual void loadProfile(QByteArray &&profile, const char *fmt = "json");
    virtual void createByJson(const QJsonDocument &doc);

protected:
    virtual void handleKeyEvent(QKeyEvent *e);
    virtual void inputKeyEvent(QKeyEvent *e);
    void createKeyboardUI();

private slots:
    void onKeyPress(KeyType, Key);
    void onKeyRelease(KeyType, Key);
    void onKeyEvent(int,KeyType, Key);
    void onEvent(Key);

signals:
    void keyboardHide();
    void keyboardNumber();
    void keyboardSymbol();
    void keyboardAlphabet();

private:
    QPlatformInputContext *m_inputCtx;
    KeyboardMeta *m_meta;
    XLayout *m_layout;
    QSize m_dsize;
};

NAMESPACE_KEYBOARD_END
