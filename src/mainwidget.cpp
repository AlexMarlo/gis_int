#include "mainwidget.h"

namespace gis
{

MainWindow::MainWindow( QWidget* parent) :
		QMainWindow( parent)
{
	state = AGSNone;
	oldState = AGSNone;

	crZoomIn = new QCursor( QBitmap( 32, 32), QBitmap( 32, 32), 6, 6);
	crZoomOut = new QCursor( QBitmap( 32, 32), QBitmap( 32, 32), 6, 6);

	MenuMapOpenSlot();

	mapWidget = new MapWidget( mapData, this);
	setCentralWidget( mapWidget);

	showMaximized();
}

void MainWindow::LVVFCurrentChangedSlot( QListViewItem* I)
{
}

void MainWindow::LVVFExpandedSlot( QListViewItem* I)
{
}

void MainWindow::fillLVVF()
{
}

void MainWindow::fillLVVF( QListViewItem* I,
		std::vector< std::pair< int, int> >&chi, bool fill)
{
}

void MainWindow::CreateMenus()
{

}

void MainWindow::CreateTools()
{
}

void MainWindow::MenuMapExitSlot()
{
	close();
}

void MainWindow::MenuMapOpenSlot()
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

void MainWindow::MenuMapPOpenSlot()
{
}

void MainWindow::MenuMapCloseSlot()
{
}

void MainWindow::MenuMapPCloseSlot()
{
}

void MainWindow::MenuModeSelectSlot()
{
	setState( AGSSelect);
}

void MainWindow::MenuModeZoomSlot()
{
	setState( AGSZoomIn);
}

void MainWindow::zoomInSlot()
{
	setState( AGSZoomIn);
}

void MainWindow::zoomOutSlot()
{
	setState( AGSZoomOut);
}

void MainWindow::checkState()
{
}
void MainWindow::MenuViewViewSlot()
{
}

void MainWindow::CreateStatus()
{
}

void MainWindow::viewCoords( double x, double y)
{
}

void MainWindow::viewScale( double sc)
{
}

void MainWindow::MenuObjCurrentSlot()
{
}

void MainWindow::MenuObjNewSlot()
{
}

void MainWindow::MenuObjMetSlot()
{
}

void MainWindow::MenuObjDelSlot()
{
}

void MainWindow::MenuObjUnselectSlot()
{
}

void MainWindow::repaintMap()
{
}

void MainWindow::qqq()
{
}

void MainWindow::ButCreateClickedSlot()
{
}

void MainWindow::closeEvent( QCloseEvent * e)
{
	QWidget::closeEvent( e);
}

void MainWindow::ButShowClickedSlot()
{
}

} /* namespace gis */
