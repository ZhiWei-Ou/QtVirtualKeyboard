/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file en_UK.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-05 10:26:45

 * @brief 
 */
#pragma once

#include "keyboardabstractIC.h"
#include <QtCore/qobjectdefs.h>

class Keyboard_EN_UK : public KeyboardAbstractIC
{
    Q_OBJECT
public:
    explicit Keyboard_EN_UK(QPlatformInputContext *ctx, QWidget *parent = Q_NULLPTR);
    virtual ~Keyboard_EN_UK();


    virtual void scale(float currentWidth) override;

protected slots:
    void keyClicked();

private:
    enum Mode { Lower, Upper };
    void updateMode();

    QFrame *rect;
    Mode mode;
};

