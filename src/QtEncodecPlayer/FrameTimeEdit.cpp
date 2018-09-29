#include "FrameTimeEdit.h"
#include <QDebug>
#include <QEvent>

FrameTimeEdit::FrameTimeEdit(QWidget *parent/* = nullptr*/)
	: QTimeEdit(parent)
{
}

FrameTimeEdit::~FrameTimeEdit()
{
}

bool FrameTimeEdit::event(QEvent * event)
{
	if (event->type() == QEvent::InputMethodQuery)
	{
		//对于input动作，动态调整一下值
		QTime tmCurent = time();
		qDebug() << tmCurent.msec();
		if (tmCurent.msec() > 24)
		{
			tmCurent.setHMS(tmCurent.hour(), tmCurent.minute(), tmCurent.second(), 24);
			setTime(tmCurent);
		}
	}
	return QTimeEdit::event(event);
}
