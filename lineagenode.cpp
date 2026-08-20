// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "lineageedge.h"
#include "lineagenode.h"
#include "lineagegraphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

LineageNode::LineageNode(LineageGraphWidget *graphWidget, const std::string &label, const Colour &colour) :
    graph(graphWidget),
    label(label)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    if (colour.toHsl().lightness < 0.5)
    {
        textColour = QColor(Qt::white);

        innerColour = QColor(colour.hexCode.c_str()).lighter(120);
        outerColour = QColor(colour.hexCode.c_str());
    }
    else
    {
        textColour = QColor(Qt::black);

        innerColour = QColor(colour.hexCode.c_str());
        outerColour = QColor(colour.hexCode.c_str()).lighter(120);
    }
}

void LineageNode::addEdge(LineageEdge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<LineageEdge *> LineageNode::edges() const
{
    return edgeList;
}

void LineageNode::calculateForces()
{
    if (!scene() || scene()->mouseGrabberItem() == this) {
        newPos = pos();
        return;
    }

    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        LineageNode *node = qgraphicsitem_cast<LineageNode *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = 2.0 * (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx * std::pow(node->radius, 1.5) * 8.0) / l;
            yvel += (dy * std::pow(node->radius, 1.5) * 8.0) / l;
        }
    }

    // Now subtract all forces pulling items together
    double weight = (edgeList.size() + 1) * 10;
    for (const LineageEdge *edge : std::as_const(edgeList)) {
        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }

    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    newPos = pos() + QPointF(xvel * forceCoefficient, yvel * forceCoefficient);
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + radius), sceneRect.right() - radius));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + radius), sceneRect.bottom() - radius));
}

bool LineageNode::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF LineageNode::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -radius - adjust, -radius - adjust, radius * 2 + adjust + 3, radius * 2 + adjust + 3);
}

QPainterPath LineageNode::shape() const
{
    QPainterPath path;
    path.addEllipse(-radius, -radius, radius * 2, radius * 2);
    return path;
}

void LineageNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-radius + 3, -radius + 3, radius * 2, radius * 2);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, innerColour.lighter(120));
        gradient.setColorAt(0, outerColour.lighter(120));
    } else {
        gradient.setColorAt(0, innerColour);
        gradient.setColorAt(1, outerColour);
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    QRectF textRect(0, 0, 200, 200);
    QString message(label.c_str());

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(6);
    painter->setFont(font);
    painter->setPen(textColour);

    auto translation = painter->boundingRect(textRect, message);
    radius = std::ceil(std::fmax(translation.height(), translation.width()) / 2.0) + 2.0;
    painter->drawText(textRect.translated(-translation.width() / 2, -translation.height() / 2), message);
}

int LineageNode::getRadius() const
{
    return radius;
}

QVariant LineageNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (LineageEdge *edge : std::as_const(edgeList))
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void LineageNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void LineageNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
