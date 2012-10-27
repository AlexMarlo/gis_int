#include "gismapwidget.h"

namespace gis
{

GisMapWidget::GisMapWidget( MapData mapData, QWidget *parent) :
		QWidget( parent),
		mapData_( mapData),
		imageBits_( 0),
		imageWidth_( 0),
		imageHeight_( 0),
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

	setWindowTitle( tr( "Карта"));
}

void GisMapWidget::scrollChanged()
{
	isNeedUpdatePixmap_ = true;
	repaint();
}

void GisMapWidget::scaleChanged()
{
	isNeedUpdatePixmap_ = true;
	repaint();
}

void GisMapWidget::resizeEvent( QResizeEvent* event)
{
	isNeedUpdatePixmap_ = true;
}

void GisMapWidget::showEvent( QShowEvent* event)
{
	isNeedUpdatePixmap_ = true;
}

void GisMapWidget::paintEvent( QPaintEvent* event)
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


void GisMapWidget::closeMap()
{
	mapCloseMap( mapData_.agmap.hmap);
	mapData_.agmap.hmap = 0;
}

void GisMapWidget::changeScale( double kscale, long int xc, long int yc)
{
	long int oldMapWidth, oldMapHeight;

	mapGetPictureSize( mapData_.agmap.hmap, &oldMapWidth, &oldMapHeight);

	mapChangeViewScale( mapData_.agmap.hmap, &xc, &yc, kscale);
	mapData_.agmap.scale = mapGetRealShowScale( mapData_.agmap.hmap);
	emit changeScaleSignal( mapData_.agmap.scale);

	mapGetPictureSize( mapData_.agmap.hmap, &mapData_.agmap.width, &mapData_.agmap.height);
}

} /* namespace gis */
