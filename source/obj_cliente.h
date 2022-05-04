#ifndef OBJ_CLIENTE_H
#define OBJ_CLIENTE_H

#include<obj_pessoa.h>
#include<obj_cep.h>
#include<obj_cnpj.h>

class obj_cliente: public obj_pessoa
{
	private:		// Variaveis
		std::string end;
		std::string ref;
		std::string cpf;
		obj_cep cep;
		obj_cnpj cnpj;

	public:			// Funcoes
		obj_cliente();
		obj_cliente(std::string cnpj);
		obj_cliente(std::string nome, std::string tel);
		obj_cliente(std::string nome, std::string tel, std::string end, std::string ref, std::string cep, std::string cnpj, std::string cpf, int idCliente=0);

		void setCpf(std::string a);
		void setEnd(std::string a);
		void setRef(std::string a);
		void setCep(std::string a)	{cep = a;}
		void setCnpj(std::string a)	{cnpj = a;}

		std::string getEnd()const	{return end;}
		std::string getRef()const	{return ref;}
		obj_cep getCep()const		{return cep;}
		obj_cnpj getCnpj()const		{return cnpj;}
		std::string getCpf()const	{return cpf;}

		bool operator<(obj_cliente const &b) const;
		bool operator==(obj_cliente const &b) const;
		bool operator!=(obj_cliente const &b) const;
};

#endif // OBJ_CLIENTE_H
