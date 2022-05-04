#ifndef BD_ROUPA_H
#define BD_ROUPA_H

#include<gl_variavel.h>

#include<set>
#include<vector>

#include<obj_roupa.h>

class bd_roupa
{
	private:
		std::set<obj_roupa> ed;
		double desconto;

	public:
		bd_roupa();

		void carregarEd();
		void inserirNovo(obj_roupa a);
		void remover(obj_roupa a);
		void editar(obj_roupa antigo, obj_roupa novo);

		obj_roupa encontrar(std::string id);

		std::set<obj_roupa>const *getEd() const	{return &ed;}

		// Precisa deletar a variavel de retorno
		std::vector<obj_roupa>const * filtroEd(QString busca)const;

		bool existe		(obj_roupa a)	const {return ed.find(a) != ed.end();}
		bool existeId	(std::string a)	const;
		bool existeRoupa(std::string a)	const;

		void setDesconto(double a);
		double getDesconto()const {return desconto;}

		void concluirVenda(std::map<std::string, std::pair<int, double>> vendas);

};

#endif // BD_ROUPA_H
