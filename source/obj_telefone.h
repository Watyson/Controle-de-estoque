#ifndef OBJ_TELEFONE_H
#define OBJ_TELEFONE_H

#include<gl_funcao.h>

class obj_telefone
{
	private:		// Variaveis
		std::string ddd;
		std::string digVer;
		std::string num;

	public:			// Funcoes
		obj_telefone();
		obj_telefone(std::string a);

		void setDDD(std::string ddd);
		void setNumero(std::string numero);
		void setDigVer(char a);
		void setTel(std::string a);

		//std::string getDDD()const		{return ddd;}
		//std::string getDigVer()const	{return digVer;}
		//std::string getNum()const		{return num;}
		std::string getNum();

		std::string numero()const	{return ddd+digVer+num;}
		std::string formatoTel();
		static std::string formatoNum(std::string tel);

		bool eNumValido(std::string a)const	{return a.size() == 11 && gl_funcao::eNum(a);}

		void operator=(std::string a);
		bool operator<(obj_telefone const &b) const		{return numero() < b.numero();}
		bool operator==(obj_telefone const &b) const	{return numero() == b.numero();}
		bool operator!=(obj_telefone const &b) const	{return numero() != b.numero();}
};

#endif // OBJ_TELEFONE_H
