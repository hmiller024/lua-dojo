/// codeeditor.h
///
/// This class creates a rich text programming editor for the user input
/// field
///
/// Author: Gavin Kerr, QT Documentation
/// Date: April 19, 2023

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QTextBlock>
#include <QPainter>
#include <QObject>
#include <QWidget>

/// @brief This class is the main text editor portion of the CodeEditor Widget
/// implementing line numbers and some syntax highlighting.
class CodeEditor : public QPlainTextEdit
{

    Q_OBJECT

public:

    /// @brief Default Constructor
    /// @param QWidget *parent
    CodeEditor(QWidget *parent = nullptr);


    /// @brief Paints the line numbers next to the code when called
    /// @param QPaintEvent* event
    void lineNumberAreaPaintEvent(QPaintEvent *event);


    /// @brief Returns the size of the linde number area width
    /// @returns line number width
    int lineNumberAreaWidth();

protected:

    /// @brief Event called when the widget is resized
    /// @param QResizeEvent
    void resizeEvent(QResizeEvent *event) override;

private slots:

    /// @brief Changes the line number area width to the passed value
    /// @param newBlockCount
    void updateLineNumberAreaWidth(int newBlockCount);


    /// @brief Highlights the currently selected line
    void highlightCurrentLine();


    /// @brief Updates the line number area
    /// @param QRect rect
    /// @param Dimentions y
    void updateLineNumberArea(const QRect &rect, int dy);


private:

    QWidget *lineNumberArea;

};


/// @brief This class seperates the code line numbers from the actual text
/// view, allowing for buttons and other stuff to be added later
class LineNumberArea : public QWidget
{

public:

    LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor) {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:

    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:

    CodeEditor *codeEditor;

};

#endif // CODEEDITOR_H
