/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyboardabstractIC.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-05 10:25:57

 * @brief 
 */
#include "keyboardabstractIC.h"
#include "platformIC.h"
#include <QKeyEvent>
#include <QDebug>
#include <QtMath>

KeyboardAbstractIC::KeyboardAbstractIC(QPlatformInputContext *ctx, QWidget *parent)
    : QFrame(parent), m_ctx(ctx), m_logCategory("qtkeyboard.KeyboardAbstractIC")
{
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    this->resize(KeyboardDesignWidth, KeyboardDesignHeight);
}

inline PlatformInputContext *Cast(QPlatformInputContext *p)
{
    return dynamic_cast<PlatformInputContext *>(p);
}

KeyboardAbstractIC::~KeyboardAbstractIC()
{
}


void KeyboardAbstractIC::sendKeyClick(int key, const QString &text, int modifiers)
{
    if (m_ctx) {
        QKeyEvent pressEvent(QEvent::KeyPress, key, Qt::KeyboardModifiers(modifiers), text);
        QKeyEvent releaseEvent(QEvent::KeyRelease, key, Qt::KeyboardModifiers(modifiers), text);

        Cast(m_ctx)->sendKeyEvent(&pressEvent);
        Cast(m_ctx)->sendKeyEvent(&releaseEvent);

        qCDebug(m_logCategory) << "sendKeyClick() ";
    } else {
        qCWarning(m_logCategory) << __PRETTY_FUNCTION__ <<" m_ctx is null";
    }
}

void KeyboardAbstractIC::scale(float currentWidth)
{
    int w, h;
    w = qRound(currentWidth);
    h = w * KeyboardDesignHeight / KeyboardDesignWidth;
    this->resize(w, h);
}

QSize KeyboardAbstractIC::keyboardScaleSize(float currentWidth)
{
    int w, h;
    w = qRound(currentWidth);
    h = w * KeyboardDesignHeight / KeyboardDesignWidth;

    return QSize(w, h);
}

void KeyboardAbstractIC::keyClicked(QPushButton *b, Qt::Key k, QString type, QString func)
{
    if (type == "letter" || type == "symbol") {
        if (b->text() == "&&") {
            return sendKeyClick(k, "&");
        }
        return sendKeyClick(k, b->text());
    } else if (type == "function") {
        if (func == "hideKeyboard") {
            emit Sig_FunctionKeyEvent(FunctionKeyType::HideKeyboard);
        } else if (func == "symbolMode") {
            emit Sig_FunctionKeyEvent(FunctionKeyType::Symbol_1);
        } else if (func == "flipTo1") {
            emit Sig_FunctionKeyEvent(FunctionKeyType::Symbol_1);
        } else if (func == "flipTo2") {
            emit Sig_FunctionKeyEvent(FunctionKeyType::Symbol_2);
        } else if (func == "alphabet") {
            emit Sig_FunctionKeyEvent(FunctionKeyType::Alphabet);
        }
    } else if (type == "misc") {
        if (k == Qt::Key_Backspace) {
            return sendKeyClick(k);
        } else if (k == Qt::Key_Space) {
            return sendKeyClick(k, " ");
        } else if (k == Qt::Key_Enter) {
            return sendKeyClick(k);
        }
    }
}
