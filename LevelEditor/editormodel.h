/// editormodel.h
///
/// This file contains code for the model which backs the main EditorWindow
/// class.
///
/// Author: Gavin Kerr, Hans Andersen, Hayden Miller, Solon Grover
/// Date: March 24, 2023
/// Modified for A8 Level Editor

#ifndef EDITORMODEL_H
#define EDITORMODEL_H

#include <QObject>
#include <QImage>
#include <QMouseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QFile>
#include <QImageWriter>
#include <QTimer>
#include <QPainter>
#include <QListWidgetItem>

#include <vector>
#include <unordered_set>

#include "spritefile.h"

class EditorModel : public QObject
{
    Q_OBJECT

public:

    /// @brief Default constructor for the EditorModel
    explicit EditorModel(QObject *parent = nullptr);


    /// @brief Initalizes the default state of the model once the
    /// view has been initalized and connected
    void init();


    /// @brief Deconstructor
    ~EditorModel();


public slots:

    /// @brief Slot for when the user requests a new frame
    void addFrame();


    /// @brief Slot for when the user wants a frame deleted
    void removeFrame();


    /// @brief Slot for when a user wants to clone a frame
    void cloneFrame();


    /// @brief Slot for when the current frame needs to be updated
    /// from the List Item
    void updateCurrentFrame(QListWidgetItem* item);


    /// @brief Slot used to change the color from the color history
    /// in the view
    void changeColorFromHistory(QListWidgetItem* item);


    /// @brief Slot for when the Playback FPS needs to be updated
    /// @param int fps
    void updatePlaybackFps(int fps);


    /// @brief Slot used to start playing the animation
    void playAnimation();


    /// @brief Slot used to stop playing the animation
    void stopAnimation();


    /// @brief Slot used to handle a change in mouse position
    /// @param const QPoint point
    void handleMouseMove(const QPoint& point);


    /// @brief Slot used for when the currently selected color is changed
    /// @param QColor new Color
    void handleColorChange(QColor& color);


    /// @brief Slot used for when a new project is requested
    /// @param int size of new project
    void handleNewProject(int size);


    /// @brief Slot used for when level data is chagned
    /// @param QString Author
    /// @param QString Title
    /// @param QString Type
    void handleLevelDataChanged(QString author, QString title, QString type);


    /// @brief Slot used for when the paint tool is selected
    void handlePaintSelected();
    

    /// @brief Slot used for when the erase tool is selected
    void handleEraseSelected();


    /// @brief Slot used for when the fill tool is selected
    void handleFillSelected();
    

    /// @brief Slot for when the user requests the project to be saved
    /// @param QString& filepath
    void handleSaveProject(QString& filepath);


    /// @brief Slot for when the user requests a project to be opened
    /// @param QString& filepath
    void handleOpenProject(QString& filepath);


    /// @brief Slot for when the user requests the project to be
    /// exported as a .png as a sheet or one frame
    /// @param QString& filepath
    /// @param bool sheet
    void handleExportProject(QString& filepath, bool isSheet);


    /// @brief Slot for when the users requests exporting the selected
    /// frame as a .level for the a8-education app
    /// @param QString& filepath
    void handleExportLevel(QString& filepath);


    /// @brief Slot used to increase the size of the brush
    void increaseButtonSize();


    /// @brief Slot used to decrease the size of the brush
    void decreaseButtonSize();


    /// @brief Slot used to toggle if the animation should play at
    /// true size
    void setShouldPlayActualSize(int shouldPlayActualSize);


signals:

    /// @brief Signal used to update FPS Label
    /// @param FPS
    void updateFpsLabel(int);


    /// @brief Signal used to remove a frame from the vector
    /// @param Frame to be remvoed
    void removeFrameFromView(int);


    /// @brief Signal used to add a frame button to the scroll view
    /// @param QString frame name
    void addFrameToView(QString);


    /// @brief Signal used to update the backing QImage on the canvas
    /// @param QImage& image
    /// @param Should Play Actual Size
    void updateCanvas(QImage&, bool);


    /// @brief Signal used to update the color history on the View
    /// @param QColor& new color
    void updateColorPalette(QColor&);


    /// @brief Signal used to indicate the paint tool is selected
    void paintSelected();


    /// @brief Signal used to indicate the erase tool is selected
    void eraseSelected();


    /// @brief Signal used to indicate the fill tool is selected
    void fillSelected();


    /// @brief Signal used to update the frame name, dimentions, and frame count
    /// of a given project
    /// @param QString filename
    /// @param QString dimentions
    /// @param QString frame count
    void updateFileDetailsUI(QString, QString, QString);


    /// @brief Signal used to update the saved indicator on the view
    void updateSaveIndicator(bool);


    /// @brief Signal used to update the playing indicator on the view
    void updatePlayIndicator(bool);


    /// @brief Signal used when a file fails to load
    void failedFileLoad();


    /// @brief Signal used to clear the Frame scroll area
    void clearFrameList();


    /// @brief Signal used for when the Frame scroll selection needs to be updated
    void setFrameListItem(int);


    /// @brief Signal used to add a new color to the color history
    void addColorToHistory(QColor&);


    /// @brief Signal used to update the brush size on the view
    void brushSizeChanged(int);


private:

    /// @brief Prefills the Color picker with the level blocks
    void initColorList();


    /// @brief Slot for when the current frame needs to be updated
    void changeFrame(int newFrame);


    /// @brief Updates the current frame for the animation
    void displayNextAnimFrame();


    /// @brief Sets the defaults for all variables
    void setDefaults(int size);


    /// @brief Helper method that paints at a particular positon
    /// @param QPoint& point
    void paintPoint(const QPoint&);


    /// @brief Helper method that fills the entire canvas
    /// @param QPoint& point
    void fillPoint(const QPoint&);


    /// @brief Helper method that erases at a particular positon
    /// @param QPoint& point
    void erasePoint(const QPoint&);


    /// @brief Helper method that returns the filename of a given
    /// project from any given path
    /// @param QString& filepath
    QString getFileNameFromPath(QString& filepath);

    // Frame Variables
    SpriteFile* spriteFile;
    int currentFrame;

    // Tool variables
    int tool;
    enum tools{paint, fill, erase};
    int brushSize;

    // Filename
    QString filename;
    bool saved;

    // Color Variables
    QColor currentColor;
    std::unordered_set<QString> colorHistory;

    // Variables for animation
    int playBackFps;
    bool animationPlaying;
    bool shouldPlayActualSize;
    QTimer *timer;
    int animFrameNum;

};

#endif // EDITORMODEL_H
