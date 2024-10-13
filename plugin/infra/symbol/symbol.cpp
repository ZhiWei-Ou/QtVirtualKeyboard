/*
 * © 2024 [ZhiWei-Ou]. All rights reserved.
 * @file symbol.cpp
 * @author Ouzw
 * @mail ouzw.mail@gmail.com
 * @date 2024-10-13 20:27:32

 * @brief 
 */
#include "symbol.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QLayout>
#include <QPushButton>
#include <QFile>
#include <QtCore/qglobal.h>
#include <QtCore/qloggingcategory.h>
#include <QtMath>
#include <QList>

#include <QDebug>
#include <QtCore/qnamespace.h>
#include <QtWidgets/qpushbutton.h>

Keyboard_Symbol::Keyboard_Symbol(QPlatformInputContext *ctx, QWidget *parent)
    : KeyboardAbstractIC(ctx, parent), rect(Q_NULLPTR)
{
    QFile file(":assets/profiles/symbol.json");
    if (!file.open(QIODevice::ReadOnly)) {
        QString error = QString("%1 %2").arg(__PRETTY_FUNCTION__).arg(file.errorString());
        throw std::runtime_error(error.toStdString());
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) {
        QString error = QString("%1 %2").arg(__PRETTY_FUNCTION__).arg("failed to load profile");
        throw std::runtime_error(error.toStdString());
    }

    this->setObjectName(doc["name"].toString());
    this->setStyleSheet(QString(R"(
         QFrame#%1 {
             background-color: %2;
         }
         QPushButton {
             %3
         }
         QPushButton#space_misc {
             color: #868482;
             font-size: 15px;
         }
         QPushButton:pressed {
             %4
         }
         QPushButton:hover {
             %5
         }
    )")
    .arg( objectName() )
    .arg( doc["bgColor"].toString() )
    .arg( doc["btnStyle"]["normal"].toString() )
    .arg( doc["btnStyle"]["pressed"].toString() )
    .arg( doc["btnStyle"]["hover"].toString() )
    );


    QGridLayout *globLayout = new QGridLayout(this);

    rect = new QFrame(this);
    // rect->setStyleSheet("border: 1px solid white;");
    globLayout->addWidget(rect);

    QVBoxLayout *vlayout = new QVBoxLayout(rect);
    vlayout->setSpacing(5);
    vlayout->setContentsMargins(0, 0, 0, 0);

    QJsonArray layoutArray = doc["layout"].toArray();
    for (auto item : layoutArray) {
        QJsonObject jo = item.toObject();
        QFrame *f = new QFrame(rect);
        QHBoxLayout *hl = new QHBoxLayout(f);
        hl->setSpacing(jo["spacing"].toInt());
        hl->setContentsMargins(
                jo["leftM"].toInt(),
                jo["topM"].toInt(),
                jo["rightM"].toInt(),
                jo["bottomM"].toInt());

        QJsonArray keysArray = jo["keys"].toArray();
        for (auto key : keysArray) {
            // {"enum":81,"key":"q","weight":1}
            auto o = key.toObject();
            
            QString type = o["type"].toString();
            QString k = o["key"].toString();
            int w = o["weight"].toInt();
            Qt::Key kenum(static_cast<Qt::Key>(o["enum"].toInt()));

            if (type == "holder") {
                QFrame *spacerHolder = new QFrame(f);
                hl->addWidget(spacerHolder, w);
                continue;
            }

            QPushButton *b = new QPushButton(f);
            b->setObjectName(k+"_"+type);
            b->setProperty("func", k);
            b->setProperty("key", kenum);
            b->setProperty("type", type);
            b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            if (!o["icon"].toString().isEmpty()) {
                b->setIcon(QIcon(o["icon"].toString()));
            } else if (!o["alternative"].toString().isEmpty()) {
                b->setText(o["alternative"].toString());
            } else {
                b->setText(QKeySequence(kenum).toString());
            }

            if (!o["style"].isNull()) {
                auto style = o["style"].toObject();
                QString normal = style["normal"].toString();
                QString pressed = style["pressed"].toString();
                b->setStyleSheet(QString(R"(
                    QPushButton#%1 {
                        %2
                    }
                    QPushButton#%1:pressed {
                        %3
                    }
                    QPushButton#%1:hover {
                        %4
                    }
                )")
                .arg(k+"_"+type)
                .arg(normal)
                .arg(pressed)
                );
            }

            connect(b, &QPushButton::clicked, this, &Keyboard_Symbol::keyClicked);
            hl->addWidget(b, w);
        }
        f->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        vlayout->addWidget(f);
    }
        
    rect->setLayout(vlayout);
    // rect->adjustSize();

    // this->show();
}

Keyboard_Symbol::~Keyboard_Symbol()
{
}


void Keyboard_Symbol::scale(float currentWidth)
{
    KeyboardAbstractIC::scale(currentWidth);

    auto x = qRound( static_cast<double>( keyboardRelativeLeftMargin * width() ) );
    auto y = qRound( static_cast<double>( keyboardRelativeTopMargin * height() ) );

    rect->move(x, y);

}

void Keyboard_Symbol::keyClicked()
{
    QPushButton *b = static_cast<QPushButton*>(sender());
    QString func = b->property("func").toString();
    QString type = b->property("type").toString();
    Qt::Key k = static_cast<Qt::Key>(b->property("key").toInt());

    if (type == "function") {
    } else if (type == "misc") {
    }

    return KeyboardAbstractIC::keyClicked(b, k, type, func);
}

