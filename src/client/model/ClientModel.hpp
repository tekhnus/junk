#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <logger/Logger.hpp>

namespace junk
{

class ClientModel
{
public:
  explicit ClientModel();
  ~ClientModel();

private:

  Logger logger;
  
}; // ClientModel

} // namespace junk