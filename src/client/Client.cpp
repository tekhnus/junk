#include "Client.hpp"

namespace junk
{

Client::Client() : controller(view, model)
{
}

void Client::connectToServer(const std::string& serverIp, int port)
{
  model.connectToServer(serverIp, port);
}

} // namespace junk
