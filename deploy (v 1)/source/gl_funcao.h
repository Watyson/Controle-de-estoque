#ifndef GL_FUNCAO_H
#define GL_FUNCAO_H

#include <string>
#include <QTableWidget>

class gl_funcao
{
	public:		// Funcoes
		gl_funcao();

		static bool eNum(std::string a);
		static bool eNum(char a) {return (a >= '0' && a <= '9');}

		static void removerLinhas(QTableWidget *a) {while(a->rowCount()) a->removeRow(0);}
};

#endif // GL_FUNCAO_H
