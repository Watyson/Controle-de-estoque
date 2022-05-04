#ifndef FM_CARREGANDO_H
#define FM_CARREGANDO_H

#include <QDialog>

namespace Ui {
	class fm_carregando;
}

class fm_carregando : public QDialog
{
		Q_OBJECT

	public:
		explicit fm_carregando(QWidget *parent = nullptr);
		~fm_carregando();

	private:
		Ui::fm_carregando *ui;
};

#endif // FM_CARREGANDO_H
