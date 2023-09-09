#include <bits/stdc++.h>
#include "Utrip.hpp"
using namespace std;

bool User::check_signup(std::string _email, std::string _username){
    if(_email == email || _username == username)
        return false;
    return true;
}

bool User::check_login(std::string _username, std::string _password){
    if(username == _username && password == _password)
        return true;
    return false;
}

void User::update_wallet(int amount){
    wallet.push_back(wallet.back()+amount);
}

