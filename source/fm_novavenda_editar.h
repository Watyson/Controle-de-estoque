#ifndef FM_NOVAVENDA_EDITAR_H
#define FM_NOVAVENDA_EDITAR_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>

namespace Ui {class fm_novaVenda_editar;}

class fm_novaVenda_editar : public QDialog
{
	Q_OBJECT
	private:		// Variaveis
		Ui::fm_novaVenda_editar *ui;

	public:			// Funcoes
		~fm_novaVenda_editar();
		explicit fm_novaVenda_editar(QWidget *parent = nullptr);

	private slots:
		void on_btn_ok_clicked();
		void on_btn_cancel_clicked();
};

#endif // FM_NOVAVENDA_EDITAR_H
