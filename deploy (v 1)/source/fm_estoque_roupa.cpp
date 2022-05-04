#include "fm_estoque_roupa.h"
#include "ui_fm_estoque_roupa.h"

fm_estoque_roupa::fm_estoque_roupa(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_estoque_roupa)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		ui->lineQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));

		// Carregando estrutura de dados e tabela da janela.
		carregarTWGestao(gl_ed::roupa.getEd());
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_estoque_roupa::~fm_estoque_roupa()
{
	delete ui;
}

void fm_estoque_roupa::carregarTWGestao(std::set<obj_roupa>const *ed)
{
	std::set<obj_roupa>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->tw->insertRow(i);
		ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getId())));
		ui->tw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getRoupa())));
		if(!it->getQtd())
		{
			ui->tw->item(i, 0)->setTextColor("red");
			ui->tw->item(i, 1)->setTextColor("red");
		}
	}
}

void fm_estoque_roupa::on_btnAtualizar_clicked()
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

		obj_roupa antigo = gl_ed::roupa.encontrar(ui->tw->item(ui->tw->currentRow(), 0)->text().toStdString());
		obj_roupa novo = antigo;
		novo.setQtd(qtd.toInt());

		gl_ed::roupa.editar(antigo, novo);

		QMessageBox::information(this, "Informação", "Roupa editada com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (135)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (135)", "Erro desconhecido.");}
}

void fm_estoque_roupa::on_btnFiltro_clicked()
{
	try
	{
		ui->tw->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->tw);
		carregarTWGestao(gl_ed::roupa.getEd());
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

void fm_estoque_roupa::on_lineFiltro_textEdited(const QString &arg1)
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
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (228)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (228)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_estoque_roupa::on_tw_itemSelectionChanged()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) return;

		int linha = ui->tw->currentRow();

		obj_roupa roupa = gl_ed::roupa.encontrar(ui->tw->item(linha,0)->text().toStdString());

		ui->lineCodBarras->setText(QString::fromStdString(roupa.getId()));
		ui->lineQtd->setText(QString::number(roupa.getQtd()));
		ui->lineCor->setText(QString::fromStdString(roupa.getRoupa()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (257)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (257)", "Erro desconhecido.");}
}

void fm_estoque_roupa::on_lineFiltro_returnPressed()
{
	on_lineFiltro_textEdited(ui->lineFiltro->text());
}
