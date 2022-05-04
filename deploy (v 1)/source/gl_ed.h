#ifndef GL_ED_H
#define GL_ED_H

#include<bd_esmalte.h>
#include<bd_cliente.h>
#include<bd_vendedor.h>
#include<bd_venda.h>
#include<bd_brinde.h>
#include<bd_relatorios.h>
#include<bd_roupa.h>

namespace Ui {class gl_ed;}

class gl_ed
{
	public:		// Variaveis
		static bd_esmalte esmalte;
		static bd_cliente cliente;
		static bd_vendedor vendedor;
		static bd_venda venda;
		static bd_brinde brinde;
		static bd_relatorios relatorios;
		static bd_roupa roupa;
};

#endif // GL_ED_H
