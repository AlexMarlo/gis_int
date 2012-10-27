#include <iostream>

#include <qapplication.h>
#include <qwindowsstyle.h>
#include <QTranslator>
#include <QTextCodec>

#include "fmain.h"

int main( int argc, char ** argv)
{
	int ret;

	QApplication* application = new QApplication( argc, argv);
	application->setStyle( new QWindowsStyle);

	QTextCodec::setCodecForLocale( QTextCodec::codecForName( "UTF-8"));
	QTextCodec::setCodecForTr( QTextCodec::codecForName( "UTF-8"));
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "UTF-8"));

	MainWindow* mainWindow = new MainWindow();
	application->setActiveWindow( mainWindow);
	mainWindow->show();
	ret = application->exec();


	delete mainWindow;
	delete application;

	return ( ret);
}

