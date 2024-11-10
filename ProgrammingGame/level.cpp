#include "level.h"

Level::Level()
{

    // Default init data
    levelSize = levelTimeLimit = levelGemCount = levelLineLimit = levelInstructionLimit = collectedGems = 0;
    levelAuthor = levelTitle = levelType = levelDescription = levelObjectives = levelHints = levelPreWrittenCode = "";
    isValid = false;

}

void Level::read(const QJsonObject &json)
{

    // Load required data in
    levelSize = json["levelSize"].toInt();
    levelGemCount = json["levelGemCount"].toInt();
    levelAuthor = json["levelAuthor"].toString();
    levelTitle = json["levelTitle"].toString();
    levelType = json["levelType"].toString();
    levelObjectives = json["levelObjectives"].toString();
    levelDescription = json["levelDescription"].toString();
    levelHints = json["levelHints"].toString();
    levelPreWrittenCode = json["levelPreWrittenCode"].toString();

    // Load optional modifiers
    levelTimeLimit = json["levelTimeLimit"].toInt();
    levelLineLimit = json["levelLineLimit"].toInt();
    levelInstructionLimit = json["levelInstructionLimit"].toInt();

    // Load and create all tiles
    worldMap.clear();

    QJsonArray levelData = json["levelData"].toArray();

    for (int i = 0; i < levelData.size(); i++) {

        // Make new tile and add it
        QJsonArray tileData = levelData.at(i).toArray();
        Tile newTile (tileData.at(0).toInt(), tileData.at(1).toInt(),
                     levelSize, tileData.at(2).toString());

        // Check if tile is start tile and set player location
        if (newTile.getTileType() == Tile::TileType::START) {
            playerStart = QPoint(newTile.getX(), newTile.getY());
            playerStartAngle = 0;
            player.setX(newTile.getX());
            player.setY(newTile.getY());
            player.setWorldSize(levelSize);
        }
        if(newTile.getTileType() == Tile::TileType::END)
        {
            levelEnd.setX(newTile.getX());
            levelEnd.setY(newTile.getY());
        }

        worldMap.push_back(newTile);
    }

    // Set valid to true once done loading
    isValid = true;
}

void Level::resetLevel()
{
    player.setX(playerStart.x());
    player.setY(playerStart.y());
    player.setAngle(playerStartAngle);

    // Reset gems
    collectedGems = 0;
    for (unsigned long i = 0; i < worldMap.size(); i++) {
        worldMap.at(i).setCollected(false);
    }

    player.setAir(false);
}

int Level::getCollectedGemCount()
{
    return collectedGems;
}

QString Level::processMove(QString move)
{

    // Allocate string for move message
    QString returnString;

    // Get current data
    int pAngle = player.getAngle();
    QPoint target(player.getX(), player.getY());

    if (move == "forward") {
        if(abs(pAngle) % 360 ==  0)
        {
            target.setX(target.x() + 1);
        }
        if(abs(pAngle) % 360 == 90)
        {
            target.setY(target.y() + 1);
        }
        if(abs(pAngle) % 360 == 180)
        {
            target.setX(target.x() - 1);
        }
        if(abs(pAngle) % 360 == 270)
        {
            target.setY(target.y() - 1);
        }

        if(checkCollision(target) == false)
        {
            player.setX(target.x());
            player.setY(target.y());
        } else {
            returnString = "Bonk! You hit a wall!";
        }

    } else if (move == "right") {
        player.setAngle(pAngle + 90);

    } else if (move == "left") {
        player.setAngle(pAngle + 270);

    } else if (move == "gem") {

        if (checkGem(target)) {
            returnString = "You got a gem!";
            collectedGems++;
        } else {
            returnString = "No gem here!";
        }

    }

    // Update backing sprite
    player.updateDirection();
    return returnString;

}

bool Level::checkCollision(QPoint target)
{
    foreach(Tile t, worldMap)
    {
        if(t.getX() == target.x() && t.getY() == target.y())
        {
            if(t.getTileType() == Tile::TileType::WALL)
            {
                return true;
            }
            if(t.getTileType() == Tile::TileType::GROUND || t.getTileType() == Tile::TileType::START || t.getTileType() == Tile::TileType::END || t.getTileType() == Tile::TileType::GEM)
            {
                return false;
            }
        }
    }
    player.setAir(true);
    return false;
}

bool Level::checkGem(QPoint target)
{
    for (unsigned long i = 0; i < worldMap.size(); i++) {
        Tile& t = worldMap.at(i);
        if (t.getX() == target.x() && t.getY() == target.y()) {
            if (t.getTileType() == Tile::TileType::GEM && t.getCollected() == false) {
                t.setCollected(true);
                return true;
            }
        }
    }
    return false;

}

std::vector<Tile> &Level::getLevelMap()
{
    return worldMap;
}

QPoint Level::getEndPos()
{
    return levelEnd;
}
Player &Level::getPlayer()
{
    return player;
}

int Level::getLevelTimeLimit()
{
    return levelTimeLimit;
}

int Level::getLevelLineLimit()
{
    return levelLineLimit;
}

int Level::getLevelInstructionLimit()
{
    return levelInstructionLimit;
}

int Level::getLevelGemCount()
{
    return levelGemCount;
}

int Level::getLevelStartingRotation()
{
    return levelStartingRotation;
}

QString Level::getLevelAuthor()
{
    return levelAuthor;
}

QString Level::getLevelTitle()
{
    return levelTitle;
}

QString Level::getLevelType()
{
    return levelType;
}

QString Level::getLevelObjectives()
{
    return levelObjectives;
}

QString Level::getLevelDescription()
{
    return levelDescription;
}

QString Level::getLevelHints()
{
    return levelHints;
}

QString Level::getPreWrittenCode()
{
    return levelPreWrittenCode;
}

int Level::getLevelSize()
{
    return levelSize;
}
