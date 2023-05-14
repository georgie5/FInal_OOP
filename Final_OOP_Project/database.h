
#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include "QMessageBox"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include <QDebug>
#include "QtSql/QSqlQuery"

class Database
{
private:
    QSqlDatabase db;
public:
    Database();
    ~Database();
    QStringList verifyUser(QString userName, QString password);
    bool addUser(QString, QString, QString, int);
    bool editUser(QString, QString , QString, int, int);
    bool removeUser(int userID);
    QSqlQuery searchByposition();
    bool addRecipe(QString,int,int,QString);
    bool editRecipe(QString,int,int, int, QString);
    bool deleteRecipe(QString,int,int, int, QString);
    bool searchForRecipe(int,QString);
    bool myRecipe(int);
    QSqlQuery searchForUser(QString userText);
    QStringList getPositionTypes();
    QSqlQuery searchByAllusers();
};

#endif // DATABASE_H
