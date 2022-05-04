#include "bd_vendedor.h"

bd_vendedor::bd_vendedor()
{}

void bd_vendedor::carregarEd()
{
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, "SELECT nome, tel, user, senha, acesso, id "
											"FROM tb_pessoas, tb_vendedores "
											"WHERE id = id_pessoa;");
	obj_vendedor vendedor;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		vendedor.setNome	(query.value(0).toString().toStdString());
		vendedor.setTel		(query.value(1).toString().toStdString());
		vendedor.setUser	(query.value(2).toString().toStdString());
		vendedor.setSenha	(query.value(3).toString().toStdString());
		vendedor.setAcesso	(query.value(4).toString().toStdString()[0]);
		vendedor.setId		(query.value(5).toString().toInt());

		ed.insert(vendedor);
	}
	gl_variavel::db.fechar();
}

void bd_vendedor::inserirNovo(obj_vendedor a)
{
	// Verifica se já existe o vendedor ou nome de usuario.
	if(existeVendedor(obj_vendedor(a.getUser()))) throw std::string("Já existe um vendedor com esse nome de usuário.");

	QString nome	= QString::fromStdString(a.getNome());
	QString tel		= QString::fromStdString(a.getTel().numero());
	QString user	= QString::fromStdString(a.getUser());
	QString senha	= QString::fromStdString(a.getSenha());
	char acesso		= a.getAcesso();

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	// Registra a nova pessoa.
	gl_variavel::db.queryPrepareExec(query, "SELECT id FROM tb_pessoas WHERE nome='"+nome+"' AND tel='"+tel+"';");
	if(!query.first())
	{
		gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_pessoas(nome, tel) "
												"VALUES ('"+nome+"','"+tel+"');");
		gl_variavel::db.queryPrepareExec(query, "SELECT id FROM tb_pessoas WHERE nome='"+nome+"' AND tel='"+tel+"';");
		query.first();
	}
	QString id = query.value(0).toString();

	// Insere a pessoa como vendedor.
	try	{gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_vendedores(user, senha, id_pessoa, acesso) "
												"VALUES ('"+user+"','"+senha+"',"+id+",'"+acesso+"')");}
	catch (...) {throw QString("Erro ao inserir no banco de dados.\nPossivel motivo: Uma pessoa com esse nome e telefone já é um vendedor.");}
	gl_variavel::db.fechar();

	a.setId(id.toInt());
	ed.insert(a);
}

void bd_vendedor::remover(obj_vendedor a)
{
	// Verifica se já existe o vendedor ou nome de usuario.
	if(!existeVendedor(obj_vendedor(a.getNome(), a.getTel().numero())))
		throw std::string("Não existe esse um vendedor com esse nome e telefone.");
	if(!existeVendedor(a))
		throw std::string("Não existe um vendedor com esse nome de usuário.");

	QString id= QString::number(a.getId());
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	// Retira a nova pessoa do banco de dados tb_pessoas.
	gl_variavel::db.queryPrepareExec(query, "SELECT * FROM tb_clientes WHERE id_pessoa="+QString::number(a.getId())+";");
	if(!query.first())
	{
		gl_variavel::db.queryPrepareExec(query, "DELETE FROM tb_pessoas "
												"WHERE id='"+id+"';");
	}

	// Retira a nova pessoa do banco de dados tb_vendedores.
	gl_variavel::db.queryPrepareExec(query, "DELETE FROM tb_vendedores "
											"WHERE id_pessoa='"+id+"';");
	gl_variavel::db.fechar();
	ed.erase(a);
}

void bd_vendedor::editar(obj_vendedor antigo, obj_vendedor novo)
{
	if(!existeVendedor(antigo))	throw std::string("Não existe esse um vendedor com esse user. (Antigo)");

	QString nome	= QString::fromStdString(novo.getNome());
	QString tel		= QString::fromStdString(novo.getTel().numero());
	QString user	= QString::fromStdString(novo.getUser());
	QString senha	= QString::fromStdString(novo.getSenha());
	QString id		= QString::number(novo.getId());
	char acesso		= novo.getAcesso();

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	if(antigo.getNome() != novo.getNome() || antigo.getTel() != novo.getTel())
	{
		// Atualiza a pessoa do banco de dados tb_pessoas.
		obj_pessoa pAntiga	(antigo.getNome(), antigo.getTel().numero(), antigo.getId());
		obj_pessoa pNova	(novo.getNome(), novo.getTel().numero(), novo.getId());

		// Atualiza a pessoa do banco de dados tb_pessoas.
		gl_variavel::db.queryPrepareExec(query, "UPDATE tb_pessoas "
												"SET nome='"+nome+"', tel='"+tel+"' "
												"WHERE id='"+id+"';");
	}

	// Atualiza a pessoa do banco de dados tb_vendedores.
	gl_variavel::db.queryPrepareExec(query, "UPDATE tb_vendedores "
											"SET user='"+user+"', senha='"+senha+"', acesso='"+acesso+"' "
											"WHERE id_pessoa='"+id+"';");
	gl_variavel::db.fechar();

	ed.erase(antigo);
	ed.insert(novo);
}

std::vector<obj_vendedor>const * bd_vendedor::filtroEd(QString busca)const
{
	std::vector<obj_vendedor> * const ed = new std::vector<obj_vendedor>();

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, busca);
	obj_vendedor vendedor;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		vendedor.setNome		(query.value(0).toString().toStdString());
		vendedor.setTel			(query.value(1).toString().toStdString());

		ed->push_back(vendedor);
	}
	gl_variavel::db.fechar();
	return ed;
}
