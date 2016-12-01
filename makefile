compilateur: bin/client.o bin/commande.o bin/fournisseur.o bin/main.o bin/medicament.o bin/menu.o bin/vente.o
				gcc bin/client.o bin/commande.o bin/fournisseur.o bin/main.o bin/medicament.o bin/menu.o bin/vente.o -o compilateur
bin/client.o: client.c fonctions.h
	gcc -c client.c -o bin/client.o
bin/commande.o: commande.c fonctions.h
	gcc -c commande.c -o bin/commande.o
bin/fournisseur.o: fournisseur.c fonctions.h
	gcc -c fournisseur.c -o bin/fournisseur.o
bin/main.o: main.c fonctions.h
	gcc -c main.c -o bin/main.o
bin/medicament.o: medicament.c fonctions.h
	gcc -c medicament.c -o bin/medicament.o
bin/menu.o: menu.c fonctions.h
	gcc -c menu.c -o bin/menu.o
bin/vente.o: vente.c fonctions.h
	gcc -c vente.c -o bin/vente.o