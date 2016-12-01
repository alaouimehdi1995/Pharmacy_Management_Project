#include"fonctions.h"
fournisseur * load_fournisseurs_fromFile(char *nom_fichier){
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
		printf("-- Chargement des fournisseurs réussi --\n");
		sleep(1);
		fournisseur *pointeur=NULL, *precedent=NULL,*tete=NULL;
		int i,n;
		medicament *m=NULL,*m_prec=NULL;
		if(feof(fichier)==0){
			tete=(fournisseur *)malloc(sizeof(fournisseur));
			fread (tete, sizeof(fournisseur),1, fichier);
			n=tete->nb_medicaments;
			for(i=0;i<n;i++){
				m=(medicament *)malloc(sizeof(medicament));
				fread (m, sizeof(medicament),1, fichier);
				if(i==0){
					tete->liste_medicaments=m;
					m_prec=m;
				}
				else{
					m_prec->suivant=m;
					m_prec=m;
				}
			}
			precedent=tete;
			pointeur=tete->suivant;
		}
		while(pointeur!=NULL){
			pointeur=(fournisseur *)malloc(sizeof(fournisseur));
			fread (pointeur, sizeof(fournisseur),1, fichier);
			n=pointeur->nb_medicaments;
			for(i=0;i<n;i++){
				m=(medicament *)malloc(sizeof(medicament));
				fread (m, sizeof(medicament),1, fichier);
				m->suivant=NULL;
				if(i==0){
					pointeur->liste_medicaments=m;
					m_prec=m;
				}
				else{
					m_prec->suivant=m;
					m_prec=m;
				}
			}
			precedent->suivant=pointeur;
			precedent=pointeur;
			pointeur=pointeur->suivant;
		}
		fclose(fichier);
		return tete;
	}//Fin de else
}//Fin de fonction
void write_fournisseurs(char *nom_fichier,fournisseur * Liste_fournisseurs){
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
		fournisseur *pointeur=Liste_fournisseurs;
		medicament *m;
		int i,n;
		while(pointeur!=NULL){
			fwrite (pointeur, sizeof(fournisseur),1, fichier);
			n=pointeur->nb_medicaments;
			m=pointeur->liste_medicaments;
			for(i=0;i<n;i++){
				fwrite (m, sizeof(medicament),1, fichier);
				m=m->suivant;
			}
			pointeur=pointeur->suivant;
		}
		printf("--- Modifications enregistrées ---\n");
		fclose(fichier);
	}
}
fournisseur * init_fournisseur(){
	fournisseur *c=(fournisseur *)malloc(sizeof(fournisseur));
	printf("Veuillez entrer le nom du fournisseur: ");
	scanf("%s",&c->nom);
	c->nb_medicaments=0;
	c->liste_medicaments=NULL;
	c->suivant=NULL;
	return c;
}
fournisseur * mise_a_jour(fournisseur *f,medicament *m){//Met à jour la liste des médicaments du fournisseur à partir de la liste des médicaments 
	fournisseur *ptr_fournisseur=f;
	printf("La fonction a été appellée\n");
	while(ptr_fournisseur!=NULL){ //On parcourt la liste des fournisseurs
		medicament *ptr_m=ptr_fournisseur->liste_medicaments;
		while(ptr_m!=NULL){ // On parcourt la liste de médicaments de chaque fournisseur
			medicament *ptr_liste=m;
			while(strcmp(ptr_liste->nom,ptr_m->nom)!=0){//Et pour chaque médicament, on parcourt la liste de médicaments de la pharmacie pour trouver le médicament correspondant
				ptr_liste=ptr_liste->suivant;
			}
			medicament *medic=(medicament *)malloc(sizeof(medicament));//On crée un médicament dans lequel on stockera les nouvelles données du médicament
			*medic=*ptr_liste;
			if(ptr_m==ptr_fournisseur->liste_medicaments){ //Et on procède au remplacement du médicament, d'abord par la suppression
				ptr_fournisseur->liste_medicaments=ptr_fournisseur->liste_medicaments->suivant;
				free(ptr_m);
			}
			else{		
				medicament *ptr=ptr_fournisseur->liste_medicaments,*precedent=NULL;
				while(ptr!=ptr_m){
					precedent=ptr;
					ptr=ptr->suivant;
				}
				precedent->suivant=ptr->suivant;
				free(ptr);
			}// puis par l'insertion des nouvelles coordonnées
			ptr_fournisseur->liste_medicaments=insertion_medicament(ptr_fournisseur->liste_medicaments,medic);
			ptr_m=ptr_m->suivant;	
		}
		ptr_fournisseur=ptr_fournisseur->suivant;
	}
	return f;
}
int fournisseur_existant(fournisseur *liste, char *nom){
	int trouve=0;
	fournisseur *ptr=liste;
	while(ptr!=NULL){
		if(strcmp(ptr->nom,nom)==0)
			trouve=1;
		ptr=ptr->suivant;
	}
	return trouve;
}
fournisseur * inserer_fournisseur(fournisseur *liste_fournisseurs,fournisseur *c){
	if(liste_fournisseurs==NULL){
		liste_fournisseurs=c;
	}
	else{
		if(strcmp(liste_fournisseurs->nom,c->nom)>=0){
			c->suivant=liste_fournisseurs;
			liste_fournisseurs=c;
		}
		else{
			fournisseur *pointeur=liste_fournisseurs,*precedent=NULL;
			while(pointeur !=NULL && strcmp(pointeur->nom,c->nom)<0){
				precedent=pointeur;
				pointeur=pointeur->suivant;
			}
			if(pointeur==NULL){
				precedent->suivant=c;
			}
			else{
				c->suivant=pointeur;
				precedent->suivant=c;
			}	
		}
	}
	return liste_fournisseurs;
}
void afficher_fournisseurs(fournisseur *liste_fournisseurs){
	printf("\n\n== Affichage de la liste: ============================\n\n");
	if(liste_fournisseurs !=NULL){
	    fournisseur *c=liste_fournisseurs;
	    while(c!=NULL){
			printf("- %s",c->nom);
			printf("- %d\n",c->nb_medicaments);
			c=c->suivant;
	    }
	}
	printf("\n\n");
}
fournisseur * modifier_fournisseur(fournisseur **l,fournisseur *cl,medicament **m){
	fournisseur *Liste_fournisseurs=*l;
	medicament *liste_m=*m;
	int modifier1,modifier2;
	char nom[50];
	int continuer=1,choix;
	if(cl!=NULL){
		fournisseur *c=(fournisseur *)malloc(sizeof(fournisseur));
		printf("Modifier le nom ?(1/0) ");
		scanf("%d",&modifier1);
		if(modifier1 !=0){
			printf("Entrer le nouveau nom: ");
			scanf("%s",&c->nom);
		}
		else
			strcpy(c->nom,cl->nom);
		printf("Modifier la liste des médicaments ? (1/0) ");
		scanf("%d",&modifier2);
		if(modifier2 !=0){
			c->liste_medicaments=cl->liste_medicaments;
			char chaine[4];
			do{
				system(CLEAR);
				printf("  ==== Modification de la liste de medicaments ==========================\n");
				printf("  #                                 				    \n");
				printf("  #   1- afficher la liste des medicaments de %s            \n",c->nom);
				printf("  #   2- ajouter un medicament à la liste de %s             \n",c->nom);
				printf("  #   3- rechercher un medicament dans la liste de %s       \n",c->nom);
				printf("  #   4- supprimer un medicament de la liste de %s          \n",c->nom);
				printf("  #                                 				    \n");
				printf("  #            Appuyer sur une touche pour revenir                  \n");
				printf("  #======================================================================\n");
				scanf("%s",&chaine);
				choix=atoi(chaine);
				switch (choix){
					case 1:
						afficher_medicaments(c->liste_medicaments);
						break;
					case 2:
						c->liste_medicaments=inserer_medicament_pour_fournisseur(c,l,m); // D'ici vient le probleme
						c->nb_medicaments=nombre_medicaments(c->liste_medicaments);
						break;
					case 3:
						printf("Entrer le nom du médicament à rechercher dans la liste de %s\n",c->nom);
						scanf("%s",&nom);
						afficher_medicament(chercher_medicament(c->liste_medicaments,nom));
						c->nb_medicaments=nombre_medicaments(c->liste_medicaments);
						break;
					case 4:
						printf("Entrer le nom du médicament à supprimer de la liste de %s\n",cl->nom);
						scanf("%s",&nom);
						medicament *med=chercher_medicament(c->liste_medicaments,nom);
						c->liste_medicaments=supprimer_medicament(med,c->liste_medicaments);
						c->nb_medicaments=nombre_medicaments(c->liste_medicaments);
						break;
					default:
						continuer=0;
						break;
				}
			}while(continuer ==1);
		}
		else{
			c->liste_medicaments=cl->liste_medicaments;
			c->nb_medicaments=cl->nb_medicaments;
		}
		c->suivant=NULL;
		if(modifier1 !=0 || modifier2!=0){
			Liste_fournisseurs=supprimer_fournisseur(Liste_fournisseurs,cl);
			Liste_fournisseurs=inserer_fournisseur(Liste_fournisseurs,c);
		}
	}
	else{
		printf("Fournisseur inexistant dans la liste\n");
	}
	return Liste_fournisseurs;
}
//====================================================================
fournisseur * supprimer_fournisseur(fournisseur *Liste_fournisseurs,fournisseur *cl){
	if(cl !=NULL){
		if(strcmp(Liste_fournisseurs->nom,cl->nom)==0){
			Liste_fournisseurs=Liste_fournisseurs->suivant;
			free(cl);
		}
		else{	
			fournisseur *pointeur=Liste_fournisseurs,*precedent=NULL;
			while(pointeur !=NULL && pointeur !=cl){
				precedent=pointeur;
				pointeur=pointeur->suivant;
			}
			if(pointeur==cl){
				precedent->suivant=pointeur->suivant;
				free(pointeur);
			}
			else{
				printf("Le fournisseur est introuvable\n");
			}
		}
	}
	else{
		printf("Fournisseur introuvable\n");
	}
	return Liste_fournisseurs;
}
fournisseur * rechercher_fournisseur(fournisseur **l,char *nom,medicament **me){
	medicament *liste_m=*me;
	fournisseur *Liste_fournisseurs=*l;
	if(Liste_fournisseurs!=NULL){
		fournisseur *pointeur=Liste_fournisseurs;
		while(pointeur !=NULL && strcmp(pointeur->nom,nom)!=0){
			pointeur=pointeur->suivant;
		}
		if(pointeur==NULL){
			printf("Le nom saisi ne figure pas dans la liste de fournisseurs\n");
		}
		else{
			// AFFICHER_fournisseur
			int choix;
			printf("- Nom du fournisseur: %s\n",pointeur->nom);
			printf("Voulez-vous modifier ce fournisseur ? (1/0) ");
			scanf("%d",&choix);
			if(choix!=0){
				Liste_fournisseurs=modifier_fournisseur(l,pointeur,me);
				printf("Liste modifiée\n");
			}
		}
	}
	return Liste_fournisseurs;
}
fournisseur * chercher_fournisseur(fournisseur *liste,char *nom){
	fournisseur *ptr=liste;
	while(ptr!=NULL){
		if(strcmp(ptr->nom,nom)==0)
			return ptr;
		ptr=ptr->suivant;
	}
	return NULL;
}
