#include "Bullet.hpp"

#include <iostream>
#include "server/model/game_model/ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bullet, bullet, BULLET)

Bullet::Bullet(Player* creator)
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

  double power = 100;
  body->ApplyLinearImpulse(b2Vec2(power * cos(angle), power*sin(angle)), body->GetWorldCenter());
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

  /*
    Set fields here
  */

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

}

void Bullet::startDestruction()
{
  if (!destroyInfo.isDestroyed)
  {
    destroyInfo.isDestroyed = true;
    destroyInfo.destroyCountdown = 5;
    cleanupTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(100);
  }
}

int Bullet::getType()
{
  return TYPE_BULLET;
}

}}} // namespace junk::server::model
