/// gamemodel.h
/// This class acts as the model for the gamewindow view
///
/// Author: Hayden Miller
/// Date: April 11, 2023

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <vector>
#include <algorithm>
#include "level.h"

// Import Lua
#include <luacpp/src/LuaCpp.hpp>
#include <iostream>
using namespace LuaCpp;
using namespace LuaCpp::Engine;
using namespace LuaCpp::Registry;

class GameModel:  public QObject
{

    Q_OBJECT

public:

    explicit GameModel(QObject *parent = nullptr);

    /// @brief Initalizes the default state of the model once the
    /// view has been initalized and connected
    void init();


    /// @brief Deconstructor
    ~GameModel();

signals:

    /// @brief Signal emmited if the game fails to load required files on
    /// launch
    void failedInit(QString);


    /// @brief Signal emmited if the game launches with no issues
    void successInit();


    /// @brief Signal used to signal a compile or runtime error
    /// @param QString Type
    /// @param QString Error
    void executionFailed(QString, QString);


    /// @brief Signal used to write text to the output field
    /// @param QString text
    /// @param bool shouldClear
    void writeToOutput(QString, bool);


    /// @brief Signal used to update the IPC in the view
    /// @param int newIPC
    void updateIPC(int newIPC);


    /// @brief Signal used to clear the level scene
    void clearLevelScene();


    /// @brief Signal used to load level tiles into the scene
    void loadLevelScene(Level& level);


    /// @brief Signal used to update the level view
    void updateLevelScene(Level& level);


    /// @brief Signal used to indicate a level has been solved
    void runLevelCompleted();


    /// @brief Signal used to indicate a level has failed
    void runLevelFailed(QString reason);


    /// @brief Signal used to indicate the player has played all levels
    void playedAllLevels();


public slots:

    /// @brief Slot used to spin up a LuaContext and run the program
    void runLua(QString code);


    /// @brief Slot used for when the IPC needs to change
    void changeIPC(int ipc);


private slots:

    /// @brief Slot used to execute the lua moves until out of moves
    void runNextInstruction();


private:


    /// @brief Searches the res folder for levels and loads them all
    /// into the game on launch
    void loadLevelsFromDisk();


    /// @brief Searches the res folder for the luaFunctions.lua file,
    /// and loads it into a QString for later use.
    void loadLuaFunctions();


    /// @brief Trims an exception message to contain only important information
    /// for the user
    /// @param std::string exception message
    /// @returns QString trimmed message
    QString trimExceptionMessage(QString exMessage);


    /// @brief Validates if a player actually finished a level within the limits
    void validateLevelSolution();


    /// @brief Container for all levels loaded on startup
    std::vector<Level> levels;


    /// @brief String for all lua functions
    QString luaFunctions;
    std::vector<QString> moves;
    bool validSolution;
    int instructionCount;
    int lineCount;


    /// @brief Variable for default IPC
    int playbackIPC;
    QTimer* instructionTimer;
    bool runningCode;


    /// @brief int storing the current level
    int currentLevelNum;


};

#endif // GAMEMODEL_H
