#pragma once

#include <QGraphicsItem>
#include <QGraphicsScene>

#include <models/ship.h>
#include <utils/moveableobjectadapter.hpp>

class MoveableObjectShip : public MoveableObjectAdapter<Ship> {
protected:
  QGraphicsItem *construct_object();

public:
  MoveableObjectShip(QGraphicsView *parent, Ship object, QPointF offset,
                     FieldStyle *style);
};
