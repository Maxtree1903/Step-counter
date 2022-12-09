QT      += core gui
QT      += sensors
QT      += core
QT      += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    stepcounteralgo.cpp

HEADERS += \
    mainwindow.h \
    stepcounteralgo.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


STATECHARTS +=

DISTFILES += \
    ../AndroidManifest/AndroidManifest.xml \
    ../AndroidManifest/AndroidManifest.xml \
    ../AndroidManifest/build.gradle \
    ../AndroidManifest/build.gradle \
    ../AndroidManifest/gradle.properties \
    ../AndroidManifest/gradle/wrapper/gradle-wrapper.jar \
    ../AndroidManifest/gradle/wrapper/gradle-wrapper.properties \
    ../AndroidManifest/gradlew \
    ../AndroidManifest/gradlew.bat \
    ../AndroidManifest/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/../AndroidManifest
}
