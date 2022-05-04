#include "fm_roupanovavenda.h"
#include "ui_fm_roupanovavenda.h"

fm_roupaNovaVenda::fm_roupaNovaVenda(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_roupaNovaVenda)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		ui->line_qtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));

		ui->line_qtd->setText("1");
		ui->line_codProd->setFocus();
		ui->lb_acao->setText("");

		ui->tw->setColumnWidth(0, 300);
		ui->tw->setColumnWidth(1, 300);
		ui->tw->setColumnWidth(2, 100);
		ui->tw->setColumnWidth(3, 50);

		ui->line_codProd->setFocus();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (9)", "Erro desconhecido.");}
}

fm_roupaNovaVenda::~fm_roupaNovaVenda()	{delete ui;}

double fm_roupaNovaVenda::atualizaTw()
{
	double preco=0;
	for(int i=0; i < ui->tw->rowCount(); ++i)
	{
		preco += ui->tw->item(i, 4)->text().toDouble();
	}
	return preco;
}

void fm_roupaNovaVenda::on_line_codProd_returnPressed()
{
	try
	{
		QString id = ui->line_codProd->text();
		QString qtd = ui->line_qtd->text();

		obj_roupa obj = gl_ed::roupa.encontrar(id.toStdString());

		if(qtd.toInt() < 1)					{throw QString("Quantidade do produto inválida.");}
		if(obj.getQtd() < 1)			{throw QString("Produto sem estoque.");}
		if(obj.getQtd() < qtd.toInt())	{throw QString("Estoque insuficiente.\nEstoque atual: "+QString::number(obj.getQtd()));}
		int linha				= 0;
		double valorUm			= obj.getVlrVenda();

		std::map<std::string, std::pair<int, double>>::iterator it = vendas.find(id.toStdString());
		if(it == vendas.end())
		{
			// =========================== Atualiza e insere ===========================
			vendas			[id.toStdString()]	= std::pair<int, double> (qtd.toInt(), valorUm);

			// Tabela: |codigo|produto|valor um|qtd|valor total|
			linha = ui->tw->rowCount();
			ui->tw->insertRow(linha);
			ui->tw->setItem(linha,0,new QTableWidgetItem(id));
			ui->tw->setItem(linha,1,new QTableWidgetItem(QString::fromStdString(obj.getRoupa())));
			ui->tw->setItem(linha,3,new QTableWidgetItem(qtd));

			// =========================== Finaliza ===========================
			ui->lb_acao->setText("Incluido com sucesso. (linha "+QString::number(linha+1)+" )");
			ui->lb_acao->setStyleSheet("QLabel{ "
										"background:#e8e8e8;"
										"color:blue;"
										"font-size:10pt;"
										"border:none;"
										"border-radius:6px;}");
		}
		else
		{
			// =========================== Encontra a posicao ===========================
			int i=0;
			for( ;i < ui->tw->rowCount() && ui->tw->item(i, 0)->text() != id; ++i);
			if(i == ui->tw->rowCount()) throw QString("Erro ao inserir novo produto.");
			linha = i;

			if(vendas[id.toStdString()].first + qtd.toInt() > obj.getQtd()) {throw QString("Estoque insuficiente.\nEstoque atual: "+
																					QString::number(obj.getQtd()));}

			// =========================== Atualiza ===========================
			vendas			[id.toStdString()]	= std::pair<int, double> (vendas			[id.toStdString()].first + qtd.toInt(), valorUm);

			// Tabela: |codigo|produto|valor um|qtd|valor total|
			ui->tw->item(linha, 3)->setText(QString::number(qtd.toInt() + ui->tw->item(linha, 3)->text().toInt()));

			ui->lb_acao->setText("Atualizado com sucesso. (linha "+QString::number(linha+1)+" )");
			ui->lb_acao->setStyleSheet("QLabel{ "
										"background:#e8e8e8;"
										"color:green;"
										"font-size:10pt;"
										"border:none;"
										"border-radius:6px;}");
		}

		ui->tw->setItem(linha, 2, new QTableWidgetItem(QString::number(valorUm, 'f', 2)));
		ui->tw->setItem(linha, 4, new QTableWidgetItem(QString::number(vendas [id.toStdString()].first * valorUm, 'f', 2)));
		ui->lb_valorTotal->setText(QString::number(atualizaTw(), 'f', 2));

		ui->line_qtd->setText("1");
		ui->line_codProd->clear();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::information(this, "Erro (68)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (68)", "Erro crítico.");}
}

void fm_roupaNovaVenda::on_btn_pesquisar_clicked()
{
	try
	{
		fm_roupaNovaVenda_pesquisar a;
		a.exec();

		if(!gl_variavel::editou) return;

		// Houve edicao
		// Tabela: |codigo|produto|valor um|qtd|valor total|
		gl_variavel::editou = false;

		ui->line_codProd->setText(QString::fromStdString(gl_variavel::id));
		ui->line_codProd->setFocus();

		gl_variavel::id = "";
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::information(this, "Erro (155)", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (155)", "Erro crítico.");}
}

void fm_roupaNovaVenda::on_btn_excluir_clicked()
{
	try
	{
		if(ui->tw->currentItem() == nullptr) throw std::string("Nenhum produto selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Excluir"), tr("Tem certeza que deseja excluir o produto da lista?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		int linha = ui->tw->currentRow();
		std::string id = ui->tw->item(linha, 0)->text().toStdString();

		// =========================== Apaga na ED ===========================
		std::map<std::string, std::pair<int, double>>::iterator it = vendas.find(ui->tw->item(linha, 0)->text().toStdString());
		if(it == vendas.end()) throw("Erro ao deletar dado.");
		vendas.erase(it);

		ui->tw->removeRow(linha);

		ui->lb_valorTotal->setText(QString::number(atualizaTw(), 'f', 2));
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (178)", "Erro crítico.");}
}

void fm_roupaNovaVenda::on_btn_editar_clicked()
{
	try
	{
		if(ui->tw->currentItem() == nullptr)	throw std::string("Nenhum produto selecionado.");

		int linha = ui->tw->currentRow();

		gl_variavel::qtd		= ui->tw->item(linha, 3)->text().toInt();
		gl_variavel::estoque	= gl_ed::roupa.encontrar(ui->tw->item(linha, 0)->text().toStdString()).getQtd();

		fm_roupaNovaVenda_editar a;
		a.exec();

		if(!gl_variavel::editou) return;
		gl_variavel::editou = false;

		// Houve edicao
		// Tabela: |codigo|produto|valor um|qtd|valor total|
		std::string id = ui->tw->item(ui->tw->currentRow(), 0)->text().toStdString();

		vendas			[id] = std::pair<int, double> (gl_variavel::qtd, vendas			[id].second);

		ui->tw->item(linha, 3)->setText(QString::number(gl_variavel::qtd));

		ui->tw->setItem(linha,2,new QTableWidgetItem(QString::number(vendas[id].second, 'f', 2)));
		ui->tw->setItem(linha,4,new QTableWidgetItem(QString::number(vendas[id].first * vendas[id].second, 'f', 2)));

		ui->lb_valorTotal->setText(QString::number(atualizaTw(), 'f', 2));
		ui->lb_acao->setText("Atualizado com sucesso. (linha "+QString::number(linha+1)+" )");
		ui->lb_acao->setStyleSheet("QLabel{ "
									"background:#e8e8e8;"
									"color:green;"
									"font-size:10pt;"
									"border:none;"
									"border-radius:6px;}");
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::information(this, "Erro (219)", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (219)", "Erro crítico.");}
}

void fm_roupaNovaVenda::on_btn_concluir_clicked()
{
	try
	{
		if(!ui->tw->rowCount()) throw QString("Sem produtos para concluir uma venda.");

		QMessageBox messageBox(QMessageBox::Question, tr("Concluir"), tr("Tem certeza que deseja finalizar a venda?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		gl_variavel::valor = atualizaTw();

		fm_roupaNovaVenda_finalizar a;
		a.exec();

		if(!gl_variavel::finalizou)
		{
			QMessageBox messageBox(QMessageBox::Question, tr("Informação"), tr("A venda NÃO foi finalizada.\nDeseja excluir os dados e iniciar uma nova venda?"), QMessageBox::Yes | QMessageBox::No, this);
			messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
			messageBox.setButtonText(QMessageBox::No, tr("Não"));
			if(messageBox.exec() == QMessageBox::Yes)
			{
				ui->line_codProd->setFocus();
				ui->line_qtd->setText("1");
				ui->lb_acao->setText("");
				ui->lb_valorTotal->setText("0.00");
				gl_funcao::removerLinhas(ui->tw);
				vendas.clear();
			}
			return;
		}
		gl_variavel::finalizou = false;

		gl_ed::roupa.concluirVenda(vendas);


		vendas.clear();

		gl_funcao::removerLinhas(ui->tw);
		ui->lb_valorTotal->setText("0.00");
		ui->lb_acao->setText("");

		if(gl_variavel::tipoPgmt == "À vista")	QMessageBox::information(this, "Venda concluida", "Venda concluída com sucesso\nValor total com desconto: .");
		else									QMessageBox::information(this, "Venda concluida", "Venda concluída com sucesso.");
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::information(this, "Erro (276)", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (276)", "Erro crítico.");}
}
