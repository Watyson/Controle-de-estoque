#ifndef OBJ_VENDEDOR_H
#define OBJ_VENDEDOR_H

#include<obj_pessoa.h>

class obj_vendedor: public obj_pessoa
{
	private:		// Variaveis
		std::string user;
		std::string senha;
		char acesso;

	public:			// Funcoes
		obj_vendedor();
		obj_vendedor(std::string user);
		obj_vendedor(std::string nome, std::string tel);
		obj_vendedor(std::string nome, std::string tel, std::string user, std::string senha, char acesso);

		void setUser(std::string a);
		void setSenha(std::string a);
		void setAcesso(char a);

		std::string getUser()const	{return user;}
		std::string getSenha()const	{return senha;}
		char getAcesso()const		{return acesso;}

		bool operator<(obj_vendedor const &b) const;
		bool operator==(obj_vendedor const &b) const;
		bool operator!=(obj_vendedor const &b) const;
};

#endif // OBJ_VENDEDOR_H
