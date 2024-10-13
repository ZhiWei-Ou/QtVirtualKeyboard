/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file platformICPlug.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-04 21:22:33

 * @brief 
 */
#include "platformICPlug.h"
#include "platformIC.h"

static const char pluginName[] = "QtKeyboard";

QStringList PlatformInputContextPlugin::keys() const
{
    return QStringList(QLatin1String(pluginName));
}

QPlatformInputContext *PlatformInputContextPlugin::create(const QString &key, const QStringList &paramList)
{
    Q_UNUSED(paramList);

#if defined(Q_OS_WIN)
    // QTBUG-93042
    ImmDisableIME(0);
#endif

    return new PlatformInputContext(this);
}

