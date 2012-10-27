#include <iostream>

#include <qwidget.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <QX11Info>

#include "fnew.h"
#include "fmain.h"
#include "vars.h"
//#include "qtqt.h"
//#include "gis.h"

FNEW::FNEW( AGSITE par_agsite, QWidget* parent) :
		QDialog( parent)
{
	agsite = par_agsite;
	previewObjectCode = 0;

	QGridLayout* mainLayout = new QGridLayout( this);
	mainLayout->setMargin( 1);
	mainLayout->setSpacing( 3);

// LVObj = new QListView( this);
// LVObj->addColumn(TO_QT("�������"));
// LVObj->addColumn(TO_QT("id"));
// LVObj->addColumn(TO_QT("lid"));
// LVObj->setRootIsDecorated(true);
// connect( LVObj, SIGNAL( selectionChanged(QListViewItem*) ) , this, SLOT(LVObjCurrentChanged(QListViewItem*)));
//
// previewWidget = new QGroupBox(TO_QT(" ��� "),this,"previewWidget");
// previewWidget->setFixedSize(200,200);

	QPushButton* butOk = new QPushButton( TO_QT("�������"), this);
	connect( butOk, SIGNAL(clicked()), this, SLOT(butOkClickedSlot()));
	QPushButton* butCancel = new QPushButton( TO_QT("������"), this);
	connect( butCancel, SIGNAL(clicked()), this, SLOT(butCancelClickedSlot()));

// mainLayout->addMultiCellWidget(LVObj,0,2,0,0);
// mainLayout->addMultiCellWidget(previewWidget,0,0,1,2);
	mainLayout->addWidget( butOk, 2, 1);
	mainLayout->addWidget( butCancel, 2, 2);

	fillLVObj();

	setWindowTitle( TO_QT("��������� ������ �������"));

	previewWidget->installEventFilter( this);

	previewXC.xcDisplay = QX11Info::display();
	previewXC.xcWindow = previewWidget->winId();
	previewXC.xcGC = XCreateGC( previewXC.xcDisplay, previewXC.xcWindow, 0,
			NULL);
	;
	previewXC.xcPoint.x = 0;
	previewXC.xcPoint.y = 0;

	return;
}

void FNEW::fillLVObj()
{
// for(int i=1;i<agsite.layerCount;i++)
// {
//    QListViewItem* I = new QListViewItem(LVObj,TO_QT( mapGetSiteLayerName(agsite.agmap.hmap,agsite.hsite,i)),"0",TO_QT(itos(i).c_str()));
//    int objCount = mapGetRscObjectCountInLayer(agsite.hrsc,i);
//    for(int j=1;j<objCount;j++)
//    {
//       int objCode = mapGetRscObjectCodeInLayer(agsite.hrsc,i,j);
//
//       QListViewItem* II = new QListViewItem(I,TO_QT(mapGetRscObjectNameInLayer(agsite.hrsc,i,j)),TO_QT(itos(objCode).c_str()));
//    }
// }
}

void FNEW::LVObjCurrentChanged( QListViewItem* I)
{
//
// previewObjectCode = stoi(FROM_QT(I->text(1)));
// previewWidget->repaint(true);
//
// return;
}

bool FNEW::eventFilter( QObject * o, QEvent * e)
{
// if( (o==previewWidget)&&(e->type()==QEvent::Paint)&&(previewObjectCode!=0) )
// {
//    RECT r;
///*
//    r.LT = 0;
//    r.UP = 0;
//    r.RT = previewWidget->width();
//    r.DN = previewWidget->height();
//*/
//    int m = 5;
//    r.LT = previewWidget->frameRect().left()+m;
//    r.UP = previewWidget->frameRect().top()+m+m;
//    r.RT = previewWidget->frameRect().right()-m;
//    r.DN = previewWidget->frameRect().bottom()-m;
//    mapPaintExampleSiteObject(agsite.agmap.hmap,
//                              agsite.hsite,
//                              (HDC)&previewXC,
//			      &r,
//			      previewObjectCode);
// }
// return QWidget::eventFilter(o,e);
//
	return false;
}

void FNEW::butCancelClickedSlot()
{
// done(0);
// return;
}

void FNEW::butOkClickedSlot()
{
// int obj = stoi(FROM_QT(LVObj->currentItem()->text(1)));
// done(obj);
// return;
}

/* EOF */
