#ifndef USER_HPP
#define USER_HPP


class User {
public:
    User(std::string _email, std::string _username, std::string _pass){
        email = _email; username = _username; password = _pass; wallet.push_back(0);
    }
    bool check_signup(std::string _email, std::string _username);
    bool check_login(std::string _username, std::string _password);
    void update_wallet(int amount);
    std::vector<int> get_wallet(){ return wallet; }
    std::string get_name(){ return username; }
    
private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<int> wallet;
};

#endif