#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <logger/Logger.hpp>

namespace junk
{

class ServerModel
{
public:
  explicit ServerModel();
  ~ServerModel();

private:
	//ClientService networkChannel	;

  Logger logger;
  
}; // ServerModel

} // namespace junk