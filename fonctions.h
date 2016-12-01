#if defined WIN32
#define CLEAR "cls"
#elif defined __linux
#define CLEAR "clear"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tm tm;
typedef struct medicament;
typedef struct fournisseur;
typedef struct commande;
typedef struct vente;
typedef struct client;
//========================= Structures
typedef struct medicament{
	int code;
	char nom[50];
	char fournisseur_par_defaut[50];
	int qte_stock;
	int qte_a_signaler;
	int qte_a_commander;
	struct medicament* suivant;
}medicament;
//===========================
typedef struct fournisseur{
	char nom[50];
	int nb_medicaments;
	medicament *liste_medicaments;
	struct fournisseur *suivant;
}fournisseur;
//============================
typedef struct commande{
	char  medicament[50];
	char fournisseur[50];
	char client[50];
	char date[70];
	int qte;
	int mode; //0=manuel et 1=automatique
	struct commande *suivant;
}commande;
//=========================
typedef struct client{
	char nom[50];
	struct client *suivant;
}client;
//========================
typedef struct vente{
	char  medicament[50];
	char date[70];
	int qte;
	struct vente *suivant;
}vente;
//======================================================================================================Clients
client * init_client();
client * load_clients_fromFile(char *nom_fichier);
void write_clients(char *nom_fichier,client * Liste_clients);
client * inserer_client(client *liste_clients,client *c);
void afficher_clients(client *liste_clients);
client * modifier_client(client *Liste_clients,client *client);
client * supprimer_client(client *Liste_clients,client *cl);
client * rechercher_client(client *Liste_clients,char *nom);
client * chercher_client(client *liste,char *nom);
//=============================================================================================Fournisseurs
fournisseur * init_fournisseur();
fournisseur * load_fournisseurs_fromFile(char *nom_fichier);
int fournisseur_existant(fournisseur *liste, char *nom);
void write_fournisseurs(char *nom_fichier,fournisseur * Liste_fournisseurs);
fournisseur * inserer_fournisseur(fournisseur *liste_fournisseurs,fournisseur *c);
void afficher_fournisseurs(fournisseur *liste_fournisseurs);
fournisseur * modifier_fournisseur(fournisseur **l,fournisseur *cl,medicament **m);
fournisseur * supprimer_fournisseur(fournisseur *Liste_fournisseurs,fournisseur *cl);
fournisseur * rechercher_fournisseur(fournisseur **l,char *nom,medicament **m);
fournisseur * mise_a_jour(fournisseur *f,medicament *m);
fournisseur * chercher_fournisseur(fournisseur *liste,char *nom);
//===============================================================================================Medicaments
medicament * inserer_medicament(medicament *Liste_medicaments,fournisseur **l);
medicament * inserer_medicament_nom(medicament *Liste_medicaments,fournisseur **l,char *nom);
medicament * inserer_medicament_pour_fournisseur(fournisseur *c,fournisseur **l, medicament **m);
void modifier_medicament(medicament *m,fournisseur *liste);
void afficher_medicaments(medicament *liste);
void afficher_medicament(medicament *m);
medicament * supprimer_medicament(medicament *m,medicament *liste);
medicament * chercher_medicament(medicament *liste,char *nom);
medicament * insertion_medicament(medicament *Liste_medicaments,medicament *m);
medicament * load_medicaments_fromFile(char *nom_fichier);
void write_medicaments(char *nom_fichier,medicament * Liste_medicaments);
int nombre_medicaments(medicament *liste);
//====================================================================================================Menu
void menu_principal(medicament **m,fournisseur **f,client **c);
void menu_clients(medicament **m,fournisseur **f,client **c);
void menu_fournisseurs(medicament **m,fournisseur **f,client **c);
void menu_medicaments(medicament **m,fournisseur **f,client **c);
void menu_commandes(medicament **m,fournisseur **f,client **c);
void menu_ventes(medicament **m,fournisseur **f,client **c);
//=================================================================================================Commande
commande * init_commande_auto(medicament *m);
commande * init_commande_manuelle(char *m,char *f,char *cl,int qte);
commande * commande_manuelle(medicament *liste_m,fournisseur *liste_f,client *liste_c);
void fusion_commandes(commande **l,commande *c_existant,commande *c_nouveau);
commande * chercher_commande(commande *liste,char *medi,char *fourn,char *cli);
void init_date(commande *c);
void inserer_commande(commande **ptr_liste,commande*c);
void capture_date(int *jour_mois,int *annee);
commande *load_commande_fromFile(char *nom_fichier);
void write_commande(commande *liste,char *nom_fichier);
void afficher_commande(commande *liste);
void modifier_commande(commande **l,medicament *liste_m,fournisseur *liste_f,client *liste_c);
void supprimer_commande(commande **l,medicament *liste_m,fournisseur *liste_f,client *liste_c);
//===============================================================================================Vente
vente *load_vente_fromFile(char *nom_fichier);
void write_vente(vente *liste,char *nom_fichier);
void init_date_vente(vente *c);
vente * init_vente(char *nom_medicament,int qte);
void afficher_vente(vente *liste);
void ajouter_vente(medicament *liste_m);
