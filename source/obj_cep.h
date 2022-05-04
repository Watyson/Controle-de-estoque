#ifndef OBJ_CEP_H
#define OBJ_CEP_H

#include<string>
#include<gl_funcao.h>

class obj_cep
{
	private:	// Variaveis
		std::string cep;

	public:		// Funcoes
		obj_cep();

		void setCep(std::string a);

		std::string getCep()const		{return cep;}

		bool eCep(std::string a)const	{return a.size() <= 8 && gl_funcao::eNum(a);}
		void operator=(std::string a);
};

#endif // OBJ_CEP_H
