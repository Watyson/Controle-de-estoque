#ifndef OBJ_DADOSCOMODATO_H
#define OBJ_DADOSCOMODATO_H

#include<string>

class obj_dadosComodato
{
	private:
		bool status;
		std::string data, hora, vendedor, cliente;
		double valor;
		int id;

	public:
		obj_dadosComodato(bool status=false, std::string data="", std::string hora="", std::string vendedor="", std::string cliente="", double valor=0.0, int id=-1);

		void setStatus(bool status)				{this->status	= status;}
		void setData(std::string data)			{this->data		= data;}
		void setHora(std::string hora)			{this->hora		= hora;}
		void setVendedor(std::string vendedor)	{this->vendedor = vendedor;}
		void setCliente(std::string cliente)	{this->cliente	= cliente;}
		void setValor(double valor)				{this->valor	= valor;}
		void setId(int id)						{this->id		= id;}

		bool getStatus()const			{return status;}
		std::string getData()const		{return data;}
		std::string getHora()const		{return hora;}
		std::string getVendedor()const	{return vendedor;}
		std::string getCliente()const	{return cliente;}
		double getValor()const			{return valor;}
		int getId()const				{return id;}

		bool operator< (obj_dadosComodato a)const	{return data < a.data || (data == a.data && hora < a.hora);}
		bool operator==(obj_dadosComodato a)const	{return data == a.data && hora == a.hora;}
		bool operator!=(obj_dadosComodato a)const	{return data != a.data && hora != a.hora;}
};

#endif // OBJ_DADOSCOMODATO_H
