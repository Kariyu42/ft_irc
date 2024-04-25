#pragma once

# include "ACommand.hpp"
# include <deque>

class MODE : public ACommand {
private:
	typedef bool	(MODE::*modeFunction)(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	map<pair<string, bool>, modeFunction>	_modeMap;

	bool	INVITE(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	UNINVITE(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	TOPIC(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	UNTOPIC(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	KEY(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	UNKEY(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	OP(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	DEOP(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	LIMIT(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;
	bool	UNLIMIT(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const;

	bool			_addFlagToModeArgs(string const &modeArgs, bool flag) const;
	bool			_isEnoughModeArgs(string const &modeString, deque<string> const &modeArgs) const;
	deque<string>	_getModeArgs(vector<string> const &args) const;
	string const	_applyModeSetting(Server &server, Client *client, Channel *channel, vector<string> &args) const;

public:
	MODE();
	~MODE();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
