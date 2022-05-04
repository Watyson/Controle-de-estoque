#ifndef OBJ_ESMALTE_H
#define OBJ_ESMALTE_H

#include<string>

class obj_esmalte
{
	private:		// Variaveis
		std::string id;
		std::string cor;
		int qtd;	// Estoque
		double valorUm;
		double valorUmCompra;
		double valorUmDesconto;

	public:			// Funcoes
		obj_esmalte(std::string id="", std::string cor="", int qtd=0, double valorUm=0,
					double valorUmCompra=0, double valorUmDesconto=0);

		void setId(std::string id)			{if(id == "")	throw std::string("Id invalida!.");				this->id = id;}
		void setCor(std::string cor)		{if(!cor.size())throw std::string("Cor ("+cor+") invalida!.");	this->cor = cor;}
		void setQtd(int qtd)				{if(qtd < 0)	throw std::string("Qtd invalida!.");			this->qtd = qtd;}
		void setValorUm(double valorUm)		{if(valorUm < 0)throw std::string("Valor unitário invalido!.");	this->valorUm = valorUm;}
		void setValorUmCompra(double valor)	{if(valor < 0)	throw std::string("Valor invalido!.");			this->valorUmCompra=valor;}
		void setValorUmDesconto(double desc){if(desc == 0.0)throw std::string("Desconto invalido!.");		this->valorUmDesconto = desc;}

		std::string getId()const		{return id;}
		std::string getCor()const		{return cor;}
		int getQtd()const				{return qtd;}
		double getValorUm()const		{return valorUm;}
		double getValorUmCompra()const	{return valorUmCompra;}
		double getValorUmDesconto()const{return valorUmDesconto;}

		bool operator< (obj_esmalte a)const	{return id < a.id;}
		bool operator==(obj_esmalte a)const	{return id == a.id && cor == a.cor;}
		bool operator!=(obj_esmalte a)const	{return id != a.id || cor != a.cor;}
};

#endif // OBJ_ESMALTE_H
