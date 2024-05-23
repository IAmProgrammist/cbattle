#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include <models/ship.h>
#include <models/field.h>

class FieldWidget : public QGraphicsScene {
    Q_OBJECT
public:
    static const double PADDING_PERCENT;
    static const QPen PEN_GRID;
    static const QPen PEN_SHIP;
    static const QBrush BRUSH_SHIP;
    Field field;

    FieldWidget(QGraphicsView *parent = nullptr) : QGraphicsScene(parent) {}

    void setField(Field field);
    Field getField();

    void redraw();

protected:
    std::pair<QPointF, QPointF> getShipScenePos(Ship& ship);
    int getCollidedShipIndex(QPointF pos);
    QPoint getCellCoordinate(QPointF scene_pos);
};

#endif // FIELDVIEW_H
