#ifndef BD_H
#define BD_H

#include<QtSql>

class bd
{
	private:
		QSqlDatabase db;

	public:
		bd(){}
		~bd(){if(db.isOpen()) db.close();}

		void inicializar(){
			db=QSqlDatabase::addDatabase("QSQLITE");
			db.setDatabaseName(qApp->applicationDirPath()+"/dados/dados.db");
		}

		void abrir()	{if(!db.open()) throw std::string("Erro ao abrir banco de dados.");}
		bool eAberto()	{return db.isOpen();}
		void fechar()	{db.close();}

		void queryPrepare(QSqlQuery &query, QString a)	{if(!query.prepare(a))	throw std::string("Erro ao preparar query\n"+a.toStdString());}
		void queryExec(QSqlQuery &query, QString a="")	{if(!query.exec(a))		throw std::string("Erro ao executar query\n"+a.toStdString());}
		void queryFirst(QSqlQuery &query)				{if(!query.first())		throw std::string("Erro ao selecionar o primeiro na query\n");}

		void queryPrepareExec(QSqlQuery &query, QString a){
			if(!query.prepare(a))	throw std::string("Erro ao preparar query\n"+a.toStdString());
			if(!query.exec())		throw std::string("Erro ao executar query\n"+a.toStdString());
		}
};

#endif // BD_H
