#ifndef BD_VENDA_H
#define BD_VENDA_H

#include<gl_variavel.h>

#include<set>
#include<vector>

class bd_venda
{
	public:
		bd_venda();

		void registrar(int idCliente, double valorVenda, char op, std::map<std::string, std::pair<int, double>> vendas);
};

#endif // BD_VENDA_H
