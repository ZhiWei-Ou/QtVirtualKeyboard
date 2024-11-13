/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyBtn.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-26 12:56:42

 * @brief 
 */

#include "keyBtn.h"
#include "common.h"
#include <QPixmap>
#include <QDebug>

NAMESPACE_KEYBOARD_BEGIN

NAMESPACE::KeyBtn::KeyBtn(QJsonObject &&meta, QWidget *parent)
    : KeyBtn(KeyMeta(meta), parent)
{
}

NAMESPACE::KeyBtn::KeyBtn(const KeyMeta &meta, QWidget *parent, QSizePolicy::Policy hor, QSizePolicy::Policy ver)
    : QPushButton(parent), m_meta(meta)
{
    if (!m_meta.pixmap.isEmpty()) {
        setIcon(QPixmap(m_meta.pixmap));
    } else {
        setText(m_meta.pretty);
        setIcon(QIcon(m_meta.icon));
    }

    if (!m_meta.style.isEmpty()) {
        SetStyleSheet(m_meta.style);

        setProperty("style", Property_Style_Customize);
    } else {
        setProperty("style", Property_Style_Basic);
    }

    setProperty("key", key2String(m_meta.key));

    setSizePolicy(hor, ver);

    connect(this, &QPushButton::pressed, [this]() { emit KeyPressed(m_meta.type, m_meta.key, QVariant(m_meta.to)); });
    connect(this, &QPushButton::released, [this]() { emit KeyReleased(m_meta.type, m_meta.key, QVariant(m_meta.to)); });
}

NAMESPACE::KeyBtn::~KeyBtn()
{
}

KeyType NAMESPACE::KeyBtn::type()
{
    return m_meta.type;
}

Key NAMESPACE::KeyBtn::key()
{
    return m_meta.key;
}

QString NAMESPACE::KeyBtn::Style()
{
    return m_meta.style;
}

void NAMESPACE::KeyBtn::SetObjectName(const QString &name)
{
    setObjectName(name);
}

void NAMESPACE::KeyBtn::SetStyleSheet(const QString &style)
{
    return SetQssStyle(this, style);
}

NAMESPACE_KEYBOARD_END

