#pragma once

#include <QGraphicsItem>
#include <QGraphicsView>

#include <widgets/fieldstyle.h>

template <typename T> class MoveableObjectAdapter {
protected:
  QGraphicsView *parent;
  T object;
  QGraphicsItem *graph_object;
  QPointF offset;
  FieldStyle *style;

  virtual QGraphicsItem *construct_object() = 0;

public:
  void onUpdateScenePos(QPointF &pos) {
    graph_object->setPos(
        QPointF(pos.x() + this->offset.x(), pos.y() + this->offset.y()));
  }

  MoveableObjectAdapter(QGraphicsView *parent, T object, QPointF offset,
                        FieldStyle *style)
      : parent(parent), object(object), offset(offset), style(style) {}

  virtual ~MoveableObjectAdapter() {
    this->parent->scene()->removeItem(graph_object);
    delete graph_object;
  }

  void init() {
    this->graph_object = construct_object();

    this->parent->scene()->addItem(graph_object);
  }

  T getObject() { return object; }

  QPointF getOffset() { return offset; }
};
