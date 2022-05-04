#include "obj_dadosvendedor.h"

void obj_dadosVendedor::setTipoPgmt(std::string pgmt)
{
	if(pgmt == "Dinheiro")				tipoPgmt = '0';
	else if(pgmt == "Cartão")			tipoPgmt = '1';
	else if(pgmt == "Comodato")			tipoPgmt = '2';
	else if(pgmt == "Transferência")	tipoPgmt = '3';
	else if(pgmt == "À vista")			tipoPgmt = '4';
	else throw std::string("Tipo de pagamento inválido.");
}

std::string obj_dadosVendedor::getTipoPagamento()const
{
	if(tipoPgmt == '0')	return "Dinheiro";
	if(tipoPgmt == '1')	return "Cartão";
	if(tipoPgmt == '2')	return "Comodato";
	if(tipoPgmt == '3')	return "Transferência";
	if(tipoPgmt == '4') return "À vista";
	return "";
}
