#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Fonction permettant le récupération des données nécessaire pour calculer et
 * afficher le nombre de jobs en attente d'éxécution moyenne sur 1 minutes.
 * 
 */

void print_loadavg()
{
	// déclaration des variables et pointeurs
	char line_upt[100];
	char *tmp = malloc(10*sizeof(char));
	char *tmp2 = malloc(10*sizeof(char));
	char *i1 = malloc(10*sizeof(char));
	char *i2 = malloc(10*sizeof(char));
	int i;
	int res;
	FILE *upt = fopen("/proc/loadavg", "r");
	
	fgets(line_upt, 100, upt);

	tmp = strtok(line_upt, " ");
	for(i = 1; i<=3; i++)
		tmp = strtok(NULL, " ");
	strcpy(tmp2, tmp+1);
	
	// jobs en total
	i1 = strtok(tmp2, " ");
	// jobs en attente
	i2 = strtok(tmp, "/");

	res = atoi(i1+1) - atoi(i2);			

	printf("Le nombre de jobs en attente d'éxécution moyenne sur 1 minutes: %d\n", 
		res);
	
	// free et fermeture des pointeurs
	// les frees provoquent une erreur.
		//free(i1);
		//free(i2);
		//free(tmp);
		//free(tmp2);
	fclose(upt);
}

/**
 * Fonction permettant le récupération des données nécessaire pour calculer et
 * afficher le pourcentage de temps passé à ne rien faire.
 * 
 */

void print_uptime()
{
	// déclaration des variables et pointeurs
	float res;
	int proc = sysconf(_SC_NPROCESSORS_CONF);
	char line_load[100];
	char *i1 = malloc(20*sizeof(char));
	char *i2 = malloc(20*sizeof(char));
	FILE *load = fopen("/proc/uptime", "r");
		
	fgets(line_load, 100, load);
	
	// temps inactif (par processeur)
	i1 = strtok(line_load, " ");
	// temps actif (en total)
	i2 = strtok(NULL, " ");
	
	// calcul du pourcentage
	res = (atof(i2) / ((atof(i1))*proc))*100;
	printf("Pourcentage de temps passé à ne rien faire: %f \n", res);
	
	// fermeture du pointeur
	fclose(load);
}

/**
 * Affichage du nombre de jobs en attente d'éxécution
 * moyenné sur 1 minutes.
 * Avec option '-i': afficher le pourcentage de temps passé à ne rien faire.
 * Avec option '-r n': mettre à jour ces informations toutes les n secondes.
 *
 */

int main(int argc, char *argv[])
{
	// déclaration des variables
	int tmp_flag = 0;
	int pct_flag = 0;
	int n = -1;
	int i;
	int c;
	
	// affichage du pid
	printf("PID: %d\n", getpid());
	
	// affichage nombre de jobs en attente
	print_loadavg();
	
	// récupération des options (si existants)
	while ((c = getopt(argc, argv, "ir:")) != -1) 
	{
   	switch(c) 
   	{
     	case 'i':
				print_uptime();
				pct_flag = 1;
				break;
			case 'r':
				tmp_flag = 1;
				// nombre de secondes de la mise à jour
				n = atoi(optarg);
				break;
   	}
	}
	
	// mise à jours des informations tout les n secondes		
	if(tmp_flag == 1)
		while(1)
		{
			sleep(n);
			print_loadavg();
			if(pct_flag == 1)
				print_uptime();
		}

	return 0;
}