#pragma once
#include <QTimeEdit>
#include <set>

class FrameTimeEdit : public QDateTimeEdit
{
public:
	FrameTimeEdit(QWidget *parent = nullptr);
	virtual ~FrameTimeEdit();
};
