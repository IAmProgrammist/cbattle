#include <widgets/fieldstyle.h>

FieldStyle::FieldStyle(double padding_percent,
                       QPen pen_grid,
                       QPen pen_ship,
                       QBrush brush_ship) : padding_percent(padding_percent), pen_grid(pen_grid), pen_ship(pen_ship), brush_ship(brush_ship) {}

double FieldStyle::get_padding_percent() {
    return this->padding_percent;
}
QPen FieldStyle::get_pen_grid() {
    return this->pen_grid;
}
QPen FieldStyle::get_pen_ship() {
    return this->pen_ship;
}
QBrush FieldStyle::get_brush_ship() {
    return this->brush_ship;
}
