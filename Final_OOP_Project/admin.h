
#ifndef ADMIN_H
#define ADMIN_H

#include "baseuser.h"

#include <string>
#include "baseuser.h"
#include <iostream>

using namespace std;

class Admin : public BaseUser {
public:
    Admin();

    bool addUser(string, string, string, int);

    bool editUser(string, string , string, int, int);

    bool removeUser(int);

    void searchByposition();

    string searchForUser(string);

    string getPositionTypes();

    string searchByAllusers();

    int getCurrentUserID();

};

#endif // ADMIN_H
