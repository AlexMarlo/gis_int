//#include <iostream.h>
//#include <stdio.h>
//
//#include "ubd.h"
//#include "gis.h"
//#include "cserv.h"
//#include "proc1.h"
//#include "defines.h"
//
//#include "otoubd.h"
//
//
//OtoUbd::OtoUbd()
// :Ubd()
//{
//
// uslConcept_OTO = "OTO";
// uslConcept_VF  = "VF";
// klsHar = "TK_C_CH_OTO";
// klsObj = "TK_C_TEFCO";
// otoConcept = new UbdConcept(uslConcept_OTO);
// vfConcept = new UbdConcept(uslConcept_VF);
//}
//
//bool OtoUbd::load()
//{
// _DEBUG_FUNC(cout<<"OtoUbd::load():"<<endl);
// if( !Ubd::load() )
// {
//    cout<<"OtoUbd::load(): ������ �������� ���"<<endl;
//    return false;
// }
// if( !loadConcept( otoConcept ) )
// {
//    cout<<"OtoUbd::load(): ������ �������� ��������� ���"<<endl;
//    return false;
// }
//
// if( !loadConcept( vfConcept ) )
// {
//    cout<<"OtoUbd::load(): ������ �������� ��������� VF"<<endl;
//    return false;
// }
//
// int kkk;
//
// kkk = getObjKodByRubr(otoConcept->getTabUPI(), rubrRK);
// if( kkk == -1 ){ cout<<"OtoUbd::load(): ������ RK �� ������."<<endl; return false;}
// upiObjRK.setKod(kkk);
// upiObjRK.setConc(otoConcept);
//
// kkk = getObjKodByRubr(otoConcept->getTabUPI(), rubrLayer);
// if( kkk == -1 ){ cout<<"OtoUbd::load(): ������ Layer �� ������."<<endl; return false;}
// upiObjLayer.setKod(kkk);
// upiObjLayer.setConc(otoConcept);
//
// kkk = getObjKodByRubr(otoConcept->getTabUPI(), rubrObj);
// if( kkk == -1 ){ cout<<"OtoUbd::load(): ������ Obj �� ������."<<endl; return false;}
// upiObjObj.setKod(kkk);
// upiObjObj.setConc(otoConcept);
//
// if( !loadObject( &upiObjRK ) ){ cout<<"OtoUbd::load(): ������ �������� RK."<<endl; return false;}
// if( !loadObject( &upiObjLayer ) ){ cout<<"OtoUbd::load(): ������ �������� Layer."<<endl; return false;}
// if( !loadObject( &upiObjObj ) ){ cout<<"OtoUbd::load(): ������ �������� Obj."<<endl; return false;}
//
// if( !loadHarRubrList(&upiObjRK) ){ cout<<"OtoUbd::load(): ������ �������� ������������ ������������� RK."<<endl; return false;}
// if( !loadHarRubrList(&upiObjLayer) ){ cout<<"OtoUbd::load(): ������ �������� ������������ ������������� Layer."<<endl; return false;}
// if( !loadHarRubrList(&upiObjObj) ){ cout<<"OtoUbd::load(): ������ �������� ������������ ������������� Obj."<<endl; return false;}
// checkHarRubrList();
//
// return true;
//}
//
//
//void OtoUbd::Print()
//{
// Ubd::Print();
//
// cout<<"============================"<<endl;
// cout<<"�������� ������������ ���������:"<<endl;
// cout<<"��� '"<<uslConcept_OTO<<"'"<<endl;
// cout<<"��  '"<<uslConcept_VF<<"'"<<endl;
// cout<<"============================"<<endl;
//
// cout<<"============================"<<endl;
// cout<<"��������� ���:"<<endl;
// otoConcept->Print();
// cout<<"============================"<<endl;
//
// upiObjRK.Print();
// upiObjLayer.Print();
// upiObjObj.Print();
//
// cout<<"============================"<<endl;
// cout<<"������ �������������"<<endl;
// harRubrList.Print();
// cout<<"============================"<<endl;
//
///*
// cout<<"============================"<<endl;
// cout<<"������ �������������"<<endl;
// upiHarList.Print();
// cout<<"============================"<<endl;
// cout<<"============================"<<endl;
// cout<<"������ �������� �������������"<<endl;
// upiHarNameList.Print();
// cout<<"============================"<<endl;
//*/
// return;
//}
//
//
//
//OtoUbdINT::OtoUbdINT()
//{
// _DEBUG_FUNC(cout<<"OtoUbdINT::OtoUbdINT()"<<endl;);
// rubrRK    = "IRK";
// rubrLayer = "ILAYER";
// rubrObj   = "IOBJ";
//}
//
//
///* EOF */
