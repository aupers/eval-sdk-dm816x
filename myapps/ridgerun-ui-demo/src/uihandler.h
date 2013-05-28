#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <QObject>
#include <QApplication>
#include <QVariant>
#include <QDeclarativeItem>
#include <stdio.h>
#include <iostream>
#include <fstream>

class UIHandler : public QDeclarativeItem
{
    Q_OBJECT
public:
    explicit UIHandler(QObject *rootElement = 0);

private:
    QObject* rootElement;
    QString state;

signals:


public slots:
    void handle_actionRequested(QString command);
    void handle_mainStateChanged(QString text);

    void setMainState(QString text);
    void showInfoMessage(QString text);
    void cancelViewerToggle();
    void updateStatusBar();

    void setSignalLevel(int level);
    void setBatteryLevel(int level);
};

#endif //UIHANDLER_H
