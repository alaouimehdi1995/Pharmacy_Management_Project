#include<stdio.h>
#include<stdlib.h>
#include"fonctions.h"
/*
Nombre total net de lignes de code (celle-ci incluse):2041
*/
int main(){
	//INITIALISATION DES LISTES =================
	fournisseur *liste_fournisseurs=NULL;
	client *liste_clients=NULL;
	commande *liste_commandes=NULL;
	vente *liste_ventes=NULL;
	medicament *liste_medicaments=NULL;
	//CHARGEMENT DES LISTES DEPUIS LES FICHIERS=======================================
	system(CLEAR);
	liste_medicaments=load_medicaments_fromFile("data/medicament.bin");
	liste_fournisseurs=load_fournisseurs_fromFile("data/fournisseur.bin");
	liste_clients=load_clients_fromFile("data/client.bin");
	//AFFICHAGE DU MENU PRINCIPAL ================================================
	menu_principal(&liste_medicaments,&liste_fournisseurs,&liste_clients);
	return 0;
}