#include "gamemodel.h"

GameModel::GameModel(QObject *parent) : QObject {parent}
{

    playbackIPC = 100;
    currentLevelNum = 10;
    validSolution = false;
    instructionCount = 0;
    lineCount = 0;
    runningCode = false;

    instructionTimer = new QTimer(this);
    connect(instructionTimer, &QTimer::timeout, this, &GameModel::runNextInstruction);

}

void GameModel::init()
{

    // Load resources
    loadLevelsFromDisk();
    loadLuaFunctions();

    // Load defaults into UI
    emit updateIPC(100);

    // Load first level
    emit loadLevelScene(levels.at(currentLevelNum));

}

GameModel::~GameModel()
{

    delete instructionTimer;

}

void GameModel::runLua(QString code)
{

    // Clear moves queue and stats
    moves.clear();
    instructionTimer->stop();
    levels[currentLevelNum].resetLevel();
    emit updateLevelScene(levels.at(currentLevelNum));

    // Create Lua Context and State
    LuaContext context;
    std::unique_ptr<LuaState> luaState = context.newState();

    // Setup shared variable
    std::shared_ptr<Engine::LuaTTable> actions = std::make_shared<Engine::LuaTTable>();
    context.AddGlobalVariable("actions", actions);

    // Compile code
    try {
        emit writeToOutput("[LUA]: Building\n", true);
        context.CompileString("userCode", luaFunctions.toStdString() + code.toStdString());
        emit writeToOutput("[LUA]: Build Complete\n", false);
        lineCount = code.count("\n") + 1;
        emit writeToOutput("-- Lines: " + QString::number(code.count("\n") + 1) + "\n", false);
    } catch (std::exception& e) {
        emit writeToOutput("[LUA]: Build failed! Please check the message below:\n" + trimExceptionMessage(e.what()), false);
        emit executionFailed("Compile Error!", trimExceptionMessage(e.what()));
        return;
    }

    // Execute code
    try {
        emit writeToOutput("[LUA]: Generating Level Instructions\n", false);
        context.Run("userCode");
        emit writeToOutput("[LUA]: Done Generating Level Instructions\n", false);
        instructionCount = actions->getValues().size();
        emit writeToOutput("-- Level Instructions: " + QString::number(actions->getValues().size()) + "\n", false);
    } catch (std::runtime_error& e) {
        emit writeToOutput("[LUA]: Runtime Error! Please check the message below:\n" + trimExceptionMessage(e.what()), false);
        emit executionFailed("Runtime Error!", trimExceptionMessage(e.what()));
        return;
    }

    // Load actions into moves
    for (unsigned long i = 0; i < actions->getValues().size(); i++) {
        std::string str = ((LuaTString &) actions->getValue(Table::Key(i + 1))).getValue();
        moves.push_back(QString::fromStdString(str));
    }

    // Run instructions
    instructionTimer->start(1000 / (playbackIPC / 100));

}

void GameModel::changeIPC(int ipc)
{

    // Round to nearest 20%
    playbackIPC = round(int((ipc + 9) / 20) * 20);

    // Restrict to 20
    if (playbackIPC < 20)
        playbackIPC = 20;

    emit updateIPC(playbackIPC);
}

void GameModel::runNextInstruction()
{
    if(levels.at(currentLevelNum).getPlayer().getAir())
    {
        levels.at(currentLevelNum).resetLevel();
        moves.clear();
        emit updateLevelScene(levels.at(currentLevelNum));
    }
    // Only run if there are any moves
    if (moves.size() > 0) {
        runningCode = true;

        // Get move and move player
        QString move = moves.front();
        emit writeToOutput("[LEVEL]: Executing instruction: " + move + "\n", false);
        QString result = levels.at(currentLevelNum).processMove(move);

        // Delete move from list
        moves.erase(moves.begin());

        // Emit update
        if (result.size() > 0)
            emit writeToOutput("[LEVEL]: " + result + "\n", false);

        emit updateLevelScene(levels.at(currentLevelNum));

        // Restart timer
        instructionTimer->start(1000 / (playbackIPC / 100));

    } else {
        runningCode = false;
        instructionTimer->stop();
        emit writeToOutput("[LEVEL]: Done Executing!", false);
        validateLevelSolution();
    }

}

void GameModel::loadLevelsFromDisk()
{

    // Iterate through folder and load all levels
    QDir dir (QDir::currentPath() + "/res/levels/");
    dir.setSorting(QDir::LocaleAware | QDir::SortFlag::Name);
    QDirIterator filesystem(dir);
    qDebug() << "Searching for files in: " + QDir::currentPath() + "/res/levels/";

    while (filesystem.hasNext()) {
        QFile file(filesystem.next());

        // Validate file extension
        if (file.fileName().endsWith(".level")) {
            Level newLevel;

            // Attempt to open file
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                emit failedInit("Failed to load level file: " + file.fileName());
                qDebug() << "Failed to load level file: " + file.fileName();
            }

            // Read Data
            QString data = file.readAll();
            file.close();

            QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
            newLevel.read(doc.object());

            // Store file
            levels.push_back(newLevel);
        }
    }

    // Sort levels
    std::sort(levels.begin(), levels.end(), std::greater<Level>());
    for (unsigned long i = 0; i < levels.size(); i++) {
        qDebug() << "Loaded:" << levels.at(i).getLevelTitle();
    }

}

void GameModel::loadLuaFunctions()
{

    // Set File
    QFile file(QDir::currentPath() + "/res/levels/luaFunctions.lua");

    // Open File
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit failedInit("Failed to load luaFunctions.lua!");
        qDebug() << "Failed to load luaFunctions.lua!";
        return;
    }

    // Read Data and close file
    luaFunctions = file.readAll();
    file.close();

}


QString GameModel::trimExceptionMessage(QString exMessage)
{

    QString finalMessage;

    // Get line number and offset
    int firstColon = exMessage.indexOf(":");
    int lastColon = exMessage.indexOf(":", firstColon + 1);
    int lineNumber = exMessage.mid(firstColon + 1, (lastColon - firstColon) - 1).toInt()
                     - luaFunctions.count("\n");

    // Build error message
    finalMessage = "[Line:" + QString::number(lineNumber) + "] " + exMessage.mid(lastColon + 1);

    return finalMessage;

}

void GameModel::validateLevelSolution()
{

    Level& level = levels.at(currentLevelNum);

    // Check line limit
    if (lineCount > level.getLevelLineLimit() && level.getLevelLineLimit() > 0) {
        emit runLevelFailed("Your solution is invalid because it is over the required line limit."
                            " The solution must be under " + QString::number(level.getLevelLineLimit())
                            + " while yours is " + QString::number(lineCount));
        level.resetLevel();
        emit updateLevelScene(levels.at(currentLevelNum));
        return;
    }

    // Check Instruction Limit
    if (instructionCount > level.getLevelInstructionLimit() && level.getLevelInstructionLimit() > 0) {
        emit runLevelFailed("Your solution is invalid because it is over the required instruction limit."
                            " The solution must be under " + QString::number(level.getLevelInstructionLimit())
                            + " while yours is " + QString::number(instructionCount));
        level.resetLevel();
        emit updateLevelScene(levels.at(currentLevelNum));
        return;
    }

    // Check Gem Count
    if (level.getLevelGemCount() != level.getCollectedGemCount()) {
        emit runLevelFailed("Your solution is invalid because you didn't collect all the gems!"
                            " You need to collect " + QString::number(level.getLevelGemCount())
                            + " while your only collected " + QString::number(level.getCollectedGemCount()));
        level.resetLevel();
        emit updateLevelScene(levels.at(currentLevelNum));
        return;
    }

    // Check player position
    Player player = level.getPlayer();
    QPoint playerPos(player.getX(), player.getY());
    if(playerPos != level.getEndPos())
    {
        emit runLevelFailed("Your solution is invalid because you didn't reach the green end block!");
        level.resetLevel();
        emit updateLevelScene(levels.at(currentLevelNum));
        return;
    }

    // Passed!
    emit runLevelCompleted();
    currentLevelNum++;

    if ((unsigned long)currentLevelNum < levels.size()) {
        emit loadLevelScene(levels.at(currentLevelNum));
    } else {
        emit playedAllLevels();
    }

}
