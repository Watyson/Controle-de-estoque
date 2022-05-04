#ifndef OBJ_DADOSESMALTE_H
#define OBJ_DADOSESMALTE_H

#include <string>

class obj_dadosEsmalte
{
	private:		// Variaveis
		std::string produto;
		int qtd;
		double valorUm;
		double valorTotal;

	public:
		obj_dadosEsmalte(std::string produto="", int qtd=0, double valorUm=0, double valorTotal=0):
						 produto(produto), qtd(qtd), valorUm(valorUm), valorTotal(valorTotal) {}

		void setProduto(std::string produto)	{this->produto = produto;}
		void setQtd(int qtd)					{this->qtd = qtd;}
		void setValorUm(double valor)			{this->valorUm = valor;}
		void setValorTotal(double valor)		{this->valorTotal = valor;}

		std::string getProduto()const	{return produto;}
		int getQtd()const				{return qtd;}
		double getValorUm()const		{return valorUm;}
		double getValorTotal()const		{return valorTotal;}

		bool operator< (obj_dadosEsmalte a)const	{return produto < a.produto || (produto == a.produto && qtd < a.qtd);}
		bool operator==(obj_dadosEsmalte a)const	{return produto == a.produto && produto == a.produto;}
		bool operator!=(obj_dadosEsmalte a)const	{return produto != a.produto || produto != a.produto;}
};

#endif // OBJ_DADOSESMALTE_H
