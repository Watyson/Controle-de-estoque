#include "fm_gestao_clientes.h"
#include "ui_fm_gestao_clientes.h"

fm_gestao_clientes::fm_gestao_clientes(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_gestao_clientes)
{
	try
	{
		ui->setupUi(this);
		setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

		// ========= Novo cliente
		// ========= ========= ========= =========
		ui->lineNovoTel->setValidator(new QRegExpValidator(QRegExp("^[0-9]{11}$")));
		ui->lineNovoCep->setValidator(new QRegExpValidator(QRegExp("^[0-9]{8}$")));
		ui->lineNovoCnpj->setValidator(new QRegExpValidator(QRegExp("^[0-9]{14}$")));
		ui->lineNovoCpf->setValidator(new QRegExpValidator(QRegExp("^[0-9]{11}$")));

		// ========= Gestao cliente
		// ========= ========= ========= =========
		ui->lineGestaoTel->setValidator(new QRegExpValidator(QRegExp("^[0-9]{11}$")));
		ui->lineGestaoCep->setValidator(new QRegExpValidator(QRegExp("^[0-9]{8}$")));
		ui->lineGestaoCnpj->setValidator(new QRegExpValidator(QRegExp("^[0-9]{14}$")));
		ui->lineGestaoCpf->setValidator(new QRegExpValidator(QRegExp("^[0-9]{11}$")));

		// Carregando estrutura de dados e tabela da janela.
		carregarTWGestao(gl_ed::cliente.getEd());
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (4)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (4)", "Erro desconhecido.");}
}

fm_gestao_clientes::~fm_gestao_clientes()
{
	delete ui;
}

void fm_gestao_clientes::carregarTWGestao(std::set<obj_cliente>const *ed)
{
	std::set<obj_cliente>::iterator it=ed->begin();
	for(int i=0; it != ed->end(); ++i, ++it)
	{
		if(it->getNome() != "Desconhecido")
		{
			int linha = ui->twGestao->rowCount();
			ui->twGestao->insertRow(linha);
			ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(it->getNome())));
			ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(it->getTel().formatoTel())));
		}
	}
}

// ========= Novo cliente
// ========= ========= ========= =========
void fm_gestao_clientes::on_btnNovoGravar_clicked()
{
	try
	{
		if(!ui->lbNovoCnpj->text().size() && !ui->lbNovoCpf->text().size())
			throw QString("O cliente precisa de um cnpj ou cpf.");

		if(ui->lbNovoCnpj->text().size() != 21) throw QString("Já existe alguem com esse CNPJ.");
		if(ui->lbNovoCpf->text().size() != 20)	throw QString("Já existe alguem com esse CPF.");

		QString nome	= ui->lineNovoNome->text();
		QString tel		= ui->lineNovoTel->text();
		QString end		= ui->lineNovoEndereco->text();
		QString ref		= ui->lineNovoRef->text();
		QString cep		= ui->lineNovoCep->text();
		QString cnpj	= ui->lineNovoCnpj->text();
		QString cpf		= ui->lineNovoCpf->text();

		// Verifica se os dados são validos.
		obj_cliente cliente(nome.toStdString(), tel.toStdString(), end.toStdString(), ref.toStdString(), cep.toStdString(), cnpj.toStdString(), cpf.toStdString());

		// Insere os dados no banco de dados e na estrutura de dados na memoria.
		gl_ed::cliente.inserirNovo(cliente);

		// Insere o novo dado no final da tabela da janela.
		ui->twGestao->setSortingEnabled(false);
		int linha = ui->twGestao->rowCount();
		ui->twGestao->insertRow(linha);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(cliente.getNome())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(cliente.getTel().formatoTel())));
		ui->twGestao->setSortingEnabled(true);

		// Limpa as linhas e prepara para inserir novo dado.
		ui->lineNovoNome->clear();
		ui->lineNovoTel->clear();
		ui->lineNovoEndereco->clear();
		ui->lineNovoRef->clear();
		ui->lineNovoCep->clear();
		ui->lineNovoCnpj->clear();

		ui->lineNovoNome->setFocus();

		QMessageBox::information(this, "Informação", "Novo cliente incluido com sucesso");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (54)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (54)", "Erro desconhecido.");}
	if(gl_variavel::db.eAberto()) gl_variavel::db.fechar();
}

void fm_gestao_clientes::on_lineNovoCnpj_textEdited(const QString &arg1)
{
	if(gl_ed::cliente.existeCNPJ(arg1.toStdString()) && arg1.toStdString() != this->cnpj)
	{
		ui->lbNovoCnpj->setText("CNPJ (Apenas números) (Já existe)");
		ui->lbNovoCnpj->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCnpj->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbNovoCnpj->setText("CNPJ (Apenas números)");
		ui->lbNovoCnpj->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCnpj->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

void fm_gestao_clientes::on_lineNovoCpf_textEdited(const QString &arg1)
{
	if(gl_ed::cliente.existeCPF(arg1.toStdString()) && arg1.toStdString() != this->cpf)
	{
		ui->lbNovoCpf->setText("CPF (Apenas números) (Já existe)");
		ui->lbNovoCpf->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCpf->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbNovoCpf->setText("CPF (Apenas números)");
		ui->lbNovoCpf->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineNovoCpf->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}

// ========= Gestao cliente
// ========= ========= ========= =========
void fm_gestao_clientes::on_btnGestaoEditar_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) throw QString("Nenhum item selecionado.");

		if(!ui->lbNovoCnpj->text().size() && !ui->lbNovoCpf->text().size())
			throw QString("O cliente precisa de um cnpj ou cpf.");

		if(ui->lbGestaoCnpj->text().size() != 21) throw QString("Já existe alguem com esse CNPJ.");
		if(ui->lbGestaoCpf->text().size() != 20)	throw QString("Já existe alguem com esse CPF.");

		QMessageBox messageBox(QMessageBox::Question, tr("Editar"), tr("Tem certeza que deseja editar os dados do cliente?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		std::string nome	= ui->lineGestaoNome->text().toStdString();
		std::string tel		= ui->lineGestaoTel->text().toStdString();
		std::string end		= ui->lineGestaoEnd->text().toStdString();
		std::string ref		= ui->lineGestaoRef->text().toStdString();
		std::string cep		= ui->lineGestaoCep->text().toStdString();
		std::string cnpj	= ui->lineGestaoCnpj->text().toStdString();
		std::string cpf		= ui->lineGestaoCpf->text().toStdString();

		int linha = ui->twGestao->currentRow();
		obj_cliente antigo = gl_ed::cliente.encontrar(ui->twGestao->item(linha,0)->text().toStdString(),
								   obj_telefone::formatoNum(ui->twGestao->item(linha,1)->text().toStdString()));

		obj_cliente novo(nome, tel, end, ref, cep, cnpj, cpf);
		novo.setId(antigo.getId());

		gl_ed::cliente.editar(antigo, novo);

		ui->twGestao->setSortingEnabled(false);
		ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString(novo.getNome())));
		ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString(novo.getTel().formatoTel())));
		ui->twGestao->setSortingEnabled(true);

		QMessageBox::information(this, "Informação", "Cliente editado com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (117)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (117)", "Erro desconhecido.");}
}

void fm_gestao_clientes::on_btnGestaoExcluir_clicked()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr|| !ui->lbGestaoNome->text().size()) throw QString("Nenhum item selecionado.");

		QMessageBox messageBox(QMessageBox::Question, tr("Excluir"), tr("Tem certeza que deseja excluir os dados do cliente?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Sim"));
		messageBox.setButtonText(QMessageBox::No, tr("Não"));
		if(messageBox.exec() == QMessageBox::No) return;

		int linha = ui->twGestao->currentRow();
		obj_cliente cliente = gl_ed::cliente.encontrar(ui->twGestao->item(linha,0)->text().toStdString(),
							  obj_telefone::formatoNum(ui->twGestao->item(linha,1)->text().toStdString()));
		gl_ed::cliente.remover(cliente);

		ui->twGestao->removeRow(linha);

		QMessageBox::information(this, "Informação", "Cliente excluido com sucesso.");
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (157)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (157)", "Erro desconhecido.");}
}

void fm_gestao_clientes::on_btnGestaoFiltro_clicked()
{
	try
	{
		ui->twGestao->setSortingEnabled(false);
		gl_funcao::removerLinhas(ui->twGestao);
		carregarTWGestao(gl_ed::cliente.getEd());
		ui->twGestao->setSortingEnabled(true);

		ui->twGestao->setItemSelected(nullptr, -1);

		ui->lineGestaoNome->setText("");
		ui->lineGestaoTel->setText("");
		ui->lineGestaoEnd->setText("");
		ui->lineGestaoRef->setText("");
		ui->lineGestaoCep->setText("");
		ui->lineGestaoCnpj->setText("");
		ui->lineGestaoFiltro->setText("");
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (182)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (182)", "Erro desconhecido.");}
}

void fm_gestao_clientes::on_lineGestaoFiltro_textEdited(const QString &arg1)
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
			if((ed->begin()+i)->getNome() != "Desconhecido")
			{
				int linha = ui->twGestao->rowCount();
				ui->twGestao->insertRow(linha);
				ui->twGestao->setItem(linha, 0, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getNome())));
				ui->twGestao->setItem(linha, 1, new QTableWidgetItem(QString::fromStdString((ed->begin()+i)->getTel().formatoTel())));
			}
		}
		ui->twGestao->setSortingEnabled(true);
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (204)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (204)", "Erro desconhecido.");}

	if(ed)	delete ed;
}

void fm_gestao_clientes::on_twGestao_itemSelectionChanged()
{
	try
	{
		if(ui->twGestao->currentItem() == nullptr) return;

		int linha = ui->twGestao->currentRow();

		obj_cliente cliente = gl_ed::cliente.encontrar(ui->twGestao->item(linha,0)->text().toStdString(),
							  obj_telefone::formatoNum(ui->twGestao->item(linha,1)->text().toStdString()));

		ui->lineGestaoNome->setText(QString::fromStdString(cliente.getNome()));
		ui->lineGestaoTel->setText(QString::fromStdString(cliente.getTel().numero()));
		ui->lineGestaoEnd->setText(QString::fromStdString(cliente.getEnd()));
		ui->lineGestaoRef->setText(QString::fromStdString(cliente.getRef()));
		ui->lineGestaoCep->setText(QString::fromStdString(cliente.getCep().getCep()));
		ui->lineGestaoCnpj->setText(QString::fromStdString(cliente.getCnpj().getCnpj()));
		ui->lineGestaoCpf->setText(QString::fromStdString(cliente.getCpf()));

		this->cnpj	= cliente.getCnpj().getCnpj();
		this->cpf	= cliente.getCpf();
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (237)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (237)", "Erro desconhecido.");}
}

void fm_gestao_clientes::on_lineGestaoCnpj_textEdited(const QString &arg1)
{
	if(ui->twGestao->currentItem() == nullptr) return;

	if(gl_ed::cliente.existeCNPJ(arg1.toStdString()) && arg1.toStdString() != this->cnpj)
	{
		ui->lbGestaoCnpj->setText("CNPJ (Apenas números) (Já existe)");
		ui->lbGestaoCnpj->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCnpj->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbGestaoCnpj->setText("CNPJ (Apenas números)");
		ui->lbGestaoCnpj->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCnpj->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}



void fm_gestao_clientes::on_lineGestaoCpf_textEdited(const QString &arg1)
{
	if(ui->twGestao->currentItem() == nullptr) return;

	if(gl_ed::cliente.existeCPF(arg1.toStdString()) && arg1.toStdString() != this->cpf)
	{
		ui->lbGestaoCpf->setText("CPF (Apenas números) (Já existe)");
		ui->lbGestaoCpf->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:red;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCpf->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:red;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
	else
	{
		ui->lbGestaoCpf->setText("CPF (Apenas números)");
		ui->lbGestaoCpf->setStyleSheet("QLabel{ "
									  "background:#e8e8e8;"
									  "color:#808080;"
									  "font-size:10pt;"
									  "border:none;"
									  "border-radius:6px;}");

		ui->lineGestaoCpf->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
										"QLineEdit:disabled{background:#e7e7e7;}"
										"QLineEdit{"
										"color:black;"
										"font-size:9pt;"
										"border-radius:7px;"
										"border:1px solid black;}");
	}
}
