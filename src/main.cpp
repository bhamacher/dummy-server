
#include <QCoreApplication>

#include <ve_commandevent.h>
#include <vcmp_componentdata.h>
#include <vn_networksystem.h>
#include <vn_tcpsystem.h>
#include <vn_introspectionsystem.h>
#include <vs_veinhash.h>
#include <vsc_scriptsystem.h>
#include <veinqml.h>
#include <veinqmlwrapper.h>
#include <ve_eventhandler.h>

#include <vl_databaselogger.h>
#include <vl_datasource.h>
#include <vl_qmllogger.h>
#include <vl_sqlitedb.h>

#include <QDebug>

#include <QLoggingCategory>
#include <QStringList>
#include <QDataStream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QRegExp>

#include "modulemanagercontroller.h"

#include "vfmoduleentity.h"

#include "rpchandler.h"
#include "vf_export.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    VeinEvent::EventHandler *evHandler = new VeinEvent::EventHandler(&a);

    // setup vein modules
    ModuleManagerController *mmController = new ModuleManagerController(&a);
    VeinNet::IntrospectionSystem *introspectionSystem = new VeinNet::IntrospectionSystem(&a);
    VeinStorage::VeinHash *storSystem = new VeinStorage::VeinHash(&a);
    VeinNet::NetworkSystem *netSystem = new VeinNet::NetworkSystem(&a);
    VeinNet::TcpSystem *tcpSystem = new VeinNet::TcpSystem(&a);
    VeinApiQml::VeinQml *qmlSystem = new VeinApiQml::VeinQml(&a);


    //setup logger
    VeinApiQml::VeinQml::setStaticInstance(qmlSystem);



    QList<VeinEvent::EventSystem*> subSystems;
    //do not reorder


    VfCpp::veinmoduleentity *someMod=new VfCpp::veinmoduleentity(300);

    vfExport::vf_export *module=new vfExport::vf_export();

    subSystems.append(module->getVeinEntity());
    subSystems.append(mmController);
    subSystems.append(introspectionSystem);
    subSystems.append(storSystem);
    subSystems.append(netSystem);
    subSystems.append(tcpSystem);
    subSystems.append(qmlSystem);



    evHandler->setSubsystems(subSystems);

    //conditional systems
    mmController->setStorage(storSystem);

    qRegisterMetaTypeStreamOperators<QList<int> >("QList<int>");
    qRegisterMetaTypeStreamOperators<QList<float> >("QList<float>");
    qRegisterMetaTypeStreamOperators<QList<double> >("QList<double>");
    qRegisterMetaTypeStreamOperators<QList<QString> >("QList<QString>");
    qRegisterMetaTypeStreamOperators<QVector<QString> >("QVector<QString>");




    // someMod->initModule();

    module->initOnce();
    qmlSystem->entitySubscribeById(3);




    mmController->initOnce();





    tcpSystem->startServer(12000);
    mmController->initializeEntity("test.json",QStringList("test.json"));

    return a.exec();
}
