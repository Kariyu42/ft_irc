#include "commands/CAP.hpp"
#include "Server.hpp"

CAP::CAP() {}

CAP::~CAP() {}

void	CAP::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	static_cast<void>(args);
	static_cast<void>(client);
}
