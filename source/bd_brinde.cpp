#include "bd_brinde.h"

bd_brinde::bd_brinde() {}

void bd_brinde::carregarEd()
{
	while(ed.size()) ed.erase(ed.begin());

	gl_variavel::db.abrir();
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, "SELECT nome, qtd, vlr_custo "
											"FROM tb_brinde;");
	obj_brinde brinde;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		brinde.setNome	(query.value(0).toString().toStdString());
		brinde.setQtd	(query.value(1).toInt());
		brinde.setValor	(query.value(2).toDouble());

		ed.insert(brinde);
	}
	gl_variavel::db.fechar();
}

void bd_brinde::inserirNovo(obj_brinde a)
{
	// Verifica se já existe o brinde.
	if(existeBrinde(a))	throw std::string("Já existe um brinde com esse nome.");

	QString nome	= QString::fromStdString(a.getNome());
	QString qtd		= QString::number(a.getQtd());
	QString valor	= QString::number(a.getValor());

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	// Insere o brinde
	try	{gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_brinde(nome, qtd, vlr_custo) "
												 "VALUES ('"+nome+"', "+qtd+", "+valor+")");}
	catch (...) {throw QString("Erro ao inserir no banco de dados.\nPossivel motivo: Já existe um brinde com esse nome.");}
	gl_variavel::db.fechar();
	ed.insert(a);
}

void bd_brinde::remover(obj_brinde a)
{
	// Verifica se já existe o brinde.
	if(!existeBrinde(a))	throw std::string("Não existe um brinde com esse nome.");

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	// Retira a pessoa do banco de dados tb_clientes.
	gl_variavel::db.queryPrepareExec(query, "DELETE FROM tb_brinde "
											"WHERE nome='"+QString::fromStdString(a.getNome())+"';");
	gl_variavel::db.fechar();
	ed.erase(a);
}

void bd_brinde::editar(obj_brinde antigo, obj_brinde novo)
{
	if(!existeBrinde(antigo))	throw std::string("Não existe um brinde com esse nome.");

	QString nome	= QString::fromStdString(novo.getNome());
	QString qtd		= QString::number(novo.getQtd());
	QString valor	= QString::number(novo.getValor());

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, "UPDATE tb_brinde "
											"SET nome='"+nome+"', qtd="+qtd+", vlr_custo="+valor+" "
											"WHERE nome='"+QString::fromStdString(antigo.getNome())+"';");
	gl_variavel::db.fechar();

	ed.erase(antigo);
	ed.insert(novo);
}

std::vector<obj_brinde>const * bd_brinde::filtroEd(QString busca)const
{
	std::vector<obj_brinde> * const ed = new std::vector<obj_brinde>();
	obj_brinde brinde;

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, busca);
	for(bool aux = query.first(); aux; aux=query.next())
	{
		brinde.setNome		(query.value(0).toString().toStdString());
		brinde.setQtd			(query.value(1).toInt());

		ed->push_back(brinde);
	}
	gl_variavel::db.fechar();
	return ed;
}
