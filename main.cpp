#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick3D/qquick3d.h>
#include "pointcloudcubegeometry.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat(4));

    qmlRegisterType<PointCloudCubeGeometry>("PointCloudCube", 1,0, "PointCloudCubeGeometry");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/PointSize_Qt6_Quick3D/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
