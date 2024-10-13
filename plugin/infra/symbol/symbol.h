/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file symbol.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-13 20:27:28

 * @brief 
 */
#pragma once

#include "keyboardabstractIC.h"
#include <QtCore/qobjectdefs.h>

class Keyboard_Symbol : public KeyboardAbstractIC
{
    Q_OBJECT
public:
    explicit Keyboard_Symbol(QPlatformInputContext *ctx, QWidget *parent = Q_NULLPTR);
    virtual ~Keyboard_Symbol();


    virtual void scale(float currentWidth) override;

protected slots:
    void keyClicked();

private:
    QFrame *rect;
};

