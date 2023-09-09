#include <bits/stdc++.h>
#include "Utrip.hpp"
#include "IO.hpp"

#define SEPERATOR ','
using namespace std;

HotelTable IO::read_hotels(string path){
    ifstream input(path);
    string line;
    HotelTable hotels;

    getline(input, line);
    while(getline(input, line)){
        vector<string> row = parse_line(line);
        hotels.push_back(Hotel(row));
    }
    sort(hotels.begin(), hotels.end(), compare_uid);
    return hotels;
}

vector<string> IO::parse_line(string line){
    string word;
    stringstream sstream(line);
    vector<string> row;
    
    while (getline(sstream, word, SEPERATOR)){
        row.push_back(word);
    }

    return row;
}

bool IO::compare_uid(Hotel hotel_1, Hotel hotel_2){
    return hotel_1.get_uid() < hotel_2.get_uid();
}