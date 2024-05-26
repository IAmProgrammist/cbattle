#pragma once

#include <utils/moveableobjectship.h>
#include <widgets/fieldwidget.h>

class FieldWidgetEdit : public FieldWidget {
  Q_OBJECT

  MoveableObjectShip *moveable_object = nullptr;

public:
  FieldWidgetEdit(QGraphicsView *parent = nullptr,
                  FieldStyle *style = &FieldStyle::STYLE_EDIT);

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
