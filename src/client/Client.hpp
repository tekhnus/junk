#pragma once

#include "client/model/ClientModel.hpp"
#include "client/view/ClientView.hpp"

namespace junk {

class Client {
 public:
  Client();

  void run();

  /*
   Created only for testing, will be removed and invoked by controller when view
   sends signal to connect with appropriate params
   */
  void connectToServer(const std::string& serverIp, int port);

 private:
  client::view::ClientView view;
  client::model::ClientModel model;
};  // Client

}  // namespace junk
