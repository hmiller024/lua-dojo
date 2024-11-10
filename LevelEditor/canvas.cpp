#include "canvas.h"

Canvas::Canvas(QWidget *parent, Qt::WindowFlags f) : QLabel (parent, f)
{

}

Canvas::Canvas(const QString& text, QWidget *parent, Qt::WindowFlags f) : QLabel (text, parent, f)
{

}

void Canvas::mouseMoveEvent(QMouseEvent *ev)
{
    const QPoint p = ev->pos();
    emit mouseMoved(p);
}

void Canvas::mousePressEvent(QMouseEvent *ev)
{
    const QPoint p = ev->pos();
    emit mouseMoved(p);
}
