/// gamewindow.h
/// This file contains backing code for the main view of the game
///
/// Author: Auto Generated by QT Creator
/// Date: April 11, 2023

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QIntValidator>
#include <QFontMetricsF>
#include <QPainter>
#include <QFont>
#include <map>
#include "gamemodel.h"
#include "level.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{

    Q_OBJECT

public:

    GameWindow(GameModel& gameModel, QWidget *parent = nullptr);

    ~GameWindow();

signals:

    /// @brief Signal used for when code should be exectuted
    /// @param QString usercode
    void executeCode(QString userCode);


    /// @brief Signal used to change the IPC for program execution
    /// in the model
    /// @param int newSpeed
    void changeIPC(int newSpeed);

public slots:

    /// @brief Slot used for when execution of code fails due to
    /// compile or runtime errors
    /// @param QString Error Type
    /// @param QString Error Message
    void handleFailedExecute(QString errorType, QString errorMsg);


    /// @brief Slot used for when the output field should be updated
    /// with text or data from the model
    /// @param QString text
    /// @param bool shouldClear
    void handleWriteToOutput(QString text, bool shouldClear);


    /// @brief Slot used for when the IPC should be changed from
    /// the model
    /// @param int IPC
    void handleIPCChange(int newIPC);


    /// @brief Slot for when the game fails to init
    /// @param QString reason
    void handleFailedInit(QString reason);


    /// @brief Slot used to clear the level
    void handleClearLevel();


    /// @brief Slot used to load the level scene
    void handleLoadLevelScene(Level& level);


    /// @brief Slot used to handle level scene updates
    void handleUpdateLevelScene(Level& level);


    /// @brief Slot used to handle when a level has been completed
    void handleLevelCompleted();


    /// @brief Slot used to handle when a solution is invalid
    void handleLevelFailed(QString reason);


    /// @brief Slot used to reset buttons and level contents for new level
    void nextLevel();


    /// @brief Slot used for when all levels have been played
    void handleAllLevelsComplete();


private slots:

    /// @brief Slot used for when the run button is pressed
    void clickedRunButton();


    /// @brief Slot used for when clear button is pressed
    void clickedClearButton();


    /// @brief Slot used for when the IPC slider is moved
    void ipcSliderChanged();


    /// @brief Slot used for when the IPC input is changed
    void ipcInputChanged();


    /// @brief Slot used for the scene effect timer
    void updateOpacity();


private:

    Ui::GameWindow *ui;
    QGraphicsScene* scene;
    std::map<long, QGraphicsPixmapItem*> sceneItems;
    int opacityCounter;
    QTimer* opacityTimer;

};
#endif // GAMEWINDOW_H
