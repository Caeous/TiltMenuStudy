#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "TiltMenuModel.h"
#include "TiltMenuOptionsModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<TiltMenuModel>("com.thalmic.TiltMenuModel", 1, 0, "TiltMenuModel");
    qmlRegisterType<TiltMenuOptionsModel>("com.thalmic.TiltMenuOptionsModel", 1, 0, "TiltMenuOptionsModel");

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
