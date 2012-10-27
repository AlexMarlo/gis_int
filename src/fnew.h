#if ! defined (_fnew_h_included_)
#define _fnew_h_included_

#include <string>

#if ! defined(MAPAPI_H)
#include <mapapi.h>
#undef max
#undef min
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#include <qwidget.h>
#include <qdialog.h>

#include "fmain.h"

class QListView;
class QGroupBox;

class FNEW : public QDialog
{
Q_OBJECT
public:
	FNEW( AGSITE par_agsite, QWidget* parent = 0);
	virtual bool eventFilter( QObject * watched, QEvent * e);

public slots:
	void LVObjCurrentChanged( QListViewItem*);
	void butCancelClickedSlot();
	void butOkClickedSlot();

protected:
	void fillLVObj();
	QListView* LVObj;
// QWidget* previewWidget;
	QGroupBox* previewWidget;

	AGSITE agsite;

private:
	XC previewXC;
	int previewObjectCode;
};

#endif //_fnew_h_included_
