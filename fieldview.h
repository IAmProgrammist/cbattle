#ifndef FIELD_VIEW_H
#define FIELD_VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "dump.h"
#include "movableobjectadapter.hpp"

class MovableObjectShip;

class FieldView : public QGraphicsScene
{
    Q_OBJECT
public:
    static const double PADDING_PERCENT;
    static const QPen PEN_GRID;
    static const QPen PEN_SHIP;
    static const QBrush BRUSH_SHIP;
    Field field;

    FieldView(QGraphicsView *parent = nullptr) : QGraphicsScene(parent) {}

    void setField(Field field);
    Field getField();

    void redraw();

protected:
    std::pair<QPointF, QPointF> getShipScenePos(Ship& ship);
    int getCollidedShipIndex(QPointF pos);
    QPoint getCellCoordinate(QPointF scene_pos);
};

#include "movableobjectship.h"

#endif // FIELD_VIEW_H
