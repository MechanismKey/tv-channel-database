#include "manager.h"
#include "ui_manager.h"

using std::unique_ptr;

Manager::Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);

    ui->tableWidget_Employee->hideColumn(1); // name
    ui->tableWidget_Employee->hideColumn(2); // second_name
    ui->tableWidget_Employee->hideColumn(3); // birthday
    ui->tableWidget_Employee->hideColumn(4); //itn

    ui->stackedWidget->setCurrentIndex(Form::tables);

    ui->tableWidget_Employee->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_Employee->setFocusPolicy(Qt::NoFocus);

    loadAllTables();
    loadComboPost();
}

Manager::~Manager()
{
    delete ui;
}

void Manager::loadAllTables()
{
    Database::loadTable(Database::employee, ui->tableWidget_Employee);
}

void Manager::loadComboPost()
{
    ui->comboBox_Post->addItems(Database::listPost());
}
int Manager::getCurrentPost()
{
    int id_post = Database::getPostId(ui->comboBox_Post->currentText());

    if(id_post == -1)
    {
        qDebug() << "\nINSERT INTO EmployeePost(title = " <<ui->comboBox_Post->currentText() << ")";
        id_post = Database::addPost(ui->comboBox_Post->currentText());

        if(id_post == -1)
        {
            qDebug() << "Error\n";
        }
        else
        {
            qDebug() << "Succes (id = "<< id_post << ")\n";
            ui->comboBox_Post->addItem(ui->comboBox_Post->currentText());
        }
    }

    return id_post;
}

void Manager::editInTableWidgetEmployee(const Employee& employee)
{
    for(int i = 0; i < ui->tableWidget_Employee->rowCount(); ++i)
    {
        if(ui->tableWidget_Employee->item(i,4)->text() == employee.passport.itn)
        {
            ui->tableWidget_Employee->item(i,5)->setText(employee.phone);
            ui->tableWidget_Employee->item(i,6)->setText(Database::getPostName(employee.id_post));
            ui->tableWidget_Employee->item(i,7)->setText(QString::number(employee.salary));
            break;
        }
    }
}

void Manager::addToTableWidgetEmployee(const Employee& emp)
{
    int row = ui->tableWidget_Employee->rowCount();
    ui->tableWidget_Employee->insertRow(row);

    QString fullname(emp.passport.surname + " " + emp.passport.name.at(0) + ". " + emp.passport.secondName.at(0) + ".");

    ui->tableWidget_Employee->setItem(row, 0, new QTableWidgetItem(fullname));
    ui->tableWidget_Employee->setItem(row, 1, new QTableWidgetItem(emp.passport.name));
    ui->tableWidget_Employee->setItem(row, 2, new QTableWidgetItem(emp.passport.secondName));
    ui->tableWidget_Employee->setItem(row, 3, new QTableWidgetItem(emp.passport.birthday.toString("yyyy-MM-dd")));
    ui->tableWidget_Employee->setItem(row, 4, new QTableWidgetItem(emp.passport.itn));
    ui->tableWidget_Employee->setItem(row, 5, new QTableWidgetItem(emp.phone));
    ui->tableWidget_Employee->setItem(row, 6, new QTableWidgetItem(Database::getPostName(std::move(emp.id_post))));
    ui->tableWidget_Employee->setItem(row, 7, new QTableWidgetItem(QString::number(emp.salary)));
    ui->tableWidget_Employee->setItem(row, 8, new QTableWidgetItem(emp.recruitment.toString("yyyy-MM-dd")));
}
void Manager::removeFromTableWidgetEmployee(const QString& itn)
{
    for(int i = 0; i < ui->tableWidget_Employee->rowCount(); ++i)
    {
        if(ui->tableWidget_Employee->item(i,4)->text() == itn)
        {
            ui->tableWidget_Employee->removeRow(i);
            break;
        }
    }
}

void Manager::clearEmployee()
{
    ui->lineEdit_Surname->clear();
    ui->lineEdit_Name->clear();
    ui->lineEdit_SecondName->clear();
    ui->dateEdit_Birthday->clear();
    ui->lineEdit_itn->clear();

    ui->lineEdit_Phone->clear();
    ui->comboBox_Post->clearEditText();
    ui->lineEdit_Salary->clear();
    ui->dateEdit_Recruitment->clear();
}
void Manager::fillEmployee(const int&& row)
{
    QString fio = ui->tableWidget_Employee->item(row,0)->text();
    ui->lineEdit_Surname->setText(fio.left(fio.indexOf(' ')));
    ui->lineEdit_Name->setText(ui->tableWidget_Employee->item(row,1)->text());
    ui->lineEdit_SecondName->setText(ui->tableWidget_Employee->item(row,2)->text());
    ui->dateEdit_Birthday->setDate(QDate::fromString(ui->tableWidget_Employee->item(row,3)->text(),
                                   "yyyy-MM-dd"));
    ui->lineEdit_itn->setText(ui->tableWidget_Employee->item(row,4)->text());

    ui->lineEdit_Phone->setText(ui->tableWidget_Employee->item(row,5)->text());;
    ui->comboBox_Post->setCurrentText(ui->tableWidget_Employee->item(row,6)->text());
    ui->lineEdit_Salary->setText(ui->tableWidget_Employee->item(row,7)->text());
    ui->dateEdit_Recruitment->setDate(QDate::fromString(ui->tableWidget_Employee->item(row,8)->text(),
                                                        "yyyy-MM-dd"));
}
void Manager::setEmployeeReadOnly(const bool answer)
{
    ui->lineEdit_Surname->setReadOnly(answer);
    ui->lineEdit_Name->setReadOnly(answer);
    ui->lineEdit_SecondName->setReadOnly(answer);
    ui->dateEdit_Birthday->setReadOnly(answer);
    ui->lineEdit_itn->setReadOnly(answer);

    ui->lineEdit_Phone->setReadOnly(answer);
    ui->comboBox_Post->setDisabled(answer);
    ui->lineEdit_Salary->setReadOnly(answer);
    ui->dateEdit_Recruitment->setReadOnly(answer);
}
void Manager::setEmployeeEdit()
{
    ui->lineEdit_Phone->setReadOnly(false);
    ui->comboBox_Post->setDisabled(false);
    ui->lineEdit_Salary->setReadOnly(false);
}
void Manager::setEmployeeMode(const EmployeeMode&& mode)
{
    employee_mode = mode;

    switch(employee_mode)
    {
    case EmployeeMode::add:
    {
        ui->label_Employee->setText("Добавление нового сотрудника");
        ui->pushButton_Employee->setText("Добавить");
        setEmployeeReadOnly(false);
        clearEmployee();
        ui->pushButton_Employee->setHidden(false);
        ui->pushButton_deleteEmployee->setHidden(true);
        ui->pushButton_changeEmployee->setHidden(true);

    } break;
    case EmployeeMode::edit:
    {
        ui->label_Employee->setText("Информация о сотруднике");
        ui->pushButton_Employee->setText("Сохранить");
        setEmployeeReadOnly(true);
        ui->pushButton_Employee->setHidden(true);
        ui->pushButton_deleteEmployee->setHidden(true);
        ui->pushButton_changeEmployee->setHidden(false);

    }break;
    };
}



void Manager::on_listWidget_itemSelectionChanged()
{
    ui->stackedWidget_Tables->setCurrentIndex(ui->listWidget->currentRow());
}

void Manager::on_pushButton_toAddEmployee_clicked()
{
    setEmployeeMode(EmployeeMode::add);
    ui->stackedWidget->setCurrentIndex(Form::employee);
}

void Manager::on_pushButton_backFromEmployee_clicked()
{
    ui->stackedWidget->setCurrentIndex(Form::tables);
}

void Manager::on_tableWidget_Employee_cellPressed(int row, int column)
{
    fillEmployee(std::move(row));
    setEmployeeMode(EmployeeMode::edit);
    ui->stackedWidget->setCurrentIndex(Form::employee);
}

void Manager::on_pushButton_Employee_clicked()
{
    Passport passport(ui->lineEdit_Surname->text(), ui->lineEdit_Name->text(), ui->lineEdit_SecondName->text(),
                      ui->dateEdit_Birthday->date(), ui->lineEdit_itn->text());

    Employee employee(passport, ui->lineEdit_Phone->text(), 1, ui->lineEdit_Salary->text().toInt(),
                      ui->dateEdit_Recruitment->date());

    if(!employee.isValid() || ui->comboBox_Post->currentText().isEmpty())
    {
        QMessageBox::information(0,0,"Ошибка входных данных");
        return;
    }

    employee.id_post = getCurrentPost();

    switch(employee_mode)
    {
    case EmployeeMode::add:
    {
        if(Database::addEmployee(employee))
        {
            addToTableWidgetEmployee(employee);
            ui->stackedWidget->setCurrentIndex(Form::tables);
            QMessageBox::information(0,0,"Сотрудник добавлен");
        }
        else
            QMessageBox::warning(0,0,"Ошибка! Сотрудник не добавлен");

    } break;
    case EmployeeMode::edit:
    {
        Database::editEmployee(employee);
        editInTableWidgetEmployee(employee);
        setEmployeeMode(EmployeeMode::edit);
        QMessageBox::information(0,0,"Информация сохранена");

    }break;
    };
}

void Manager::on_pushButton_changeEmployee_clicked()
{
    ui->pushButton_changeEmployee->setHidden(true);
    ui->pushButton_Employee->setHidden(false);
    ui->pushButton_deleteEmployee->setHidden(false);
    setEmployeeEdit();
    ui->label_Employee->setText("Редактирование информации");
}

void Manager::on_pushButton_deleteEmployee_clicked()
{
    auto result = QMessageBox::question(0,0,"Вы уверены, что хотите удалить сотрудника ?",
                                        QMessageBox::Yes|QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
        QString itn = ui->lineEdit_itn->text();
        if(Database::removeEmployee(itn))
        {
            removeFromTableWidgetEmployee(itn);
            ui->stackedWidget->setCurrentIndex(Form::tables);
            QMessageBox::information(0,0,"Сотрудник удален");
        }
        else
        {
            QMessageBox::information(0,0,"Ошибка удаления!");
        }
    }
}

