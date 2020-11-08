#include "mainwindow.h"
#include "ui_mainwindow.h"


//#include "QSqlDatabase"//для работы с БД
//#include "QSqlQuery"//для работы с SQL запросами


#include "QTableView"//для работы с графическим выводом информации в виде таблиц

#include "QSqlTableModel" //class provides an editable data model for a single database table.
#include "QSqlRelationalTableModel" //class provides an editable data model for a single database table, with foreign key support.
#include "QSqlQueryModel" //class provides a read-only data model for SQL result sets

//#include "QDebug"
//#include "QLabel"

static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");// db - это внешняя глобальная переменная, которую можно использовать тво всех файлах программы
//static QSqlTableModel model;

QSqlTableModel *model = new QSqlTableModel; //создается объект модели


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTable();//запуск функции, выводящий базу данных сразу после запуска программы

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(workingdbsave())); //для сохранения изменений в БД
        }

    MainWindow::~MainWindow()
    {
        delete ui;
    }


//функция для добавлени строки в таблицу БД
    void MainWindow::workingdbsavecansel(){

        //Общие действия 1:
        //подключить БД по ее адресу на компьютере
       db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
        //открывает базу данных, указанную в db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
        db.open();

}

    //функция для сохранения изменений в БД
        void MainWindow::workingdbsave(){

            //Общие действия 1:
            //подключить БД по ее адресу на компьютере
           db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
            //открывает базу данных, указанную в db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
            db.open();
model->submitAll();//сохранить все изменения в таблице
//этот метод необходим при настройке setEditStrategy(QSqlTableModel::OnManualSubmit)
    }

        //функция, которая должна выводить базу данных в таблице при запуске программы
        void MainWindow::createTable(){
            //автоматический вывод таблицы при заппуске программы
                //начало кода вывода программы

                //Общие действия 1:
                //подключить БД по ее адресу на компьютере
               db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
                //открывает базу данных, указанную в db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
                db.open();

               //Различия в применении QSqlTableModel и QSqlRelationalTableModel - таблицы с редактируемыми ячейками

               //QSqlRelationalTableModel работает как QSqlTableModel, но позволяет настройку внешних ключей с другими таблицами
                       //QSqlTableModel *model = new QSqlTableModel; //создается объект модели - делаем глобальным этот объект, разместив вне функции
                       model->setTable("basetable");//выбирается существующая табл БД
                       //Возможны значения для редактирования записей:
                       model->setEditStrategy(QSqlTableModel::OnManualSubmit);//настраивается редактирование таблицы
                       //model->setEditStrategy(QSqlTableModel::OnFieldChange);//данные сохранятся в БД сразу при переходе на другую ячейку
                       //model->setEditStrategy(QSqlTableModel::OnRowChange);//данные сохранятся в БД сразу при переходе на другую строку


                       model->select();//заполняет модель данными из таблицы, без этого кода выйдет пустая таблица

            /*
                //Различия в применении QSqlQueryModel - только читает информацию через запросы SQL

                    QSqlQueryModel *model = new QSqlQueryModel; //создается объект модели
                    model->setQuery("SELECT * FROM basetable");//в модель помещается результат SQL запроса к существующим в БД, таблице и полям
            */


                    //Общие действия 2:

                    //QTableView *view = new QTableView;//создается объект TableView

                       // Устанавливаем режим выделения лишь одно строки в таблице
                   ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

                   ui->tableView->setModel(model);//выводит в виде таблицы все элементы в окне приложения, не работает в функции main()

                    //view->show();//создает отдельное окно для таблицы

                //конец кода вывода программы
        }
