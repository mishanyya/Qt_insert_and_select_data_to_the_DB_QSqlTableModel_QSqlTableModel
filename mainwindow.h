#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
void createTable();// это созданный нами слот для вывода БД при запуске
void workingdbsave();// это созданный нами слот для сохранения изменений в БД
void workingdbsavecansel();// это созданный нами слот для отмены сохранения изменений в БД

};
#endif // MAINWINDOW_H
