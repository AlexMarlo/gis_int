//#include <iostream.h>
//
//#include <qapplication.h>
//#include <qwindowsstyle.h>
//
//#include "ubd.h"
//#include "otoubd.h"
//
//#include "fmain.h"
//#include "vars.h"
//
//
//int main( int argc, char ** argv )
//{
// int ret;
//
////��������� ���
// otoUbd = new OtoUbdINT();
// if(!otoUbd->load())
// {
//    cout<<argv[0]<<": ������ �������� �������� ���!"<<endl;
//    return 1;
// }
//
// vfRel = otoUbd->getTrelKod(otoUbd->uslTrel_BP);
//
//
// QApplication* a = new QApplication( argc, argv );
// a->setFont( QFont("Helvetica",10,QFont::Bold,FALSE,QFont::KOI8R),true);
// a->setStyle( new QWindowsStyle );
//
// try{ fMAIN = new FMAIN(NULL,"fMAIN"); } //������� ������� ����
// catch(...)
// {
//    cout<<argv[0]<<": ������ �������� fMAIN!"<<endl;
//    return 1;
// }
//
// a->setMainWidget( fMAIN );
// fMAIN->show();
// ret = a->exec();
// delete fMAIN;
//
// return(ret);
//}
//
