/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyboard.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-26 13:31:00

 * @brief 
 */
#include "keyboard.h"

#include "keyBtn.h"
#include "common.h"
#include "platformIC.h"
#include "xlayout.h"
#include <QLayout>
#include <QtMath>
#include <QtCore/qglobal.h>
#include <cstring>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

inline PlatformInputContext *Cast(QPlatformInputContext *p)
{ return dynamic_cast<PlatformInputContext *>(p); }

NAMESPACE::Keyboard::Keyboard(QPlatformInputContext *input, const QString &profile)
    : QFrame(Q_NULLPTR), m_inputCtx(input), m_meta(Q_NULLPTR), m_layout(Q_NULLPTR),m_dsize(dwidth, dheight)
{
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    resize(m_dsize);
    setLayout(new QHBoxLayout(this));

    setProperty("flag", "root");

    QFile f(profile);
    f.open(QIODevice::ReadOnly);

    loadProfile(f.readAll());
    createKeyboardUI();

    f.close();

    setObjectName(m_meta->name);
}

NAMESPACE::Keyboard::~Keyboard()
{
}

void NAMESPACE::Keyboard::handleKeyEvent(QKeyEvent *e)
{
}

void NAMESPACE::Keyboard::inputKeyEvent(QKeyEvent *e)
{
    if (e) {
        try {
            Cast(m_inputCtx)->sendKeyEvent(e);
        } catch (...) {
            // Catch All Exception
            // This code will never do anything
        }
    }
}

void NAMESPACE::Keyboard::loadProfile(QByteArray &&profile, const char *fmt)
{
    if (strcmp(fmt, "json") == 0) {
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(profile, &err);
        createByJson(doc);
    } else {
        // further code
        // YAML, XML, Conf
    }
}

void NAMESPACE::Keyboard::createByJson(const QJsonDocument &doc)
{
    if (!m_meta) {
        m_meta = new KeyboardMeta(doc.object());
    }

    if (!m_layout) {
        m_layout = new XLayout(doc);
    }
}

void NAMESPACE::Keyboard::createKeyboardUI()
{
    if (!m_layout) {
        return;
    }

    QFrame *rectangle = new QFrame(this);
    rectangle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *rectanle_vlayout = new QVBoxLayout(rectangle);
    rectangle->setLayout(rectanle_vlayout);

    rectanle_vlayout->setContentsMargins(0, 0, 0, 0);
    rectanle_vlayout->setSpacing(5);

    auto root_layout = layout();
    root_layout->setContentsMargins(10, 10, 10, 10);
    root_layout->setSpacing(0);
    root_layout->addWidget(rectangle);

    for (auto &&row : m_layout->rows) {
        QFrame *f = new QFrame(rectangle);
        QHBoxLayout *l = new QHBoxLayout(f);
        f->setLayout(l);
        l->setSpacing(row.spacing);
        l->setContentsMargins(row.margin.left, row.margin.top, row.margin.right, row.margin.bottom);
        rectangle->layout()->addWidget(f);

        for (auto &&key : row.keys) {
            KeyBtn *btn = new KeyBtn(key, this);
            l->addWidget(btn, key.weight);

            connect(btn, SIGNAL(KeyPressed(KeyType, Key)), SLOT(onKeyPress(KeyType, Key)));
            connect(btn, SIGNAL(KeyReleased(KeyType, Key)), SLOT(onKeyRelease(KeyType, Key)));
        }
    }

    layout()->addWidget(rectangle);
    rectangle->adjustSize();

    SetQssStyle(this, m_layout->style);
}

void NAMESPACE::Keyboard::Scale(float fixedW)
{
    resize(CalRoundSize(this, fixedW));
}

QSize NAMESPACE::Keyboard::CalRoundSize(Keyboard *d, float w, int dw, int dh)
{
    int wid, hei;
    wid = qRound(w);
    hei = w * dh / dw;

    return QSize(wid, hei);
}

void NAMESPACE::Keyboard::Show()
{
    if (!isVisible()) {
        emit ShowSignal();
        show();
    }
}

void NAMESPACE::Keyboard::Hide()
{
    if (isVisible()) {
        emit HideSignal();
        hide();
    }
}

void NAMESPACE::Keyboard::onKeyPress(KeyType t, Key k)
{
    return onKeyEvent(QKeyEvent::KeyPress, t, k);
}

void NAMESPACE::Keyboard::onKeyRelease(KeyType t, Key k)
{
    return onKeyEvent(QKeyEvent::KeyRelease, t, k);
}

void NAMESPACE::Keyboard::onKeyEvent(int type, KeyType t, Key k)
{
    auto *btn = dynamic_cast<KeyBtn *>(sender());

    switch (t) {
    case KeyType::Alphabet:
    case KeyType::Number:
    case KeyType::Symbol:
        {
            QKeyEvent evt(QEvent::Type(type), key2QtKey(k), Qt::NoModifier, btn->text());
            inputKeyEvent(&evt);
        }
        break;

    case KeyType::Function:
        {
            if (k == Key::Key_Space) {
                QKeyEvent evt(QEvent::Type(type), key2QtKey(k), Qt::NoModifier, " ");
                inputKeyEvent(&evt);
            } else {
                QKeyEvent evt(QEvent::Type(type), key2QtKey(k), Qt::NoModifier, "");
                inputKeyEvent(&evt);
            }
        }
        break;
    case KeyType::Event:
        {
            onEvent(k);
        }
        break;
    case KeyType::Misc:
    case KeyType::Unkonwn:
    default:
        break;
    }
}

void NAMESPACE::Keyboard::onEvent(Key k)
{
    switch (k) {
    case Key_Hide:
        emit keyboardHide();
        break;
    case Key_Symbol:
        emit keyboardSymbol();
        break;
    case Key_Number:
        emit keyboardNumber();
        break;
    case Key_Alpha:
        emit keyboardAlphabet();
        break;
    default:
        break;
    }
}
