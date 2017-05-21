#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "affiche.h"

int gagnant(int j1, int j2, int c1, int c2) {
	//j est le score du joueur
	int j;
	if (j2 > 21){
		j = j1;
	}
	else{
		j = j2;
	}
	/**c est le score du croupier**/
	int call;
	if (c2 > 21)
		call = c1;
	else
		call = c2;
	//si le croupier est busted
	if (call > 21)
		return 1;
	//si le joueur est busted
	if (j > 21)
		return 0;
	return j>call;
}
int busted(int j1, int j2) {
	// 1 pour un score superieur a 21
	// 0 pour un score inferieur a 21
	if (j1 < 22) {
		return 0;
	}
	if (j2 < 22) {
		return 0;
	}
	return 1;
}

char *decide(void) {
	printf("(c)arte ou (r)este \t\t");
	char *ch = malloc(sizeof(char));
	*ch = 'e';
	scanf("%s", ch);
	while ((*ch != 'c') && (*ch != 'r')) {
		printf("vous devez repondre par (c) pour une carte additionelle ou (r) pour rester sur votre score actuel\n");
		scanf("%s", ch);
	}
	return ch;
}

int miser(int credit) {
	int mise;
	int miseMax = 30000 + credit;
	printf(
			"******************************************\nEntrez le montant de la mise (maximum %d)\t\t",
			miseMax);
	scanf("%d", &mise);
	while (credit - mise < -30000 || mise < 1) {
		if (mise < 1)
			printf("vous devez miser un montant superieur a zero !!\n");
		else
			printf("vous ne pouvez depasser votre limite d'endettement\n");
		printf("Entrez le montant de la mise\n");
		scanf("%d", &mise);
		printf("\n");
	}
	return mise;
}

carte pige(struct _paquet * pack) {
	int var = rand();
	int lapige = var % 52;
	while (pack->cartes[lapige].disp == 0) {
		var = rand();
		lapige = var % 52;
	}
	pack->cartes[lapige].disp = 0;
	return pack->cartes[lapige];
}

int carte_croupier(int s1, int s2, int nasc) {
	if (nasc == 0) {
		if (s1 < 17) {
			return 1;
		} else {
			return 0;
		}
	}
	if (s2 > 21) {
		if (s1 < 17) {
			return 1;
		} else {
			return 0;
		}
	}
	if (s2 < 17) {
		return 1;
	}
	return 0;
}
int main(void) {

	/*amorce de la fonction de generation de nombre aleatoire */
	time_t *tp = malloc(sizeof(time_t));
	time(tp);
	srand(*tp);

	/*declaration des variables */
	struct _paquet *p = malloc(sizeof(struct _paquet));
	struct _paquet paquet = *p;

	carte jeu[11];
	carte jeu_croupier[11];
	int score, score2;
	char *decision;
	int nas = 0;
	int i, j, k = 0;
	int credit = -15000;
	int nb_carte_croupier;
	int mise = 0;
	char *continuer = malloc(sizeof(char));
	*continuer = 'o';

	/*etablissement des comptes */
	printf("\nBienvenue, ce programme est un jeu de Black Jack.");
	printf("\nCette version en C-ANSI est issue de code java");

	printf(
			"\nVotre montant initial de jetons virtuels (sans valeur monetaire) est de %d\n",
			credit);


	/* grande boucle tant qu'il y a des crédits à  miser */

	while (credit > -30000 && *continuer == 'o') {

		/*definition du paquet de cartes */

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 13; j++) {
				paquet.cartes[k].sorte = i;
				paquet.cartes[k].hauteur = j;
				paquet.cartes[k].disp = 1;
				affiche(paquet.cartes[k]);
				k++;
			}
		}

		/*mise du joueur */
		mise = miser(credit);

		/*distribution et affichage des cartes du joueur */
		nas = 0;
		for (k = 0; k < 2; k++) {
			jeu[k] = pige(&paquet);
			if (jeu[k].hauteur == 0)
				nas++;
			affiche(jeu[k]);
		}

		/*distribution et affichage des cartes du croupier */
		nb_carte_croupier = 2;
		int nasc = 0;
		for (k = 0; k < 2; k++) {
			jeu_croupier[k] = pige(&paquet);
			if (jeu_croupier[k].hauteur == 0)
				nasc++;
		}

		/*compte-rendu de la distribution */
		score = 0;
		score2 = 0;
		for (k = 0; k < 2; k++) {
			score += jeu[k].hauteur < 10 ? jeu[k].hauteur + 1 : 10;
		}
		printf("Votre score est de %d", score);
		if (nas > 0) {
			score2 = score + (10);
			printf(" ou %d\n", score2);
		} else {
			score2 = score;
			printf("\n");
		}
		/* compte-rendu de la distribution des cartes du croupier */

		int score_croupier = 0;
		int score_croupier2 = 0;
		for (k = 0; k < 2; k++) {
			score_croupier
					+= jeu_croupier[k].hauteur < 10 ? jeu_croupier[k].hauteur
							+ 1 : 10;
			if (nasc > 0) {
				score_croupier2 = score_croupier + (10);
			} else {
				score_croupier2 = score_croupier;
			}
		}

		/*jeu */

		decision = decide();

		while ((*decision == 'c') && !busted(score, score2)) {
			jeu[k] = pige(&paquet);
			affiche(jeu[k]);
			int increment = (jeu[k].hauteur < 10) ? (jeu[k].hauteur) + 1 : 10;
			score += increment;
			if (jeu[k].hauteur == 0) {
				nas++;
				score2+= increment +10;
			}
			/* affichage du score */
			if (score < 22) {
				printf("\nVotre score est de %d", score);
				if (nas > 0 && score2 < 22)
					printf(" ou %d\n", score2);
				else
					printf("\n");
			} else {
				printf("\nVotre score est de %d", score);
				if (nas > 0 && score2 < 22)
					printf(" ou %d\n", score2);
				else {
					printf("\n");
				}
			}
			k++;
			if (!busted(score, score2)) {
				decision = decide();
			}
		}

		if (busted(score, score2)) {
			//jeu perdant
			credit = credit - mise;
			printf("Vous avez depasser 21\n");
			printf("Votre credit est maintenant de %d\n", credit);
			if (credit == -30000) {
				printf("votre endettement maximal est atteint\nMeilleur chance la prochaine fois\n");
				exit(1);
			}
		}
		//else, le croupier se mesure au joueur.

		else {
			k = 2;
			while (carte_croupier(score_croupier, score_croupier2, nasc)) {
				jeu_croupier[k] = pige(&paquet);
				nb_carte_croupier++;
				int
						increment =
								(jeu_croupier[k].hauteur < 10) ? (jeu_croupier[k].hauteur)
										+ 1
										: 10;
				score_croupier += increment;
				if (jeu_croupier[k].hauteur < 1) {
					nasc++;
					score_croupier2 = increment + 10;
				}
			}
			if (gagnant(score, score2, score_croupier, score_croupier2)) {
				credit = credit + mise;
				printf("Le croupier avait un score de %d\n",score_croupier);
				if(score_croupier2 < 22){
					printf("ou de %d",score_croupier2);
				}
				printf("et ses cartes sont : \n");
				for (k = 0; k < nb_carte_croupier; k++) {
					affiche(jeu_croupier[k]);
				}
				printf("Ce qui fait que vous remporter cette manche.");
				printf("\nVotre credit est maintenant de %d\n", credit);
			} else {
				//jeu perdant
				printf("Le score du croupier est de %d\n",score_croupier);
				if(score_croupier2 < 22){
					printf("ou de %d",score_croupier2);
				}
				printf("et ses cartes etaient : \n");
				for (k = 0; k < nb_carte_croupier; k++) {
					affiche(jeu_croupier[k]);
				}
				printf("Le croupier remporte cette manche\n");
				credit = credit - mise;
				if (credit <= -30000) {
					printf("votre endettement maximal est atteint\nMeilleur chance la prochaine fois\n");
					exit(1);
				}
				else{
					printf("Votre score est maintenant de %d",credit);
				}
			}
		}

		//dans tous les cas, si l'endettement maximal n'est pas atteint, 
		//on demande au joueur s'il veut continuer
		do {
			printf("Est-ce que vous vouler continuer ? repondre oui(o) ou non(n)\t\t");
			scanf("%s", continuer);
		} while (*continuer != 'o' && *continuer != 'n');
	}

	printf("l'important c'est de participer !\n\n");
	return 0;

}
