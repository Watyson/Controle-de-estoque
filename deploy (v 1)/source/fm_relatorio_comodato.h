#ifndef FM_RELATORIO_COMODATO_H
#define FM_RELATORIO_COMODATO_H

#include <QDialog>
#include <QMessageBox>

#include <gl_variavel.h>
#include <bd_relatorios.h>

namespace Ui {class fm_relatorio_comodato;}

class fm_relatorio_comodato : public QDialog
{
	Q_OBJECT
	public:
		explicit fm_relatorio_comodato(QWidget *parent = nullptr);
		~fm_relatorio_comodato();
		void carregarTWGestao(std::set<obj_dadosComodato>const *ed);

	private slots:
		void on_btnStatus_clicked();
		void on_tw_itemSelectionChanged();
		void on_btnFiltro_clicked();
		void on_lineFiltro_textEdited(const QString &arg1);
		void on_rbPendente_clicked();
		void on_rbPago_clicked();

	private:
		Ui::fm_relatorio_comodato *ui;
		bd_relatorios relatorio;
};

#endif // FM_RELATORIO_COMODATO_H
