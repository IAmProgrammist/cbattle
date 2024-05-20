#ifndef FIELDVIEWEDIT_H
#define FIELDVIEWEDIT_H

#include "fieldview.h"

class FieldViewEdit : public FieldView{
    Q_OBJECT

    MovableObjectShip* moveable_object = nullptr;
public:
    FieldViewEdit(QGraphicsView *parent = nullptr) : FieldView(parent) {}
protected:
    void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
    void mousePressEvent( QGraphicsSceneMouseEvent *event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent *event );
};

#endif // FIELDVIEWEDIT_H
