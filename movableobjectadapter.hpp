#ifndef MOVABLEOBJECTADAPTER_H
#define MOVABLEOBJECTADAPTER_H

#include <QGraphicsView>
#include <QGraphicsItem>

#include "dump.h"

template<typename T>
class MovableObjectAdapter {
protected:
    QGraphicsView* parent;
    T object;
    QGraphicsItem* graph_object;
    QPointF offset;

    virtual ~MovableObjectAdapter() {
        this->parent->scene()->removeItem(graph_object);
        delete graph_object;
    }

    virtual QGraphicsItem* construct_object() = 0;

public:
    void on_update_scene_pos(QPointF& pos) {
        graph_object->setPos(QPointF(pos.x() + this->offset.x(), pos.y() + this->offset.y()));
    }

    MovableObjectAdapter(QGraphicsView* parent, Ship object, QPointF offset) : parent(parent), object(object), offset(offset) {}

    void init() {
        this->graph_object = construct_object();

        this->parent->scene()->addItem(graph_object);
    }

    T getObject() {
        return object;
    }

    QPointF getOffset() {
        return offset;
    }
};

#endif // MOVABLEOBJECTADAPTER_H
