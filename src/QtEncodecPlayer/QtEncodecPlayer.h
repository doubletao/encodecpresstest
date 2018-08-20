#pragma once

#include <QtWidgets/QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

class QtEncodecPlayer : public QDialog
{
	Q_OBJECT
public:
	QtEncodecPlayer(QWidget *parent = Q_NULLPTR);
	~QtEncodecPlayer();
protected:
	//整体上布局为垂直layout，上部是个水平layout，中部一根时间轴，下部又一个水平layout
};
