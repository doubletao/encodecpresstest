#include "QtEncodecPlayer.h"

QtEncodecPlayer::QtEncodecPlayer(QWidget *parent)
	: QDialog(parent)
{
	resize(1440, 900);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint;
	setWindowFlags(flags);
}
