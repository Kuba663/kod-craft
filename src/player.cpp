#include "player.h"
#include "world.h"

Player* player;

Player::Player() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

void Player::draw() {
    this->dimension->draw();
}

void Player::setDimension(Dimension* dimension) {
    this->dimension = dimension;
}

void Player::setDimension(std::string dimension) {
    this->setDimension(world->findDimension(dimension));
}
