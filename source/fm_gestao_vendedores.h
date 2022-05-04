#ifndef FM_GESTAO_VENDEDORES_H
#define FM_GESTAO_VENDEDORES_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_gestao_vendedores;}

class fm_gestao_vendedores : public QDialog
{
	Q_OBJECT
	private:		// Variaveis
		Ui::fm_gestao_vendedores *ui;

	private slots:	// Funcoes
		void on_lineNovoUser_textEdited(const QString &arg1);
		void on_rbNovoSenha_clicked(bool checked);
		void on_btnNovoGravar_clicked();
		void on_twGestao_itemSelectionChanged();
		void on_btnGestaoFiltro_clicked();
		void on_lineGestaoFiltro_textEdited(const QString &arg1);
		void on_lineGestaoUser_textEdited(const QString &arg1);
		void on_btnGestaoExcluir_clicked();
		void on_btnGestaoEditar_clicked();
		void on_radioButton_clicked(bool checked);

	public:			// Funcoes
		~fm_gestao_vendedores();
		void carregarTWGestao(std::set<obj_vendedor>const *ed);
		explicit fm_gestao_vendedores(QWidget *parent = nullptr);
};

#endif // FM_GESTAO_VENDEDORES_H
