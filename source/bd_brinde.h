#ifndef BD_BRINDE_H
#define BD_BRINDE_H

#include<gl_variavel.h>

#include<set>
#include<vector>

#include<obj_brinde.h>

class bd_brinde
{
	private:
		std::set<obj_brinde> ed;

	public:
		bd_brinde();

		void carregarEd();
		void inserirNovo(obj_brinde a);
		void remover(obj_brinde a);
		void editar(obj_brinde antigo, obj_brinde novo);

		obj_brinde encontrar(std::string nome)	{return *ed.find(obj_brinde(nome));}
		std::set<obj_brinde>const * getEd()const {return &ed;}

		// Precisa deletar a variavel de retorno
		std::vector<obj_brinde>const * filtroEd(QString busca)const;

		// Se o objeto A tiver nome e telefone ele vai procurar o vendedor por esse, se não vai procurar pelo user.
		bool existeBrinde(obj_brinde a)const{return ed.find(a) != ed.end();}

		int qtdBrindes()const {return int(ed.size());}
};

#endif // BD_BRINDE_H
