/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyBtn.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-26 12:56:34

 * @brief 
 */
#pragma once

#include "common.h"
#include "xlayout.h"
#include <QJsonObject>
#include <QPushButton>

NAMESPACE_KEYBOARD_BEGIN

// #define KeyBtn_Spec_Style_ObjName_Suffix "_ss"
// #define KeyBtn_Not_Spec_Style_ObjName_Suffix "_ns"

class KeyBtn : public QPushButton {
    Q_OBJECT
public:
    explicit KeyBtn(QJsonObject &&meta, QWidget *parent = Q_NULLPTR);
    explicit KeyBtn(const KeyMeta &meta,
            QWidget *parent = Q_NULLPTR,
            QSizePolicy::Policy hor = QSizePolicy::Expanding,
            QSizePolicy::Policy ver = QSizePolicy::Expanding);
    virtual ~KeyBtn();

    Key key();
    KeyType type();
    QString Style();

    void SetStyleSheet(const QString &style);
    void SetObjectName(const QString &name);

signals:
    void KeyPressed(KeyType, Key, QVariant = QVariant());
    void KeyReleased(KeyType, Key, QVariant = QVariant());

private:
    KeyMeta m_meta;
};

NAMESPACE_KEYBOARD_END

