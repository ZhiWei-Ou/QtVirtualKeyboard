/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file platformICPlug.hpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-04 21:21:54

 * @brief 
 */
#pragma once

#pragma once

#include <qpa/qplatforminputcontextplugin_p.h>

QT_BEGIN_NAMESPACE

class  PlatformInputContextPlugin: public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "qtkeyboard.json")

public:
    QStringList keys() const;
    QPlatformInputContext *create(const QString&, const QStringList&) override;
};

QT_END_NAMESPACE
