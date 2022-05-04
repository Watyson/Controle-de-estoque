#ifndef FM_NOVAVENDA_PESQUISAR_H
#define FM_NOVAVENDA_PESQUISAR_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>
#include <gl_ed.h>

namespace Ui {class fm_novaVenda_pesquisar;}

class fm_novaVenda_pesquisar : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_novaVenda_pesquisar *ui;

	public:
		explicit fm_novaVenda_pesquisar(QWidget *parent = nullptr);
		~fm_novaVenda_pesquisar();
		void carregarTWGestao(std::set<obj_esmalte>const *ed);

	private slots:
		void on_lineFiltro_textEdited(const QString &arg1);
		void on_btnFiltro_clicked();
		void on_twGestao_itemSelectionChanged();
		void on_btnCancelar_clicked();
		void on_btnConfirmar_clicked();
};

#endif // FM_NOVAVENDA_PESQUISAR_H
