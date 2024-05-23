#pragma once

#include <QGraphicsView>
#include <QGraphicsItem>

template<typename T>
class MoveableObjectAdapter {
protected:
    QGraphicsView* parent;
    T object;
    QGraphicsItem* graph_object;
    QPointF offset;

    virtual ~MoveableObjectAdapter() {
        this->parent->scene()->removeItem(graph_object);
        delete graph_object;
    }

    virtual QGraphicsItem* construct_object() = 0;

public:
    void on_update_scene_pos(QPointF& pos) {
        graph_object->setPos(QPointF(pos.x() + this->offset.x(), pos.y() + this->offset.y()));
    }

    MoveableObjectAdapter(QGraphicsView* parent, T object, QPointF offset) : parent(parent), object(object), offset(offset) {}

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

