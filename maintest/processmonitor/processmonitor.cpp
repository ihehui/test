#include "processmonitor.h"

#include <QApplication>

#include <QtConcurrent>

// Windows Header Files:
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>



#include "HHSharedCore/hcryptography.h"


const WCHAR serviceName[] = L"ProcessMonitor";
const WCHAR deviceName[] = L"\\\\.\\HHPROCMON";



ProcessMonitor::ProcessMonitor(QObject *parent) : QObject(parent)
{

    m_errorCode = ERROR_SUCCESS;

    m_passthroughOnError = true;

}

ProcessMonitor::~ProcessMonitor()
{
    cleanupDriver();
}

unsigned long ProcessMonitor::lastErrorCode() const{
    return m_errorCode;
}

bool ProcessMonitor::init(){
    qDebug()<<"--ProcessMonitor::init()";

    m_errorCode = ERROR_SUCCESS;

    if(!setupDriver()){
        return false;
    }

    DWORD controlbuff[64];
    DWORD dw;


    //CreateThread(0,0,(LPTHREAD_START_ROUTINE)monitor,0,0,&dw);
    QtConcurrent::run(this, &ProcessMonitor::monitor);

    //Open Device
    HANDLE device=CreateFileW(deviceName, GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_SYSTEM,0);
    if( INVALID_HANDLE_VALUE == device){
        m_errorCode = GetLastError();
        qCritical()<<QString("ERROR! CreateFileW failed. Error Code: %1").arg(m_errorCode);

        cleanupDriver();
        return false;
    }

    //Get NtCreateSection address, 将它传给驱动, 也将缓冲区的地址传给驱动
    DWORD * addr=(DWORD *)(1+(DWORD)GetProcAddress(GetModuleHandleW(L"ntdll.dll"),"NtCreateSection"));
    ZeroMemory(outputbuff,256);
    controlbuff[0]=addr[0];
    controlbuff[1]=(DWORD)&outputbuff[0];
    bool ok = DeviceIoControl(device,1000,controlbuff,256,controlbuff,256,&dw,0);
    if(!ok){
        m_errorCode = GetLastError();
        qCritical()<<QString("ERROR! DeviceIoControl failed. Error Code: %1").arg(m_errorCode);

        cleanupDriver();
    }

    return ok;

}


void ProcessMonitor::monitor()
{

    qDebug()<<"--ProcessMonitor::monitor()";


    DWORD a,x;
    wchar_t msgbuff[512];

    while(1)
    {
        memmove(&a,&outputbuff[0],4);

        //如果缓冲区为空，则休眠10ms，继续检查
        if(!a)
        {
            Sleep(10);continue;
        }

        // 如果文件的名字和路径在机器的运行进程列表中，则发送一个OK的回应
        char*name=(char*)&outputbuff[8];
        qDebug()<<"name:"<<name;
        QString appPath = QString::fromLocal8Bit(name);
        qDebug()<<"----appPath:"<<appPath;

        QString errorString;
        QString md5 = HEHUI::Cryptography::getFileMD5HexString(appPath, &errorString);
        qDebug()<<QString("MD5: %1 \n%2").arg(md5).arg(errorString);
        if(md5.isEmpty() && m_passthroughOnError){
            a=1;
            goto skip;
        }

        if(md5WhiteList.contains(md5, Qt::CaseInsensitive)){
            a=1;
            goto skip;
        }

        if(!md5BlackList.contains(md5, Qt::CaseInsensitive)){
            a=1;
            goto skip;
        }


//        msg = QString("Do you want to run '%1'?").arg(appPath);
//        wcscpy(msgbuff, msg.toStdWString().c_str());

//        // 如果用户同意，则添加该程序到信任列表里
//        if(IDYES==MessageBoxW(0, msgbuff,L"WARNING",MB_YESNO|MB_ICONQUESTION|0x00200000L))
//        {
//            a=1;
//            md5WhiteList.append(appPath);
//        }else{
            a=0;
//        }


        qDebug()<<"-------2-------";
        // 把用户的选择写进通信缓冲区，驱动将接收
    skip:memmove(&outputbuff[4], &a, 4);
qDebug()<<"-------3-------";

        //通知驱动继续进行运行
        a=0;
        memmove(&outputbuff[0], &a, 4);

        qDebug()<<"-------4-------";
    }

}


bool ProcessMonitor::setupDriver(){

    QString drvPath = QApplication::applicationDirPath() + "\\ProcessMonitor.sys";
    if(!QFileInfo::exists(drvPath)){
        m_errorCode = ERROR_FILE_NOT_FOUND;
        qDebug()<<QString("ERROR! Driver '%1' not found.").arg(drvPath);
        return false;
    }

    //Load Driver
    SC_HANDLE schSCManager=OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);
    if (NULL == schSCManager){
        m_errorCode = GetLastError();
        qCritical()<<QString("ERROR! OpenSCManagerW failed. Error Code: %1").arg(m_errorCode);
        return false;
    }

    SC_HANDLE schService = OpenServiceW(schSCManager, serviceName, SERVICE_ALL_ACCESS);
    if (schService == NULL){
        schService=CreateServiceW(schSCManager, serviceName, serviceName, SERVICE_START|SERVICE_STOP,SERVICE_KERNEL_DRIVER,SERVICE_DEMAND_START,SERVICE_ERROR_NORMAL,drvPath.toStdWString().c_str(),0,0,0,0,0);
    }

    if (schService == NULL){
        m_errorCode = GetLastError();
        qCritical()<<QString("ERROR! OpenServiceW failed. Error Code: %1").arg(m_errorCode);
        CloseServiceHandle(schSCManager);
        return false;
    }

    bool ok = StartServiceW(schService,0,0);
    if(!ok){
        m_errorCode = GetLastError();
        qCritical()<<QString("ERROR! StartServiceW failed. Error Code: %1").arg(m_errorCode);

        if(ERROR_SERVICE_ALREADY_RUNNING == m_errorCode){
            ok = true;
        }else{
            DeleteService(schService);
        }

    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);

    return  ok;

}

void ProcessMonitor::cleanupDriver(){
    SC_HANDLE schSCManager = OpenSCManager(0,0,SC_MANAGER_ALL_ACCESS);
    SERVICE_STATUS stat;
    SC_HANDLE schService = OpenService(schSCManager, serviceName, SERVICE_ALL_ACCESS);
    ControlService(schService,SERVICE_CONTROL_STOP,&stat);
    DeleteService(schService);

}

