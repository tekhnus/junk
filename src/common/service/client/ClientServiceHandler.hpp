#pragma once

#include <SFML/System.hpp>
#include <boost/signals2.hpp>
#include <common/logger/Logger.hpp>

#include <gen-cpp/ClientService.h>

#include <mutex>

namespace junk
{

class ClientServiceHandler : virtual public ClientServiceIf
{
public:
  ClientServiceHandler();
  ~ClientServiceHandler();

  int32_t connect();
  void getChanges(GameChanges& gameChanges, int32_t id);
  void move(int32_t id, const Vector2f& direction);
  void rotate(int32_t id, const Vector2f& direction);
  void fire(int32_t id, const Vector2f& direction);

  boost::signals2::signal<int32_t (), boost::signals2::last_value<int32_t> > connectSignal;
  boost::signals2::signal<GameChanges (int32_t), boost::signals2::last_value<GameChanges> > getChangesSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> moveSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> rotateSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> fireSignal;

private:
  std::mutex getChangesMutex;

}; // ClientServiceHandle

} // namespace junk
