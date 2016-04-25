#include "tcp.h"



namespace HEHUI {


TCP::TCP(QObject *parent) :
    TCPBase(parent)
{

}

void TCP::processData(quint32 socketID, QByteArray *data){

    QString address;
    quint16 port;
    getAddressInfoFromSocket(socketID, &address, &port);

    emit dataReceived(address, port, data);



}













}
