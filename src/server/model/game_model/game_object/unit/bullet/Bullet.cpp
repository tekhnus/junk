#include "Bullet.hpp"

#include <iostream>
#include "server/model/game_model/ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bullet, bullet, BULLET)

Bullet::Bullet(Player* creator, int type)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;

  double angle = creator->body->GetAngle();
  double rad = 1.5;
  bodyDef.position.Set(creator->position.x + rad * cos(angle),
    creator->position.y + rad * sin(angle));

  bodyDef.bullet = true;

  body = creator->model->world->CreateBody(&bodyDef);
  body->SetUserData((Unit*)this);

  b2CircleShape circleShape;
  circleShape.m_radius = 1.0f / 7;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &circleShape;
  fixtureDef.density = 2.0f;
  fixtureDef.restitution = 0.7f;

  body->CreateFixture(&fixtureDef);
  body->SetLinearDamping(0.1);

  this->type = type;

  double power = 100;
  body->ApplyLinearImpulse(b2Vec2(power * cos(angle), power*sin(angle)), body->GetWorldCenter());

  setOwner(creator->getName());
}

Bullet::~Bullet()
{
}

void Bullet::init()
{}

BulletPatch Bullet::getBulletPatch()
{
  BulletPatch bulletPatch;
  bulletPatch.unitPatch = getUnitPatch();
  bulletPatch.owner = getOwner();

  /*
    Set fields here
  */

  bulletPatch.type = type;
  return bulletPatch;
}

void Bullet::process() {

  GameObject::process();
  if (lifetime == 50) {
    startDestruction();
  }
  b2Vec2 pos = body->GetWorldCenter();
  position.x = pos.x;
  position.y = pos.y;
  setChanged();
}

void Bullet::startDestruction()
{
  if (!destroyInfo.isDestructing)
  {
    destroyInfo.isDestructing = true;
    destroyTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
    cleanupTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
  }
  setChanged();
}

GameObjectType Bullet::getType()
{
  return GameObjectType::BULLET;
}

const std::string& Bullet::getOwner() const
{
    return owner;
}

void Bullet::setOwner(const std::string& owner)
{
    this->owner = owner;
}

}}} // namespace junk::server::model
