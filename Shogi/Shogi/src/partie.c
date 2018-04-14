#include "partie.h"

/***************************FONCTION PIECE**************************************************/

piece_t piece_creer(int joueur,char type,int statut)
{
	/* Declaration et initialisation d'une piece a retourner */
    piece_t p={joueur,type,statut}; 
    return p;
}

				/********************************************/
piece_t piece_identifier(char type)
{
	int i=0;
	char *tab_type=malloc(15*sizeof(char));
	piece_t piece=piece_creer(JOUEUR_VIDE,'.',VIDE);

	strcpy(tab_type,"plnbrsgkdjcfta");

	if(isupper(type)) /*on regarde si la piece est en majuscule donc elle appartient au joueur 0*/
	{
		for(i=0;i<8;i++) /*on devise le tableau on deux partie de 0 a 7 les pieces sont non promue*/
		{
			if(toupper(tab_type[i])== type) 
			{
				return piece_creer(JOUEUR0,type,NON_PROMUE);
			}
		}
		for(i=8;i<14;i++) /*on devise le tableau on deux partie de 8 a 14 les pieces sont promue*/
		{
			if(toupper(tab_type[i])== type)
			{
				return piece_creer(JOUEUR0,type,PROMUE);
			}
		}
	}
	else /*sinon c'est le cas du joueur 1*/
	{
		for(i=0;i<8;i++)
		{
			if(tab_type[i]== type)
			{
				return piece_creer(JOUEUR1,type,NON_PROMUE);
			}
		}
		for(i=8;i<14;i++)
		{
			if(tab_type[i]== type)
			{
				return piece_creer(JOUEUR1,type,PROMUE);
			}
		}
	}

	return piece;
}

				/********************************************/


char piece_caractere(piece_t piece)
{

    return piece.type; 
}

				/********************************************/


void piece_afficher(piece_t piece)
{

    printf("%3c",piece.type);
}

				/********************************************/
int piece_joueur(piece_t piece) 
{
	/* Retourne le propriétaire de la piece en paramétre */
    return piece.joueur;
} 

				/********************************************/

void changer_statut(piece_t *piece) 
{
	int i; /* Variable de boucle */

	/* Allocation de deux tableaux de 7 cases pour stocker les caracteres des pieces promouvables */
	char *tab1=malloc(7*sizeof(char));
	char *tab2=malloc(7*sizeof(char));
	/* Initialisation des tableaux */
	strcpy(tab1,"djcfta");
	strcpy(tab2,"plnbrs");

	/* Si la piece est en majuscule (appartient au Joueur0) */
	if(isupper(piece->type))
	{
		/* Transforme les tableaux en caracteres majuscules */
		for(i=0;i<6;i++)
		{
			tab1[i]=toupper(tab1[i]);
			tab2[i]=toupper(tab2[i]);
		}
	}

	if(piece->statut == PROMUE) /* Si la piece est promue */
	{
		/* Parcours du tableau */
		for(i=0;i<6;i++)
		{
			/* Recherche du caractere correspondant */
			if(tab1[i]== piece->type)
			{
				piece->type=tab2[i]; /* changer le type de la piece */
				break; /* Sortir de la boucle */
			}
		}
		/* Changer statut de la piece */
		piece->statut=NON_PROMUE;
	}
	else /* Si la piece n'est pas promue */
	{
		/* Parcours du tableau */
		for(i=0;i<6;i++)
		{
			/* Recherche du caractere correspondant */
			if(tab2[i]== piece->type)
			{
				piece->type=tab1[i]; /* Changer le type de la piece */
				break; /* Sortir de la boucle  */
			}
		}
		/* Changer statut de la piece */
		piece->statut=PROMUE;
	}

	/* Detruire les tableaux */
	free(tab2);
	free(tab1);
}

				/********************************************/


/***************************FONCTION PIECE**************************************************/


/*****************FONCTION SECONDAIRE******************/



void affiche_plateau(partie_t *partie)
{
	int i=0,j=0;
	
	printf("\n-----------------------------------\n\n  ");
	
	for(i=0;i<TAILLE;i++)
	{
		printf("%3d",i);
	}
	printf("\n");
    for (i=0; i<TAILLE; i++)
    {
    	
    	printf("%2d",i);
        
        for(j=0; j<TAILLE; j++)
        {
            piece_afficher(partie->tablier[i][j]);
        }
        printf("\n");
    }
}
				
				/********************************************/


void changer_joueur(partie_t *partie )
{

	partie->bool_joueur=(!partie->bool_joueur);
}


				/********************************************/


int case_vide(piece_t caze)
{

	return (caze.type == '.')? VRAI : FAUX;
}


				/********************************************/



void modifier_case(partie_t *partie,piece_t piece,coordonnees_t coords) // Modifie juste la case d'arrivée
{

	partie->tablier[coords.x][coords.y]=piece;
}


				/********************************************/


void test_coordonnees(coordonnees_t *depart, coordonnees_t *arrivee) /*les parametre ce sont des pointeur vers des coordonner*/
{
	do 
	{	/*initialisation des coordonner */
		printf("Veuillez entrer les coordonnees de depart\nLigne : ");
		scanf(" %d",&depart->x);
		printf("Colonne : ");
		scanf(" %d",&depart->y);
		printf("Veuillez entrer les coordonnees d'arrivee\nLigne : ");
		scanf(" %d",&arrivee->x);
		printf("Colonne : ");
		scanf(" %d",&arrivee->y);

		if((depart->x >= 0 && depart->x < TAILLE && depart->y >= 0 && depart->y < TAILLE) && (arrivee->x >0 && arrivee->y< TAILLE-1 && arrivee->x < TAILLE-1 && arrivee->y > 0))
		{
			return; /*on regarde si les coordonner donner appartienne bien au tablier en sort de la boucle sinon on y reste*/
		}
		else
		{
			printf("\n\t/!\\ Coordonnees non valides hors du tablier /!\\\n");
		}
	}while(VRAI);
}

				/********************************************/



int echec(partie_t *partie)
{
	coordonnees_t indice; /*indice est t'une variable de type coordonner qui va parcourire le tablier */

	/*  *****************
		* cavalier(j1)   *
		*****************
	*/

	if(partie->bool_joueur == JOUEUR1) 
	{
		if(partie->tablier[KING[JOUEUR1].x-2][KING[JOUEUR1].y-1].type == 'N' || partie->tablier[KING[JOUEUR1].x-2][KING[JOUEUR1].y+1].type == 'N')
		{
			return VRAI;
		}

	}
	
	/*  *****************
		* cavalier(j0)   *
		*****************
	*/

	else if(partie->bool_joueur == JOUEUR0)
	{
		if(partie->tablier[KING[JOUEUR0].x+2][KING[JOUEUR0].y-1].type == 'n' || partie->tablier[KING[JOUEUR0].x+2][KING[JOUEUR0].y+1].type == 'n')
		{
			return VRAI;
		}

	}
	
	/*  ****************************************************************************************************
		* tour(j1) / tour(j0) / pion(j0) / lance (j0) / general_d'or(j1 et j0)/ general_d'argent(j1 et j0)  *
		****************************************************************************************************
	*/
	/* Verification vers le bas sur la meme colonne */

	for(indice.x=KING[partie->bool_joueur].x+1 , indice.y=KING[partie->bool_joueur].y; indice.x < TAILLE-1; indice.x++)
	{
		if(!case_vide(partie->tablier[indice.x][KING[partie->bool_joueur].y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;

			}
			changer_joueur(partie);
			return FAUX;
		}
	}


	/*  *********************************************************************************************************************
		* tour(j1) / pion(j1)/ tour(j0)  / lance (j1) / general_d'or(j1 et j0)/ general_d'argent(j1 et j0)/ roi(j0 et j1)   *
		*********************************************************************************************************************
	*/
	/* Verification vers le haut sur la meme colonne */
	
	for(indice.x=KING[partie->bool_joueur].x-1 ; indice.x > 0 ; indice.x--)
	{
		if(!case_vide(partie->tablier[indice.x][indice.y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;
			}
			changer_joueur(partie);
			break;
		}

	}	

	/*  *********************************************************************************************
		* tour(j1) / tour(j0) / general_d'or(j1 et j0)/ general_d'argent(j1 et j0) / roi(j1 et j0) / *
		*********************************************************************************************
	*/
	/* Verification vers la droite sur la meme ligne */

	for(indice.y=KING[partie->bool_joueur].y+1 , indice.x=KING[partie->bool_joueur].x ; indice.y<TAILLE-1 ; indice.y++)
	{
		if(!case_vide(partie->tablier[indice.x][indice.y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;
			}
			changer_joueur(partie);
			break;
		}
	}

	/*  *********************************************************************************************
		* tour(j1) / tour(j0) / general_d'or(j1 et j0) / roi(j1 et j0) / *
		*********************************************************************************************
	*/
	/* Verification vers la gauche sur la meme ligne */

	for(indice.y=KING[partie->bool_joueur].y-1 ; indice.y > 0; indice.y--)
	{
		if(!case_vide(partie->tablier[indice.x][indice.y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;
			}
			changer_joueur(partie);
			break;
		}
	}

	/*  *********************************************************************************************
		* / general_d'or(j1 et j0)/ general_d'argent(j1 et j0) / roi(j1 et j0) / fou (j1 et j0)*
		*********************************************************************************************
	*/
	/* Verification vers le haut a droite */

	for(indice.x=KING[partie->bool_joueur].x-1,indice.y=KING[partie->bool_joueur].y+1 ; indice.x > 0 && indice.y < TAILLE-1; indice.y++ ,indice.x--)
	{
		if(!case_vide(partie->tablier[indice.x][indice.y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;
			}
			changer_joueur(partie);
			break;
		}
	}

	/*  *********************************************************************************************
		* / general_d'or(j1 et j0)/ general_d'argent(j1 et j0) / roi(j1 et j0) / fou (j1 et j0)*
		*********************************************************************************************
	*/
 	/* Verification vers le bas a gauche */

	for(indice.x=KING[partie->bool_joueur].x+1,indice.y=KING[partie->bool_joueur].y-1 ; indice.y > 0 && indice.x < TAILLE-1; indice.y-- ,indice.x++)
	{
		if(!case_vide(partie->tablier[indice.x][indice.y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;
			}
			changer_joueur(partie);
			break;
		}
	}

	/*  *********************************************************************************************
		* / general_d'or(j1 et j0)/ general_d'argent(j1 et j0) / roi(j1 et j0) / fou (j1 et j0)*
		*********************************************************************************************
	*/
	/* Verification vers le haut a gauche */

	for(indice.x=KING[partie->bool_joueur].x-1,indice.y=KING[partie->bool_joueur].y-1 ; indice.y < TAILLE-1 && indice.x < TAILLE-1; indice.y-- ,indice.x--)
	{
		if(!case_vide(partie->tablier[indice.x][indice.y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;
			}
			changer_joueur(partie);
			break;
		}
	}

	/*  *********************************************************************************************
		* / general_d'or(j1 et j0)/ general_d'argent(j1 et j0) / roi(j1 et j0) / fou (j1 et j0)*
		*********************************************************************************************
	*/
	/* Verification vers le bas a droite */

	for(indice.x=(KING[partie->bool_joueur].x+1), indice.y=(KING[partie->bool_joueur].y+1) ; indice.y > 0 && indice.x > 0; indice.y++ ,indice.x++)
	{
		if(!case_vide(partie->tablier[indice.x][indice.y]))
		{
			changer_joueur(partie);
			if(deplacement_valide(indice,KING[!partie->bool_joueur],partie))
			{
				changer_joueur(partie);
				return VRAI;
			}
			changer_joueur(partie);
			break;
		}
	}

	return FAUX;

}



/*****************FONCTION SECONDAIRE******************/




/********************** PARTIE *************************/


partie_t *partie_creer()
{	/*allocation et initialisation de tableau king qui sauvegardera les coordonner des rois de chaque joueur*/
	KING=malloc(2*sizeof(coordonnees_t));
	KING[0].x=1;
	KING[0].y=5;
	KING[1].x=9;
	KING[1].y=5;

	LC=malloc(sizeof(liste_capture_t));
	LC->taille=0;
	LC->debut=NULL;

	/* declaration et initialisation de la liste des coups joués*/	
	partie_t *partie=malloc(sizeof(partie_t));
	partie->coups_joues.debut=NULL;
	partie->coups_joues.fin=NULL;
	partie->coups_joues.nb_coups=0;

	return partie; 
}

				/********************************************/



partie_t *partie_nouvelle()
{
	partie_t *partie=partie_creer(); /* en alloue de la memoire pour la partie */
	partie->bool_joueur=JOUEUR1; /*on initialise bool_joueur au joueur 1, donc a chaque nouvelle partie sa sera le joueur 1 qui commencera*/
	
	char *chaine=malloc(sizeof(char)*((3*TAILLE)+1));
	int j=0,i=0;
	/*initialisation de la chaine de texte */
	strcpy(chaine,".LNSGKGSNL...R.....B...PPPPPPPPP.");
	/* initialise les case vide avec des point */
	if(partie != NULL)
	{
		for(j=0;j<TAILLE;j++)
		{
			partie->tablier[0][j]=piece_identifier('.');
			partie->tablier[4][j]=piece_identifier('.');
			partie->tablier[5][j]=piece_identifier('.');
			partie->tablier[6][j]=piece_identifier('.');
			partie->tablier[7][j]=piece_identifier('.');
			partie->tablier[10][j]=piece_identifier('.');
		}
	}

	/* initialise les piece de l'echequier  */
	for(i=1;i<4;i++)
	{
		for(j=0;j<TAILLE;j++)
		{
			partie->tablier[i][j]=piece_identifier(chaine[(i-1)*TAILLE+j]);
			partie->tablier[TAILLE-i-1][TAILLE-j-1]=piece_identifier(tolower(chaine[(i-1)*TAILLE+j]));

		}
	}

	free(chaine);

	return partie;
}

				/********************************************/


partie_t *partie_charger(const char *nom)
{
	FILE* fichier=NULL;
	partie_t* partie = NULL; // On initialise a NULL pour ne pas mettre de else 
	char *chaine=malloc(sizeof(char)*TAILLE);
	char *chemin=malloc(sizeof(char)*25);
							 // on retourne directement partie
	int i,j; // Pour le remplissage et le parcour du tablier

	strcpy(chemin,"Plateaux/");
	strcat(chemin,nom);
	strcat(chemin,".plt");

	fichier = fopen(chemin,"r");


	if(fichier != NULL) // Si le fichier existe 
	{
		
		fscanf(fichier,"%s",chaine); // On recupere le premier mot 

		if(!(strcmp(chaine,"PL"))) // Si ce mot c'est PL on cree une partie
		{
			
			partie =partie_creer(); // louer de l'espace pour la partie

			for(i=0;i<TAILLE;i++) 
			{
				fscanf(fichier,"%s",chaine); // Lire le 1er mot du fichier qui represente les cases de la 1ere ligne du tablier
				
				for(j=0;j<TAILLE;j++) 
				{
					partie->tablier[i][j] = piece_identifier(chaine[j]); // creer des pieces en fonction du type

				}
			}
			fscanf(fichier,"%s",chaine);
			partie->bool_joueur = atoi(chaine);// Convertir le dernier caractere du fichier qui represente le joueur qui va jouer en entier 
		}

		fclose(fichier);
	}

	return partie;

}

				/********************************************/


void partie_jouer(partie_t *partie,int charger,const char *nomv) /* modif */
{
	coordonnees_t depart, arrivee;
	int bol_annule=VRAI,bol_sauvegarde=FAUX,bol_prom=FAUX;
	char reponse;
	char *chemin=NULL;
	char nom[20];
	int i=0,j=0;

	/* Affochage du tablier au debut du jeu */
	affiche_plateau(partie);
	do
	{
		/* Pour le premier coup */
		if(partie->coups_joues.nb_coups <= 1)
		{
			do
			{
				printf("\n********** Tour du joueur %d **********\n",partie->bool_joueur);
				printf("\n _______________________________________________\n|\t\t\t\t\t\t|\
						\n|Vous voulez :\t\t\t\t\t|\
						\n|-Faire un deplacement,\t\ttappez 'd'\t|\
						\n|-Quitter,\t\t\ttappez 'q'\t|\
						\n|____________________________________________: ");
				scanf(" %c",&reponse);

			}while(reponse!='q' && reponse!='d');
		}
		else /* Les coups suivants (annulation possible) */
		{
			do
			{

				printf("\n********** Tour du joueur %d **********\n",partie->bool_joueur);
				printf("\n _______________________________________________\n|\t\t\t\t\t\t|\
						\n|Vous voulez :\t\t\t\t\t|\
						\n|-Faire un deplacement,\t\ttappez 'd'\t|\
						\n|-Annuler un deplacement,\ttappez 'a'\t|\
						\n|-Quitter,\t\t\ttappez 'q'\t|\
						\n|____________________________________________: ");
				
				scanf(" %c",&reponse);

			}while(reponse!='q' && reponse!='d' && reponse!='a');
		}
		if(reponse == 'd')
		{
			bol_prom=promotion(partie); /* s'il existe une piece (ou plusieurs) on demande de la promouvoir  */
			
			printf("\n#-#-#-#-#-#-#- DEPLACEMENT -#-#-#-#-#-#-#\n\n");

			/* On teste les coordonnées que l'utilisateur entre */
			test_coordonnees(&depart,&arrivee);

			if(deplacement_valide(depart,arrivee,partie))
			{
				bol_prom=FAUX;
				deplacement(partie,depart,arrivee);
				

				if(tolower(partie->tablier[arrivee.x][arrivee.y].type) == 'k')
				{
					if(echec(partie))
					{
						annuler_deplacement(partie);
						printf("\n\t/!\\ Attention ! vous ne pouvez pas effectuer ce deplacement car votre roi sera en echec /!\\\n");
						affiche_plateau(partie);
						changer_joueur(partie);

					}
					else 
					{
						affiche_plateau(partie);
					}
					
				}
				else
				{
					
					affiche_plateau(partie);
					
					if(LC->taille != 0)
					{
						if(tolower(partie->tablier[LC->debut->coord_capture.x][LC->debut->coord_capture.y].type) == 'k')
						{
							printf("******** BRAVO ! le joueur %d remporte la partie ********\n",partie->bool_joueur);
							reponse='q';
						}
					}
				}
				
				if(deplacement_valide(arrivee,KING[!partie->bool_joueur],partie))
				{
					printf("\n\t/!\\ Attention le roi du joueur %d est en echec /!\\\n",!partie->bool_joueur);
				}
				
				changer_joueur(partie);
				
			}
			else if(parachutage(depart,arrivee,partie))
			{

				affiche_plateau(partie);
			}
		
		}
		else if((reponse == 'a' || reponse == 'q') && bol_prom)
		{
			printf("\n\tVeuillez faire un deplacement avant d'annuler ou de quitter \n");
		}
		else if(reponse == 'a' && (!bol_prom))
		{
			while(partie->coups_joues.nb_coups > 1 && bol_annule)
			{
				changer_joueur(partie); /* pour annuler le coup du joueur adverse pour pouvoir annuler le sien */
				annuler_deplacement(partie);
				affiche_plateau(partie);
				changer_joueur(partie); /* annuler le coup du joueur qui est entrain de jouer */
				annuler_deplacement(partie);
				affiche_plateau(partie);
				if(partie->coups_joues.nb_coups > 1)
				{
					printf("\n-----------------------------------------\
							\nVoulez vous annuler un autre deplacement?\
							\nsi oui tappez: 1\
							\nsi non tappez: 0\n");
					scanf(" %d",&bol_annule);
				}
				else
				{
					printf("\n\t/!\\ Vous ne pouvez pas annuler d'autre deplacement /!\\\n");
				}
			}
		}

		if(reponse == 'q' && (!bol_prom))
		{
			do
			{
				printf("\n************* Voulez vous enregistrer la partie *************\n"\
				  	 "si vous voulez sauvegarder le plateau\n"\
				   	"tappez 1\n"\
				   	"si vous voulez sauvegarder un replay\n"\
				   	"tappez 2\n"\
				   	"sinon tappez 0\n"\
				   	);
				scanf(" %d",&bol_sauvegarde);
			}while(bol_sauvegarde < 0 || bol_sauvegarde > 2);

			

			if(bol_sauvegarde == 1)
			{
				
				chemin=malloc(sizeof(char)*26);
				strcpy(chemin,"./Plateaux/");
				
				printf("\nVeuillez donner le nom du fichier a sauvegarder :\n");
				i=11;
				chemin[i]=fgetc(stdin);
				while((chemin[i++]=fgetc(stdin)) != '\n' && i < 21);
				chemin[i-1]='\0'; /* des fois  pause probleme sur l'emplacement de '\0' */
				printf("\nPlateau sauvegardee sous le nom : ");
				for (j=11;j<i; ++j)
				{
					printf("%c",chemin[j]);
				}
				printf("\n");
				strcat(chemin,".plt");
				partie_sauvegarder(partie,chemin);
				free(chemin);
			}
			else if(bol_sauvegarde == 2)
			{
				chemin=malloc(sizeof(char)*26);
				strcpy(chemin,"./Parties/");
				if(charger)
				{
					strcpy(chemin,nomv);
					strcat(chemin,".part");
				}
				else
				{
					
					printf("\nVeuillez donner le nom de votre fichier :\n");
					i=0;
					nom[i]=fgetc(stdin);
					while((nom[i++]=fgetc(stdin))!='\n' && i<10);
					nom[i-1]='\0';
					strcat(chemin,nom);
					strcat(chemin,".part");

				}
				printf("\nReplay sauvegardee sous le nom : %s\n",nom);
				
		
				replay_sauvegarder(partie,chemin);

				free(chemin);
			}
		}
		if(bol_prom)
		{
			reponse='.';
		}
		
	}while(reponse != 'q');
}

				/********************************************/



void partie_sauvegarder(partie_t* partie, const char* chemin) /* modif */
{
	FILE* fichier = fopen(chemin,"w+");
	int i,j;

	if(fichier != NULL)
	{
		/* On met "PL" au debut du fichier */
		fprintf(fichier,"PL\n");
		
		/* On dessine le tablier dans le fichier */
		for(i=0;i<TAILLE;i++)
		{
			for(j=0;j<TAILLE;j++)
			{

				fputc(partie->tablier[i][j].type,fichier);
			
			}
			/* Retour a la ligne */
			fputc('\n',fichier);
		}

		/* On ecrit le joueur qui commencera la partie une fois chargée */
		fprintf(fichier,"%d",partie->bool_joueur);

		/* On ferme le fichier */
		fclose(fichier);
	}
	else
	{
		printf("\n\t/!\\ Erreur lors de la sauvegarde /!\\\n");
	}
}


				/********************************************/


void partie_detruire(partie_t *partie)
{
	/* Creation d'un coup (maillon) pour parcourir et detruire les coups */
	coup_t *parcours=NULL;

	/* Boucle pour parcourir les coups (maillons) */
	while(partie->coups_joues.nb_coups > 0)
	{
		/* Extraire et detruire le dernier coup (maillon) de la liste */
		parcours=extraire_fin_liste(&partie->coups_joues);
		free(parcours);
	}

	/* Destruction de la liste des coordonnées de captures */
	detruire_liste_LC(LC);
	/* Destruction de la liste (vide) contenant les données de la partie */
	free(partie);
	/* Destruction du tableau alloué pour stocker les coordonnées des deux rois */
	free(KING); 
}



/********************** PARTIE *************************/




/********************** REPLAY *************************/


partie_t *replay_charger(const char *nom)
{
	partie_t *partie=NULL;
	
	char *chemin=malloc(sizeof(char)*25);
	FILE *fichier=NULL;
	
	char *lecture_ligne=malloc(sizeof(char)*16);
	int i=0;
	coup_t *new_coup = NULL;
	

	strcpy(chemin,"Parties/"); 
	strcat(chemin,nom);
	strcat(chemin,".part");
	
	fichier=fopen(chemin,"r");	
	
	if(fichier!= NULL)
	{
		partie=partie_nouvelle();
		while((lecture_ligne[i++]=fgetc(fichier))!=EOF)
		{
			new_coup=malloc(sizeof(coup_t));
			while((lecture_ligne[i++]=fgetc(fichier))!='\n');
			
			new_coup->depart.x=atoi(lecture_ligne);
			new_coup->depart.y=atoi(&lecture_ligne[3]);
			new_coup->arrivee.x=atoi(&lecture_ligne[6]);
			new_coup->arrivee.y=atoi(&lecture_ligne[9]);
			new_coup->promotion=atoi(&lecture_ligne[12]);
			new_coup->capture=atoi(&lecture_ligne[14]);
			i=0;
				/* ajouter les coups recupérés du fichier, un par un, dans la liste des coups_joués */
			ajouter_coup_fin(partie,new_coup);

		}
			
		fclose(fichier);
		

	}
	
	free(chemin);
	free(lecture_ligne);

	return partie; 
}

				/********************************************/


void replay_jouer(partie_t* partie)
{
	char choix='p';
	coup_t* coup=partie->coups_joues.debut;

	if(coup!=NULL)
	{
		while(coup->depart.x==coup->arrivee.x && coup->depart.y==coup->arrivee.y)
		{
			changer_statut(&partie->tablier[coup->depart.x][coup->depart.y]);
			coup=coup->suivant;
		}
		replay_suivant(partie,coup->depart,coup->arrivee);
		if(coup->promotion==VRAI)
		{
			changer_statut(&partie->tablier[coup->arrivee.x][coup->arrivee.y]);
		}
		changer_joueur(partie);

		affiche_plateau(partie);
		while(choix!='q')
		{	
			
			do
			{
				printf("\n*******************\
						\n-Suivant\t(s)\
						\n-Precedent\t(p)\
						\n-Quitter\t(q)\n");
				scanf(" %c", &choix);
			}while(choix!='s' && choix!='p' && choix!='q');

			if(choix == 's')
			{
				/* suivant */
				if(coup->suivant!=NULL)
				{
					coup=coup->suivant;
					while(coup->depart.x==coup->arrivee.x && coup->depart.y==coup->arrivee.y)
					{
						changer_statut(&partie->tablier[coup->depart.x][coup->depart.y]);
						coup=coup->suivant;
					}
					replay_suivant(partie,coup->depart,coup->arrivee);
					if(coup->promotion==VRAI)
					{
						changer_statut(&partie->tablier[coup->arrivee.x][coup->arrivee.y]);
					}
					changer_joueur(partie);
					affiche_plateau(partie);
				}

				else
				{
					printf("\n\t/!\\Il ne reste plus de coups suivants... /!\\\n");
				}
			}
			else if(choix=='p')
			{
				/* precedent */
				if(coup->precedent!=NULL)
				{
					if(coup->promotion==VRAI)
					{
						changer_statut(&partie->tablier[coup->arrivee.x][coup->arrivee.y]);
					}
					replay_precedent(partie,coup->depart,coup->arrivee,coup->capture);
					coup=coup->precedent;

					while(coup->depart.x==coup->arrivee.x && coup->depart.y==coup->arrivee.y)
					{
						changer_statut(&partie->tablier[coup->depart.x][coup->depart.y]);
						if(coup->precedent!=NULL)
						{
							coup=coup->precedent;
						}
						else
						{
							break;
						}
					}
					changer_joueur(partie);
					affiche_plateau(partie);
				}
				else
				{
					printf("\n\t/!\\Il ne reste plus de coups precedents.../!\\\n");
				}
			}
		}
	}
}


				/********************************************/


void replay_precedent(partie_t *partie,coordonnees_t depart,coordonnees_t arrivee, int capture) /* modif */
{
	/* on va l'utiliser pour detacher et recuperer les informations du dernier coup joué par le joueur  */
	maillon_capture_t *last=NULL;

	/* on modifie la case d'arrivée a vide */
	modifier_case(partie,partie->tablier[arrivee.x][arrivee.y],depart);
	modifier_case(partie,partie->tablier[TAILLE-1][0],arrivee);
	
	if(capture == VRAI) /* dans le cas ou on a capturé une piece */
	{
		/* la piece qui a été capturée et remise dans le jeux a sa place */
		last=LC->debut;
		modifier_case(partie,partie->tablier[LC->debut->coord_capture.x][LC->debut->coord_capture.y],arrivee);
		/* On modifie la case de reserve de la piece extraite a vide */
		modifier_case(partie,partie->tablier[TAILLE-1][0],LC->debut->coord_capture);
		LC->debut = last->suiv;
		last->suiv=NULL;
		LC->taille--;
		free(last);

		partie->tablier[arrivee.x][arrivee.y].joueur=!partie->bool_joueur;

		if(isupper(partie->tablier[arrivee.x][arrivee.y].type)) /* on change le caractere de la piece juste pour savoir a qui appartient dorenavant la piece capturée */
		{
			partie->tablier[arrivee.x][arrivee.y].type=tolower(partie->tablier[arrivee.x][arrivee.y].type);	
		}
		else
		{
			partie->tablier[arrivee.x][arrivee.y].type=toupper(partie->tablier[arrivee.x][arrivee.y].type);		
		}
	}
}

				/********************************************/



void replay_suivant(partie_t *partie,coordonnees_t coord_depart,coordonnees_t coord_arrivee)
{
	int i=0,j=0;
	
	if(!case_vide(partie->tablier[coord_arrivee.x][coord_arrivee.y]))
	{
		if(partie->bool_joueur==JOUEUR1)
		{
			j=1;
			i=TAILLE-1;
			while(!case_vide(partie->tablier[i][j]) && (j < TAILLE-1))
			{
				j++;
			}
			while(!case_vide(partie->tablier[i][j]) && (i > 0))
			{
				i--;
			}
			partie->tablier[coord_arrivee.x][coord_arrivee.y].joueur=JOUEUR1;
		}
		else
		{
			i=0;
			j=TAILLE-2;
			while(!case_vide(partie->tablier[i][j]) && (j > 0))
			{
				j--;
			}
			while(!case_vide(partie->tablier[i][j]) && (i < TAILLE-1))
			{
				i++;
			}
			partie->tablier[coord_arrivee.x][coord_arrivee.y].joueur=JOUEUR0;
		}
		/* on stock les coordonnées de la case libre trouvée dans la reserve */
		maillon_capture_t *mc = malloc(sizeof(maillon_capture_t)); 
		mc->coord_capture.x = i;
		mc->coord_capture.y = j;
		if(LC->taille != 0)/* on declare cette liste dans la structure  */
		{
			mc->suiv = LC->debut;
		}
		else
		{
			mc->suiv = NULL;
		}
		LC->debut = mc;
		LC->taille++;
		/* on met la piece capturée dans la reserve */
		modifier_case(partie,partie->tablier[coord_arrivee.x][coord_arrivee.y],LC->debut->coord_capture);
		if(isupper(partie->tablier[i][j].type)) /* on change le caractere de la piece juste pour savoir a qui appartient desormé  la piece capturée */
		{
			partie->tablier[i][j].type=tolower(partie->tablier[i][j].type);	
		}
		else
		{
			partie->tablier[i][j].type=toupper(partie->tablier[i][j].type);		
		}
	}
	
	modifier_case(partie,partie->tablier[coord_depart.x][coord_depart.y],coord_arrivee); /* en utilise la fonction modifier pour deplacer la piece vers larriver */
	modifier_case(partie,partie->tablier[TAILLE-1][0],coord_depart); /* en initialise la case a vide  */
}

				/********************************************/



void replay_sauvegarder(partie_t *partie,const char *nom)
{
	coup_t *new_coup=partie->coups_joues.debut;
	int i=0;
	FILE *fichier=NULL;
	


	fichier=fopen(nom,"w+");

	if(fichier != NULL)
	{
		fprintf(fichier, "PR\n");
		while(i < partie->coups_joues.nb_coups && new_coup != NULL)
		{
			fprintf(fichier, "%2d %2d %2d %2d %d %d\n" ,new_coup->depart.x,new_coup->depart.y,new_coup->arrivee.x,new_coup->arrivee.y,new_coup->promotion,new_coup->capture);
			new_coup=new_coup->suivant;	
		}
		
	}
	else
	{
		printf("\n\t/!\\ Erreur lors de la sauvegarde du fichier /!\\\n");
	}
}


/********************** REPLAY *************************/


/********************** LISTES *************************/


void ajouter_coup_fin(partie_t *partie,coup_t *new_coup)
{

	new_coup->suivant=NULL;
	new_coup->precedent=partie->coups_joues.fin; 
	
	if (partie->coups_joues.nb_coups != 0)
	{
		partie->coups_joues.fin->suivant=new_coup;
	}
	else
	{
		partie->coups_joues.debut=new_coup;
	}

	partie->coups_joues.fin=new_coup;
			
	partie->coups_joues.nb_coups++;
}

				/********************************************/


coup_t *extraire_fin_liste(liste_t *liste) // cette fonction en l'utilisera dans detruire partie
{
	coup_t *resultat=liste->fin;

	if(liste->nb_coups != 0)
	{
		if(liste->nb_coups != 1)
		{
			liste->fin=resultat->precedent;
			liste->fin->suivant=NULL;
		}
		else
		{
			liste->fin=NULL;
			liste->debut=NULL;
		}
		liste->nb_coups--;
		resultat->precedent=NULL;
	}
	return resultat;
}

				/********************************************/


void detruire_liste_LC(liste_capture_t *lc)
{
	maillon_capture_t *last_coup=NULL;

	while(lc->taille != 0)
	{
		last_coup = LC->debut;
		LC->debut = last_coup->suiv;
		last_coup->suiv=NULL;
		LC->taille--;
		free(last_coup);	
	}
	
	free(lc);
}


/********************** LISTES *************************/


/********************** DEPLACEMENTS *********************/


void deplacement(partie_t *partie,coordonnees_t coord_depart,coordonnees_t coord_arrivee)
{
	int i=0,j=0,bool_capture=FAUX,bool_promotion=FAUX,reponse=FAUX;
	coup_t *new_coup=malloc(sizeof(coup_t));  /* on l'utilise pour l'ajout d'un coup a la liste */

	if(!case_vide(partie->tablier[coord_arrivee.x][coord_arrivee.y]))
	{
		if(partie->bool_joueur==JOUEUR1)
		{
			j=1;
			i=TAILLE-1;
			while(!case_vide(partie->tablier[i][j]) && (j < TAILLE-1))
			{
				j++;
			}
			while(!case_vide(partie->tablier[i][j]) && (i > 0))
			{
				i--;
			}
			partie->tablier[coord_arrivee.x][coord_arrivee.y].joueur=JOUEUR1;

		}
		else
		{
			i=0;
			j=TAILLE-2;
			while(!case_vide(partie->tablier[i][j]) && (j > 0))
			{
				j--;
			}
			while(!case_vide(partie->tablier[i][j]) && (i < TAILLE-1))
			{
				i++;
			}
			partie->tablier[coord_arrivee.x][coord_arrivee.y].joueur=JOUEUR0;

		}
		bool_capture=VRAI;
		/* on stock les coordonnées de la case libre trouvée dans la reserve */
		maillon_capture_t *mc = malloc(sizeof(maillon_capture_t)); 
		mc->coord_capture.x = i;
		mc->coord_capture.y = j;
		if(LC->taille != 0)/* on declare cette liste dans la structure  */
		{
			mc->suiv = LC->debut;
		}
		else
		{
			mc->suiv = NULL;
		}
		LC->debut = mc;
		LC->taille++;
		/* on regard les coordonner du roi si l'adversaire la capturer  */
		if(coord_arrivee.x == KING[!partie->bool_joueur].x && coord_arrivee.y == KING[!partie->bool_joueur].y)
		{
			printf("\n*** Le roi du joueur %d a été capturé, fin de la partie ***\n",!partie->bool_joueur);
		}
		/* on met la piece capturée dans la reserve  */
		modifier_case(partie,partie->tablier[coord_arrivee.x][coord_arrivee.y],LC->debut->coord_capture);
		if(isupper(partie->tablier[i][j].type)) /* on change le caractere de la piece juste pour savoir a qui appartient desormé  la piece capturée */
		{
			partie->tablier[i][j].type=tolower(partie->tablier[i][j].type);	
		}
		else
		{
			partie->tablier[i][j].type=toupper(partie->tablier[i][j].type);		
		}
	}
	
	modifier_case(partie,partie->tablier[coord_depart.x][coord_depart.y],coord_arrivee); /* en utilise la fonction modifier pour deplacer la piece vers larriver */
	modifier_case(partie,partie->tablier[TAILLE-1][0],coord_depart); /* en initialise la case a vide  */
	
	if(partie->tablier[coord_arrivee.x][coord_arrivee.y].statut == NON_PROMUE)
	{
		
		if(partie->tablier[coord_arrivee.x][coord_arrivee.y].type != 'G'  && partie->tablier[coord_arrivee.x][coord_arrivee.y].type != 'K'\
		 && partie->tablier[coord_arrivee.x][coord_arrivee.y].type != 'g'&& partie->tablier[coord_arrivee.x][coord_arrivee.y].type != 'k') /* pour la promotion */
		{
			if((partie->bool_joueur==JOUEUR1 && coord_arrivee.x < 4) || (partie->bool_joueur == JOUEUR0 && coord_arrivee.x > 6))
			{
				/* Promouvoir obligatoirement ou demander au joueur */
				if(tolower(partie->tablier[coord_arrivee.x][coord_arrivee.y].type == 'p') && (coord_arrivee.x == 1 || coord_arrivee.x == 9))
				{
					changer_statut(&partie->tablier[coord_arrivee.x][coord_arrivee.x]);
					bool_promotion=VRAI;
				}
				else if((partie->tablier[coord_arrivee.x][coord_arrivee.y].type == 'l' && coord_arrivee.x == 1) || (partie->tablier[coord_arrivee.x][coord_arrivee.y].type == 'L' && coord_arrivee.x == 9))
				{
					changer_statut(&partie->tablier[coord_arrivee.x][coord_arrivee.y]);
					bool_promotion=VRAI;
				}
				else if((partie->tablier[coord_arrivee.x][coord_arrivee.y].type == 'n' && coord_arrivee.x < 3) ||(partie->tablier[coord_arrivee.x][coord_arrivee.y].type == 'N' && coord_arrivee.x > 7))
				{
					changer_statut(&partie->tablier[coord_arrivee.x][coord_arrivee.y]);
					bool_promotion=VRAI;
				}
				else
				{ 
					do
					{
						printf("\nVoulez-vous promouvoire la piece jouer ?\
								\nsi oui tapper : 1\
								\nsi non tapper: 0\n");
						scanf(" %d",&reponse);
					}while(reponse != VRAI && reponse != FAUX);

					if(reponse)
					{
						changer_statut(&partie->tablier[coord_arrivee.x][coord_arrivee.y]);
						affiche_plateau(partie);
						bool_promotion=VRAI;
					}
				}
			}
		} 
	}

	/* initialisation du new_coup */
	new_coup->promotion=bool_promotion;
	new_coup->capture=bool_capture;
		
	new_coup->depart=coord_depart;
	new_coup->arrivee=coord_arrivee;
			
	/* ajouter le new_coup a la liste */

	ajouter_coup_fin(partie,new_coup);
}

				/********************************************/


int deplacement_valide(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie)
{
	int bol_roi=FAUX;

	
	
		if(depart.x < TAILLE-1 && depart.x > 0 && depart.y < TAILLE-1 && depart.y > 0) 
		{
			if(partie->bool_joueur == piece_joueur(partie->tablier[depart.x][depart.y]))
			{
				switch(tolower(partie->tablier[depart.x][depart.y].type))
				{
					if(partie->tablier[depart.x][depart.y].statut==PROMUE)
					{
						case 'p': return deplacement_valide_pion(depart,arrivee,partie);
						case 'l': return deplacement_valide_lance(depart,arrivee,partie);
						case 'n': return deplacement_valide_cavalier(depart,arrivee,partie);
						case 'b': return deplacement_valide_fou(depart,arrivee,partie);
						case 'r': return deplacement_valide_tour(depart,arrivee,partie);
						case 's': return deplacement_valide_silver(depart,arrivee,partie);
						case 'g': return deplacement_valide_gold(depart,arrivee,partie);
						case 'k':
								 {
									bol_roi=deplacement_valide_roi(depart,arrivee,partie);
									if(bol_roi)
									{
										KING[partie->bool_joueur]=arrivee; /* on suavegarde les coordonnées d'arrivée du roi */
									}
									return bol_roi;
								}
					}
					else 
					{
						case 'd': return deplacement_valide_gold(depart,arrivee,partie);
						case 'j': return deplacement_valide_gold(depart,arrivee,partie);
						case 'c': return deplacement_valide_gold(depart,arrivee,partie);
						case 'f': return deplacement_valide_horse(depart,arrivee,partie);
						case 't': return deplacement_valide_dragon(depart,arrivee,partie);
						case 'a': return deplacement_valide_gold(depart,arrivee,partie);
					}
				}
			}
		}

		else /* si on est dans la reserve (cas d'un parachutage)  */
		{
			
			if(partie->bool_joueur == piece_joueur(partie->tablier[depart.x][depart.y]))
			{
				
				if(case_vide(partie->tablier[arrivee.x][arrivee.y])) /* on peut pas capturé une piece donc l'arrivée doit etre vide */
				{
					
					return (parachutage(depart,arrivee,partie)); /* le deplacement est fait a l'interieur de la fonction parachutage si le roi n'ai pas on echec  */
				}

			}
		}
	
	
	return FAUX;
}

				/********************************************/



int deplacement_valide_tour(coordonnees_t d, coordonnees_t a, partie_t* partie)
{
	if(d.x==a.x)
	{
		if(a.y<d.y && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			int i;
			for(i=(d.y-1);i>a.y;i--)
			{
				if(!case_vide(partie->tablier[a.x][i]))
				{
					return FAUX;
				}
			}
		}
		else if(a.y>d.y && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			int i;
			for(i=(d.y+1);i<a.y;i++)
			{
				if(!case_vide(partie->tablier[a.x][i]))
				{
					return FAUX;
				}
			}
		}
		return VRAI;
	}
	else if(d.y==a.y)
	{
		if(a.x<d.x && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			int i;
			for(i=(d.x-1);i>a.x;i--)
			{
				if(!case_vide(partie->tablier[i][a.y]))
				{
					return FAUX;
				}
			}
		}
		else if(a.x>d.x && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			int i;
			for(i=(d.x+1);i<a.x;i++)
			{
				if(!case_vide(partie->tablier[i][a.y]))
				{
					return FAUX;
				}
			}
		}
		return VRAI;
	}
	return FAUX;
}

				/********************************************/



int deplacement_valide_horse(coordonnees_t d, coordonnees_t a, partie_t* partie)
{
	if(deplacement_valide_fou(d,a,partie)==FAUX)
	{
		if(d.x==a.x)
		{
			if(abs(d.y-a.y)==1 && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
			{
				return VRAI;
			}
		}
		else if(d.y==a.y)
		{
			if(abs(d.x-a.x)==1 && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
			{
				return VRAI;
			}
		}
		return FAUX;
	}
	return VRAI;
}

				/********************************************/



int deplacement_valide_dragon(coordonnees_t d, coordonnees_t a, partie_t* partie)
{
	if(deplacement_valide_tour(d,a,partie)==FAUX)
	{
		if(abs(d.x-a.x)==abs(d.y-a.y) && abs(d.x-a.x)==1 && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			return VRAI;
		}
		return FAUX;
	}
	return VRAI;
}

				/********************************************/



int deplacement_valide_roi(coordonnees_t d, coordonnees_t a, partie_t *partie)
{
	if(abs(d.x-a.x)==abs(d.y-a.y) && abs(d.x-a.x)==1 && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
	{
		return VRAI;
	}
	else if(d.x==a.x)
	{
		if(abs(d.y-a.y)==1 && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			return VRAI;
		}
	}
	else if(d.y==a.y)
	{
		if(abs(d.x-a.x)==1 && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			return VRAI;
		}
	}
	return FAUX;
}


				/********************************************/


int deplacement_valide_silver(coordonnees_t d, coordonnees_t a, partie_t* partie)
{
	
	if(abs(d.x-a.x)==abs(d.y-a.y) && abs(d.x-a.x)==1 && partie->tablier[a.x][a.y].joueur != partie->bool_joueur)
	{
		
		return VRAI;
	}
	else if(d.y==a.y)
	{
		if(d.x-a.x == 1 && partie->bool_joueur == JOUEUR1 && partie->tablier[a.x][a.y].joueur != JOUEUR1 ) /*J1*/
		{
				return VRAI;
		}

		else if(a.x-d.x == 1 && partie->bool_joueur == JOUEUR0 && partie->tablier[a.x][a.y].joueur != JOUEUR0) /*J0*/
		{
				return VRAI;
		}
	}
	return FAUX;
}

				/********************************************/



int deplacement_valide_gold(coordonnees_t d, coordonnees_t a, partie_t* partie)
{
	if(a.y==d.y)
	{
		if(abs(d.x-a.x)==1 && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			return VRAI;
		}	
	}
	else if(abs(a.y-d.y)==1)
	{
		if(a.x==d.x && partie->tablier[a.x][a.y].joueur!=partie->bool_joueur)
		{
			return VRAI;
		}
		else if(partie->bool_joueur==JOUEUR1 && a.x==d.x-1 && partie->tablier[a.x][a.y].joueur!=JOUEUR1)
		{
			return VRAI;
		}
		else if(partie->bool_joueur==JOUEUR0 && a.x==d.x+1 && partie->tablier[a.x][a.y].joueur!=JOUEUR0)
		{
			return VRAI;
		}
	}
	return FAUX;
}

				/********************************************/



int deplacement_valide_fou(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie)
{
	int i,j;
	if(partie->tablier[depart.x][depart.y].joueur == partie->tablier[arrivee.x][arrivee.y].joueur) /* Si la piece qui se trouve dans les coordonnées d'arrivée est celle du joueur qui fait le deplacement */
		{
			return FAUX; /* alors on ne peut pas faire le deplacement */
		}
	if(abs(arrivee.x-depart.x) == abs(arrivee.y-depart.y)) /* Si la case d'arrivée est l'une des quatres coins d'un carré */
	{
		if((arrivee.x < depart.x) && (arrivee.y < depart.y)) /* si la case d'arrivée se trouve en haut a gauche */
		{
			for(i=depart.x-1,j=depart.y-1; i>arrivee.x; i--,j--) /* on parcour toutes les cases entre la case de depart et celle d'arrivée */
			{
				if(!case_vide(partie->tablier[i][j])) /* on verifie si la case n'est pas vide alors on peut pas faire le deplacement */
				{
					return FAUX;
				}
			}
		}
		else if((arrivee.x < depart.x) && (arrivee.y > depart.y)) /* si la case d'arrivée se trouve en haut a droite */
		{
			
			for(i=depart.x-1,j=depart.y+1; i>arrivee.x; i--,j++)
			{
			
				if(!case_vide(partie->tablier[i][j]))
				{
					return FAUX;
				}
			}
		}
		else if((arrivee.x > depart.x) && (arrivee.y < depart.y)) /* si la case d'arrivée se trouve en bas a gauche */
		{
			for(i=depart.x+1,j=depart.y-1; i>arrivee.x; i++,j--)
			{
				if(!case_vide(partie->tablier[i][j]))
				{
					return FAUX;
				}
			}
		}
		else /* si la case d'arrivée se trouve en bas a droite */
		{
			for(i=depart.x+1,j=depart.y+1; i>arrivee.x; i++,j++)
			{
				if(!case_vide(partie->tablier[i][j]))
				{
					return FAUX;
				}
			}
		}
		return VRAI;
	}
	return FAUX;
}

				/********************************************/



int deplacement_valide_cavalier(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie)
{
	if((depart.y == arrivee.y+1) || (depart.y == arrivee.y-1)) /* si la colonne d'arrivée est la colonne suivante gauche/droite de la colonne de depart  */
	{
		if(partie->tablier[depart.x][depart.y].joueur == JOUEUR1) /* le joueur 1 qui fait le deplacement */
		{
			if(depart.x-2 == arrivee.x)  /* si la ligne d'arrivée se trouve a deux lignes de la ligne de depart  */
			{
				if(partie->tablier[arrivee.x][arrivee.y].joueur != JOUEUR1)/* Si la piece qui se trouve dans les coordonnées d'arrivée est celle du joueur 1 */
				{
					return VRAI;
				}
			}
		}
		else /* le joueur 0 qui fait le deplacement */
		{
			if(depart.x+2 == arrivee.x)
			{
				if(partie->tablier[arrivee.x][arrivee.y].joueur != JOUEUR0)  /* Si la piece qui se trouve dans les coordonnées d'arrivée est celle du joueur 0 */
				{
					return VRAI;
				}
			}
		}
	}
	return FAUX;
}

				/********************************************/



int deplacement_valide_lance(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie)
{
	int i;
	if(arrivee.y == depart.y)
	{
		if(partie->tablier[depart.x][depart.y].joueur != partie->tablier[arrivee.x][arrivee.y].joueur)
		{
			if(partie->tablier[depart.x][depart.y].joueur == JOUEUR1)
			{
				for(i=(depart.x-1); i > arrivee.x; i--)
				{
					if(!case_vide(partie->tablier[i][depart.y]))
					{
						return FAUX;
					}
				}
				return VRAI;
			}
			else 
			{
				for(i=(depart.x+1); i < arrivee.x; i++)
				{
					if(!case_vide(partie->tablier[i][depart.y]))
						{
							return FAUX;
						}
				}
				return VRAI;
			}
		}
	}
	return FAUX;
}

				/********************************************/



int deplacement_valide_pion(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie)
{
	if(partie->tablier[depart.x][depart.y].joueur == JOUEUR1)
	{
		if((arrivee.y == depart.y) && ((arrivee.x+1) == depart.x))
		{
			if(partie->tablier[arrivee.x][arrivee.y].joueur != JOUEUR1)
			{
				return VRAI;
			}
		}
	}
	else
	{
		if((arrivee.y == depart.y) && ((arrivee.x-1) == depart.x))
		{
			if(partie->tablier[arrivee.x][arrivee.y].joueur != JOUEUR0)
			{
				return VRAI;
			}
		}
	}
	return FAUX;
}

				/********************************************/



void annuler_deplacement(partie_t *partie)
{
	/* last_coup est  un pointeur de coups qui pointe vers le dernier coups jouer  */
	/* on va l'utiliser pour detacher et recuperer les information du dernier coup joué par le joueur  */

	coup_t *last_coup=partie->coups_joues.fin;
	maillon_capture_t *last=NULL;

	if(partie->coups_joues.nb_coups > 1)
	{
		last_coup->precedent->suivant=NULL; /* detache le dernier maillon_coup de lavant dernier */
		partie->coups_joues.fin=last_coup->precedent; /* le champs fin reçoit l'adresse de l'avant dernier qui devient donc le dernier */
	}
	partie->coups_joues.nb_coups--; 

	/* deplace la piece vers son origine de depart*/
	/* on modifie la case d'arriver a vide */
	modifier_case(partie,partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y],last_coup->depart);
	modifier_case(partie,partie->tablier[TAILLE-1][0],last_coup->arrivee);
	
	if(last_coup->capture == VRAI) /* dans le cas ou en a capturer une piece */
	{
		/* la piece qui a était capturer et remise dans le jeux a sa place */
		last=LC->debut;
		modifier_case(partie,partie->tablier[LC->debut->coord_capture.x][LC->debut->coord_capture.y],last_coup->arrivee);
		/*  en modifie la reserve de la piece extraite a vide */
		modifier_case(partie,partie->tablier[TAILLE-1][0],LC->debut->coord_capture);
		LC->debut = last->suiv;
		last->suiv=NULL;
		LC->taille--;
		free(last);

		partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y].joueur=(!partie->bool_joueur);
		if(isupper(partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y].type)) /* on change le caractere de la piece juste pour savoir a qui appartient desormé  la piece capturée  */
		{
			partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y].type=tolower(partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y].type);	
		}
		else
		{
			partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y].type=toupper(partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y].type);		
		}

	}
	if(last_coup->promotion == PROMUE)
	{
		changer_statut(&partie->tablier[last_coup->depart.x][last_coup->depart.y]);
		/* si il y'a eu une promotion on remet la piece a l'état précédent sinon elle reste telle qu'elle est */
	}

	free(last_coup);

	if(partie->coups_joues.nb_coups > 0)
	{
		/* annuler les promotions faite avant le dernier deplacement */
		while(partie->bool_joueur == partie->tablier[partie->coups_joues.fin->arrivee.x][partie->coups_joues.fin->arrivee.y].joueur)
		{
			last_coup = extraire_fin_liste(&partie->coups_joues);
			changer_statut(&partie->tablier[last_coup->arrivee.x][last_coup->arrivee.y]);
			free(last_coup);
		}
	}
}

				/********************************************/



int promotion(partie_t *partie) /* parcourir les trois premieres case du tablier pour voir si il existe des pieces qui peuvent etre promues */
{
	int i,j, reponse=FAUX;

	coup_t *new_coup=NULL;
	
	if(partie->bool_joueur == JOUEUR1) /* pour le JOUEUR1 */
	{
		for(i=1; i<4; i++) /* parcourir les 3 premieres lignes du tablier */
		{
			for(j=1; j<TAILLE-1; j++) /* parcourir toutes les colonnes (des trois premieres lignes) */
			{
				/* tester si la piece appartient au JOUEUR1 et elle n'est pas promue et elle est differente du roi et du general d'or (qui ne peuevtn pas etre promue) */
				
				if((partie->tablier[i][j].joueur == JOUEUR1) && (partie->tablier[i][j].statut == NON_PROMUE) && (partie->tablier[i][j].type != 'k') && (partie->tablier[i][j].type != 'g'))
				{
					do
					{
						/* afficher a l'utilisateur le type de la piece et ses coordonnees  et demander s'il desir la promouvoir */
						printf("\nVoulez vous promouvoir la piece %c qui se trouve a la ligne %d, colonne %d ?\n Tapez 1 pour oui et 0 pour non\n",partie->tablier[i][j].type,i,j);
						scanf("%d",&reponse);
					}while((reponse != FAUX) && (reponse != VRAI)); /* Si la reponse n'est pas valide (un nombre diffenrent de 1 et 0) */
					if(reponse) /* Si la reponse est OUI (1)  */
					{
						changer_statut(&partie->tablier[i][j]); /* changer le statut ( promouvoir la piece) */

						new_coup=malloc(sizeof(coup_t)); /* on alloue un nouveau maillon que si , on fait une promotion  */

						new_coup->capture=VRAI;
						new_coup->promotion=PROMUE;
						new_coup->depart.x=i;
						new_coup->depart.y=j;
						new_coup->arrivee=new_coup->depart;
						ajouter_coup_fin(partie,new_coup);
						return VRAI; /*si il y'a eux promotion je retourne  vrai */


					}
				}
			}
		}
	}
	else /* if(partie->bool_joueur == JOUEUR0) pour le JOUEUR0 */
	{
		for(i=TAILLE-4; i<TAILLE-1; i++) /* parcourir les 3 dernieres lignes du tablier  */
		{
			for(j=1; j<TAILLE-1; j++) /* parcourir toutes les colonnes  */
			{
				if((partie->tablier[i][j].joueur == JOUEUR0) && (partie->tablier[i][j].statut != PROMUE) && (partie->tablier[i][j].type != 'K') && (partie->tablier[i][j].type != 'G'))
				{
					do
					{
						printf("\nVoulez vous promouvoir la piece %c qui se trouve a la ligne %d, colonne %d ?\nTapez 1 pour oui et 0 pour non\n",partie->tablier[i][j].type,i,j);
						scanf("%d",&reponse);
					}while((reponse != 0) && (reponse != 1));
					if(reponse)
					{
						changer_statut(&partie->tablier[i][j]);

						new_coup=malloc(sizeof(coup_t)); /* on alloue un nouveau maillon que si , on fait une promotion  */

						new_coup->capture=VRAI;
						new_coup->promotion=PROMUE;
						new_coup->depart.x=i;
						new_coup->depart.y=j;
						new_coup->arrivee=new_coup->depart;
						ajouter_coup_fin(partie,new_coup);
						
						return VRAI; /*si il y'a eux promotion je return vrai */
						
						
					}
				}
			}
		}
	}
	return FAUX;
}

				/********************************************/



int parachutage(coordonnees_t depart,coordonnees_t arrivee, partie_t *partie)
{
	int i=1;

	if(tolower(partie->tablier[depart.x][depart.y].type)=='p') /* Le cas du parachutage d'un pion */
	{
		for(i=1;i<TAILLE-1;i++) /* on parcour la colonne d'arrivée si il n'y a aucun pion non_promue du joueur adverse */
		{
			/* si on trouve un pion non_promu apartenant au joueur adverse dans la meme colonne dont on veut parachuter notre pion */
			if(tolower(partie->tablier[i][arrivee.y].type) == 'p' && partie->bool_joueur == partie->tablier[i][arrivee.y].joueur)
			{
				return FAUX; /* on retourn faux (le parachutage ne peut pas avoir lieu) */
			}
		}
	}
	deplacement(partie,depart,arrivee); /* on parachute la piece a sa coordonner d'arrivee */
	if(deplacement_valide(arrivee,KING[!partie->bool_joueur],partie)) /* on verifie que le roie n'est pas on echec  */
	{
		annuler_deplacement(partie); /* si le roi est on echec en annule le coup */
		return FAUX;
	}
	changer_joueur(partie); /* sinon on laisse le deplacement on change de joueur  */
	affiche_plateau(partie); /* on affiche a la fin le plateau  */
	printf("\n********** Tour du joueur %d **********\n",partie->bool_joueur);

	return FAUX; /* on retourne faux pour que le deplacement dans partie_jouer ne s'effectue pas car on l'a deja fait  */
}


/***************************PROTOTYPE**************************************************/












































