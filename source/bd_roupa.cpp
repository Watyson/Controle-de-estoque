#include "bd_roupa.h"

bd_roupa::bd_roupa()
{}

void bd_roupa::carregarEd()
{
	while(ed.size()) ed.erase(ed.begin());

	obj_roupa obj;
	QSqlQuery query;

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "SELECT roupa, qtd, vlr_venda, vlr_compra, id "
											"FROM tb_roupa;");

	for(bool aux = query.first(); aux; aux=query.next())
	{
		obj.setRoupa	(query.value(0).toString().toStdString());
		obj.setQtd		(query.value(1).toInt());
		obj.setVlrVenda	(query.value(2).toDouble());
		obj.setVlrCompra(query.value(3).toDouble());
		obj.setId		(query.value(4).toString().toStdString());

		ed.insert(obj);
	}

	gl_variavel::db.queryPrepareExec(query, "SELECT qtd FROM variavel_desc_roupa;");
	query.first();
	desconto = query.value(0).toDouble();

	gl_variavel::db.fechar();
}

void bd_roupa::inserirNovo(obj_roupa a)
{
	QString roupa	= QString::fromStdString(a.getRoupa());
	QString qtd		= QString::number(a.getQtd());
	QString compra	= QString::number(a.getVlrCompra());
	QString venda	= QString::number(a.getVlrVenda());
	QString id		= QString::fromStdString(a.getId());

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	// Registra o produto.
	gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_roupa(id, roupa, qtd, vlr_compra, vlr_venda) "
											"VALUES ('"+id+"', '"+roupa+"', "+qtd+", "+compra+","+venda+");");
	ed.insert(a);

	gl_variavel::db.fechar();
}

void bd_roupa::remover(obj_roupa a)
{
	// Verifica se já existe a roupa.
	if(!existe(a)) throw std::string("Não existe uma roupa com esse codigo de barras.");

	QSqlQuery query;

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "DELETE FROM tb_roupa "
											"WHERE id='"+QString::fromStdString(a.getId())+"';");
	gl_variavel::db.fechar();

	ed.erase(a);
}

void bd_roupa::editar(obj_roupa antigo, obj_roupa novo)
{
	// Verifica se já existe o vendedor ou nome de usuario.
	if(!existe(antigo)) throw std::string("Não existe uma roupa com esse cod de barras.");

	QString roupa	= QString::fromStdString(novo.getRoupa());
	QString qtd		= QString::number(novo.getQtd());
	QString compra	= QString::number(novo.getVlrCompra());
	QString venda	= QString::number(novo.getVlrVenda());
	QString id		= QString::fromStdString(novo.getId());

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "UPDATE tb_roupa "
											"SET id='"+id+"', roupa='"+roupa+"', vlr_compra="+compra+", vlr_venda="+venda+", qtd="+qtd+" "
											"WHERE id='"+QString::fromStdString(antigo.getId())+"';");
	gl_variavel::db.fechar();

	ed.erase(antigo);
	ed.insert(novo);
}

obj_roupa bd_roupa::encontrar(std::string id)
{
	std::set<obj_roupa>::iterator it = ed.find(obj_roupa(id));
	if(it == ed.end())	throw std::string("Roupa não encontrada.");
	return *it;
}

std::vector<obj_roupa>const * bd_roupa::filtroEd(QString busca)const
{
	std::vector<obj_roupa> * const ed = new std::vector<obj_roupa>();
	QSqlQuery query;
	obj_roupa obj;

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}

	gl_variavel::db.queryPrepareExec(query, busca);
	for(bool aux = query.first(); aux; aux=query.next())
	{
		obj.setId	(query.value(0).toString().toStdString());
		obj.setRoupa(query.value(1).toString().toStdString());

		ed->push_back(obj);
	}
	gl_variavel::db.fechar();

	return ed;
}

bool bd_roupa::existeId(std::string a)const{
	std::set<obj_roupa>::iterator it = ed.begin();
	for( ; it != ed.end() && it->getId() != a; ++it);
	return it != ed.end();
}

bool bd_roupa::existeRoupa(std::string a)const{
	std::set<obj_roupa>::iterator it = ed.begin();
	for( ; it != ed.end() && it->getRoupa() != a; ++it);
	return it != ed.end();
}

void bd_roupa::setDesconto(double a)
{
	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "UPDATE variavel_desc_roupa "
											"SET qtd="+QString::number(a)+";");
	gl_variavel::db.fechar();

	desconto = a;
}

void bd_roupa::concluirVenda(std::map<std::string, std::pair<int, double>> vendas)
{
	// ========= Atualiza estoque
	double valorT=0;
	std::map<std::string, std::pair<int, double>>::iterator it;
	for(it = vendas.begin(); it != vendas.end(); ++it)
	{
		obj_roupa antigo, novo;
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

	QString pgmt = QString();
	if(gl_variavel::tipoPgmt == "Dinheiro")				pgmt = "0";
	else if(gl_variavel::tipoPgmt == "Cartão")			pgmt = "1";
	else if(gl_variavel::tipoPgmt == "Comodato")		pgmt = "2";
	else if(gl_variavel::tipoPgmt == "Transferência")	pgmt = "3";
	else if(gl_variavel::tipoPgmt == "À vista")			pgmt = "4";

	QString valor= "";
	if(pgmt == "4")
	{
		valor = QString::number(valorT - valorT * (desconto/100));
	}
	else			valor = QString::number(valorT);

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}

	gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_vendas(data, hora, id_vendedor, id_cliente, valor_total, tipo_pgmt, tipo_venda) "
											"VALUES	('"+data+"','"+hora+"',"+idVen+","+idCli+","+valor+",'"+pgmt+"', 'r');");

	// Seleciona o id da venda
	gl_variavel::db.queryPrepareExec(query, "SELECT * FROM tb_vendas WHERE data='"+data+"' AND hora='"+hora+"';");
	gl_variavel::db.queryFirst(query);

	// tb_produtos_vendidos |id|id_venda|id_produto|qtd|valor_um|valor_total|
	QString idVenda = query.value(0).toString();
	QString idProdu, qtd, vUnitar, vTotal;

	// Registra comodato
	if(pgmt == "2")
	{
		gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_comodato(id_venda, status) "
												"VALUES	("+idVenda+", 0);");
	}

	for(it = vendas.begin(); it != vendas.end(); ++it)
	{
		obj_roupa a = *ed.find(it->first);

		idProdu = QString::fromStdString(a.getId());
		qtd		= QString::number(it->second.first);
		if(pgmt == "4")	vUnitar = QString::number(it->second.second - it->second.second * (desconto/100));
		else			vUnitar = QString::number(it->second.second);
		vTotal	= QString::number(it->second.first * vUnitar.toDouble());

		gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_produtos_vendidos(id_venda, id_produto, qtd, valor_um, valor_total) "
												"VALUES	("+idVenda+","+idProdu+","+qtd+","+vUnitar+","+vTotal+");");
	}

	gl_variavel::db.fechar();
}
