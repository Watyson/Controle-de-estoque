#ifndef OBJ_DADOSVENDEDOR_H
#define OBJ_DADOSVENDEDOR_H

#include<string>

class obj_dadosVendedor
{
	private:
		int id;
		std::string data, hora, vendedor;
		double valorVenda;
		char tipoPgmt;

	public:
		obj_dadosVendedor(int id=0, std::string data="", std::string hora="", std::string vendedor="",
						  double valorVenda=0.0, char tipoPgmt=' '):
						  id(id), data(data), hora(hora), vendedor(vendedor), valorVenda(valorVenda), tipoPgmt(tipoPgmt) {}

		void setId(int id)						{this->id = id;}
		void setData(std::string data)			{this->data = data;}
		void setHora(std::string hora)			{this->hora = hora;}
		void setVendedor(std::string vendedor)	{this->vendedor = vendedor;}
		void setValorVenda(double valor)		{this->valorVenda = valor;}
		void setTipoPgmt(char pgmt)				{this->tipoPgmt = pgmt;}
		void setTipoPgmt(std::string pgmt);

		int getId()const				{return id;}
		std::string getData()const		{return data;}
		std::string getHora()const		{return hora;}
		std::string getVendedor()const	{return vendedor;}
		double getValorVenda()const		{return valorVenda;}
		char getTipoPgmt()const			{return tipoPgmt;}
		std::string getTipoPagamento()const;

		bool operator< (obj_dadosVendedor a)const	{return id < a.id || (id == a.id && data < a.data) || (id == a.id && data == a.data && hora < a.hora);}
		bool operator==(obj_dadosVendedor a)const	{return id == a.id;}
		bool operator!=(obj_dadosVendedor a)const	{return id != a.id;}
};

#endif // OBJ_DADOSVENDEDOR_H
