#ifndef OBJ_BRINDE_H
#define OBJ_BRINDE_H

#include<string>

class obj_brinde
{
	private:
		std::string nome;
		int qtd;
		double valor;

	public:
		obj_brinde(std::string nome="", int qtd=-1, double valor=0): nome(nome), qtd(qtd), valor(valor) {}

		void setNome(std::string nome)	{this->nome=nome;}
		void setQtd(int qtd)			{this->qtd=qtd;}
		void setValor(double valor)		{this->valor=valor;}

		std::string getNome()const	{return nome;}
		int getQtd()const			{return qtd;}
		double getValor()const		{return valor;}

		bool operator<(obj_brinde const &b) const	{return nome < b.nome;}
		bool operator==(obj_brinde const &b)const	{return getNome() == b.getNome();}
		bool operator!=(obj_brinde const &b)const	{return (getNome() != b.getNome());}
};

#endif // OBJ_BRINDE_H
