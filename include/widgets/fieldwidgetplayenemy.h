#pragma once

#include <widgets/fieldwidget.h>
#include <game/client/client.h>

class FieldWidgetPlayEnemy : public FieldWidget {
    Q_OBJECT
    GameClient* client;
public:
    FieldWidgetPlayEnemy(GameClient* client, QGraphicsView *parent = nullptr);
protected:
    void mousePressEvent( QGraphicsSceneMouseEvent *event );
};
