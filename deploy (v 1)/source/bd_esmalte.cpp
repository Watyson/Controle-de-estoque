#include "bd_esmalte.h"

bd_esmalte::bd_esmalte()
{}

void bd_esmalte::carregarEd()
{
	while(ed.size()) ed.erase(ed.begin());

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, "SELECT id, cor, qtd, valor_um, valor_um_compra, valor_desconto "
											"FROM tb_esmalte;");
	bool aux = query.first();

	obj_esmalte obj;
	for(; aux; aux=query.next())
	{
		obj.setId(query.value(0).toString().toStdString());
		obj.setCor(query.value(1).toString().toStdString());
		obj.setQtd(query.value(2).toInt());
		obj.setValorUm(query.value(3).toDouble());
		obj.setValorUmCompra(query.value(4).toDouble());
		obj.setValorUmDesconto(query.value(5).toDouble());

		ed.insert(obj);
	}

	gl_variavel::db.queryPrepareExec(query, "SELECT qtd FROM variavel_desconto;");
	query.first();
	qtdDesconto = query.value(0).toInt();

	gl_variavel::db.fechar();
}

void bd_esmalte::inserirNovo(obj_esmalte a)
{
	QString id				= QString::fromStdString(a.getId());
	QString cor				= QString::fromStdString(a.getCor());
	QString qtd				= QString::number(a.getQtd());
	QString valorUm			= QString::number(a.getValorUm());
	QString valorUmCompra	= QString::number(a.getValorUmCompra());
	QString valorUmDesconto = QString::number(a.getValorUmDesconto());

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	// Registra o produto.
	gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_esmalte(id, cor, qtd, valor_um, valor_um_compra, valor_desconto) "
											"VALUES ('"+id+"','"+cor+"',"+qtd+","+valorUm+","+valorUmCompra+","+valorUmDesconto+");");
	ed.insert(a);
	gl_variavel::db.fechar();
}

void bd_esmalte::remover(obj_esmalte a)
{
	// Verifica se já existe o esmalte.
	if(!existe(a)) throw std::string("Não existe um esmalte com esse codigo de barras.");

	QSqlQuery query;

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "DELETE FROM tb_esmalte "
											"WHERE id='"+QString::fromStdString(a.getId())+"';");
	gl_variavel::db.fechar();

	ed.erase(a);
}

void bd_esmalte::editar(obj_esmalte antigo, obj_esmalte novo)
{
	// Verifica se já existe o vendedor ou nome de usuario.
	if(!existe(antigo)) throw std::string("Não existe um esmalte com essa descrição.");

	QString id				= QString::fromStdString(novo.getId());
	QString cor				= QString::fromStdString(novo.getCor());
	QString qtd				= QString::number(novo.getQtd());
	QString valorUm			= QString::number(novo.getValorUm());
	QString valorUmCompra	= QString::number(novo.getValorUmCompra());
	QString valorUmDesconto = QString::number(novo.getValorUmDesconto());

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "UPDATE tb_esmalte "
											"SET id='"+id+"', cor='"+cor+"', qtd="+qtd+", valor_um="+valorUm+
												", valor_um_compra="+valorUmCompra+", valor_desconto="+valorUmDesconto+
											" WHERE id='"+QString::fromStdString(antigo.getId())+"';");
	gl_variavel::db.fechar();

	ed.erase(antigo);
	ed.insert(novo);
}

bool bd_esmalte::existeCor(std::string cor)
{
	std::set<obj_esmalte>::iterator it = ed.begin();
	for(it = ed.begin(); it != ed.end() && it->getCor() != cor; ++it);
	if(it != ed.end())
	{
		return true;
	}
	return false;
}

obj_esmalte bd_esmalte::encontrar(std::string id)
{
	std::set<obj_esmalte>::iterator it = ed.find(obj_esmalte(id));
	if(it == ed.end())	throw std::string("Esmalte não encontrado.");
	return *it;
}

std::vector<obj_esmalte>const * bd_esmalte::filtroEd(QString busca)const
{
	std::vector<obj_esmalte> * const ed = new std::vector<obj_esmalte>();
	QSqlQuery query;
	obj_esmalte esmalte;

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}

	gl_variavel::db.queryPrepareExec(query, busca);
	for(bool aux = query.first(); aux; aux=query.next())
	{
		esmalte.setId(query.value(0).toString().toStdString());
		esmalte.setCor(query.value(1).toString().toStdString());

		ed->push_back(esmalte);
	}
	gl_variavel::db.fechar();

	return ed;
}

void bd_esmalte::setQtdDesconto(int a)
{
	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "UPDATE variavel_desconto "
											"SET qtd="+QString::number(a)+";");
	gl_variavel::db.fechar();

	qtdDesconto = a;
}

void bd_esmalte::concluirVenda(std::map<std::string, std::pair<int, double>> vendas)
{
	// ========= Atualiza estoque
	double valorT=0;
	std::map<std::string, std::pair<int, double>>::iterator it;
	for(it = vendas.begin(); it != vendas.end(); ++it)
	{
		obj_esmalte antigo, novo;
		antigo = novo = *ed.find(it->first);
		novo.setQtd(novo.getQtd() - it->second.first);
		editar(antigo, novo);

		valorT += vendas[antigo.getId()].first * vendas[antigo.getId()].second;
	}

	// ========= Atualiza aba de venda
	// tb_vendas |id|data|hora|id_vendedor|id_cliente|valor_total|tipo_pgmt|
	QString data = QDate::currentDate().toString("yyyy-MM-dd");
	QString hora = QTime::currentTime().toString("hh:mm:ss");
	QString idVen= QString::number(gl_variavel::idVendedor);
	QString idCli= QString::number(gl_variavel::idCliente);
	QString valor= QString::number(valorT);
	QString pgmt = QString();
	if(gl_variavel::tipoPgmt == "Dinheiro")		pgmt = "0";
	else if(gl_variavel::tipoPgmt == "Cartão")	pgmt = "1";
	else										pgmt = "2";

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}

	gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_vendas(data, hora, id_vendedor, id_cliente, valor_total, tipo_pgmt, tipo_venda) "
											"VALUES	('"+data+"','"+hora+"',"+idVen+","+idCli+","+valor+",'"+pgmt+"', 'e');");

	gl_variavel::db.queryPrepareExec(query, "SELECT * FROM tb_vendas WHERE data='"+data+"' AND hora='"+hora+"';");
	gl_variavel::db.queryFirst(query);

	// tb_produtos_vendidos |id|id_venda|id_produto|qtd|valor_um|valor_total|
	QString idVenda = query.value(0).toString();
	QString idProdu, qtd, vUnitar, vTotal;

	// Registra comodato
	if(pgmt == "2")
	{
		gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_comodato(id_venda, status) "
												"VALUES	("+idVenda+",0);");
	}

	for(it = vendas.begin(); it != vendas.end(); ++it)
	{
		obj_esmalte a = *ed.find(it->first);

		idProdu = QString::fromStdString(a.getId());
		qtd		= QString::number(it->second.first);
		vUnitar = QString::number(it->second.second);
		vTotal	= QString::number(it->second.first * it->second.second);

		gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_produtos_vendidos(id_venda, id_produto, qtd, valor_um, valor_total) "
												"VALUES	("+idVenda+","+idProdu+","+qtd+","+vUnitar+","+vTotal+");");
	}

	gl_variavel::db.fechar();
}
