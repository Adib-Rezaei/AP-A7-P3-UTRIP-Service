#include <bits/stdc++.h>
#include "Utrip.hpp"
#include "../server/server.hpp"
using namespace std;


void Utrip::signup(string username, string pass, string email){
    
    for(auto &user : users)
        if(!user->check_signup(email, username))
            throw Server::Exception("This user already exists with same username or email");

    User* user = new User(email, username, hashing(pass));
    users.push_back(user);
    current = user;
}

string Utrip::hashing(std::string password){
    hash<string> myhash;
    return to_string(myhash(password));
}

void Utrip::login(string username, string pass){
    
    for(auto &user : users){
        if(user->check_login(username, hashing(pass))){
            current = user;
            return;
        }
    }
    throw Server::Exception("User not found");
}

User* Utrip::find_user(std::string username){
    for(auto & user : users){
        if(user->get_name() == username)
            return user;
    }
    throw Server::Exception("Not found such session/ Not logined yet");
}

void Utrip::logout(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    current = NULL;
    for(auto &_filter : Filters)
        _filter = NULL;
    cout << "OK" << endl;
}

void Utrip::wallet(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    string word;
    sstream >> word >> word >> word;
    if(stoi(word) <= 0)
        throw ImportException(BAD_REQUEST);
    
    current->update_wallet(stoi(word));
    cout << "OK" << endl;
}

void Utrip::get_wallet(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    string count;
    sstream >> count >> count >> count;
    int size = current->get_wallet().size();
    for(int i=1; i<= stoi(count); i++){
        if(size - i < 0)
            break;
        cout << current->get_wallet()[size - i] << endl;
    }
}

void Utrip::get_hotels(stringstream &sstream){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);

    if(sstream.eof()){
        filter_hotels();
        return;
    }

    string word;
    sstream >> word >> word >> word;
    for(auto &hotel : hotels){
        if(word == hotel.get_uid()){
            hotel.print();
            return;
        }
    }
    throw ImportException(NOT_FOUND);
}

void Utrip::filters(stringstream &sstream){
    string word;
    sstream >> word >> word;
    if(word == "city"){
        city_filter(sstream);
    }
    else if(word == "min_star" || word == "max_star"){
        string command = sstream.str();
        stringstream ss(command.substr(command.find('?')+2));
        star_filter(ss);
    }
    else if(word == "min_price" || word == "max_price"){
        string command = sstream.str();
        stringstream ss(command.substr(command.find('?')+2));
        cost_filter(ss);
    }
    else if(word == "type" || word == "quantity" || word == "chech_in" || word == "check_out"){
        string command = sstream.str();
        stringstream ss(command.substr(command.find('?')+2));
        specific_filter(ss);
    }
    else 
        throw ImportException(BAD_REQUEST);
}

void Utrip::filter_hotels(){
    if(current == NULL)
        throw ImportException(PERMISSION_DENIED);
    
    HotelTable selected = hotels;
    for(int i=0; i< Filters.size(); i++){
        if(Filters[i] == NULL)
            continue;
        selected = Filters[i]->set_filter(selected);
    }

    Filter::print_hotels(selected);
}

void Utrip::city_filter(stringstream &sstream){
    string word;
    getline(sstream, word);
    word.erase(word.begin());
    City* new_filter = new City(word);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::star_filter(stringstream &sstream){
    string word;
    int min, max;
    for(int i=0; i< 2; i++){
        sstream >> word; 
        if(word == "min_star"){
            sstream >> min;
        }
        else if(word == "max_star"){
            sstream >> max;
        }
        else
            throw ImportException(BAD_REQUEST);
    }
    if(min > max || min < 1 || max <1 || min > 5 || max > 5)
        throw ImportException(BAD_REQUEST);
    
    Star* new_filter = new Star(min, max);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::cost_filter(stringstream &sstream){
    string word;
    double min, max;
    for(int i=0; i< 2; i++){
        sstream >> word; 
        if(word == "min_price"){
            sstream >> min;
        }
        else if(word == "max_price"){
            sstream >> max;
        }
        else
            throw ImportException(BAD_REQUEST);
    }
    if(min < 0 || max < 0 || min > max)
        throw ImportException(BAD_REQUEST);
    
    Cost* new_filter = new Cost(min, max);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::specific_filter(stringstream &sstream){
    string word, type;
    int quantity, in, out;
    for(int i=0; i< 4; i++){
        sstream >> word;
        if(word == "type"){
            sstream >> type;
        }
        else if(word == "quantity"){
            sstream >> quantity;
        }
        else if(word == "check_in"){
            sstream >> in;
        }
        else if(word == "check_out"){
            sstream >> out;
        }
        else
            throw ImportException(BAD_REQUEST);
    }
    if(in <1 || out > 30 || in > out)
        throw ImportException(BAD_REQUEST);
    
    Specific* new_filter = new Specific(type, quantity, in, out);
    Filters[new_filter->get_id()-1] = new_filter;
    cout << "OK" << endl;
}

void Utrip::reserve_room(RoomTable &rooms, int in, int out){
    for(auto &room : rooms)
        room->reserve(in, out);
}

void Utrip::comments(stringstream &sstream){
    string word, uid, comment;
    sstream >> word;
    for(int i=0; i<2; i++){
        sstream >> word;
        if(word == "hotel"){
            sstream >> uid;
        }
        else if(word == "comment"){
            sstream >> comment;
        }
        else 
            throw ImportException(BAD_REQUEST);
    }
    Hotel* hotel = find_hotel(uid);
    if(hotel == NULL)
        throw ImportException(NOT_FOUND);
    hotel->set_comment(current->get_name() + ": " + comment);
    cout << "OK" << endl;
}

void Utrip::get_comments(stringstream &sstream){
    string word, uid;
    sstream >> word >> word;
    if(word != "hotel")
        throw ImportException(BAD_REQUEST);
    sstream >> uid;
    Hotel* hotel = find_hotel(uid);
    if(hotel == NULL)
        throw ImportException(NOT_FOUND);
    hotel->print_comments();
}

Hotel* Utrip::find_hotel(string uid){
    for(auto &hotel : hotels)
        if(hotel.get_uid() == uid)
            return &hotel;
    return NULL;
}

void Utrip::ratings(stringstream &sstream){
    string word, uid;
    Ratings ratings;
    sstream >> word;
    for(int i=0; i<7; i++){
        sstream >> word;
        if(word == "hotel")
            sstream >> uid;
        else if(word == "location")
            sstream >> ratings.location;
        else if(word == "cleanliness")
            sstream >> ratings.cleanlines;
        else if(word == "staff")
            sstream >> ratings.staff;
        else if(word == "facilities")
            sstream >> ratings.facilities;
        else if(word == "value_for_money")
            sstream >> ratings.value_for_money;
        else if(word == "overall_rating")
            sstream >> ratings.overall_rating;
        else 
            throw ImportException(BAD_REQUEST);
    }
    if(ratings.location<1 || ratings.cleanlines<1 || ratings.staff<1 || ratings.facilities<1
    || ratings.value_for_money<1 || ratings.overall_rating<1 || ratings.location>5 || ratings.cleanlines>5
    || ratings.staff>5 || ratings.facilities>5 || ratings.value_for_money>5 || ratings.overall_rating>5)
        throw ImportException(BAD_REQUEST);

    ratings.initialize = true;
    Hotel* hotel = find_hotel(uid);
    hotel->set_ratings(ratings);
    cout << "OK" << endl;
}

void Utrip::get_ratings(stringstream &sstream){
    string word, uid;
    sstream >> word >> word;
    if(word == "hotel")
        sstream >> uid;
    else 
        throw ImportException(BAD_REQUEST);
    
    Hotel *hotel= find_hotel(uid);
    hotel->print_ratings();
}