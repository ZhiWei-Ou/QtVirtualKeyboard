/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file xlayout.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-26 13:53:00

 * @brief 
 */
#include "xlayout.h"
#include <QJsonArray>

NAMESPACE::KeyMeta::KeyMeta(const QJsonObject &obj)
{
    /*
       {
       "key": "shift",
       "pixmap": ":assets/images/shift-80c342.svg",
       "pretty": "Shift",
       "style": ":assets/shift.qss",
       "type": "function",
       "weight": 204
       }
   */

    type = string2KeyType(obj.value("type").toString());
    key = string2Key(obj.value("key").toString());
    pretty = obj.value("pretty").toString();
    icon = obj.value("icon").toString();
    pixmap = obj.value("pixmap").toString();
    style = obj.value("style").toString();
    weight = obj.value("weight").toInt();
}


NAMESPACE::KeyboardMeta::KeyboardMeta(const QJsonObject &obj)
{
    name = obj["name"].toString();
    model = obj["model"].toString();
    category = obj["category"].toString();
    description = obj["description"].toString();
    version = obj["version"].toString();
}


NAMESPACE::H::H(const QJsonObject &obj)
{
    /*
       {
       "row": 0,
       "spacing": 5,
       "margin": {
       "top": 1,
       "bottom": 1,
       "left": 1,
       "right": 1
       },
       "keys": [
       {"type": "alphabet", "key": "q", "pretty": "q", "weight": 1},
       ...
       ]
       },
       */

    row = obj.value("row").toInt();
    spacing = obj.value("spacing").toInt();

    auto m = obj.value("margin").toObject();
    margin.top = m.value("top").toInt();
    margin.bottom = m.value("bottom").toInt();
    margin.left = m.value("left").toInt();
    margin.right = m.value("right").toInt();

    QJsonArray arr = obj.value("keys").toArray();
    for (const auto &i : arr) {
        keys.push_back(KeyMeta(i.toObject()));
    }
}

NAMESPACE::XLayout::XLayout(const QJsonDocument &obj)
{
    auto root = obj["keyboard"].toObject();
    auto s = root["style"].toString();
    auto l = root["layout"].toArray();

    style = s;

    for (const auto &i : l) {
        rows.push_back(H(i.toObject()));
    }
}
