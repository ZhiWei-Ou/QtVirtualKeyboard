/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file symbol2.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-13 21:56:44

 * @brief 
 */
#pragma once

#include "keyboardabstractIC.h"
#include <QtCore/qobjectdefs.h>

class Keyboard_Symbol2 : public KeyboardAbstractIC
{
    Q_OBJECT
public:
    explicit Keyboard_Symbol2(QPlatformInputContext *ctx, QWidget *parent = Q_NULLPTR);
    virtual ~Keyboard_Symbol2();


    virtual void scale(float currentWidth) override;

protected slots:
    void keyClicked();

private:
    QFrame *rect;
};

