#pragma once

#include <game/client/client.h>
#include <widgets/fieldwidget.h>

class FieldWidgetPlayEnemy : public FieldWidget {
  Q_OBJECT
  GameClient *client;

public:
  FieldWidgetPlayEnemy(GameClient *client, QGraphicsView *parent = nullptr,
                       FieldStyle *style = &FieldStyle::STYLE_PLAY_ENEMY);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
};
