﻿/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "diagramitem.h"
#include "diagramtextitem.h"

#include <QGraphicsScene>
#include <CREATECMD.H>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class CCommand;

//! [0]
class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    //实体类型
    enum EntityType {
        GI_BASE = 1,
        GI_SHAPE = 2,
        GI_RECT = 3,
        GI_ELIPSE = 4,
        GI_POLYGON = 5,
        GI_LINE = 6,
        GI_PIXEL = 7,
        GI_TEXT = 8
    };

    explicit DiagramScene(QMenu *itemMenu, QObject *parent = 0);
    QFont font() const { return myFont; }
    QColor textColor() const { return myTextColor; }
    QColor itemColor() const { return myItemColor; }
    QColor lineColor() const { return myLineColor; }
    qreal penWidth() const { return myPenWidth; }
    Qt::PenStyle penStyle() const{ return myPenStyle; }

    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(const QFont &font);
    void setPenStyle(Qt::PenStyle ps);
    void setPenWidth(qreal wid);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);
    void editorLostFocus(DiagramTextItem *item);

signals:
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent) override;

private:
    bool isItemChange(int type);

    DiagramItem::DiagramType myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    DiagramTextItem *textItem;
    QColor myTextColor;
    QColor myItemColor;

    QColor myLineColor;
    Qt::PenStyle myPenStyle;
    qreal myPenWidth;

    CCommand* m_pCmd;

public:
    void Save(QDataStream& out);
    void Read(QDataStream& in);
    void SaveLine(QDataStream& out, QGraphicsLineItem* lineItem);
    void ReadLine(QDataStream& in, QGraphicsLineItem* lineItem);

public:
    void selectEntity();
    void ResetSelectStatus();
    void drawLine();
    void drawCircle();
    void drawArc();
    void drawRect();
    void drawEllipse();
    void drawPolygon();
    //修改
    void moveEntity();
    void rotateEntity();
    void symetryEntity();
    //视窗
    void zoomWindow();
    void zoomPan();

    /*******尺寸标注******/
    void horizontalDimension();
    void verticalDimension();

//private:
//    CREATEDIMENSION* createdDimensionCommand;
};
//! [0]

#endif // DIAGRAMSCENE_H
