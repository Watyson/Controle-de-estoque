#include "fm_estoque_esmalte.h"
#include "ui_fm_estoque_esmalte.h"

fm_estoque_esmalte::fm_estoque_esmalte(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_estoque_esmalte)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		// ========= Gestao esmalte
		// ========= ========= ========= =========
		ui->lineQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));

		// Carregando estrutura de dados e tabela da janela.
		carregarTWGestao(gl_ed::esmalte.getEd());
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_estoque_esmalte::~fm_estoque_esmalte()
{
	delete ui;
}

void fm_estoque_esmalte::carregarTWGestao(std::set<obj_esmalte>const *ed)
{
	std::set<obj_esmalte>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->tw->insertRow(i);
		ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getId())));
		ui->tw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getCor())));
		if(!it->getQtd())
		{
			ui->tw->item(i, 0)->setTextColor("red");
			ui->tw->item(i, 1)->setTextColor("red");
		}
	}
}

void fm_estoque_esmalte::on_btnAtualizar_clicked()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Editar"), tr("Tem certeza que deseja atualizar os dados?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		QString qtd	= ui->lineQtd->text();
		QString cor	= ui->lineCor->text();
		QString id	= ui->lineCodBarras->text();

		obj_esmalte antigo = gl_ed::esmalte.encontrar(ui->tw->item(ui->tw->currentRow(), 0)->text().toStdString());
		obj_esmalte novo = antigo;
		novo.setQtd(qtd.toInt());

		gl_ed::esmalte.editar(antigo, novo);

		QMessageBox::information(this, "Informação", "Esmalte Editado com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (135)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (135)", "Erro desconhecido.");}
}

void fm_estoque_esmalte::on_btnFiltro_clicked()
{
	try
	{
		ui->tw->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->tw);
		carregarTWGestao(gl_ed::esmalte.getEd());
		ui->tw->setSortingEnabled(true);

		ui->tw->setItemSelected(nullptr, -1);
		ui->lineQtd->setText("");
		ui->lineCor->setText("");
		ui->lineCodBarras->setText("");
		ui->lineFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (204)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (204)", "Erro desconhecido.");}
}

void fm_estoque_esmalte::on_lineFiltro_textEdited(const QString &arg1)
{
	std::vector<obj_esmalte> const * ed = nullptr;

	try
	{
		QString busca = "SELECT id, cor "
						"FROM tb_esmalte "
						"WHERE id like '%"+arg1+"%' OR cor like '%"+arg1+"%';";

		ed = gl_ed::esmalte.filtroEd(busca);

		gl_funcao::removerLinhas(ui->tw);
		ui->tw->setSortingEnabled(false);

		for(int i=0; i < int(ed->size()); ++i)
		{
			ui->tw->insertRow(i);
			ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getId())));
			ui->tw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getCor())));
		}
		ui->tw->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (228)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (228)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_estoque_esmalte::on_tw_itemSelectionChanged()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) return;

		int linha = ui->tw->currentRow();

		obj_esmalte esmalte = gl_ed::esmalte.encontrar(ui->tw->item(linha,0)->text().toStdString());

		ui->lineCodBarras->setText(QString::fromStdString(esmalte.getId()));
		ui->lineQtd->setText(QString::number(esmalte.getQtd()));
		ui->lineCor->setText(QString::fromStdString(esmalte.getCor()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (257)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (257)", "Erro desconhecido.");}
}

void fm_estoque_esmalte::on_lineFiltro_returnPressed()
{
	on_lineFiltro_textEdited(ui->lineFiltro->text());
}
