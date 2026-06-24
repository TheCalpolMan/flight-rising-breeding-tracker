#ifndef CLICKABLEQGRAPHICSVIEW_H
#define CLICKABLEQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>

class ClickableQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    ClickableQGraphicsView(QWidget*& parent);
signals:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CLICKABLEQGRAPHICSVIEW_H
