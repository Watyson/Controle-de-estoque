#include "obj_vendedor.h"

obj_vendedor::obj_vendedor():
	user(""),
	senha(""),
	acesso(' ')
{}

obj_vendedor::obj_vendedor(std::string user):
	senha(""),
	acesso(' ')
{
	setUser(user);
}

obj_vendedor::obj_vendedor(std::string nome, std::string tel):
	user(""),
	senha(""),
	acesso(' ')
{
	setNome(nome);
	setTel(tel);
}

obj_vendedor::obj_vendedor(std::string nome, std::string tel, std::string user, std::string senha, char acesso)
{
	setNome(nome);
	setTel(tel);
	setAcesso(acesso);
	setUser(user);
	setSenha(senha);
}

void obj_vendedor::setUser(std::string a)
{
	if(a.size() > 15 || !a.size()) throw std::string("user inválido.");
	user = a;
}

void obj_vendedor::setSenha(std::string a)
{
	if(a.size() > 15 || !a.size()) throw std::string("senha inválida.");
	senha = a;
}

void obj_vendedor::setAcesso(char a)
{
	if(a != 'A' && a != 'B' ) throw std::string("Acesso inválido.");
	acesso = a;
}

bool obj_vendedor::operator<(obj_vendedor const &b) const
{
	std::string nome = getNome();
	std::string tel = getTel().numero();

	std::string bNome = b.getNome();
	std::string bTel = b.getTel().numero();

	if(nome.size() && bNome.size() && tel.size() && bTel.size())
	{
		return nome < bNome || (nome == bNome && tel < bTel);
	}
	return user < b.user;
}

bool obj_vendedor::operator==(obj_vendedor const &b) const
{
	std::string nome = getNome();
	std::string tel = getTel().numero();

	std::string bNome = b.getNome();
	std::string bTel = b.getTel().numero();

	if(nome.size() && bNome.size() && tel.size() && bTel.size())
	{
		return nome == bNome && tel == bTel;
	}
	return user == b.user;
}

bool obj_vendedor::operator!=(obj_vendedor const &b) const
{
	std::string nome = getNome();
	std::string tel = getTel().numero();

	std::string bNome = b.getNome();
	std::string bTel = b.getTel().numero();

	if(nome.size() && bNome.size() && tel.size() && bTel.size())
	{
		return nome != bNome || tel != bTel;
	}
	return user != b.user;
}
