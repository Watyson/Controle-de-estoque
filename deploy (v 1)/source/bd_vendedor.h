#ifndef BD_VENDEDOR_H
#define BD_VENDEDOR_H

#include<gl_variavel.h>

#include<set>
#include<vector>

#include<obj_vendedor.h>

class bd_vendedor
{
	private:
		std::set<obj_vendedor> ed;

	public:
		bd_vendedor();

		void carregarEd();
		void inserirNovo(obj_vendedor a);
		void remover(obj_vendedor a);
		void editar(obj_vendedor antigo, obj_vendedor novo);

		obj_vendedor encontrarVendedor(std::string user)					{return *ed.find(obj_vendedor(user));}
		obj_vendedor encontrarVendedor(std::string nome, std::string tel)	{return *ed.find(obj_vendedor(nome, tel));}

		std::set<obj_vendedor>const * getEdVendedor()const {return &ed;}

		// Precisa deletar a variavel de retorno
		std::vector<obj_vendedor>const * filtroEd(QString busca)const;

		// Se o objeto A tiver nome e telefone ele vai procurar o vendedor por esse, se não vai procurar pelo user.
		bool existeVendedor(obj_vendedor a)const{return ed.find(a) != ed.end();}

		int qtdVendedor()const {return int(ed.size());}
};

#endif // BD_VENDEDOR_H
