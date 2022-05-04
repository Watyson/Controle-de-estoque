#include "bd_venda.h"

bd_venda::bd_venda()
{}

void bd_venda::registrar(int idCliente, double valorVenda, char op, std::map<std::string, std::pair<int, double>> vendas)
{
	QString data = QDate::currentDate().toString("dd/MM/yyyy");
	QString hora = QTime::currentTime().toString("hh:mm:ss");
	QString vendedor = QString::number(gl_variavel::idVendedor);
	QString cliente = QString::number(idCliente);
	QString valorTotal = QString::number(valorVenda);

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	query.prepare("INSERT INTO tb_vendas(data, hora, id_vendedor, id_cliente, valor_total, tipo_pagamento)"
				  "VALUES ('"+data+"','"+hora+"',"+vendedor+","+cliente+","+valorTotal+","+op+");");
	gl_variavel::db.queryExec(query);

	// Seleciona o id da venda que foi gerado
	query.prepare("SELECT id FROM tb_vendas ORDER BY id DESC LIMIT 1");
	gl_variavel::db.queryExec(query);
	query.first();
	QString idVenda = query.value(0).toString();

	// Registrando cada produto vendido
	QString id_prod, qtd, valorUm;
	for(std::map<std::string, std::pair<int, double>>::iterator it = vendas.begin(); it != vendas.end(); ++it)
	{
		id_prod		= QString::fromStdString(it->first);
		qtd			= QString::number(it->second.first);
		valorUm		= QString::number(it->second.second);

		query.prepare("INSERT INTO tb_produtos_vendidos(id_venda, id_produto, qtd, valor_um)"
					  "VALUES ("+idVenda+","+id_prod+","+qtd+","+valorUm+");");
		gl_variavel::db.queryExec(query);
	}
	gl_variavel::db.fechar();
}
