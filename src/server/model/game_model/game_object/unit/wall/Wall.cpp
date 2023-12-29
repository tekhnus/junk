#include "Wall.hpp"
#include "common/utils/Convert.hpp"
#include "server/model/game_model/ServerGameModel.hpp"

#include <iostream>
#include <cassert>

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Wall, wall, WALL)

Wall::Wall()
{
}

Wall::~Wall()
{
}

WallPatch Wall::getWallPatch()
{
  WallPatch wallPatch;
  wallPatch.unitPatch = getUnitPatch();
  // dbg.debug("COrners size:", corns->size());
  for (const b2Vec2& corner : corns)
  {
    Vector2f vec;
    vec.x = corner.x;
    vec.y = corner.y;
    wallPatch.corners.push_back(vec);
  }
  return wallPatch;
}

void Wall::destroy()
{
  if (!isRemoved)
  {
    
    isRemoved = true;
  }
}

void Wall::onBulletHit(int , const std::string& )
{}

void Wall::init()
{
}

GameObjectType Wall::getType()
{
  return GameObjectType::WALL;
}

void Wall::setCorners(const std::vector<b2Vec2>& corners)
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  // bodyDef.position.Set(3.0f, 3.0f);

  body = model->world->CreateBody(&bodyDef);

  b2PolygonShape convexShape;
  /*
  for (int i = 0; i < corners.size(); ++i) {
    dbg.debug(corners.data()[i].x, corners.data()[i].y);
  }
  */
  convexShape.Set(corners.data(), corners.size());

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &convexShape;

  body->CreateFixture(&fixtureDef);
  body->GetUserData().pointer = reinterpret_cast<uintptr_t>((Unit*)this);

  corns = corners;
}


}}} // namespace junk::server::model
