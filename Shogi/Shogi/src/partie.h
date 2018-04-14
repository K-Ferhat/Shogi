#ifndef PARTIE_H
#define PARTIE_H

/*************LES BIBLIOTHEQUE**********************/
#include <stdio.h>      /* printf(), scanf()*/
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <string.h>   /* strcpy() */
#include <ctype.h>   /* isupper(), toupper(), tolower() */
/*************LES BIBLIOTHEQUE**********************/


/****************************************LES CONSTANTE SYMBOLIQUE********************/

#define JOUEUR1 1		        /* Joueur numero 1 */
#define JOUEUR0 0		       /* Joueur numero 0 */
#define JOUEUR_VIDE -1 	      /* Pour les cases ne contenants pas de pieces */
#define PROMUE 1		     /* Piece promue */
#define NON_PROMUE 0	    /* Piece non promue */
#define VIDE -1			   /* Statut pour les cases vides */
#define VRAI 1			  /* Valeur Vraie pour les conditions */ 
#define FAUX 0			 /* Valeur Fausse pour les conditions */
#define TAILLE 11 		/* Nombre de lignes et de colonnes du tablier (avec la réserve) */

/****************************************LES CONSTANTE SYMBOLIQUE********************/



/*****************************DEBUT LA DEFINITION DES STRUCTURE*************************************/

/* STRUCTURE CONTENANT LES INFORMATIONS D'UNE PIECE  */
typedef struct
{
    int joueur;   /* Propriétaire (Joueur1 ou Joueur0) */
    char type;   /* Le caractere represantant la piece */
    int statut; /* Promue ou non promue */
}piece_t;



/* STRUCTURE CONTENANT LES INFORMATION D'UNE COORDONNER DANS UN PLAN CARTESIEN (X,Y) */
typedef struct 
{
	int x;  /* Lignes */
	int y; /* Colonnes */
}coordonnees_t;





/* MAILLON REPRESENTANT UN COUPS */
typedef struct coup_s coup_t;

struct coup_s 
{
	coordonnees_t depart;   /* Coordonnées de la piece avant le deplacement (au depart) */
	coordonnees_t arrivee; /* Coordonnées de la piece aprés le deplacement (à l'arrivée) */ 
	int promotion;        /* Booleen indiquant si une promotion a eu lieu */
	int capture;         /* Booleen indiquant si une capture a eu lieu */
	coup_t *suivant;    /* Pointeur vers le coup (maillon) suivant (si il y en a)  */
	coup_t *precedent; /* Pointeur vers le coup (maillon) precedent (si il y en a) */
};




/* LISTE POUR LES COUPS EFFECTUER */ 
typedef struct 
{
	coup_t *debut; /* Adresse du premier coup (maillon) */
	int nb_coups; /* Nombre de coups effectués (maillons existants) */
	coup_t *fin; /* Adresse du dernier coup (maillon) */
}liste_t;





/* STRUCTURE CONTENANT LES INFORMATION D'UNE PARTIE EN COURS */
typedef struct 
{
	piece_t tablier[TAILLE][TAILLE]; // ShogiBan
	liste_t coups_joues; // Liste des coups effectués
	int bool_joueur; // Joueur dont c'est le tour de jouer
}partie_t;





/*MAILLON REPRESENTANT LES  COORDONNÉES DE LA CASE ACCEULLANT LA PIECE CAPTURÉE*/

typedef struct maillon_capture_s maillon_capture_t;
struct maillon_capture_s
{
	coordonnees_t coord_capture; /* Coordonnées de la case de la reserve */
	maillon_capture_t *suiv;    /* Pointeur vers le maillon suivant */
};




/*LISTE POUR LES CAPTURES EFFECTUÉES */

typedef struct
{
	maillon_capture_t *debut; /* Adresse des premieres coordonnées (maillon) */
	int taille; /* Nombre de pieces dans les reserves (maillons existants) */
}liste_capture_t; 



/******************************************************************/
/******************************************************************/




/*****************************DECLARATION DES VARIABLES GLOBALES******************************/

liste_capture_t *LC; /* Liste contenant les positions des pieces mises dans la reserve (les pieces capturées)*/
coordonnees_t *KING; /* Tableau de sauvegarde des coordonnées des 2 rois */ 

/*
	(petite astuce en a un tableau a une dimension de taille 2 )
 	KING[0]= JOUEUR0 (bool_joueur)
  	KING[1]= JOUEUR1 (bool_joueur) 
*/


/*****************************DECLARATION DES VARIABLES GLOBALES******************************/
/*****************************DEBUT DES FONCTIONS HEADERS *****************************/
 


/********************** LES FONCTIONS POUR LES PIECES **************************/

 /** Cree une piece qui appartient un joueur "joueur", de type "type" et de statut "statut" **/
piece_t piece_creer(int joueur,char type,int statut);
 /** Identifie la piece correspondante au caractere "type" **/
piece_t piece_identifier(char type);
 /** Renvoie le caractere (qui est le type) associé à la piece "piece" **/
char piece_caractere(piece_t piece);
 /** Renvoie le joueur associé à la piece "piece" **/
int piece_joueur(piece_t piece);
 /** Change le statut de la pièce "piece" (promue en non promue et vice versa **/
void changer_statut(piece_t *piece);
 /** Affiche le caractere associé à la piece "piece" **/
void piece_afficher(piece_t piece);

/********************** LES FONCTION POUR LES PIECE PIECE **************************/



/********************************LISTE**************************************/

 /** ajoute le coup "new_coup" à la fin de la liste_coups_joues de la partie "partie" **/
void ajouter_coup_fin(partie_t *partie,coup_t *new_coup);
 /** Extrait le dérnier maillon de la liste "liste" **/
coup_t *extraire_fin_liste(liste_t *liste);
 /** Libère l'espace occupé par la liste chainée "lc" **/
void detruire_liste_LC(liste_capture_t *lc);


/********************************LISTE**************************************/


/*****************FONCTION SECONDAIRE******************/

void affiche_plateau(partie_t *partie);
void changer_joueur(partie_t *partie );
int case_vide(piece_t caze);
void modifier_case(partie_t *partie,piece_t piece,coordonnees_t coords);
 /** Teste si les coordonnées sont valide et les renvoie **/
void test_coordonnees(coordonnees_t *depart, coordonnees_t *arrivee);
 /** Renvoie VRAI si le roi est en echec, FAUX sinon **/
int echec(partie_t *partie);

/*****************FONCTION SECONDAIRE******************/



/********************** PARTIE *************************/

 /** Allocation de l'espace mémoire pour la partie et initialisation à NULL **/
partie_t *partie_creer();
 /** Crée une nouvelle partie en mettant les pièces dans le tablier **/
partie_t *partie_nouvelle();
partie_t *partie_charger(const char* chemin);
void partie_jouer(partie_t *partie,int charger,const char *nomv);
 /** Sauvegarde le tablier ainsi que le joueur de la partie dans un fichier "nom" **/
void partie_sauvegarder(partie_t* partie, const char* chemin);
 /** Libère l'espace mémoire occupé par la partie **/
void partie_detruire(partie_t *partie);

/********************** PARTIE *************************/


/********************** REPLAY *************************/

partie_t *replay_charger(const char *nom);
void replay_jouer(partie_t* partie);
 /** Aller au coup suivant **/
void replay_suivant(partie_t *partie,coordonnees_t coord_depart,coordonnees_t coord_arrivee);
 /** Revenir au coup précédent **/
void replay_precedent(partie_t *partie,coordonnees_t coord_depart,coordonnees_t coord_arrivee,int capture);
 /** Sauvegarde la partie entière dans un fichier "nom" **/
void replay_sauvegarder(partie_t *partie,const char *nom);

/********************** REPLAY *************************/






/********************** DEPLACEMENTS *********************/

 /** Deplacer une pièce de la case d'arrivée vers la case du départ dans le tablier **/
void deplacement(partie_t *partie,coordonnees_t coord_depart,coordonnees_t coord_arrivee);
 /** Retourne vrai si le deplacement de lapièce est valide, FAUX sinon **/
int deplacement_valide(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie);
 /** Retourne VRAI si le déplacement de la tour dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_tour(coordonnees_t d, coordonnees_t a, partie_t* partie);
 /** Retourne VRAI si le déplacement d'une tour promue dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_horse(coordonnees_t d, coordonnees_t a, partie_t* partie);
 /** Retourne VRAI si le déplacement d'un fou promu dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_dragon(coordonnees_t d, coordonnees_t a, partie_t* partie);
 /** Retourne VRAI si le déplacement du roi dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_roi(coordonnees_t d, coordonnees_t a, partie_t *partie);
 /** Retourne VRAI si le déplacement du général d'argent dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_silver(coordonnees_t d, coordonnees_t a, partie_t* partie);
 /** Retourne VRAI si le déplacement du général d'or dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_gold(coordonnees_t d, coordonnees_t a, partie_t* partie);
 /** Retourne VRAI si le déplacement du fou dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_fou(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie);
 /** Retourne VRAI si le déplacement du cavalier dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_cavalier(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie);
 /** Retourne VRAI si le déplacement de la lance dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_lance(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie);
 /** Retourne VRAI si le déplacement du pion dans les coordonnées donnés est vailde, FAUX sinon **/
int deplacement_valide_pion(coordonnees_t depart,coordonnees_t arrivee,partie_t *partie);

 /** Annule le déplacement d'une pièce ( remet la pièce a sa case de départ **/
void annuler_deplacement(partie_t *partie);

int promotion(partie_t *partie);
 /** Retourne VRAI si le parachutage est valide, FAUX sinon**/
int parachutage(coordonnees_t depart,coordonnees_t arrivee, partie_t *partie);

/********************** DEPLACEMENTS *********************/



/*****************************FIN DES FONCTIONS HEADERS *****************************/


/**********************************/


#endif