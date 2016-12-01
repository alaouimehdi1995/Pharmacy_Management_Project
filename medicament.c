#include"fonctions.h"

int nombre_medicaments(medicament *liste){
	if (liste==NULL)
		return 0;
	else{
		int i=0;
		medicament *ptr=liste;
		while (ptr!=NULL){
			i+=1;
			ptr=ptr->suivant;
		}
		return i;
	}
}
medicament * load_medicaments_fromFile(char *nom_fichier){
	FILE *fichier=NULL;
	fichier=fopen(nom_fichier,"rb");
	if(fichier==NULL){
		printf("  == Erreur ==========================================================\n");
		printf("  #                                                                  #\n");
		printf("  #   Le fichier contenant les données sauvegardées est inexistant   #\n");
		printf("  #                                                                  #\n");
		printf("  ====================================================================\n\n\n");
		sleep(1);
		return NULL;
	}
	else{
		printf("-- Chargement des médicaments réussi --\n");
		sleep(1);
		medicament *pointeur=NULL, *precedent=NULL,*tete=NULL;
		if(feof(fichier)==0){
			tete=(medicament *)malloc(sizeof(medicament));
			fread (tete, sizeof(medicament),1, fichier);
			precedent=tete;
			pointeur=tete;
		}
		while(pointeur->suivant!=NULL){
			pointeur=(medicament *)malloc(sizeof(medicament));
			fread (pointeur, sizeof(medicament),1, fichier);
			precedent->suivant=pointeur;
			precedent=pointeur;
		}
		pointeur->suivant=NULL;
		fclose(fichier);
		return tete;
	}
}
void write_medicaments(char *nom_fichier,medicament * Liste_medicaments){
	FILE *fichier=fopen(nom_fichier,"wb");
	if(fichier==NULL){
		mkdir("data/", 0777);
		fichier=fopen(nom_fichier,"wb+");
	}
	if(fichier==NULL){
		printf("  == Erreur ==========================================================\n");
		printf("  #                                                                  #\n");
		printf("  #                  impossible de créer le fichier                  #\n");
		printf("  #                                                                  #\n");
		printf("  ====================================================================\n\n\n");
	}
	else{
		medicament *pointeur=Liste_medicaments;
		while(pointeur!=NULL){
			fwrite (pointeur, sizeof(medicament),1, fichier);
			pointeur=pointeur->suivant;
		}
		printf("--- Modifications enregistrées ---\n");
		fclose(fichier);
	}
}
medicament * insertion_medicament(medicament *Liste_medicaments,medicament *m){
	if(Liste_medicaments==NULL)
		Liste_medicaments=m;
	else{
		if(strcmp(Liste_medicaments->nom,m->nom)>=0){
			m->suivant=Liste_medicaments;
			Liste_medicaments=m;
		}
		else{
			medicament *pointeur=Liste_medicaments,*precedent=NULL;
			while(pointeur !=NULL && strcmp(pointeur->nom,m->nom)<0){
				precedent=pointeur;
				pointeur=pointeur->suivant;
			}
			if(pointeur==NULL){
				precedent->suivant=m;
			}
			else{
				m->suivant=pointeur;
				precedent->suivant=m;
			}	
		}
	}
	return Liste_medicaments;
}
medicament * inserer_medicament(medicament *Liste_medicaments,fournisseur **l){//N'ajoute un medicament que si le fournisseur existe
	fournisseur *liste=*l;
	int choix;
	medicament *m=(medicament *)malloc(sizeof(medicament));
	printf("Entrer le code du medicament: ");
	scanf("%d",&m->code);
	printf("Entrer le nom du medicament: ");
	scanf("%s",&m->nom);
	printf("Entrer le fournisseur par defaut du medicament: ");
	scanf("%s",&m->fournisseur_par_defaut);
	while(fournisseur_existant(liste, m->fournisseur_par_defaut)==0){
		printf("Erreur, ce fournisseur n'existe pas parmi votre liste de fournisseurs, voulez-vous l'ajouter ?(1/0): ");
		scanf("%d",&choix);
		if(choix==0){
			printf("Entrer le fournisseur par defaut du medicament: ");
			scanf("%s",&m->fournisseur_par_defaut);
		}
		else{
			fournisseur *c=(fournisseur *)malloc(sizeof(fournisseur));
			strcpy(c->nom,m->fournisseur_par_defaut);
			c->nb_medicaments=0;
			c->liste_medicaments=NULL;
			c->suivant=NULL;
			liste=inserer_fournisseur(liste,c);
			printf("Fournisseur ajouté avec succes\n");
			*l=liste;
		}
	}
	printf("Entrer la quantité actuelle de %s disponible au stock: ",m->nom);
	scanf("%d",&m->qte_stock);
	printf("Entrer la quantité minimale de %s au stock: ",m->nom);
	scanf("%d",&m->qte_a_signaler);
	printf("Entrer la quantité de %s à commander automatiquement: ",m->nom);
	scanf("%d",&m->qte_a_commander);
	if(m->qte_stock<=m->qte_a_signaler){
		commande *liste_commandes=NULL;
		char nom_fichier[5],nom_dossier[12];
		int temp1,temp2;
		capture_date(&temp1,&temp2);
		sprintf(nom_fichier,"%d.bin",temp1);
		sprintf(nom_dossier,"%d/",temp2);
		strcat(nom_dossier,nom_fichier);
		liste_commandes=load_commande_fromFile(nom_dossier);
		inserer_commande(&liste_commandes,init_commande_auto(m));
		write_commande(liste_commandes,nom_dossier);
	}
	m->suivant=NULL;
	if(Liste_medicaments==NULL)
		Liste_medicaments=m;
	else{
		if(strcmp(Liste_medicaments->nom,m->nom)>=0){
			m->suivant=Liste_medicaments;
			Liste_medicaments=m;
		}
		else{
			medicament *pointeur=Liste_medicaments,*precedent=NULL;
			while(pointeur !=NULL && strcmp(pointeur->nom,m->nom)<0){
				precedent=pointeur;
				pointeur=pointeur->suivant;
			}
			if(pointeur==NULL){
				precedent->suivant=m;
			}
			else{
				m->suivant=pointeur;
				precedent->suivant=m;
			}	
		}
	}
	return Liste_medicaments;
}
medicament * inserer_medicament_nom(medicament *Liste_medicaments,fournisseur **l,char *nom){//N'ajoute un medicament que si le fournisseur existe
	fournisseur *liste=*l;
	int choix;
	medicament *m=(medicament *)malloc(sizeof(medicament));
	printf("Entrer le code du medicament: ");
	scanf("%d",&m->code);
	strcpy(m->nom,nom);
	printf("Entrer le fournisseur par defaut du medicament: ");
	scanf("%s",&m->fournisseur_par_defaut);
	while(fournisseur_existant(liste, m->fournisseur_par_defaut)==0){
		printf("Erreur, ce fournisseur n'existe pas parmi votre liste de fournisseurs, voulez-vous l'ajouter ?(1/0): ");
		scanf("%d",&choix);
		if(choix==0){
			printf("Entrer le fournisseur par defaut du medicament: ");
			scanf("%s",&m->fournisseur_par_defaut);
		}
		else{
			fournisseur *c=(fournisseur *)malloc(sizeof(fournisseur));
			strcpy(c->nom,m->fournisseur_par_defaut);
			c->nb_medicaments=0;
			c->liste_medicaments=NULL;
			c->suivant=NULL;
			liste=inserer_fournisseur(liste,c);
			printf("Fournisseur ajouté avec succes\n");
			*l=liste;
		}
	}
	printf("Entrer la quantité actuelle de %s disponible au stock: ",m->nom);
	scanf("%d",&m->qte_stock);
	printf("Entrer la quantité minimale de %s au stock: ",m->nom);
	scanf("%d",&m->qte_a_signaler);
	printf("Entrer la quantité de %s à commander automatiquement: ",m->nom);
	scanf("%d",&m->qte_a_commander);
	if(m->qte_stock<=m->qte_a_signaler){
		commande *liste_commandes=NULL;
		char nom_fichier[5],nom_dossier[12];
		int temp1,temp2;
		capture_date(&temp1,&temp2);
		sprintf(nom_fichier,"%d.bin",temp1);
		sprintf(nom_dossier,"%d/",temp2);
		strcat(nom_dossier,nom_fichier);
		liste_commandes=load_commande_fromFile(nom_dossier);
		inserer_commande(&liste_commandes,init_commande_auto(m));
		write_commande(liste_commandes,nom_dossier);
	}
	m->suivant=NULL;
	if(Liste_medicaments==NULL)
		Liste_medicaments=m;
	else{
		if(strcmp(Liste_medicaments->nom,m->nom)>=0){
			m->suivant=Liste_medicaments;
			Liste_medicaments=m;
		}
		else{
			medicament *pointeur=Liste_medicaments,*precedent=NULL;
			while(pointeur !=NULL && strcmp(pointeur->nom,m->nom)<0){
				precedent=pointeur;
				pointeur=pointeur->suivant;
			}
			if(pointeur==NULL){
				precedent->suivant=m;
			}
			else{
				m->suivant=pointeur;
				precedent->suivant=m;
			}	
		}
	}
	return Liste_medicaments;
}
medicament * inserer_medicament_pour_fournisseur(fournisseur *c,fournisseur **l, medicament **me){
	//fonction qui n'insere un medicament dans liste que s'il existe dans liste_m
	fournisseur *liste_f=*l;
	medicament *Liste_medicaments=c->liste_medicaments,*Liste_m=*me;
	char nom[50];
	int choix;
	int existe=0;
	medicament *m,*m2=NULL;
	printf("Entrer le nom d'un medicament valide à inserer: ");
	scanf("%s",&nom);
	m2=chercher_medicament(Liste_m,nom);
	while(m2==NULL){
		printf("Erreur, ce médicament est inexistant, voulez-vous l'ajouter à votre liste de médicaments ?(1/0): ");
		scanf("%d",&choix);
		if(choix==0){
			m2=NULL;
			printf("Entrer le nom d'un medicament valide à inserer: ");
			scanf("%s",&nom);
			m2=chercher_medicament(Liste_m,nom);
		}
		else{
			Liste_m=inserer_medicament_nom(Liste_m,l,nom);
			*me=Liste_m;
			m2=chercher_medicament(Liste_m,nom);	
		}
	}
	m=(medicament *)malloc(sizeof(medicament));
	*m=*m2;
	m->suivant=NULL;
	if(Liste_medicaments==NULL){
		Liste_medicaments=m;
	}
	else{
		if(strcmp(Liste_medicaments->nom,m->nom)>0){
			m->suivant=Liste_medicaments;
			Liste_medicaments=m;
		}
		else if(strcmp(Liste_medicaments->nom,m->nom)<0){
			medicament *pointeur=Liste_medicaments,*precedent=NULL;
			while(pointeur !=NULL && strcmp(pointeur->nom,m->nom)<0){
				printf("%s\n",pointeur->nom);
				precedent=pointeur;
				pointeur=pointeur->suivant;
			}
			if(pointeur==NULL){
				precedent->suivant=m;
			}
			else if(strcmp(pointeur->nom,m->nom)>0){
				m->suivant=pointeur;
				precedent->suivant=m;
			
			}	
		}
	}
	return Liste_medicaments;
}
void modifier_medicament(medicament *m,fournisseur *liste){
	if(m!=NULL){
		printf("Modification du médicament %s :\n",m->nom);
		do{
			printf("Entrer le fournisseur par defaut du medicament: ");
			scanf("%s",&m->fournisseur_par_defaut);
			//while(le fournisseur ne figure pas parmi la liste des fournisseurs);
		}while(fournisseur_existant(liste, m->fournisseur_par_defaut)==0);
		//ce medicament ne figure pas dans la liste des medicaments de ce fournisseur, voulez vous l'ajouter ?
		printf("Entrer la quantité actuelle de %s disponible au stock: ",m->nom);
		scanf("%d",&m->qte_stock);
		printf("Entrer la quantité minimale de %s au stock: ",m->nom);
		scanf("%d",&m->qte_a_signaler);
		printf("Entrer la quantité de %s à commander automatiquement: ",m->nom);
		scanf("%d",&m->qte_a_commander);
		if(m->qte_stock<=m->qte_a_signaler){
			commande *liste_commandes=NULL;
			char nom_fichier[5],nom_dossier[12];
			int temp1,temp2;
			capture_date(&temp1,&temp2);
			sprintf(nom_fichier,"%d.bin",temp1);
			sprintf(nom_dossier,"%d/",temp2);
			strcat(nom_dossier,nom_fichier);
			liste_commandes=load_commande_fromFile(nom_dossier);
			inserer_commande(&liste_commandes,init_commande_auto(m));
			write_commande(liste_commandes,nom_dossier);
		}
	}
	else
		printf("\n\nMedicament introuvable\n\n\n");
}
medicament * supprimer_medicament(medicament *m,medicament *liste){
if(m!=NULL){
	if(m!=liste){
		medicament *ptr=liste,*precedent=NULL;
		while(ptr!=m){
		precedent=ptr;
		ptr=ptr->suivant;
		}
		precedent->suivant=ptr->suivant;
		free(ptr);
		return liste;
	}
	else{
		medicament *ptr=liste->suivant;
		free(liste);
		return ptr;
	}
printf("Medicament supprimé avec succès");
}
else
printf("Medicament introuvable\n");
return liste;
}
void afficher_medicament(medicament *m){
	if(m!=NULL){
		printf("- Code: %d\n",m->code);
		printf("- Nom: %s\n",m->nom);
		printf("- Fournisseur par défaut: %s\n",m->fournisseur_par_defaut);
		printf("- Quantité disponible au stock: %d\n",m->qte_stock);
		printf("- Quantité minimale avant de commander automatiquement: %d\n",m->qte_a_signaler);
		printf("- Quantité à commander automatiquement lors de l'épuisement du stock: %d\n",m->qte_a_commander);
		printf("==========================================================================\n");
		printf("\n\n\n");
	}
	else{
		printf("\n\n Aucun medicament à afficher..\n\n");
	}
}
void afficher_medicaments(medicament *liste){
	medicament *p=liste;
	while(p!=NULL){
		printf("- Code: %d\n",p->code);
		printf("- Nom: %s\n",p->nom);
		printf("- Fournisseur par défaut: %s\n",p->fournisseur_par_defaut);
		printf("- Quantité disponible au stock: %d\n",p->qte_stock);
		printf("- Quantité minimale avant de commander automatiquement: %d\n",p->qte_a_signaler);
		printf("- Quantité à commander automatiquement lors de l'épuisement du stock: %d\n",p->qte_a_commander);
		printf("==========================================================================\n");
		p=p->suivant;
	}
	printf("\n\n\n");
	if(liste==NULL){
		printf("\n\n Aucun medicament à afficher..\n\n");
	}
}
medicament * chercher_medicament(medicament *liste,char *nom){
	medicament *ptr=liste;
	while(ptr!=NULL){
		if(strcmp(ptr->nom,nom)==0)
			return ptr;
		ptr=ptr->suivant;
	}
	return NULL;
}
