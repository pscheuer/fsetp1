#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Affichage des informations suivantes : * – le nombre de processeurs * – le nom du modèle * – la taille du cache
 *
 * On peut récupérer ces informations du fichier /proc/cpuinfo.
 * On lit ligne par ligne et si on retrouve les lignes souhaitant,
 * on coupe les informations et les affiches
 * Comme les champs du nom de model et la taille du cache sont identiques 
 * pour tous les processeurs, on a besoin de prendre ces informations juste
 * une seule fois.
 * 
 */

int main()
{
	// déclaration des variables et pointeurs
	char line[100];
	char model[75];
	char cache[10];
	int nb_proc = 0;
	FILE *cpuInfo = fopen("/proc/cpuinfo", "r");
	
	// tant que le fichiers n'est pas lit en complet...
	while(!feof(cpuInfo))
	{
		// prendre ligne par ligne
		fgets(line, 100, cpuInfo);
	
		// en testant si cette ligne contient le mot 'processor'
		if(strstr(line, "processor") != NULL)
		{
			nb_proc++;
			continue;
		}
		
		// récupération des informations sur le model et le cache (une seule fois)
		if(nb_proc ==1)
		{
			if(strstr(line, "model name") != NULL)
			{
				strcpy(model, line+13);
				continue;
			}
			
			if(strstr(line, "cache size") != NULL)
				strcpy(cache, line+13);
		}
	}
	
	// affichage des informations obtenues
	printf("Processor(s): %d. \nModel: %s", nb_proc, model);
	printf("Cache: %s", cache);
	
	// fermeture du pointeur
	fclose(cpuInfo);
	
	return 0;
}