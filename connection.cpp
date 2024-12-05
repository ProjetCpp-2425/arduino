#include "connection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnect() {
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("mytest"); // DSN de votre base de données
    db.setUserName("system");      // Nom d'utilisateur
    db.setPassword("emnaemna");   // Mot de passe

    if (db.open()) {
        test = true;

        // Créer la table Commande si elle n'existe pas
        QSqlQuery query;
        bool ok = query.exec("CREATE TABLE IF NOT EXISTS Commande (id_commande INT)");

        if (!ok) {
            qDebug() << "Erreur de création de la table : " << query.lastError().text();
        } else {
            qDebug() << "Table Commande créée avec succès.";
        }
    } else {
        qDebug() << "Erreur de connexion : " << db.lastError().text();
    }

    return test;
}
