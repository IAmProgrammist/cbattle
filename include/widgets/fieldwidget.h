#pragma once

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QPen>

#include <models/field.h>
#include <models/ship.h>
#include <widgets/fieldstyle.h>

class FieldWidget : public QGraphicsScene {
  Q_OBJECT
public:
  Field field;

  FieldWidget(QGraphicsView *parent = nullptr,
              FieldStyle *style = &FieldStyle::STYLE_PLAY_SELF)
      : QGraphicsScene(parent), style(style) {}

  void setField(Field field);
  Field getField();

  void redraw();

protected:
  FieldStyle *style;
  std::pair<QPointF, QPointF> getShipScenePos(Ship &ship);
  int getCollidedShipIndex(QPointF pos);
  QPoint getCellCoordinate(QPointF scene_pos);
};
