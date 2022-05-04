#include "obj_cep.h"

obj_cep::obj_cep()
{}

void obj_cep::setCep(std::string a)
{
	if(!eCep(a)) throw std::string("Cep inválido.");
	cep = a;
}

void obj_cep::operator=(std::string a)
{
	if(!eCep(a)) throw std::string("Cep inválido.");
	cep = a;
}
