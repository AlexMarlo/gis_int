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

void MapWidget::contentsMousePressEvent( QMouseEvent * e)
{
}

void MapWidget::contentsMouseMoveEvent( QMouseEvent * e)
{
}

void MapWidget::contentsMouseReleaseEvent( QMouseEvent * e)
{
}

void MapWidget::changeScale( double kscale, long int xc, long int yc)
{
	long int oldMapWidth, oldMapHeight;

	mapGetPictureSize( mapData_.agmap.hmap, &oldMapWidth, &oldMapHeight);

	mapChangeViewScale( mapData_.agmap.hmap, &xc, &yc, kscale);
	mapData_.agmap.scale = mapGetRealShowScale( mapData_.agmap.hmap);
	emit changeScaleSignal( mapData_.agmap.scale);

	mapGetPictureSize( mapData_.agmap.hmap, &mapData_.agmap.width, &mapData_.agmap.height);
}

/* RIP */
