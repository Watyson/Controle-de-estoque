#ifndef OBJ_ROUPA_H
#define OBJ_ROUPA_H

#include<string>

class obj_roupa
{
	private:
		std::string id;
		std::string roupa;
		int qtd;
		double vlrCompra;
		double vlrVenda;

	public:
		obj_roupa(std::string id="", std::string roupa="", int qtd=-1, double compra=-1, double venda=-1);

		void setRoupa(const std::string &value);
		void setQtd(int value);
		void setVlrVenda(double value);
		void setVlrCompra(double value);
		void setId(const std::string &value);

		double getVlrCompra() const;
		double getVlrVenda() const;
		std::string getRoupa() const;
		int getQtd() const;
		std::string getId() const;

		bool operator< (obj_roupa b) const	{return id < b.id;}
		bool operator==(obj_roupa b) const	{return id == b.id && roupa == b.roupa;}
		bool operator!=(obj_roupa b) const	{return id != b.id || roupa != b.roupa;}
};

#endif // OBJ_ROUPA_H
