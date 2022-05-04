#include "fm_menu.h"
#include "ui_fm_menu.h"

bd gl_variavel::db;
bool gl_variavel::login = false;
int gl_variavel::idVendedor = -1;
std::string gl_variavel::nomeVendedor = "";
char gl_variavel::acessoVendedor = ' ';

bd_esmalte gl_ed::esmalte;
bd_cliente gl_ed::cliente;
bd_vendedor gl_ed::vendedor;
bd_venda gl_ed::venda;
bd_brinde gl_ed::brinde;
bd_relatorios gl_ed::relatorios;
bd_roupa gl_ed::roupa;

int gl_variavel::idCliente = -1;
std::string gl_variavel::nomeCliente = "";
std::string gl_variavel::tipoPgmt = "";

bool gl_variavel::editou = false;
int gl_variavel::qtd = 0;
int gl_variavel::estoque = 0;
std::string gl_variavel::id = "";
bool gl_variavel::finalizou = false;
double gl_variavel::valor = 0;

fm_menu::fm_menu(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::fm_menu)
{
	ui->setupUi(this);
	// === Icones
	QString dir = qApp->applicationDirPath();
	cadFechado.addFile(dir+"/dados/imagens/cadeado_fechado.png");
	cadAberto.addFile(dir+"/dados/imagens/cadeado_aberto.png");

	ui->btn_login->setIcon(cadFechado);
	ui->btn_login->setText("");
	ui->statusbar->addWidget(ui->btn_login);

	ui->lb_logado->setText("");
	ui->statusbar->addWidget(ui->lb_logado);

	acesso();

	try
	{
		gl_variavel::db.inicializar();
		gl_ed::esmalte.carregarEd();
		gl_ed::cliente.carregarEd();
		gl_ed::vendedor.carregarEd();
		gl_ed::brinde.carregarEd();
		gl_ed::relatorios.carregarEd();
		gl_ed::roupa.carregarEd();
	}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (21)", "Problemas ao incializar dados "+QString::fromStdString(e));}
	catch(...)			{QMessageBox::critical(this, "Erro(21)", "Erro critico.");}
}

fm_menu::~fm_menu()
{
	delete ui;
}

void fm_menu::acesso()
{
	if(gl_variavel::acessoVendedor == 'A')
	{
		ui->actionEsmalte->setEnabled(true);
		ui->actionGestao->setEnabled(true);
		ui->actionGestao_2->setEnabled(true);
		ui->actionTransaoes->setEnabled(true);
		ui->actionTransaoes_2->setEnabled(true);
		ui->actionBrinde->setEnabled(true);
		ui->btn_novaVenda->setEnabled(true);
		ui->btn_comodato->setEnabled(true);
		ui->btn_estoque->setEnabled(true);
		ui->actionRoupa->setEnabled(true);
		ui->actionDados->setEnabled(true);
	}
	else if(gl_variavel::acessoVendedor == 'B')
	{
		ui->actionEsmalte->setEnabled(false);
		ui->actionGestao->setEnabled(false);
		ui->actionGestao_2->setEnabled(false);
		ui->actionTransaoes->setEnabled(false);
		ui->actionTransaoes_2->setEnabled(false);
		ui->actionBrinde->setEnabled(false);
		ui->btn_novaVenda->setEnabled(true);
		ui->btn_comodato->setEnabled(true);
		ui->btn_estoque->setEnabled(false);
		ui->actionRoupa->setEnabled(false);
		ui->actionDados->setEnabled(false);
	}
	else
	{
		ui->actionEsmalte->setEnabled(false);
		ui->actionGestao->setEnabled(false);
		ui->actionGestao_2->setEnabled(false);
		ui->actionTransaoes->setEnabled(false);
		ui->actionTransaoes_2->setEnabled(false);
		ui->actionBrinde->setEnabled(false);
		ui->btn_novaVenda->setEnabled(false);
		ui->btn_comodato->setEnabled(false);
		ui->btn_estoque->setEnabled(false);
		ui->actionRoupa->setEnabled(false);
		ui->actionDados->setEnabled(false);
	}
}

void fm_menu::on_actionGestao_triggered()
{
	try
	{
		if(gl_variavel::acessoVendedor != 'A') throw QString("Acesso negado.");

		close();
		fm_gestao_vendedores a;
		a.exec();
		show();

		ui->lb_logado->setText(QString::fromStdString(gl_variavel::nomeVendedor));
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (88)", "Erro desconhecido.");}
}

void fm_menu::on_actionGestao_2_triggered()
{
	try
	{
		if(gl_variavel::acessoVendedor != 'A') throw QString("Acesso negado.");

		close();
		fm_gestao_clientes a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (105)", "Erro desconhecido.");}
}

void fm_menu::on_actionEsmalte_triggered()
{
	try
	{
		if(gl_variavel::acessoVendedor != 'A') throw QString("Acesso negado.");

		close();
		fm_gestao_esmalte a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (120)", "Erro desconhecido.");}
}

void fm_menu::on_btn_login_clicked()
{
	try
	{
		if(!gl_variavel::login)
		{
			fm_login a;
			a.exec();

			if(gl_variavel::login)
			{
				ui->lb_logado->setText(QString::fromStdString(gl_variavel::nomeVendedor));
				ui->btn_login->setIcon(cadAberto);
			}
		}
		else
		{
			gl_variavel::idVendedor = -1;
			gl_variavel::acessoVendedor = ' ';
			gl_variavel::login=false;
			ui->lb_logado->setText("");
			ui->btn_login->setIcon(cadFechado);
		}
		acesso();
	}
	catch(...)
	{
		QMessageBox::warning(this, "Erro (135)", "Erro desconhecido.");
	}
}

void fm_menu::on_btn_novaVenda_clicked()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		QMessageBox messageBox(QMessageBox::Question, tr("Nova Venda"), tr("O que deseja ver?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Roupas"));
		messageBox.setButtonText(QMessageBox::No, tr("Esmalte"));

		close();
		if(messageBox.exec() == QMessageBox::Yes){
			fm_roupaNovaVenda a;
			a.exec();
		}
		else{
			fm_novaVenda a;
			a.exec();
		}
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (166)", "Erro desconhecido.");}
}

void fm_menu::on_actionSobre_triggered()
{
	QMessageBox::about(this, "Sobre", "Programa para gestão de vendas V 1.0\n\nCriado por João e Watyson.");
}

void fm_menu::on_btn_comodato_clicked()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		close();
		fm_relatorio_comodato a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (186)", "Erro desconhecido.");}
}

void fm_menu::on_btn_estoque_clicked()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		QMessageBox messageBox(QMessageBox::Question, tr("Estoque"), tr("O que deseja ver?"), QMessageBox::Yes | QMessageBox::No, this);
		messageBox.setButtonText(QMessageBox::Yes, tr("Roupas"));
		messageBox.setButtonText(QMessageBox::No, tr("Esmalte"));

		close();
		if(messageBox.exec() == QMessageBox::Yes){
			fm_estoque_roupa a;
			a.exec();
		}
		else{
			fm_estoque_esmalte a;
			a.exec();
		}
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (166)", "Erro desconhecido.");}
}

void fm_menu::on_actionBrinde_triggered()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		close();
		fm_gestao_brinde a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (186)", "Erro desconhecido.");}
}

void fm_menu::on_actionSair_triggered()
{
	close();
}

void fm_menu::on_actionTransaoes_triggered()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		close();
		fm_transacao_vendedor a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (186)", "Erro desconhecido.");}
}

void fm_menu::on_actionTransaoes_2_triggered()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		close();
		fm_transacao_cliente a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (186)", "Erro desconhecido.");}
}

void fm_menu::on_actionRoupa_triggered()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		close();
		fm_gestao_roupa a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (186)", "Erro desconhecido.");}
}

void fm_menu::on_actionDados_triggered()
{
	try
	{
		if(!gl_variavel::login) throw QString("Faça login.");

		close();
		fm_dados a;
		a.exec();
		show();
	}
	catch(QString &e)	{QMessageBox::information(this, "Informação", e);}
	catch(...)			{QMessageBox::warning(this, "Erro (186)", "Erro desconhecido.");}
}
