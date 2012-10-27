#include "mainwidget.h"

namespace gis
{

MainWidget::MainWidget( QWidget* parent) :
		QMainWindow( parent)
{
	mapWidget = new GisMapWidget( this);

	QString filename = "/home/smartnlg/workspace/dena/maps/Voronezh/m3709.map";
//	filename = QFileDialog::getOpenFileName( this, tr( "Открытие файла карты"), "", tr( "Файл карты (*.map)"));

	if( filename.isEmpty()) return;
	mapWidget->MapOpen( filename, true);

	setCentralWidget( mapWidget);
	showMaximized();
}

void MainWidget::MenuMapOpenSlot()
{
}

void MainWidget::closeEvent( QCloseEvent * e)
{
	QWidget::closeEvent( e);
}

} /* namespace gis */
