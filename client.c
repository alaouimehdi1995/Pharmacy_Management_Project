
#include"fonctions.h"
client * load_clients_fromFile(char *nom_fichier){
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
		printf("-- Chargement des clients réussi --\n");
		sleep(1);
		client *pointeur=NULL, *precedent=NULL,*tete=NULL;
		if(feof(fichier)==0){
			tete=(client *)malloc(sizeof(client));
			fread (tete, sizeof(client),1, fichier);
			precedent=tete;
			pointeur=tete;
		}
		while(pointeur->suivant!=NULL){
			pointeur=(client *)malloc(sizeof(client));
			fread (pointeur, sizeof(client),1, fichier);
			precedent->suivant=pointeur;
			precedent=pointeur;
		}
		pointeur->suivant=NULL;
		fclose(fichier);
		return tete;
	}
}
void write_clients(char *nom_fichier,client * Liste_clients){
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
		client *pointeur=Liste_clients;
		while(pointeur!=NULL){
			fwrite (pointeur, sizeof(client),1, fichier);
			pointeur=pointeur->suivant;
		}
		fclose(fichier);
	}
}
client * init_client(){
	client *c=(client *)malloc(sizeof(client));
	printf("Veuillez entrer le nom du client: ");
	scanf("%s",&c->nom);
	c->suivant=NULL;
	return c;
}
client * inserer_client(client *liste_clients,client *c){
	if(liste_clients==NULL){
		liste_clients=c;
	}
	else{
		if(strcmp(liste_clients->nom,c->nom)>=0){
			c->suivant=liste_clients;
			liste_clients=c;
		}
		else{
			client *pointeur=liste_clients,*precedent=NULL;
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
	return liste_clients;
}
void afficher_clients(client *liste_clients){
	printf("\n\n== Affichage de la liste: ==================\n\n");
	if(liste_clients !=NULL){
	    client *c=liste_clients;
	    while(c!=NULL){
			printf("- %s\n",c->nom);
			c=c->suivant;
	    }
	}
	printf("\n\n");
}
client * modifier_client(client *Liste_clients,client *cl){
	int modifier;
	client *c=(client *)malloc(sizeof(client));
	printf("Modifier le nom ?(1/0) ");
	scanf("%d",&modifier);
	if(modifier !=0){
		printf("Entrer le nouveau nom: ");
		scanf("%s",&c->nom);
	}
	else
		strcpy(c->nom,cl->nom);
	c->suivant=NULL;
	if(modifier !=0){
		Liste_clients=supprimer_client(Liste_clients,cl);
		Liste_clients=inserer_client(Liste_clients,c);
	 }
	return Liste_clients;
}
client * supprimer_client(client *Liste_clients,client *cl){
	if(cl!=NULL){
		if(strcmp(Liste_clients->nom,cl->nom)==0){
			client *c=Liste_clients;
			Liste_clients=Liste_clients->suivant;
			printf("Le client %s a été supprimé\n",c->nom);
			free(c);
		}
		else{	
			int trouve=0;
			client *pointeur=Liste_clients,*precedent=NULL;
			while(pointeur !=NULL){
				if(strcmp(pointeur->nom,cl->nom)==0){
					trouve=1;
					precedent->suivant=pointeur->suivant;
					printf("Le client %s a été supprimé\n",pointeur->nom);
					free(pointeur);
					pointeur=precedent->suivant;
				}
				else{
					precedent=pointeur;
					pointeur=pointeur->suivant;
				}
			}	
			if(trouve==0){
			printf("Le client est introuvable\n");
			}
		}
	}
	else{
		printf("Le client est introuvable\n");
	}
	return Liste_clients;
}
client * rechercher_client(client *Liste_clients,char *nom){
	if(Liste_clients!=NULL){
		client *pointeur=Liste_clients;
		while(pointeur !=NULL && strcmp(pointeur->nom,nom)!=0){
			pointeur=pointeur->suivant;
		}
		if(pointeur==NULL){
			printf("Le nom saisi ne figure pas dans la liste de clients\n");
		}
		else{
			int choix;
			printf("- Nom du client: %s\n",pointeur->nom);
			printf("Voulez-vous modifier ce client ? (1/0) ");
			scanf("%d",&choix);
			if(choix!=0){
				Liste_clients=modifier_client(Liste_clients,pointeur);
				printf("Liste modifiée\n");
			}
		}
	}
	return Liste_clients;
}
client * chercher_client(client *liste,char *nom){
	client *ptr=liste;
	while(ptr!=NULL){
		if(strcmp(ptr->nom,nom)==0)
			return ptr;
		ptr=ptr->suivant;
	}
	return NULL;
}
