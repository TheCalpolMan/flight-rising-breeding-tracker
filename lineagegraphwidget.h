// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef LINEAGEGRAPHWIDGET_H
#define LINEAGEGRAPHWIDGET_H

#include <QBasicTimer>
#include <QGraphicsView>

#include "dragon.h"

class LineageNode;

class LineageGraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    LineageGraphWidget(QWidget *parent = nullptr);

    void itemMoved();

    void setGraph(const std::vector<std::shared_ptr<Dragon>> dragons);

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    QBasicTimer timer;
};

#endif // LINEAGEGRAPHWIDGET_H
