#include "obj_cnpj.h"

obj_cnpj::obj_cnpj()
{

}

void obj_cnpj::setCnpj(std::string a)
{
	if(!eCnpj(a)) throw std::string("Cnpj inválido.");
	cnpj = a;
}

void obj_cnpj::operator=(std::string a)
{
	if(!eCnpj(a)) throw std::string("Cnpj inválido.");
	cnpj = a;
}
