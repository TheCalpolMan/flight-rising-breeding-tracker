// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef LINEAGEEDGE_H
#define LINEAGEEDGE_H

#include <QGraphicsItem>

class LineageNode;

class LineageEdge : public QGraphicsItem
{
public:
    LineageEdge(LineageNode *sourceNode, LineageNode *destNode, int thickness);

    LineageNode *sourceNode() const;
    LineageNode *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    LineageNode *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;

    qreal arrowSize;
    qreal thickness;
};

#endif // LINEAGEEDGE_H
