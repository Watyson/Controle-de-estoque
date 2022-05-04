#ifndef FM_ROUPANOVAVENDA_H
#define FM_ROUPANOVAVENDA_H

#include <map>

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>
#include <gl_ed.h>

#include <fm_roupanovavenda_editar.h>
#include <fm_roupanovavenda_pesquisar.h>
#include <fm_roupanovavenda_finalizar.h>

namespace Ui {class fm_roupaNovaVenda;}

class fm_roupaNovaVenda : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_roupaNovaVenda *ui;
		std::map<std::string, std::pair<int, double>> vendas;

	public:
		explicit fm_roupaNovaVenda(QWidget *parent = nullptr);
		~fm_roupaNovaVenda();
		double atualizaTw();

	private slots:
		void on_line_codProd_returnPressed();
		void on_btn_pesquisar_clicked();
		void on_btn_excluir_clicked();
		void on_btn_editar_clicked();
		void on_btn_concluir_clicked();
};

#endif // FM_ROUPANOVAVENDA_H
