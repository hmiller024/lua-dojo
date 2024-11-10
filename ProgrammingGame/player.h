/// player.h
///
/// This file inherets the LevelEntity type to make a player
///
/// Author: Gavin Kerr
/// Data: April 26, 2023

#ifndef PLAYER_H
#define PLAYER_H

#include <levelentity.h>

class Player : public LevelEntity
{

public:

    Player();

    Player(float x, float y, float worldSize);

    void updateDirection();

    /// @brief getter for whether or not the player is standing on air, true if on air, false if not
    bool getAir();

    /// @brief setter for setting the status of the player on air
    /// @param true if on air, false if not.
    void setAir(bool);


private:

    void init();

    // All the different pixmaps needed
    QPixmap upPixmap;
    QPixmap downPixmap;
    QPixmap leftPixmap;
    QPixmap rightPixmap;
    bool onAir;

};

#endif // PLAYER_H
