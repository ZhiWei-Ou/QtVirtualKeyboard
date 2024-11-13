/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file xlayout.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-26 13:52:51

 * @brief 
 */
#pragma once

#include "common.h"
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>

NAMESPACE_KEYBOARD_BEGIN


/* Design Size */
static constexpr int dwidth = 2560, dheight = 800;

struct KeyboardMeta {
    QString name;
    QString model;
    QString category;
    QString description;
    QString version;

    KeyboardMeta() = default;
    explicit KeyboardMeta(const QJsonObject &obj);
};


struct KeyMeta {
    KeyType type;
    Key key;
    int weight;
    QString pretty;
    QString icon;
    QString pixmap;
    QString style;
    QString to;

    KeyMeta() = default;
    explicit KeyMeta(const QJsonObject &obj);
    explicit KeyMeta(const KeyMeta &obj) = default;
    ~KeyMeta() = default;
};

struct H {
    int row;
    int spacing;
    struct Margin {
        int top;
        int bottom;
        int left;
        int right;
    };
    Margin margin;
    QVector<KeyMeta> keys;

    H() = default;
    explicit H(const QJsonObject &obj);
    H(const H &obj) = default;
    ~H() = default;
};

struct XLayout {

    QString style;
    QVector<H> rows;

    XLayout() = default;
    explicit XLayout(const QJsonDocument &obj);
    XLayout(const XLayout &obj) = default;
    ~XLayout() = default;
};

NAMESPACE_KEYBOARD_END
