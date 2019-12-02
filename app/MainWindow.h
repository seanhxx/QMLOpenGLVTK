#ifndef MainWindow_h
#define MainWindow_h

#include <memory>
#include <QObject>

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void mousePressHandler(const int & button, const int & mouseX, const int & mouseY);
}


#endif
