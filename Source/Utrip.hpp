#ifndef UTRIP_HPP
#define UTRIP_HPP


typedef std::vector<std::string> Line;
#include "Hotel.hpp"
#include "User.hpp"
typedef std::vector<Hotel> HotelTable;
typedef std::vector<User*> UserTable;
#include "IO.hpp"
#include "Filter.hpp"
#include "ImportException.hpp"


class Utrip {
public:
    Utrip(HotelTable _hotels){
        hotels = _hotels; current = NULL; Filters.resize(4,NULL);
    }
    void signup(std::string username, std::string pass, std::string email);
    void login(std::string username, std::string pass);
    HotelTable get_hotels(){ return hotels; }
    User* find_user(std::string username);
    Hotel* find_hotel(std::string uid);
    User* get_current(){ return current; }
    void delete_current(){ current = NULL; }

private:
    
    void logout(std::stringstream &sstream);
    void wallet(std::stringstream &sstream);
    void filters(std::stringstream &sstream);
    void city_filter(std::stringstream &sstream);
    void star_filter(std::stringstream &sstream);
    void cost_filter(std::stringstream &sstream);
    void specific_filter(std::stringstream &sstream);
    void comments(std::stringstream &sstream);
    void ratings(std::stringstream &sstream);

    void get_wallet(std::stringstream &sstream);
    void get_hotels(std::stringstream &sstream);
    void get_comments(std::stringstream &sstream);
    void get_ratings(std::stringstream &sstream);
    
    void delete_reserve(std::stringstream &sstream);
    void filter_hotels();
    
    void reserve_room(RoomTable &rooms, int in, int out);
    std::string hashing(std::string password);

    HotelTable hotels;
    UserTable users;
    User* current;
    std::vector<Filter*> Filters;

};


#endif