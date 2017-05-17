#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T14:59:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix:TARGET = ../../bin/MobileDesignTemplate
win32:TARGET = ../../../dist/bin/MobileDesignTemplate
TEMPLATE = app


SOURCES +=  main.cpp\
            splashscreen.cpp \
            homescreen.cpp \
            registerscreen.cpp \
            settingscreen.cpp \
            widgets/vlabel.cpp \
            aboutscreen.cpp \
            imagecropper/imagecropper.cpp \
            avatarscreen.cpp \
            layout/flowlayout.cpp \
            locationscreen.cpp \
            glassscreen.cpp \
            widgets/dragwidget.cpp \
            widgets/vtoolbutton.cpp \
            widgets/vpushbutton.cpp \
            widgets/vcheckbox.cpp \
            widgets/vradiobutton.cpp \
            widgets/vswitchbutton.cpp

HEADERS  += splashscreen.h \
            homescreen.h \
            registerscreen.h \
            settingscreen.h \
            widgets/vlabel.h \
            aboutscreen.h \
            imagecropper/imagecropper.h \
            imagecropper/imagecropper_e.h \
            imagecropper/imagecropper_p.h \
            avatarscreen.h \
            layout/flowlayout.h \
            locationscreen.h \
            glassscreen.h \
            widgets/dragwidget.h \
            widgets/vtoolbutton.h \
            widgets/vpushbutton.h \
            widgets/vcheckbox.h \
            widgets/vradiobutton.h \
            widgets/vswitchbutton.h

FORMS    += splashscreen.ui \
            homescreen.ui \
            registerscreen.ui \
            settingscreen.ui \
            aboutscreen.ui \
            avatarscreen.ui \
            locationscreen.ui \
            glassscreen.ui

RESOURCES += \
    design_res.qrc

win32:RC_FILE = DesignTemplate.rc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
