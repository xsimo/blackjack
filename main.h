typedef struct _carte carte;

struct _carte{
  int sorte;
  int hauteur;
  int disp;
};

struct _paquet{
  carte cartes[52];
};

int busted(int,int);

char * decide(void);

int miser(int);

carte pige(struct _paquet *);

int carte_croupier(int,int,int);

int gagnant(int,int,int,int);

