#ifndef FM_DADOS_H
#define FM_DADOS_H

#include <QDialog>
#include <QMessageBox>

#include <gl_ed.h>
#include <fm_carregando.h>

namespace Ui {class fm_dados;}

class fm_dados : public QDialog
{
	Q_OBJECT
	private:
		Ui::fm_dados *ui;

	public:
		explicit fm_dados(QWidget *parent = nullptr);
		~fm_dados();
		void roupa();
		void esmalte();

	private slots:
		void on_btnCarregar_clicked();
};

#endif // FM_DADOS_H
