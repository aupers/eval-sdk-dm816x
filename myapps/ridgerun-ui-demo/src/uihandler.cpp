#include "uihandler.h"

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <QDebug>

using namespace std;

UIHandler::UIHandler(QObject *rootElement)
{
    this->rootElement = rootElement;

    QObject::connect((QObject*) rootElement, SIGNAL(actionRequested(QString)),(QObject*) this, SLOT(handle_actionRequested(QString)), Qt::DirectConnection);
    QObject::connect((QObject*) rootElement, SIGNAL(mainStateChanged(QString)),(QObject*) this, SLOT(handle_mainStateChanged(QString)), Qt::DirectConnection);

    state = "splash";
}

void UIHandler::handle_actionRequested(QString command){

    QStringList commParts = command.split(" ");

    //Handle enter setup request
    if(commParts.at(0) == "config"){
        if (state == "splash"){

            //@TODO: Load settings here

            setMainState("config");
        }
        else if(state != "config"){
            showInfoMessage("Error: Can't enter setup when live view is active.");
        }
    }


    //Handle snapshot request
    else if(commParts.at(0) == "snapshot"){

        //@TODO: Screenshot-taking logic here

        showInfoMessage("Snapshot Taken");
    }

    //Handle live view request
    else if(commParts.at(0) == "live_view"){

        //@TODO: Live view start logic here

        if(commParts.at(1) == "start"){
            if (state == "splash"){
                //Load settings
                setMainState("viewer");
            }
            else if (state != "viewer"){
                showInfoMessage("Error: Can't enter live view when setup is active.");
                cancelViewerToggle();
            }
        }
        else{

            //@TODO: Live view stop logic here

            setMainState("splash");
        }
    }

    //Handle save setup request
    else if(commParts.at(0) == "save_config"){

        //@TODO: Settings-saving logic here (I guess)

    }

    else if(commParts.at(0) == "changeVolume"){

        QString msg = "Volume should now be: "+commParts.at(1);
        qDebug()<< msg;

    }

    else{

        qDebug("Command not recognized");

    }
}


void UIHandler::handle_mainStateChanged(QString text){
    state = text;
}

void UIHandler::updateStatusBar(){

    // @TODO: Get a number between 0 and 4 for the battery:
    setBatteryLevel(3);

    // @TODO: Get a number between 0 and 4 for the signal:
    setSignalLevel(2);

}

void UIHandler::setSignalLevel(int level){
    QVariant message = level;
    QMetaObject::invokeMethod(rootElement, "setSignalLevel",
                              Q_ARG(QVariant, message));
}

void UIHandler::setBatteryLevel(int level){
    QVariant message = level;
    QMetaObject::invokeMethod(rootElement, "setBatteryLevel",
                              Q_ARG(QVariant, message));
}

void UIHandler::setMainState(QString state){
    QVariant message = state;
    QMetaObject::invokeMethod(rootElement, "setMainState",
                              Q_ARG(QVariant, message));
}

void UIHandler::showInfoMessage(QString text){
    QVariant message = text;
    QMetaObject::invokeMethod(rootElement, "showInfoMessage",
                              Q_ARG(QVariant, message));
}

void UIHandler::cancelViewerToggle(){
    QMetaObject::invokeMethod(rootElement, "cancelViewerToggle");
}
