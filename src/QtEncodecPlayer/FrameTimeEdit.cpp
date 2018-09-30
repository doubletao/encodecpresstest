#include "FrameTimeEdit.h"
#include <QDebug>
#include <QEvent>

FrameTimeEdit::FrameTimeEdit(QWidget *parent/* = nullptr*/)
	: QDateTimeEdit(parent)
{
	//设定日期范围是2000年到2024年，取年份的后两位当作帧
	setDateRange(QDate(2000, 12, 31), QDate(2024, 12, 31));
}

FrameTimeEdit::~FrameTimeEdit()
{
}
