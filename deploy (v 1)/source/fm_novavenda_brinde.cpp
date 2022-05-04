#include "fm_novavenda_brinde.h"
#include "ui_fm_novavenda_brinde.h"

fm_novaVenda_brinde::fm_novaVenda_brinde(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_novaVenda_brinde)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	ui->setupUi(this);

	ui->lineQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));

	carregarTWGestao(gl_ed::brinde.getEd());
}

fm_novaVenda_brinde::~fm_novaVenda_brinde()
{
	delete ui;
}

void fm_novaVenda_brinde::carregarTWGestao(std::set<obj_brinde>const *ed)
{
	std::set<obj_brinde>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->tw->insertRow(i);
		ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getNome())));
	}
}

void fm_novaVenda_brinde::on_lineFiltro_textEdited(const QString &arg1)
{
	std::vector<obj_brinde> const * ed = nullptr;

	try
	{
		QString busca = "SELECT nome "
						"FROM tb_brinde "
						"WHERE nome like '%"+arg1+"%';";

		ed = gl_ed::brinde.filtroEd(busca);

		gl_funcao::removerLinhas(ui->tw);

		ui->tw->setSortingEnabled(false);
		for(int i=0; i < int(ed->size()); ++i)
		{
			ui->tw->insertRow(i);
			ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getNome())));
		}
		ui->tw->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (228)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (228)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_novaVenda_brinde::on_btnFiltro_clicked()
{
	try
	{
		ui->tw->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->tw);
		carregarTWGestao(gl_ed::brinde.getEd());
		ui->tw->setSortingEnabled(true);

		ui->tw->setItemSelected(nullptr, -1);
		ui->lineQtd->setText("");
		ui->lineNome->setText("");
		ui->lineFiltro->setText("");
		ui->lbEstoque->setText("Em estoque: 0");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (204)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (204)", "Erro desconhecido.");}
}

void fm_novaVenda_brinde::on_tw_itemSelectionChanged()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) return;

		int linha = ui->tw->currentRow();

		obj_brinde brinde = gl_ed::brinde.encontrar(ui->tw->item(linha,0)->text().toStdString());

		ui->lineNome->setText(QString::fromStdString(brinde.getNome()));
		ui->lineQtd->setText("1");
		ui->lbEstoque->setText("Em estoque: "+QString::number(brinde.getQtd()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (257)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (257)", "Erro desconhecido.");}
}

void fm_novaVenda_brinde::on_lineQtd_textEdited(const QString &arg1)
{
	if(ui->tw->currentItem() == nullptr) return;
	obj_brinde brinde = gl_ed::brinde.encontrar(ui->tw->item(ui->tw->currentRow(),0)->text().toStdString());

	if(brinde.getQtd() <= arg1.toInt() || !brinde.getQtd())
	{
		ui->lbQtd->setStyleSheet("QLabel{ "
								  "background:#e8e8e8;"
								  "color:red;"
								  "font-size:10pt;"
								  "border:none;"
								  "border-radius:6px;}");

		ui->lineQtd->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
									"QLineEdit:disabled{background:#e7e7e7;}"
									"QLineEdit{"
									"color:red;"
									"font-size:9pt;"
									"border-radius:7px;"
									"border:1px solid black;}");
	}
	else
	{
		ui->lbQtd->setStyleSheet("QLabel{ "
								  "background:#e8e8e8;"
								  "color:#808080;"
								  "font-size:10pt;"
								  "border:none;"
								  "border-radius:6px;}");

		ui->lineQtd->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
									"QLineEdit:disabled{background:#e7e7e7;}"
									"QLineEdit{"
									"color:black;"
									"font-size:9pt;"
									"border-radius:7px;"
									"border:1px solid black;}");
	}
}

void fm_novaVenda_brinde::on_btnEditar_clicked()
{
	try
	{
		obj_brinde antigo = gl_ed::brinde.encontrar(ui->tw->item(ui->tw->currentRow(),0)->text().toStdString());

		if(antigo.getQtd() < ui->lineQtd->text().toInt()) throw QString("Quantidade maior do que o estoque do produto.");

		obj_brinde novo = antigo;
		novo.setQtd(novo.getQtd() - ui->lineQtd->text().toInt());

		gl_ed::brinde.editar(antigo, novo);

		QMessageBox::information(this, "Informação", "Estoque do brinde atualizado com sucesso.");

		close();
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (257)", QString::fromStdString(e));}
	catch(QString &e)	{QMessageBox::warning(this, "Informação", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (257)", "Erro desconhecido.");}
}
