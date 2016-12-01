#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"
commande * chercher_commande(commande *liste,char *medi,char *fourn,char *cli){
	commande *c=liste;
	while(c!=NULL && (strcmp(c->medicament,medi)!=0 || strcmp(c->fournisseur,fourn)!=0 || strcmp(c->client,cli)!=0)){
		c=c->suivant;
	}
	return c;
}
void fusion_commandes(commande **l,commande *c_existant,commande *c_nouveau){
	commande *liste=*l;
	commande *c=liste,*prec=liste;
	while(c!=c_existant){
		prec=c;
		c=c->suivant;
	}
	if(c!=NULL){
		c_nouveau->qte+=c_existant->qte;
		if(c==liste){
			liste=liste->suivant;
			free(c);
		}
		else{
			prec->suivant=c->suivant;
			free(c);
		}
		inserer_commande(&liste,c_nouveau);
	}
	*l=liste;
}
commande * init_commande_auto(medicament *m){
	commande *c=(commande *)malloc(sizeof(commande));
	strcpy(c->medicament,m->nom);
	strcpy(c->fournisseur,m->fournisseur_par_defaut);
	strcpy(c->client,"(com. auto)");
	c->mode=1;
	c->suivant=NULL;
	c->qte=m->qte_a_commander;
	init_date(c);
	return c;
}
commande * init_commande_manuelle(char *m,char *f,char *cl,int qte){
	commande *c=(commande *)malloc(sizeof(commande));
	strcpy(c->medicament,m);
	strcpy(c->fournisseur,f);
	strcpy(c->client,cl);
	c->mode=0;
	c->suivant=NULL;
	c->qte=qte;
	init_date(c);
	return c;
}
commande * commande_manuelle(medicament *liste_m,fournisseur *liste_f,client *liste_c){
	char c[50],f[50],m[50];
	int qte;
	printf("Entrer le medicament à commander manuellement: \n");
	scanf("%s",&m);
	while(chercher_medicament(liste_m,m)==NULL){
		printf("Medicament non existant dans la base de données\n");
		printf("Entrer un nom de medicament valide: \n");
		scanf("%s",&m);
	}
	printf("Entrer le fournisseur de la commande manuelle: \n");
	scanf("%s",&f);
	while(chercher_fournisseur(liste_f,f)==NULL){
		printf("Fournisseur non existant dans la base de données\n");
		printf("Entrer un nom de fournisseur valide: \n");
		scanf("%s",&f);
	}
	printf("Entrer le client auquel est destinée la commande: \n");
	scanf("%s",&c);
	while(chercher_client(liste_c,c)==NULL){
		printf("Client non existant dans la base de données\n");
		printf("Entrer un nom de client valide: \n");
		scanf("%s",&c);
	}
	printf("Entrer la quantité de %s à commander: ",m);
	scanf("%d",&qte);
	return init_commande_manuelle(m,f,c,qte);
}
void init_date(commande *c){
	char format[128]="";
    time_t temps;
    struct tm date;
    time(&temps);
    date=*localtime(&temps);
    strftime(format, 128, "Le %d/%m/%Y à %H:%M ", &date);
	strcpy(c->date,format);
}
void inserer_commande(commande **ptr_liste,commande*c){
	commande *liste_commandes=*ptr_liste;
	commande *m=chercher_commande(liste_commandes,c->medicament,c->fournisseur,c->client);
	if(m!=NULL){
		fusion_commandes(&liste_commandes,m,c);
		*ptr_liste=liste_commandes;
	}
	else{
		if(liste_commandes==NULL){
			*ptr_liste=c;
		}
		else{
			commande *ptr=liste_commandes,*precedent;
			while(ptr!=NULL){
				precedent=ptr;
				ptr=ptr->suivant;
			}
			precedent->suivant=c;
			*ptr_liste=liste_commandes;
		}
	}
}
void capture_date(int *jour_mois,int *annee){
	char nom_f[5],nom_d[5];
    time_t temps;
    struct tm date;
    time(&temps);
    date=*localtime(&temps);
    strftime(nom_f, 5, "%d%m", &date);
    strftime(nom_d, 5, "%Y", &date);
	*jour_mois=atoi(nom_f);
	*annee=atoi(nom_d);
}
commande *load_commande_fromFile(char *nom_fichier){
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
		commande *c=NULL,*tete=NULL,*prec=NULL;
		if(feof(fichier)==0){
			tete=(commande *)malloc(sizeof(commande));
			fread (tete, sizeof(commande),1, fichier);
			c=tete;
			prec=tete;
			while(c->suivant!=NULL){
				c=(commande *)malloc(sizeof(commande));
				fread (c, sizeof(commande),1, fichier);
				prec->suivant=c;
				prec=c;
			}
		}
		fclose(fichier);
		return tete;
	}
}
void write_commande(commande *liste,char *nom_fichier){
	FILE *fichier=NULL;
	fichier=fopen(nom_fichier,"wb+");
	if(fichier==NULL){
		char dossier[11];
		int i=0;
		for(i=0;i<10;i++)
			dossier[i]=nom_fichier[i];
		mkdir(dossier, 0777);
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
		while(liste!=NULL){
			fwrite (liste, sizeof(commande),1, fichier);
			liste=liste->suivant;
		}
		fclose(fichier);
	}
}
void modifier_commande(commande **l,medicament *liste_m,fournisseur *liste_f,client *liste_c){
	commande *liste=*l,*ptr,*prec;
	ptr=liste;
	prec=liste;
	char medicament[50],fournisseur[50],client[50];
	int qte,choix=1;
	do{
		printf("Entrer le nom du médicament de la commande à modifier: ");
		scanf("%s",&medicament);
		printf("Entrer le fournisseur de la commande à modifier: ");
		scanf("%s",&fournisseur);
		printf("Entrer le nom du client qui a fait la commande à modifier: ");
		scanf("%s",&client);
		printf("Entrer la quantité de la commande à modifier: ");
		scanf("%d",&qte);
		while(ptr!=NULL && (strcmp(medicament,ptr->medicament)!=0 || strcmp(fournisseur,ptr->fournisseur)!=0 || strcmp(client,ptr->client)!=0 || qte!=ptr->qte)){
			prec=ptr;
			ptr=ptr->suivant;
		}
		if(ptr==NULL){
			printf("Commande introuvable, refaire une rechercher ?(1/0) ");
			scanf("%d",&choix);
		}
		else{
			printf("=== Commande trouvée ===\n");
			choix=0;
			if(ptr==liste){
				liste=liste->suivant;
				free(ptr);
			}
			else{
				prec->suivant=ptr->suivant;
				free(ptr);
			}
			*l=liste;
			commande *c=commande_manuelle(liste_m,liste_f,liste_c);
			inserer_commande(&liste,c);

		}
	}while(choix!=0);
	*l=liste;
}
void supprimer_commande(commande **l,medicament *liste_m,fournisseur *liste_f,client *liste_c){
	commande *liste=*l,*ptr,*prec;
	ptr=liste;
	prec=liste;
	char medicament[50],fournisseur[50],client[50];
	int qte,choix=1;
	do{
		printf("Entrer le nom du médicament de la commande à supprimer: ");
		scanf("%s",&medicament);
		printf("Entrer le fournisseur de la commande à supprimer: ");
		scanf("%s",&fournisseur);
		printf("Entrer le nom du client qui a fait la commande à supprimer: ");
		scanf("%s",&client);
		printf("Entrer la quantité de la commande à supprimer: ");
		scanf("%d",&qte);
		while(ptr!=NULL && (strcmp(medicament,ptr->medicament)!=0 || strcmp(fournisseur,ptr->fournisseur)!=0 || strcmp(client,ptr->client)!=0 || qte!=ptr->qte)){
			prec=ptr;
			ptr=ptr->suivant;
		}
		if(ptr==NULL){
			printf("Commande introuvable, refaire une rechercher ?(1/0) ");
			scanf("%d",&choix);
		}
		else{
			printf("=== Commande trouvée ===\n");
			choix=0;
			if(ptr==liste){
				printf("au début\n");
				liste=liste->suivant;
				free(ptr);
			}
			else{
				printf("pas au début\n");
				prec->suivant=ptr->suivant;
				free(ptr);
			}
		}
	}while(choix!=0);
	*l=liste;
}
void afficher_commande(commande *liste){
	printf("            Date            #          Medicament       #          Fournisseur         #          Client         #       Quantité        \n");
	printf("=========================================================================================================================================\n");
	int d=22,m=27,c=26,f=30,q=22,i,j=9,n;
	while(liste!=NULL){
		for(i=0;i<3;i++)
			printf(" ");
		printf("%s",liste->date);
		n=d-1-strlen(liste->date);
		for(i=0;i<3;i++)
			printf(" ");
		printf("#");
		for(i=0;i<j;i++)
			printf(" ");
		printf("%s",liste->medicament);
		n=m-j-strlen(liste->medicament);
		for(i=0;i<n;i++)
			printf(" ");
		printf("#");
		for(i=0;i<j;i++)
			printf(" ");
		printf("%s",liste->fournisseur);
		n=f-j-strlen(liste->fournisseur);
		for(i=0;i<n;i++)
			printf(" ");
		printf("#");
		for(i=0;i<j;i++)
			printf(" ");
		printf("%s",liste->client);
		n=c-j-strlen(liste->client);
		for(i=0;i<n;i++)
			printf(" ");
		printf("#");
		for(i=0;i<j;i++)
			printf(" ");
		printf("%d\n",liste->qte);
		printf("=========================================================================================================================================\n");
		liste=liste->suivant;
	}
	printf("\n\n");
}
