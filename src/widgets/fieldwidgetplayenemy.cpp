#include <widgets/fieldwidgetplayenemy.h>

FieldWidgetPlayEnemy::FieldWidgetPlayEnemy(GameClient* client, QGraphicsView *parent, FieldStyle style) : FieldWidget(parent, style), client(client) {}

void FieldWidgetPlayEnemy::mousePressEvent( QGraphicsSceneMouseEvent *event ){
    if (event->button() == Qt::LeftButton) {
        auto cell = getCellCoordinate({event->scenePos().x(),
                                       event->scenePos().y()});

        this->client->on_step(cell.x(), cell.y());
    }
}
