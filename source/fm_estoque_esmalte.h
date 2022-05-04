#ifndef FM_ESTOQUE_ESMALTE_H
#define FM_ESTOQUE_ESMALTE_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_estoque_esmalte;}

class fm_estoque_esmalte : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_estoque_esmalte *ui;

	public:
		explicit fm_estoque_esmalte(QWidget *parent = nullptr);
		~fm_estoque_esmalte();
		void carregarTWGestao(std::set<obj_esmalte>const *ed);

	private slots:
		void on_btnAtualizar_clicked();
		void on_btnFiltro_clicked();
		void on_lineFiltro_textEdited(const QString &arg1);
		void on_tw_itemSelectionChanged();
		void on_lineFiltro_returnPressed();
};

#endif // FM_ESTOQUE_ESMALTE_H
