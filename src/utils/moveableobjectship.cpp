#include <utils/moveableobjectship.h>

#include <widgets/fieldwidget.h>

MoveableObjectShip::MoveableObjectShip(QGraphicsView* parent, Ship object, QPointF offset) : MoveableObjectAdapter<Ship>(parent, object, offset) {
    init();
}

QGraphicsItem* MoveableObjectShip::construct_object() {
    double height = parent->height() - FieldWidget::PEN_GRID.width();
    double width = parent->width() - FieldWidget::PEN_GRID.width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    double beg_x = FieldWidget::PADDING_PERCENT * tile_size_width;
    double end_x = (((this->object.is_horizontal ? this->object.length : 1)) - FieldWidget::PADDING_PERCENT) * tile_size_width;
    double beg_y = FieldWidget::PADDING_PERCENT * tile_size_height;
    double end_y = (((this->object.is_horizontal ? 1 : this->object.length)) - FieldWidget::PADDING_PERCENT) * tile_size_height;

    auto res = new QGraphicsRectItem(beg_x, beg_y, end_x, end_y);
    res->setPen(FieldWidget::PEN_SHIP);
    res->setBrush(FieldWidget::BRUSH_SHIP);

    return res;
}
