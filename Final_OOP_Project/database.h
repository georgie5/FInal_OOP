
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
    QString currentUserID;
    QString currentUsername;

public:
    Database();
    ~Database();
    QStringList verifyUser(QString userName, QString password);
    bool addUser(QString, QString, QString, int);
    bool editUser(QString, QString , QString, int, int);
    bool removeUser(int userID);
    QSqlQuery searchByposition();
    bool addRecipe(QString, int, QStringList, QString);
    bool editRecipe(QString, int, QStringList, QString, int resipeID);
    bool deleteRecipe(QString,int,int, int, QString);
    QSqlQuery searchForRecipe(QString);
    bool myRecipe(int);
    QSqlQuery searchForUser(QString userText);
    QStringList getPositionTypes();
    QSqlQuery searchByAllusers();
    QStringList getDishTypes();
    QStringList getIngredients();
    QString getCurrentUserID() const;
};

#endif // DATABASE_H
