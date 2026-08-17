// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef LINEAGENODE_H
#define LINEAGENODE_H

#include <QList>
#include <QGraphicsItem>

#include "colour.h"

class LineageEdge;
class LineageGraphWidget;

class LineageNode : public QGraphicsItem
{
public:
    LineageNode(LineageGraphWidget *graphWidget, std::string label, Colour colour);

    void addEdge(LineageEdge *edge);
    QList<LineageEdge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int getRadius() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int radius = 10;
    static constexpr float forceCoefficient = 0.2;

    QColor textColour;
    QColor innerColour;
    QColor outerColour;

    QList<LineageEdge *> edgeList;
    QPointF newPos;
    LineageGraphWidget *graph;

    std::string label;
};

#endif // LINEAGENODE_H
