#include "fm_relatorio_comodato.h"
#include "ui_fm_relatorio_comodato.h"

fm_relatorio_comodato::fm_relatorio_comodato(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_relatorio_comodato)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		ui->tw->setColumnWidth(0, 250);
		ui->tw->setColumnWidth(1, 75);
		ui->tw->setColumnWidth(2, 75);

		ui->btnStatus->setText("");

		ui->rbPago->setChecked(false);
		ui->rbPendente->setChecked(false);

		relatorio.carregarEd();
		on_lineFiltro_textEdited("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_relatorio_comodato::~fm_relatorio_comodato()
{
	delete ui;
}

void fm_relatorio_comodato::carregarTWGestao(std::set<obj_dadosComodato>const *ed)
{
	ui->tw->setSortingEnabled(false);
	std::set<obj_dadosComodato>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->tw->insertRow(i);
		ui->tw->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getCliente())));
		ui->tw->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getData())));
		ui->tw->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(it->getHora())));

		QString status	= "Pendente";
		QString cor		= "red";
		if(it->getStatus())
		{
			status	= "Pago";
			cor		= "green";
		}
		ui->tw->setItem(i, 3, new QTableWidgetItem(status));
		ui->tw->item(i, 3)->setTextColor(QColor(cor));
	}
	ui->tw->setSortingEnabled(true);
}

void fm_relatorio_comodato::on_btnStatus_clicked()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) throw QString("Nenhum item selecionado.");
		if(ui->btnStatus->text() == "Pago") return;

		QMessageBox messageBox(QMessageBox::Question, tr("Quitar"), tr("Tem certeza que deseja quitar a dívida?\nAção não pode ser desfeita."), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		obj_dadosComodato aux;
		aux.setCliente	(ui->tw->item(ui->tw->currentRow(), 0)->text().toStdString());
		aux.setData		(ui->tw->item(ui->tw->currentRow(), 1)->text().toStdString());
		aux.setHora		(ui->tw->item(ui->tw->currentRow(), 2)->text().toStdString());
		aux = relatorio.getComodato(aux);

		relatorio.confirmarPagamento(aux);

		ui->tw->item(ui->tw->currentRow(), 3)->setText("Pago");
		ui->tw->item(ui->tw->currentRow(), 3)->setTextColor(QColor("green"));

		ui->btnStatus->setText("Pago");
		ui->btnStatus->setStyleSheet("QPushButton:enabled{background:#7dbe50;}"
									 "QPushButton:disabled{background:#aaff7f;}"
									 "QPushButton:pressed{background:#aaff00;}"
									 "QPushButton{"
									 "color:#ffffff;"
									 "font-size:9pt;"
									 "border:none;"
									 "border-radius:10px;"
									 "border:1px solid black;}");

		QMessageBox::information(this, "Sucesso", "Pagamento quitado com sucesso.");
	}
	catch(QString &e)	{QMessageBox::warning(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (59)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (59)", "Erro desconhecido.");}
}

void fm_relatorio_comodato::on_tw_itemSelectionChanged()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) return;

		obj_dadosComodato aux;
		aux.setCliente	(ui->tw->item(ui->tw->currentRow(), 0)->text().toStdString());
		aux.setData		(ui->tw->item(ui->tw->currentRow(), 1)->text().toStdString());
		aux.setHora		(ui->tw->item(ui->tw->currentRow(), 2)->text().toStdString());

		if(ui->tw->item(ui->tw->currentRow(), 3)->text() == "Pendente")
		{
			aux.setStatus(false);
			ui->btnStatus->setStyleSheet("QPushButton:enabled{background:#faa91d;}"
										 "QPushButton:disabled{background:#fabe50;}"
										 "QPushButton:pressed{background:#ffd500;}"
										 "QPushButton{"
										 "color:#ffffff;"
										 "font-size:9pt;"
										 "border:none;"
										 "border-radius:10px;"
										 "border:1px solid black;}");
		}
		else
		{
			aux.setStatus(true);
			ui->btnStatus->setStyleSheet("QPushButton:enabled{background:#7dbe50;}"
										 "QPushButton:disabled{background:#aaff7f;}"
										 "QPushButton:pressed{background:#aaff00;}"
										 "QPushButton{"
										 "color:#ffffff;"
										 "font-size:9pt;"
										 "border:none;"
										 "border-radius:10px;"
										 "border:1px solid black;}");
		}

		obj_dadosComodato dado=relatorio.getComodato(aux);

		ui->btnStatus->setText		(ui->tw->item(ui->tw->currentRow(), 3)->text());
		ui->lineData->setText		(QString::fromStdString(dado.getData()));
		ui->lineHora->setText		(QString::fromStdString(dado.getHora()));
		ui->lineValor->setText		(QString::number(dado.getValor()));
		ui->lineCliente->setText	(QString::fromStdString(dado.getCliente()));
		ui->lineVendedor->setText	(QString::fromStdString(dado.getVendedor()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (92)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (92)", "Erro desconhecido.");}
}

void fm_relatorio_comodato::on_btnFiltro_clicked()
{
	try
	{
		gl_funcao::removerLinhas	(ui->tw);
		on_lineFiltro_textEdited	("");
		ui->btnStatus->setText		("");
		ui->lineData->setText		("");
		ui->lineHora->setText		("");
		ui->lineValor->setText		("");
		ui->lineCliente->setText	("");
		ui->lineVendedor->setText	("");
		ui->rbPago->setChecked		(false);
		ui->rbPendente->setChecked	(false);
		ui->btnStatus->setStyleSheet("QPushButton:enabled{background:#e0e0e0;}"
									 "QPushButton:disabled{background:#e0e0e0;}"
									 "QPushButton:pressed{background:#e0e0e0;}"
									 "QPushButton{"
									 "color:#404040;"
									 "font-size:9pt;"
									 "border:none;"
									 "border-radius:10px;"
									 "border:1px solid black;}");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (127)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (127)", "Erro desconhecido.");}
}

void fm_relatorio_comodato::on_lineFiltro_textEdited(const QString &arg1)
{
	std::set<obj_dadosComodato> const * ed = nullptr;
	try
	{
		QString status="0";
		if(ui->rbPago->isChecked()) status="1";

		QString busca = "SELECT A.status, A.data, A.hora, \"vendedor\", \"cliente\", valor_total "
						"FROM("
							"(SELECT status, data, hora, P.nome\"vendedor\", V.valor_total "
								"FROM tb_comodato as C, tb_vendas as V, tb_pessoas as P "
								"WHERE C.id_venda = V.id AND V.id_vendedor = P.id) as A "
							"INNER JOIN "
							"(SELECT status, data, hora, P.nome\"cliente\", V.valor_total\"valor\" "
								"FROM tb_comodato as C, tb_vendas as V, tb_pessoas as P "
								"WHERE C.id_venda = V.id AND V.id_cliente = P.id) as B "
							"ON A.hora = B.hora) "
						"WHERE A.status = "+status+" AND \"cliente\" like '%"+arg1+"%';";

		ed = relatorio.buscaComodato(busca.toStdString());
		gl_funcao::removerLinhas(ui->tw);
		carregarTWGestao(ed);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (146)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (146)", "Erro desconhecido.");}
	if(ed)	delete ed;
}

void fm_relatorio_comodato::on_rbPendente_clicked()
{
	on_btnFiltro_clicked();
	fm_relatorio_comodato::on_lineFiltro_textEdited(ui->lineFiltro->text());
}

void fm_relatorio_comodato::on_rbPago_clicked()
{
	on_btnFiltro_clicked();
	fm_relatorio_comodato::on_lineFiltro_textEdited(ui->lineFiltro->text());
}
