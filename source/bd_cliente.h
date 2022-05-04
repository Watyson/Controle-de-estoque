#ifndef BD_CLIENTE_H
#define BD_CLIENTE_H

#include<gl_variavel.h>

#include<set>
#include<vector>

#include<obj_cliente.h>

class bd_cliente
{
	private:
		std::set<obj_cliente> ed;

	public:
		bd_cliente();

		void carregarEd();
		void inserirNovo(obj_cliente a);
		void remover(obj_cliente a);
		void editar(obj_cliente antigo, obj_cliente novo);

		obj_cliente encontrar(std::string nome, std::string tel)	{return *ed.find(obj_cliente(nome, tel));}

		obj_cliente encontrarCliente(std::string cnpj)					{return *ed.find(obj_cliente(cnpj));}
		obj_cliente encontrarCliente(std::string nome, std::string tel)	{return *ed.find(obj_cliente(nome, tel));}

		std::set<obj_cliente>const * getEd()const {return &ed;}

		// Precisa deletar a variavel de retorno
		std::vector<obj_cliente>const * filtroEd(QString busca)const;

		// Se o objeto A tiver nome e telefone ele vai procurar o vendedor por esse, se não vai procurar pelo user.
		bool existeCliente(obj_cliente a)const{return ed.find(a) != ed.end();}
		bool existeTel(std::string cor);
		bool existeCNPJ(std::string cnpj);
		bool existeCPF(std::string cpf);

		int qtdCliente()const {return int(ed.size());}
};

#endif // BD_CLIENTE_H
