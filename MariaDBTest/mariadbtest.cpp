#include "mariadbtest.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

MariaDBTest::MariaDBTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.pB_connect,&QPushButton::clicked,this,&MariaDBTest::onClicked_conn);
    connect(ui.pB_disconnect, &QPushButton::clicked, this, &MariaDBTest::onClicked_disconn);
    
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "firstConn"); //возвращает ссылку (стат)
    db.setHostName(ui.lE_host->text());
    db.setPort(ui.lE_port->text().toInt());
    db.setDatabaseName(ui.lE_DB->text());
    db.setUserName(ui.lE_name->text());
    db.setPassword(ui.lE_password->text()); // ? Виден пароль. Иначе не подключается
}

void MariaDBTest::onClicked_conn()
{
    QSqlDatabase db = QSqlDatabase::database("firstConn", false); //получаем объект при помощи имени соеднения
    if (!db.open())
    {
        ui.textEdit->append(db.lastError().text());
        return;
    }
    ui.textEdit->append(u8"Успешное соединение");
    ui.pB_connect->setDisabled(true);
    ui.pB_disconnect->setDisabled(false);

    QSqlQuery q(db); //запрос к БД
    q.prepare(
        "SELECT a.Name FROM book b "
		"INNER JOIN author a ON b.ID_Author = a.ID "
		"WHERE b.Name = :bk" 
        );
    q.bindValue(":bk", u8"Книга1"); // вместо плейсхолдера bk подставляем значение (QVariant)
    if (!q.exec())
    {
        ui.textEdit->append(q.lastError().text());
        return;
    }
    while (q.next()) //перемещение по кортежам (1 кортеж - совокупность полей/значений [столбцов] в запросе SELECT)
    {
        QString str = q.value("Name").toString(); //обращение к столбцу "Name"
        ui.textEdit->append(str);
    }
    ui.lE_host->setDisabled(true);
    ui.lE_port->setDisabled(true);
    ui.lE_name->setDisabled(true);
    ui.lE_password->setDisabled(true);
    ui.lE_DB->setDisabled(true);
}

void MariaDBTest::onClicked_disconn()
{
    QSqlDatabase db = QSqlDatabase::database("firstConn", false);
    if (db.isOpen())
    {
        db.close();
    }
	ui.pB_connect->setDisabled(false);
	ui.pB_disconnect->setDisabled(true);
	ui.lE_host->setDisabled(false);
	ui.lE_port->setDisabled(false);
	ui.lE_name->setDisabled(false);
	ui.lE_password->setDisabled(false);
	ui.lE_DB->setDisabled(false);
}
