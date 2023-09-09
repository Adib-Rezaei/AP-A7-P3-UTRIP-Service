#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "Room.hpp"
typedef std::vector<Room*> RoomTable;

struct Quantity {
    int standard;
    int deluxe;
    int luxury;
    int premium;
};

struct Price {
    int standard;
    int deluxe;
    int luxury;
    int premium;
};

struct Ratings {
    bool initialize;
    double location;
    double cleanlines;
    double staff;
    double facilities;
    double value_for_money;
    double overall_rating;
};

class Hotel {
public:
    Hotel(Line &row);
    void print();
    void filter_print();
    std::string get_uid(){ return uid; }
    std::string get_city(){ return city; }
    int get_star(){ return star; }
    std::vector<Room*> get_rooms(){ return rooms; }
    double calc_avg();
    RoomTable find_rooms(std::string type, int quantity, int in, int out);
    void set_comment(std::string comment){ comments.push_back(comment); }
    void print_comments();
    void set_ratings(Ratings _ratings){ ratings = _ratings; }
    void print_ratings();
    std::string get_img(){ return image_url; }
    std::string get_name(){ return name; }
    std::string get_overview(){ return overview;}
    std::string get_amenities(){ return amenities; }
    Quantity get_quantity(){ return quantity; }
    Price get_price(){ return price; }

private:
    void initialize_rooms(Line &row);
    void which_room(int col, int id);
    void print_extra();

    std::string uid;
    std::string name;
    int star;
    std::string overview;
    std::string amenities;
    std::string city;
    double latitude;
    double longitude;
    std::string image_url;
    RoomTable rooms;
    Price price;
    Ratings ratings;
    std::vector<std::string> comments;
    Quantity quantity;
};


#endif