#include "fm_gestao_roupa.h"
#include "ui_fm_gestao_roupa.h"

fm_gestao_roupa::fm_gestao_roupa(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_gestao_roupa)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		// ========= Nova roupa
		// ========= ========= ========= =========
		ui->lineNovoQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));
		ui->lineNovoValorUmC->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));
		ui->lineNovoValorUmV->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));

		// ========= Gestao roupa
		// ========= ========= ========= =========
		ui->lineGestaoQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));
		ui->lineGestaoValorUmC->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));
		ui->lineGestaoValorUmV->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));

		// =========
		ui->lineDesconto->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));
		ui->lbDescontoQtd->setText		("Porcentagem atual para realizar desconto: "+QString::number(gl_ed::roupa.getDesconto())+"%");

		// Carregando estrutura de dados e tabela da janela.
		carregarTWGestao(gl_ed::roupa.getEd());
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_gestao_roupa::~fm_gestao_roupa()
{
	delete ui;
}

void fm_gestao_roupa::carregarTWGestao(std::set<obj_roupa>const *ed)
{
	std::set<obj_roupa>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->twGestao->insertRow(i);
		ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getId())));
		ui->twGestao->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getRoupa())));
	}
}

void fm_gestao_roupa::on_btnNovoGravar_clicked()
{
	try
	{
		if(ui->lbNovoRoupa->text().size() != 5) throw QString("Roupa inválida.");
		if(ui->lbNovoCodBarras->text().size() != 16) throw QString("Cód. de barras inválido.");

		QString id			= ui->lineNovoCodBarras->text();
		QString roupa		= ui->lineNovoRoupa->text();
		QString qtd			= ui->lineNovoQtd->text();
		QString valorUmC	= ui->lineNovoValorUmC->text();
		QString valorUmV	= ui->lineNovoValorUmV->text();

		// Verifica se os dados são validos.
		obj_roupa obj(id.toStdString(), roupa.toStdString(), qtd.toInt(), valorUmV.toDouble(), valorUmC.toDouble());

		// Insere os dados no banco de dados e na estrutura de dados na memoria.
		gl_ed::roupa.inserirNovo(obj);

		// Insere o novo dado no final da tabela da janela.
		ui->twGestao->setSortingEnabled(false);
		int linha = ui->twGestao->rowCount();
		ui->twGestao->insertRow(linha);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(obj.getId())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(obj.getRoupa())));
		ui->twGestao->setSortingEnabled(true);

		// Limpa as linhas e prepara para inserir novo dado.
		ui->lineNovoCodBarras->clear();
		ui->lineNovoRoupa->clear();
		ui->lineNovoQtd->clear();
		ui->lineNovoValorUmC->clear();
		ui->lineNovoValorUmV->clear();

		ui->lineNovoCodBarras->setFocus();

		QMessageBox::information(this, "Informação", "Novo produto incluido com sucesso");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (53)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (53)", "Erro desconhecido.");}
	if(gl_variavel::db.eAberto()) gl_variavel::db.fechar();
}

void fm_gestao_roupa::on_lineNovoRoupa_textEdited(const QString &arg1)
{
	if(gl_ed::roupa.existeRoupa(arg1.toStdString()))
	{
		ui->lbNovoRoupa->setText("Roupa (Já existe)");
		ui->lbNovoRoupa->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoRoupa->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbNovoRoupa->setText("Roupa");
		ui->lbNovoRoupa->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoRoupa->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_roupa::on_lineNovoCodBarras_textEdited(const QString &arg1)
{
	if(gl_ed::roupa.existeId(arg1.toStdString()))
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

void fm_gestao_roupa::on_btnGestaoEditar_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Editar"), tr("Tem certeza que deseja editar os dados?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		QString qtd			= ui->lineGestaoQtd->text();
		QString cor			= ui->lineGestaoRoupa->text();
		QString id			= ui->lineGestaoCodBarras->text();
		QString valorUmC	= ui->lineGestaoValorUmC->text();
		QString valorUmV	= ui->lineGestaoValorUmV->text();

		obj_roupa antigo = gl_ed::roupa.encontrar(ui->twGestao->item(ui->twGestao->currentRow(), 0)->text().toStdString());
		obj_roupa novo(id.toStdString(), cor.toStdString(), qtd.toInt(), valorUmC.toDouble(), valorUmV.toDouble());

		gl_ed::roupa.editar(antigo, novo);

		int linha = ui->twGestao->currentRow();
		ui->twGestao->setSortingEnabled(false);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(novo.getId())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(novo.getRoupa())));
		ui->twGestao->setSortingEnabled(true);

		QMessageBox::information(this, "Informação", "Roupa editada com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (135)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (135)", "Erro desconhecido.");}
}

void fm_gestao_roupa::on_btnGestaoExcluir_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr || !ui->lbGestaoCodBarras->text().size()) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Excluir"), tr("Tem certeza que deseja excluir os dados?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		int linha = ui->twGestao->currentRow();
		obj_roupa obj = gl_ed::roupa.encontrar(ui->twGestao->item(linha,0)->text().toStdString());

		gl_ed::roupa.remover(obj);

		ui->twGestao->removeRow(linha);

		ui->lineGestaoCodBarras->setText("");
		ui->lineGestaoQtd->setText("");
		ui->lineGestaoRoupa->setText("");
		ui->lineGestaoValorUmC->setText("");
		ui->lineGestaoValorUmV->setText("");

		QMessageBox::information(this, "Informação", "Excluido com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (172)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (172)", "Erro desconhecido.");}
}

void fm_gestao_roupa::on_btnGestaoFiltro_clicked()
{
	try
	{
		ui->twGestao->setSortingEnabled(false);

		gl_funcao::removerLinhas(ui->twGestao);
		carregarTWGestao(gl_ed::roupa.getEd());

		ui->twGestao->setSortingEnabled(true);

		ui->twGestao->setItemSelected(nullptr, -1);
		ui->lineGestaoQtd->setText("");
		ui->lineGestaoRoupa->setText("");
		ui->lineGestaoCodBarras->setText("");
		ui->lineGestaoValorUmC->setText("");
		ui->lineGestaoValorUmV->setText("");
		ui->lineGestaoFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (204)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (204)", "Erro desconhecido.");}
}

void fm_gestao_roupa::on_lineGestaoFiltro_textEdited(const QString &arg1)
{
	std::vector<obj_roupa> const * ed = nullptr;

	try
	{
		QString busca = "SELECT id, roupa "
						"FROM tb_roupa "
						"WHERE id like '%"+arg1+"%' OR roupa like '%"+arg1+"%';";

		ed = gl_ed::roupa.filtroEd(busca);

		gl_funcao::removerLinhas(ui->twGestao);
		ui->twGestao->setSortingEnabled(false);

		for(int i=0; i < int(ed->size()); ++i)
		{
			ui->twGestao->insertRow(i);
			ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getId())));
			ui->twGestao->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getRoupa())));
		}
		ui->twGestao->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (228)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (228)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_gestao_roupa::on_twGestao_itemSelectionChanged()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) return;

		obj_roupa obj = gl_ed::roupa.encontrar(ui->twGestao->item(ui->twGestao->currentRow(),0)->text().toStdString());

		ui->lineGestaoCodBarras->setText(QString::fromStdString(obj.getId()));
		ui->lineGestaoQtd->setText(QString::number(obj.getQtd()));
		ui->lineGestaoRoupa->setText(QString::fromStdString(obj.getRoupa()));
		ui->lineGestaoValorUmC->setText(QString::number(obj.getVlrCompra(), 'f', 2));
		ui->lineGestaoValorUmV->setText(QString::number(obj.getVlrVenda(), 'f', 2));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (257)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (257)", "Erro desconhecido.");}
}

void fm_gestao_roupa::on_lineGestaoCodBarras_textEdited(const QString &arg1)
{
	if(ui->twGestao->currentItem() == nullptr) return;

	int linha = ui->twGestao->currentRow();
	if(gl_ed::roupa.existeId(arg1.toStdString()) && arg1 != ui->twGestao->item(linha, 0)->text())
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

void fm_gestao_roupa::on_lineGestaoRoupa_textEdited(const QString &arg1)
{
	if(ui->twGestao->currentItem() == nullptr) return;

	int linha = ui->twGestao->currentRow();
	if(gl_ed::roupa.existeRoupa(arg1.toStdString()) && arg1 != ui->twGestao->item(linha, 1)->text())
	{
		ui->lbGestaoRoupa->setText("Roupa (Já existe)");
		ui->lbGestaoRoupa->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoRoupa->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbGestaoRoupa->setText("Roupa");
		ui->lbGestaoRoupa->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoRoupa->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_roupa::on_btnDesconto_clicked()
{
	try
	{
		gl_ed::roupa.setDesconto(ui->lineDesconto->text().toDouble());
		ui->lbDescontoQtd->setText("Porcentagem atual para realizar desconto: "+QString::number(gl_ed::roupa.getDesconto())+"%");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (325)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (325)", "Erro desconhecido.");}
}

void fm_gestao_roupa::on_lineGestaoFiltro_returnPressed()
{
	on_lineGestaoFiltro_textEdited(ui->lineGestaoFiltro->text());
}
