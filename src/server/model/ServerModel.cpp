#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include "ServerModel.hpp"

namespace junk
{

ServerModel::ServerModel() : logger("server_model.log", "SERVER_MODEL", true)
{
	/*gameModel.subscribeForPositionUpdatedSignal(sigc::mem_fun(&networkModel, 
		&ServerNetworkModel::clientPositionUpdated));

	gameModel.subscribeForDirectionUpdatedSignal(sigc::mem_fun(&networkModel, 
		&ServerNetworkModel::clientDirectionUpdated));*/

	logger << "ServerModel created";
}

ServerModel::~ServerModel()
{
	logger << "ServerModel destroyed";
}

} // namespace junk