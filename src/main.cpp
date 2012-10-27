#include <iostream>

#include <qapplication.h>
#include <qwindowsstyle.h>
#include <QTranslator>
#include <QTextCodec>

#include "gismapstructs.h"
#include "mainwidget.h"

int main( int argc, char ** argv)
{
	int ret;

	QApplication* application = new QApplication( argc, argv);
	application->setStyle( new QWindowsStyle);

	QTextCodec::setCodecForLocale( QTextCodec::codecForName( "UTF-8"));
	QTextCodec::setCodecForTr( QTextCodec::codecForName( "UTF-8"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "UTF-8"));

	gis::MainWidget* mainWindow = new gis::MainWidget();
	application->setActiveWindow( mainWindow);
	mainWindow->show();
	ret = application->exec();

	delete mainWindow;
	delete application;

	return ( ret);
}
