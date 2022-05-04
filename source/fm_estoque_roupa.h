#ifndef FM_ESTOQUE_ROUPA_H
#define FM_ESTOQUE_ROUPA_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_estoque_roupa;}

class fm_estoque_roupa : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_estoque_roupa *ui;

	public:
		explicit fm_estoque_roupa(QWidget *parent = nullptr);
		~fm_estoque_roupa();
		void carregarTWGestao(std::set<obj_roupa>const *ed);

	private slots:
		void on_btnAtualizar_clicked();
		void on_btnFiltro_clicked();
		void on_lineFiltro_textEdited(const QString &arg1);
		void on_tw_itemSelectionChanged();
		void on_lineFiltro_returnPressed();
};

#endif // FM_ESTOQUE_ROUPA_H
