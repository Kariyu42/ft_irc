#include "Server.hpp"

bool	Server::_signalReceived = false;

void Server::signalHandler(int signum)
{
	(void)signum;
	_signalReceived = true;
	//! when signal is received, need to call QUIT command and close all file descriptors
}

void Server::closeFileDescriptors() {
	_clients.closeFileDescriptors();
	if (_sockfd != -1) {
		close(_sockfd);
	}
}

void Server::removePollFd(int fd) {
	for (size_t i = 0; i < _pollFds.size(); i++) {
		if (_pollFds[i].fd == fd) {
			_pollFds.erase(_pollFds.begin() + i);
			break;
		}
	}
}

void	Server::runServer() {
	signal(SIGINT, &signalHandler);
	signal(SIGQUIT, &signalHandler);

	// Run the server, must handle signals
	while (_signalReceived == false) {
		// Poll for incoming events
		if (poll(&_pollFds[0], _pollFds.size(), -1) < 0) {
			throw runtime_error("Failed at trying to run the server\n");
		}
		// Check if the server socket has an event
		for (size_t i = 0; i < _pollFds.size(); i++) {
			if (_pollFds[i].revents & POLLIN) {
				if (_pollFds[i].fd == _sockfd) {
					acceptNewClient();
				} else {
					receiveData(_pollFds[i].fd);
				}
			}
		}
	}

	//! send broadcast message to all clients that server is shutting down using QUIT command
	
	closeFileDescriptors(); // Close the server socket and all client sockets if they are still open
}
