#ifndef FM_TRANSACAO_VENDEDOR_H
#define FM_TRANSACAO_VENDEDOR_H

#include <QDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QDesktopServices>
#include <QFileDialog>

#include <gl_variavel.h>
#include <gl_ed.h>

namespace Ui {class fm_transacao_vendedor;}

class fm_transacao_vendedor : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_transacao_vendedor *ui;

	public:
		explicit fm_transacao_vendedor(QWidget *parent = nullptr);
		~fm_transacao_vendedor();
		void carregarTWVendedor(std::set<obj_dadosVendedor>const *ed);
		void carregarTWVendas(std::set<obj_dadosEsmalte>const *ed);

	private slots:
		void on_twVendedor_itemSelectionChanged();
		void on_lineVendedor_textEdited(const QString &arg1);
		void on_pushButton_2_clicked();
		void on_dateInicial_userDateChanged();
		void on_dateFinal_userDateChanged();
		void on_btnRelatorio_clicked();
		void on_rbEsmalte_clicked();
		void on_rbRoupa_clicked();
};

#endif // FM_TRANSACAO_VENDEDOR_H
