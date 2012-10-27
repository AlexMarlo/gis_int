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

	void GetMapLeftTop( int* top, int* left);
	void SetMapLeftTop( long int left, long int top);

	HMAP GetMapHandle();
	QString GetMapFileName();

	bool MapOpen( QString absoluteMapPath, bool param);
	void MapClose();

	bool GetMapActive();

	void ConvertMetric( double *X, double* Y, PPLACE pplace1, PPLACE pplace2);

signals:
	void changeCoordSignal( double, double);
	void changeScaleSignal( double);

	void SignalMouseMove( int, int, int);
	void SignalMousePress(int, int, int);
	void SignalMouseRelease( int, int, int);

public slots:
	void scrollChanged();
	void scaleChanged();

protected:

	virtual void paintEvent( QPaintEvent* event);
	virtual void resizeEvent( QResizeEvent* event);
	virtual void showEvent( QShowEvent* event);

private:
	QScrollBar * verticalScrollBar_;
	QScrollBar * horizontalScrollBar_;

	MapData mapData_;

	char *imageBits_;
	int imageWidth_;
	int imageHeight_;

	bool isNeedUpdatePixmap_;

	QRect zoomRect;
	QPainter zoomPainter;
	bool zoomBegin;
};

} /* namespace gis */
#endif /* GISMAPWIDGET_H_ */
