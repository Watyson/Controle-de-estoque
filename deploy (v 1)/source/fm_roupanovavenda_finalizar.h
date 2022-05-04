#ifndef FM_ROUPANOVAVENDA_FINALIZAR_H
#define FM_ROUPANOVAVENDA_FINALIZAR_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>
#include <gl_ed.h>

#include <fm_novavenda_brinde.h>
#include <fm_novavenda_cadastrocliente.h>

namespace Ui {class fm_roupaNovaVenda_finalizar;}

class fm_roupaNovaVenda_finalizar : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_roupaNovaVenda_finalizar *ui;

	public:
		explicit fm_roupaNovaVenda_finalizar(QWidget *parent = nullptr);
		~fm_roupaNovaVenda_finalizar();
		void carregarTW(std::set<obj_cliente>const *ed);
	private slots:
		void on_btnSelecionar_clicked();
		void on_btnFiltro_clicked();
		void on_lineFiltro_textEdited(const QString &arg1);
		void on_btnCadastrar_clicked();
		void on_tw_itemSelectionChanged();
		void on_cbTipoPgmt_currentIndexChanged(const QString &arg1);
};

#endif // FM_ROUPANOVAVENDA_FINALIZAR_H




