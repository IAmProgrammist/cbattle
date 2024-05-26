#pragma once

#include <QPen>
#include <QBrush>

class FieldStyle {
    double padding_percent;
    QPen pen_grid;
    QPen pen_ship;
    QBrush brush_ship;
    QPixmap* cross_img;
    QPixmap* explosion_img;

    FieldStyle(std::optional<double> padding_percent = std::nullopt,
               std::optional<QPen> pen_grid = std::nullopt,
               std::optional<QPen> pen_ship = std::nullopt,
               std::optional<QBrush> brush_ship = std::nullopt,
               std::optional<std::string> cross = std::nullopt,
               std::optional<std::string> exposion = std::nullopt);

    FieldStyle(int _);

    ~FieldStyle();

public:
    static double DEFAULT_PADDING_PERCENT;
    static QPen DEFAULT_PEN_GRID;
    static QPen DEFAULT_PEN_SHIP;
    static QBrush DEFAULT_BRUSH_SHIP;
    static std::string DEFAULT_CROSS;
    static std::string DEFAULT_EXPLOSION;

    static FieldStyle STYLE_EDIT;
    static FieldStyle STYLE_PLAY_SELF;
    static FieldStyle STYLE_PLAY_ENEMY;

    static void initStyles();

    double getPaddingPercent();
    QPen getPenGrid();
    QPen getPenShip();
    QBrush getBrushShip();
    QPixmap& getCrossImg();
    QPixmap& getExplosionImg();
};
