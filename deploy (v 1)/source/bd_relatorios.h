#ifndef BD_RELATORIOS_H
#define BD_RELATORIOS_H

#include<gl_variavel.h>

#include<set>
#include<vector>
#include<obj_dadoscomodato.h>
#include<obj_dadosvendedor.h>
#include<obj_dadosesmalte.h>

class bd_relatorios
{
	private:
		std::set<obj_dadosComodato> edComodato;
		std::set<obj_dadosVendedor> edVendedor;
		std::set<obj_dadosVendedor> edCliente;
		std::set<obj_dadosEsmalte> edEsmalte;

	public:
		bd_relatorios();

		void carregarEd();
		std::set<obj_dadosComodato>const* getEdComodato()	{return &edComodato;}
		obj_dadosComodato getComodato(obj_dadosComodato comodato);
		std::set<obj_dadosComodato>const* buscaComodato(std::string busca);
		void confirmarPagamento(obj_dadosComodato comodato);

		std::set<obj_dadosVendedor>const* getEdVendedor()	{return &edVendedor;}
		obj_dadosVendedor getVendedor(obj_dadosVendedor vendedor);
		std::set<obj_dadosVendedor>const* buscaVendedor(std::string busca = "");

		std::set<obj_dadosEsmalte>const* getEdEsmalte()		{return &edEsmalte;}
		obj_dadosEsmalte getEsmalte(obj_dadosEsmalte esmalte);
		std::set<obj_dadosEsmalte>const* buscaEsmalte(std::string busca = "");

		std::set<obj_dadosVendedor>const* getEdCliente()	{return &edVendedor;}
		obj_dadosVendedor getCliente(obj_dadosVendedor cliente);
		std::set<obj_dadosVendedor>const* buscaCliente(std::string busca = "");
};

#endif // BD_RELATORIOS_H
