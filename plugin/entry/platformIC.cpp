/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file platformIC.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-04 21:24:26

 * @brief 
 */
#include "platformIC.h"
#include <QLocale>
#include <QRectF>
#include <QDebug>
#include <QLoggingCategory>
#include <QGuiApplication>
#include <QWindow>
#include <QStackedWidget>
#include <QtCore/qloggingcategory.h>

#include "en/en_UK.h"
#include "symbol/symbol.h"
#include "symbol/symbol2.h"

QLoggingCategory qtKeyboardCategory("qtkeyboard.platformIC");

__attribute__((weak)) QSize GlobGetScreenSize(bool &ok)
{
    qCWarning(qtKeyboardCategory) << "Suggested to define QSize GlobGetScreenSize(bool &ok)";
    ok = false;
    return QSize(0, 0);
}

PlatformInputContext::PlatformInputContext(QPlatformInputContextPlugin *pluginCtx)
    : QPlatformInputContext()
{
    bool ok = false;
    QSize size = GlobGetScreenSize(ok);
    if (ok) {
        m_screenSize = size;
        qCDebug(qtKeyboardCategory) << "Get user define screen size: " << m_screenSize;

    }

    qCDebug(qtKeyboardCategory) << "PlatformInputContext::PlatformInputContext()";
}

PlatformInputContext::~PlatformInputContext()
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::~PlatformInputContext()";
}

bool PlatformInputContext::isValid() const
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::isValid()";

    return true;
}

bool PlatformInputContext::hasCapability(Capability capability) const
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::hasCapability(capability:" << capability << ")";
    return true;
}

void PlatformInputContext::reset()
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::reset()";
}
void PlatformInputContext::commit()
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::commit()";
}

void PlatformInputContext::invokeAction(QInputMethod::Action act, int cursorPosition)
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::invokeAction(act:" << act << ", cursorPosition:" << cursorPosition << ")";
}

bool PlatformInputContext::filterEvent(const QEvent *event)
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::filterEvent(event:" << event << ")";
    return true;
}

QRectF PlatformInputContext::keyboardRect() const
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::keyboardRect()";
    return QRectF();
}

bool PlatformInputContext::isAnimating() const
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::isAnimating()";
    return false;
}

void PlatformInputContext::showInputPanel()
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::showInputPanel()";

    if (m_keyboards[page_en_uk]) {
        m_keyboards[page_en_uk]->show();
    }
}

void PlatformInputContext::hideInputPanel()
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::hideInputPanel()";

    for (auto w : m_keyboards) {
        w->hide();
    }
}

bool PlatformInputContext::isInputPanelVisible() const
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::isInputPanelVisible()";
    return true;
}

QLocale PlatformInputContext::locale() const
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::locale()";
    return QLocale();
}   

Qt::LayoutDirection PlatformInputContext::inputDirection() const
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::inputDirection()";
    return Qt::LayoutDirectionAuto;
}   

void PlatformInputContext::update(Qt::InputMethodQueries queries)
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::update(queries:" << queries << ")";
}   

void PlatformInputContext::setFocusObject(QObject *object)
{
    qCDebug(qtKeyboardCategory) << "PlatformInputContext::setFocusObject(object:" << object << ")";


    static bool flag = false;
    if (flag) {
        return;
    } else {
        QWindow *w = QGuiApplication::focusWindow();
        if (w) {
            m_screenSize = w->size();
            qCDebug(qtKeyboardCategory) << "QGuiApplication::focusWindow: " << w
                                << "Size: " << m_screenSize;
        }

        m_keyboards[page_en_uk] = new Keyboard_EN_UK(this);
        m_keyboards[page_symbol_1] = new Keyboard_Symbol(this);
        m_keyboards[page_symbol_2] = new Keyboard_Symbol2(this);
        for (auto p : m_keyboards) {
            if (p) {
                p->scale(m_screenSize.width());
                p->move(w->x() + 0, w->y() + (m_screenSize.height()/2 - p->height()/2));
                connect(p, &KeyboardAbstractIC::Sig_FunctionKeyEvent, this, &PlatformInputContext::FunctionKeyHandler);
            }
        }
        flag = true;
    }
}   

void PlatformInputContext::FunctionKeyHandler(KeyboardAbstractIC::FunctionKeyType type)
{
    switch (type) {
    case KeyboardAbstractIC::Alphabet:
        m_keyboards[page_en_uk]->show();

        m_keyboards[page_symbol_1]->hide();
        m_keyboards[page_symbol_2]->hide();
        break;
    case KeyboardAbstractIC::Symbol_1:
        m_keyboards[page_symbol_1]->show();

        m_keyboards[page_symbol_2]->hide();
        m_keyboards[page_en_uk]->hide();
        break;
    case KeyboardAbstractIC::Symbol_2:
        m_keyboards[page_symbol_2]->show();

        m_keyboards[page_symbol_1]->hide();
        m_keyboards[page_en_uk]->hide();
        break;
    case KeyboardAbstractIC::HideKeyboard:
        hideInputPanel();
        break;
    default:
        break;
    }
}

void PlatformInputContext::sendKeyEvent(QKeyEvent *event)
{
    const QGuiApplication *app = qApp;
    QWindow *focusWindow = app ? app->focusWindow() : nullptr;
    if (focusWindow) {
        QGuiApplication::sendEvent(focusWindow, event);
    }
}
