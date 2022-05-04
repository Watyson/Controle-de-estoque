#ifndef FM_GESTAO_CLIENTES_H
#define FM_GESTAO_CLIENTES_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_gestao_clientes;}

class fm_gestao_clientes : public QDialog
{
	Q_OBJECT
	private:		// Variaveis
		Ui::fm_gestao_clientes *ui;
		std::string cnpj;
		std::string cpf;

	private slots:	// Funcoes
		void on_btnNovoGravar_clicked();
		void on_btnGestaoEditar_clicked();
		void on_btnGestaoExcluir_clicked();
		void on_btnGestaoFiltro_clicked();
		void on_lineGestaoFiltro_textEdited(const QString &arg1);
		void on_twGestao_itemSelectionChanged();
		void on_lineNovoCnpj_textEdited(const QString &arg1);
		void on_lineGestaoCnpj_textEdited(const QString &arg1);

		void on_lineNovoCpf_textEdited(const QString &arg1);

		void on_lineGestaoCpf_textEdited(const QString &arg1);

	public:			// Funcoes
		~fm_gestao_clientes();
		void carregarTWGestao(std::set<obj_cliente>const *ed);
		explicit fm_gestao_clientes(QWidget *parent = nullptr);
};

#endif // FM_GESTAO_CLIENTES_H
