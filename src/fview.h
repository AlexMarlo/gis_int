#if ! defined (_fview_h_included_)
#define _fview_h_included_

#include <string>

#if ! defined(MAPAPI_H)
#include <mapapi.h>
#undef max
#undef min
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#include <qwidget.h>
#include <qmainwindow.h>

class QPushButton;
class QLineEdit;
class QScrollBar;

class FVIEW : public QMainWindow
{
Q_OBJECT

public:
	FVIEW( QWidget* parent = 0);

public slots:
	void closeSlot();
	void butDefaultsSlot();
	void sbBrightChangedSlot( int);
	void sbContrastChangedSlot( int);

protected:
	QLineEdit* leBright;
	QLineEdit* leContrast;
	QScrollBar* sbBright;
	QScrollBar* sbContrast;
};

#endif //_fview_h_included_
