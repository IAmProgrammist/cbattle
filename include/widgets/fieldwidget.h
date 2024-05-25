#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include <models/ship.h>
#include <models/field.h>
#include <widgets/fieldstyle.h>

class FieldWidget : public QGraphicsScene {
    Q_OBJECT
public:
    Field field;

    FieldWidget(QGraphicsView *parent = nullptr, FieldStyle* style = &FieldStyle::STYLE_PLAY_SELF) : QGraphicsScene(parent), style(style) {}

    void setField(Field field);
    Field getField();

    void redraw();

protected:
    FieldStyle* style;
    std::pair<QPointF, QPointF> getShipScenePos(Ship& ship);
    int getCollidedShipIndex(QPointF pos);
    QPoint getCellCoordinate(QPointF scene_pos);
};

