#pragma once
#include <QTimeEdit>
#include <set>

class FrameTimeEdit : public QTimeEdit
{
private:
	std::set<int> m_setEventType;
public:
	FrameTimeEdit(QWidget *parent = nullptr);
	virtual ~FrameTimeEdit();
	virtual bool event(QEvent *event) override;
};
