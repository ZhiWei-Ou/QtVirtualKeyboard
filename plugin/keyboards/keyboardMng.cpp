/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyboardMng.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-27 18:12:46

 * @brief 
 */
#include "keyboardMng.h"
#include <QGuiApplication>
#include <QtCore/qglobal.h>
#include <QDebug>

NAMESPACE_KEYBOARD_BEGIN

KeyboardMng::KeyboardMng(const QStringList &profiles, QPlatformInputContext *ctx, QObject *parent)
    : QObject(nullptr), m_ctx(ctx),
    m_showKeyboardSignalMapper(new QSignalMapper(this)), m_hideKeyboardSignalMapper(new QSignalMapper(this))
{
    bool setDefaultKeyoardNameFlag = false;

    for (const QString &profile : profiles) {
        auto k = new Keyboard(m_ctx, profile);
        m_keyboards[k->Name()] = k;

        if (!setDefaultKeyoardNameFlag) {
            setDefaultKeyoardNameFlag = true;
            m_defaultKeyboardName = k->Name();
        }

        connect(k, SIGNAL(ShowSignal()), m_showKeyboardSignalMapper, SLOT(map()));
        m_showKeyboardSignalMapper->setMapping(k, k->Name());

        connect(k, SIGNAL(HideSignal()), m_hideKeyboardSignalMapper, SLOT(map()));
        m_hideKeyboardSignalMapper->setMapping(k, k->Name());

        connect(k, SIGNAL(keyboardHide()), this, SLOT(onKeyboardHide(onKeyboardHideAll())));

        connect(k, &Keyboard::keyboardWanaChange, this, &KeyboardMng::JustShowSpec);

        // connect(k, &Keyboard::keyboardNumber, this, [this]() {
        //     onChangeKeyboard("number");
        // });
        // connect(k, &Keyboard::keyboardSymbol, this, [this]() {
        //     onChangeKeyboard("symbol");            
        // });
        //
        // connect(k, &Keyboard::keyboardAlphabet, this, [this]() {
        //     onChangeKeyboard("alphabet");            
        // });
    }

    // connect(m_showKeyboardSignalMapper, SIGNAL(mapped(QString)), this, SLOT(onKeyboardShow(QString)));
    // connect(m_hideKeyboardSignalMapper, SIGNAL(mapped(QString)), this, SLOT(onKeyboardHide(QString)));
}

void KeyboardMng::onKeyboardShow(QString &name)
{

}

void KeyboardMng::onKeyboardHide(QString &name)
{

}

void KeyboardMng::onKeyboardHideAll()
{

}

void KeyboardMng::JustShowSpec(const QString &name)
{
    qDebug() << "-- JustShowSpec: " << name;
    Keyboard *spec = Q_NULLPTR;
    for (auto &&k : m_keyboards) {
        if (k->Name() == name) {
            spec = k;
        } else {
            k->Hide();
        }
    }

    if (spec) {
        spec->Show();
    }
}

void KeyboardMng::DefaultShow()
{
    for (auto &&k : m_keyboards) {
        if (k->Name() == m_defaultKeyboardName) {
            k->Show();
            break;
        } else {
            k->Hide();
        }
    }
}

void KeyboardMng::HideAll()
{
    for (auto &&k : m_keyboards) {
        k->Hide();
    }
}

void KeyboardMng::Scale(float currentWidth)
{
    for (auto &&k : m_keyboards) {
        k->Scale(currentWidth);
    }
}

void KeyboardMng::SetDirection(int direction, QWindow *bench)
{
    QWindow *w;
    if (bench == Q_NULLPTR)
        w = QGuiApplication::focusWindow();
    else
        w = bench;

    switch (direction) {
    case FloatBottom:
        for (auto &&k : m_keyboards) {
            k->move(w->x() + 0, w->y() + w->size().height() - k->height());
        }
        break;

    default:
        break;
    }
}

void KeyboardMng::onChangeKeyboard(const QString &model)
{
    for (auto &&k : m_keyboards) {
        if (k->Model() == model) {
            k->Show();
            break;
        } else {
            k->Hide();
        }
    }

}

NAMESPACE_KEYBOARD_END
