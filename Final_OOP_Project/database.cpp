
#include "database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    //setting connection credentials
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("object_oriented_project");

    //exception handling
    try
    {
        if(db.open())
        {
            qDebug() << "Successfully connected to database!";

        }
        else
        // Lets the program know that it didnt connect to the server
        {
            QString error = db.lastError().text();
            throw error.toStdString().c_str();
        }


    }
    catch(const char * message)  //catches the exception as a char pointer
    {
        QMessageBox messagebox;
        messagebox.about(NULL,"Connection to database failed!",message);
        qFatal("Connection to database failed!");
    }
}

Database::~Database()
{
    db.close();
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );  //remove database
    return;
}

QStringList Database::verifyUser(QString userName, QString password)
{
    QSqlQuery qry;
    qry.prepare("SELECT persons.ID, persons.Name, persons.UserID,persons.Password, persons.PositionID, position.position "
                 "FROM persons "
                 "LEFT JOIN position ON persons.PositionID = position.ID "
                 "WHERE UserID = :userid AND Password = :pword");

    qry.bindValue(":userid", userName);
    qry.bindValue(":pword", password);
    qry.exec();

    if( !qry.exec() ){
        qDebug() <<"Login query failed "<< db.lastError();
    }

    QStringList result;

    if(qry.next()){
        result << qry.value("ID").toString();
        result << qry.value("Name").toString();
        result << qry.value("Password").toString();
        result << qry.value("UserID").toString();
        result << qry.value("PositionID").toString();
        result << qry.value("position").toString();
    }

    return result;
}

bool Database::addUser(QString name, QString userid, QString password, int positionID)
{

    QSqlQuery query;
    query.prepare("INSERT INTO persons (Name, UserID, Password, PositionID) VALUES (:Name, :userid, :password, :PositionID)");
    query.bindValue(":Name", name);
    query.bindValue(":userid", userid);
    query.bindValue(":password", password);
    query.bindValue(":PositionID", positionID);

    bool insert = false;

    if (query.exec()) {
        insert = true;
    } else {
        qDebug() << "Insertion of a new user into the database failed. " << query.lastError().text();
    }
    return insert;
}

bool Database::editUser(QString name, QString username, QString password, int positionID, int userID)
{
    QSqlQuery qry;
    qry.prepare("UPDATE persons SET Name = :name, UserID = :username, Password = :password, PositionID = :positionID WHERE ID = :userID ");
    qry.bindValue(":name", name);
    qry.bindValue(":username", username);
    qry.bindValue(":password", password);
    qry.bindValue(":positionID", positionID);
    qry.bindValue(":userID", userID);

    if( !qry.exec() ){
        qDebug()<<"Updating user information in the database failed. ID "<< db.lastError();
        qDebug() << "Query:" << qry.lastQuery();
        qDebug() << "Parameters:" << name<<username<<password<<positionID<<userID;
        return false;
    }
    return true;
}

QSqlQuery Database::searchForUser(QString userText)
{

    QSqlQuery qry;
    qry.prepare("SELECT * FROM persons WHERE UserID = :text");
    qry.bindValue(":text", userText);

    if (!qry.exec()) {
        qDebug() << "User search failed: " << qry.lastError().text();
    }

    return qry;

}

QStringList Database::getPositionTypes()
{
    QStringList positionTypes;

    QSqlQuery qry;
    qry.prepare("SELECT position FROM position");

    if (!qry.exec()) {
        qDebug() << "Failed to retrieve position types: " << qry.lastError().text();
        return positionTypes;
    }

    while (qry.next()) {
        positionTypes << qry.value(0).toString();
    }

    return positionTypes;
}

bool Database::removeUser( int userID )
{
    QSqlQuery qry;
    qry.prepare("DELETE FROM persons WHERE ID = :userID ");
    qry.bindValue(":userID", userID);
    if( !qry.exec() ){
        qDebug()<<"Removing user from the database failed. " << db.lastError();
        return false;
    }
    return true;
}

QSqlQuery Database::searchByposition()
{
    QSqlQuery qry;
    qry.prepare("SELECT pe.ID, pe.Name, pe.UserID, pe.Password, po.position "
                "FROM persons pe "
                "JOIN position po ON pe.PositionID = po.ID "
                "ORDER BY po.position ");

    if (!qry.exec()) {
        qDebug() << "Failed to generate report. " << db.lastError().text();
         qDebug()<<"Query: "<<qry.lastQuery();
    }

    return qry;
}

QSqlQuery Database::searchByAllusers()
{
    QSqlQuery qry;
    qry.prepare("SELECT pe.ID, pe.Name, pe.UserID, pe.Password, po.position "
                "FROM persons pe "
                "JOIN position po ON pe.PositionID = po.ID ");

    if (!qry.exec()) {
        qDebug() << "Querry error: " << qry.lastError().text();
    }

    return qry;
}
//----
bool Database::addRecipe(QString Name, int DishID, QStringList Ingredientlist, QString Instruction)
{
    QSqlQuery query;
    QString ingredients = Ingredientlist.join(", "); // Join the ingredients with comma separator
    query.prepare("INSERT INTO recipe (RecipeName, DishID, Ingredient, Instruction) VALUES (:name, :dishid, :ingredients, :instruction)");
    query.bindValue(":name", Name);
    query.bindValue(":dishid", DishID);
    query.bindValue(":ingredients", ingredients);
    query.bindValue(":instruction", Instruction);

    bool insert = false;

    if (query.exec()) {
        insert = true;
    } else {
        qDebug() << "recipe was not added" << query.lastError().text();
        qDebug() << "Parameters:" << Name<<DishID<<Ingredientlist<<Instruction;
    }
    return insert;
}

QStringList Database::getDishTypes()
{
    QStringList positionTypes;

    QSqlQuery qry;
    qry.prepare("SELECT DishType FROM dish");

    if (!qry.exec()) {
        qDebug() << "Failed to retrieve dish types: " << qry.lastError().text();
        return positionTypes;
    }

    while (qry.next()) {
        positionTypes << qry.value(0).toString();
    }

    return positionTypes;
}

QStringList Database::getIngredients()
{
    QStringList ingredients;

    QSqlQuery qry;
    qry.prepare("SELECT IngredientName FROM ingredient");

    if (!qry.exec()) {
        qDebug() << "Failed to retrieve ingredients: " << qry.lastError().text();
        return ingredients;
    }

    while (qry.next()) {
        ingredients << qry.value(0).toString();
    }

    return ingredients;
}

bool Database::editRecipe(QString Name, int DishID, int IngredientID, int ID, QString Instruction)
{
    QSqlQuery qry;
    qry.prepare("UPDATE recipe SET RecipeName = :name, DishID = :dishid, IngredientID = :ingredientid, Instruction = :instruction WHERE ID = :id ");
    qry.bindValue(":name", Name);
    qry.bindValue(":dishid", DishID);
    qry.bindValue(":ingredientid", IngredientID);
    qry.bindValue(":instruction", Instruction);
    qry.bindValue(":id", ID);

    if( !qry.exec() ){
        qDebug()<<"Updating recipe information in the database failed. ID "<< db.lastError();
        return false;
    }
    return true;
}

bool Database::deleteRecipe(QString Name, int DishID, int IngredientID, int ID, QString Instruction)
{
    QSqlQuery qry;
    qry.prepare("DELETE FROM recipe RecipeName = :name, DishID = :dishid, IngredientID = :ingredientid, Instruction = :instruction WHERE ID = :id ");
    qry.bindValue(":name", Name);
    qry.bindValue(":dishid", DishID);
    qry.bindValue(":ingredientid", IngredientID);
    qry.bindValue(":instruction", Instruction);
    qry.bindValue(":id", ID);

    if( !qry.exec() ){
        qDebug()<<"Removing recipe from the database failed. " << db.lastError();
        return false;
    }
    return true;
}

bool Database::searchForRecipe(int DishID,QString Name)
{
    QSqlQuery qry;
    qry.prepare("SELECT RecipeName = :name FROM recipe WHERE DishID = :dishid ");
    qry.bindValue(":name",Name);
    qry.bindValue(":dishid",DishID);

    if( !qry.exec() ){
        qDebug()<<"Searching for recipe from the database failed. " << db.lastError();
        return false;
    }
    return true;
}

bool Database::myRecipe(int PersonID)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM connection WHERE PersonID = :personid ");
    qry.bindValue(":personid",PersonID);

    if( !qry.exec() ){
        qDebug()<<"Searching for recipe from the database failed. " << db.lastError();
        return false;
    }
    return true;
}
