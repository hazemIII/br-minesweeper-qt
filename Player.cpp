#include"Player.h"

Player::Player(QString name, CompeteGameLogic *gl){
    this->name=name;
    this->gl=gl;
    this->score=0;
}
int Player::getScore(){return score;}
QString Player::getName(){return name;}
void Player::increaseScore(){score++;}
void Player::clearScore(){score=0;}
