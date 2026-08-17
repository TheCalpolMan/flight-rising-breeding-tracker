// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "lineagegraphwidget.h"

#include <cmath>
#include <QKeyEvent>
#include <QRandomGenerator>

#include "lineageedge.h"
#include "lineagenode.h"
#include "vectorhelpers.h"

LineageGraphWidget::LineageGraphWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1.2), qreal(1.2));
    setMinimumSize(400, 400);
}

void LineageGraphWidget::itemMoved()
{
    using namespace std::chrono_literals;

    if (!timer.isActive())
        timer.start(1000ms / 25, this);
}

void LineageGraphWidget::setGraph(const std::vector<std::shared_ptr<Dragon> > dragons)
{
    scene()->clear();

    std::vector<LineageNode *> nodes = decltype(nodes)();

    int radius = 75;

    for (int i = 0; i < dragons.size(); i++)
    {
        const auto dragon = dragons.at(i);
        float theta = 3.1415 * 2.0 / dragons.size() * i;

        float xCoord = radius * std::cos(theta);
        float yCoord = radius * std::sin(theta);

        nodes.push_back(new LineageNode(this, dragon->name, dragon->primaryColour));
        nodes.back()->setPos(xCoord, yCoord);
    }

    for (const auto node : nodes)
    {
        scene()->addItem(node);
    }

    for (int i = 0; i < dragons.size(); i++)
    {
        const auto dragon = dragons.at(i);

        for (const auto& relation : dragon->lineage)
        {
            if (relation.second.expired())
            {
                continue;
            }

            scene()->addItem(new LineageEdge(nodes.at(i), nodes.at(VectorHelpers::getIndex(dragons, relation.second.lock())), 5 - relation.first));
        }
    }
}

void LineageGraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void LineageGraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<LineageNode *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (LineageNode *node = qgraphicsitem_cast<LineageNode *>(item))
            nodes << node;
    }

    for (LineageNode *node : std::as_const(nodes))
        node->calculateForces();

    bool itemsMoved = false;
    for (LineageNode *node : std::as_const(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved)
        timer.stop();
}

#if QT_CONFIG(wheelevent)
void LineageGraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., event->angleDelta().y() / 240.0));
}
#endif

void LineageGraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

void LineageGraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void LineageGraphWidget::shuffle()
{
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<LineageNode *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void LineageGraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void LineageGraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
