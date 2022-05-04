#include "fm_carregando.h"
#include "ui_fm_carregando.h"

fm_carregando::fm_carregando(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_carregando)
{
	ui->setupUi(this);
}

fm_carregando::~fm_carregando()
{
	delete ui;
}
