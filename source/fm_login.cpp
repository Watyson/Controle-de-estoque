#include "fm_login.h"
#include "ui_fm_login.h"

fm_login::fm_login(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_login)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui->line_user->setFocus();

	QSqlQuery query;
	gl_variavel::db.abrir();
	gl_variavel::db.queryPrepareExec(query, "SELECT user FROM variavel_user;");
	gl_variavel::db.fechar();

	query.first();
	if(query.value(0).toString().size())
		{ui->cbSalvarUser->setChecked(true);}
	else
		{ui->cbSalvarUser->setChecked(false);}
	ui->line_user->setText(query.value(0).toString());
}

fm_login::~fm_login()
{
	delete ui;
}

void fm_login::on_btn_logar_clicked()
{
	try
	{
		QString user = ui->line_user->text();
		QString senha = ui->line_senha->text();

		gl_variavel::db.abrir();
		QSqlQuery query;

		if(ui->cbSalvarUser->isChecked())
		{
			gl_variavel::db.queryPrepareExec(query, "UPDATE variavel_user SET user='"+ui->line_user->text()+"';");
		}
		else
		{
			gl_variavel::db.queryPrepareExec(query, "UPDATE variavel_user SET user='';");
		}

		gl_variavel::db.queryPrepareExec(query, "SELECT nome, acesso, id "
										 "FROM tb_pessoas, tb_vendedores "
										 "WHERE user = '"+user+"' AND senha = '"+senha+"' AND id = id_pessoa;");
		if(!query.first()) throw std::string("Colaborador não encontrado.");
		gl_variavel::db.fechar();

		gl_variavel::login			= true;
		gl_variavel::nomeVendedor	= query.value(0).toString().toStdString();
		gl_variavel::acessoVendedor	= query.value(1).toString().toStdString()[0];
		gl_variavel::idVendedor		= query.value(2).toInt();

		close();
	}
	catch(std::string &e)	{QMessageBox::information(this, "Informação", QString::fromStdString(e));}
	catch(QString &e)		{QMessageBox::warning(this, "Erro (19)", e);}
	catch(...)				{QMessageBox::critical(this, "Erro (19)", "Erro critico.");}
	gl_variavel::db.fechar();
}

void fm_login::on_btn_cancel_clicked()
{
	gl_variavel::login = false;
	close();
}

void fm_login::on_cbMostrarSenha_stateChanged(int arg1)
{
	if(arg1)	{ui->line_senha->setEchoMode(QLineEdit::Normal);}
	else		{ui->line_senha->setEchoMode(QLineEdit::Password);}
}
