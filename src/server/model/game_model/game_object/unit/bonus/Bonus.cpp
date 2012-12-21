#include "Bonus.hpp"
#include "common/utils/Convert.hpp"

#include "server/model/game_model/ServerGameModel.hpp"

#include <iostream>
#include <cmath>

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bonus, bonus, BONUS)

Bonus::Bonus(b2World *world, sf::Vector2f bornPosition, int newBonusType)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(bornPosition.x, bornPosition.y);

    body = world->CreateBody(&bodyDef);
    body->SetUserData((Unit*)this);

    b2CircleShape circleShape;
    circleShape.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 2.0f;
    fixtureDef.restitution = 0.7f;

    body->CreateFixture(&fixtureDef);
    body->SetLinearDamping(0.1);
    // body->ApplyLinearImpulse(b2Vec2(10, 10), body->GetWorldCenter());

    this->bonusType = newBonusType;
}

Bonus::~Bonus()
{
}

void Bonus::process()
{
    GameObject::process();
    b2Vec2 pos = body->GetWorldCenter();
    if (position.x != pos.x || position.y != pos.y)
    {
      position.x = pos.x;
      position.y = pos.y;
      setChanged();
    }
}

BonusPatch Bonus::getBonusPatch()
{
    BonusPatch bonusPatch;
    bonusPatch.unitPatch = getUnitPatch();

    /*
      Set fields here
    */

    bonusPatch.bonusType = bonusType;

    return bonusPatch;
}

void Bonus::startDestruction()
{
    if (!destroyInfo.isDestructing)
    {
      destroyInfo.isDestructing = true;
      destroyTime = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(10);
      cleanupTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
    }
    setChanged();
}

GameObjectType Bonus::getType()
{
    return GameObjectType::BONUS;
}

void Bonus::init()
{

}

}}} // namespace junk::server::model

