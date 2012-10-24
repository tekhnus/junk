#pragma once

#include "client/view/ClientView.hpp"
#include "client/model/ClientModel.hpp"
#include "client/controller/ClientController.hpp"

namespace junk
{

class Client
{
public:
	Client();

	void run();

	/*
	 Created only for testing, will be removed and invoked by controller when view sends
	 signal to connect with appropriate params
	*/
  void connectToServer(const std::string& serverIp, int port);

private:
	ClientView view;
	ClientModel model;
	ClientController controller;
}; // Client

} // namespace junk