#include <bits/stdc++.h>
#include "Utrip.hpp"
#include "handlers.hpp"
#include "../server/server.hpp"

using namespace std;

int main(int argc, char **argv) {
  
	Utrip utrip(IO::read_hotels("hotels.csv"));
	
	try {
	Server server(5000);
	server.setNotFoundErrPage("static/404.html");
	
	server.get("/", new ShowPage("static/utrip.html"));
	server.get("/login", new ShowPage("static/login.html"));
	server.get("/signup", new ShowPage("static/signup.html"));
	server.post("/login", new LoginHandler(&utrip));
	server.post("/signup", new SignUpHandler(&utrip));

	server.get("/home", new ShowPage("static/home.html"));
	server.get("/home/wallet", new WalletHandler(&utrip));
	server.get("/home/hotels", new HotelsHandler(&utrip));
	server.get("/home/property", new PropertyHandler(&utrip));
	server.get("/home/logout", new LogoutHandler(&utrip));

	server.run();
	} catch (Server::Exception e) {
	cerr << e.getMessage() << endl;
	}
}
