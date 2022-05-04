#ifndef FM_NOVAVENDA_H
#define FM_NOVAVENDA_H

#include <map>

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>
#include <gl_ed.h>

#include <fm_novavenda_editar.h>
#include <fm_novavenda_pesquisar.h>
#include <fm_novavenda_finalizar.h>

namespace Ui {class fm_novaVenda;}

class fm_novaVenda : public QDialog
{
	Q_OBJECT
	private:		// Variaveis
		Ui::fm_novaVenda *ui;
		std::map<std::string, std::pair<int, double>> vendas;
		std::map<std::string, std::pair<int, double>> vendasDesconto;
		int qtdProdutos;

	public:			// Funcoes
		~fm_novaVenda();
		explicit fm_novaVenda(QWidget *parent = nullptr);
		void atualizaPreco(bool desconto);
		double atualizaTw();

	private slots:	// Funcoes
		void on_line_codProd_returnPressed();
		void on_btn_pesquisar_clicked();
		void on_btn_excluir_clicked();
		void on_btn_editar_clicked();
		void on_btn_concluir_clicked();
};

#endif // FM_NOVAVENDA_H
