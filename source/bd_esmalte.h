#ifndef BD_ESMALTE_H
#define BD_ESMALTE_H

#include<gl_variavel.h>

#include<set>
#include<vector>

#include<obj_esmalte.h>

class bd_esmalte
{
	private:
		std::set<obj_esmalte> ed;
		int qtdDesconto;

	public:
		bd_esmalte();

		void setQtdDesconto(int a);
		int getQtdDesconto()		{return qtdDesconto;}

		void carregarEd();
		void inserirNovo(obj_esmalte a);
		void remover(obj_esmalte a);
		void editar(obj_esmalte antigo, obj_esmalte novo);

		obj_esmalte encontrar(std::string id);

		std::set<obj_esmalte>const * getEd()const	{return &ed;}

		// Precisa deletar a variavel de retorno
		std::vector<obj_esmalte>const * filtroEd(QString busca)const;

		// Se o objeto A tiver nome e telefone ele vai procurar o vendedor por esse, se não vai procurar pelo user.
		bool existe(obj_esmalte a)const{return ed.find(a) != ed.end();}
		bool existeId(std::string a)const{return ed.find(a) != ed.end();}
		bool existeCor(std::string cor);

		int qtd()const {return int(ed.size());}

		void concluirVenda(std::map<std::string, std::pair<int, double>> vendas);
};

#endif // BD_ESMALTE_H
