// Reviewed by Hans Andersen
#include "editormodel.h"

EditorModel::EditorModel(QObject *parent)
    : QObject{parent}
{

    // Initalizes default values
    setDefaults(SpriteFile::DEFAULT_WIDTH);

}

void EditorModel::init()
{

    emit updateCanvas(spriteFile->getFrame(currentFrame),  false);
    emit updateColorPalette(currentColor);
    emit updateFileDetailsUI(filename, QString::number(spriteFile->getWidth()),
                             QString::number(spriteFile->getFrameCount()));
    emit updateSaveIndicator(saved);
    emit addFrameToView("Frame " + QString::number(spriteFile->getFrameCount() - 1));
    handlePaintSelected();
    emit brushSizeChanged(brushSize + 1);
    emit updatePlayIndicator(false);
    initColorList();

}

EditorModel::~EditorModel()
{

    delete spriteFile;

}

void EditorModel::addFrame()
{
    if (animationPlaying)
        return;

    spriteFile->addFrame();
    emit addFrameToView("Frame " + QString::number(spriteFile->getFrameCount() - 1));

    // Show the new frame
    changeFrame(spriteFile->getFrameCount() - 1);
}

void EditorModel::cloneFrame()
{
    if (animationPlaying)
        return;

    spriteFile->cloneFrame(currentFrame);
    emit addFrameToView("Frame " + QString::number(spriteFile->getFrameCount() - 1));

    // Show the new frame
    changeFrame(spriteFile->getFrameCount() - 1);
}

void EditorModel::removeFrame()
{
    if (animationPlaying)
        return;

    // Don't let the user delete if we only have 1 frame
    if (spriteFile->getFrameCount() > 1)
    {
        spriteFile->removeFrame(currentFrame);
        if (currentFrame !=0)
            currentFrame--;
        emit removeFrameFromView(currentFrame);
    }

    // Change the frame image if the current frame was deleted
    QImage& image = spriteFile->getFrame(currentFrame);
    // Update canvas
    emit updateCanvas(image,  false);
}

void EditorModel::updateCurrentFrame(QListWidgetItem* item)
{

    int selectedFrame = item->text().remove(0, 5).toInt();

    currentFrame = selectedFrame;
    QImage& image = spriteFile->getFrame(currentFrame);

    // Update canvas
    emit updateCanvas(image,  false);
}

void EditorModel::changeColorFromHistory(QListWidgetItem *item)
{

    QColor newColor(item->text());
    currentColor = newColor;
    emit updateColorPalette(newColor);

}

void EditorModel::updatePlaybackFps(int fps)
{
    playBackFps = fps;

    // Only update live if animation is alrady playing
    if (animationPlaying) {
        stopAnimation();
        playAnimation();
    }

    emit updateFpsLabel(fps);
}

void EditorModel::playAnimation()
{
    if (!animationPlaying)
    {
        animationPlaying = true;
        timer->start(1000/playBackFps);
        emit updatePlayIndicator(true);
    }
}

void EditorModel::displayNextAnimFrame()
{
    if (animFrameNum == spriteFile->getFrameCount())
    {
        animFrameNum = 0;
    }

    changeFrame(animFrameNum);
    emit setFrameListItem(animFrameNum);

    animFrameNum++;
}

void EditorModel::stopAnimation()
{
    if (animationPlaying)
    {
        animationPlaying = false;
        timer->stop();
        emit updateCanvas(spriteFile->getFrame(currentFrame),  false);
        emit updatePlayIndicator(false);
    }
}

void EditorModel::handleMouseMove(const QPoint &point)
{
    if (animationPlaying)
        return;

    QImage& image = spriteFile->getFrame(currentFrame);

    // frame size/image size
    float scale = (600 / (float)spriteFile->getWidth());

    float xpos = (float)point.x() / scale;
    float ypos = (float)point.y() / scale;

    // Don't push update if drawing off frame
    if (xpos < 0 || xpos >= spriteFile->getWidth() || ypos < 0 || ypos >= spriteFile->getHeight())
        return;

    if(tool == erase)
    {
        if (brushSize == 0) {
            image.setPixelColor(xpos, ypos, QColor(0,0,0,0));
        }
        else {
            for (int i = -brushSize; i < brushSize; i++) {
                for (int j = -brushSize; j < brushSize; j++) {
                    image.setPixelColor(xpos + i, ypos + j, QColor(0,0,0,0));
                }

            }
        }
    }
    else if (tool == paint)
    {
        if (brushSize == 0) {
            image.setPixelColor(xpos, ypos, currentColor);
        }
        else {
            for (int i = -brushSize; i < brushSize; i++) {
                for (int j = -brushSize; j < brushSize; j++) {
                    image.setPixelColor(xpos + i, ypos + j, currentColor);
                }

            }
        }

        // Add to color history if it hasn't been yet
        std::unordered_set<QString>::const_iterator hasColor = colorHistory.find(currentColor.name(QColor::HexArgb));
        if (hasColor == colorHistory.end()) {
            colorHistory.emplace(currentColor.name(QColor::HexArgb));
            emit addColorToHistory(currentColor);
        }

    } else if (tool == fill) {
        image.fill(currentColor);
    }

    // Update canvas
    emit updateCanvas(image,  false);

    // Update save state
    saved = false;
    emit updateSaveIndicator(saved);
}

void EditorModel::handleColorChange(QColor &color)
{

    currentColor = color;
    emit updateColorPalette(currentColor);

}

void EditorModel::handleNewProject(int size)
{
    // Remove frames
    for (int i = 0; i < spriteFile->getFrameCount(); i++)
        emit removeFrameFromView(0);

    // Remove old spritefile
    delete spriteFile;
    setDefaults(size);

    stopAnimation();
    emit updateCanvas(spriteFile->getFrame(currentFrame),  false);
    emit updateFileDetailsUI(filename, QString::number(spriteFile->getWidth()),
                             QString::number(spriteFile->getFrameCount()));
    emit clearFrameList();
    emit addFrameToView("Frame " + QString::number(spriteFile->getFrameCount() - 1));

}

void EditorModel::handleLevelDataChanged(QString author, QString title, QString type)
{

    spriteFile->setLevelData(author, title, type, 60);

}

void EditorModel::handlePaintSelected()
{
    tool = paint;
    emit paintSelected();
}

void EditorModel::handleEraseSelected()
{
    tool = erase;
    emit eraseSelected();
}

void EditorModel::handleFillSelected()
{
    tool = fill;
    emit fillSelected();
    emit updateFileDetailsUI(filename, QString::number(spriteFile->getWidth()),
                             QString::number(spriteFile->getFrameCount()));
    emit updateSaveIndicator(saved);

}

void EditorModel::handleSaveProject(QString &filepath)
{
    // Open up file to save data
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly)) {
        emit failedFileLoad();
        return;
    }

    QJsonObject fileData;
    spriteFile->write(fileData);

    file.write(QJsonDocument(fileData).toJson(QJsonDocument::Compact));
    file.close();

    saved = true;
    filename = getFileNameFromPath(filepath);
    emit updateSaveIndicator(saved);
    emit updateFileDetailsUI(filename, QString::number(spriteFile->getWidth()),
                             QString::number(spriteFile->getFrameCount()));
}

void EditorModel::handleExportProject(QString &filepath, bool isSheet)
{
    // Stop animation first
    stopAnimation();

    // Remove extension
    if(filepath.contains(".spp"))
    {
        filepath.remove((".spp"));
    }

    // Open file for export
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly)) {
        emit failedFileLoad();
        return;
    }

    if(isSheet)
    {
        int size = std::ceil(std::sqrt(spriteFile->getFrameCount()));
        QImage spriteSheet(size * spriteFile->getHeight(), size * spriteFile->getWidth(), QImage::Format_ARGB32);
        spriteSheet.fill(QColor(0,0,0,0));

        QPainter painter(&spriteSheet);
        int x = 0;
        int y = 0;
        int frame = 0;

        for(int i = 0; i < size; i++)
        {
            x = 0;
            for(int k = 0; k < size; k++)
            {

                if(frame > spriteFile->getFrameCount()-1)
                    break;
                painter.drawImage(x,y,spriteFile->getFrame(frame));
                x += spriteFile->getHeight();
                frame++;

            }
            y+= spriteFile->getWidth();
        }
        spriteSheet.save(filepath, nullptr);
    }
    else
    {
        spriteFile->getFrame(currentFrame).save(filepath, nullptr);
    }
}

void EditorModel::handleExportLevel(QString &filepath)
{

    // Open file for export
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly)) {
        emit failedFileLoad();
        return;
    }

    QJsonObject fileData;
    spriteFile->writeLevel(fileData);
    //QJsonDocument::Compact
    file.write(QJsonDocument(fileData).toJson());
    file.close();

}

void EditorModel::handleOpenProject(QString &filepath)
{

    // Open file, attempt to load data
    QFile file(filepath);
    QString fileData;


    // Open file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        emit failedFileLoad();
        return;
    }

    fileData = file.readAll();
    file.close();

    // Load sprite
    QJsonDocument doc = QJsonDocument::fromJson(fileData.toUtf8());
    spriteFile->read(doc.object());

    currentFrame = 0;
    filename = getFileNameFromPath(filepath);

    if(filename.contains(".ssp"))
    {
        filename.remove((".ssp"));
    }
    stopAnimation();
    emit updateCanvas(spriteFile->getFrame(currentFrame), false);
    emit updateFileDetailsUI(filename, QString::number(spriteFile->getWidth()),
                             QString::number(spriteFile->getFrameCount()));
    emit updateSaveIndicator(saved);

    // Add Frame buttons
    emit clearFrameList();
    for (int i = 0; i < spriteFile->getFrameCount(); i++) {
        emit addFrameToView("Frame " + QString::number(i));
    }

}

void EditorModel::setDefaults(int size)
{

    spriteFile = new SpriteFile(size, size);
    currentColor.setNamedColor("white");
    playBackFps = 5;
    animationPlaying = false;
    shouldPlayActualSize = false;
    animFrameNum = 0;
    currentFrame = 0;
    saved = true;
    brushSize = 0;
    filename = "new";

    // Connect timer to animation method
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EditorModel::displayNextAnimFrame);

}

QString EditorModel::getFileNameFromPath(QString &filepath)
{

    QStringList strings = filepath.split("/");
    return strings.last();

}

void EditorModel::increaseButtonSize() {
    if (brushSize < spriteFile->getWidth() / 2) {
        brushSize++;
        emit brushSizeChanged(brushSize + 1);
    }
}

void EditorModel::decreaseButtonSize() {
    if (brushSize > 0) {
        brushSize--;
        emit brushSizeChanged(brushSize + 1);
    }
}

void EditorModel::setShouldPlayActualSize(int shouldPlayActualSize)
{
    this->shouldPlayActualSize = shouldPlayActualSize;
}

void EditorModel::initColorList()
{

    QColor tempColor;

    // Air
    tempColor.setRgba(qRgba(0, 0, 0, 0));
    colorHistory.emplace(tempColor.name(QColor::HexArgb));
    emit addColorToHistory(tempColor);

    // Ground
    tempColor.setRgba(qRgba(0, 0, 0, 255));
    colorHistory.emplace(tempColor.name(QColor::HexArgb));
    emit addColorToHistory(tempColor);

    // Wall
    tempColor.setRgba(qRgba(150, 150, 150, 255));
    colorHistory.emplace(tempColor.name(QColor::HexArgb));
    emit addColorToHistory(tempColor);

    // Start
    tempColor.setRgba(qRgba(0, 255, 0, 255));
    colorHistory.emplace(tempColor.name(QColor::HexArgb));
    emit addColorToHistory(tempColor);

    // End
    tempColor.setRgba(qRgba(255, 0, 0, 255));
    colorHistory.emplace(tempColor.name(QColor::HexArgb));
    emit addColorToHistory(tempColor);

    // Gem
    tempColor.setRgba(qRgba(0, 0, 255, 255));
    colorHistory.emplace(tempColor.name(QColor::HexArgb));
    emit addColorToHistory(tempColor);


}

void EditorModel::changeFrame(int newFrame)
{

    currentFrame = newFrame;
    QImage& image = spriteFile->getFrame(currentFrame);

    // Update canvas
    emit updateCanvas(image, shouldPlayActualSize);

}
