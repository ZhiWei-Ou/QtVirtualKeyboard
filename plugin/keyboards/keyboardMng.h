/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyboardMng.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-27 18:12:37

 * @brief 
 */
#pragma once

#include <QMap>
#include <QObject>
#include <QWindow>
#include <QStringList>
#include <QSignalMapper>
#include <qpa/qplatforminputcontext.h>

#include "common.h"
#include "keyboard.h"

NAMESPACE_KEYBOARD_BEGIN

class KeyboardMng : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardMng(const QStringList &profiles, QPlatformInputContext *ctx, QObject *parent = nullptr);
    virtual ~KeyboardMng() = default;

    enum Direction : int {FloatBottom};
    void SetDirection(int direction, QWindow *bench);
    void Scale(float currentWidth);
    void DefaultShow();
    void HideAll();

private slots:
    void onKeyboardShow(QString &name);
    void onKeyboardHide(QString &name);
    void onKeyboardHideAll();
    void onChangeKeyboard(const QString &model);
    
private:
    QMap<QString, Keyboard*> m_keyboards;
    QSignalMapper *m_showKeyboardSignalMapper;
    QSignalMapper *m_hideKeyboardSignalMapper;

    QPlatformInputContext *m_ctx;

    QString m_defaultKeyboardName;
};

NAMESPACE_KEYBOARD_END
