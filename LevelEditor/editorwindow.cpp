// Reviewed by: Gavin Kerr
#include "editorwindow.h"
#include "ui_editorwindow.h"

EditorWindow::EditorWindow(EditorModel& editorModel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    connect(ui->canvas, &Canvas::mouseMoved, &editorModel, &EditorModel::handleMouseMove);
    connect(&editorModel, &EditorModel::updateCanvas, this, &EditorWindow::updateCanvas);

    // Connect Color Palette Slides, Text, and Labels
    // Red
    connect(ui->redColorSlider, &QSlider::sliderReleased, this, &EditorWindow::colorSliderMoved);
    connect(ui->redColorTextInput, &QLineEdit::textChanged, this, &EditorWindow::colorLineEditChanged);
    // Green
    connect(ui->greenColorSlider, &QSlider::sliderReleased, this, &EditorWindow::colorSliderMoved);
    connect(ui->greenColorTextInput, &QLineEdit::textChanged, this, &EditorWindow::colorLineEditChanged);
    // Blue
    connect(ui->blueColorSlider, &QSlider::sliderReleased, this, &EditorWindow::colorSliderMoved);
    connect(ui->blueColorTextInput, &QLineEdit::textChanged, this, &EditorWindow::colorLineEditChanged);
    // Alpha
    connect(ui->alphaColorSlider, &QSlider::sliderReleased, this, &EditorWindow::colorSliderMoved);
    connect(ui->alphaColorTextInput, &QLineEdit::textChanged, this, &EditorWindow::colorLineEditChanged);

    connect(this, &EditorWindow::colorChange, &editorModel, &EditorModel::handleColorChange);
    connect(&editorModel, &EditorModel::updateColorPalette, this, &EditorWindow::updateColorPalette);

    // Connect File Actions buttons
    // New
    connect(ui->newFileButton, &QPushButton::clicked, this, &EditorWindow::clickedNewProject);
    connect(this, &EditorWindow::newProject, &editorModel, &EditorModel::handleNewProject);
    // Open
    connect(ui->openFileButton, &QPushButton::clicked, this, &EditorWindow::clickedOpenProject);
    connect(this, &EditorWindow::openProject, &editorModel, &EditorModel::handleOpenProject);
    // Save
    connect(ui->saveButton, &QPushButton::clicked, this, &EditorWindow::clickedSaveProject);
    connect(this, &EditorWindow::saveProject, &editorModel, &EditorModel::handleSaveProject);
    connect(ui->exportButton, &QPushButton::clicked, this, &EditorWindow::clickedExportProject);
    connect(this, &EditorWindow::exportProject, &editorModel, &EditorModel::handleExportProject);

    // Connect File Details Elements
    connect(&editorModel, &EditorModel::updateFileDetailsUI, this, &EditorWindow::updateFileDetails);
    connect(&editorModel, &EditorModel::updateSaveIndicator, this, &EditorWindow::updateSaveIndicator);

    // Connect Tool Buttons
    connect(ui->paintButton, &QPushButton::clicked, &editorModel, &EditorModel::handlePaintSelected);
    connect(ui->eraseButton, &QPushButton::clicked, &editorModel, &EditorModel::handleEraseSelected);
    connect(ui->fillButton, &QPushButton::clicked, &editorModel, &EditorModel::handleFillSelected);
    connect(&editorModel, &EditorModel::paintSelected, this, &EditorWindow::paintSelected);
    connect(&editorModel, &EditorModel::eraseSelected, this, &EditorWindow::eraseSelected);
    connect(&editorModel, &EditorModel::fillSelected, this, &EditorWindow::fillSelected);

    // Connect add frame button
    connect(ui->addFrameButton, &QPushButton::clicked, &editorModel, &EditorModel::addFrame);
    connect(&editorModel, &EditorModel::addFrameToView, this, &EditorWindow::addFrameButton);

    // Connect remove frame button
    connect(ui->removeFrameButton, &QPushButton::clicked, &editorModel, &EditorModel::removeFrame);
    connect(&editorModel, &EditorModel::removeFrameFromView, this, &EditorWindow::removeFrameButton);

    // Connect clone frame button
    connect(ui->cloneFrameButton, &QPushButton::clicked, &editorModel, &EditorModel::cloneFrame);

    // Connect the update frame signal in view to update frame slot in model
    connect(ui->listWidgetForFrames, &QListWidget::itemClicked, &editorModel, &EditorModel::updateCurrentFrame);
    connect(&editorModel, &EditorModel::setFrameListItem, this, &EditorWindow::setFrameSelection);
    connect(&editorModel, &EditorModel::clearFrameList, this, &EditorWindow::clearFrameList);

    // Connect FPS slider
    connect(ui->horizontalSliderFps, &QSlider::sliderMoved, &editorModel, &EditorModel::updatePlaybackFps);
    connect(&editorModel, &EditorModel::updateFpsLabel, this, &EditorWindow::updateFpsLabel);

    // Connect Animation Buttons
    connect(ui->pushButtonPlayAnimation, &QPushButton::clicked, &editorModel, &EditorModel::playAnimation);
    connect(ui->pushButtonStopAnimation, &QPushButton::clicked, &editorModel, &EditorModel::stopAnimation);
    connect(ui->checkBoxActualSpriteSize, &QCheckBox::stateChanged, &editorModel, &EditorModel::setShouldPlayActualSize);
    connect(&editorModel, &EditorModel::updatePlayIndicator, this, &EditorWindow::updatePlayIndicator);

    // Connect Brush size modifiers 
    connect(ui->increaseButton, &QPushButton::clicked, &editorModel, &EditorModel::increaseButtonSize);
    connect(ui->decreaseButton, &QPushButton::clicked, &editorModel, &EditorModel::decreaseButtonSize);
    connect(&editorModel, &EditorModel::brushSizeChanged, this, &EditorWindow::updatePaintBrushSize);

    // Connect color history
    connect(ui->colorHistory, &QListWidget::itemClicked, &editorModel, &EditorModel::changeColorFromHistory);
    connect(&editorModel, &EditorModel::addColorToHistory, this, &EditorWindow::addColorToHistory);

    // Connect level edit changes
    connect(ui->levelAuthorEdit, &QLineEdit::textChanged, this, &EditorWindow::levelLineEditChanged);
    connect(ui->levelTitleEdit, &QLineEdit::textChanged, this, &EditorWindow::levelLineEditChanged);
    connect(ui->levelTypeEdit, &QLineEdit::textChanged, this, &EditorWindow::levelLineEditChanged);
    connect(this, &EditorWindow::updateLevelData, &editorModel, &EditorModel::handleLevelDataChanged);
    connect(ui->levelExportButton, &QPushButton::clicked, this, &EditorWindow::clickedExportLevel);
    connect(this, &EditorWindow::saveLevel, &editorModel, &EditorModel::handleExportLevel);

    editorModel.init();

}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::updateFpsLabel(int fps) {
    ui->labelFps->setText("Speed: " + QString::number(fps) + " fps");
}

void EditorWindow::addFrameButton(const QString &text)
{

    QListWidget *list = ui->listWidgetForFrames;

    // Create a new item for the list view
    QListWidgetItem *item = new QListWidgetItem(list);
    item->setSelected(true);
    item->setText(text);

}

void EditorWindow::removeFrameButton(int frame) {

    // Remove the frame from the list
    ui->listWidgetForFrames->takeItem(frame);

    // Cycle through the rest of the items and update the names
    for (int i = frame; i < ui->listWidgetForFrames->count(); i++) {
        QListWidgetItem *item = ui->listWidgetForFrames->item(i);
        item->setText("Frame " + QString::number(i));
    }

}

void EditorWindow::addColorToHistory(QColor color)
{

    QListWidgetItem* item = new QListWidgetItem();
    item->setText(color.name(QColor::HexArgb));
    item->setBackground(color);

    // Detect System Wide Theme
    QColor systemTheme = palette().color(QPalette::Window);

    // Change text color depending on system theme
    if (systemTheme.redF() > 0.5f) {
        // Light on dark color for light mode
        if (color.valueF() < 0.5f)
            item->setForeground(QColor::fromRgbF(1.0, 1.0, 1.0));
    } else {
        // Light on dark color for dark mode
        if (color.valueF() > 0.5f)
            item->setForeground(QColor::fromRgbF(0.0, 0.0, 0.0));
    }


    ui->colorHistory->addItem(item);

}

void EditorWindow::updatePaintBrushSize(int size)
{
    ui->brushSizeLabel->setText(QString::number(size));
}

void EditorWindow::closeEvent(QCloseEvent *event)
{

    // Check for unsaved work first
    if (promptUnsavedWork("Do you still want to exit?")) {
        event->accept();
    } else {
        event->ignore();
    }

}

void EditorWindow::updateCanvas(QImage& image, bool shouldPlayActualSize) {

    int canvasSize = ui->canvas->size().width();

    if (shouldPlayActualSize) {
        ui->canvas->setPixmap(QPixmap::fromImage(image));
    } else {
        ui->canvas->setPixmap(QPixmap::fromImage(image.scaled(canvasSize, canvasSize)));
    }

}

void EditorWindow::updateColorPalette(QColor &color)
{

    ui->redColorSlider->setValue(color.red());
    ui->greenColorSlider->setValue(color.green());
    ui->blueColorSlider->setValue(color.blue());
    ui->alphaColorSlider->setValue(color.alpha());

    ui->redColorTextInput->setText(QString::number(color.red()));
    ui->greenColorTextInput->setText(QString::number(color.green()));
    ui->blueColorTextInput->setText(QString::number(color.blue()));
    ui->alphaColorTextInput->setText(QString::number(color.alpha()));

    QString styleSheetVal = QString::number(color.red()) + "," + QString::number(color.green()) + "," +
                            QString::number(color.blue()) + "," + QString::number(color.alpha());

    ui->colorPreview->setStyleSheet(QString("QWidget {background-color: rgba(" + styleSheetVal + ");}"));

}

void EditorWindow::colorSliderMoved()
{

    QColor tempColor;
    tempColor.setRed(ui->redColorSlider->value());
    tempColor.setGreen(ui->greenColorSlider->value());
    tempColor.setBlue(ui->blueColorSlider->value());
    tempColor.setAlpha(ui->alphaColorSlider->value());
    emit colorChange(tempColor);

}

void EditorWindow::colorLineEditChanged()
{

    QColor tempColor;
    tempColor.setRed(ui->redColorTextInput->text().toInt());
    tempColor.setGreen(ui->greenColorTextInput->text().toInt());
    tempColor.setBlue(ui->blueColorTextInput->text().toInt());
    tempColor.setAlpha(ui->alphaColorTextInput->text().toInt());
    emit colorChange(tempColor);

}

void EditorWindow::levelLineEditChanged()
{

    emit updateLevelData(ui->levelAuthorEdit->text(),
                         ui->levelTitleEdit->text(),
                         ui->levelTypeEdit->text());

}


void EditorWindow::clickedNewProject()
{

    if (!promptUnsavedWork("Discard it?"))
        return;

    NewProjectDialog dialog;
    dialog.exec();

    if (dialog.Accepted) {

        emit newProject(dialog.getImageSize());

    }
}

void EditorWindow::fillSelected()
{
    deselectAll();
    ui->fillButton->setEnabled(false);   
}

void EditorWindow::paintSelected()
{
    deselectAll();
    ui->paintButton->setEnabled(false);
}

void EditorWindow::eraseSelected()
{
    deselectAll();
    ui->eraseButton->setEnabled(false);
}

void EditorWindow::deselectAll()
{
    ui->eraseButton->setEnabled(true);
    ui->fillButton->setEnabled(true);
    ui->paintButton->setEnabled(true);
}

void EditorWindow::clickedOpenProject()
{

    if (!promptUnsavedWork("Discard it?"))
        return;

    // Pop new file dialog, pass output to model
    QFileDialog fileDialog;
    fileDialog.setNameFilter(tr("Images (*.ssp)"));
    fileDialog.setDirectoryUrl(QDir::homePath());
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setViewMode(QFileDialog::Detail);

    QStringList filenames;
    if (fileDialog.exec()) {
        filenames = fileDialog.selectedFiles();
        QString file = filenames.at(0);
        emit openProject(file);
    }

}

void EditorWindow::clickedSaveProject()
{
    // Popup file dialog
    QFileDialog saveFileDialog;
    saveFileDialog.selectFile(ui->nameEdit->text());
    saveFileDialog.setDirectoryUrl(QDir::homePath());
    saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveFileDialog.setViewMode(QFileDialog::Detail);

    QStringList filenames;
    if (saveFileDialog.exec()) {
        // Get selected file
        filenames = saveFileDialog.selectedFiles();
        QString file = filenames.at(0);

        // Add .ssp if missing
        if (!file.contains(".ssp")){
            file.append(".ssp");
        }
        emit saveProject(file);
    }

}

void EditorWindow::clickedExportProject()
{

    QMessageBox reply;
    reply.setText("What type of export would you like?");
    reply.setIcon(QMessageBox::Question);
    QAbstractButton *singleFrameButton = reply.addButton("Current Frame Only", QMessageBox::YesRole);
    QAbstractButton *spriteSheetButton = reply.addButton("Spritesheet", QMessageBox::NoRole);
    reply.exec();

    // User canceled, give up
    if (reply.clickedButton() == singleFrameButton)
        saveSprite(false);
    else if (reply.clickedButton() == spriteSheetButton)
    {
        saveSprite(true);
    }

}

void EditorWindow::clickedExportLevel()
{

    emit levelLineEditChanged();

    // Popup file dialog
    QFileDialog saveFileDialog;
    saveFileDialog.selectFile(ui->nameEdit->text());
    saveFileDialog.setDirectoryUrl(QDir::homePath());
    saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveFileDialog.setViewMode(QFileDialog::Detail);

    QStringList filenames;
    if (saveFileDialog.exec()) {
        // Get selected file
        filenames = saveFileDialog.selectedFiles();
        QString file = filenames.at(0);

        // Add .ssp if missing
        if (!file.contains(".level")){
            file.append(".level");
        }
        emit saveLevel(file);
    }

}

bool EditorWindow::promptUnsavedWork(QString msg)
{

    // Check if file is unsaved, kinda a funny way to do this but it works.
    if (ui->saveIndicator->isVisible()) {

        QMessageBox::StandardButton reply = QMessageBox::question(this,
                    "Unsaved work!",
                    "You currently have unsaved work! " + msg, QMessageBox::Yes | QMessageBox::No);

        // User canceled, give up
        if (reply == QMessageBox::No)
            return false;

    }

    return true;
}

void EditorWindow::saveSprite(bool isSheet)
{

    // Popup file dialog
    QFileDialog saveFileDialog;
    saveFileDialog.selectFile(ui->nameEdit->text());
    saveFileDialog.setDirectoryUrl(QDir::homePath());
    saveFileDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveFileDialog.setViewMode(QFileDialog::Detail);

    QStringList filenames;

    if (saveFileDialog.exec()) {
        // Get selected file
        filenames = saveFileDialog.selectedFiles();
        QString file = filenames.at(0);

        // Add .png if missing
        if (!file.contains(".png")){
            file.append(".png");
        }

        emit exportProject(file, isSheet);
    }

}

void EditorWindow::updateFileDetails(QString filename, QString dimentions, QString frames)
{

    ui->nameEdit->setText(filename);
    ui->dimentionsEdit->setText(dimentions + "x" + dimentions);
    ui->framesEdit->setText(frames);
    this->setWindowTitle("Level Editor | " + filename + ".level");

}

void EditorWindow::clearFrameList()
{

    ui->listWidgetForFrames->clear();

}

void EditorWindow::setFrameSelection(int item)
{

    ui->listWidgetForFrames->setCurrentRow(item);

}

void EditorWindow::updateSaveIndicator(bool saved)
{
    ui->saveIndicator->setVisible(!saved);
}

void EditorWindow::updatePlayIndicator(bool playing)
{
    ui->playIndicator->setVisible(playing);
}
