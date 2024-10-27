/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file common.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-23 15:08:13

 * @brief 
 */

#include "common.h"
#include <map>
#include <QWidget>


NAMESPACE_KEYBOARD_BEGIN

Qt::Key key2QtKey(const Key& key) {
    if (key >= Key::Key_Event) {
        return Qt::Key_unknown;
    }

    return static_cast<Qt::Key>(key);
}

Key string2Key(const QString& sequence) {
    /*
     * alphabet:
     * q w e r t y u i o p
     * a s d f g h j k l
     * z x c v b n m
     *
     * number:
     * 1 2 3 4 5 6 7 8 9 0
     *
     * symbol:
     * ! @ # $ % ^ & * ( ) - _ = +
     * : ; ' " , < . > /
     * [ ] { } | \ ~ ` ? ,
     * 
     *
     * function:
     * backspace space enter shift capslock
     * tab ctrl alt option
     * delete up down left right
     *
     * event:
     * hide
     */
    static const std::map<QString, Key> keyMap = {
        {"q", Key::Key_Q}, {"w", Key::Key_W}, {"e", Key::Key_E}, {"r", Key::Key_R}, {"t", Key::Key_T}, {"y", Key::Key_Y},
        {"u", Key::Key_U}, {"i", Key::Key_I}, {"o", Key::Key_O}, {"p", Key::Key_P}, {"a", Key::Key_A}, {"s", Key::Key_S},
        {"d", Key::Key_D}, {"f", Key::Key_F}, {"g", Key::Key_G}, {"h", Key::Key_H}, {"j", Key::Key_J}, {"k", Key::Key_K},
        {"l", Key::Key_L}, {"z", Key::Key_Z}, {"x", Key::Key_X}, {"c", Key::Key_C}, {"v", Key::Key_V}, {"b", Key::Key_B},
        {"n", Key::Key_N}, {"m", Key::Key_M},

        {"1", Key::Key_1}, {"2", Key::Key_2}, {"3", Key::Key_3}, {"4", Key::Key_4}, {"5", Key::Key_5}, {"6", Key::Key_6},
        {"7", Key::Key_7}, {"8", Key::Key_8}, {"9", Key::Key_9}, {"0", Key::Key_0},

        {"!", Key::Key_Exclam}, {"@", Key::Key_At}, {"#", Key::Key_NumberSign}, {"$", Key::Key_Dollar}, {"%", Key::Key_Percent},
        {"^", Key::Key_Caret}, {"&", Key::Key_Ampersand}, {"*", Key::Key_Asterisk}, {"(", Key::Key_ParenLeft},
        {")", Key::Key_ParenRight}, {"-", Key::Key_Minus}, {"_", Key::Key_Underscore}, {"=", Key::Key_Equals},
        {"+", Key::Key_Plus}, {":", Key::Key_Colon}, {";", Key::Key_Semicolon}, {"'", Key::Key_QuoteDbl}, {"\"", Key::Key_Quote},
        {",", Key::Key_Comma}, {"<", Key::Key_Less}, {".", Key::Key_Period}, {">", Key::Key_Large}, {"/", Key::Key_Slash},
        {"[", Key::Key_BracketLeft}, {"]", Key::Key_BracketRight}, {"{", Key::Key_BraceLeft}, {"}", Key::Key_BraceRight},
        {"|", Key::Key_Bar}, {"\\", Key::Key_Backslash}, {"~", Key::Key_Tilde}, {"`", Key::Key_Backquote}, {"?", Key::Key_Question},
        {",", Key::Key_Comma}, {"<", Key::Key_Less}, {".", Key::Key_Period}, {">", Key::Key_Large}, {"/", Key::Key_Slash},

        {"backspace", Key::Key_Backspace}, {"space", Key::Key_Space}, {"enter", Key::Key_Enter}, {"shift", Key::Key_Shift},
        {"capslock", Key::Key_CapsLock}, {"tab", Key::Key_Tab}, {"ctrl", Key::Key_Control}, {"alt", Key::Key_Alt},
        {"option", Key::Key_Option}, {"delete", Key::Key_Delete}, {"up", Key::Key_Up}, {"down", Key::Key_Down},
        {"left", Key::Key_Left}, {"right", Key::Key_Right},

        {"hide", Key::Key_Hide}, {"symbol", Key::Key_Symbol}, {"number", Key::Key_Number}, {"alpha", Key::Key_Alpha},

        {"spacer", Key::Key_Specer}
    };

    if (keyMap.count(sequence) > 0) {
        return keyMap.at(sequence);
    } else {
        return Key::Key_UnKnown;
    }
}

QString key2String(const Key& key) {
    static const std::map<Key, QString> keyMap = {
        {Key::Key_Q, "q"}, {Key::Key_W, "w"}, {Key::Key_E, "e"}, {Key::Key_R, "r"}, {Key::Key_T, "t"}, {Key::Key_Y, "y"},
        {Key::Key_U, "u"}, {Key::Key_I, "i"}, {Key::Key_O, "o"}, {Key::Key_P, "p"}, {Key::Key_A, "a"}, {Key::Key_S, "s"},
        {Key::Key_D, "d"}, {Key::Key_F, "f"}, {Key::Key_G, "g"}, {Key::Key_H, "h"}, {Key::Key_J, "j"}, {Key::Key_K, "k"},
        {Key::Key_L, "l"}, {Key::Key_Z, "z"}, {Key::Key_X, "x"}, {Key::Key_C, "c"}, {Key::Key_V, "v"}, {Key::Key_B, "b"},
        {Key::Key_N, "n"}, {Key::Key_M, "m"},

        {Key::Key_1, "1"}, {Key::Key_2, "2"}, {Key::Key_3, "3"}, {Key::Key_4, "4"}, {Key::Key_5, "5"}, {Key::Key_6, "6"},
        {Key::Key_7, "7"}, {Key::Key_8, "8"}, {Key::Key_9, "9"}, {Key::Key_0, "0"},

        {Key::Key_Backspace, "backspace"}, {Key::Key_Space, "space"}, {Key::Key_Enter, "enter"}, {Key::Key_Shift, "shift"},
        {Key::Key_CapsLock, "capslock"}, {Key::Key_Tab, "tab"}, {Key::Key_Control, "ctrl"}, {Key::Key_Alt, "alt"},
        {Key::Key_Option, "option"}, {Key::Key_Delete, "delete"}, {Key::Key_Up, "up"}, {Key::Key_Down, "down"},
        {Key::Key_Left, "left"}, {Key::Key_Right, "right"},

        {Key::Key_Hide, "hide"}, {Key::Key_Symbol, "symbol"}, {Key::Key_Number, "number"}, {Key::Key_Alpha, "alpha"},

        {Key::Key_Specer, "spacer"},
    };

    if (keyMap.count(key) > 0) {
        return keyMap.at(key);
    } else {
        return QString();
    }
}


KeyType string2KeyType(const QString &str) {
    static const QMap<QString, KeyType> KeyTypeString = {
        {"alphabet", KeyType::Alphabet}, {"number", KeyType::Number}, {"symbol", KeyType::Symbol}, {"function", KeyType::Function}, {"event", KeyType::Event},

        {"misc", KeyType::Misc},

        {"unkonwn", KeyType::Unkonwn}};

    if (KeyTypeString.contains(str)) {
        return KeyTypeString.value(str);
    } else {
        return KeyType::Unkonwn;
    }
}

void SetQssStyle(QWidget *w, const QString &file)
{
    QFile qssFile(file);
    auto ok = qssFile.open(QFile::ReadOnly);
    if (ok) {
        w->setStyleSheet(qssFile.readAll());
        qssFile.close();
    }
}

NAMESPACE_KEYBOARD_END
