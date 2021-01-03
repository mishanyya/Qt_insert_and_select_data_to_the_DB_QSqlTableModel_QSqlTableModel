#include "mainwindow.h"
#include "ui_mainwindow.h"


//#include "QSqlDatabase"//для работы с БД
#include "QSqlQuery"//для работы с SQL запросами


#include "QTableView"//для работы с графическим выводом информации в виде таблиц

#include "QSqlTableModel" //класс для работы с редактируемой одиночной таблицей из БД
#include "QSqlRelationalTableModel" //класс для работы с редактируемой таблицей из БД с поддержкой внешних ключей
#include "QSqlQueryModel" //класс для работы с таблицей только для чтения из БД для вывода SQL запросов

static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");// db - это внешняя глобальная переменная, которую можно использовать тво всех файлах программы

QSqlTableModel *model = new QSqlTableModel; //создается глобальный объект модели таблицы с редактируемыми ячейками
QSqlQueryModel *model1 = new QSqlQueryModel; //создается объект модели с таблицей только для чтения

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTable();//запуск функции, выводящий базу данных сразу после запуска программы

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(workingdbsave())); //для сохранения изменений в БД
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(inserttodb())); //для вставки данных в БД
        }

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    //функция для сохранения изменений в БД
        void MainWindow::workingdbsave(){
            //подключить БД по ее адресу на компьютере
           db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
            //открывает базу данных, указанную в db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
            db.open();            
            //этот метод работает при настройке setEditStrategy(QSqlTableModel::OnManualSubmit)
            model->submitAll();//сохранить все изменения в таблице
    }

        //функция для вставки значений в БД
            void MainWindow::inserttodb(){
                //подключить БД по ее адресу на компьютере
               db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
                //открывает базу данных, указанную в db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
                db.open();
                //ввод данных из полей в переменные
                QString vname=ui->lineEdit->text();
                QString vfone=ui->lineEdit_2->text();
                QString vautomodel=ui->lineEdit_3->text();
                QString vprice=ui->lineEdit_4->text();
                //создание объекта для запроса
                QSqlQuery query;
                //создание подготовленного запроса
                   query.prepare("INSERT INTO basetable (name, fone,automodel,price) VALUES (:name, :fone,:automodel,:price)");
                   //вставка знасений в запрос
                   query.bindValue(":name", vname);
                   query.bindValue(":fone", vfone);
                   query.bindValue(":automodel", vautomodel);
                   query.bindValue(":price", vprice);
                   //исполнение SQL запроса
                   query.exec();
        }

        //функция, которая должна выводить базу данных в таблице при запуске программы
        void MainWindow::createTable(){
                //Общий код для QSqlTableModel, QSqlRelationalTableModel и QSqlQueryModel:
                //подключить БД по ее адресу на компьютере
               db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
                //открывает базу данных, указанную в db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
                db.open();

               //Код для QSqlTableModel и QSqlRelationalTableModel - таблиц с редактируемыми ячейками
               //QSqlRelationalTableModel работает также как QSqlTableModel, но позволяет настройку внешних ключей с другими таблицами
                       model->setTable("basetable");//выбирается существующая табл БД
                       //Возможны значения для редактирования записей:
                       model->setEditStrategy(QSqlTableModel::OnManualSubmit);//настраивается редактирование таблицы
                       //model->setEditStrategy(QSqlTableModel::OnFieldChange);//данные сохранятся в БД сразу при переходе на другую ячейку
                       //model->setEditStrategy(QSqlTableModel::OnRowChange);//данные сохранятся в БД сразу при переходе на другую строку
                       model->select();//заполняет модель данными из таблицы, без этого кода выйдет пустая таблица
                       ui->tableView->setModel(model);//выводит в виде таблицы все элементы в окне приложения


 /*
              //Код для QSqlQueryModel - таблиц только для чтения информации через запросы SQL
                    model1->setQuery("SELECT * FROM basetable");//в модель помещается результат SQL запроса к существующим в БД, таблице и полям
                    ui->tableView->setModel(model1);//выводит в виде таблицы все элементы в окне приложения, не работает в функции main()
*/
        }
