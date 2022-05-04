#ifndef FM_NOVAVENDA_BRINDE_H
#define FM_NOVAVENDA_BRINDE_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_novaVenda_brinde;}

class fm_novaVenda_brinde : public QDialog
{
	Q_OBJECT
	public:
		explicit fm_novaVenda_brinde(QWidget *parent = nullptr);
		~fm_novaVenda_brinde();
		void carregarTWGestao(std::set<obj_brinde>const *ed);

	private slots:
		void on_lineFiltro_textEdited(const QString &arg1);
		void on_btnFiltro_clicked();
		void on_tw_itemSelectionChanged();
		void on_lineQtd_textEdited(const QString &arg1);
		void on_btnEditar_clicked();

	private:
		Ui::fm_novaVenda_brinde *ui;
};

#endif // FM_NOVAVENDA_BRINDE_H
