

#include "baseuser.h"

BaseUser::BaseUser()
{

}

void BaseUser::set_dishID(int id)
{
    DishID = id;
}

int BaseUser::get_dishID()
{
    return DishID;
}

void BaseUser::set_ingredient(string ingredient)
{
    Ingredient = ingredient;
}

string BaseUser::get_ingredient()
{
    return Ingredient;
}

void BaseUser::set_instruction(string instruction)
{
    Instruction = instruction;
}

string BaseUser::get_instruction()
{
    return Instruction;
}

void BaseUser::set_name(string name)
{
    Name = name;
}

string BaseUser::get_name()
{
    return Name;
}

void BaseUser::set_password(string password)
{
    Password = password;
}

string BaseUser::get_password()
{
    return Password;
}

void BaseUser::set_position(int position)
{
    Position = position;
}

int BaseUser::get_position()
{
    return Position;
}

void BaseUser::set_recipeName(string rname)
{
    RecipeName = rname;
}

string BaseUser::get_recipeName()
{
    return RecipeName;
}

void BaseUser::set_userid(string userid)
{
    Userid = userid;
}

string BaseUser::get_userid()
{
    return Userid;
}

bool BaseUser::addRecipe(string name, int dishid, string ingredient, string instruction)
{

}

bool BaseUser::verifyUser(string userid, string password)
{

}

bool BaseUser::deleteRecipe(int recipeid)
{

}

bool BaseUser::editRecipe(string name, int dishid, string ingredient, string instruction, int id)
{

}

void BaseUser::searchForRecipe(string recipeName)
{

}

void BaseUser::myRecipe(int id)
{

}

string BaseUser::getDishTypes()
{

}
