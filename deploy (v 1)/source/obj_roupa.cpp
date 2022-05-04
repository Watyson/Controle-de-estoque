#include "obj_roupa.h"

obj_roupa::obj_roupa(std::string id, std::string roupa, int qtd, double compra, double venda):
	id(""),
	roupa(""),
	qtd(-1),
	vlrCompra(-1),
	vlrVenda(-1)
{
	setId(id);
	setRoupa(roupa);
	setQtd(qtd);
	setVlrCompra(compra);
	setVlrVenda(venda);
}

std::string obj_roupa::getId() const
{
	return id;
}

void obj_roupa::setId(const std::string &value)
{
	id = value;
}

std::string obj_roupa::getRoupa() const
{
	return roupa;
}

void obj_roupa::setRoupa(const std::string &value)
{
	roupa = value;
}

int obj_roupa::getQtd() const
{
	return qtd;
}

void obj_roupa::setQtd(int value)
{
	qtd = value;
}

double obj_roupa::getVlrCompra() const
{
	return vlrCompra;
}

double obj_roupa::getVlrVenda() const
{
	return vlrVenda;
}

void obj_roupa::setVlrVenda(double value)
{
	vlrVenda = value;
}

void obj_roupa::setVlrCompra(double value)
{
	vlrCompra = value;
}
