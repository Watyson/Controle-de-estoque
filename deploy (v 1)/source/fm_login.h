#ifndef FM_LOGIN_H
#define FM_LOGIN_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>

namespace Ui {class fm_login;}

class fm_login : public QDialog
{
	Q_OBJECT
	private:		// Variaveis
		Ui::fm_login *ui;

	private slots:	// Funcoes
		void on_btn_logar_clicked();
		void on_btn_cancel_clicked();
		void on_cbMostrarSenha_stateChanged(int arg1);

	public:			// Funcoes
		~fm_login();
		explicit fm_login(QWidget *parent = nullptr);
};

#endif // FM_LOGIN_H
