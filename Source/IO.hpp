#ifndef IO_HPP
#define IO_HPP

class IO {
public:
    IO();
    static HotelTable read_hotels(std::string path);
private:
    static std::vector<std::string> parse_line(std::string line);
    static bool compare_uid(Hotel hotel_1, Hotel hotel_2);
};

#endif