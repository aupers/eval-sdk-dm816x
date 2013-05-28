TARGET= ridgerun-ui-demo

QT += declarative dbus core

CONFIG += qdbus link_pkconfig debug

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    uihandler.cpp

HEADERS += \
    uihandler.h

RESOURCES += \
    qmlresources.qrc

OTHER_FILES += qml/ridgerun-ui-demo/ConfigPane.qml \
	qml/ridgerun-ui-demo/Button.qml \
	qml/ridgerun-ui-demo/CustomRadioButton.qml \
	qml/ridgerun-ui-demo/InfoMessage.qml \
	qml/ridgerun-ui-demo/main.qml \
	qml/ridgerun-ui-demo/MainPane.qml \
	qml/ridgerun-ui-demo/SideBar.qml \
	qml/ridgerun-ui-demo/Slider.qml \
	qml/ridgerun-ui-demo/StatusBar.qml \
	qml/ridgerun-ui-demo/TabButton.qml \
	qml/ridgerun-ui-demo/ToggleInfoMessage.qml \
	qml/ridgerun-ui-demo/ToggleButton.qml

target.path = /usr/bin

INSTALLS = target

