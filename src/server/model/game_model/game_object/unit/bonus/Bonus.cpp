#include "Bonus.hpp"
#include "common/utils/Convert.hpp"

#include "server/model/game_model/ServerGameModel.hpp"

#include <iostream>
#include <cmath>

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bonus, bonus, BONUS)

Bonus::Bonus(b2World *world)
{
    srand(43);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(rand() % 36, rand() % 36);

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
    body->ApplyLinearImpulse(b2Vec2(10, 10), body->GetWorldCenter());

    bonusType = 0;
}

Bonus::~Bonus()
{
}

void Bonus::process()
{
    GameObject::process();
    b2Vec2 pos = body->GetWorldCenter();
    position.x = pos.x;
    position.y = pos.y;
    dbg .debug("Processing bonus ", pos.x, " ", pos.y);
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
      destroyInfo.destroyCountdown = 2;
      cleanupTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
    }
}

int Bonus::getType()
{
    return TYPE_BONUS;
}

void Bonus::init()
{

}

}}} // namespace junk::server::model

