/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file keyboardabstractIC.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-05 10:25:54

 * @brief 
 */
#pragma once

#include <QFrame>
#include <QString>
#include <QPushButton>
#include <QtCore/qglobal.h>
#include <qpa/qplatforminputcontext.h>
#include <QLoggingCategory>

#define KeyboardDesignWidth 2560
#define KeyboardDesignHeight 800

static constexpr double keyboardRelativeLeftMargin = 114.0 / KeyboardDesignWidth;
static constexpr double keyboardRelativeRightMargin = 114.0 / KeyboardDesignWidth;
static constexpr double keyboardRelativeTopMargin = 13.0 / KeyboardDesignHeight;
static constexpr double keyboardRelativeBottomMargin = 86.0 / KeyboardDesignHeight;

// #define keyboardRelativeLeftMargin (114 / KeyboardDesignWidth)
// #define keyboardRelativeRightMargin (114 / KeyboardDesignWidth)
// #define keyboardRelativeTopMargin (13 / KeyboardDesignHeight)
// #define keyboardRelativeBottomMargin (86 / KeyboardDesignHeight)

class KeyboardAbstractIC : public QFrame
{
    Q_OBJECT

public:
    explicit KeyboardAbstractIC(QPlatformInputContext *ctx, QWidget *parent = Q_NULLPTR);
    virtual ~KeyboardAbstractIC();

    static QSize keyboardScaleSize(float currentWidth);
    virtual void scale(float currentWidth);
    virtual void sendKeyClick(int key, const QString &text = "", int modifiers = 0);

    enum FunctionKeyType : int {Alphabet, Symbol_1, Symbol_2, HideKeyboard = 0xf};
signals:
    void Sig_FunctionKeyEvent(FunctionKeyType type);

protected:
    void keyClicked(QPushButton *b, Qt::Key k=Qt::Key_Escape, QString type="", QString func="");

private:
    QPlatformInputContext *m_ctx; 
    QLoggingCategory m_logCategory;
};

Q_DECLARE_METATYPE(KeyboardAbstractIC::FunctionKeyType)
