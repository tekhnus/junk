#include "Player.hpp"

namespace junk {
namespace common {

Player::Player()
{
    maxHealth = 1;
    health = maxHealth;
}

Player::~Player()
{
}

int32_t Player::getHealth() const
{
    return health;
}

int32_t Player::getMaxHealth() const
{
    return maxHealth;
}

const std::string& Player::getName() const
{
    return name;
}

void Player::setHealth(int32_t health)
{
    this->health = health;
}

void Player::setMaxHealth(int32_t maxHealth)
{
    this->maxHealth = maxHealth;
}

void Player::setName(const std::string& name)
{
    this->name = name;
}

}} // namespace junk::common
