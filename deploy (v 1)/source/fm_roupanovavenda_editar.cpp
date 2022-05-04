#include "fm_roupanovavenda_editar.h"
#include "ui_fm_roupanovavenda_editar.h"

fm_roupaNovaVenda_editar::fm_roupaNovaVenda_editar(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_roupaNovaVenda_editar)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui->lb_estoque->setText("Em estoque disponível: "+QString::number(gl_variavel::estoque));
	ui->line_qtd->setText(QString::number(gl_variavel::qtd));
}

fm_roupaNovaVenda_editar::~fm_roupaNovaVenda_editar()
{
	delete ui;
}

void fm_roupaNovaVenda_editar::on_btn_ok_clicked()
{
	try
	{
		if(ui->line_qtd->text().toInt() < 1)					throw std::string("Quantidade inválida.");
		if(gl_variavel::estoque < ui->line_qtd->text().toInt()) throw std::string("Estoque insuficiente.");
		if(gl_variavel::qtd == ui->line_qtd->text().toInt())	on_btn_cancel_clicked();

		gl_variavel::editou = true;
		gl_variavel::qtd = ui->line_qtd->text().toInt();
		close();
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (20)", "Erro crítico.");}
}

void fm_roupaNovaVenda_editar::on_btn_cancel_clicked()
{
	gl_variavel::editou = false;
	close();
}
