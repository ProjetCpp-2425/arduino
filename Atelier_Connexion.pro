#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT += sql
QT += widgets sql printsupport
QT += core gui serialport



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# Activer les avertissements pour les fonctionnalités Qt obsolètes
DEFINES += QT_DEPRECATED_WARNINGS

# Vous pouvez désactiver les API obsolètes avant une certaine version de Qt :
# Décommentez la ligne suivante si nécessaire.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # désactive toutes les API obsolètes avant Qt 6.0.0

# Activer le support C++11 (ou plus récent si nécessaire)
CONFIG += c++11

# Fichiers sources
SOURCES += \
    commande.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp

# Fichiers d'en-têtes
HEADERS += \
    commande.h \
    mainwindow.h \
    connection.h

# Fichiers UI
FORMS += \
    mainwindow.ui

# Règles par défaut pour le déploiement
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Si vous souhaitez inclure des ressources spécifiques au PDF, ajoutez-les ici
# Par exemple, les ressources peuvent inclure des images, des logos ou des fichiers nécessaires pour générer le PDF
# RESOURCES += ressources.qrc
