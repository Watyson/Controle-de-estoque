#include "fm_novavenda_pesquisar.h"
#include "ui_fm_novavenda_pesquisar.h"

fm_novaVenda_pesquisar::fm_novaVenda_pesquisar(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_novaVenda_pesquisar)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	on_lineFiltro_textEdited("");
}

fm_novaVenda_pesquisar::~fm_novaVenda_pesquisar()
{
	delete ui;
}

void fm_novaVenda_pesquisar::carregarTWGestao(std::set<obj_esmalte>const *ed)
{
	std::set<obj_esmalte>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->twGestao->insertRow(i);
		ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getId())));
		ui->twGestao->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getCor())));
	}
}

void fm_novaVenda_pesquisar::on_lineFiltro_textEdited(const QString &arg1)
{
	std::vector<obj_esmalte> const * ed = nullptr;

	try
	{
		QString busca = "SELECT id, cor "
						"FROM tb_esmalte "
						"WHERE id like '%"+arg1+"%' OR cor like '%"+arg1+"%';";

		ed = gl_ed::esmalte.filtroEd(busca);

		gl_funcao::removerLinhas(ui->twGestao);
		ui->twGestao->setSortingEnabled(false);

		for(int i=0; i < int(ed->size()); ++i)
		{
			ui->twGestao->insertRow(i);
			ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getId())));
			ui->twGestao->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getCor())));
		}
		ui->twGestao->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (30)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (30)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_novaVenda_pesquisar::on_btnFiltro_clicked()
{
	try
	{
		ui->twGestao->setSortingEnabled(false);

		gl_funcao::removerLinhas(ui->twGestao);
		carregarTWGestao(gl_ed::esmalte.getEd());

		ui->twGestao->setSortingEnabled(true);

		ui->twGestao->setItemSelected(nullptr, -1);
		ui->lineQtd->setText("");
		ui->lineCor->setText("");
		ui->lineCodBarras->setText("");
		ui->lineValorUmC->setText("");
		ui->lineValorUmV->setText("");
		ui->lineValorDesc->setText("");
		ui->lineFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (59)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (59)", "Erro desconhecido.");}
}

void fm_novaVenda_pesquisar::on_twGestao_itemSelectionChanged()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) return;

		int linha = ui->twGestao->currentRow();

		obj_esmalte esmalte = gl_ed::esmalte.encontrar(ui->twGestao->item(linha,0)->text().toStdString());

		ui->lineCodBarras->setText(QString::fromStdString(esmalte.getId()));
		ui->lineQtd->setText(QString::number(esmalte.getQtd()));
		ui->lineCor->setText(QString::fromStdString(esmalte.getCor()));
		ui->lineValorUmC->setText(QString::number(esmalte.getValorUmCompra()));
		ui->lineValorUmV->setText(QString::number(esmalte.getValorUm()));
		ui->lineValorDesc->setText(QString::number(esmalte.getValorUmDesconto()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (83)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (83)", "Erro desconhecido.");}
}

void fm_novaVenda_pesquisar::on_btnCancelar_clicked()
{
	gl_variavel::editou = false;
	gl_variavel::id = "";
	close();
}

void fm_novaVenda_pesquisar::on_btnConfirmar_clicked()
{
	try
	{
		if(!ui->lineCodBarras->text().size())	throw std::string("Nenhum item selecionado.");

		gl_variavel::editou = true;
		gl_variavel::id = ui->lineCodBarras->text().toStdString();
		close();
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (111)", "Erro crítico.");}
}
