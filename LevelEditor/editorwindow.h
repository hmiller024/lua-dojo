/// editorwindow.h
///
/// This file contains code for the main view of the SpriteEditor program
///
/// Author: Gavin Kerr, Hans Andersen, Hayden Miller, Solon Grover
/// Reviewed by: Gavin Kerr
/// Date: March 24, 2023

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QString>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QDir>

#include "editormodel.h"

// QT Creator says this is not needed, but removing it breaks the program...
#include "newprojectdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EditorWindow; }
QT_END_NAMESPACE

class EditorWindow : public QMainWindow
{

    Q_OBJECT

public:

    /// @brief Constructor for the EditorWindow
    EditorWindow(EditorModel& editorModel, QWidget *parent = nullptr);


    /// @brief Deconstructor for the EditorWindow
    ~EditorWindow();


    /// @brief Overrides the default closeEvent and replaces it
    /// in a way that prompts the user of unsaved work before
    /// closing
    /// @param QCloseEvent event
    void closeEvent(QCloseEvent *event);

signals:

    /// @brief Updates the current frame number from the view
    /// to the model
    /// @param int new frame
    void updateFrame(int);


    /// @brief Signal emitted when a new color is selected from
    /// any of the sliders or input fields
    /// @param QColor color
    void colorChange(QColor&);


    /// @brief Signal emmitted when a new color is selected from
    /// and of the sliders or input fields
    /// @param QString Author
    /// @param QString Title
    /// @param QString Type
    void updateLevelData(QString, QString, QString);


    /// @brief Signal emitted when the user requests a new project
    /// @param Project Dimentions
    void newProject(int);


    /// @brief Signal emitted when the user requests a project to
    /// be opened from disk
    /// @param QString filepath
    void openProject(QString&);


    /// @brief Signal emitted when the user requests a project to
    /// be saved to disk
    /// @param QString filepath
    void saveProject(QString&);


    /// @brief Signal emmited when the user requests a level to
    /// be saved to disk
    /// @param QString filepath
    void saveLevel(QString&);


    /// @brief Signal emitted when the user requests a project to
    /// be be exported as a .png
    /// @param QString filepath
    /// @param bool isSpritesheet
    void exportProject(QString&, bool);


public slots:

    /// @brief Slot for when the canvas is updated from the model
    /// @param QImage newCanvas
    /// @param bool to set play size
    void updateCanvas(QImage& image, bool shouldPlayActualSize);


    /// @brief Slot for when the color is changed from the model
    /// @param QColor color
    void updateColorPalette(QColor& color);


    /// @brief Slot for when the model returns the state if a project
    /// is saved to indicate save/unsaved work
    /// @param saved state
    void updateSaveIndicator(bool saved);


    /// @brief Slot for when the model returns the state if a project
    /// is playing
    /// @param playing state
    void updatePlayIndicator(bool playing);


    /// @brief Slot used for when file details are changed in the model
    /// to update the file details area
    /// @param QString filename
    /// @param QString dimentions
    /// @param QString frames
    void updateFileDetails(QString filename, QString dimentions, QString frames);


    /// @brief Slot that clears the current frame list
    void clearFrameList();


    /// @brief Slot used to set the currently selected item in the
    /// frame view
    /// @param int item
    void setFrameSelection(int item);


    /// @brief Adds a new frame button to the frame scroll view
    /// @param QString frame text
    void addFrameButton(const QString &text);


    /// @brief Removes a frame button from the frame scroll view
    /// @param frameNum
    void removeFrameButton(int frame);


    /// @brief Slot used for adding a new color to the color history
    void addColorToHistory(QColor color);


    /// @brief Slot used to update the current size of the paint brush
    void updatePaintBrushSize(int size);


private slots:

    /// @brief Slot for when any color slider is moved
    void colorSliderMoved();


    /// @brief Slot for when any color input bar is changed
    void colorLineEditChanged();


    /// @brief Slot for when any level file data is changed
    void levelLineEditChanged();
    

    /// @brief Slot for when paint is selected
    void paintSelected();


    /// @brief Slot for when erase is selected
    void eraseSelected();


    /// @brief for when the fill tool is selected
    void fillSelected();


    /// @brief Slot for when New Project is clicked
    void clickedNewProject();


    /// @brief Slot for when Open Project is clicked
    void clickedOpenProject();


    /// @brief Slot for when Save is clicked
    void clickedSaveProject();


    /// @brief Slot for when Export is clicked
    void clickedExportProject();

    /// @brife Slot for when Export Level is clicked
    void clickedExportLevel();


private:

    /// @brief Updates the FPS label
    /// @param new FPS
    void updateFpsLabel(int fps);


    /// @brief Prompts the user with a message if they have unsaved
    /// work, along with the passed message
    /// @param msg
    bool promptUnsavedWork(QString msg);


    /// @brief Helper function to pick between saving as a spritesheet
    /// or a single frame
    /// @param bool isSheet
    void saveSprite(bool isSheet);


    /// @brief Deselects all of the current tools
    void deselectAll();

    Ui::EditorWindow *ui;

};

#endif // EDITORWINDOW_H
