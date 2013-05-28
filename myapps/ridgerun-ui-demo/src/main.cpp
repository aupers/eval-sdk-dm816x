#include <QtGui/QApplication>
#include <QVariant>
#include <QtDeclarative>
#include "uihandler.h"

#ifdef __ARMEL__
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <video/davincifb_ioctl.h>
#include <QWSServer>

/* This function set up the color key in the Davinci */
void fb_init (void){
    int fbfd;
    char enable = 1;

    vpbe_bitmap_blend_params_t blendparam;
    vpbe_backg_color_t backg;

    blendparam.colorkey = 0xf81f;
    blendparam.enable_colorkeying = 1;
    blendparam.bf = 0;

    backg.clut_select = 0;
    backg.color_offset = 255;

    fbfd = open("/dev/fb0",O_RDWR);
    if (fbfd < 0){
        perror("Failed to open the framebuffer device");
        exit(-1);
    }

    if (ioctl(fbfd,FBIO_ENABLE_DISABLE_WIN,&enable) < 0){
        perror("Failed to enable the OSD window");
        exit(-1);
    }

    if (ioctl(fbfd,FBIO_SET_BACKG_COLOR,&backg) < 0){
        perror("Failed to enable the OSD window: set background color");
        exit(-1);
    }

    if (ioctl(fbfd,FBIO_SET_BITMAP_BLEND_FACTOR,&blendparam) < 0){
        perror("Failed to set the blending factor");
        exit(-1);
    }

    close(fbfd);
}
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Bind QML file:
    QDeclarativeView view;
    view.setSource(QUrl("qrc:/main"));

    //Obtain root element and logic-making things
    QObject *rootElement = (QObject*) view.rootObject();

    //Connect quit signal:
    QObject::connect((QObject*) view.engine(), SIGNAL(quit()),(QObject*) QCoreApplication::instance(), SLOT(quit()), Qt::DirectConnection);

    //Create a handler
    UIHandler* handler;
    handler = new UIHandler(rootElement);

    //Create a timer for status bar updates
    QTimer *statusBarUpdater = new QTimer();
    QObject::connect(statusBarUpdater, SIGNAL(timeout()), handler, SLOT(updateStatusBar()));
    statusBarUpdater->start(1000);

    //Start the show:
#ifdef __ARMEL__
    if (!QWSServer::mouseHandler())
            qFatal("No mouse handler installed");
    view.setWindowFlags(Qt::FramelessWindowHint);
#endif
    view.show();

    //Start up event system:
    return app.exec();

}
