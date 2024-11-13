/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file common.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-23 15:06:34

 * @brief 
 */
#pragma once

#include <QMap>
#include <QKeyEvent>
#include <QString>
#include <QtCore/qnamespace.h>


#define NAMESPACE xkeyboard

#define NAMESPACE_KEYBOARD_BEGIN namespace NAMESPACE {
#define NAMESPACE_KEYBOARD_END }

NAMESPACE_KEYBOARD_BEGIN 
using Error = int;
enum ErrorType : int {
    OK = 0, ERROR,
};

#define Property_Style_Basic "basic"
#define Property_Style_Customize "customize"

NAMESPACE_KEYBOARD_END

NAMESPACE_KEYBOARD_BEGIN 
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
 * misc:
 * specer
 *
 * event:
 * hide symbol number alphabet
 */

enum class KeyType { Alphabet = 0x0, Number = 0x1, Symbol = 0x2, Function = 0x3, Event = 0x4, Misc = 0x5, Unkonwn = 0xff };
KeyType string2KeyType(const QString &str);

enum Key : int {
    /* alphabet */
    Key_Q = Qt::Key_Q, Key_W = Qt::Key_W, Key_E = Qt::Key_E, Key_R = Qt::Key_R, Key_T = Qt::Key_T, Key_Y = Qt::Key_Y,
    Key_U = Qt::Key_U, Key_I = Qt::Key_I, Key_O = Qt::Key_O, Key_P = Qt::Key_P, Key_A = Qt::Key_A, Key_S = Qt::Key_S,
    Key_D = Qt::Key_D, Key_F = Qt::Key_F, Key_G = Qt::Key_G, Key_H = Qt::Key_H, Key_J = Qt::Key_J, Key_K = Qt::Key_K,
    Key_L = Qt::Key_L, Key_Z = Qt::Key_Z, Key_X = Qt::Key_X, Key_C = Qt::Key_C, Key_V = Qt::Key_V, Key_B = Qt::Key_B,
    Key_N = Qt::Key_N, Key_M = Qt::Key_M,

    /* number */
    Key_1 = Qt::Key_1, Key_2 = Qt::Key_2, Key_3 = Qt::Key_3, Key_4 = Qt::Key_4, Key_5 = Qt::Key_5, Key_6 = Qt::Key_6,
    Key_7 = Qt::Key_7, Key_8 = Qt::Key_8, Key_9 = Qt::Key_9, Key_0 = Qt::Key_0,

    /* symbol */
    Key_Exclam/*!*/ = Qt::Key_Exclam, Key_At/*@*/ = Qt::Key_At, Key_NumberSign/*#*/ = Qt::Key_NumberSign,
    Key_Dollar/*$*/ = Qt::Key_Dollar, Key_Percent/*%*/ = Qt::Key_Percent, Key_Caret/*^*/ = Qt::Key_AsciiCircum,
    Key_Ampersand/*&*/ = Qt::Key_Ampersand, Key_Asterisk/***/ = Qt::Key_Asterisk, Key_ParenLeft/*(*/ = Qt::Key_ParenLeft,
    Key_ParenRight/*)*/ = Qt::Key_ParenRight, Key_Minus/*-*/ = Qt::Key_Minus, Key_Underscore/*_*/ = Qt::Key_Underscore,
    Key_Equals/*=*/ = Qt::Key_Equal, Key_Plus/*+*/ = Qt::Key_Plus, Key_Colon/*:*/ = Qt::Key_Colon,
    Key_Semicolon/*;*/ = Qt::Key_Semicolon, Key_Quote/*'*/ = Qt::Key_Question, Key_QuoteDbl/*"*/ = Qt::Key_QuoteDbl,
    Key_Comma/*,*/ = Qt::Key_Comma, Key_Less/*<*/=Qt::Key_Less, Key_Period/*.*/ = Qt::Key_Period, Key_Large/*>*/=Qt::Key_Greater,
    Key_Slash/*\/*/ = Qt::Key_Slash, Key_Backslash/*\*/ = Qt::Key_Backslash, Key_Tilde/*~*/ = Qt::Key_AsciiTilde,
    Key_BracketLeft/*[*/=Qt::Key_BraceLeft, Key_BracketRight/*]*/ = Qt::Key_BraceRight,
    Key_BraceLeft/*{*/ = Qt::Key_BraceLeft, Key_BraceRight/*}*/ = Qt::Key_BraceRight, Key_Bar/*|*/ = Qt::Key_Bar,
    Key_Backquote/*`*/ = Qt::Key_QuoteLeft, Key_Question/*?*/ = Qt::Key_Question, Key_Semicolon2/*:*/ = Qt::Key_Semicolon,

    /* function */
    Key_Backspace = Qt::Key_Backspace, Key_Space = Qt::Key_Space, Key_Enter = Qt::Key_Enter, Key_Shift = Qt::Key_Shift,
    Key_CapsLock = Qt::Key_CapsLock, Key_Tab = Qt::Key_Tab, Key_Control = Qt::Key_Control, Key_Alt = Qt::Key_Alt,
    Key_Option = Qt::Key_Option, Key_Delete = Qt::Key_Delete,
    Key_Up = Qt::Key_Up, Key_Down = Qt::Key_Down, Key_Left = Qt::Key_Left, Key_Right = Qt::Key_Right,

    /* Event */
    Key_Event = 0x02000001,
    Key_Hide = 0x02000002, Key_Symbol = 0x02000003,
    Key_Number = 0x02000004, Key_Alpha = 0x02000005, Key_ChangeKeyboard = 0x02000006,
    Key_Event2 = 0x020000ff,

    /* misc */
    Key_Specer = 0x03000001,

    /**/
    Key_UnKnown = Qt::Key_unknown
};

/*
 * Key To Qt::Key
 *
 * */
Qt::Key key2QtKey(const Key& key);

/*
 * Key Sequence to Key
 *
 * @throw std::runtime_error
 * */
Key string2Key(const QString& sequence);

/*
 * Key to Key Sequence
 *
 * @throw std::runtime_error
 * */
QString key2String(const Key& key);

void SetQssStyle(QWidget *w, const QString &file);

NAMESPACE_KEYBOARD_END

Q_DECLARE_METATYPE(NAMESPACE::Key)
Q_DECLARE_METATYPE(NAMESPACE::KeyType)

