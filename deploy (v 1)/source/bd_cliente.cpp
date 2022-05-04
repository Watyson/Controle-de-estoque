#include "bd_cliente.h"

bd_cliente::bd_cliente()	{}

void bd_cliente::carregarEd()
{
	while(ed.size()) ed.erase(ed.begin());

	gl_variavel::db.abrir();
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, "SELECT nome, tel, id_pessoa, endereco, ref, cep, cnpj, cpf "
											"FROM tb_pessoas, tb_clientes "
											"WHERE id = id_pessoa;");
	obj_cliente cliente;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		cliente.setNome		(query.value(0).toString().toStdString());
		cliente.setTel		(query.value(1).toString().toStdString());
		cliente.setId		(query.value(2).toString().toInt());
		cliente.setEnd		(query.value(3).toString().toStdString());
		cliente.setRef		(query.value(4).toString().toStdString());
		cliente.setCep		(query.value(5).toString().toStdString());
		cliente.setCnpj		(query.value(6).toString().toStdString());
		cliente.setCpf		(query.value(7).toString().toStdString());

		ed.insert(cliente);
	}
	gl_variavel::db.fechar();
}


void bd_cliente::inserirNovo(obj_cliente a)
{
	// Verifica se já existe o cliente.
	if(a.getCpf().size())
	{
		obj_cliente c;
		c.setCpf(a.getCpf());

		if(existeCliente(c))
			throw std::string("Já existe um cliente com esse cpf registrado.");
	}

	if(a.getCnpj().getCnpj().size())
	{
		obj_cliente c;
		c.setCnpj(a.getCnpj().getCnpj());

		if(existeCliente(c))
			throw std::string("Já existe um cliente com esse cnpj registrado.");
	}

	QString nome	= QString::fromStdString(a.getNome());
	QString tel		= QString::fromStdString(a.getTel().numero());
	QString endereco= QString::fromStdString(a.getEnd());
	QString ref		= QString::fromStdString(a.getRef());
	QString cep		= QString::fromStdString(a.getCep().getCep());
	QString cnpj	= QString::fromStdString(a.getCnpj().getCnpj());
	QString cpf		= QString::fromStdString(a.getCpf());

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, "SELECT id FROM tb_pessoas WHERE nome='"+nome+"' AND tel='"+tel+"';");
	if(!query.first())
	{
		gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_pessoas(nome, tel) "
												"VALUES ('"+nome+"','"+tel+"');");
		gl_variavel::db.queryPrepareExec(query, "SELECT id FROM tb_pessoas WHERE nome='"+nome+"' AND tel='"+tel+"';");
		query.first();
	}
	QString id = query.value(0).toString();

	// Insere a pessoa como cliente.
	try	{gl_variavel::db.queryPrepareExec(query, "INSERT INTO tb_clientes(id_pessoa, endereco, ref, cep, cnpj, cpf) "
												"VALUES ("+id+",'"+endereco+"','"+ref+"','"+cep+"','"+cnpj+"', '"+cpf+"')");}
	catch (...) {throw QString("Erro ao inserir no banco de dados.\nPossivel motivo: Uma pessoa com esse CNPJ/CPF já é um cliente.");}
	gl_variavel::db.fechar();

	a.setId(id.toInt());
	ed.insert(a);
}

void bd_cliente::remover(obj_cliente a)
{
	// Verifica se já existe o cliente ou CNPJ.
	if(!existeCliente(obj_cliente(a.getNome(), a.getTel().numero())))
		throw std::string("Não existe esse um cliente com esse nome e telefone.");
	if(!existeCliente(a))
		throw std::string("Não existe um cliente com esse CNPJ.");

	QString id= QString::number(a.getId());
	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	// Verifica se existe um vendedor com esses dados, se sim não exclui a pessoa.
	gl_variavel::db.queryPrepareExec(query, "SELECT * FROM tb_vendedores WHERE id_pessoa="+QString::number(a.getId())+";");
	if(!query.first())
	{
		gl_variavel::db.queryPrepareExec(query, "DELETE FROM tb_pessoas "
												"WHERE id='"+id+"';");
	}

	// Retira a pessoa do banco de dados tb_clientes.
	gl_variavel::db.queryPrepareExec(query, "DELETE FROM tb_clientes "
											"WHERE id_pessoa='"+id+"';");
	gl_variavel::db.fechar();
	ed.erase(a);
}

void bd_cliente::editar(obj_cliente antigo, obj_cliente novo)
{
	if(!existeCliente(antigo))	throw std::string("Não existe esse um cliente com esse nome e telefone.");

	QString nome	= QString::fromStdString(novo.getNome());
	QString tel		= QString::fromStdString(novo.getTel().numero());
	QString end		= QString::fromStdString(novo.getEnd());
	QString ref		= QString::fromStdString(novo.getRef());
	QString cep		= QString::fromStdString(novo.getCep().getCep());
	QString cnpj	= QString::fromStdString(novo.getCnpj().getCnpj());
	QString id		= QString::number(novo.getId());
	QString cpf		= QString::fromStdString(novo.getCpf());

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

	// Atualiza a pessoa do banco de dados tb_clientes.
	gl_variavel::db.queryPrepareExec(query, "UPDATE tb_clientes "
											"SET endereco='"+end+"', ref='"+ref+"', cep='"+cep+"', cnpj='"+cnpj+"', cpf='"+cpf+"'"
											"WHERE id_pessoa="+id+";");
	gl_variavel::db.fechar();

	ed.erase(antigo);
	ed.insert(novo);
}

bool bd_cliente::existeTel(std::string tel)
{
	std::set<obj_cliente>::iterator it = ed.begin();
	for(it = ed.begin(); it != ed.end() && it->getTel().numero() != tel; ++it);
	return it != ed.end();
}

bool bd_cliente::existeCNPJ(std::string cnpj)
{
	std::set<obj_cliente>::iterator it = ed.begin();
	for(it = ed.begin(); it != ed.end() && it->getCnpj().getCnpj() != cnpj; ++it);
	return it != ed.end();
}

bool bd_cliente::existeCPF(std::string cpf)
{
	std::set<obj_cliente>::iterator it = ed.begin();
	for(it = ed.begin(); it != ed.end() && it->getCpf() != cpf; ++it);
	return it != ed.end();
}

std::vector<obj_cliente>const * bd_cliente::filtroEd(QString busca)const
{
	std::vector<obj_cliente> * const ed = new std::vector<obj_cliente>();

	if(!gl_variavel::db.eAberto())	{gl_variavel::db.abrir();}
	QSqlQuery query;

	gl_variavel::db.queryPrepareExec(query, busca);
	obj_cliente vendedor;
	for(bool aux = query.first(); aux; aux=query.next())
	{
		vendedor.setNome		(query.value(0).toString().toStdString());
		vendedor.setTel			(query.value(1).toString().toStdString());

		ed->push_back(vendedor);
	}
	gl_variavel::db.fechar();
	return ed;
}
