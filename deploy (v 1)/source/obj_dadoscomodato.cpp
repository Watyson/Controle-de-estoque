#include "obj_dadoscomodato.h"

obj_dadosComodato::obj_dadosComodato(bool status, std::string data, std::string hora, std::string vendedor, std::string cliente, double valor, int id):
	status	(status),
	data	(data),
	hora	(hora),
	vendedor(vendedor),
	cliente	(cliente),
	valor	(valor),
	id		(id)
{}
