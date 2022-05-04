#ifndef FM_ROUPANOVAVENDA_PESQUISAR_H
#define FM_ROUPANOVAVENDA_PESQUISAR_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>
#include <gl_ed.h>

namespace Ui {class fm_roupaNovaVenda_pesquisar;}

class fm_roupaNovaVenda_pesquisar : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_roupaNovaVenda_pesquisar *ui;

	public:
		explicit fm_roupaNovaVenda_pesquisar(QWidget *parent = nullptr);
		~fm_roupaNovaVenda_pesquisar();
		void carregarTW(std::set<obj_roupa>const *ed);

	private slots:
		void on_btnEditar_clicked();
		void on_btnExcluir_clicked();
		void on_btnFiltro_clicked();
		void on_lineFiltro_textEdited(const QString &arg1);
		void on_tw_itemSelectionChanged();
};

#endif // FM_ROUPANOVAVENDA_PESQUISAR_H
