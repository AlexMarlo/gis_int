#ifndef MAINWIDGET_H_
#define MAINWIDGET_H_

#include <QtGui>
#include "QMainWindow"
#include "fmain.h"

namespace gis
{

class MainWindow : public QMainWindow
{
Q_OBJECT
	friend class MapWidget;

public:
	MainWindow( QWidget* parent = 0);

	void setState( AGState st)
	{
		oldState = state;
		state = st;
		checkState();
	}

	int getState()
	{
		return state;
	}

	int getOldState()
	{
		return oldState;
	}

	void repaintMap();

	MapWidget* getMapWidget()
	{
		return mapWidget;
	}

public slots:
	void MenuMapOpenSlot();
	void MenuMapCloseSlot();
	void MenuMapPOpenSlot();
	void MenuMapPCloseSlot();
	void MenuMapExitSlot();
	void MenuModeSelectSlot();
	void MenuModeZoomSlot();
	void MenuViewViewSlot();
	void zoomInSlot();
	void zoomOutSlot();
	void MenuObjCurrentSlot();
	void MenuObjNewSlot();
	void MenuObjMetSlot();
	void MenuObjDelSlot();
	void MenuObjUnselectSlot();
	void LVVFExpandedSlot( QListViewItem*);
	void LVVFCurrentChangedSlot( QListViewItem*);
	void viewCoords( double, double);
	void viewScale( double);
	void qqq();
	void ButCreateClickedSlot();
	void ButShowClickedSlot();

protected:
	void CreateMenus();
	void CreateTools();
	void CreateStatus();
	void checkState();
	virtual void closeEvent( QCloseEvent * e);

	void fillLVVF();
	void fillLVVF( QListViewItem* I, std::vector< std::pair< int, int> >&chi, bool fill);

	MapWidget* mapWidget;
	MapData mapData;

	QMenuBar* menuBar_;
	QToolBar* VFWidget;
	QListView* LVVF;
	QListView* LVOTO;

	QToolBar* tbZoom;

	QMenu* smenuMap;
	QMenu* smenuView;
	QMenu* smenuMode;
	QMenu* smenuObj;

	QMenu* PopupMenuZoom;
	QMenu* PopupMenuSelect;

	QCursor *crZoomIn;
	QCursor *crZoomOut;

	QLabel* statusLabelScale;
	QLabel* statusLabelCoord;

	AGState state;
	AGState oldState;
};

} /* namespace gis */
#endif /* MAINWIDGET_H_ */
