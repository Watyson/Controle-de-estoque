#include "fm_novavenda_cadastrocliente.h"
#include "ui_fm_novavenda_cadastrocliente.h"

fm_novaVenda_cadastroCliente::fm_novaVenda_cadastroCliente(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_novaVenda_cadastroCliente)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui->lineTel->setValidator(new QRegExpValidator(QRegExp("^[0-9]{11}$")));
	ui->lineCep->setValidator(new QRegExpValidator(QRegExp("^[0-9]{8}$")));
	ui->lineCnpj->setValidator(new QRegExpValidator(QRegExp("^[0-9]{14}$")));
}

fm_novaVenda_cadastroCliente::~fm_novaVenda_cadastroCliente()
{
	delete ui;
}

void fm_novaVenda_cadastroCliente::on_btnGravar_clicked()
{
	try
	{
		if(ui->lbCnpj->text().size() != 21) throw QString("Já existe alguem com esse CNPJ.");


		if(!ui->lbCnpj->text().size() && !ui->lbCpf->text().size())
			throw QString("O cliente precisa de um cnpj ou cpf.");

		if(ui->lbCnpj->text().size() != 21) throw QString("Já existe alguem com esse CNPJ.");
		if(ui->lbCpf->text().size() != 20)	throw QString("Já existe alguem com esse CPF.");


		std::string nome	= ui->lineNome->text().toStdString();
		std::string tel		= ui->lineTel->text().toStdString();
		std::string end		= ui->lineEndereco->text().toStdString();
		std::string ref		= ui->lineRef->text().toStdString();
		std::string cep		= ui->lineCep->text().toStdString();
		std::string cnpj	= ui->lineCnpj->text().toStdString();
		std::string cpf		= ui->lineCpf->text().toStdString();

		// Verifica se os dados são validos.
		obj_cliente cliente(nome, tel, end, ref, cep, cnpj, cpf);

		// Insere os dados no banco de dados e na estrutura de dados na memoria.
		gl_ed::cliente.inserirNovo(cliente);

		QMessageBox::information(this, "Informação", "Novo cliente incluido com sucesso");
		close();
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (21)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (21)", "Erro desconhecido.");}
	if(gl_variavel::db.eAberto()) gl_variavel::db.fechar();
}

void fm_novaVenda_cadastroCliente::on_lineCnpj_textEdited(const QString &arg1)
{
	if(gl_ed::cliente.existeCNPJ(arg1.toStdString()))
	{
		ui->lbCnpj->setText("CNPJ (Apenas números) (Já existe)");
		ui->lbCnpj->setStyleSheet("QLabel{ "
								  "background:#e8e8e8;"
								  "color:red;"
								  "font-size:10pt;"
								  "border:none;"
								  "border-radius:6px;}");

		ui->lineCnpj->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
									"QLineEdit:disabled{background:#e7e7e7;}"
									"QLineEdit{"
									"color:red;"
									"font-size:9pt;"
									"border-radius:7px;"
									"border:1px solid black;}");
	}
	else
	{
		ui->lbCnpj->setText("CNPJ (Apenas números)");
		ui->lbCnpj->setStyleSheet("QLabel{ "
								  "background:#e8e8e8;"
								  "color:#808080;"
								  "font-size:10pt;"
								  "border:none;"
								  "border-radius:6px;}");

		ui->lineCnpj->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
									"QLineEdit:disabled{background:#e7e7e7;}"
									"QLineEdit{"
									"color:black;"
									"font-size:9pt;"
									"border-radius:7px;"
									"border:1px solid black;}");
	}
}

void fm_novaVenda_cadastroCliente::on_lineCpf_textEdited(const QString &arg1)
{
	if(gl_ed::cliente.existeCPF(arg1.toStdString()))
	{
		ui->lbCpf->setText("CPF (Apenas números) (Já existe)");
		ui->lbCpf->setStyleSheet("QLabel{ "
								  "background:#e8e8e8;"
								  "color:red;"
								  "font-size:10pt;"
								  "border:none;"
								  "border-radius:6px;}");

		ui->lineCpf->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
									"QLineEdit:disabled{background:#e7e7e7;}"
									"QLineEdit{"
									"color:red;"
									"font-size:9pt;"
									"border-radius:7px;"
									"border:1px solid black;}");
	}
	else
	{
		ui->lbCpf->setText("CPF (Apenas números)");
		ui->lbCpf->setStyleSheet("QLabel{ "
								  "background:#e8e8e8;"
								  "color:#808080;"
								  "font-size:10pt;"
								  "border:none;"
								  "border-radius:6px;}");

		ui->lineCpf->setStyleSheet("QLineEdit:enabled{background:#ffffff;}"
									"QLineEdit:disabled{background:#e7e7e7;}"
									"QLineEdit{"
									"color:black;"
									"font-size:9pt;"
									"border-radius:7px;"
									"border:1px solid black;}");
	}
}
