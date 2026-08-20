// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "lineageedge.h"
#include "lineagenode.h"

#include <QPainter>
#include <QtMath>

LineageEdge::LineageEdge(LineageNode *sourceNode, LineageNode *destNode, int thickness) :
    source(sourceNode),
    dest(destNode),
    thickness(thickness)
{
    arrowSize = 2 + thickness * 0.75;

    setAcceptedMouseButtons(Qt::NoButton);
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

LineageNode *LineageEdge::sourceNode() const
{
    return source;
}

LineageNode *LineageEdge::destNode() const
{
    return dest;
}

void LineageEdge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(source->getRadius() + dest->getRadius())) {
        QPointF sourceEdgeOffset((line.dx() * source->getRadius()) / length, (line.dy() * source->getRadius()) / length);
        QPointF destEdgeOffset((line.dx() * dest->getRadius()) / length, (line.dy() * dest->getRadius()) / length);

        sourcePoint = line.p1() + sourceEdgeOffset;
        destPoint = line.p2() - destEdgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF LineageEdge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void LineageEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrow
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI / 3) * arrowSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
}
