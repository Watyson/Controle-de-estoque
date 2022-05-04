#ifndef FM_ROUPANOVAVENDA_EDITAR_H
#define FM_ROUPANOVAVENDA_EDITAR_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>

namespace Ui {class fm_roupaNovaVenda_editar;}

class fm_roupaNovaVenda_editar : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_roupaNovaVenda_editar *ui;

	public:
		explicit fm_roupaNovaVenda_editar(QWidget *parent = nullptr);
		~fm_roupaNovaVenda_editar();

	private slots:
		void on_btn_ok_clicked();
		void on_btn_cancel_clicked();
};

#endif // FM_ROUPANOVAVENDA_EDITAR_H
