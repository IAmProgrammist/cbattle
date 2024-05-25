#include <widgets/fieldwidget.h>

#include <QMouseEvent>
#include <QPixmap>

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
    double height = parent->height() - style->get_pen_grid().width();
    double width = parent->width() - style->get_pen_grid().width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    for (int i = 0; i < GAME_SIZE + 1; i++) {
        this->addLine(0, i * tile_size_height, parent->width(), i * tile_size_height, style->get_pen_grid());
        this->addLine(i * tile_size_width, 0, i * tile_size_width, parent->height(), style->get_pen_grid());
    }

    for (auto & ship : field.ships) {
        auto ship_data = getShipScenePos(ship);

        this->addRect(ship_data.first.x(), ship_data.first.y(),
                      ship_data.second.x() - ship_data.first.x(),
                      ship_data.second.y() - ship_data.first.y(), style->get_pen_ship(), style->get_brush_ship());
    }


    for (int y = 0; y < GAME_SIZE; y++) {
        for (int x = 0; x < GAME_SIZE; x++) {
            if (field.field[y][x] == FieldElement::EMPTY_CHECKED) {
                auto p = new QGraphicsPixmapItem(style->get_cross_img().scaled(tile_size_width * (1 - style->get_padding_percent()),
                                                                               tile_size_height * (1 - style->get_padding_percent())));
                p->setPos((x + style->get_padding_percent()) * tile_size_width, (y + style->get_padding_percent()) * tile_size_height);
                this->addItem(p);
            } else if (field.field[y][x] == FieldElement::EXPOLSION_CHECKED) {
                auto p = new QGraphicsPixmapItem(style->get_exposion_img().scaled(tile_size_width * (1 - style->get_padding_percent()),
                                                                               tile_size_height * (1 - style->get_padding_percent())));
                p->setPos((x + style->get_padding_percent()) * tile_size_width, (y + style->get_padding_percent()) * tile_size_height);
                this->addItem(p);
            }
        }
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
    double height = parent->height() - style->get_pen_grid().width();
    double width = parent->width() - style->get_pen_grid().width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    double beg_x = (ship.x + style->get_padding_percent()) * tile_size_width;
    double end_x = ((ship.x + (ship.is_horizontal ? ship.length : 1)) - style->get_padding_percent()) * tile_size_width;
    double beg_y = (ship.y + style->get_padding_percent()) * tile_size_height;
    double end_y = ((ship.y + (ship.is_horizontal ? 1 : ship.length)) - style->get_padding_percent()) * tile_size_height;

    return {QPointF(beg_x, beg_y), QPointF(end_x, end_y)};
}

QPoint FieldWidget::getCellCoordinate(QPointF scene_pos) {
    auto parent = reinterpret_cast<QGraphicsView*>(this->parent());
    double height = parent->height() - style->get_pen_grid().width();
    double width = parent->width() - style->get_pen_grid().width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;

    int x = scene_pos.x() / tile_size_width;
    int y = scene_pos.y() / tile_size_height;

    return {x, y};
}
