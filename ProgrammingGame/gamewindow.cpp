#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(GameModel& gameModel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{

    ui->setupUi(this);

    // Set custom font for text editor
    QFont monospaceFont("SourceCodePro-Regular");
    monospaceFont.setStyleHint(QFont::Monospace);
    ui->codeBox->setFont(monospaceFont);
    ui->outputBox->setFont(monospaceFont);

    // Set tab width
    ui->codeBox->setTabStopDistance(QFontMetricsF(monospaceFont).horizontalAdvance(" ") * 4);

    // Connect Run button
    connect(ui->runButton, &QPushButton::clicked, this, &GameWindow::clickedRunButton);
    connect(this, &GameWindow::executeCode, &gameModel, &GameModel::runLua);

    // Connect clear button
    connect(ui->clearButton, &QPushButton::clicked, this, &GameWindow::clickedClearButton);

    // Connect Error Handle Warning
    connect(&gameModel, &GameModel::executionFailed, this, &GameWindow::handleFailedExecute);

    // Connect Output Field
    connect(&gameModel, &GameModel::writeToOutput, this, &GameWindow::handleWriteToOutput);

    // Connect IPC Slider and Input
    connect(ui->ipcInput, &QLineEdit::editingFinished, this, &GameWindow::ipcInputChanged);
    connect(ui->ipcSlider, &QSlider::sliderReleased, this, &GameWindow::ipcSliderChanged);
    connect(this, &GameWindow::changeIPC, &gameModel, &GameModel::changeIPC);
    connect(&gameModel, &GameModel::updateIPC, this, &GameWindow::handleIPCChange);
    ui->ipcInput->setValidator(new QIntValidator(0, 400, this));

    // Connect Failed Init
    connect(&gameModel, &GameModel::failedInit, this, &GameWindow::handleFailedInit);

    // Connect Clear Scene
    connect(&gameModel, &GameModel::clearLevelScene, this, &GameWindow::handleClearLevel);

    // Connect Load Scene
    connect(&gameModel, &GameModel::loadLevelScene, this, &GameWindow::handleLoadLevelScene);

    // Connect Update Scene
    connect(&gameModel, &GameModel::updateLevelScene, this, &GameWindow::handleUpdateLevelScene);

    // Set up graphics view
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,550,550);
    ui->gameDisplay->setScene(scene);
    ui->gameDisplay->show();

    // Fade timer
    opacityCounter = 0;
    opacityTimer = new QTimer(this);
    connect(opacityTimer, &QTimer::timeout, this, &GameWindow::updateOpacity);

    //Lose screen stuff
    ui->levelCompleteWidget->setVisible(false);

    // Connect start level completed
    connect(&gameModel, &GameModel::runLevelCompleted, this, &GameWindow::handleLevelCompleted);

    // Connect failed level
    connect(&gameModel, &GameModel::runLevelFailed, this, &GameWindow::handleLevelFailed);

    // Connect Finished All levels
    connect(&gameModel, &GameModel::playedAllLevels, this, &GameWindow::handleAllLevelsComplete);

    // This should always be last
    // Finish setting up model
    gameModel.init();

}

GameWindow::~GameWindow()
{

    delete scene;
    delete ui;

}

void GameWindow::handleFailedExecute(QString errorType, QString errorMsg)
{
    QMessageBox err;
    err.setWindowTitle(errorType);
    err.critical(this, errorType, errorMsg);
}

void GameWindow::handleWriteToOutput(QString text, bool shouldClear)
{

    // Only clear if specified
    QString existingText = ui->outputBox->toPlainText();

    if (shouldClear) {
        ui->outputBox->setPlainText(text);
    } else {
        ui->outputBox->setPlainText(existingText + text);
    }

    ui->outputBox->moveCursor(QTextCursor::End);

}

void GameWindow::handleIPCChange(int newIPC)
{

    ui->ipcSlider->setValue(newIPC);
    ui->ipcInput->setText(QString::number(newIPC));

}

void GameWindow::handleFailedInit(QString reason)
{

    QMessageBox err;
    err.critical(this, "Fatal Error!", "Unable to start game beacuse: " + reason);

}

void GameWindow::clickedRunButton()
{

    // Get text from input
    emit executeCode(ui->codeBox->toPlainText());

}

void GameWindow::clickedClearButton()
{

    ui->codeBox->setPlainText("");
    ui->outputBox->setPlainText("");

}

void GameWindow::ipcSliderChanged()
{
    emit changeIPC(ui->ipcSlider->value());
}

void GameWindow::ipcInputChanged()
{
    emit changeIPC(ui->ipcInput->text().toInt());
}

void GameWindow::updateOpacity()
{

    opacityCounter++;

    if (opacityCounter < 350) {
        ui->levelCompleteWidget->setVisible(true);
        opacityTimer->start(10);
    } else if (opacityCounter >= 350 && opacityCounter <= 450){
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(ui->levelCompleteWidget);
        effect->setOpacity(1.0 - (opacityCounter % 350) * 0.01);
        ui->levelCompleteWidget->setGraphicsEffect(effect);
        opacityTimer->start(10);
    } else {
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(ui->levelCompleteWidget);
        effect->setOpacity(1.0);
        ui->levelCompleteWidget->setGraphicsEffect(effect);
        ui->levelCompleteWidget->stopAnimation();
        opacityCounter = 0;
        opacityTimer->stop();
        nextLevel();
    }

}

void GameWindow::handleClearLevel()
{

    // Clear scene
    scene->clear();
    sceneItems.clear();

}

void GameWindow::handleLoadLevelScene(Level &level)
{
    scene->clear();
    sceneItems.clear();

    // Load level text
    ui->levelTitle->setText(level.getLevelTitle());
    ui->levelDescription->setPlainText(level.getLevelDescription());
    ui->levelObjectives->setPlainText(level.getLevelObjectives());
    ui->levelHints->setPlainText(level.getLevelHints());
    ui->codeBox->setPlainText(level.getPreWrittenCode());

    // Calculate tile size
    double tileSize = 550.0f / (float)level.getLevelSize();

    // Load tiles
    std::vector<Tile> tiles = level.getLevelMap();
    for (unsigned long i = 0; i < tiles.size(); i++) {

        QGraphicsPixmapItem *tile = scene->addPixmap(tiles.at(i).getPixmap());

        // Set properties
        tile->setScale(tileSize / 16.0f);
        tile->setPos(QPointF(tiles.at(i).getX() * tileSize, tiles.at(i).getY() * tileSize));
        sceneItems.emplace(std::make_pair(tiles.at(i).getID(), tile));

    }

    // Load player
    QGraphicsPixmapItem *player;
    QPixmap& playerImg = level.getPlayer().getPixmap();

    player = scene->addPixmap(playerImg);
    player->setZValue(3);
    player->setScale(tileSize / (float)playerImg.width());
    player->setPos(QPointF(level.getPlayer().getX() * tileSize, level.getPlayer().getY() * tileSize));
    sceneItems.emplace(std::make_pair(level.getPlayer().getID(), player));

}

void GameWindow::handleUpdateLevelScene(Level &level)
{

    // Calculate tile size
    float tileSize = 550.0f / (float)level.getLevelSize();

    // Load tiles
    std::vector<Tile> tiles = level.getLevelMap();
    std::vector<LevelEntity> entities;

    entities.insert(entities.begin(), tiles.begin(), tiles.end());
    entities.push_back(level.getPlayer());

    for (unsigned long i = 0; i < entities.size(); i++) {

        // Only update tiles currently inside of the world
        if (sceneItems.contains(entities.at(i).getID())) {

            QGraphicsPixmapItem* tile = sceneItems.at(entities.at(i).getID());
            LevelEntity entity = entities.at(i);
            tile->setPixmap(entity.getPixmap());

            // Set properties
            tile->setScale(tileSize / (float)entity.getPixmap().width());
            tile->setPos(QPointF(entities.at(i).getX() * tileSize, entities.at(i).getY() * tileSize));

        }

    }

}

void GameWindow::handleLevelCompleted()
{
    //Deactivate buttons
    ui->clearButton->setEnabled(false);
    ui->runButton->setEnabled(false);

    //Animation stuff
    ui->levelCompleteWidget->resetAnimation();
    ui->levelCompleteWidget->setVisible(true);
    opacityTimer->start(10);
}

void GameWindow::handleLevelFailed(QString reason)
{

    QMessageBox err;
    err.setWindowTitle(reason);
    err.critical(this, "Level Failed!", reason);

}

void GameWindow::nextLevel()
{
    //Activate buttons
    ui->clearButton->setEnabled(true);
    ui->runButton->setEnabled(true);

    // Hide level completed widget
    ui->levelCompleteWidget->setVisible(false);
}

void GameWindow::handleAllLevelsComplete()
{

    QMessageBox msg;
    msg.setWindowTitle("Contrats!");
    msg.information(this, "Congratulations!", "You've played and passed all the levels, happy programming!");

}
