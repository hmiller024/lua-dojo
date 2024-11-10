#include "tile.h"

Tile::Tile(float x, float y, float worldSize, QString type) : LevelEntity{x, y, worldSize}
{

    if (type == "ground") {
        tileType = Tile::TileType::GROUND;
        setPixmap(":/res/tiles/oak_planks.png");
    } else if (type == "wall") {
        tileType = Tile::TileType::WALL;
        setPixmap(":/res/tiles/cobblestone.png");
    } else if (type == "start") {
        tileType = Tile::TileType::START;
        setPixmap(":/res/tiles/light_blue_shulker_box.png");
    } else if (type == "end") {
        tileType = Tile::TileType::END;
        setPixmap(":/res/tiles/lime_shulker_box.png");
    } else if (type == "gem") {
        tileType = Tile::TileType::GEM;
        setPixmap(":/res/tiles/amethyst_block.png");
    } else {
        tileType = Tile::TileType::AIR;
    }

    collected = false;

}

Tile::TileType Tile::getTileType()
{
    return tileType;
}

void Tile::setCollected(bool state)
{
    if (tileType == Tile::TileType::GEM) {
        collected = state;

        if (collected) {
            setPixmap(":/res/tiles/oak_planks.png");
        } else {
            setPixmap(":/res/tiles/amethyst_block.png");
        }
    }

}

bool Tile::getCollected()
{
    return collected;
}
