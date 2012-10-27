#include <qapplication.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qbitmap.h>
#include <qstatusbar.h>
#include <qlabel.h>
#include <qworkspace.h>
#include <qtoolbar.h>
#include <qsplitter.h>
#include <qpushbutton.h>
#include <QMouseEvent>
#include <QScrollBar>
#include <QListView>
#include <QAction>
#include <QtGui>
#include <QCursor>
#include <QX11Info>
#include <QImage>

#include <math.h>

#include "fmain.h"
#include "fview.h"
#include "fnew.h"
#include "vars.h"
#include "dgtbtns.xpm"
#include "dgtcurs.xpm"
#include "otoubd.h"
#include <qscrollarea.h>
#include <qpainter.h>

MapData::MapData()
{
	clear();
}

void MapData::clear()
{
	agmap.clear();
	agtmpsite.clear();
	agsites.clear();
}

AGMAP::AGMAP()
{
	clear();
}
;

void AGMAP::clear()
{
	hmap = 0;
	width = 0;
	height = 0;
	path = "";
	scale = 0;
	minScale = 4000;
	maxScale = 1000000;
}

void AGMAP::init( HMAP par_hmap)
{
	char str[4096];
	hmap = par_hmap;
	mapGetPictureSize( hmap, &width, &height);
	scale = mapGetRealShowScale( hmap);
	layerCount = mapGetLayerCount( hmap);
	strcpy( str, mapGetMapPath( hmap));
	path = std::string( str);
}

void AGMAP::Print()
{
	std::cout << "AGMAP:" << std::endl;
	std::cout << "hmap       = " << hmap << std::endl;
	std::cout << "width      = " << width;
	std::cout << "height     = " << height << std::endl;
	std::cout << "path       = '" << path << "'" << std::endl;
	std::cout << "scale      = " << scale << std::endl;
	std::cout << "minScale   = " << minScale << std::endl;
	std::cout << "maxScale   = " << maxScale << std::endl;
	std::cout << "bright     = " << bright << std::endl;
	std::cout << "contrast   = " << contrast << std::endl;
	std::cout << "layerCount = " << layerCount << std::endl;
}

AGSITE::AGSITE()
{
	clear();
}

void AGSITE::clear()
{
	hsite = 0;
	path = "";
	memset( &cs, 0, sizeof(CREATESITE));

	hrsc = 0;
	rscPath = "";
}

void AGSITE::init( AGMAP par_agmap, HSITE par_hsite)
{
	char str[4096];

	agmap = par_agmap;
	hsite = par_hsite;
	strcpy( str, mapGetSiteFileName( agmap.hmap, hsite));
	path = std::string( str);
	hrsc = mapGetRscIdent( agmap.hmap, hsite);
	mapGetRscFileName( hrsc, str, 4096);
	rscPath = std::string( str);
	layerCount = mapGetSiteLayerCount( agmap.hmap, hsite);
}

void AGSITE::Print()
{
	std::cout << "AGSITE:" << std::endl;
	agmap.Print();
	std::cout << "hsite      = " << hsite << std::endl;
	std::cout << "hrsc       = " << hrsc << std::endl;
	std::cout << "path       = '" << path << "'" << std::endl;
	std::cout << "rscPath    = '" << rscPath << "'" << std::endl;
	std::cout << "layerCount = " << layerCount << std::endl;
}

MapWidget::MapWidget( MapData mapData, QWidget *parent) :
		QWidget( parent),
		mapData_( mapData),
		imageBits_( 0),
		imageWidth_( 0),
		imageHeight_ ( 0),
		isNeedUpdatePixmap_ ( true)
{
	verticalScrollBar_ = new QScrollBar( Qt::Horizontal, this);
	horizontalScrollBar_ = new QScrollBar( Qt::Vertical, this);

	verticalScrollBar_->setFixedWidth( 100);
	horizontalScrollBar_->setFixedHeight( 100);

	verticalScrollBar_->setMinimum( 0);
	horizontalScrollBar_->setMinimum( 0);

	verticalScrollBar_->setMaximum( mapData_.agmap.width);
	horizontalScrollBar_->setMaximum( mapData_.agmap.height);

	connect( verticalScrollBar_, SIGNAL( valueChanged( int)), this, SLOT( scrollChanged()));
	connect( horizontalScrollBar_, SIGNAL( valueChanged( int)), this, SLOT( scrollChanged()));

	setWindowTitle( "MapWidget");
}

void MapWidget::scrollChanged()
{
	isNeedUpdatePixmap_ = true;
	repaint();
}

void MapWidget::scaleChanged()
{
	isNeedUpdatePixmap_ = true;
	repaint();
}

void MapWidget::resizeEvent( QResizeEvent* event)
{
	isNeedUpdatePixmap_ = true;
}

void MapWidget::showEvent( QShowEvent* event)
{
	isNeedUpdatePixmap_ = true;
}

void MapWidget::paintEvent( QPaintEvent* event)
{
	HMAP hMap = mapData_.agmap.hmap;
	int mapDepth = mapGetMapScreenDepth();;

	RECT rectDraw;
	int cx, cy, cw, ch;
	int bytes_per_line;

	if( hMap)
	{
		cx = verticalScrollBar_->value();
		cy = horizontalScrollBar_->value();
		cw = event->rect().width();
		ch = event->rect().height();
		bytes_per_line = cw * mapDepth / 8;

		if( isNeedUpdatePixmap_)
		{
			XIMAGEDESC Ximagedesc;
			long allignwidth = cw * mapDepth / 8;
			long size = allignwidth * ch;

			if( imageWidth_ != event->rect().width() || imageHeight_ != event->rect().height())
			{
				if( imageBits_)
					FreeTheMemory(imageBits_);

				imageBits_ = ::AllocateTheMemory( size);
				if( !imageBits_) return;
				memset( imageBits_, 0x0, size);
				imageWidth_ = event->rect().width();
				imageHeight_ = event->rect().height();
			}

			Ximagedesc.Point = imageBits_;
			Ximagedesc.Width = cw;
			Ximagedesc.Height = ch;
			Ximagedesc.Depth = mapDepth;
			Ximagedesc.CellSize = mapDepth / 8;
			Ximagedesc.RowSize = cw * Ximagedesc.CellSize;

			rectDraw.left = cx;
			rectDraw.top = cy;
			rectDraw.right = cx + cw;
			rectDraw.bottom = cy + ch;

			mapPaintToXImage( hMap, &Ximagedesc, 0, 0, &rectDraw);
			isNeedUpdatePixmap_ = false;
		}

		QImage::Format format;
		switch( mapDepth)
		{
			case 8:
				format = QImage::Format_Indexed8;
				break;
			case 16:
				format = QImage::Format_RGB16;
				break;
			case 32:
				format = QImage::Format_RGB32;
				break;
			default:
				format = QImage::Format_Invalid;
				break;
		}
		QImage image( ( uchar *)imageBits_, cw, ch, bytes_per_line, format);

		QPainter painter( this);
		painter.drawImage( QPoint( 0, 0), image);
	}
}


void MapWidget::closeMap()
{
	mapCloseMap( mapData_.agmap.hmap);
	mapData_.agmap.hmap = 0;
}

void PrintMouseEvent( QMouseEvent* e)
{
}

void MapWidget::contentsMousePressEvent( QMouseEvent * e)
{
}

void MapWidget::contentsMouseMoveEvent( QMouseEvent * e)
{
}

void MapWidget::contentsMouseReleaseEvent( QMouseEvent * e)
{
//	_DEBUG_FUNC(std::cout<<"EMap::contentsMouseReleaseEvent:"<<std::endl);
//	PrintMouseEvent( e);
//
//	if( e->button() & Qt::LeftButton)
//	{
//		switch( mainWindow->getState())
//		{
//			case AGSSelect:
//				break;
//			case AGSZoomIn:
//			case AGSZoomOut:
//
//				double kscale; // �������������� �������
//				double scalex, scaley; // ��� ���������� ��������� �� x � y
//				double x, y; // ��� ������ ����������
//
//				zoomPainter.drawRect( zoomRect); // ������� ������
//				zoomPainter.end();
//
//				// �������� �������� �����
//				x = zoomRect.x() + contentsRect().x();
//				y = zoomRect.y() + contentsRect().y();
//				x = x + zoomRect.width() / 2;
//				y = y + zoomRect.height() / 2;
//
//				if( visibleRegion().numRects() == 1)
//				{
//					scalex = ( double)visibleRegion().rects().at( 0).width()
//							/ ( double)zoomRect.width();
//					scaley = ( double)visibleRegion().rects().at( 0).height()
//							/ ( double)zoomRect.height();
//				}
//
//				if( zoomBegin)
//					kscale = MIN( scalex, scaley);
//				else
//					kscale = 1.1; // ���� ������ ������ ������ - ������� �������������
//
//				if( mainWindow->getState() == AGSZoomIn)
//				{
//					if( ( mapData.agmap.scale / kscale)
//							< mapData.agmap.minScale)
//						kscale = mapData.agmap.scale / mapData.agmap.minScale;
//				}
//
//				if( mainWindow->getState() == AGSZoomOut)
//				{
//					kscale = 1 / kscale;
//					if( ( mapData.agmap.scale / kscale)
//							> mapData.agmap.maxScale)
//						kscale = mapData.agmap.scale / mapData.agmap.maxScale;
//				}
//
//				changeScale( kscale, ( long int)x, ( long int)y);
//
//				break;
//			default:
//				break;
//		}
//	}
}

void MapWidget::changeScale( double kscale, long int xc, long int yc)
{
	long int oldMapWidth, oldMapHeight; //������ ������� �����
	//	int oldVbw, oldHbh; // ������� ���������

	// �������� ������ ��������
	//	oldVbw = verticalScrollBar()->width();
	//	oldHbh = horizontalScrollBar()->height();
	mapGetPictureSize( mapData.agmap.hmap, &oldMapWidth, &oldMapHeight);

	mapChangeViewScale( mapData.agmap.hmap, &xc, &yc, kscale); // ������ �������
	mapData.agmap.scale = mapGetRealShowScale( mapData.agmap.hmap);
	emit changeScaleSignal( mapData.agmap.scale);

	mapGetPictureSize( mapData.agmap.hmap, &mapData.agmap.width,
			&mapData.agmap.height); // ������ ����� ������

	// ��������������� ���������� ���.
	//  - ������� ������� � ����������� �� ���������� ����������
	//  - ��������� ��������� viewport
	//  - ������������ �����
	//  - ������ ������� ��������� (resizeContents)
	//  - ���������� ��������
	//  - ��������� ��������� viewport
	//  - ��������� viewport
	// ����� ���������� ��������������� � ���� -
	// ������� ��� ����������� ���. ����� ��������������� �� ������
	// �������������� ��� ������� �������.
	// � ����� �� ������������ � ����� - ������ �� ����������
	// �� �������� ���� ������ ��� ������ ����� ������������� �����
	// ������� ���������. � ���� ������ resizeContents
	// ��� ������� ������� �� ����������� (� ������ �������
	// updateScrollBars) ������, ��� ���������� ��������������� scrollbar�.
	// ���� ������ ����������� ����� ������� ������� - ����������
	// �������������� scrollbar � ���������� ����������� ������� �����
	// �����, ������� ���� �� ������.
	// ���� ������ ����������� ����� ������� ������� - ����������
	// ������������ scrollbar � ���������� ����������� ������� �����
	// �����, ������� ���� �� ������.
	// ���� �� ����������� - resizeContents ���������� �� ���
	// �� ��� ����������� � � �����-������ ������������ ������ ������ �����.

	// ��� ���� ������ ����� resizeContents - ��� ����� ������ �������
	// ���������
	int repaintFlag;
	repaintFlag = 0;
	// if( (oldMapWidth>visibleWidth())&&(mapData.agmap.width<visibleWidth()) )
	// {
	//    // ����������� ������ - ��������� �������������� scrollbar
	//    repaintFlag |= 0x01;
	// }
	// if( (oldMapHeight>visibleHeight())&&(mapData.agmap.height<visibleHeight()) )
	// {
	//    // ����������� ������ - ��������� ������������ scrollbar
	//    repaintFlag |= 0x02;
	// }

	//	viewport()->setUpdatesEnabled( FALSE); //��������� ����������

	// resizeContents(mapData.agmap.width,mapData.agmap.height); // ������ ������� ���������
	// center(xc,yc); // ���������� � ������ �����

	//	viewport()->setUpdatesEnabled( TRUE); //��������� ����������

	// � ������ ��������, ��� ��� ���� ������������
	if( repaintFlag == 0x03)
	{
		// ������ �� ���� - �� ������� �� ���
	}
	else if( repaintFlag == 0x01)
	{
		// ���������� �� ����� ������� ����
		//    repaintContents(contentsRect().x(),contentsRect().y(),visibleWidth(),visibleHeight()-oldHbh);
	}
	else if( repaintFlag == 0x02)
	{
		// ���������� �� ����� ������� ����
		//    repaintContents(contentsRect().x(),contentsRect().y(),visibleWidth()-oldVbw,visibleHeight());
	}
	else
	{
		// ���������� ��� ������� �������
		//    repaintContents(contentsRect().x(),contentsRect().y(),visibleWidth(),visibleHeight());
	}

	return;
}

MainWindow::MainWindow( QWidget* parent) :
		QMainWindow( parent)
{
	state = AGSNone;
	oldState = AGSNone;

	fVIEW = 0;

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
	_DEBUG_FUNC(std::cout<<"FMAIN::MenuMapOpenSlot():"<<std::endl);

	QString filename = "/home/smartnlg/workspace/dena/maps/Voronezh/m3709.map";

//	filename = QFileDialog::getOpenFileName( this, tr( "Открытие файла карты"), "", tr( "Файл карты (*.map)"));

	if( filename.isEmpty()) return;

	HMAP hmap = mapOpenMap( filename.toStdString().c_str());
	if( hmap == 0) return;
	mapData.agmap.init( hmap);
	mapData.agmap.Print();

	mapSetBackColor( mapData.agmap.hmap, 0xFAFAFA);
//	mapWidget->resize( mapData.agmap.width, mapData.agmap.height);
//	viewScale( mapData.agmap.scale);
//
//	HSITE hsite = mapCreateAndAppendSite( mapData.agmap.hmap,
//			"/tmp/tmpsite.sit", "/home/aero/uoto/redarmy.rsc",
//			&mapData.agtmpsite.cs);
//	mapData.agtmpsite.init( mapData.agmap, hsite);
//	mapData.agtmpsite.Print();

//	setState( AGSSelect);
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
	if( !fVIEW) fVIEW = new FVIEW( this);
		fVIEW->show();
}

void MainWindow::CreateStatus()
{
	statusLabelCoord = new QLabel( TO_QT("X=0 Y=0"), statusBar());
	statusLabelCoord->setFrameStyle( QFrame::Box);

	statusLabelScale = new QLabel( TO_QT("1:0"), statusBar());
	statusLabelScale->setFrameStyle( QFrame::Box);

	statusBar()->addWidget( statusLabelCoord, 1);
	statusBar()->addWidget( statusLabelScale, 1);
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
	mapWidget->repaint();
}
;

void MapWidget::qqq()
{

}

void MainWindow::qqq()
{
	mapWidget->qqq();
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

/* RIP */
