#ifndef FM_MENU_H
#define FM_MENU_H

#include <QMainWindow>
#include <QMessageBox>
#include <QIcon>

#include <gl_variavel.h>

#include <fm_gestao_vendedores.h>
#include <fm_gestao_clientes.h>
#include <fm_gestao_esmalte.h>
#include <fm_gestao_brinde.h>
#include <fm_gestao_roupa.h>
#include <fm_login.h>
#include <fm_novavenda.h>
#include <fm_roupaNovaVenda.h>
#include <fm_relatorio_comodato.h>
#include <fm_estoque_esmalte.h>
#include <fm_estoque_roupa.h>
#include <fm_transacao_vendedor.h>
#include <fm_transacao_cliente.h>
#include <fm_dados.h>

namespace Ui {class fm_menu;}

class fm_menu : public QMainWindow
{
	Q_OBJECT
	private:		// Variaveis
		Ui::fm_menu *ui;

		QIcon cadAberto;
		QIcon cadFechado;

	private slots:	// Funcoes
		void on_actionGestao_triggered();
		void on_actionGestao_2_triggered();
		void on_actionEsmalte_triggered();
		void on_btn_login_clicked();
		void on_btn_novaVenda_clicked();
		void on_actionSobre_triggered();
		void on_btn_comodato_clicked();
		void on_btn_estoque_clicked();
		void on_actionBrinde_triggered();
		void on_actionSair_triggered();
		void on_actionTransaoes_triggered();
		void on_actionTransaoes_2_triggered();
		void on_actionRoupa_triggered();

		void on_actionDados_triggered();

	public:			// Funcoes
		~fm_menu();
		explicit fm_menu(QWidget *parent = nullptr);
		void acesso();
};

#endif // FM_MENU_H
