#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QImage>
#include <QDir>
#include <QFileInfo>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "commande.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); // Constructeur
    ~MainWindow();                                  // Destructeur

private slots:
    // Gestion Arduino
    bool connectToArduino();
      void readFromArduino();
      void onFlameDetected();
      void onNoFlameDetected();
      void checkFlameStatus();
    // Gestion des commandes
    void on_ajouter_clicked();
    void on_afficher_clicked();
    void on_mettre_a_jour_clicked();
    void on_supprimer_clicked();
    void on_pdf_clicked();
    void on_lineEdit_recherche_cursorPositionChanged();
    void on_comboBox_3_activated(int index);
    void on_statistique_clicked();
    void on_ajouterArticle_clicked();
    void on_viderPanier_clicked();
    void on_afficherPanier_clicked();
    void on_calculerPrixTotal_clicked();
    void on_supprimerArticleButton_clicked();
    float getPrixFromDatabase(const QString &article);
    // Obtenir le prix d'un article depuis la base

private:
    Ui::MainWindow *ui;

    // Gestion Arduino
    QSerialPort *arduino;             // Gestionnaire du port série
    QString arduinoPortName;          // Nom du port Arduino
      QTimer *flameCheckTimer;  // Timer to check flame status periodically
      bool flameDetected;
      void toggleBuzzer(bool state);//
private:
    bool interfaceReady; // Indique si l'interface Qt est prête
    // Se connecter à l'Arduino

    // Gestion des commandes
    commande commandeInstance;
    QSqlTableModel *commandeModel;    // Modèle pour les commandes
};

#endif // MAINWINDOW_H
