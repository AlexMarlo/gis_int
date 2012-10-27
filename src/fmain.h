#if ! defined (_fmain_h_included_)
#define _fmain_h_included_

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <iostream>

extern "C"
{
#include <mapapi.h>
}
#undef max
#undef min
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#include <qwidget.h>
#include <qmainwindow.h>
#include <qpainter.h>
#include <qscrollarea.h>
#include <QMenu>
#include <QScrollBar>

#include <X11/Xlib.h>

#include "vars.h"
#include <qmenubar.h>

#define TO_QT(a) QString::fromLocal8Bit(a)
#define FROM_QT(a) (const char*)(a).local8Bit()

#if ! defined __DEBUG_FUNC__
#define _DEBUG_FUNC(a)
#else
#define _DEBUG_FUNC(a) a
#endif

#if ! defined _DEBUG_
#define _DEBUG(a)
#else
#define _DEBUG(a) a
#endif

enum AGState
{
	AGSNone = 0,
	AGSSelect,
	AGSZoomIn,
	AGSZoomOut
};

typedef struct XC
{
	Display* xcDisplay; //  ����� � � - ��������
	Window xcWindow; //  ������������� ����
	GC xcGC; //  ����������� �������� ����
	DRAWPOINT xcPoint; //  ������������ ������� ������ � ���� :
					   //  �������, �����  ���� � ��������
} XC;

class AGMAP
{
public:
	AGMAP();
	void clear();
	void init( HMAP par_hmap);
	void Print();

public:
	HMAP hmap;
	long int width;
	long int height;
	std::string path;
	double scale;
	double minScale;
	double maxScale;
	int bright;
	int contrast;
	int layerCount;
};

class AGSITE
{
public:
	AGSITE();
	void clear();
	void init( AGMAP par_agmap, HSITE par_hsite);
	void Print();

public:
	AGMAP agmap;
	HSITE hsite;
	HRSC hrsc;
	std::string path;
	CREATESITE cs;
	std::string rscPath;
	int layerCount;
};

class MapData
{
public:
	MapData();
	void clear();

public:
	AGMAP agmap;
	AGSITE agtmpsite;
	std::vector< AGSITE> agsites;
};

class FVIEW;
class QPushButton;
class QToolBar;
class QToolButton;
class QLabel;
class QListView;
class QListViewItem;

class MapWidget : public QWidget
{
Q_OBJECT
public:
	MapWidget( MapData mapData, QWidget *parent = 0);

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
	XC xc_;

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

/////////////////////////////////////////////////////////////////

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
	void fillLVVF( QListViewItem* I, std::vector< std::pair< int, int> >&chi
			,bool fill);

	MapWidget* mapWidget;
	QMenuBar* menuBar_;
	FVIEW* fVIEW;
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

#endif //_fmain_h_included_
