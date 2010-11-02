#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Affichage de la version d'OS utilisé, son numéro de release et
 * le nombre maximum authorisé pour un pid
 * 
 */

int main()
{
	char line[100];
	
	// récupération de la donnée souhaitant et affichage
	FILE *type = fopen("/proc/sys/kernel/ostype", "r");
	fgets(line, 100, type);
	printf("Le systeme d exploitation est: %s\n", line);
	
	// idem
	FILE *version = fopen("/proc/sys/kernel/version", "r");
	fgets(line, 100, version);
	printf("La version courrante est: %s\n", line);

	// idem	
	FILE *release = fopen("/proc/sys/kernel/osrelease", "r");
	fgets(line, 100, release);
	printf("La date de release est: %s\n", line);
	
	// idem
	FILE *pid = fopen("/proc/sys/kernel/pid_max", "r");
	fgets(line, 100, pid);
	printf("Le nombre maximal authorise pour un pid est: %s\n", line);
	
	// fermeture des pointeurs
	fclose(type);
	fclose(version);
	fclose(release);
	fclose(pid);
	
	
	return 0;
}