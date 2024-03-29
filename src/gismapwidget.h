#ifndef GISMAPWIDGET_H_
#define GISMAPWIDGET_H_

#include <QtGui>

#include "gismapstructs.h"

namespace gis
{

class GisMapWidget : public QWidget
{
Q_OBJECT
public:
	GisMapWidget( QWidget *parent = 0);

	void closeMap();
	void changeScale( double kscale, long int xc, long int yc);

	void Repaint();

	void GetMapHW( long int* h, long int* w);
	void SetViewScale( long int scale);
	long int GetViewScale();

	void GetMapLeftTop( int * left, int * top);
	void SetMapLeftTop( long int left, long int top);

	HMAP GetMapHandle();
	QString GetMapFileName();

	bool MapOpen( QString absoluteMapPath, bool param);
	void MapClose();

	bool GetMapActive();

	void ConvertMetric( double *x, double *y, int placein, int placeout);

	DOUBLEPOINT pictureToGeo( int x, int y);
	DOUBLEPOINT geoToPicture( const DOUBLEPOINT& coordinate);

signals:
	void changeCoordSignal( double, double);
	void changeScaleSignal( double);

	void SignalMouseMove( int x, int y, int modkey);
	void SignalMousePress( int x, int y, int modkey);
	void SignalMouseRelease( int x, int y, int modkey);

	void beforePaintSignal( QPixmap& pixmap, QRect rect);

public slots:
	void scrollChanged();
	void scaleChanged();

	void zoomInSlot();
	void zoomOutSlot();

protected:

	virtual void paintEvent( QPaintEvent* event);
	virtual void resizeEvent( QResizeEvent* event);
	virtual void showEvent( QShowEvent* event);
	void wheelEvent( QWheelEvent* event);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    void setupUi();

    void resizeScoll();

private:
    QVBoxLayout *verticalLayout_;
    QHBoxLayout *horizontalLayout_;
    QSpacerItem *horizontalSpacer_;
	QScrollBar * verticalScrollBar_;
	QScrollBar * horizontalScrollBar_;

	HMAP hMap_;
	QString mapPath_;
	MapData mapData_;

	char *imageBits_;
	int imageWidth_;
	int imageHeight_;

	bool isNeedUpdatePixmap_;

	const double ScaleFactor_;

	QRect zoomRect;
	QPainter zoomPainter;
	bool zoomBegin;

	long int defaultScale_;
};

} /* namespace gis */
#endif /* GISMAPWIDGET_H_ */
