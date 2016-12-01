#include "fonctions.h"
//les parametres sont des doubles pointeurs !!!
void menu_principal(medicament **m,fournisseur **f,client **c){
	int continuer=1;
	int choix,code;
	char chaine[4];
	while(continuer!=0){
		system(CLEAR);
		printf("\n\n");
		printf("  ====== Bienvenue ================================\n");
		printf("  # 1- Gestion clients                            #\n");
		printf("  # 2- Gestion fournisseurs                       #\n");
		printf("  # 3- Gestion médicaments                        #\n");
		printf("  # 4- Gestion commandes                          #\n");
		printf("  # 5- Gestion ventes                             #\n");
		printf("  #   Appuyer sur n'importe quelle autre touche   #\n");
		printf("  #                  pour quitter                 #\n");
		printf("  =================================================\n");
		scanf("%s",&chaine);
		choix=atoi(chaine);
		switch (choix){
			case 1:
				system(CLEAR);
				menu_clients(m,f,c);
				break;
			case 2:
				system(CLEAR);
				menu_fournisseurs(m,f,c);
				break;
			case 3:
				system(CLEAR);
				menu_medicaments(m,f,c);
				break;
			case 4:
				system(CLEAR);
				menu_commandes(m,f,c);
				break;
			case 5:
				system(CLEAR);
				menu_ventes(m,f,c);
				break;
			default:
				continuer=0;
				break;
		}
	}
}
void menu_clients(medicament **m,fournisseur **f,client **c){
	client *liste_clients=*c;
	fournisseur *liste_fournisseurs=*f;
	medicament *liste_medicaments=*m;
	client *cl;
	int continuer=1;
	int choix,code;
	char chaine[4];
	char nom[50];
	while(continuer!=0){
		system(CLEAR);
		printf("\n\n");
		printf("  ====== Section client: ==========================\n");
		printf("  # 1- Inserer un client                          #\n");
		printf("  # 2- Modifier un client                         #\n");
		printf("  # 3- Chercher un client                         #\n");
		printf("  # 4- Supprimer un client                        #\n");
		printf("  # 5- Afficher  les clients                      #\n");
		printf("  #   Appuyer sur n'importe quelle autre touche   #\n");
		printf("  #                  pour quitter                 #\n");
		printf("  =================================================\n");
		scanf("%s",&chaine);
		choix=atoi(chaine);
		switch (choix){
			case 1:
				do{
					system(CLEAR);
					cl=init_client();
					liste_clients=inserer_client(liste_clients,cl);
					write_clients("data/client.bin",liste_clients);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 2:
				do{
					system(CLEAR);
					printf("Saisir le nom du client à modifier: ");
					scanf("%s",&nom);
					liste_clients=modifier_client(liste_clients,nom);
					write_clients("data/client.bin",liste_clients);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 3:
				do{
					system(CLEAR);
					printf("Saisir le nom du client à rechercher: ");
					scanf("%s",&nom);
					liste_clients=rechercher_client(liste_clients,nom);
					write_clients("data/client.bin",liste_clients);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 4:
				do{
					system(CLEAR);
					printf("Saisir le nom du client à supprimer: ");
					scanf("%s",&nom);
					liste_clients=supprimer_client(liste_clients,chercher_client(liste_clients,nom));
					write_clients("data/client.bin",liste_clients);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 5:
				do{
					system(CLEAR);
					afficher_clients(liste_clients);
					printf("Appuyer sur n'importe quelle touche pour revenir au menu principal  ");
					scanf("%s",&chaine);
					continuer=atoi(chaine);
					continuer=0;
				}while(continuer==1);
				continuer=1;
				break;	
			default:
				continuer=0;
				break;
		}
	}
	*c=liste_clients;
	*m=liste_medicaments;
	*f=liste_fournisseurs;
}
void menu_fournisseurs(medicament **m,fournisseur **f,client **c){
	client *liste_clients=*c;
	fournisseur *liste_fournisseurs=*f;
	medicament *liste_medicaments=*m;
	fournisseur *fo;
	int continuer=1;
	int choix,code;
	char chaine[4];
	char nom[50];
	while(continuer!=0){
		system(CLEAR);
		printf("\n\n");
		printf("  ====== Section fournisseur: =====================\n");
		printf("  # 1- Inserer un fournisseur                     #\n");
		printf("  # 2- Modifier un fournisseur                    #\n");
		printf("  # 3- Chercher un fournisseur                    #\n");
		printf("  # 4- Supprimer un fournisseur                   #\n");
		printf("  # 5- Afficher les fournisseurs                  #\n");
		printf("  #   Appuyer sur n'importe quelle autre touche   #\n");
		printf("  #                  pour quitter                 #\n");
		printf("  =================================================\n");
		scanf("%s",&chaine);
		choix=atoi(chaine);
		switch (choix){
			case 1:
				do{
					system(CLEAR);
					fo=init_fournisseur();
					liste_fournisseurs=inserer_fournisseur(liste_fournisseurs,fo);
					write_fournisseurs("data/fournisseur.bin",liste_fournisseurs);
					write_medicaments("data/medicament.bin",liste_medicaments);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 2:
				do{
					system(CLEAR);
					printf("Saisir le nom du fournisseur à modifier: ");
					scanf("%s",&nom);
					liste_fournisseurs=modifier_fournisseur(&liste_fournisseurs,chercher_fournisseur(liste_fournisseurs,nom),&liste_medicaments);
					write_fournisseurs("data/fournisseur.bin",liste_fournisseurs);
					write_medicaments("data/medicament.bin",liste_medicaments);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 3:
				do{
					system(CLEAR);
					printf("Saisir le nom du fournisseur à rechercher: ");
					scanf("%s",&nom);
					liste_fournisseurs=rechercher_fournisseur(&liste_fournisseurs,nom,&liste_medicaments);
					write_fournisseurs("data/fournisseur.bin",liste_fournisseurs);
					write_medicaments("data/medicament.bin",liste_medicaments);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 4:
				do{
					printf("Saisir le nom du fournisseur à supprimer: ");
					scanf("%s",&nom);
					liste_fournisseurs=supprimer_fournisseur(liste_fournisseurs,chercher_fournisseur(liste_fournisseurs,nom));
					write_fournisseurs("data/fournisseur.bin",liste_fournisseurs);
					write_medicaments("data/medicament.bin",liste_medicaments);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 5:
				do{
					system(CLEAR);
					afficher_fournisseurs(liste_fournisseurs);
					printf("Appuyer sur n'importe quelle touche pour revenir au menu principal  ");
					scanf("%s",&chaine);
					continuer=atoi(chaine);
					continuer=0;
				}while(continuer==1);
				continuer=1;
				break;	
			default:
				continuer=0;
				break;
		}
	}
	*c=liste_clients;
	*m=liste_medicaments;
	*f=liste_fournisseurs;
}
void menu_medicaments(medicament **m,fournisseur **f,client **c){
	client *liste_clients=*c;
	fournisseur *liste_fournisseurs=*f;
	medicament *liste_medicaments=*m;
	medicament *me;
	int continuer=1;
	int choix,code;
	char chaine[4];
	char nom[50];
	while(continuer!=0){
		system(CLEAR);
		printf("\n\n");
		printf("  ====== Section medicament: ======================\n");
		printf("  # 1- Inserer un medicament                      #\n");
		printf("  # 2- Chercher un medicament                     #\n");
		printf("  # 3- Supprimer un medicament                    #\n");
		printf("  # 4- Afficher les medicaments                   #\n");
		printf("  #   Appuyer sur n'importe quelle autre touche   #\n");
		printf("  #                  pour quitter                 #\n");
		printf("  =================================================\n");
		scanf("%s",&chaine);
		choix=atoi(chaine);
		switch (choix){
			case 1:
				do{
					system(CLEAR);
					liste_medicaments=inserer_medicament(liste_medicaments,&liste_fournisseurs);
					write_medicaments("data/medicament.bin",liste_medicaments);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 2:
				do{
					system(CLEAR);
					printf("Saisir le nom du medicament à rechercher: ");
					scanf("%s",&nom);
					modifier_medicament(chercher_medicament(liste_medicaments,nom),liste_fournisseurs);
					write_medicaments("data/medicament.bin",liste_medicaments);
					write_fournisseurs("data/fournisseur.bin",liste_fournisseurs);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 3:
				do{
					system(CLEAR);
					printf("Saisir le nom du medicament à supprimer: ");
					scanf("%s",&nom);
					liste_medicaments=supprimer_medicament(chercher_medicament(liste_medicaments,nom),liste_medicaments);
					write_medicaments("data/medicament.bin",liste_medicaments);
					write_fournisseurs("data/fournisseur.bin",liste_fournisseurs);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 4:
				do{
					system(CLEAR);
					afficher_medicaments(liste_medicaments);
					printf("Appuyer sur n'importe quelle touche pour revenir au menu principal  ");
					scanf("%s",&chaine);
					continuer=atoi(chaine);
					continuer=0;
				}while(continuer==1);
				continuer=1;
				break;	
			default:
				continuer=0;
				break;
		}
	}
	*c=liste_clients;
	*m=liste_medicaments;
	*f=liste_fournisseurs;
}
void menu_commandes(medicament **m,fournisseur **f,client **c){
	client *liste_clients=*c;
	fournisseur *liste_fournisseurs=*f;
	medicament *liste_medicaments=*m;
	commande *liste_commandes=NULL;
	char nom_fichier[5],nom_dossier[17];
	int continuer=1,temp1,temp2;
	int choix,code;
	char chaine[4];
	char nom[50];
	while(continuer!=0){
		system(CLEAR);
		printf("\n\n");
		printf("  ====== Section commandes: =======================\n");
		printf("  # 1- Inserer une commande                       #\n");
		printf("  # 2- Afficher les commandes d'aujourd'hui       #\n");
		printf("  # 3- Afficher les commandes d'un jour donné     #\n");
		printf("  # 4- Modifier une commande d'aujourd'hui        #\n");
		printf("  # 5- Supprimer une commande                     #\n");
		printf("  #   Appuyer sur n'importe quelle autre touche   #\n");
		printf("  #                  pour quitter                 #\n");
		printf("  =================================================\n");
		scanf("%s",&chaine);
		choix=atoi(chaine);
		switch (choix){
			case 1:
				do{	
					capture_date(&temp1,&temp2);
					sprintf(nom_fichier,"%d.bin",temp1);
					sprintf(nom_dossier,"data/%d/",temp2);
					strcat(nom_dossier,nom_fichier);
					liste_commandes=load_commande_fromFile(nom_dossier);
					commande *com=commande_manuelle(liste_medicaments,liste_fournisseurs,liste_clients);
					inserer_commande(&liste_commandes,com);
					write_commande(liste_commandes,nom_dossier);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 2:
				do{	
					system(CLEAR);
					capture_date(&temp1,&temp2);
					sprintf(nom_fichier,"%d.bin",temp1);
					sprintf(nom_dossier,"data/%d/",temp2);
					strcat(nom_dossier,nom_fichier);
					liste_commandes=load_commande_fromFile(nom_dossier);
					afficher_commande(liste_commandes);
					printf("Appuyer sur n'importe quelle touche pour revenir au menu principal  ");
					scanf("%s",&chaine);
					continuer=atoi(chaine);
					continuer=0;
				}while(continuer==1);
				continuer=1;
				break;	
	//			break;
			case 3:
				do{
					system(CLEAR);
					printf("Entrer le jour du mois: ");
					scanf("%d",&temp1);
					printf("Entrer le numéro du mois: ");
					scanf("%d",&temp2);
					sprintf(nom_fichier,"%d%d.bin",temp1,temp2);
					printf("Entrer l'année: ");
					scanf("%d",&temp2);
					sprintf(nom_dossier,"data/%d/",temp2);
					strcat(nom_dossier,nom_fichier);
					liste_commandes=load_commande_fromFile(nom_dossier);
					afficher_commande(liste_commandes);
					printf("Appuyer sur n'importe quelle touche pour revenir au menu principal  ");
					scanf("%s",&chaine);
					continuer=atoi(chaine);
					continuer=0;
				}while(continuer==1);
				continuer=1;
				break;	
	//			break;
			case 4:
				do{	
					system(CLEAR);
					capture_date(&temp1,&temp2);
					sprintf(nom_fichier,"%d.bin",temp1);
					sprintf(nom_dossier,"data/%d/",temp2);
					strcat(nom_dossier,nom_fichier);
					liste_commandes=load_commande_fromFile(nom_dossier);
					afficher_commande(liste_commandes);
					printf("\n\n\n");
					modifier_commande(&liste_commandes,liste_medicaments,liste_fournisseurs,liste_clients);
					afficher_commande(liste_commandes);
					write_commande(liste_commandes,nom_dossier);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 5:
				system(CLEAR);
				capture_date(&temp1,&temp2);
				sprintf(nom_fichier,"%d.bin",temp1);
				sprintf(nom_dossier,"data/%d/",temp2);
				strcat(nom_dossier,nom_fichier);
				liste_commandes=load_commande_fromFile(nom_dossier);
				supprimer_commande(&liste_commandes,liste_medicaments,liste_fournisseurs,liste_clients);
				write_commande(liste_commandes,nom_dossier);
				continuer=1;
				break;
			default:
				continuer=0;
				break;
		}
	}
	*c=liste_clients;
	*m=liste_medicaments;
	*f=liste_fournisseurs;
}
void menu_ventes(medicament **m,fournisseur **f,client **c){
	client *liste_clients=*c;
	fournisseur *liste_fournisseurs=*f;
	medicament *liste_medicaments=*m;
	vente *liste_ventes=NULL;
	char nom_fichier[6],nom_dossier[18];
	int continuer=1,temp1,temp2;
	int choix,code;
	char chaine[4];
	char nom[50];
	while(continuer!=0){
		system(CLEAR);
		printf("\n\n");
		printf("  ====== Section ventes: ==========================\n");
		printf("  # 1- Inserer une vente                          #\n");
		printf("  # 2- Afficher les ventes d'aujourd'hui          #\n");
		printf("  # 3- Afficher les ventes d'un jour donné        #\n");
		printf("  #   Appuyer sur n'importe quelle autre touche   #\n");
		printf("  #                  pour quitter                 #\n");
		printf("  =================================================\n");
		scanf("%s",&chaine);
		choix=atoi(chaine);
		switch (choix){
			case 1:
				do{
					system(CLEAR);
					ajouter_vente(liste_medicaments);
					do{
						printf("Continuer ?(1/0) ");
						scanf("%d",&continuer);
					}while(continuer!=0 && continuer!=1);
				}while(continuer==1);
				continuer=1;
				break;
			case 2:
				system(CLEAR);
				capture_date(&temp1,&temp2);
				sprintf(nom_fichier,"%d_.bin",temp1);
				sprintf(nom_dossier,"data/%d/",temp2);
				strcat(nom_dossier,nom_fichier);
				liste_ventes=load_vente_fromFile(nom_dossier);
				afficher_vente(liste_ventes);
				printf("Appuyer sur n'importe quel touche pour continuer\n");
				scanf("%d",&continuer);
				continuer=1;
				break;
			case 3:
				system(CLEAR);
				printf("Entrer le jour du mois: ");
				scanf("%d",&temp1);
				printf("Entrer le numéro du mois: ");
				scanf("%d",&temp2);
				sprintf(nom_fichier,"%d%d_.bin",temp1,temp2);
				printf("Entrer l'année: ");
				scanf("%d",&temp2);
				sprintf(nom_dossier,"data/%d/",temp2);
				strcat(nom_dossier,nom_fichier);
				liste_ventes=load_vente_fromFile(nom_dossier);
				afficher_vente(liste_ventes);
				printf("Appuyer sur n'importe quel touche pour continuer\n");
				scanf("%d",&continuer);
				continuer=1;	
				break;
			default:
				continuer=0;
				break;
		}
	}
	*c=liste_clients;
	*m=liste_medicaments;
	*f=liste_fournisseurs;
}
