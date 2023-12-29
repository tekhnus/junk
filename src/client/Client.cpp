#include "Client.hpp"

namespace junk {

Client::Client() {
  view.setModel(&model);
}

void Client::connectToServer(const std::string& serverIp, int port) {
  model.connectToServer(serverIp, port);
}

}  // namespace junk
