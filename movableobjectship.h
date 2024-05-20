#ifndef MOVABLEOBJECTSHIP_H
#define MOVABLEOBJECTSHIP_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include "dump.h"
#include "fieldview.h"
#include "movableobjectadapter.hpp"

class MovableObjectShip : public MovableObjectAdapter<Ship> {
protected:
    QGraphicsItem* construct_object() override {
        double height = parent->height() - FieldView::PEN_GRID.width();
        double width = parent->width() - FieldView::PEN_GRID.width();
        double tile_size_height = height / GAME_SIZE;
        double tile_size_width = width / GAME_SIZE;

        double beg_x = FieldView::PADDING_PERCENT * tile_size_width;
        double end_x = (((this->object.is_horizontal ? this->object.length : 1)) - FieldView::PADDING_PERCENT) * tile_size_width;
        double beg_y = FieldView::PADDING_PERCENT * tile_size_height;
        double end_y = (((this->object.is_horizontal ? 1 : this->object.length)) - FieldView::PADDING_PERCENT) * tile_size_height;

        auto res = new QGraphicsRectItem(beg_x, beg_y, end_x, end_y);
        res->setPen(FieldView::PEN_SHIP);
        res->setBrush(FieldView::BRUSH_SHIP);

        return res;
    }

public:
    MovableObjectShip(QGraphicsView* parent, Ship object, QPointF offset) : MovableObjectAdapter<Ship>(parent, object, offset) {
        init();
    };
};

#endif // MOVABLEOBJECTSHIP_H
