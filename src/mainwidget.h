#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QtGui>
#include "QMainWindow"

#include "gismapstructs.h"
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
};

} /* namespace gis */
#endif /* MAINWIDGET_H_ */
