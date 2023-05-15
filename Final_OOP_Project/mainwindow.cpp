
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set the login stack widget page as the current index
    ui->stackedWidget->setCurrentIndex(0);

    // create a new instance of the Database class
    db = new Database();

    // populate the positions in the positions combobox
    QStringList positionTypes = db->getPositionTypes();
    if (positionTypes.isEmpty()) {
        qDebug() << "Failed to retrieve position types.";
    } else {
        ui->addPositionBox->clear();
        ui->addPositionBox->addItems(positionTypes);
        ui->editPositionComboBox->clear();
        ui->editPositionComboBox->addItems(positionTypes);
        ui->deletePositionComboBox->clear();
        ui->deletePositionComboBox->addItems(positionTypes);
    }
    // set the position combobox to clear
    ui->addPositionBox->setCurrentIndex(-1);
    ui->editPositionComboBox->setCurrentIndex(-1);
    ui->deletePositionComboBox->setCurrentIndex(-1);
    ui->searchDishComboBox->setCurrentIndex(-1);

    //populate dish types in dish combobox
     QStringList dishTypes = db->getDishTypes();
     if(dishTypes.empty())
     {
        qDebug() << "Failed to retrieve dish types.";
     }
     else {
            ui->addDishComboBox->clear();
            ui->addDishComboBox->addItems(dishTypes);

            ui->editDishComboBox->clear();
            ui->editDishComboBox->addItems(dishTypes);

            ui->deleteDishComboBox->clear();
            ui->deleteDishComboBox->addItems(dishTypes);

            ui->searchDishComboBox->clear();
            ui->searchDishComboBox->addItems(dishTypes);
          }
     ui->addDishComboBox->setCurrentIndex(-1);
     ui->editDishComboBox->setCurrentIndex(-1);
     ui->deleteDishComboBox->setCurrentIndex(-1);
     ui->searchDishComboBox->setCurrentIndex(-1);

   connect(ui->searchDishComboBox, &QComboBox::activated, this, &MainWindow::clearRecipeNameInput);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_loginButton_clicked()
{
    // get the username and password entered by the user
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    QStringList userinfo = db->verifyUser(username, password);

    foreach (const QString &str, userinfo) {
        qDebug() << str;
    }

    if(userinfo.isEmpty()){
        // The username and/or password is incorrect
        QMessageBox::warning(this, "Login Failed", "Invalid username and/or password. Please try again.");
    }
    else {
        int positionId = userinfo[4].toInt();
        if(positionId == 1){
            ui->stackedWidget->setCurrentIndex(1); // Taken to admin dashboard
        }
        else{
            ui->stackedWidget->setCurrentIndex(6); // Taken to user dashboard
        }
    }
}


void MainWindow::on_addUserButton_clicked()
{
ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_editUserButton_clicked()
{
ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_deleteUserButton_clicked()
{
ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_reportButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_logoutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_addButton_clicked()
{

    QString name = ui->addNameEdit->text();
    QString username = ui->addUsernameEdit->text();
    QString password = ui->addPasswordEdit->text();

    int positionID = ui->addPositionBox->currentIndex() + 1;

    // check if all fields are inputed
    if (name.isEmpty() || username.isEmpty() || password.isEmpty() || positionID == 0) {
        QMessageBox::warning(this, "New User", "Please fill all the required fields.");
        return;
    }

    // call the addUser function with the person's data as arguments
    if (db->addUser(name, username, password, positionID) ) {
        qDebug() << "User added successfully!";
        QMessageBox::information(this, "New User", "Employee added successfully");
    } else {
        qDebug() << "Failed to add user.";
        QMessageBox::warning(this, "New user", "Failed to add Employee");
    }

    // clear the text fields and reset the combobox to the first item
    ui->addNameEdit->clear();
    ui->addUsernameEdit->clear();
    ui->addPasswordEdit->clear();
    ui->addPositionBox->setCurrentIndex(-1);
}


void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_changeButton_clicked()
{
    QString name = ui->editNameEdit->text();
    QString username =  ui->editUsernameEdit->text();
    QString password =  ui->editPasswordEdit->text();
    int positionID =  ui->editPositionComboBox->currentIndex() + 1;

    int userID = ui->edit_userID->text().toInt();

    // call the addUser function with the person's data as arguments
    if (db->editUser(name, username, password, positionID, userID) ) {
        qDebug() << "User updated successfully!";
        QMessageBox::information(this,  "Success", "The User information was updated successfully.");
    } else {
        qDebug() << "Failed to update User.";
        QMessageBox::warning(this,"Error", "There was an error updating the User information.");
    }

    // clear the text fields and reset the combobox to the first item
    ui->editNameEdit->clear();
    ui->editUsernameEdit->clear();
    ui->editPasswordEdit->clear();
    ui->editPositionComboBox->setCurrentIndex(-1);
    ui->edit_userID->clear();
}


void MainWindow::on_backButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_deleteButton_clicked()
{
    int userID = ui->delete_userID->text().toInt();
    // Remove the selected user from the database
    bool remove = db->removeUser(userID);

    if (remove) {
        QMessageBox::information(this, "Success", "User has been deleted.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete user.");
    }
    // fill in the employee information fields
    ui->deleteNameEdit->clear();
    ui->deleteUseridEdit->clear();
    ui->deletePasswordEdi->clear();
    ui->deletePositionComboBox->clear();
    ui->delete_userID->clear();
    ui->deletesearchUserinput->clear();
}


void MainWindow::on_backButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_printButton_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        ui->reportTableView->render(&painter);
    }
}


void MainWindow::on_backButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_addRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_editRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_deleteRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}


void MainWindow::on_searchRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_myRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);

    // Get the user's recipes
    QSqlQuery qry = db->getUserRecipes();

    // Populate the QListView with the recipe names
    QStringListModel *model = new QStringListModel();
    QStringList recipeNames;
    while (qry.next()) {
        recipeNames << qry.value(0).toString();
    }
    model->setStringList(recipeNames);
    ui->myrecipeView->setModel(model);
}


void MainWindow::on_createRecipeButton_clicked()
{
    QString recipeName = ui->addRecipenameEdit->text();
    int dishID = ui->addDishComboBox->currentIndex() + 1;
    QStringList ingredientsList = ui->addIngredientText->toPlainText().split("\n", Qt::SkipEmptyParts);
    QString recipeInstructions = ui->addInstructionsEdit->toPlainText();

    // Check if all fields are inputted
    if (recipeName.isEmpty() || dishID == -1 || ingredientsList.isEmpty() || recipeInstructions.isEmpty()) {
        QMessageBox::warning(this, "New recipe", "Please fill all the required fields.");
        return;
    }

    // Call the addRecipe function with the recipe's data as arguments
    if (db->addRecipe(recipeName, dishID, ingredientsList, recipeInstructions)) {
        qDebug() << "Recipe added successfully!";
        QMessageBox::information(this, "New Recipe", "Recipe added successfully");
    } else {
        qDebug() << "Failed to add recipe.";
        QMessageBox::warning(this, "New Recipe", "Failed to add Recipe");
    }

    ui->addRecipenameEdit->clear();
    ui->addDishComboBox->setCurrentIndex(-1);
    ui->addIngredientText->clear();
    ui->addInstructionsEdit->clear();


}


void MainWindow::on_backButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_editButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_backButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_removeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_backButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_backButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_PrintButton_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        ui->recipeTableView->render(&painter);
    }
}


void MainWindow::on_backButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_backButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_myAddRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_myEditRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);

    // get the selected recipe name
    QString recipeName = ui->myrecipeView->currentIndex().data().toString();

    ui->recipeSearchInput->setText(recipeName);
}


void MainWindow::on_myDeleteRecipeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);

    // get the selected recipe name
    QString recipeName = ui->myrecipeView->currentIndex().data().toString();

    ui->deleterecipeSearchInput->setText(recipeName);
}


void MainWindow::on_logoutButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_editSearchButton_clicked()
{
    QString userText = ui->editsearchUserinput->text();

    // search for the user by username
    QSqlQuery result = db->searchForUser(userText);

    if (result.next())
    {
        // fill in the employee information fields
        ui->editNameEdit->setText(result.value("Name").toString());
        ui->editUsernameEdit->setText(result.value("UserID").toString());
        ui->editPasswordEdit->setText(result.value("Password").toString());
        ui->editPositionComboBox->setCurrentIndex(result.value("PositionID").toInt() - 1);
        ui->edit_userID->setText(result.value("ID").toString());

    } else {
        QMessageBox::warning(this, "Error", "User not found.");
    }

}


void MainWindow::on_deleteSearchtButton_clicked()
{

    QString userText = ui->deletesearchUserinput->text();

    // search for the user by username
    QSqlQuery result = db->searchForUser(userText);

    if (result.next())
    {
        // fill in the employee information fields
        ui->deleteNameEdit->setText(result.value("Name").toString());
        ui->deleteUseridEdit->setText(result.value("UserID").toString());
        ui->deletePasswordEdi->setText(result.value("Password").toString());
        ui->deletePositionComboBox->setCurrentIndex(result.value("PositionID").toInt() - 1);
        ui->delete_userID->setText(result.value("ID").toString());

    } else {
        QMessageBox::warning(this, "Error", "User not found.");
    }
}


void MainWindow::on_generateButton_clicked()
{
    QString reportType = ui->reportComboBox->currentText();

     // Generate the SQL query for the selected report type
    if(reportType == "All users")
    {
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(db->searchByAllusers());
        ui->reportTableView->setModel(model);
    }
    else if(reportType == "Position")
    {
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(db->searchByposition());
        ui->reportTableView->setModel(model);
    }
}


void MainWindow::on_RegisterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
}


void MainWindow::on_LoginpageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_createAccountButton_clicked()
{
    QString name = ui->registerName->text();
    QString username = ui->registerUsername->text();
    QString password = ui->registerPassword->text();

    int positionID = 2;

    // check if all fields are inputed
    if (name.isEmpty() || username.isEmpty() || password.isEmpty() ) {
        QMessageBox::warning(this, "New User", "Please fill all the required fields.");
        return;
    }

    // call the addUser function with the person's data as arguments
    if (db->addUser(name, username, password, positionID) ) {
        qDebug() << "User added successfully!";
        QMessageBox::information(this, "New User", "Registered Successfully");
        ui->stackedWidget->setCurrentIndex(0);

    } else {
        qDebug() << "Failed to add user.";
        QMessageBox::warning(this, "New User", "Failed to Register");
    }

    // clear the text fields and reset the combobox to the first item
    ui->registerName->clear();
    ui->registerUsername->clear();
    ui->registerPassword->clear();

}


void MainWindow::on_editRecipeSelectButton_clicked()
{
    QString userText = ui->recipeSearchInput->text();

    // search for the user by username
    QSqlQuery result = db->searchForRecipe(userText);

    if (result.next())
    {
        // fill in the employee information fields
        ui->editRecipename->setText(result.value("RecipeName").toString());
        ui->editDishComboBox->setCurrentIndex(result.value("DishID").toInt() - 1);
        ui->editIngredientText->setText(result.value("Ingredient").toString().replace(", ", "\n"));
        ui->editInstructionsEdit->setText(result.value("Instruction").toString());
        ui->edit_recipeID->setText(result.value("recipe_ID").toString());
    } else {
        QMessageBox::warning(this, "Error", "Recipe not found.");
    }
}


void MainWindow::on_recipeEditButton_clicked()
{
    QString recipeName = ui->editRecipename->text();
    int dishID = ui->editDishComboBox->currentIndex() + 1;
    QStringList ingredientsList = ui->editIngredientText->toPlainText().split("\n", Qt::SkipEmptyParts);
    QString recipeInstructions = ui->editInstructionsEdit->toPlainText();

    int userID = ui->edit_recipeID->text().toInt();

    // call the addUser function with the person's data as arguments
    if (db->editRecipe(recipeName, dishID, ingredientsList, recipeInstructions, userID) ) {
        qDebug() << "Recipe updated successfully!";
        QMessageBox::information(this,  "Success", "Recipe updated successfully!");
    } else {
        qDebug() << "Failed to update Recipe.";
        QMessageBox::warning(this,"Error", "There was an error updating the Recipe information.");
    }

    // clear the text fields and reset the combobox to the first item
     ui->editRecipename->clear();
     ui->editDishComboBox->setCurrentIndex(-1);
     ui->editIngredientText->clear();
     ui->editInstructionsEdit->clear();
     ui->editRecipename->clear();
     ui->edit_recipeID->clear();
     ui->recipeSearchInput->clear()
}


void MainWindow::on_deleteresipeButton_clicked()
{
    int userID = ui->delete_recipeID->text().toInt();
    // Remove the selected user from the database
    bool remove = db->deleteRecipe(userID);

    if (remove) {
        QMessageBox::information(this, "Success", "Recipe has been deleted.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete recipe.");
    }
    // fill in the employee information fields
    ui->deleteRecipename->clear();
    ui->deleteDishComboBox->clear();
    ui->deleteIngredientText->clear();
    ui->deleteInstructionsEdit->clear();
    ui->delete_recipeID->clear();
    ui->deleterecipeSearchInput->clear();
}


void MainWindow::on_deleteRecipeSearchButton_clicked()
{
    QString userText = ui->deleterecipeSearchInput->text();

    // search for the user by username
    QSqlQuery result = db->searchForRecipe(userText);

    if (result.next())
    {
        // fill in the employee information fields
        ui->deleteRecipename->setText(result.value("RecipeName").toString());
        ui->deleteDishComboBox->setCurrentIndex(result.value("DishID").toInt() - 1);
        ui->deleteIngredientText->setText(result.value("Ingredient").toString().replace(", ", "\n"));
        ui->deleteInstructionsEdit->setText(result.value("Instruction").toString());
        ui->delete_recipeID->setText(result.value("recipe_ID").toString());

    } else {
        QMessageBox::warning(this, "Error", "Recipe not found.");
    }
}


void MainWindow::on_searchRecipeSearchButton_clicked()
{

    // Get the search input values
    QString dishType = ui->searchDishComboBox->currentText();
    QString recipeName = ui->searchRecipenameinput->text();

    QSqlQueryModel *model = new QSqlQueryModel;

    if(!dishType.isEmpty())
    {
         // Search by dish type
        model->setQuery(db->searchBydishType(dishType));
        ui->searchrecipeView->setModel(model);
    }
    else if(!recipeName.isEmpty())
    {
        // Search by recipename
        model->setQuery(db->searchByRecipeName(recipeName));
        ui->searchrecipeView->setModel(model);
    }

}


void MainWindow::on_myrecipeviewButton_clicked()
{


    // get the selected recipe name
    QString recipeName = ui->myrecipeView->currentIndex().data().toString();

    // search for the recipe in the database
    QSqlQuery result = db->searchForRecipe(recipeName);

    if (result.next())
    {
        // create a new model to hold the recipe details
        QStandardItemModel *model = new QStandardItemModel();
        model->setColumnCount(4);
        model->setHorizontalHeaderItem(0, new QStandardItem("Recipe Name"));
        model->setHorizontalHeaderItem(1, new QStandardItem("Dish Type"));
        model->setHorizontalHeaderItem(2, new QStandardItem("Ingredients"));
        model->setHorizontalHeaderItem(3, new QStandardItem("Instructions"));

        // add the recipe details to the model
        QString dishName = db->getDishName(result.value("DishID").toInt());
        QString ingredients = result.value("Ingredient").toString().replace(", ", "\n");
        model->setItem(0, 0, new QStandardItem(result.value("RecipeName").toString()));
        model->setItem(0, 1, new QStandardItem(dishName));
        model->setItem(0, 2, new QStandardItem(ingredients));
        model->setItem(0, 3, new QStandardItem(result.value("Instruction").toString()));

        // set the model to the table view
        ui->recipeTableView->setModel(model);
        ui->recipeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->recipeTableView->horizontalHeader()->setStretchLastSection(true);

        // set the row height and maximum height
        QFontMetrics fm(ui->recipeTableView->font());
        int rowHeight = qMax(fm.height()*20, ui->recipeTableView->rowHeight(20));
        ui->recipeTableView->setRowHeight(10, rowHeight);
        ui->recipeTableView->verticalHeader()->setDefaultSectionSize(rowHeight);
        ui->recipeTableView->verticalHeader()->setMaximumSectionSize(rowHeight);

        ui->stackedWidget->setCurrentIndex(11);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Recipe not found.");
    }
}


void MainWindow::on_viewrecipeButton_clicked()
{
    // Get the selected row index from the table view
    QModelIndexList selectedrecipe = ui->searchrecipeView->selectionModel()->selectedIndexes();


    QString recipeName = selectedrecipe.at(0).siblingAtColumn(0).data().toString();

    // search for the recipe in the database
    QSqlQuery result = db->searchByRecipeName(recipeName);

    if (result.next())
    {
        // create a new model to hold the recipe details
        QStandardItemModel *model = new QStandardItemModel();
        model->setColumnCount(4);
        model->setHorizontalHeaderItem(0, new QStandardItem("Recipe Name"));
        model->setHorizontalHeaderItem(1, new QStandardItem("Dish Type"));
        model->setHorizontalHeaderItem(2, new QStandardItem("Ingredients"));
        model->setHorizontalHeaderItem(3, new QStandardItem("Instructions"));

        // add the recipe details to the model

        QString ingredients = result.value("Ingredient").toString().replace(", ", "\n");
        model->setItem(0, 0, new QStandardItem(result.value("RecipeName").toString()));
        model->setItem(0, 1, new QStandardItem(result.value("DishType").toString()));
        model->setItem(0, 2, new QStandardItem(ingredients));
        model->setItem(0, 3, new QStandardItem(result.value("Instruction").toString()));

        // set the model to the table view
        ui->recipeTableView->setModel(model);
        ui->recipeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->recipeTableView->horizontalHeader()->setStretchLastSection(true);

        // set the row height and maximum height
        QFontMetrics fm(ui->recipeTableView->font());
        int rowHeight = qMax(fm.height()*20, ui->recipeTableView->rowHeight(20));
        ui->recipeTableView->setRowHeight(10, rowHeight);
        ui->recipeTableView->verticalHeader()->setDefaultSectionSize(rowHeight);
        ui->recipeTableView->verticalHeader()->setMaximumSectionSize(rowHeight);

        ui->stackedWidget->setCurrentIndex(11);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Recipe not found. Make sure to select a recipe");

    }

}

void MainWindow::clearRecipeNameInput()
{
    ui->searchRecipenameinput->clear();
}

void MainWindow::on_searchRecipenameinput_cursorPositionChanged(int arg1, int arg2)
{
    ui->searchDishComboBox->setCurrentIndex(-1);
}




