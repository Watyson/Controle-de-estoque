#include "obj_telefone.h"

obj_telefone::obj_telefone()
{
	ddd=digVer=num="";
}

obj_telefone::obj_telefone(std::string a)
{
	operator=(a);
}

void obj_telefone::setDDD(std::string ddd)
{
	if(ddd.size() != 2 && !gl_funcao::eNum(ddd)) throw std::string("DDD inválido.");
	this->ddd = ddd;
}

void obj_telefone::setDigVer(char a)
{
	if(!gl_funcao::eNum(a))	throw std::string("Digito verificador inválido.");
	digVer = a;
}

void obj_telefone::setNumero(std::string numero)
{
	if(numero.size() != 8 || !gl_funcao::eNum(numero)) throw std::string("Número de telefone ("+numero+") inválido. (1)");
	num = numero;
}

void obj_telefone::setTel(std::string a)
{
	if(a.size() != 11 || !eNumValido(a)) throw std::string("Número de telefone ("+a+") inválido. (2)");

	std::string aux;
	aux = a[0];
	aux+= a[1];
	setDDD(aux);
	setDigVer(a[2]);

	aux="";
	for(unsigned long long i=3; i<11; aux+=a[i++]);
	setNumero(aux);
}

std::string obj_telefone::formatoTel()
{
	std::string t = ddd + digVer + num;
	if(t.size() != 11 || !eNumValido(t)) throw std::string("Número de telefone ("+t+") inválido. (3)");

	std::string aux = "(";
	for(unsigned long long i=0; i<11; i++)
	{
		aux+=t[i];
		if(i == 1) aux+=") ";
		else if(i == 2) aux+=" ";
		else if(i == 6) aux+="-";
	}
	return aux;	//(xx) x xxxx-xxxx
}

std::string obj_telefone::formatoNum(std::string tel)
{
	if(tel.size() != 16) throw std::string("Número de telefone ("+tel+") inválido. (4)");
	std::string aux = "";
	for(unsigned long long i=1; i<tel.size(); i++)
	{
		if(i != 3 && i != 4 && i !=6 && i !=11) aux += tel[i];
	}
	//(xx) x xxxx-xxxx
	return aux;	//xxxxxxxxxxx
}

void obj_telefone::operator=(std::string a)
{
	if(a.size() != 11 || !eNumValido(a)) throw std::string("Número de telefone ("+a+") inválido. (5)");

	std::string aux;
	aux = a[0];
	aux+= a[1];
	setDDD(aux);
	setDigVer(a[2]);

	aux="";
	for(unsigned long long i=3; i<11; aux+=a[i++]);
	setNumero(aux);
}
