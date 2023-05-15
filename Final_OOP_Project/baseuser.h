
#ifndef BASEUSER_H
#define BASEUSER_H

#include <string>
#include <iostream>

using namespace std;

class BaseUser {
public:
    BaseUser();
    bool verifyUser(string, string);

    bool addRecipe(string, int, string, string);

    bool editRecipe(string, int, string, string, int);

    bool deleteRecipe(int);

    void searchForRecipe(string);

    void myRecipe(int);

    string getDishTypes();
    \
    void set_name(string);
    string get_name();

    void set_userid(string);
    string get_userid();

    void set_password(string);
    string get_password();

    void set_position(int);
    int get_position();

    void set_recipeName(string);
    string get_recipeName();

    void set_dishID(int);
    int get_dishID();

    void set_ingredient(string);
    string get_ingredient();

    void set_instruction(string);
    string get_instruction();

private:
    string RecipeName;
    int DishID;
    string Ingredient;
    string Instruction;

    string Name;
    string Userid;
    string Password;
    int Position;

};

#endif // BASEUSER_H
