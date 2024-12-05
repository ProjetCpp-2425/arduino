#include "commande.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>

commande::commande()
    : id_commande(0), fournisseur(0), montant_total(0.0f)
{
    date_commande = QDate::currentDate();
    date_livraison = QDate::currentDate();
}

commande::commande(int id_commande, int fournisseur, QDate date_commande, QDate date_livraison, QString liste_articles, float montant_total, QString etat_commande)
    : id_commande(id_commande), fournisseur(fournisseur), date_commande(date_commande), date_livraison(date_livraison),
      liste_articles(liste_articles), montant_total(montant_total), etat_commande(etat_commande)
{
}

bool commande::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO COMMANDE (ID_COMMANDE, FOURNISSEUR, DATE_COMMANDE, DATE_LIVRAISON, LISTE_ARTICLES, MONTANT_TOTAL, ETAT_COMMANDE) "
                  "VALUES (:id_commande, :fournisseur, :date_commande, :date_livraison, :liste_articles, :montant_total, :etat_commande)");

    // Liaison des valeurs dynamiques
    query.bindValue(":id_commande", id_commande);
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":date_commande", date_commande);
    query.bindValue(":date_livraison", date_livraison);
    query.bindValue(":liste_articles", liste_articles);
    query.bindValue(":montant_total", montant_total);
    query.bindValue(":etat_commande", etat_commande);

    if (!query.exec()) {
        qDebug() << "Erreur d'ajout : " << query.lastError().text();
        return false;
    }

    qDebug() << "Commande ajoutée avec succès.";
    return true;
}

QSqlQueryModel* commande::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_COMMANDE, FOURNISSEUR, DATE_COMMANDE, DATE_LIVRAISON, LISTE_ARTICLES, MONTANT_TOTAL, ETAT_COMMANDE FROM COMMANDE");
    return model;
}

bool commande::mettre_a_jour()
{
    QSqlQuery query;
    query.prepare("UPDATE COMMANDE SET FOURNISSEUR = :fournisseur, DATE_COMMANDE = :date_commande, DATE_LIVRAISON = :date_livraison, "
                  "LISTE_ARTICLES = :liste_articles, MONTANT_TOTAL = :montant_total, ETAT_COMMANDE = :etat_commande WHERE ID_COMMANDE = :id_commande");

    query.bindValue(":id_commande", id_commande);
    query.bindValue(":fournisseur", fournisseur);
    query.bindValue(":date_commande", date_commande);
    query.bindValue(":date_livraison", date_livraison);
    query.bindValue(":liste_articles", liste_articles);
    query.bindValue(":montant_total", montant_total);
    query.bindValue(":etat_commande", etat_commande);

    if (!query.exec()) {
        qDebug() << "Erreur de mise à jour :" << query.lastError().text();
        return false;
    }
    return true;
}

bool commande::supprimer(int id_commande)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Commande WHERE id_commande = :id_commande");
    query.bindValue(":id_commande", id_commande);
    return query.exec();
}

QMap<QString, int> commande::statistiquesEtat()
{
    QMap<QString, int> stats;
    QSqlQuery query;
    query.prepare("SELECT etat_commande, COUNT(*) as nombre FROM commande GROUP BY etat_commande");

    if (query.exec()) {
        while (query.next()) {
            QString etat = query.value(0).toString();
            int count = query.value(1).toInt();
            stats.insert(etat, count);
        }
    } else {
        qWarning() << "Erreur lors de l'exécution de la requête de statistiques:" << query.lastError().text();
    }

    return stats;
}

// ------------------ Fonctions panier ----------------------


float commande::calculerPrixTotal()
{
    float total = 0.0f;

    if (panier_articles.isEmpty()) {
        qDebug() << "Le panier est vide. Aucun total à calculer.";
        return total;  // Retourne 0 directement si le panier est vide
    }

    // Ajouter les prix des articles
    for (float prix : panier_prix) {
        if (prix >= 0) {  // Vérifie que chaque prix est valide (optionnel)
            total += prix;
        } else {
            qWarning() << "Attention : Un prix invalide détecté (" << prix << "). Ignoré.";
        }
    }

    qDebug() << "Prix total calculé : " << total;
    return total;
}


void commande::ajouterArticle(const QString& article, float prix)
{
    if (article.isEmpty() || prix <= 0) {
        qDebug() << "Erreur : Nom d'article vide ou prix invalide.";
        return;
    }

    panier_articles.append(article);  // Ajouter l'article à la liste des articles
    panier_prix.append(prix);         // Ajouter le prix à la liste des prix
    qDebug() << "Article ajouté :" << article << ", Prix :" << prix;
}

void commande::viderPanier()
{
    // Vider les listes des articles et des prix
    panier_articles.clear();
    panier_prix.clear();
    qDebug() << "Le panier a été vidé.";
}

QString commande::afficherPanier()
{
    QString panierText = "Articles dans le panier :\n";

    if (panier_articles.isEmpty()) {
        panierText += "Le panier est vide.";
    } else {
        for (int i = 0; i < panier_articles.size(); ++i) {
            panierText += QString::number(i + 1) + ". " + panier_articles[i] + " - " + QString::number(panier_prix[i]) + "€\n";
        }
    }

    qDebug() << "Contenu du panier :\n" << panierText;
    return panierText;
}

void commande::supprimerArticle(const QString& article)
{
    if (article.isEmpty()) {
        qDebug() << "Erreur : Nom d'article vide. Impossible de supprimer.";
        return;
    }

    int index = panier_articles.indexOf(article);  // Trouver l'indice de l'article à supprimer
    if (index != -1) {
        panier_articles.removeAt(index);  // Supprimer l'article de la liste
        panier_prix.removeAt(index);      // Supprimer le prix correspondant
        qDebug() << "Article supprimé :" << article;
    } else {
        qDebug() << "Article non trouvé dans le panier :" << article;
    }
}
