#ifndef FM_NOVAVENDA_FINALIZAR_H
#define FM_NOVAVENDA_FINALIZAR_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>
#include <gl_ed.h>

#include <fm_novavenda_brinde.h>
#include <fm_novavenda_cadastrocliente.h>

namespace Ui {class fm_novaVenda_finalizar;}

class fm_novaVenda_finalizar : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_novaVenda_finalizar *ui;

	public:
		explicit fm_novaVenda_finalizar(QWidget *parent = nullptr);
		~fm_novaVenda_finalizar();
		void carregarTW(std::set<obj_cliente>const *ed);

	private slots:
		void on_btnSelecionar_clicked();
		void on_btnFiltro_2_clicked();
		void on_twGestao_itemSelectionChanged();
		void on_lineFiltro_2_textEdited(const QString &arg1);
		void on_btnCadastrar_clicked();
		void on_btnBrinde_clicked();
};

#endif // FM_NOVAVENDA_FINALIZAR_H
