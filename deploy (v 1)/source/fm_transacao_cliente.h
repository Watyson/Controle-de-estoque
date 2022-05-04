#ifndef FM_TRANSACAO_CLIENTE_H
#define FM_TRANSACAO_CLIENTE_H

#include <QDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QDesktopServices>
#include <QFileDialog>

#include <gl_variavel.h>
#include <gl_ed.h>

namespace Ui {class fm_transacao_cliente;}

class fm_transacao_cliente : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_transacao_cliente *ui;

	public:
		explicit fm_transacao_cliente(QWidget *parent = nullptr);
		~fm_transacao_cliente();
		void carregarTWCliente(std::set<obj_dadosVendedor>const *ed);
		void carregarTWVendas(std::set<obj_dadosEsmalte>const *ed);

	private slots:
		void on_twCliente_itemSelectionChanged();
		void on_lineCliente_textEdited(const QString &arg1);
		void on_btnMostrarTudo_clicked();
		void on_dateInicial_userDateChanged();
		void on_dateFinal_userDateChanged();
		void on_btnRelatorio_clicked();
		void on_rbEsmalte_clicked();
		void on_rbRoupa_clicked();
};

#endif // FM_TRANSACAO_CLIENTE_H
