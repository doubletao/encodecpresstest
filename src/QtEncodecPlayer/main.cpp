#include "QtEncodecPlayer.h"
#include <QtWidgets/QApplication>
#include <QTRanslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	//¼ÓÔØ·­Òë
	QTranslator *translator = new QTranslator;
	QString strTransFilePath = a.applicationDirPath().append("/translate/");
	if (translator->load("zh.qm", strTransFilePath))
	{
		a.installTranslator(translator);
	}

	QtEncodecPlayer w;
	w.show();
	return a.exec();
}
