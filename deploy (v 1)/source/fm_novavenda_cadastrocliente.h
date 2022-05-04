#ifndef FM_NOVAVENDA_CADASTROCLIENTE_H
#define FM_NOVAVENDA_CADASTROCLIENTE_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>

#include <gl_variavel.h>
#include <gl_funcao.h>

#include <gl_ed.h>

namespace Ui {class fm_novaVenda_cadastroCliente;}

class fm_novaVenda_cadastroCliente : public QDialog
{
		Q_OBJECT

	public:
		explicit fm_novaVenda_cadastroCliente(QWidget *parent = nullptr);
		~fm_novaVenda_cadastroCliente();

	private slots:
		void on_btnGravar_clicked();
		void on_lineCnpj_textEdited(const QString &arg1);
		void on_lineCpf_textEdited(const QString &arg1);

	private:
		Ui::fm_novaVenda_cadastroCliente *ui;
};

#endif // FM_NOVAVENDA_CADASTROCLIENTE_H
