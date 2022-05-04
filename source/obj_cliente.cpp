#include "obj_cliente.h"

obj_cliente::obj_cliente():
	ref("")
{}

obj_cliente::obj_cliente(std::string nome, std::string tel):
	ref("")
{
	setNome(nome);
	setTel(tel);
}

obj_cliente::obj_cliente(std::string cnpj)
{
	setCnpj(cnpj);
}

obj_cliente::obj_cliente(std::string nome, std::string tel, std::string end, std::string ref, std::string cep, std::string cnpj, std::string cpf, int idCliente):
	end(""),
	ref(""),
	cpf("")
{
	setNome(nome);
	setTel(tel);
	setEnd(end);
	setRef(ref);
	setCep(cep);
	setCnpj(cnpj);
	setId(idCliente);
	setCpf(cpf);
}

void obj_cliente::setEnd(std::string a)
{
	if(a.size() > 150) throw std::string("Endereço muito grande.");
	end = a;
}

void obj_cliente::setRef(std::string a)
{
	if(a.size() > 150) throw std::string("Ponto de referência muito grande.");
	ref = a;
}

void obj_cliente::setCpf(std::string a)
{
	if(a.size() != 11) throw std::string("CPF inválido.");
	cpf = a;
}

bool obj_cliente::operator<(obj_cliente const &b) const
{
	std::string nome = getNome();
	std::string tel = getTel().numero();

	std::string bNome = b.getNome();
	std::string bTel = b.getTel().numero();

	if(nome.size() && bNome.size() && tel.size() && bTel.size())
		return nome < bNome || (nome == bNome && tel < bTel);
	if(cnpj.getCnpj().size())
		return cnpj.getCnpj() < b.cnpj.getCnpj();
	return cpf < b.getCpf();
}

bool obj_cliente::operator==(obj_cliente const &b) const
{
	std::string nome = getNome();
	std::string tel = getTel().numero();

	std::string bNome = b.getNome();
	std::string bTel = b.getTel().numero();

	if(cnpj.getCnpj().size())
		return cnpj.getCnpj() == b.cnpj.getCnpj();
	return cpf == b.getCpf();
}

bool obj_cliente::operator!=(obj_cliente const &b) const
{
	std::string nome = getNome();
	std::string tel = getTel().numero();

	std::string bNome = b.getNome();
	std::string bTel = b.getTel().numero();

	if(nome.size() && bNome.size() && tel.size() && bTel.size())
	{
		return nome != bNome || tel != bTel;
	}
	if(cnpj.getCnpj().size())
		return cnpj.getCnpj() != b.cnpj.getCnpj();
	return cpf != b.getCpf();
}
