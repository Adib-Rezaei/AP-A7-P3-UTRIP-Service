#include <bits/stdc++.h>
#include "Utrip.hpp"
using namespace std;

void Filter::print_hotels(HotelTable &_hotels){
    if(_hotels.empty())
        cout << "Empty" << endl;
    for(int i=0; i< _hotels.size(); i++){
        _hotels[i].filter_print();
    }
}

HotelTable City::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        if(hotel.get_city() == name){
            filter.push_back(hotel);
        }
    }
    return filter;
}

HotelTable Star::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        if(hotel.get_star() >= min && hotel.get_star() <= max)
            filter.push_back(hotel);
    }
    return filter;
}

HotelTable Cost::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        if(hotel.calc_avg() >= min && hotel.calc_avg() <= max)
            filter.push_back(hotel);
    }
    return filter;
}

HotelTable Specific::set_filter(HotelTable selected){
    HotelTable filter;
    for(auto &hotel : selected){
        vector<Room*> rooms = hotel.get_rooms();
        int cnt=0;
        for(auto &room : rooms){
            if(is_ok_room(room))
                cnt++;
        }
        if(cnt >= quantity)
            filter.push_back(hotel);
    }
        
    return filter;
}

bool Specific::is_ok_room(Room* room){
    if(room->get_name()[0] == type[0]){
        vector<int> date = room->get_date();
        for(int i=check_in; i<= check_out; i++){
            if(date[i]){
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}