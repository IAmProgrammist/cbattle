#ifndef FIELDWIDGETEDIT_H
#define FIELDWIDGETEDIT_H

#include <widgets/fieldwidget.h>
#include <utils/moveableobjectship.h>

class FieldWidgetEdit : public FieldWidget {
    Q_OBJECT

    MoveableObjectShip* moveable_object = nullptr;
public:
    FieldWidgetEdit(QGraphicsView *parent = nullptr);
protected:
    void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
    void mousePressEvent( QGraphicsSceneMouseEvent *event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );
};

#endif // FIELDWIDGETEDIT_H
