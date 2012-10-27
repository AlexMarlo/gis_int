#ifndef GISMAPWIDGET_H_
#define GISMAPWIDGET_H_

#include <QtGui>

#include "fmain.h"

namespace gis
{

//class GisMapWidget

class GisMapWidget : public QWidget
{
Q_OBJECT
public:
	GisMapWidget( MapData mapData, QWidget *parent = 0);

	void closeMap();
	void changeScale( double kscale, long int xc, long int yc);
	void qqq();

signals:
	void changeCoordSignal( double, double);
	void changeScaleSignal( double);

public slots:
	void scrollChanged();
	void scaleChanged();

protected:
	virtual void contentsMousePressEvent( QMouseEvent *);
	virtual void contentsMouseReleaseEvent( QMouseEvent *);
	virtual void contentsMouseMoveEvent( QMouseEvent *);

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
