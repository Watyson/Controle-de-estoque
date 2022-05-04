#include "fm_novavenda_finalizar.h"
#include "ui_fm_novavenda_finalizar.h"

fm_novaVenda_finalizar::fm_novaVenda_finalizar(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_novaVenda_finalizar)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	carregarTW(gl_ed::cliente.getEd());
}

fm_novaVenda_finalizar::~fm_novaVenda_finalizar()
{
	delete ui;
}

void fm_novaVenda_finalizar::carregarTW(std::set<obj_cliente>const *ed)
{
	std::set<obj_cliente>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		int linha = ui->twGestao->rowCount();
		ui->twGestao->insertRow(linha);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(it->getNome())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(it->getTel().formatoTel())));
	}
}

void fm_novaVenda_finalizar::on_btnSelecionar_clicked()
{
	try
	{
		if(ui->cbTipoPgmt->currentText() == "Comodato" && ui->twGestao->item(ui->twGestao->currentRow(),0)->text() == "Desconhecido")
			throw QString("Alguem desconhecido não pode efetuar esse tipo de pagamento.");
		if(!ui->cbTipoPgmt->currentText().size()) throw QString("Selecione um tipo de pagamento.");
		if(ui->twGestao->currentItem() == nullptr || !ui->lineNome->text().size()) throw QString("Selecione um cliente.");

		gl_variavel::nomeCliente= ui->lineNome->text().toStdString();
		gl_variavel::tipoPgmt	= ui->cbTipoPgmt->currentText().toStdString();
		gl_variavel::finalizou	= true;

		close();
	}
	catch(QString &e)		{QMessageBox::warning(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (38)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (38)", "Erro desconhecido.");}
}

void fm_novaVenda_finalizar::on_btnFiltro_2_clicked()
{
	try
	{
		ui->twGestao->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->twGestao);
		carregarTW(gl_ed::cliente.getEd());
		ui->twGestao->setSortingEnabled(true);

		ui->twGestao->setItemSelected(nullptr, -1);

		ui->lineNome->setText("");
		ui->lineTel->setText("");
		ui->lineRef->setText("");
		ui->lineCep->setText("");
		ui->lineCnpj->setText("");
		ui->lineFiltro_2->setText("");
		ui->lineCpf->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (54)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (54)", "Erro desconhecido.");}
}

void fm_novaVenda_finalizar::on_twGestao_itemSelectionChanged()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) return;

		int linha = ui->twGestao->currentRow();

		obj_cliente cliente = gl_ed::cliente.encontrar(ui->twGestao->item(linha,0)->text().toStdString(),
							  obj_telefone::formatoNum(ui->twGestao->item(linha,1)->text().toStdString()));

		ui->lineNome->setText(QString::fromStdString(cliente.getNome()));
		ui->lineTel->setText(QString::fromStdString(cliente.getTel().numero()));
		ui->lineEnd->setText(QString::fromStdString(cliente.getEnd()));
		ui->lineRef->setText(QString::fromStdString(cliente.getRef()));
		ui->lineCep->setText(QString::fromStdString(cliente.getCep().getCep()));
		ui->lineCnpj->setText(QString::fromStdString(cliente.getCnpj().getCnpj()));
		ui->lineCpf->setText(QString::fromStdString(cliente.getCpf()));

		gl_variavel::idCliente = cliente.getId();
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (76)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (76)", "Erro desconhecido.");}
}

void fm_novaVenda_finalizar::on_lineFiltro_2_textEdited(const QString &arg1)
{
	std::vector<obj_cliente> const * ed = nullptr;

	try
	{
		QString busca = "SELECT nome, tel "
						"FROM tb_pessoas, tb_clientes "
						"WHERE id=id_pessoa AND nome like '%"+arg1+"%' OR id=id_pessoa AND tel like '%"+arg1+"%';";

		ed = gl_ed::cliente.filtroEd(busca);

		ui->twGestao->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->twGestao);

		for(int i=0; i < int(ed->size()); ++i)
		{
			int linha = ui->twGestao->rowCount();
			ui->twGestao->insertRow(linha);
			ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getNome())));
			ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getTel().formatoTel())));
		}
		ui->twGestao->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (100)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (100)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_novaVenda_finalizar::on_btnCadastrar_clicked()
{
	fm_novaVenda_cadastroCliente a;
	a.exec();

	gl_funcao::removerLinhas(ui->twGestao);
	carregarTW(gl_ed::cliente.getEd());
}

void fm_novaVenda_finalizar::on_btnBrinde_clicked()
{
	fm_novaVenda_brinde a;
	a.exec();
}
