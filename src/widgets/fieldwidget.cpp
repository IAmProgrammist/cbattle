#include <widgets/fieldwidget.h>

#include <QMouseEvent>

const double FieldWidget::PADDING_PERCENT = 0;
const QPen FieldWidget::PEN_GRID = QPen(Qt::gray, 3);
const QPen FieldWidget::PEN_SHIP = QPen(Qt::blue, 3);
const QBrush FieldWidget::BRUSH_SHIP = QColor(0, 0, 255, 30);

void FieldWidget::setField(Field field) {
    this->field = field;

    redraw();
}

Field FieldWidget::getField() {
    return this->field;
}

void FieldWidget::redraw() {
    this->clear();
    auto parent = reinterpret_cast<QGraphicsView*>(this->parent());
    double height = parent->height() - PEN_GRID.width();
    double width = parent->width() - PEN_GRID.width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    for (int i = 0; i < GAME_SIZE + 1; i++) {
        this->addLine(0, i * tile_size_height, parent->width(), i * tile_size_height, PEN_GRID);
        this->addLine(i * tile_size_width, 0, i * tile_size_width, parent->height(), PEN_GRID);
    }

    for (auto & ship : field.ships) {
        auto ship_data = getShipScenePos(ship);

        this->addRect(ship_data.first.x(), ship_data.first.y(),
                      ship_data.second.x() - ship_data.first.x(),
                      ship_data.second.y() - ship_data.first.y(), PEN_SHIP, BRUSH_SHIP);
    }
}

int FieldWidget::getCollidedShipIndex(QPointF pos) {
    for (int i = 0; i < this->field.ships.size(); i++) {
        auto ship_data = getShipScenePos(this->field.ships[i]);

        if (pos.x() >= ship_data.first.x() && pos.x() <= ship_data.second.x() &&
            pos.y() >= ship_data.first.y() && pos.y() <= ship_data.second.y())
            return i;
    }

    return -1;
}

std::pair<QPointF, QPointF> FieldWidget::getShipScenePos(Ship& ship) {
    auto parent = reinterpret_cast<QGraphicsView*>(this->parent());
    double height = parent->height() - PEN_GRID.width();
    double width = parent->width() - PEN_GRID.width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    double beg_x = (ship.x + PADDING_PERCENT) * tile_size_width;
    double end_x = ((ship.x + (ship.is_horizontal ? ship.length : 1)) - PADDING_PERCENT) * tile_size_width;
    double beg_y = (ship.y + PADDING_PERCENT) * tile_size_height;
    double end_y = ((ship.y + (ship.is_horizontal ? 1 : ship.length)) - PADDING_PERCENT) * tile_size_height;

    return {QPointF(beg_x, beg_y), QPointF(end_x, end_y)};
}

QPoint FieldWidget::getCellCoordinate(QPointF scene_pos) {
    auto parent = reinterpret_cast<QGraphicsView*>(this->parent());
    double height = parent->height() - PEN_GRID.width();
    double width = parent->width() - PEN_GRID.width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    int x = scene_pos.x() / tile_size_width;
    int y = scene_pos.y() / tile_size_height;

    return {x, y};
}
