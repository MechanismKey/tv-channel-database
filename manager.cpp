#include "manager.h"
#include "ui_manager.h"

using std::unique_ptr;

Manager::Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->tableWidget_Employee->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget_Employee->setFocusPolicy(Qt::NoFocus);

    //ui->tableWidget_Employee->setSelectionBehavior(QAbstractItemView::AdjustToContentsOnFirstShow);

    loadAllTables();
    loadComboPost();
}

Manager::~Manager()
{
    delete ui;
}

int Manager::getCurrentPost()
{
    int id_post = Database::id_post(ui->comboBox_Post->currentText());

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

void Manager::loadComboPost()
{
    ui->comboBox_Post->addItems(Database::listPost());
}

//void Manager::loadTable(const int&& tableTitle, QTableView* tableView)
//{
//    model = new QSqlTableModel();

//    switch(tableTitle)
//    {
//    case Table::schedule:
//    {
//        model->setTable("Schedule");
//        model->setHeaderData(0,Qt::Horizontal, "Начало");
//        model->setHeaderData(1,Qt::Horizontal, "Контент");
//        model->setHeaderData(2,Qt::Horizontal, "Команда");
//    } break;

//    case Table::employee:
//    {
//        model->setTable("Employee");
//        model->setHeaderData(0,Qt::Horizontal, "Ф.И.О.");
//        model->setHeaderData(1,Qt::Horizontal, "Телефон");
//        model->setHeaderData(2,Qt::Horizontal, "Должность");
//        model->setHeaderData(3,Qt::Horizontal, "Зарплата");
//        model->setHeaderData(4,Qt::Horizontal, "Работает с");
//        model->setHeaderData(5,Qt::Horizontal, "Отпускные");
//        model->setHeaderData(6,Qt::Horizontal, "Больничные");
//    }break;

//    case Table::teamList:
//    {
//        model->setTable("TeamList");
//        model->setHeaderData(0,Qt::Horizontal, "Команда");
//        model->setHeaderData(1,Qt::Horizontal, "Работник");
//    }break;
//    };

//    model->select();
//    tableView->setModel(model);
//    tableView->resizeColumnsToContents();
//    tableView->show();
//}

void Manager::loadAllTables()
{
    Database::loadTable(Database::employee, ui->tableWidget_Employee);
}

void Manager::on_listWidget_itemSelectionChanged()
{
    ui->stackedWidget_Tables->setCurrentIndex(ui->listWidget->currentRow());
}

void Manager::on_pushButton_toAddEmployee_clicked()
{
    ui->stackedWidget->setCurrentIndex(Form::AddEmployee);
}

void Manager::on_pushButton_backFromAddEmployee_clicked()
{
    ui->stackedWidget->setCurrentIndex(Form::Tables);
}

void Manager::on_pushButton_toEditEmployee_clicked()
{
    QMessageBox::information(0,0,"Check!");
}

void Manager::on_pushButton_addEmployee_clicked()
{
        Passport passport(ui->lineEdit_Surname->text(), ui->lineEdit_Name->text(), ui->lineEdit_SecondName->text(),
                          ui->dateEdit_Birthday->date(), ui->lineEdit_itn->text().toInt());

        Employee employee(passport, ui->lineEdit_Phone->text(), getCurrentPost(), ui->lineEdit_Salary->text().toInt(),
                          ui->dateEdit_Recruitment->date());

        if(!employee.isValid())
        {
            QMessageBox::information(0,0,"Ошибка при добавлении");
            return;
        }

        if(Database::addEmployee(employee))
            QMessageBox::information(0,0,"Сотрудник добавлен");
        else
            QMessageBox::warning(0,0,"Ошибка! Сотрудник не добавлен");
}


void Manager::on_tableWidget_Employee_cellPressed(int row, int column)
{
    ui->stackedWidget->setCurrentIndex(Form::AddEmployee);
    //ui->tableWidget_Employee->clearSelection();

}
