#include <stdio.h> /* printf(), scanf() */
#include <stdlib.h> /* EXIT_SUCCESS */
#include "partie.h"


/* En argument : Nom du fichier a charger */
int main(int argc, char **argv)
{
	partie_t *p=NULL;
	char *nom_argv=NULL;
	int reponse=1;

	/* Pas d'arguments => Nouvelle partie */
	if(argc == 1)
	{
		printf("\n\n********** Nouvelle partie **********\n");
		p=partie_nouvelle();
		partie_jouer(p,FAUX,nom_argv);	/*nom_argv=NULL*/	
	}
	/* Un argument => Charger partie ou replay */
	else if(argc == 2)
	{
		nom_argv=malloc(sizeof(char)*25);
		strcpy(nom_argv,argv[1]);

		/* partie et replay disponibles */
		if(((p=partie_charger(nom_argv))) != NULL && replay_charger(nom_argv) != NULL ) /* on donne juste le nom pas le chemin */
		{	
			do
			{
				printf("\nSi vous voulez charger la partie \nTappez 1\nSi vous voulez faire un replay\nTappez 0\n");
				scanf(" %d",&reponse);
			} while (reponse != 1 && reponse != 0);
			
			if(reponse)
			{
				partie_jouer(p,VRAI,nom_argv);	
			}
			else
			{
				p=replay_charger(nom_argv);
				replay_jouer(p);
			}
		}
		/* Partie disponible */
		else if((p=partie_charger(nom_argv)) != NULL)
		{
			partie_jouer(p,VRAI,nom_argv);
		}
		/* Replay disponnible */
		else if((p=replay_charger(nom_argv)) != NULL)
		{
			replay_jouer(p);
		}
		else
		{
			printf("\n\t/!\\ Erreur le fichier n'existe pas /!\\\n");

			free(nom_argv);
			return EXIT_FAILURE;
		}
		/* Liberer l'espace alloué */
		free(nom_argv);
	}
	/* Nombre d'arguments depassant 1 */ 
	else
	{
		 printf("\n\t/!\\ Erreur veuillez saisir moins de 2 arguments /!\\\n");
		 return EXIT_FAILURE;
	}

	/* Detruire la partie */
	partie_detruire(p);	
	
	/* Execution reussie */
	return EXIT_SUCCESS;
}