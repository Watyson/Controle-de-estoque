#ifndef FM_GESTAO_ESMALTE_H
#define FM_GESTAO_ESMALTE_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_gestao_esmalte;}

class fm_gestao_esmalte : public QDialog
{
	Q_OBJECT
	private:		// Variaveis
		Ui::fm_gestao_esmalte *ui;

	public:			//Funcoes
		~fm_gestao_esmalte();
		void carregarTWGestao(std::set<obj_esmalte>const *ed);
		explicit fm_gestao_esmalte(QWidget *parent = nullptr);

	private slots:	// Funcoes
		void on_btnNovoGravar_clicked();
		void on_lineNovoCodBarras_textEdited(const QString &arg1);
		void on_lineNovoCor_textEdited(const QString &arg1);

		void on_btnGestaoEditar_clicked();
		void on_btnGestaoExcluir_clicked();
		void on_btnGestaoFiltro_clicked();
		void on_lineGestaoFiltro_textEdited(const QString &arg1);

		void on_twGestao_itemSelectionChanged();
		void on_lineGestaoCodBarras_textEdited(const QString &arg1);
		void on_lineGestaoCor_textEdited(const QString &arg1);
		void on_btnDesconto_clicked();
		void on_lineGestaoFiltro_returnPressed();
};

#endif // FM_GESTAO_ESMALTE_H
