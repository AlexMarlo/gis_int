#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QtGui>
#include "QMainWindow"

#include "fmain.h"
#include "gismapwidget.h"

namespace gis
{

class MainWidget : public QMainWindow
{
Q_OBJECT
public:
	MainWidget( QWidget* parent = 0);

public slots:
	void MenuMapOpenSlot();

protected:
	virtual void closeEvent( QCloseEvent * e);

private:
	GisMapWidget* mapWidget;
	MapData mapData;
	AGState state;
	AGState oldState;
};

} /* namespace gis */
#endif /* MAINWIDGET_H_ */
