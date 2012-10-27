#include <iostream>

#include <qwidget.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QGroupBox>

#include "fview.h"
#include "fmain.h"
#include "vars.h"
#include <QScrollBar>

FVIEW::FVIEW( QWidget* parent) :
		QMainWindow( parent)
{
	QWidget* mainWidget = new QWidget( this);
	QGridLayout* mainLayout = new QGridLayout( mainWidget);
	mainLayout->setMargin( 1);
	mainLayout->setSpacing( 3);

	QGroupBox* gb1 = new QGroupBox( TO_QT("��� �����"), mainWidget);
	QGridLayout* gb1Layout = new QGridLayout( gb1);
	gb1Layout->setMargin( 15);
	gb1Layout->setSpacing( 3);

	QLabel* l1 = new QLabel( TO_QT("�������"), gb1);
	l1->setFixedSize( l1->sizeHint());
	sbBright = new QScrollBar( Qt::Horizontal, gb1);
	sbBright->setFixedWidth( 150);
	connect( sbBright, SIGNAL(valueChanged(int)), this,
			SLOT(sbBrightChangedSlot(int)));
	leBright = new QLineEdit( "Bright", gb1);
	leBright->setEnabled( false);
	leBright->setFixedWidth( 25);

	QLabel* l2 = new QLabel( TO_QT("��������"), gb1);
	l2->setFixedSize( l2->sizeHint());
	sbContrast = new QScrollBar( Qt::Horizontal, gb1);
	sbContrast->setFixedWidth( 150);
	connect( sbContrast, SIGNAL(valueChanged(int)), this,
			SLOT(sbContrastChangedSlot(int)));
	leContrast = new QLineEdit( "Contrast", gb1);
	leContrast->setEnabled( false);
	leContrast->setFixedWidth( 25);

	gb1Layout->addWidget( l1, 0, 0, Qt::AlignLeft);
	gb1Layout->addWidget( sbBright, 0, 1, Qt::AlignLeft | Qt::AlignRight);
	gb1Layout->addWidget( leBright, 0, 2, Qt::AlignRight);

	gb1Layout->addWidget( l2, 1, 0, Qt::AlignLeft);
	gb1Layout->addWidget( sbContrast, 1, 1, Qt::AlignLeft | Qt::AlignRight);
	gb1Layout->addWidget( leContrast, 1, 2, Qt::AlignRight);

	sbBrightChangedSlot( 0);
	sbContrastChangedSlot( 0);

	QPushButton* butOk = new QPushButton( TO_QT("��"), mainWidget);
	connect( butOk, SIGNAL(clicked()), this, SLOT(closeSlot()));

	QPushButton* butDefaults = new QPushButton( TO_QT("�� ���������"),
			mainWidget);
	connect( butDefaults, SIGNAL(clicked()), this, SLOT(butDefaultsSlot()));

	mainLayout->addWidget( gb1, 0, 0, 0, 1);
	mainLayout->addWidget( butOk, 2, 0);
	mainLayout->addWidget( butDefaults, 2, 1);
// mainLayout->expand(2,3);

	setCentralWidget( mainWidget);

	setWindowTitle( TO_QT("��� �����"));

	return;
}

void FVIEW::closeSlot()
{
	_DEBUG_FUNC(std::cout<<"FVIEW::MenuMapExitSlot():"<<std::endl);
	hide();
	return;
}

void FVIEW::sbBrightChangedSlot( int val)
{
	std::cout << "sbBrightChangedSlot(int val)" << std::endl;
	char str[10];
	sprintf( str, "%d", val);
	leBright->setText( TO_QT(str));

	mapSetBright( mapData.agmap.hmap, val);
	mapData.agmap.bright = val;
	mainWindow->getMapWidget()->repaint();
}

void FVIEW::sbContrastChangedSlot( int val)
{
	std::cout << "sbContrastChangedSlot(int val)" << std::endl;
	char str[10];
	sprintf( str, "%d", val);
	leContrast->setText( TO_QT(str));

	mapSetContrast( mapData.agmap.hmap, val);
	mapData.agmap.contrast = val;
	mainWindow->getMapWidget()->repaint();
}

void FVIEW::butDefaultsSlot()
{
// sbBrightChangedSlot(0);
// sbContrastChangedSlot(0);
	sbBright->setValue( 0);
	sbContrast->setValue( 0);
}

/* EOF */
