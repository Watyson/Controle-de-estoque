#include "gl_funcao.h"

gl_funcao::gl_funcao()
{}

bool gl_funcao::eNum(std::string a)
{
	unsigned long long i=0;
	for( ; i<a.size() && (a[i] >= '0' && a[i] <= '9'); ++i);
	if(i != a.size()) return false;
	return true;
}
