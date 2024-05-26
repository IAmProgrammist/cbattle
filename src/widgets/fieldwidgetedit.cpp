#include <widgets/fieldwidgetedit.h>

FieldWidgetEdit::FieldWidgetEdit(QGraphicsView *parent, FieldStyle *style)
    : FieldWidget(parent, style) {}

void FieldWidgetEdit::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (moveable_object != nullptr) {
    QPointF newPos = event->scenePos();
    moveable_object->onUpdateScenePos(newPos);
  }
}

void FieldWidgetEdit::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QPointF newPos = event->scenePos();
  if (event->button() == Qt::LeftButton) {
    auto index = getCollidedShipIndex(event->scenePos());
    if (index == -1)
      return;

    Ship ship = this->field.ships[index];
    auto ship_data = getShipScenePos(ship);
    this->field.ships.erase(this->field.ships.begin() + index);
    this->redraw();

    if (moveable_object != nullptr)
      delete moveable_object;
    this->moveable_object = new MoveableObjectShip(
        reinterpret_cast<QGraphicsView *>(this->parent()), ship,
        QPointF(ship_data.first.x() - event->scenePos().x(),
                ship_data.first.y() - event->scenePos().y()),
        style);
    this->moveable_object->onUpdateScenePos(newPos);
  } else if (event->button() == Qt::RightButton && this->moveable_object) {
    auto ship = this->moveable_object->getObject();
    ship.is_horizontal = !ship.is_horizontal;
    auto offset = this->moveable_object->getOffset();

    delete this->moveable_object;
    this->moveable_object = new MoveableObjectShip(
        reinterpret_cast<QGraphicsView *>(this->parent()), ship, offset, style);
    this->moveable_object->onUpdateScenePos(newPos);
  }
}

void FieldWidgetEdit::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
  if (event->button() == Qt::LeftButton && moveable_object) {
    auto parent = reinterpret_cast<QGraphicsView *>(this->parent());
    double height = parent->height() - style->getPenGrid().width();
    double width = parent->width() - style->getPenGrid().width();
    double tile_size_height = height / GAME_SIZE;
    double tile_size_width = width / GAME_SIZE;
    auto ship = moveable_object->getObject();
    auto cell = getCellCoordinate(
        {event->scenePos().x() + moveable_object->getOffset().x() +
             0.5 * tile_size_width, // moveable_object->getOffset().x(),
         event->scenePos().y() + moveable_object->getOffset().y() +
             0.5 * tile_size_height}); //- moveable_object->getOffset().y()});
    ship.x = cell.x();
    ship.y = cell.y();

    if (ship.x < 0)
      ship.x = 0;
    if (ship.y < 0)
      ship.y = 0;
    if (ship.x + (ship.is_horizontal ? ship.length : 1) > GAME_SIZE)
      ship.x = GAME_SIZE - (ship.is_horizontal ? ship.length : 1);
    if (ship.y + (!ship.is_horizontal ? ship.length : 1) > GAME_SIZE)
      ship.y = GAME_SIZE - (!ship.is_horizontal ? ship.length : 1);

    delete this->moveable_object;
    moveable_object = nullptr;

    this->field.ships.push_back(ship);
    this->redraw();
  }
}
