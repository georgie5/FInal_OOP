
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQueryModel>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populatePositionsComboBox();

private slots:
    void on_loginButton_clicked();

    void on_addUserButton_clicked();

    void on_editUserButton_clicked();

    void on_deleteUserButton_clicked();

    void on_reportButton_clicked();

    void on_logoutButton_clicked();

    void on_addButton_clicked();

    void on_backButton_clicked();

    void on_changeButton_clicked();

    void on_backButton_2_clicked();

    void on_deleteButton_clicked();

    void on_backButton_3_clicked();

    void on_printButton_clicked();

    void on_backButton_4_clicked();

    void on_addRecipeButton_clicked();

    void on_editRecipeButton_clicked();

    void on_deleteRecipeButton_clicked();

    void on_searchRecipeButton_clicked();

    void on_myRecipeButton_clicked();

    void on_createRecipeButton_clicked();

    void on_backButton_5_clicked();

    void on_editButton_clicked();

    void on_backButton_6_clicked();

    void on_removeButton_clicked();

    void on_backButton_7_clicked();

    void on_viewButton_clicked();

    void on_backButton_8_clicked();

    void on_PrintButton_clicked();

    void on_backButton_9_clicked();

    void on_backButton_10_clicked();

    void on_myAddRecipeButton_clicked();

    void on_myEditRecipeButton_clicked();

    void on_myDeleteRecipeButton_clicked();

    void on_logoutButton_2_clicked();

    void on_editSearchButton_clicked();

    void on_deleteSearchtButton_clicked();

    void on_generateButton_clicked();



    void on_RegisterButton_clicked();

    void on_LoginpageButton_clicked();

    void on_createAccountButton_clicked();

private:
    Ui::MainWindow *ui;
    Database *db;
};

#endif // MAINWINDOW_H
