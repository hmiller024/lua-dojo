/// LevelEntity.h
///
/// This class serves as a base class for all items that can be added
/// to the scene
///
/// Author: Gavin Kerr
/// Date: April 25, 2023

#ifndef LEVELENTITY_H
#define LEVELENTITY_H

#include <QObject>
#include <QDebug>
#include <QPixmap>
#include <QString>

class LevelEntity
{

public:

    static const float CANVAS_SIZE;

    LevelEntity(float x, float y, float worldSize);

    virtual ~LevelEntity();

    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    /// @brief Gets the x positon of the entity
    float getX();


    /// @brief Gets the y postion of the entity
    float getY();


    /// @brief Gets the angle of the entity
    float getAngle();


    /// @brief Gets the world size the entity is in
    float getWorldSize();


    /// @brief Gets the world scale of the entity
    float getWorldScale();


    /// @brief Returns the pixmap of the entity
    virtual QPixmap& getPixmap();


    /// @brief Returns the ID of the entity
    long getID();


    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    /// @brief Sets the scaled x position of the Entity
    void setX(float x);


    /// @brief Sets the scaled y position of the Entity
    void setY(float y);


    /// @brief Sets the angle of the Entity
    void setAngle(float angle);


    /// @brief Set the world size of the Entity
    void setWorldSize(float size);


    /// @brief Sets the pixmap of the entity to the passed object
    /// and recalculates scale and positioning
    void setPixmap(QString pixmapPath);


    /// @brief Sets the pixmap to the passed pixmap
    void setPixmap(QPixmap& pixmap);


private:

    // Static counter for unique ID's for each entity
    static long ID;
    long localID;

    // Object variables
    float x;
    float y;
    float angle;
    float worldSize;
    float worldScale;

    QPixmap pixmap;

};

#endif // LEVELENTITY_H
