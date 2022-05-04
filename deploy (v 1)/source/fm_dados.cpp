#include "fm_dados.h"
#include "ui_fm_dados.h"

fm_dados::fm_dados(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::fm_dados)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	QDate max = QDate::currentDate();
	QDate min(2021, 1, 1);

	ui->de_inicio->setDateRange(min, max);
	ui->de_fim->setDateRange(min, max);
	ui->de_fim->setDate(max);
}

fm_dados::~fm_dados(){delete ui;}

void fm_dados::roupa(){
	QString ini = ui->de_inicio->date().toString("yyyy-MM-dd");
	QString fim = ui->de_fim->date().toString("yyyy-MM-dd");

	QString pgmt;
	double vV=0, vDinheiro=0, vCartao=0, vComodato=0, vTransferencia=0, vVista=0, vTotal=0;
	double vC=0, vCTotal=0;

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	// =============================================
	// ================== Estoque ==================
	// =============================================

	gl_variavel::db.queryPrepareExec(query, "SELECT qtd, vlr_venda, vlr_compra "
											"FROM tb_roupa;");
	double qtd=0;
	for(bool aux = query.first(); aux; aux=query.next()){

		qtd = query.value(0).toInt();
		vV = query.value(1).toDouble();
		vC = query.value(2).toDouble();

		vTotal += vV * qtd;
		vCTotal += vC * qtd;
	}

	ui->lbRETotal->setText("Total: R$ "+QString::number(vTotal, 'f', 2));
	ui->lbRLuTotal->setText("R$ "+QString::number(vTotal-vCTotal, 'f', 2));
	// ===========================================
	// ================== Lucro ==================
	// ===========================================

	/* bugou ;(
	gl_variavel::db.queryPrepareExec(query,
	"SELECT A.id, valor_total, tipo_pgmt, A.tipo_venda "
	"FROM((SELECT id, valor_total, tipo_pgmt, tipo_venda "
	"FROM tb_vendas "
	"WHERE data BETWEEN '"+ini+"' AND '"+fim+"' AND tipo_venda='r') as A "
	"LEFT JOIN "
	"(SELECT id, valor_total, tipo_pgmt, tipo_venda "
	"FROM tb_vendas, tb_comodato "
	"WHERE data BETWEEN '"+ini+"' AND '"+fim+"' AND tipo_venda='r' AND id = id_venda AND status = 1) as B "
	"ON A.id=B.id) "
	"WHERE B.id is NULL;");
	*/

	gl_variavel::db.queryPrepareExec(query,
	"SELECT id, valor_total, tipo_pgmt, tipo_venda "
	"FROM tb_vendas, tb_comodato "
	"WHERE data BETWEEN '"+ini+"' AND '"+fim+"' AND tipo_venda='r' AND id = id_venda AND status = 0;");
	std::pair<QString, std::pair<double, QString>> dado;
	std::set<std::pair<QString, std::pair<double, QString>>> dados;
	for(bool aux = query.first(); aux; aux=query.next()){
		dado.first			= query.value(0).toString();
		dado.second.first	= query.value(1).toDouble();
		dado.second.second	= query.value(2).toString();
		dados.insert(dado);
	}

	gl_variavel::db.queryPrepareExec(query,
	"SELECT id, valor_total, tipo_pgmt, tipo_venda "
	"FROM tb_vendas "
	"WHERE data BETWEEN '"+ini+"' AND '"+fim+"' AND tipo_venda='r';");
	vTotal = vV = 0;
	for(bool aux = query.first(); aux; aux=query.next()){
		dado.first			= query.value(0).toString();
		dado.second.first	= query.value(1).toDouble();
		dado.second.second	= query.value(2).toString();

		if(dados.find(dado) == dados.end())
		{
			if(dado.second.second == "0")		{vDinheiro += dado.second.first;}
			else if(dado.second.second == "1")	{vCartao += dado.second.first;}
			else if(dado.second.second == "2")	{vComodato += dado.second.first;}
			else if(dado.second.second == "3")	{vTransferencia += dado.second.first;}
			else								{vVista += dado.second.first;}
			vTotal+=dado.second.first;
		}
	}

	ui->lbRLDinheiro->		setText("Dinheiro: R$ "+QString::number(vDinheiro, 'f', 2));
	ui->lbRLCartao->		setText("Cartão: R$ "+QString::number(vCartao, 'f', 2));
	ui->lbRLComodato->		setText("Comodato: R$ "+QString::number(vComodato, 'f', 2));
	ui->lbRLTransferencia->	setText("Transferência: R$ "+QString::number(vTransferencia, 'f', 2));
	ui->lbRLVista->			setText("À vista: R$ "+QString::number(vVista, 'f', 2));
	ui->lbRLTotal->			setText("Total: R$ "+QString::number(vTotal, 'f', 2));

	gl_variavel::db.fechar();
}

void fm_dados::esmalte(){
	QString ini = ui->de_inicio->date().toString("yyyy-MM-dd");
	QString fim = ui->de_fim->date().toString("yyyy-MM-dd");

	QString pgmt;
	double vV=0, vDinheiro=0, vCartao=0, vComodato=0, vTotal=0;
	double vC=0, vCTotal=0;

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}

	// =============================================
	// ================== Estoque ==================
	// =============================================
	gl_variavel::db.queryPrepareExec(query, "SELECT qtd, valor_um, valor_um_compra "
											"FROM tb_esmalte;");
	double qtd=0;
	for(bool aux = query.first(); aux; aux=query.next()){

		qtd = query.value(0).toInt();
		vV = query.value(1).toDouble();
		vC = query.value(2).toDouble();

		vTotal += vV * qtd;
		vCTotal += vC * qtd;
	}

	ui->lbETotal->setText("Total: R$ "+QString::number(vTotal, 'f', 2));
	ui->lbELTotal->setText("R$ "+QString::number(vTotal-vCTotal, 'f', 2));

	// ===========================================
	// ================== Lucro ==================
	// ===========================================
	 gl_variavel::db.queryPrepareExec(query,
	"SELECT id, valor_total, tipo_pgmt, tipo_venda "
	"FROM tb_vendas, tb_comodato "
	"WHERE data BETWEEN '"+ini+"' AND '"+fim+"' AND tipo_venda='e' AND id = id_venda AND status = 0;");
	std::pair<QString, std::pair<double, QString>> dado;
	std::set<std::pair<QString, std::pair<double, QString>>> dados;
	for(bool aux = query.first(); aux; aux=query.next()){
		dado.first			= query.value(0).toString();
		dado.second.first	= query.value(1).toDouble();
		dado.second.second	= query.value(2).toString().toStdString()[0];
		dados.insert(dado);
	}

	gl_variavel::db.queryPrepareExec(query,
	"SELECT id, valor_total, tipo_pgmt, tipo_venda "
	"FROM tb_vendas "
	"WHERE data BETWEEN '"+ini+"' AND '"+fim+"' AND tipo_venda='e';");
	vTotal = vV = 0;
	for(bool aux = query.first(); aux; aux=query.next()){
		dado.first			= query.value(0).toString();
		dado.second.first	= query.value(1).toDouble();
		dado.second.second	= query.value(2).toString();

		if(dados.find(dado) == dados.end())
		{
			if(dado.second.second == "0")		{vDinheiro += dado.second.first;}
			else if(dado.second.second == "1")	{vCartao += dado.second.first;}
			else								{vComodato += dado.second.first;}
			vTotal+=dado.second.first;
		}
	}

	ui->lbEVDinheiro->		setText("Dinheiro: R$ "+QString::number(vDinheiro, 'f', 2));
	ui->lbEVCartao->		setText("Cartão: R$ "+QString::number(vCartao, 'f', 2));
	ui->lbEVComodato->		setText("Comodato: R$ "+QString::number(vComodato, 'f', 2));
	ui->lbEVTotal->			setText("Total: R$ "+QString::number(vTotal, 'f', 2));

	gl_variavel::db.fechar();
}

void fm_dados::on_btnCarregar_clicked()
{
	try
	{
		fm_carregando a;
		a.show();
		roupa();
		esmalte();
		a.close();
	}
	catch(QString &e)		{QMessageBox::information(this, "Informação", e);}
	catch(std::string &e)	{QMessageBox::warning(this, "Erro (135)", QString::fromStdString(e));}
	catch(...)				{QMessageBox::critical(this, "Erro (135)", "Erro desconhecido.");}
}
