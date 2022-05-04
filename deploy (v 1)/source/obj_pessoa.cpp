#include "obj_pessoa.h"

obj_pessoa::obj_pessoa():
	nome(""),
	id(0)
{}

obj_pessoa::obj_pessoa(std::string nome, std::string tel):
	nome(nome),
	id(0)
{
	this->tel.setTel(tel);
}

obj_pessoa::obj_pessoa(std::string nome, std::string tel, int id)
{
	setTel(tel);
	setNome(nome);
	setId(id);
}

void obj_pessoa::setNome(std::string nome)
{
	if(!nome.size())		throw std::string("Nome inválido.");
	if(nome.size() > 150)	throw std::string("Nome muito grande.");
	this->nome = nome;
}
