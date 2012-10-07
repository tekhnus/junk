#include "ClientModel.hpp"

namespace junk
{

ClientModel::ClientModel() : logger("client_model.log", "CLIENT_MODEL", true)
{
	logger << "ClientModel created";
}

ClientModel::~ClientModel()
{
	logger << "ClientModel destructed";
}

} // namespace junk