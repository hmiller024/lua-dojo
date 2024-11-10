#include "levelentity.h"

long LevelEntity::ID = 0;
const float LevelEntity::CANVAS_SIZE = 550.0f;

LevelEntity::LevelEntity(float x, float y, float worldSize)
{

    // Load data into local storage
    this->x = x;
    this->y = y;
    this->angle = 0.0f;
    this->worldSize = worldSize;

    // Calculate worldScale
    worldScale = CANVAS_SIZE / worldSize;

    // Increment ID
    localID = ID++;

}

LevelEntity::~LevelEntity()
{

}

float LevelEntity::getX()
{
    return x;
}

float LevelEntity::getY()
{
    return y;
}

float LevelEntity::getAngle()
{
    return angle;
}

float LevelEntity::getWorldSize()
{
    return CANVAS_SIZE;
}

float LevelEntity::getWorldScale()
{
    return worldScale;
}

QPixmap &LevelEntity::getPixmap()
{
    return pixmap;
}

long LevelEntity::getID()
{
    return localID;
}

void LevelEntity::setX(float x)
{
    this->x = x;
}

void LevelEntity::setY(float y)
{
    this->y = y;
}

void LevelEntity::setAngle(float angle)
{
    this->angle = angle;
}

void LevelEntity::setWorldSize(float size)
{
    this->worldSize = size;
    worldScale = CANVAS_SIZE / worldSize;
}

void LevelEntity::setPixmap(QString pixmapPath)
{

    // Load new pixmap
    bool loaded = pixmap.load(pixmapPath);
    if (!loaded) {
        pixmap.load(":/res/sprites/missingTexture.png");
        qDebug() << "Failed to load resource" << pixmapPath;
    }

    // Set scale for new pixmap
    worldScale = CANVAS_SIZE / worldSize;

}

void LevelEntity::setPixmap(QPixmap &pixmap)
{
    this->pixmap = pixmap;
    worldScale = CANVAS_SIZE / worldSize;
}
