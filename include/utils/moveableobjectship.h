#ifndef MOVABLEOBJECTSHIP_H
#define MOVABLEOBJECTSHIP_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <utils/moveableobjectadapter.hpp>
#include <models/ship.h>

class MoveableObjectShip : public MoveableObjectAdapter<Ship> {
protected:
    QGraphicsItem* construct_object();

public:
    MoveableObjectShip(QGraphicsView* parent, Ship object, QPointF offset);
};

#endif // MOVABLEOBJECTSHIP_H
