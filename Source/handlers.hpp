#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "Utrip.hpp"
#include "../server/server.hpp"

class LoginHandler : public RequestHandler {
public:
	LoginHandler(Utrip* _utrip){ utrip = _utrip; }
	Response* callback(Request *);

private:
	Utrip* utrip;
};

class SignUpHandler : public RequestHandler {
public:
	SignUpHandler(Utrip* _utrip) { utrip = _utrip; }
	Response* callback(Request *);

private:
	Utrip* utrip;
};

class WalletHandler : public RequestHandler {
public:
	WalletHandler(Utrip* _utrip) { utrip = _utrip; }
	Response* callback(Request *);

private:
	Utrip* utrip;
};

class HotelsHandler : public RequestHandler {
public:
	HotelsHandler(Utrip* _utrip) { utrip = _utrip; }
	Response* callback(Request *);

private:
	Utrip* utrip;
};

class PropertyHandler : public RequestHandler {
public:
	PropertyHandler(Utrip* _utrip) { utrip = _utrip; }
	Response* callback(Request *);

private:
	Utrip* utrip;
	std::vector<std::string> amenities_parser(std::string amenities);
};

class LogoutHandler : public RequestHandler {
public:
	LogoutHandler(Utrip* _utrip){ utrip = _utrip; }
	Response* callback(Request *);
private:
	Utrip* utrip;
};

#endif
