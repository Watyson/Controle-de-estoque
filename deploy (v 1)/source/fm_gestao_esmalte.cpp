#include "fm_gestao_esmalte.h"
#include "ui_fm_gestao_esmalte.h"

fm_gestao_esmalte::fm_gestao_esmalte(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_gestao_esmalte)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		// ========= Novo esmalte
		// ========= ========= ========= =========
		ui->lineNovoQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));
		ui->lineNovoValorUmC->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));
		ui->lineNovoValorUmV->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));
		ui->lineNovoValorDesc->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));

		// ========= Gestao esmalte
		// ========= ========= ========= =========
		ui->lineGestaoQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));
		ui->lineGestaoValorUmC->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));
		ui->lineGestaoValorUmV->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));
		ui->lineGestaoValorDesc->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));

		// =========
		ui->lbDescontoQtd->setText("Quantidade atual para realizar desconto: "+QString::number(gl_ed::esmalte.getQtdDesconto()));

		// Carregando estrutura de dados e tabela da janela.
		carregarTWGestao(gl_ed::esmalte.getEd());
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_gestao_esmalte::~fm_gestao_esmalte()
{
	delete ui;
}

void fm_gestao_esmalte::carregarTWGestao(std::set<obj_esmalte>const *ed)
{
	std::set<obj_esmalte>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->twGestao->insertRow(i);
		ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getId())));
		ui->twGestao->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getCor())));
	}
}

void fm_gestao_esmalte::on_btnNovoGravar_clicked()
{
	try
	{
		if(ui->lbNovoCor->text().size() != 3) throw QString("Cor inválida.");
		if(ui->lbNovoCodBarras->text().size() != 16) throw QString("Cód. de barras inválido.");

		QString id			= ui->lineNovoCodBarras->text();
		QString cor			= ui->lineNovoCor->text();
		QString qtd			= ui->lineNovoQtd->text();
		QString valorUmC	= ui->lineNovoValorUmC->text();
		QString valorUmV	= ui->lineNovoValorUmV->text();
		QString valorDesc	= ui->lineNovoValorDesc->text();

		// Verifica se os dados são validos.
		obj_esmalte esmalte(id.toStdString(), cor.toStdString(), qtd.toInt(), valorUmV.toDouble(),
							valorUmC.toDouble(), valorDesc.toDouble());

		// Insere os dados no banco de dados e na estrutura de dados na memoria.
		gl_ed::esmalte.inserirNovo(esmalte);

		// Insere o novo dado no final da tabela da janela.
		ui->twGestao->setSortingEnabled(false);

		int linha = ui->twGestao->rowCount();
		ui->twGestao->insertRow(linha);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(esmalte.getId())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(esmalte.getCor())));

		ui->twGestao->setSortingEnabled(true);

		// Limpa as linhas e prepara para inserir novo dado.
		ui->lineNovoCodBarras->clear();
		ui->lineNovoCor->clear();
		ui->lineNovoQtd->clear();
		ui->lineNovoValorUmC->clear();
		ui->lineNovoValorUmV->clear();
		ui->lineNovoValorDesc->clear();

		ui->lineNovoCodBarras->setFocus();

		QMessageBox::information(this, "Informação", "Novo produto incluido com sucesso");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (53)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (53)", "Erro desconhecido.");}
	if(gl_variavel::db.eAberto()) gl_variavel::db.fechar();
}

void fm_gestao_esmalte::on_lineNovoCor_textEdited(const QString &arg1)
{
	if(gl_ed::esmalte.existeCor(arg1.toStdString()))
	{
		ui->lbNovoCor->setText("Cor (Já existe)");
		ui->lbNovoCor->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCor->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbNovoCor->setText("Cor");
		ui->lbNovoCor->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCor->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_esmalte::on_lineNovoCodBarras_textEdited(const QString &arg1)
{
	if(gl_ed::esmalte.existeId(arg1.toStdString()))
	{
		ui->lbNovoCodBarras->setText("Código de barras (Já existe)");
		ui->lbNovoCodBarras->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCodBarras->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbNovoCodBarras->setText("Código de barras");
		ui->lbNovoCodBarras->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCodBarras->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

// =========================== Gestão ===========================
void fm_gestao_esmalte::on_btnGestaoEditar_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Editar"), tr("Tem certeza que deseja editar os dados?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		QString qtd			= ui->lineGestaoQtd->text();
		QString cor			= ui->lineGestaoCor->text();
		QString id			= ui->lineGestaoCodBarras->text();
		QString valorUmC	= ui->lineGestaoValorUmC->text();
		QString valorUmV	= ui->lineGestaoValorUmV->text();
		QString valorDesc	= ui->lineGestaoValorDesc->text();

		obj_esmalte antigo = gl_ed::esmalte.encontrar(ui->twGestao->item(ui->twGestao->currentRow(), 0)->text().toStdString());
		obj_esmalte novo(id.toStdString(), cor.toStdString(), qtd.toInt(), valorUmV.toDouble(),
							valorUmC.toDouble(), valorDesc.toDouble());

		gl_ed::esmalte.editar(antigo, novo);

		int linha = ui->twGestao->currentRow();
		ui->twGestao->setSortingEnabled(false);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(novo.getId())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(novo.getCor())));
		ui->twGestao->setSortingEnabled(true);

		QMessageBox::information(this, "Informação", "Esmalte editado com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (135)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (135)", "Erro desconhecido.");}
}

void fm_gestao_esmalte::on_btnGestaoExcluir_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Excluir"), tr("Tem certeza que deseja excluir os dados do esmalte?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		int linha = ui->twGestao->currentRow();
		obj_esmalte esmalte = gl_ed::esmalte.encontrar(ui->twGestao->item(linha,0)->text().toStdString());

		gl_ed::esmalte.remover(esmalte);

		ui->twGestao->removeRow(linha);

		ui->lineGestaoCodBarras->setText("");
		ui->lineGestaoQtd->setText("");
		ui->lineGestaoCor->setText("");
		ui->lineGestaoValorUmC->setText("");
		ui->lineGestaoValorUmV->setText("");
		ui->lineGestaoValorDesc->setText("");

		QMessageBox::information(this, "Informação", "Esmalte excluido com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (172)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (172)", "Erro desconhecido.");}
}

void fm_gestao_esmalte::on_btnGestaoFiltro_clicked()
{
	try
	{
		ui->twGestao->setSortingEnabled(false);

		gl_funcao::removerLinhas(ui->twGestao);
		carregarTWGestao(gl_ed::esmalte.getEd());

		ui->twGestao->setSortingEnabled(true);

		ui->twGestao->setItemSelected(nullptr, -1);
		ui->lineGestaoQtd->setText("");
		ui->lineGestaoCor->setText("");
		ui->lineGestaoCodBarras->setText("");
		ui->lineGestaoValorUmC->setText("");
		ui->lineGestaoValorUmV->setText("");
		ui->lineGestaoValorDesc->setText("");
		ui->lineGestaoFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (204)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (204)", "Erro desconhecido.");}
}

void fm_gestao_esmalte::on_lineGestaoFiltro_textEdited(const QString &arg1)
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
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (228)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (228)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_gestao_esmalte::on_twGestao_itemSelectionChanged()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr|| !ui->lbGestaoCodBarras->text().size()) return;

		int linha = ui->twGestao->currentRow();

		obj_esmalte esmalte = gl_ed::esmalte.encontrar(ui->twGestao->item(linha,0)->text().toStdString());

		ui->lineGestaoCodBarras->setText(QString::fromStdString(esmalte.getId()));
		ui->lineGestaoQtd->setText(QString::number(esmalte.getQtd()));
		ui->lineGestaoCor->setText(QString::fromStdString(esmalte.getCor()));
		ui->lineGestaoValorUmC->setText(QString::number(esmalte.getValorUmCompra(), 'f', 2));
		ui->lineGestaoValorUmV->setText(QString::number(esmalte.getValorUm(), 'f', 2));
		ui->lineGestaoValorDesc->setText(QString::number(esmalte.getValorUmDesconto()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (257)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (257)", "Erro desconhecido.");}
}

void fm_gestao_esmalte::on_lineGestaoCodBarras_textEdited(const QString &arg1)
{
	if(ui->twGestao->currentItem() == nullptr) return;

	int linha = ui->twGestao->currentRow();
	if(gl_ed::esmalte.existeId(arg1.toStdString()) && arg1 != ui->twGestao->item(linha, 0)->text())
	{
		ui->lbGestaoCodBarras->setText("Código de barras (Já existe)");
		ui->lbGestaoCodBarras->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCodBarras->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbGestaoCodBarras->setText("Código de barras");
		ui->lbGestaoCodBarras->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCodBarras->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_esmalte::on_lineGestaoCor_textEdited(const QString &arg1)
{
	if(ui->twGestao->currentItem() == nullptr) return;

	int linha = ui->twGestao->currentRow();
	if(gl_ed::esmalte.existeCor(arg1.toStdString()) && arg1 != ui->twGestao->item(linha, 1)->text())
	{
		ui->lbGestaoCor->setText("Cor (Já existe)");
		ui->lbGestaoCor->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCor->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbGestaoCor->setText("Cor");
		ui->lbGestaoCor->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCor->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_esmalte::on_btnDesconto_clicked()
{
	try
	{
		gl_ed::esmalte.setQtdDesconto(ui->lineDesconto->text().toInt());
		ui->lbDescontoQtd->setText("Quantidade atual para realizar desconto: "+QString::number(gl_ed::esmalte.getQtdDesconto()));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (325)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (325)", "Erro desconhecido.");}
}

void fm_gestao_esmalte::on_lineGestaoFiltro_returnPressed()
{
	on_lineGestaoFiltro_textEdited(ui->lineGestaoFiltro->text());
}
