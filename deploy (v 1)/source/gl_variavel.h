#ifndef GL_VARIAVEL_H
#define GL_VARIAVEL_H

#include<string>

#include<bd.h>
#include<bd_esmalte.h>
#include<bd_cliente.h>
#include<bd_vendedor.h>

class gl_variavel
{
	public:		// Variaveis
		// Banco de dados
		static bd db;
		static bool login;
		static int idVendedor;
		static std::string nomeVendedor;
		static char acessoVendedor;

		// Editar nova venda
		static bool editou;
		static int qtd;
		static int estoque;
		static std::string id;

		// Finalizar venda
		static int idCliente;
		static std::string nomeCliente;
		static std::string tipoPgmt;
		static bool finalizou;
		static double valor;
};

#endif // GL_VARIAVEL_H
