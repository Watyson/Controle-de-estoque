#ifndef OBJ_CNPJ_H
#define OBJ_CNPJ_H

#include<string>
#include<gl_funcao.h>

class obj_cnpj
{
	private:		// Variaveis
		std::string cnpj;

	public:			// Funcoes
		obj_cnpj();

		void setCnpj(std::string a);

		std::string getCnpj()const		{return cnpj;}

		bool eCnpj(std::string a)const	{return a.size() <= 14 && gl_funcao::eNum(a);}

		void operator=(std::string a);
};

#endif // OBJ_CNPJ_H
