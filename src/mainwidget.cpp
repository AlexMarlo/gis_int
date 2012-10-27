#include "mainwidget.h"

namespace gis
{

MainWidget::MainWidget( QWidget* parent) :
		QMainWindow( parent)
{
	state = AGSNone;
	oldState = AGSNone;

	crZoomIn = new QCursor( QBitmap( 32, 32), QBitmap( 32, 32), 6, 6);
	crZoomOut = new QCursor( QBitmap( 32, 32), QBitmap( 32, 32), 6, 6);

	MenuMapOpenSlot();

	mapWidget = new GisMapWidget( mapData, this);
	setCentralWidget( mapWidget);

	showMaximized();
}

void MainWidget::LVVFCurrentChangedSlot( QListViewItem* I)
{
}

void MainWidget::LVVFExpandedSlot( QListViewItem* I)
{
}

void MainWidget::fillLVVF()
{
}

void MainWidget::fillLVVF( QListViewItem* I,
		std::vector< std::pair< int, int> >&chi, bool fill)
{
}

void MainWidget::CreateMenus()
{

}

void MainWidget::CreateTools()
{
}

void MainWidget::MenuMapExitSlot()
{
	close();
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

void MainWidget::MenuMapPOpenSlot()
{
}

void MainWidget::MenuMapCloseSlot()
{
}

void MainWidget::MenuMapPCloseSlot()
{
}

void MainWidget::MenuModeSelectSlot()
{
	setState( AGSSelect);
}

void MainWidget::MenuModeZoomSlot()
{
	setState( AGSZoomIn);
}

void MainWidget::zoomInSlot()
{
	setState( AGSZoomIn);
}

void MainWidget::zoomOutSlot()
{
	setState( AGSZoomOut);
}

void MainWidget::checkState()
{
}
void MainWidget::MenuViewViewSlot()
{
}

void MainWidget::CreateStatus()
{
}

void MainWidget::viewCoords( double x, double y)
{
}

void MainWidget::viewScale( double sc)
{
}

void MainWidget::MenuObjCurrentSlot()
{
}

void MainWidget::MenuObjNewSlot()
{
}

void MainWidget::MenuObjMetSlot()
{
}

void MainWidget::MenuObjDelSlot()
{
}

void MainWidget::MenuObjUnselectSlot()
{
}

void MainWidget::repaintMap()
{
}

void MainWidget::qqq()
{
}

void MainWidget::ButCreateClickedSlot()
{
}

void MainWidget::closeEvent( QCloseEvent * e)
{
	QWidget::closeEvent( e);
}

void MainWidget::ButShowClickedSlot()
{
}

} /* namespace gis */
