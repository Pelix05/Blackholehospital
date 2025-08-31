QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SmartMedicalDB.cpp \
    appointment.cpp \
    appointmentlistpage.cpp \
    attendancepage.cpp \
    casedialog.cpp \
    dataanalysispage.cpp \
    databasemanager.cpp \
    doctordetial.cpp \
    doctorplatform.cpp \
    doctorprofilepage.cpp \
    doctorwindow.cpp \
    editprofile.cpp \
    forgotpasswordwidget.cpp \
    healthyselfcheck.cpp \
    hospitalization.cpp \
    instruction.cpp \
    main.cpp \
    loginwidget.cpp \
    medicalrecord.cpp \
    medicinesearch.cpp \
    patientdetailpage.cpp \
    patientinfo.cpp \
    patientmainwindow.cpp \
    prescription.cpp \
    prescriptionpage.cpp \
    recharge.cpp \
    registerpage.cpp \
    registerwidget.cpp

HEADERS += \
    SmartMedicalDB.h \
    appointment.h \
    appointmentlistpage.h \
    attendancepage.h \
    casedialog.h \
    dataanalysispage.h \
    databasemanager.h \
    doctordetial.h \
    doctorplatform.h \
    doctorprofilepage.h \
    doctorwindow.h \
    editprofile.h \
    forgotpasswordwidget.h \
    healthyselfcheck.h \
    hospitalization.h \
    instruction.h \
    loginwidget.h \
    medicalrecord.h \
    medicinesearch.h \
    patientdetailpage.h \
    patientinfo.h \
    patientmainwindow.h \
    personalprofile.h \
    prescription.h \
    prescriptionpage.h \
    recharge.h \
    registerpage.h \
    registerwidget.h

FORMS += \
    appointment.ui \
    appointmentlistpage.ui \
    attendancepage.ui \
    casedialog.ui \
    dataanalysispage.ui \
    doctordetial.ui \
    doctorplatform.ui \
    doctorprofilepage.ui \
    doctorwindow.ui \
    editprofile.ui \
    forgotpasswordwidget.ui \
    healthyselfcheck.ui \
    hospitalization.ui \
    instruction.ui \
    loginwidget.ui \
    medicalrecord.ui \
    medicinesearch.ui \
    patientdetailpage.ui \
    patientinfo.ui \
    patientmainwindow.ui \
    prescription.ui \
    prescriptionpage.ui \
    recharge.ui \
    registerpage.ui \
    registerwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/resources.qrc

DISTFILES +=
