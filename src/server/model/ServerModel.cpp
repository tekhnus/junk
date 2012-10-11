#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <logger/Logger.hpp>
#include "ServerModel.hpp"

namespace junk
{

ServerModel::ServerModel() : logger("server_model.log", "SERVER_MODEL", true)
{
	logger << "ServerModel created";
}

ServerModel::~ServerModel()
{
	logger << "ServerModel destroyed";
}

} // namespace junk