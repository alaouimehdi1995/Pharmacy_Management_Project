#include"fonctions.h"
vente *load_vente_fromFile(char *nom_fichier){
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
		vente *c=NULL,*tete=NULL,*prec=NULL;
		if(feof(fichier)==0){
		tete=(vente *)malloc(sizeof(vente));
		fread (tete, sizeof(vente),1, fichier);
		c=tete;
		prec=tete;
		while(c->suivant!=NULL){
			c=(vente *)malloc(sizeof(vente));
			fread (c, sizeof(vente),1, fichier);
			prec->suivant=c;
			prec=c;
		}
		}
		fclose(fichier);
		return tete;
	}
}
void write_vente(vente *liste,char *nom_fichier){
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
			fwrite (liste, sizeof(vente),1, fichier);
			liste=liste->suivant;
		}
		fclose(fichier);
	}
}
void init_date_vente(vente *c){
	char format[128]="";
    time_t temps;
    struct tm date;
    time(&temps);
    date=*localtime(&temps);
    strftime(format, 128, "Le %d/%m/%Y à %H:%M ", &date);
	strcpy(c->date,format);	
}
vente * init_vente(char *nom_medicament,int qte){
	vente *v=(vente *)malloc(sizeof(vente));
	strcpy(v->medicament,nom_medicament);
	v->qte=qte;
	v->suivant=NULL;
	init_date_vente(v);
	return v;
}
void inserer_vente(vente **ptr_liste,vente *c){
	vente *liste_ventes=*ptr_liste;
	if(liste_ventes==NULL){
		*ptr_liste=c;
	}
	else{
		vente *ptr=liste_ventes,*precedent;
		while(ptr!=NULL){
			precedent=ptr;
			ptr=ptr->suivant;
		}
		precedent->suivant=c;
		*ptr_liste=liste_ventes;
	}
}
void afficher_vente(vente *liste){
	printf("                  Date                  #            Medicament          #        Quantité        \n");
	printf("==================================================================================================\n");
	int d=40,m=32,q=22,i,j=12,n;
	while(liste!=NULL){
		for(i=0;i<8;i++)
			printf(" ");
		printf("%s",liste->date);
		n=d-7-strlen(liste->date);
		for(i=0;i<n;i++)
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
		printf("%d\n",liste->qte);
		printf("==================================================================================================\n");
		liste=liste->suivant;
	}
	printf("\n\n");
}
void ajouter_vente(medicament *liste_m){
	vente *liste_ventes=NULL;
	char nom_fichier[6],nom_dossier[18],nom_medicament[50];
	int temp1,temp2,qte;
	//============================================= FIN INITIALISATION
	capture_date(&temp1,&temp2);
	sprintf(nom_fichier,"%d_.bin",temp1);
	sprintf(nom_dossier,"data/%d/",temp2);
	strcat(nom_dossier,nom_fichier);
	//============================================== FIN DE GENERATION DU NOM DU FICHIER
	liste_ventes=load_vente_fromFile(nom_dossier);
	printf("Entrer le médicament à vendre\n");
	scanf("%s",&nom_medicament);
	medicament *m=chercher_medicament(liste_m,nom_medicament);
	while(m==NULL){
		printf("Erreur, veuillez entrer un nom de médicament valide\n");
		scanf("%s",&nom_medicament);
		m=chercher_medicament(liste_m,nom_medicament);
	}
	printf("Veuillez entrer la quantité de %s à vendre: ",&nom_medicament);
	scanf("%d",&qte);
	if(m->qte_stock>=qte){
		m->qte_stock-=qte;
		printf("Quantité suffisante\n");//Message à supprimer par la suite
	}
	else{
		printf("Impossible de faire une vente de %d car le stock ne contient que %d, la vente sera donc de %d unités\n",qte,m->qte_stock,qte);
		qte=m->qte_stock;
		m->qte_stock=0;
	}
	vente *v=init_vente(nom_medicament,qte);
	inserer_vente(&liste_ventes,v);
	write_vente(liste_ventes,nom_dossier);
	//=============================================== ICI AJOUTER LE BOUT DE CODE POUR LANCER LA COMMANDE AUTOMATIQUE;
	commande *liste_commandes=NULL;
	capture_date(&temp1,&temp2);
	sprintf(nom_fichier,"%d.bin",temp1);
	sprintf(nom_dossier,"data/%d/",temp2);
	strcat(nom_dossier,nom_fichier);
	liste_commandes=load_commande_fromFile(nom_dossier);
	if(m->qte_stock<=m->qte_a_signaler){
		commande *liste_commandes=NULL;
		char nom_fichier[5],nom_dossier[12];
		int temp1,temp2;
		capture_date(&temp1,&temp2);
		sprintf(nom_fichier,"%d.bin",temp1);
		sprintf(nom_dossier,"data/%d/",temp2);
		strcat(nom_dossier,nom_fichier);
		liste_commandes=load_commande_fromFile(nom_dossier);
		inserer_commande(&liste_commandes,init_commande_auto(m));
		write_commande(liste_commandes,nom_dossier);
	}
}
