#include <bits/stdc++.h>
#include "handlers.hpp"

using namespace std;

Response* LoginHandler::callback(Request *req){
	Response* res = Response::redirect("/home");
	string username = req->getBodyParam("username");
	string pass = req->getBodyParam("password");

	utrip->login(username, pass);
	res->setSessionId(username);
	return res;
}

Response* SignUpHandler::callback(Request *req){
	string username = req->getBodyParam("username");
	string pass = req->getBodyParam("password");
	string email = req->getBodyParam("email");
	
	if(pass != req->getBodyParam("confirm-password"))
		throw Server::Exception("Confirm password doesn't match the original");
	
	utrip->signup(username, pass, email);
	return Response::redirect("/login");
}	

Response* WalletHandler::callback(Request *req){
	User* user = utrip->get_current() == NULL ? throw Server::Exception("No such session, Not logined yet") : utrip->get_current();
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	string query = req->getQueryParam("charge");
	if(query != ""){
		if(stoi(query) > 0){
			user->update_wallet(stoi(query));
		}
		else
			throw Server::Exception("charge amount cannot be non positive");
	}

	stringstream body;
	body
	<<"	<!DOCTYPE html>" << endl
	<<"	<html>" << endl
	<<"	<body style='text-align: center;'>" << endl
	<<"		<div style='background-color:cornflowerblue; padding: 1%; max-width: 300px; border-radius: 6px; margin: auto;'>" << endl
	<<"			<form action='/home/wallet' method='GET'>" << endl
	<<"				<h4>Wallet</h4> <br>" << endl
	<<"				<p> Current account balance : "<< user->get_wallet().back() <<" </p>" << endl
	<<"				<input name='charge' type='text' placeholder='charge amount' style='display: block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;'/> <br />" << endl
	<<"				<button type='submit' style='display:block; width: 100%; padding: 7px;' >Submit</button>" << endl
	<<"			</form>" << endl
	<<"		</div>"<< endl
	<<"		<br>" << endl
	<<"		<div style='background-color:crimson; padding: 1%; max-width: 300px; border-radius: 6px; margin: auto;'>" << endl
	<<"			<form action='/home/logout' method='GET'>" << endl
	<<"				<button type='submit' style='display:block; width: 100%; padding: 7px;' > Logout </button>" << endl
	<<"			</form>" << endl
	<<"		</div>" << endl
	<<"	</body>" << endl
	<<"	</html>" << endl;

	

	res->setBody(body.str());
	return res;

}

Response* HotelsHandler::callback(Request *req){
	User* user = utrip->get_current() == NULL ? throw Server::Exception("No such session, Not logined yet") : utrip->get_current();
	cout << user->get_name() << endl;
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	HotelTable hotels = utrip->get_hotels();

	int min_star = req->getQueryParam("min_star") == "" ? 1 : stoi(req->getQueryParam("min_star"));
	int max_star = req->getQueryParam("max_star") == "" ? 5 : stoi(req->getQueryParam("max_star"));

	if(min_star > max_star)
		throw Server::Exception("min can't be bigger than max");

	Filter* filter = new Star(min_star, max_star);
	hotels = filter->set_filter(hotels);


	stringstream body;
	body
	<< "<!DOCTYPE html>" << endl
	<<" <html>" << endl 
	<<"		<head>" << endl
	<<"			<style>" << endl
	<<"			table, th, td {" << endl
	<<"			border: 1px solid black;" << endl
	<<"			border-collapse: collapse;" << endl
	<<"			table-layout: fixed;" << endl
	<<"			}" << endl
	<<"			th, td {" << endl
	<<"			padding: 10px;" << endl
	<<"			font-size: 25px;" << endl
	<<"			text-align: left;" << endl
	<<"			}" << endl
	<<"			</style>" << endl
	<<"		</head>" << endl
	<<"		<div style='background-color:cornflowerblue; padding: 1%; max-width: 200px; border-radius: 6px; margin: auto'>" << endl
	<<"			<form action='/home/hotels' method='GET'>" << endl
	<<"				<h3> Filter stars  </h3>" << endl
	<<"				min star: <input name='min_star' type='text' placeholder='min star' value='" << min_star << "' style='display: block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;' />" << endl
	<<"				max star: <input name='max_star' type='text' placeholder='max star' value='" << max_star << "' style='display: block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;'/> <br />" << endl
	<<"				<button type='submit' style='display:block; width: 100%; padding: 7px;' >Set</button>" << endl
	<<"			</form>" << endl
	<<"			<br> " << endl
	<<"			<form action='/home/wallet' method='GET'>" << endl
	<<"				<button type='submit' style='display:block; width: 100%; padding: 7px;' >Go to Wallet</button>" << endl
	<<"			</form>" << endl
	<<"		</div>" << endl
	<<"		<br>" << endl
	<<"		<div style='background-color:crimson; padding: 0.5%; max-width: 200px; border-radius: 6px; margin: auto;'> " << endl
    <<"       <form action='/home/logout' method='GET'> " << endl
    <<"            <button type='submit' style='display:block; width: 100%; padding: 7px;' > Logout </button> " << endl
    <<"        </form> " << endl
    <<"    </div> <br> " << endl
	<<"		<body>" << endl
	<<"			<table style='width: 100%;'>" << endl
	<<"				<tr>" << endl
	<<"					<th> property name </th>" << endl
	<<"					<th> star rating </th>" << endl
	<<"					<th> city </th>" << endl
	<<"					<th> image </th>" << endl
	<<"				</tr>" << endl;
	
	for(auto &hotel : hotels){
	body 
		<<"				<tr>" << endl
		<<"					<td> <a href='/home/property?id="<< hotel.get_uid() <<" '>" << hotel.get_name() << "</a> </td>" << endl
		<<"					<td> " << hotel.get_star() << " </td> " << endl
		<<"					<td> " << hotel.get_city() << " </td>" << endl
		<<"					<td> <img src=' "<< hotel.get_img() << " ' style='width: 30%;'> </td>" << endl
		<<"				</tr>" << endl;
	}

	body 
	<<"			</table>" << endl
	<<"		</body>" << endl
	<<"	</html>" << endl;
	
	res->setBody(body.str());
	return res;
}

Response* PropertyHandler::callback(Request *req){
	User* user = utrip->get_current() == NULL ? throw Server::Exception("No such session, Not logined yet") : utrip->get_current();
	Response* res = new Response;
	res->setHeader("Content-Type", "text/html");
	string uid = req->getQueryParam("id");
	Hotel* hotel = utrip->find_hotel(uid);
	vector<string> amenities = amenities_parser(hotel->get_amenities());
	Quantity quantity = hotel->get_quantity();
	Price price = hotel->get_price();

	stringstream body;
	body 
	<<"	<!DOCTYPE html>	" << endl
	<<"	<html> " << endl
	<<"		<body style='font-size: 30px;'> " << endl
	<<"			<style> " << endl
	<<"				table, th, td { " << endl
	<<"				border: 1px solid black; " << endl
	<<"				border-collapse: collapse; " << endl
	<<"				table-layout: fixed; " << endl
	<<"				} " << endl
	<<"				th, td { " << endl
	<<"				padding: 10px; " << endl
	<<"				font-size: 25px; " <<endl 
	<<"				text-align: left; " << endl 
	<<"				} " << endl
	<<"				h3 { display: inline; }" << endl
	<<"			</style> " << endl 
	<<"			<img src='"<< hotel->get_img() << "' style='width: 30%; height: 30%;'> <br> " << endl
	<<"			<h3> property name : </h3> "<< hotel->get_name() << " <br> " << endl 
	<<"			<h3> hotel overview : </h3> "<< hotel->get_overview() << " <br> <br> " << endl
	<<"			<h3> property amentities : </h3> <br> " << endl
	<<"			<ul> " << endl;

	for(int i=0; i< amenities.size(); i++){
		body
		<<"				<li> "<< amenities[i] << " </li> " << endl;
	}
	
	body
	<<"			</ul> " << endl
	<<"			<h3> city : </h3> "<< hotel->get_city() << " <br> <br> " << endl
	<<"			<table style='width: 100%; border: 1px solid black; border-collapse: collapse; table-layout: fixed;'> " << endl
	<<"				<tr> " << endl
	<<"					<th>&nbsp;</th> " << endl 
	<<"					<th> standard rooms </th> " <<endl  
	<<"					<th> deluxe rooms </th> " << endl
	<<"					<th> luxury rooms </th> " << endl
	<<"					<th> premium rooms </th> " << endl 
	<<"				</tr> " << endl
	<<"				<tr> " << endl
	<<"					<td> quantity </td> " << endl
	<<"					<td> "<< quantity.standard << " </td> " << endl
	<<"					<td> "<< quantity.deluxe << " </td> " << endl
	<<"					<td> "<< quantity.luxury << " </td> " << endl
	<<"					<td> "<< quantity.premium << " </td> " << endl
	<<"				</tr> " << endl
	<<"				<tr> " << endl
	<<"					<td> price </td> " << endl
	<<"					<td> "<< price.standard << " </td> " << endl
	<<"					<td> "<< price.deluxe << " </td> " << endl
	<<"					<td> "<< price.luxury << " </td> " << endl
	<<"					<td> "<< price.premium << " </td> " << endl
	<<"				</tr> " << endl
	<<"			</table> " << endl
	<<"		</body> " << endl
	<<"	</html> " << endl;

	res->setBody(body.str());
	return res;
}

vector<string> PropertyHandler::amenities_parser(string amenities){
	string word;
    stringstream sstream(amenities);
    vector<string> row;
    
    while (getline(sstream, word, '|')){
        row.push_back(word);
    }

	return row;
}

Response* LogoutHandler::callback(Request *req){
	Response *res = new Response;
	utrip->delete_current();
	return res->redirect("/");
}