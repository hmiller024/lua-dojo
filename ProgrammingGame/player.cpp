#include "player.h"


Player::Player() : LevelEntity{0, 0, 0}
{

    init();

}

Player::Player(float x, float y, float worldSize) : LevelEntity{x, y, worldSize}
{

    init();

}

void Player::updateDirection()
{

    // Get angle of sprite
    int pAngle = this->getAngle();

    // Handle Sprite Change
    if (pAngle % 360 == 0) {
        setPixmap(rightPixmap);
    }
    if (pAngle % 360 == 90) {
        setPixmap(downPixmap);
    }
    if (pAngle % 360 == 180) {
        setPixmap(leftPixmap);
    }
    if (pAngle % 360 == 270) {
        setPixmap(upPixmap);
    }

}


void Player::init()
{

    // Load all sprites
    upPixmap.load(":/res/sprites/HaydenUp");
    downPixmap.load(":/res/sprites/HaydenDown");
    leftPixmap.load(":/res/sprites/HaydenLeft");
    rightPixmap.load(":/res/sprites/HaydenRight");
    onAir = false;
    updateDirection();

}
void Player::setAir(bool air)
{
    onAir = air;
}
bool Player::getAir()
{
    return onAir;
}



