#ifndef PROCESSMONITOR_H
#define PROCESSMONITOR_H

#include <QObject>
#include <QStringList>




class ProcessMonitor : public QObject
{
    Q_OBJECT
public:
    explicit ProcessMonitor(QObject *parent = 0);
    ~ProcessMonitor();

    unsigned long lastErrorCode() const;

signals:


public slots:
    bool init();


private slots:
    void monitor();


private:
    bool setupDriver();
    void cleanupDriver();



private:
    unsigned long m_errorCode;
    bool m_passthroughOnError;

    char outputbuff[256];


    QString msg;

    QStringList md5WhiteList;
    QStringList md5BlackList;
    QStringList filePathWhiteList;
    QStringList filePathBlackList;


};

#endif // PROCESSMONITOR_H
