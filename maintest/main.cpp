
#include <QtGui>
#include <QApplication>
#include <QSplashScreen>


#include "./mainwindow/mainwindow.h"
#include "./shared/app_constants.h"

#include "HHSharedCore/hlogdebug.h"
#include "HHSharedSystemUtilities/SystemUtilities"
#include "HHSharedSystemUtilities/WinUtilities"
#include "HHSharedGUI/RichTextEditorWidget"


#include "processmonitor/processmonitor.h"


using namespace HEHUI;
/////////////////////////////////////////////////////////////////////////

#pragma comment(lib,"Advapi32")

















////////////////////////////////////////////////////////////////////////

void showSplashMessage(QSplashScreen *s, const QString &str){
    s->showMessage(str, Qt::AlignRight | Qt::AlignBottom, Qt::darkGreen);
}


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);


    a.addLibraryPath(QCoreApplication::applicationDirPath());
    a.addLibraryPath(QCoreApplication::applicationDirPath() + QDir::separator () + QString(PLUGINS_MAIN_DIR));
    a.addLibraryPath(QCoreApplication::applicationDirPath() + QDir::separator () + QString(MYLIBS_DIR));
    qDebug()<<"----main(....)~~Library Paths"<<QCoreApplication::libraryPaths ();


    for(int i = 0; i < argc; i++){
        if(QString(argv[i]).toLower() == "-log"){
            qInstallMessageHandler(logDebug);
            qAddPostRoutine(closeDebugLog);
        }
    }

////////////////////////////////

QString userName = "";

    HEHUI::WinUtilities::getLogonInfoOfCurrentUser(&userName, 0);
qDebug()<<"------userName:"<<userName;



    //HEHUI::WinUtilities::getFileVersion(QCoreApplication::applicationFilePath());

    unsigned long code = 0;

    QStringList predefinedVersionInfo;
    predefinedVersionInfo<<"InternalName"<<"ProductName"
       <<"CompanyName"<<"LegalCopyright"
      <<"ProductVersion"<<"FileDescription"
     <<"FileVersion"<<"OriginalFilename";

    //HEHUI::WinUtilities::getFileVersion("C:/Program Files (x86)/VisualDDK/AutoCompletion.dll", &predefinedVersionInfo, &code);
    //qDebug()<<HEHUI::WinUtilities::WinSysErrorMsg(code);
    //qDebug()<<predefinedVersionInfo;

//    for(int i=0;i<100;i++){
//        HEHUI::WinUtilities::getCPUUsage();
//    }

//    quint64 totalBytes = 0; int usage = 0;
//    HEHUI::SystemUtilities::getMemoryStatus(&totalBytes, &usage);
//    qDebug()<<"Total:"<<(totalBytes/(1024*1024))<<" Load:"<<usage;


//ProcessMonitor monitor;
//if(!monitor.init()){
//    return 0;
//}





//     HEHUI::WindowsManagement wm;
    //long long ll = 1422594833*10000000 + 116444736000000000;
    //long long ll =  Int32x32To64(1422594833, 10000000) + 116444736000000000;
    //qWarning()<<QString::number(ll>>32);
    //qWarning()<<QString::number(ll/(2^32));

    //qWarning()<< wm.WinSysErrorMsg(2118);

    //qDebug()<<"------------------";
     qDebug()<<HEHUI::SystemUtilities::getCPUSerialNumber();
     qDebug()<<HEHUI::SystemUtilities::getCPUName();

    // qDebug()<<wm.getHardDriveSerialNumber();
    // qDebug()<<wm.getHardDriveSerialNumber(1);




    //bool ok = false;
    //ok = wm.setStartupWithWin(QApplication::applicationFilePath(), "-test", "TEST", true);
    //ok = wm.isStartupWithWin(QApplication::applicationFilePath(), "-test", "TEST");
    //qDebug()<<"isStartupWithWin:"<<ok;

    //ok = wm.setStartupWithWin(QApplication::applicationFilePath(), "-test", "TEST", false);
    //ok = wm.isStartupWithWin(QApplication::applicationFilePath(), "-test", "TEST");
    //qDebug()<<"isStartupWithWin:"<<ok;

    //ok = wm.runAsForDesktopApplication("test", "", "testtest", "notepad.exe", "", true, "", true);
    ////ok = wm.runAsForDesktopApplication("test", "", "testtest", "cmd.exe", "/K echo %temp%", true);
    //qDebug()<<"runAsForDesktopApplication:"<<ok;

    //qDebug()<<" sizeof( void * ):"<<( sizeof( void * ) );
    //qDebug()<<"isWow64:"<<wm.isWow64();


    //HKEY hKey;
    //HKEY hKey2;
    //QString bin, sz, multi_sz;

    //wm.regOpen("HKEY_LOCAL_MACHINE\\SOFTWARE", &hKey, KEY_READ|KEY_WOW64_64KEY);
    //wm.regCreateKey(hKey, "1Test", &hKey2);
    //wm.regSetValue(hKey2, "SZ3", "SZ3", REG_SZ);
    //wm.regRead(hKey2, "SZ3", &sz);
    //qDebug()<<"sz:"<<sz;
    //wm.regDeleteValue(hKey2, "SZ3");
    //wm.regDeleteKey(hKey2, "", true);

    //wm.regDeleteKey("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", true);


    //wm.regRead("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", "BootDir", &sz);
    //wm.regRead("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Lsa\\Audit\\AuditPolicy", "AuditPolicySD", &bin);
    //wm.regRead("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", "Installation Sources1", &multi_sz);


    //wm.regCreateKey("HKEY_LOCAL_MACHINE\\SOFTWARE", "1Test", &hKey2, true);
    //wm.regSetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", "DWORD", "100", REG_DWORD);
    //wm.regSetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", "BINARY", bin, REG_BINARY);
    //wm.regSetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", "SZ", "sz4", REG_SZ, true);
    //wm.regSetValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", "MULTI_SZ", multi_sz, REG_MULTI_SZ);



    //wm.regRead("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", "SZ", &sz, true);
    //qDebug()<<"sz:"<<sz;

    //wm.regRead("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", "MULTI_SZ", &multi_sz);
    //qDebug()<<"multi_sz:"<<multi_sz;


    //wm.regDeleteKey("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", true);
    //wm.regDeleteValue("HKEY_LOCAL_MACHINE\\SOFTWARE\\1Test", "SZ3");

    //QStringList list;
    //wm.regEnumVal("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Nls\\CodePage", &list);
    //wm.regEnumKey("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Nls", &list);
    //qDebug()<<"list:"<<'\n'<<list;

    //return 0;

    //创建Splash Screen
    //Create Splash Screen
    QSplashScreen *splash = new QSplashScreen( QPixmap(QString(RESOURCE_PATH)+QString(APP_SPLASH_IMAGE_PATH)) );
    splash->show();

    //设置程序信息
    //Setup the program information
    showSplashMessage(splash, QObject::tr("Setup Application Info"));
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);
    a.setWindowIcon(QIcon(QString(RESOURCE_PATH)+QString(APP_ICON_PATH)));
    a.setOrganizationName(APP_ORG);
    a.setOrganizationDomain(APP_ORG_DOMAIN);
    showSplashMessage(splash, QString(APP_NAME) + " " + QString(APP_VERSION));


    //创建主窗口
    //Create the main window
//    HEHUI::MainWindow w;

//    showSplashMessage(splash, QObject::tr("Loading Plugins"));
//    w.loadPlugins("E:/workspace/Qt/QtApps/plugins/bin/debug/plugins/hehui");
//    w.showMaximized();

//    //    HEHUI::Screenshot w;
//    //    w.show();


//    //结束Splash Screen
//    //Finish the Splash Screen
//    splash->finish(&w);

    delete splash;


    RichTextEditorWidget wgt;
    wgt.show();
    wgt.setSourceCodeEditEnabled(false);




    return a.exec();

}

