#include "fm_roupanovavenda_pesquisar.h"
#include "ui_fm_roupanovavenda_pesquisar.h"

fm_roupaNovaVenda_pesquisar::fm_roupaNovaVenda_pesquisar(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_roupaNovaVenda_pesquisar)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	on_lineFiltro_textEdited("");
}

fm_roupaNovaVenda_pesquisar::~fm_roupaNovaVenda_pesquisar()
{
	delete ui;
}

void fm_roupaNovaVenda_pesquisar::carregarTW(std::set<obj_roupa>const *ed)
{
	std::set<obj_roupa>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->tw->insertRow(i);
		ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getId())));
		ui->tw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getRoupa())));
	}
}

void fm_roupaNovaVenda_pesquisar::on_btnEditar_clicked()
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

void fm_roupaNovaVenda_pesquisar::on_btnExcluir_clicked()
{
	gl_variavel::editou = false;
	gl_variavel::id = "";
	close();
}

void fm_roupaNovaVenda_pesquisar::on_btnFiltro_clicked()
{
	try
	{
		ui->tw->setSortingEnabled(false);

		gl_funcao::removerLinhas(ui->tw);
		carregarTW(gl_ed::roupa.getEd());

		ui->tw->setSortingEnabled(true);

		ui->tw->setItemSelected(nullptr, -1);
		ui->lineQtd->setText("");
		ui->lineRoupa->setText("");
		ui->lineCodBarras->setText("");
		ui->lineValorUmC->setText("");
		ui->lineValorUmV->setText("");
		ui->lineFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (59)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (59)", "Erro desconhecido.");}
}

void fm_roupaNovaVenda_pesquisar::on_lineFiltro_textEdited(const QString &arg1)
{
	std::vector<obj_roupa> const * ed = nullptr;

	try
	{
		QString busca = "SELECT id, roupa "
						"FROM tb_roupa "
						"WHERE id like '%"+arg1+"%' OR roupa like '%"+arg1+"%';";

		ed = gl_ed::roupa.filtroEd(busca);

		gl_funcao::removerLinhas(ui->tw);
		ui->tw->setSortingEnabled(false);

		for(int i=0; i < int(ed->size()); ++i)
		{
			ui->tw->insertRow(i);
			ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getId())));
			ui->tw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getRoupa())));
		}
		ui->tw->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (30)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (30)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_roupaNovaVenda_pesquisar::on_tw_itemSelectionChanged()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) return;

		int linha = ui->tw->currentRow();

		obj_roupa obj = gl_ed::roupa.encontrar(ui->tw->item(linha,0)->text().toStdString());

		ui->lineCodBarras->setText(QString::fromStdString(obj.getId()));
		ui->lineQtd->setText(QString::number(obj.getQtd()));
		ui->lineRoupa->setText(QString::fromStdString(obj.getRoupa()));
		ui->lineValorUmC->setText(QString::number(obj.getVlrCompra()));
		ui->lineValorUmV->setText(QString::number(obj.getVlrVenda()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (83)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (83)", "Erro desconhecido.");}
}
