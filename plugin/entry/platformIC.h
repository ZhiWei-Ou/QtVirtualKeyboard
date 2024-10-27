/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file platformIC.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-04 21:24:22

 * @brief 
 */
#pragma once

#include <QtCore/qcompilerdetection.h>
#include <qpa/qplatforminputcontext.h>
#include <qpa/qplatforminputcontextplugin_p.h>
#include <QSize>
#include <QKeyEvent>
#include <QMap>

#include "common.h"
#include "keyboardMng.h"

class PlatformInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    explicit PlatformInputContext(QPlatformInputContextPlugin *pluginCtx = Q_NULLPTR);
    virtual ~PlatformInputContext();


    // QPlatformInputContext ABI
    virtual bool isValid() const override;
    virtual bool hasCapability(Capability capability) const override;

    virtual void reset() override;
    virtual void commit() override;
    virtual void invokeAction(QInputMethod::Action, int cursorPosition) override;
    virtual bool filterEvent(const QEvent *event) override;
    virtual QRectF keyboardRect() const override;

    virtual bool isAnimating() const override;

    virtual void showInputPanel() override;
    virtual void hideInputPanel() override;
    virtual bool isInputPanelVisible() const override;

    virtual QLocale locale() const override;
    virtual Qt::LayoutDirection inputDirection() const override;

    virtual void update(Qt::InputMethodQueries queries) override;

    virtual void setFocusObject(QObject *object) override;

    void sendKeyEvent(QKeyEvent *event);

private:
    QSize m_screenSize;
    bool m_keyboardUiInitOnceFlag;
    NAMESPACE::KeyboardMng *m_keyboardMng;
};

