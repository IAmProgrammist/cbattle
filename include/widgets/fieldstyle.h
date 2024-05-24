#pragma once

#include <QPen>
#include <QBrush>

class FieldStyle {
    const double padding_percent = 0;
    const QPen pen_grid = QPen(Qt::gray, 3);
    const QPen pen_ship = QPen(Qt::blue, 3);
    const QBrush brush_ship = QColor(0, 0, 255, 30);

public:
    FieldStyle(double padding_percent = 0,
               QPen pen_grid = QPen(Qt::gray, 3),
               QPen pen_ship = QPen(Qt::blue, 3),
               QBrush brush_ship = QColor(0, 0, 255, 30));

    double get_padding_percent();
    QPen get_pen_grid();
    QPen get_pen_ship();
    QBrush get_brush_ship();
};
