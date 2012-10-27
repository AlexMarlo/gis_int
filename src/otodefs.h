//====================================================================
// CVS header
// $Id: otodefs.h,v 1.2 2004/03/19 03:56:22 eugene Exp $
//====================================================================
#if ! defined ( __OTODEFS_H__ )
#define __OTODEFS_H__

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define PROG_NAME "Óïðàâëåíèå ÎÒÎ"
#define WININFO_DIR "/home/aero/comm/cfg/oto"

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


#endif /* __OTODEFS_H__ */
