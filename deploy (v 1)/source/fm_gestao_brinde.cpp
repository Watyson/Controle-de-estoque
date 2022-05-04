#include "fm_gestao_brinde.h"
#include "ui_fm_gestao_brinde.h"

fm_gestao_brinde::fm_gestao_brinde(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_gestao_brinde)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		// ========= Novo Brinde
		// ========= ========= ========= =========
		ui->lineNovoQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));
		ui->lineNovoValorCusto->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));

		// ========= Gestao Brinde
		// ========= ========= ========= =========
		ui->lineGestaoQtd->setValidator(new QRegExpValidator(QRegExp("^[0-9]{6}$")));
		ui->lineNovoValorCusto->setValidator	(new QRegExpValidator(QRegExp("^[0-9]{1,4}[.]{1}[0-9]{2}$")));

		// Carregando estrutura de dados e tabela da janela.
		carregarTWGestao(gl_ed::brinde.getEd());
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_gestao_brinde::~fm_gestao_brinde()
{
	delete ui;
}

void fm_gestao_brinde::carregarTWGestao(std::set<obj_brinde>const *ed)
{
	std::set<obj_brinde>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->twGestao->insertRow(i);
		ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getNome())));
	}
}

void fm_gestao_brinde::on_lineNovoNome_textEdited(const QString &arg1)
{
	if(gl_ed::brinde.existeBrinde(obj_brinde(arg1.toStdString())))
	{
		ui->lbNovoNome->setText("Nome (Já existe)");
		ui->lbNovoNome->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoNome->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbNovoNome->setText("Nome");
		ui->lbNovoNome->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoNome->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_brinde::on_btnNovoGravar_clicked()
{
	try
	{
		if(ui->lbNovoNome->text().size() != 4) throw QString("Nome inválido.");

		QString nome	= ui->lineNovoNome->text();
		QString qtd		= ui->lineNovoQtd->text();
		QString valor	= ui->lineNovoValorCusto->text();

		// Verifica se os dados são validos.
		obj_brinde brinde(nome.toStdString(), qtd.toInt(), valor.toDouble());

		// Insere os dados no banco de dados e na estrutura de dados na memoria.
		gl_ed::brinde.inserirNovo(brinde);

		// Insere o novo dado no final da tabela da janela.
		ui->twGestao->setSortingEnabled(false);
		int linha = ui->twGestao->rowCount();
		ui->twGestao->insertRow(linha);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(brinde.getNome())));
		ui->twGestao->setSortingEnabled(true);

		// Limpa as linhas e prepara para inserir novo dado.
		ui->lineNovoNome->clear();
		ui->lineNovoQtd->clear();
		ui->lineNovoValorCusto->clear();

		ui->lineNovoNome->setFocus();

		QMessageBox::information(this, "Informação", "Novo produto incluido com sucesso");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (53)", QString::fromStdString(e));}
	//catch(...)				{QMessageBox::critical(this, "Erro (53)", "Erro desconhecido.");}
	if(gl_variavel::db.eAberto()) gl_variavel::db.fechar();
}

// =========================== Gestão ===========================
void fm_gestao_brinde::on_lineGestaoFiltro_textEdited(const QString &arg1)
{
	std::vector<obj_brinde> const * ed = nullptr;

	try
	{
		QString busca = "SELECT nome "
						"FROM tb_brinde "
						"WHERE nome like '%"+arg1+"%';";

		ed = gl_ed::brinde.filtroEd(busca);

		gl_funcao::removerLinhas(ui->twGestao);

		ui->twGestao->setSortingEnabled(false);
		for(int i=0; i < int(ed->size()); ++i)
		{
			ui->twGestao->insertRow(i);
			ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getNome())));
		}
		ui->twGestao->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (228)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (228)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_gestao_brinde::on_btnGestaoFiltro_clicked()
{
	try
	{
		ui->twGestao->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->twGestao);
		carregarTWGestao(gl_ed::brinde.getEd());
		ui->twGestao->setSortingEnabled(true);

		ui->twGestao->setItemSelected(nullptr, -1);
		ui->lineGestaoQtd->setText("");
		ui->lineGestaoNome->setText("");
		ui->lineGestaoValorCusto->setText("");
		ui->lineGestaoFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (204)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (204)", "Erro desconhecido.");}
}

void fm_gestao_brinde::on_twGestao_itemSelectionChanged()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) return;

		int linha = ui->twGestao->currentRow();

		obj_brinde brinde = gl_ed::brinde.encontrar(ui->twGestao->item(linha,0)->text().toStdString());

		ui->lineGestaoNome->setText(QString::fromStdString(brinde.getNome()));
		ui->lineGestaoQtd->setText(QString::number(brinde.getQtd()));
		ui->lineGestaoValorCusto->setText(QString::number(brinde.getValor(), 'f', 2));
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (257)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (257)", "Erro desconhecido.");}
}

void fm_gestao_brinde::on_lineGestaoNome_textEdited(const QString &arg1)
{
	if(gl_ed::brinde.existeBrinde(obj_brinde(arg1.toStdString())))
	{
		ui->lbGestaoNome->setText("Nome (Já existe)");
		ui->lbNovoNome->setText("Nome");
		ui->lbNovoNome->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoNome->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbGestaoNome->setText("Nome");
		ui->lbNovoNome->setText("Nome");
		ui->lbNovoNome->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoNome->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_brinde::on_btnGestaoEditar_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Editar"), tr("Tem certeza que deseja editar os dados?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		QString nome	= ui->lineGestaoNome->text();
		QString qtd		= ui->lineGestaoQtd->text();
		QString valor	= ui->lineGestaoValorCusto->text();

		obj_brinde antigo = gl_ed::brinde.encontrar(ui->twGestao->item(ui->twGestao->currentRow(), 0)->text().toStdString());
		obj_brinde novo(nome.toStdString(), qtd.toInt(), valor.toDouble());

		gl_ed::brinde.editar(antigo, novo);

		if(antigo.getNome() != novo.getNome())
		{
			ui->twGestao->setSortingEnabled(false);
			ui->twGestao->setItem(ui->twGestao->currentRow(), 0, new QTableWidgetItem(QString::fromStdString(novo.getNome())));
			ui->twGestao->setSortingEnabled(true);
		}

		QMessageBox::information(this, "Informação", "Brinde Editado com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (135)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (135)", "Erro desconhecido.");}
}

void fm_gestao_brinde::on_btnGestaoExcluir_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr || !ui->lbGestaoNome->text().size()) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Excluir"), tr("Tem certeza que deseja excluir os dados?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		int linha = ui->twGestao->currentRow();
		obj_brinde brinde = gl_ed::brinde.encontrar(ui->twGestao->item(linha,0)->text().toStdString());

		gl_ed::brinde.remover(brinde);

		ui->twGestao->removeRow(linha);

		ui->lineGestaoNome->setText("");
		ui->lineGestaoQtd->setText("");
		ui->lineGestaoValorCusto->setText("");

		QMessageBox::information(this, "Informação", "Brinde excluido com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (172)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (172)", "Erro desconhecido.");}
}

void fm_gestao_brinde::on_btnGestaoVerVendas_clicked()
{

}
