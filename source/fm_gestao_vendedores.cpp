#include "fm_gestao_vendedores.h"
#include "ui_fm_gestao_vendedores.h"

fm_gestao_vendedores::fm_gestao_vendedores(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_gestao_vendedores)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		// ========= Novo vendedor
		// ========= ========= ========= =========
		ui->lineNovoTel->setValidator(new QRegExpValidator(QRegExp("^[0-9]{11}$")));

		// ========= Gestao vendedor
		// ========= ========= ========= =========
		ui->lineGestaoTel->setValidator(new QRegExpValidator(QRegExp("^[0-9]{11}$")));

		// Carregando estrutura de dados e tabela da janela.
		carregarTWGestao(gl_ed::vendedor.getEdVendedor());
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_gestao_vendedores::~fm_gestao_vendedores()
{
	delete ui;
}

void fm_gestao_vendedores::carregarTWGestao(std::set<obj_vendedor>const *ed)
{
	std::set<obj_vendedor>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		ui->twGestao->insertRow(i);
		ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(it->getNome())));
		ui->twGestao->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->getTel().formatoTel())));
	}
}

// ========= Novo vendedor
// ========= ========= ========= =========
void fm_gestao_vendedores::on_lineNovoUser_textEdited(const QString &arg1)
{
	try
	{
		if(gl_ed::vendedor.existeVendedor(obj_vendedor(arg1.toStdString())))
		{
			ui->lbNovoUser->setText("User (Já existe)");
			ui->lbNovoUser->setStyleSheet("QLabel{ "
										  "background:#e8e8e8;"
										  "color:red;"
										  "font-size:10pt;"
										  "border:none;"
										  "border-radius:6px;}");

			ui->lineNovoUser->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:red;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");
		}
		else
		{
			ui->lbNovoUser->setText("User");
			ui->lbNovoUser->setStyleSheet("QLabel{ "
										  "background:#e8e8e8;"
										  "color:#808080;"
										  "font-size:10pt;"
										  "border:none;"
										  "border-radius:6px;}");

			ui->lineNovoUser->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:black;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");
		}
	}
	catch(std::string)	{}
	catch(...)			{QMessageBox::critical(this, "Erro (46)", "Erro desconhecido.");}
}

void fm_gestao_vendedores::on_btnNovoGravar_clicked()
{
	try
	{
		if(ui->lbNovoUser->text().size() != 4) throw QString("Usuário já existe.");

		QString nome  = ui->lineNovoNome->text();
		QString tel   = ui->lineNovoTel->text();
		QString user  = ui->lineNovoUser->text();
		QString senha = ui->lineNovoSenha->text();
		QChar acesso  = ui->cbNovoAcesso->currentText()[0];

		// Verifica se os dados são validos.
		obj_vendedor vendedor(nome.toStdString(), tel.toStdString(), user.toStdString(), senha.toStdString(), acesso.toLatin1());

		// Insere os dados no banco de dados e na estrutura de dados na memoria.
		gl_ed::vendedor.inserirNovo(vendedor);

		// Insere o novo dado no final da tabela da janela.
		ui->twGestao->setSortingEnabled(false);
		int linha = ui->twGestao->rowCount();
		ui->twGestao->insertRow(linha);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(vendedor.getNome())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(vendedor.getTel().formatoTel())));
		ui->twGestao->setSortingEnabled(true);

		// Limpa as linhas e prepara para inserir novo dado.
		ui->lineNovoNome->clear();
		ui->lineNovoTel->clear();
		ui->lineNovoUser->clear();
		ui->lineNovoSenha->clear();
		ui->cbNovoAcesso->setCurrentIndex(0);

		ui->lineNovoNome->setFocus();

		QMessageBox::information(this, "Informação", "Novo vendedor incluido com sucesso");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (67)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (67)", "Erro desconhecido.");}
	if(gl_variavel::db.eAberto()) gl_variavel::db.fechar();
}

void fm_gestao_vendedores::on_rbNovoSenha_clicked(bool checked)
{
	try
	{
		if(checked)	ui->lineNovoSenha->setEchoMode(QLineEdit::EchoMode::Normal);
		else		ui->lineNovoSenha->setEchoMode(QLineEdit::EchoMode::Password);
	}
	catch(...)
	{
		QMessageBox::critical(this, "Erro (78)", "Erro desconhecido.");
	}
}

// ========= Gestao vendedor
// ========= ========= ========= =========
void fm_gestao_vendedores::on_twGestao_itemSelectionChanged()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) return;

		int linha = ui->twGestao->currentRow();
		//if(ui->twGestao->item(linha, 0) == ui->twGestao->currentItem() || ui->twGestao->item(linha, 1) == ui->twGestao->currentItem()) return;

		obj_vendedor vendedor = gl_ed::vendedor.encontrarVendedor(ui->twGestao->item(linha,0)->text().toStdString(),
											   obj_telefone::formatoNum(ui->twGestao->item(linha,1)->text().toStdString()));

		ui->lineGestaoNome->setText(QString::fromStdString(vendedor.getNome()));
		ui->lineGestaoTel->setText(QString::fromStdString(vendedor.getTel().numero()));
		ui->lineGestaoUser->setText(QString::fromStdString(vendedor.getUser()));
		ui->lineGestaoSenha->setText(QString::fromStdString(vendedor.getSenha()));

		int aux=0;
		if(vendedor.getAcesso() == 'A')		aux=1;
		else if(vendedor.getAcesso() == 'B')aux=2;
		ui->cbGestaoAcesso->setCurrentIndex(aux);

		if(ui->twGestao->item(linha, 0)->text() == "Admin")
		{
			ui->lineGestaoNome->setReadOnly(true);
			ui->lineGestaoTel->setReadOnly(true);
			ui->cbGestaoAcesso->setEnabled(false);
			ui->lineGestaoNome->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:blue;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");
			ui->lineGestaoTel->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:blue;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");

		}
		else
		{
			ui->lineGestaoNome->setReadOnly(false);
			ui->lineGestaoTel->setReadOnly(false);
			ui->cbGestaoAcesso->setEnabled(true);
			ui->lineGestaoNome->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:black;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");
			ui->lineGestaoTel->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:black;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");
		}
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (125)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (125)", "Erro desconhecido.");}
}

void fm_gestao_vendedores::on_lineGestaoUser_textEdited(const QString &arg1)
{
	try
	{
		if(gl_ed::vendedor.existeVendedor(obj_vendedor(arg1.toStdString())))
		{
			ui->lbGestaoUser->setText("User (Já existe)");
			ui->lbGestaoUser->setStyleSheet("QLabel{ "
										  "background:#e8e8e8;"
										  "color:red;"
										  "font-size:10pt;"
										  "border:none;"
										  "border-radius:6px;}");

			ui->lineNovoUser->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:red;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");
		}
		else
		{
			ui->lbGestaoUser->setText("User");
			ui->lbGestaoUser->setStyleSheet("QLabel{ "
										  "background:#e8e8e8;"
										  "color:#808080;"
										  "font-size:10pt;"
										  "border:none;"
										  "border-radius:6px;}");

			ui->lineNovoUser->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
											"QLineEdit:disabled{background:#e7e7e7;}"
											"QLineEdit{"
											"color:black;"
											"font-size:9pt;"
											"border-radius:7px;"
											"border:1px solid black;}");
		}
	}
	catch(std::string)	{}
	catch(...)			{QMessageBox::critical(this, "Erro (169)", "Erro desconhecido.");}
}

void fm_gestao_vendedores::on_btnGestaoExcluir_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Excluir"), tr("Tem certeza que deseja excluir os dados do vendedor?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		int linha = ui->twGestao->currentRow();
		obj_vendedor vendedor = gl_ed::vendedor.encontrarVendedor(ui->twGestao->item(linha,0)->text().toStdString(),
											   obj_telefone::formatoNum(ui->twGestao->item(linha,1)->text().toStdString()));
		gl_ed::vendedor.remover(vendedor);

		ui->twGestao->removeRow(linha);

		ui->lineGestaoNome->setText("");
		ui->lineGestaoTel->setText("");
		ui->lineGestaoUser->setText("");
		ui->lineGestaoSenha->setText("");
		ui->cbGestaoAcesso->setCurrentIndex(0);

		QMessageBox::information(this, "Informação", "Vendedor excluido com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (190)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (190)", "Erro desconhecido.");}
}

void fm_gestao_vendedores::on_btnGestaoEditar_clicked()
{
	try
	{
		if(ui->lbGestaoUser->text().size() != 4) throw QString("Usuário já existe.");

		if(ui->twGestao->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Editar"), tr("Tem certeza que deseja editar os dados do vendedor?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		QString nome  = ui->lineGestaoNome->text();
		QString tel   = ui->lineGestaoTel->text();
		QString user  = ui->lineGestaoUser->text();
		QString senha = ui->lineGestaoSenha->text();
		QChar acesso  = ui->cbGestaoAcesso->currentText()[0];

		int linha = ui->twGestao->currentRow();
		obj_vendedor antigo = gl_ed::vendedor.encontrarVendedor(ui->twGestao->item(linha,0)->text().toStdString(),
											 obj_telefone::formatoNum(ui->twGestao->item(linha,1)->text().toStdString()));

		obj_vendedor novo(nome.toStdString(), tel.toStdString(), user.toStdString(), senha.toStdString(), acesso.toLatin1());
		novo.setId(antigo.getId());

		gl_ed::vendedor.editar(antigo, novo);

		ui->twGestao->setSortingEnabled(false);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(novo.getNome())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(novo.getTel().formatoTel())));
		ui->twGestao->setSortingEnabled(true);

		QMessageBox::information(this, "Informação", "Vendedor Editado com sucesso.");

		if(nome.toStdString() == gl_variavel::nomeVendedor)		gl_variavel::nomeVendedor=nome.toStdString();
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (221)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (221)", "Erro desconhecido.");}
}

void fm_gestao_vendedores::on_btnGestaoFiltro_clicked()
{
	try
	{
		ui->twGestao->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->twGestao);
		carregarTWGestao(gl_ed::vendedor.getEdVendedor());
		ui->twGestao->setSortingEnabled(true);

		ui->twGestao->setItemSelected(nullptr, -1);

		ui->lineGestaoNome->setText("");
		ui->lineGestaoTel->setText("");
		ui->lineGestaoUser->setText("");
		ui->lineGestaoSenha->setText("");
		ui->cbGestaoAcesso->setCurrentIndex(0);
		ui->lineGestaoFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (263)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (263)", "Erro desconhecido.");}
}

void fm_gestao_vendedores::on_lineGestaoFiltro_textEdited(const QString &arg1)
{
	std::vector<obj_vendedor> const * ed = nullptr;
	try
	{
		QString busca = "SELECT nome, tel "
						"FROM tb_pessoas, tb_vendedores "
						"WHERE id=id_pessoa AND nome like '%"+arg1+"%' OR id=id_pessoa AND tel like '%"+arg1+"%';";

		ed = gl_ed::vendedor.filtroEd(busca);

		gl_funcao::removerLinhas(ui->twGestao);
		ui->twGestao->setSortingEnabled(false);
		for(int i=0; i < int(ed->size()); ++i)
		{
			ui->twGestao->insertRow(i);
			ui->twGestao->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getNome())));
			ui->twGestao->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getTel().formatoTel())));
		}
		ui->twGestao->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (285)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (285)", "Erro desconhecido.");}
	if(ed) delete ed;
}

void fm_gestao_vendedores::on_radioButton_clicked(bool checked)
{
	try
	{
		if(checked)	ui->lineGestaoSenha->setEchoMode(QLineEdit::EchoMode::Normal);
		else		ui->lineGestaoSenha->setEchoMode(QLineEdit::EchoMode::Password);
	}
	catch(...)
	{
		QMessageBox::critical(this, "Erro (78)", "Erro desconhecido.");
	}
}
