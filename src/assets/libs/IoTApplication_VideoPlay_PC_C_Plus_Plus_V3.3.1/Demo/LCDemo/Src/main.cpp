#include <QTranslator>
#include <libdsl/DPrintLog.h>
#include "libdsl/DExceptionHandler.h"
#include "View/MainForm.h"
#include <QtWidgets/QApplication>

bool g_isReleasedForOverseas = false;

#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE * __cdecl __iob_func(unsigned i) {
    return __acrt_iob_func(i);
}
#endif /* _MSC_VER>=1900 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator* trans = new QTranslator;
    //g_isReleasedForOverseas = !(trans->load("ch.qm"));
	g_isReleasedForOverseas = trans->load("ch.qm");
    a.installTranslator(trans);

    QTime curTime = QTime::currentTime();
    char szLogName[25] = { 0 };
    sprintf_s(szLogName, sizeof(szLogName), "log\\%02d-%02d-%02d", curTime.hour(), curTime.minute(), curTime.second());
    DLOG_SET_FILE(szLogName);
    DLOG_SET_STDERR(true);
    DLOG_SET_SYSLOG(true);

    QString strDump =  QString("ClientDump");
    dsl::DExceptionHandler::StartMonitor(strDump.toLocal8Bit().data());

    MainForm w;
    w.init();
    w.show();
    return a.exec();
}
