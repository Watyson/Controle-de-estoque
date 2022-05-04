#include "bd_relatorios.h"

bd_relatorios::bd_relatorios()	{}

void bd_relatorios::carregarEd()
{
	while(edComodato.size()) edComodato.erase(edComodato.begin());

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "SELECT A.status, A.data, A.hora, \"vendedor\", \"cliente\", valor_total, id_venda "
											"FROM("
												"(SELECT status, data, hora, P.nome\"vendedor\", V.valor_total "
													"FROM tb_comodato as C, tb_vendas as V, tb_pessoas as P "
													"WHERE C.id_venda = V.id AND V.id_vendedor = P.id) as A "
												"INNER JOIN "
												"(SELECT status, data, hora, P.nome\"cliente\", V.valor_total\"valor\", id_venda "
													"FROM tb_comodato as C, tb_vendas as V, tb_pessoas as P "
													"WHERE C.id_venda = V.id AND V.id_cliente = P.id) as B "
												"ON A.hora = B.hora);");
	obj_dadosComodato dado;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		dado.setStatus	(query.value(0).toBool());
		dado.setData	(query.value(1).toString().toStdString());
		dado.setHora	(query.value(2).toString().toStdString());
		dado.setVendedor(query.value(3).toString().toStdString());
		dado.setCliente	(query.value(4).toString().toStdString());
		dado.setValor	(query.value(5).toDouble());
		dado.setId		(query.value(6).toInt());

		edComodato.insert(dado);
	}
	gl_variavel::db.fechar();
}

obj_dadosComodato bd_relatorios::getComodato(obj_dadosComodato comodato)
{
	std::set<obj_dadosComodato>::iterator it = edComodato.find(comodato);
	if(it == edComodato.end()) throw std::string("Dado não encontrado "+ comodato.getData());
	return *it;
}

std::set<obj_dadosComodato>const* bd_relatorios::buscaComodato(std::string busca)
{
	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, QString::fromStdString(busca));

	obj_dadosComodato dado;
	std::set<obj_dadosComodato>* ed = new std::set<obj_dadosComodato>;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		dado.setStatus	(query.value(0).toBool());
		dado.setData	(query.value(1).toString().toStdString());
		dado.setHora	(query.value(2).toString().toStdString());
		dado.setVendedor(query.value(3).toString().toStdString());
		dado.setCliente	(query.value(4).toString().toStdString());
		dado.setValor	(query.value(5).toDouble());

		ed->insert(dado);
	}
	gl_variavel::db.fechar();
	return ed;
}

void bd_relatorios::confirmarPagamento(obj_dadosComodato comodato)
{
	QString data = QDate::currentDate().toString("yyyy-MM-dd");
	QString hora = QTime::currentTime().toString("hh:mm:ss");

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, "UPDATE tb_comodato "
											"SET status=1, hora_pago='"+hora+"', data_pago='"+data+"' "
											"WHERE id_venda = "+QString::number(comodato.getId())+";");
	gl_variavel::db.fechar();
}

obj_dadosVendedor bd_relatorios::getVendedor(obj_dadosVendedor vendedor)
{
	std::set<obj_dadosVendedor>::iterator it = edVendedor.find(vendedor);
	if(it == edVendedor.end()) throw std::string("Dado não encontrado"+ QString::number(vendedor.getId()).toStdString());
	return *it;
}

std::set<obj_dadosVendedor>const* bd_relatorios::buscaVendedor(std::string busca)
{
	if(!busca.size())
	{
		busca = "SELECT tb_vendas.id, data, hora, nome\"vendedor\", valor_total, tipo_pgmt "
				"FROM tb_vendas, tb_pessoas "
				"WHERE id_vendedor = tb_pessoas.id";
	}

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, QString::fromStdString(busca));

	obj_dadosVendedor dado;
	std::set<obj_dadosVendedor>* ed = new std::set<obj_dadosVendedor>;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		dado.setId			(query.value(0).toInt());
		dado.setData		(query.value(1).toString().toStdString());
		dado.setHora		(query.value(2).toString().toStdString());
		dado.setVendedor	(query.value(3).toString().toStdString());
		dado.setValorVenda	(query.value(4).toDouble());
		dado.setTipoPgmt	(query.value(5).toString()[0].toLatin1());

		ed->insert(dado);
	}
	gl_variavel::db.fechar();
	return ed;
}

obj_dadosEsmalte bd_relatorios::getEsmalte(obj_dadosEsmalte esmalte)
{
	std::set<obj_dadosEsmalte>::iterator it = edEsmalte.find(esmalte);
	if(it == edEsmalte.end()) throw std::string("Dado não encontrado, "+ esmalte.getProduto());
	return *it;
}

std::set<obj_dadosEsmalte>const* bd_relatorios::buscaEsmalte(std::string busca)
{
	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, QString::fromStdString(busca));

	obj_dadosEsmalte dado;
	std::set<obj_dadosEsmalte>* ed = new std::set<obj_dadosEsmalte>;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		dado.setProduto		(query.value(0).toString().toStdString());
		dado.setQtd			(query.value(1).toInt());
		dado.setValorUm		(query.value(2).toDouble());
		dado.setValorTotal	(query.value(3).toDouble());

		ed->insert(dado);
	}
	gl_variavel::db.fechar();
	return ed;
}

obj_dadosVendedor bd_relatorios::getCliente(obj_dadosVendedor cliente)
{
	std::set<obj_dadosVendedor>::iterator it = edCliente.find(cliente);
	if(it == edCliente.end()) throw std::string("Dado não encontrado, "+ cliente.getVendedor());
	return *it;
}

std::set<obj_dadosVendedor>const* bd_relatorios::buscaCliente(std::string busca)
{
	if(!busca.size())
	{
		busca = "SELECT tb_vendas.id, data, hora, nome\"cliente\", valor_total, tipo_pgmt "
				"FROM tb_vendas, tb_pessoas "
				"WHERE id_cliente = tb_pessoas.id";
	}

	QSqlQuery query;
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	gl_variavel::db.queryPrepareExec(query, QString::fromStdString(busca));

	obj_dadosVendedor dado;
	std::set<obj_dadosVendedor>* ed = new std::set<obj_dadosVendedor>;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		dado.setId			(query.value(0).toInt());
		dado.setData		(query.value(1).toString().toStdString());
		dado.setHora		(query.value(2).toString().toStdString());
		dado.setVendedor	(query.value(3).toString().toStdString());
		dado.setValorVenda	(query.value(4).toDouble());
		dado.setTipoPgmt	(query.value(5).toString()[0].toLatin1());

		ed->insert(dado);
	}
	gl_variavel::db.fechar();
	return ed;
}
