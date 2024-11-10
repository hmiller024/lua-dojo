/// canvas.h
///
/// This file contains code for the canavs, monitoring mouse movements on canvas for
/// editormodel to use.
///
/// Author: Gavin Kerr, Hans Andersen, Hayden Miller, Solon Grover
/// Date: March 24, 2023
#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class Canvas : public QLabel
{

    Q_OBJECT

public:

    /// @brief Default constructor for a QLabel Object
    /// @param QWidget parent, default nullptr
    /// @param Qt::WindowFlags f, default Qt::WindowFlags()
    Canvas(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    /// @brief Default constructor for a QLabel Object with text
    /// @param QString& text
    /// @param QWidget parent, default nullptr
    /// @param Qt::WindowFlags f, default Qt::WindowFlags()
    Canvas(const QString& text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    /// @brief Override for the mouse move event
    /// @param QMouseEvent* ev
    void mouseMoveEvent(QMouseEvent* ev);

    /// @brief Override for the mouse clicked event
    /// @param QMouseEvent* ev
    void mousePressEvent(QMouseEvent* ev);

signals:

    /// @brief Signal that gets emitted whenever the mouse is moved
    /// @param QPoint new position
    void mouseMoved (const QPoint&);


private:

};

#endif // CANVAS_H
