#ifndef FM_GESTAO_ROUPA_H
#define FM_GESTAO_ROUPA_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_gestao_roupa;}

class fm_gestao_roupa : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_gestao_roupa *ui;

	public:
		explicit fm_gestao_roupa(QWidget *parent = nullptr);
		~fm_gestao_roupa();
		void carregarTWGestao(std::set<obj_roupa>const *ed);

	private slots:
		void on_btnNovoGravar_clicked();
		void on_lineNovoRoupa_textEdited(const QString &arg1);
		void on_lineNovoCodBarras_textEdited(const QString &arg1);
		void on_btnGestaoEditar_clicked();
		void on_btnGestaoExcluir_clicked();
		void on_btnGestaoFiltro_clicked();
		void on_lineGestaoFiltro_textEdited(const QString &arg1);
		void on_twGestao_itemSelectionChanged();
		void on_lineGestaoCodBarras_textEdited(const QString &arg1);
		void on_lineGestaoRoupa_textEdited(const QString &arg1);
		void on_btnDesconto_clicked();
		void on_lineGestaoFiltro_returnPressed();
};

#endif // FM_GESTAO_ROUPA_H
