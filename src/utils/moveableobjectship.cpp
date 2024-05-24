#include <utils/moveableobjectship.h>

#include <widgets/fieldwidget.h>

MoveableObjectShip::MoveableObjectShip(QGraphicsView* parent, Ship object, QPointF offset, FieldStyle style) : MoveableObjectAdapter<Ship>(parent, object, offset, style) {
    init();
}

QGraphicsItem* MoveableObjectShip::construct_object() {
    double height = parent->height() - style.get_pen_grid().width();
    double width = parent->width() - style.get_pen_grid().width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    double beg_x = style.get_padding_percent() * tile_size_width;
    double end_x = (((this->object.is_horizontal ? this->object.length : 1)) - style.get_padding_percent()) * tile_size_width;
    double beg_y = style.get_padding_percent() * tile_size_height;
    double end_y = (((this->object.is_horizontal ? 1 : this->object.length)) - style.get_padding_percent()) * tile_size_height;

    auto res = new QGraphicsRectItem(beg_x, beg_y, end_x, end_y);
    res->setPen(style.get_pen_ship());
    res->setBrush(style.get_brush_ship());

    return res;
}
