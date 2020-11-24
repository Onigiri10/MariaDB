#pragma once

#include <QtWidgets/QWidget>
#include "ui_mariadbtest.h"

class MariaDBTest : public QWidget
{
    Q_OBJECT

public:
    MariaDBTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::MariaDBTestClass ui;

private slots:
    void onClicked_conn();
    void onClicked_disconn();
};
