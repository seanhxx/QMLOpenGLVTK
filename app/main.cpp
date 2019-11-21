#include <QDebug>
#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char **argv)
{
    qDebug() << "Program Start!";
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/app.qml")));
    
    if(engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}