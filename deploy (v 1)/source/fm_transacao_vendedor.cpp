#include "fm_transacao_vendedor.h"
#include "ui_fm_transacao_vendedor.h"

fm_transacao_vendedor::fm_transacao_vendedor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_transacao_vendedor)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		QDate max = QDate::currentDate();
		QDate min;
		min.setDate(2021, 1, 1);

		ui->dateInicial->setDateRange(min, max);
		ui->dateFinal->setDateRange(min, max);
		ui->dateFinal->setDate(max);

		ui->twProdutos->setColumnWidth(0, 200);
		ui->twProdutos->setColumnWidth(1, 75);
		ui->twProdutos->setColumnWidth(2, 75);
		ui->twProdutos->setColumnWidth(3, 75);

		ui->twVendedor->setColumnWidth(0, 75);
		ui->twVendedor->setColumnWidth(1, 75);
		ui->twVendedor->setColumnWidth(2, 75);
		ui->twVendedor->setColumnWidth(3, 200);
		ui->twVendedor->setColumnWidth(4, 100);
		ui->twVendedor->setColumnWidth(5, 75);

		on_lineVendedor_textEdited(ui->lineVendedor->text());
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::information(this, "Erro", e);}
	catch(...)	{QMessageBox::warning(this, "Erro (4)", "Erro desconhecido.");}
}

fm_transacao_vendedor::~fm_transacao_vendedor()
{
	delete ui;
}

void fm_transacao_vendedor::carregarTWVendedor(std::set<obj_dadosVendedor>const *ed)
{
	gl_funcao::removerLinhas(ui->twVendedor);
	ui->twVendedor->setSortingEnabled(false);
	std::set<obj_dadosVendedor>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->twVendedor->insertRow(i);
		ui->twVendedor->setItem(i, 0, new QTableWidgetItem(QString::number(it->getId())));
		ui->twVendedor->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getData())));
		ui->twVendedor->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(it->getHora())));
		ui->twVendedor->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(it->getVendedor())));
		ui->twVendedor->setItem(i, 4, new QTableWidgetItem(QString::number(it->getValorVenda(), 'f', 2)));
		ui->twVendedor->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(it->getTipoPagamento())));
	}
	ui->twVendedor->setSortingEnabled(true);
}

void fm_transacao_vendedor::carregarTWVendas(std::set<obj_dadosEsmalte>const *ed)
{
	gl_funcao::removerLinhas(ui->twProdutos);
	ui->twProdutos->setSortingEnabled(false);
	std::set<obj_dadosEsmalte>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->twProdutos->insertRow(i);
		try
		{
			if(gl_ed::esmalte.existeCor(it->getProduto()))
			{
				ui->twProdutos->setItem(i, 0, new QTableWidgetItem("Esmalte "+QString::fromStdString(it->getProduto())));
			}
			else
			{
				ui->twProdutos->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getProduto())));
			}
		}
		catch (...){}
		ui->twProdutos->setItem(i, 1, new QTableWidgetItem(QString::number(it->getQtd())));
		ui->twProdutos->setItem(i, 2, new QTableWidgetItem(QString::number(it->getValorUm(), 'f', 2)));
		ui->twProdutos->setItem(i, 3, new QTableWidgetItem(QString::number(it->getValorTotal(), 'f', 2)));
	}
	ui->twProdutos->setSortingEnabled(true);
}

void fm_transacao_vendedor::on_twVendedor_itemSelectionChanged()
{
	try
	{
		if(ui->twVendedor->currentItem() == nullptr) return;

		QString idVenda = ui->twVendedor->item(ui->twVendedor->currentRow(), 0)->text();
		std::string busca;

		if(ui->rbRoupa->isChecked()){
			busca = "SELECT roupa, qtd, valor_um, valor_total "
					"FROM tb_produtos_vendidos, (SELECT id, roupa FROM tb_roupa) as A "
					"WHERE id_produto = A.id AND id_venda = "+idVenda.toStdString()+";";
		}
		else{
			busca = "SELECT cor, qtd, valor_um, valor_total "
					"FROM tb_produtos_vendidos, (SELECT id, cor FROM tb_esmalte) as A "
					"WHERE id_produto = A.id AND id_venda = "+idVenda.toStdString()+";";
		}

		std::set<obj_dadosEsmalte>const *ed = gl_ed::relatorios.buscaEsmalte(busca);

		carregarTWVendas(ed);
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::information(this, "Erro", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (47)", "Erro crítico.");}
}

void fm_transacao_vendedor::on_lineVendedor_textEdited(const QString &arg1)
{
	try
	{
		QDate i(ui->dateInicial->date().year(), ui->dateInicial->date().month(), ui->dateInicial->date().day());
		QDate f(ui->dateFinal  ->date().year(), ui->dateFinal  ->date().month(), ui->dateFinal  ->date().day());

		std::string dataIni = i.toString("yyyy-MM-dd").toStdString();
		std::string dataFim = f.toString("yyyy-MM-dd").toStdString();

		char tv='e';
		if(ui->rbRoupa->isChecked()) tv = 'r';

		std::string busca = "SELECT tb_vendas.id, data, hora, nome\"vendedor\", valor_total, tipo_pgmt "
							"FROM tb_vendas, tb_pessoas "
							"WHERE id_vendedor=tb_pessoas.id "
								"AND \"vendedor\" like '%"+arg1.toStdString()+"%' "
								"AND data BETWEEN '"+dataIni+"' and '"+dataFim+"' "
								"AND tipo_venda = '"+tv+"';";

		gl_funcao::removerLinhas(ui->twProdutos);
		std::set<obj_dadosVendedor>const *ed = gl_ed::relatorios.buscaVendedor(busca);
		carregarTWVendedor(ed);
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::information(this, "Erro", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (47)", "Erro crítico.");}
}

void fm_transacao_vendedor::on_pushButton_2_clicked()
{
	gl_funcao::removerLinhas(ui->twProdutos);
	on_lineVendedor_textEdited(ui->lineVendedor->text());

	ui->dateInicial->setDate(QDate(2021,1,1));
	ui->dateFinal->setDate(QDate::currentDate());
}

void fm_transacao_vendedor::on_dateInicial_userDateChanged()
{
	on_lineVendedor_textEdited(ui->lineVendedor->text());
}

void fm_transacao_vendedor::on_dateFinal_userDateChanged()
{
	on_lineVendedor_textEdited(ui->lineVendedor->text());
}

void fm_transacao_vendedor::on_btnRelatorio_clicked()
{
	try
	{
		if(!ui->twVendedor->currentItem()) throw QString("Nenhum item selecionado.");

		QString data	= ui->twVendedor->item(ui->twVendedor->currentRow(), 1)->text();
		QString hora	= ui->twVendedor->item(ui->twVendedor->currentRow(), 2)->text();
		QString cliente = ui->twVendedor->item(ui->twVendedor->currentRow(), 3)->text();

		hora.replace(':', '-');

		QString nome = cliente+"_"+data+"_"+hora+".pdf";
		QString dir = QFileDialog::getExistingDirectory(this, "Selecionar diretorio", QDir::currentPath());

		QPrinter printer;
		printer.setOutputFormat(QPrinter::PdfFormat);
		printer.setOutputFileName(dir+"/"+nome);

		QPainter painter;
		if(!painter.begin(&printer))
		{
			throw QString("Erro ao abrir arquivo pdf.\n"+dir+"/"+nome);
		}

		int l = ui->twVendedor->currentRow();
		int linha=105, salto=20;

		for(int i=0; i<ui->twProdutos->rowCount(); ++i,  linha+=salto)
		{
			if(!(i%49))
			{
				if(i)	printer.newPage();
				painter.drawText(25, 25, "Relatório  ID: "+ui->twVendedor->item(l,0)->text());
				painter.drawText(125, 25, "Data: "+ui->twVendedor->item(l,1)->text());
				painter.drawText(225, 25, "Hora: "+ui->twVendedor->item(l,2)->text());
				painter.drawText(325, 25, "Vendedor: "+ui->twVendedor->item(l,3)->text());
				painter.drawText(525, 25, "Total: R$ "+ui->twVendedor->item(l,4)->text());
				painter.drawText(625, 25, "Tipo pgmt: "+ui->twVendedor->item(l,5)->text());

				painter.drawText(25, 65, "Cor Esmalte");
				painter.drawText(225, 65, "Quantidade");
				painter.drawText(325, 65, "Valor Unitário");
				painter.drawText(425, 65, "Valor Total");
				linha=105;
			}
			painter.drawText(25, linha, ui->twProdutos->item(i,0)->text());
			painter.drawText(225, linha, ui->twProdutos->item(i,1)->text());
			painter.drawText(325, linha, ui->twProdutos->item(i,2)->text());
			painter.drawText(425, linha, ui->twProdutos->item(i,3)->text());
		}
		painter.end();

		QMessageBox messageBox(QMessageBox::Question, tr("Informação"), tr("Arquivo PDF criado com sucesso.\nDeseja abrir o relatorio?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		QDesktopServices::openUrl(dir+"/"+nome);
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::information(this, "Erro", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (47)", "Erro crítico.");}
}

void fm_transacao_vendedor::on_rbEsmalte_clicked()
{
	on_lineVendedor_textEdited(ui->lineVendedor->text());
}

void fm_transacao_vendedor::on_rbRoupa_clicked()
{
	on_lineVendedor_textEdited(ui->lineVendedor->text());
}
