#ifndef COMMANDE_H
#define COMMANDE_H

#include "qsqlquerymodel.h"
#include <QString>
#include <QDate>
#include <QList>
#include <QMap>

class commande
{
private:

    int id_commande;         // ID de la commande
    int fournisseur;         // ID du fournisseur
    QDate date_commande;     // Date de la commande
    QDate date_livraison;   // Date de livraison
    QString liste_articles;  // Détail sous forme de texte
    float montant_total;     // Montant total de la commande
    QString etat_commande;   // Etat de la commande

    // Attributs pour gérer le panier
    QList<QString> panier_articles; // Liste des noms d'articles
    QList<float> panier_prix;


public:
    // Constructeurs
    commande();
    commande(int id_commande, int fournisseur, QDate date_commande, QDate date_livraison, QString liste_articles, float montant_total, QString etat_commande);

    // Méthodes de gestion de commande
    bool ajouter();
    bool mettre_a_jour();
    bool supprimer(int id_commande);
    QSqlQueryModel* afficher();
    QMap<QString, int> statistiquesEtat();



    // Méthodes panier


        void ajouterArticle(const QString& article, float prix);  // Ajouter un article
        void viderPanier();  // Vider le panier
        QString afficherPanier();  // Afficher le contenu du panier
        void supprimerArticle(const QString& article);  // Supprimer un article par son nom


    // Setters et Getters
    void setIdCommande(int id) { id_commande = id; }  // Setter pour id_commande
    int getIdCommande() const { return id_commande; }  // Getter pour id_commande
    int getPanierArticles();
    float calculerPrixTotal();


    int getFournisseur() const { return fournisseur; }
    QDate getDateCommande() const { return date_commande; }
    QDate getDateLivraison() const { return date_livraison; }
    QString getListeArticles() const { return liste_articles; }
    float getMontantTotal() const { return montant_total; }
    QString getEtatCommande() const { return etat_commande; }
    QList<QString> getPanierArticles() const { return panier_articles; }


};

#endif // COMMANDE_H
