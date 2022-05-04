#ifndef FM_GESTAO_BRINDE_H
#define FM_GESTAO_BRINDE_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_gestao_brinde;}

class fm_gestao_brinde : public QDialog
{
	Q_OBJECT
	public:
		explicit fm_gestao_brinde(QWidget *parent = nullptr);
		~fm_gestao_brinde();
		void carregarTWGestao(std::set<obj_brinde>const *ed);

	private slots:
		void on_lineNovoNome_textEdited(const QString &arg1);
		void on_btnNovoGravar_clicked();
		void on_lineGestaoFiltro_textEdited(const QString &arg1);
		void on_btnGestaoFiltro_clicked();
		void on_twGestao_itemSelectionChanged();
		void on_lineGestaoNome_textEdited(const QString &arg1);
		void on_btnGestaoEditar_clicked();
		void on_btnGestaoExcluir_clicked();
		void on_btnGestaoVerVendas_clicked();

	private:
		Ui::fm_gestao_brinde *ui;
};

#endif // FM_GESTAO_BRINDE_H
