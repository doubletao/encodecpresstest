#include "QtEncodecPlayer.h"
#include <QtWidgets/QApplication>
#include <QTRanslator>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//º”‘ÿ∑≠“Î
	QTranslator *translator = new QTranslator(&a);
	QString strTransFilePath = a.applicationDirPath().append("/translate/");
	if (translator->load("zh.qm", strTransFilePath))
	{
		a.installTranslator(translator);
	}

	//º”‘ÿ∆§∑Ù
	QString strSkinPath = a.applicationDirPath().append("/usedefineskin.qss");
	QFile qss(strSkinPath);
	qss.open(QFile::ReadOnly);
	a.setStyleSheet(qss.readAll());
	qss.close();

	QtEncodecPlayer w;
	w.show();
	return a.exec();
}
