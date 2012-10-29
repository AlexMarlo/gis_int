#include "gismapwidget.h"

namespace gis
{

GisMapWidget::GisMapWidget( QWidget *parent) :
		QWidget( parent),
		hMap_( 0),
		imageBits_( 0),
		imageWidth_( 0),
		imageHeight_( 0),
		isNeedUpdatePixmap_ ( true),
		ScaleFactor_( 1.25)
{
	setupUi();

	defaultScale_ = GetViewScale();
}

void GisMapWidget::setupUi()
{
    verticalLayout_ = new QVBoxLayout(this);
    verticalLayout_->setSpacing(0);
    verticalLayout_->setContentsMargins( 0, 0, 0, 0);
    verticalLayout_->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout_ = new QHBoxLayout();
    horizontalLayout_->setSpacing(6);
    horizontalLayout_->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer_ = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_->addItem( horizontalSpacer_);

    verticalScrollBar_ = new QScrollBar(this);
    verticalScrollBar_->setObjectName( QString::fromUtf8("verticalScrollBar"));
    verticalScrollBar_->setOrientation( Qt::Vertical);

    horizontalLayout_->addWidget( verticalScrollBar_);

    verticalLayout_->addLayout( horizontalLayout_);

    horizontalScrollBar_ = new QScrollBar( this);
    horizontalScrollBar_->setObjectName(QString::fromUtf8("horizontalScrollBar"));
    horizontalScrollBar_->setOrientation(Qt::Horizontal);

    verticalLayout_->addWidget( horizontalScrollBar_);

	connect( verticalScrollBar_, SIGNAL( valueChanged( int)), this, SLOT( scrollChanged()));
	connect( horizontalScrollBar_, SIGNAL( valueChanged( int)), this, SLOT( scrollChanged()));

} // setupUi

void GisMapWidget::showEvent(QShowEvent *event)
{
	isNeedUpdatePixmap_ = true;
}

void GisMapWidget::scrollChanged()
{
	resizeScoll();
	Repaint();
}

void GisMapWidget::scaleChanged()
{
	Repaint();
}

void GisMapWidget::Repaint()
{
	isNeedUpdatePixmap_ = true;
	repaint();
}

void GisMapWidget::resizeEvent( QResizeEvent* event)
{
	isNeedUpdatePixmap_ = true;
	resizeScoll();
}

void GisMapWidget::resizeScoll()
{
	if( hMap_ == 0)
		return;

	long int x, y;
	long int mapW, mapH;

	mapGetPictureSize( hMap_, &mapW, &mapH);

	x = mapW - width();
	y = mapH - height();

	std::cout << "resizeScoll() mapW " << mapW << " mapH "<< mapH  << std::endl;

	if (x < 0) x = 0;
	if (y < 0) y = 0;

//	horizontalScrollBar_->setValue( horizontalScrollBar_->value() * scale);
//	verticalScrollBar_->setValue( verticalScrollBar_->value() * scale);

	horizontalScrollBar_->setMaximum( x);
	verticalScrollBar_->setMaximum( y);
}

void GisMapWidget::paintEvent( QPaintEvent *event)
{
	int mapDepth = mapGetMapScreenDepth();
	RECT rectDraw;
	int cx, cy, cw, ch;
	int bytes_per_line;

	if( hMap_)
	{
		cx = horizontalScrollBar_->value();
		cy = verticalScrollBar_->value();
		cw = event->rect().width();
		ch = event->rect().height();
		bytes_per_line = cw * mapDepth / 8;
		if(isNeedUpdatePixmap_)
		{
			XIMAGEDESC Ximagedesc;
			long allignwidth = cw * mapDepth / 8;
			long size = allignwidth * ch;
			if( imageWidth_ != event->rect().width() || imageHeight_ != event->rect().height())
			{
				if(imageBits_)
					FreeTheMemory(imageBits_);

				imageBits_ = AllocateTheMemory(size);
				if(!imageBits_)
					return;

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
			mapPaintToXImage( hMap_, &Ximagedesc, 0, 0, &rectDraw);
			isNeedUpdatePixmap_ = false;
		}

		QImage::Format format;
		switch (mapDepth)
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

		QImage image((uchar*)(imageBits_), cw, ch, bytes_per_line, format);
		QPainter painter(this);
		QPixmap pixmap = QPixmap::fromImage( image);

		emit beforePaintSignal( pixmap, event->rect());

		painter.drawPixmap( QPoint(0, 0), pixmap);
		//painter.drawImage( QPoint(0, 0), image);
	}
}

void GisMapWidget::closeMap()
{
	mapCloseMap(mapData_.agmap.hmap);
	mapData_.agmap.hmap = 0;
}

void GisMapWidget::changeScale( double kscale, long int xc, long int yc)
{
	if (hMap_ == 0) return;

	long int oldMapWidth, oldMapHeight;
	mapGetPictureSize( mapData_.agmap.hmap, &oldMapWidth, &oldMapHeight);
	mapChangeViewScale( mapData_.agmap.hmap, &xc, &yc, kscale);
	mapData_.agmap.scale = mapGetRealShowScale( mapData_.agmap.hmap);
	changeScaleSignal( mapData_.agmap.scale);

	mapGetPictureSize( mapData_.agmap.hmap, &mapData_.agmap.width, &mapData_.agmap.height);
}

bool GisMapWidget::MapOpen( QString absoluteMapPath, bool param)
{
	if( absoluteMapPath.isEmpty())
		return false;

	hMap_ = mapOpenMap( absoluteMapPath.toStdString().c_str());
	if( hMap_ == 0)
		return false;

	mapPath_ = absoluteMapPath;
	mapData_.agmap.init( hMap_);
	mapData_.agmap.Print();

	resizeScoll();

	return true;
}


void GisMapWidget::GetMapHW( long int * h, long int * w)
{
	*h = mapData_.agmap.height;
	*w = mapData_.agmap.width;
}

void GisMapWidget::SetViewScale( long int scale)
{
	if ( hMap_ == 0) return;

	std::cout << "SetViewScale( long int scale) " << scale << std::endl;
	mapSetRealShowScale( hMap_, scale);
	resizeScoll();
}

long int GisMapWidget::GetViewScale()
{
	if ( hMap_ == 0) return 0;

	std::cout << "GetViewScale( long int scale) " << mapGetRealShowScale( hMap_) << std::endl;
	return 	mapGetRealShowScale( hMap_);

}

void GisMapWidget::GetMapLeftTop( int * left, int * top)
{
	*left = horizontalScrollBar_->value();
	*top = verticalScrollBar_->value();
}

void GisMapWidget::SetMapLeftTop( long int left, long int top)
{
	horizontalScrollBar_->setValue( left);
	verticalScrollBar_->setValue( top);
	Repaint();
}

HMAP GisMapWidget::GetMapHandle()
{
	return mapData_.agmap.hmap;
}

QString GisMapWidget::GetMapFileName()
{
	return mapPath_;
}

void GisMapWidget::MapClose()
{
}

bool GisMapWidget::GetMapActive()
{
	return true;
}

void GisMapWidget::ConvertMetric( double *x, double *y, int placein, int placeout)
{
	DOUBLEPOINT src;
	src.X = *x;
	src.Y = *y;
	DOUBLEPOINT tag = src;

	mapTransformPoints( hMap_, &src, placein, &tag, placeout, 1);

	*x = tag.X;
	*y = tag.Y;
}

void GisMapWidget::mousePressEvent(QMouseEvent *event)
{
	std::cout << "mousePressEvent(QMouseEvent *event)" << std::endl;
	emit SignalMousePress( event->x(), event->y(), event->button());
}

void GisMapWidget::mouseReleaseEvent(QMouseEvent *event)
{
	std::cout << "mouseReleaseEvent(QMouseEvent *event)" << std::endl;
	emit SignalMouseRelease( event->x(), event->y(), event->button());
}

void GisMapWidget::mouseDoubleClickEvent(QMouseEvent *event)
{}

void GisMapWidget::mouseMoveEvent(QMouseEvent *event)
{
	std::cout << "mouseMoveEvent(QMouseEvent *event)" << std::endl;
	emit SignalMouseMove( event->x(), event->y(), event->button());
}

void GisMapWidget::wheelEvent( QWheelEvent* event)
{
//	if( scrollingMode_)
//		return;

	if( event->delta() < 0)
		zoomInSlot();
	else
		zoomOutSlot();
}

void GisMapWidget::zoomOutSlot()
{
	long int h, w;
	this->GetMapHW( &h, &w);
	QPoint mousePos = mapFromGlobal( QCursor::pos());
	DOUBLEPOINT coordinate( this->pictureToGeo( mousePos.x(), mousePos.y()));
	this->SetViewScale( this->GetViewScale() / ScaleFactor_);

//	if( sender() != zoomOutAction_)
//	{
		DOUBLEPOINT dPoint = this->geoToPicture( coordinate);
		this->SetMapLeftTop( dPoint.x - mousePos.x(), dPoint.y - mousePos.y());
//	}
}

void GisMapWidget::zoomInSlot()
{
	long int h, w;
	this->GetMapHW( &h, &w);
	QSize size = this->size();
	QPoint mousePos = mapFromGlobal( QCursor::pos());
	DOUBLEPOINT coordinate = this->pictureToGeo( mousePos.x(), mousePos.y());

	if( h >= size.height() || w >= size.width())
		this->SetViewScale( this->GetViewScale() * ScaleFactor_);
	else
		return;

//	if( sender() != zoomInAction_)
//	{
		DOUBLEPOINT dPoint = this->geoToPicture( coordinate);
		this->SetMapLeftTop( dPoint.x - mousePos.x(), dPoint.y - mousePos.y());
//	}
}

DOUBLEPOINT GisMapWidget::pictureToGeo( int x, int y)
{
	int left, top;
	DOUBLEPOINT dpoint;

	this->GetMapLeftTop(&left, &top);

	dpoint.X = left + x;
	dpoint.Y = top + y;
	this->ConvertMetric(&dpoint.X, &dpoint.Y, PP_PICTURE, PP_GEO);

	return dpoint;
}

DOUBLEPOINT GisMapWidget::geoToPicture( const DOUBLEPOINT& coordinate)
{
	DOUBLEPOINT doublePoint;
	doublePoint.x = coordinate.x;
	doublePoint.y = coordinate.y;

	this->ConvertMetric( &doublePoint.X, &doublePoint.Y, PP_GEO, PP_PICTURE);

	return doublePoint;
}

} /* namespace gis */
