#ifndef OBJ_PESSOA_H
#define OBJ_PESSOA_H

#include <string>
#include <obj_telefone.h>

class obj_pessoa
{
	private:		// Variaveis
		std::string nome;	//Até 150 carac
		obj_telefone tel;	//Até 11 carac
		int id;

	public:			// Funcoes
		obj_pessoa();
		obj_pessoa(std::string nome, std::string tel);
		obj_pessoa(std::string nome, std::string tel, int id);

		void setNome(std::string nome);
		void setTel(std::string tel)	{this->tel.setTel(tel);}
		void setId(int id)	{this->id=id;}

		std::string getNome()const	{return nome;}
		obj_telefone getTel()const	{return tel;}
		int getId()const			{return id;}

		bool operator<(obj_pessoa const &b) const{
			return getNome() < b.getNome() || (getNome() == b.getNome() && getTel().numero() < getTel().numero());
		}

		bool operator==(obj_pessoa const &b) const{
			return (getNome() == b.getNome() && getTel().numero() == b.getTel().numero());
		}

		bool operator!=(obj_pessoa const &b) const{
			return (getNome() != b.getNome() || getTel().numero() != b.getTel().numero());
		}
};

#endif // OBJ_PESSOA_H
