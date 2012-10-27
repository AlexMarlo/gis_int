#include "mainwidget.h"

namespace gis
{

MainWidget::MainWidget( QWidget* parent) :
		QMainWindow( parent)
{
	state = AGSNone;
	oldState = AGSNone;

	MenuMapOpenSlot();

	mapWidget = new GisMapWidget( mapData, this);
	setCentralWidget( mapWidget);

	showMaximized();
}

void MainWidget::MenuMapOpenSlot()
{
	QString filename = "/home/smartnlg/workspace/dena/maps/Voronezh/m3709.map";
//	filename = QFileDialog::getOpenFileName( this, tr( "Открытие файла карты"), "", tr( "Файл карты (*.map)"));

	if( filename.isEmpty()) return;

	HMAP hmap = mapOpenMap( filename.toStdString().c_str());
	if( hmap == 0) return;
	mapData.agmap.init( hmap);
	mapData.agmap.Print();

	mapSetBackColor( mapData.agmap.hmap, 0xFAFAFA);

	return;
}

void MainWidget::closeEvent( QCloseEvent * e)
{
	QWidget::closeEvent( e);
}

} /* namespace gis */
