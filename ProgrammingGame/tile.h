/// tile.h
///
/// This file represents a tile for the game world
///
/// Author: Hayden Miller, Gavin Kerr
/// Date: April 15, 2023

#ifndef TILE_H
#define TILE_H

#include <QObject>
#include "levelentity.h"

class Tile : public LevelEntity
{

public:

    /// @brief Base Enum used to classify what type of tile a given
    /// tile is
    enum class TileType {
        AIR,
        GROUND,
        WALL,
        START,
        END,
        GEM
    };


    /// @brief Constructor
    Tile(float x, float y, float worldSize, QString type);


    /// @brief Returns the tile type of this tile
    /// @returns TileType
    Tile::TileType getTileType();


    /// @brief Set Collected state
    /// @param state
    void setCollected(bool state);


    /// @brief Get Collected state
    /// @returns collected
    bool getCollected();


private:

    TileType tileType;

    bool collected;

};

#endif // TILE_H
