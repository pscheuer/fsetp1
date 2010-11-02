#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Afficher sur plusieurs lignes les variables * d'environnement associées à un processus dont 
 * le pid est passé en argument
 * 
 */

void get_env (char* pid)
{
  int i;
  int n=0;
  char* path = malloc(25*sizeof(char));
  // 4096 est le nombre maximal possible de bytes dans /environ
  char* line = malloc(4096*sizeof(char));

	sprintf(path, "/proc/%s/environ", pid);
  FILE* file = fopen(path, "r");
  free(path);

  if (file == NULL)
  {
    printf("%s n'est pas valide.\n", pid);
    exit(2);
  }

  if (fgets(line, 4096, file) != NULL)
	{
    fclose(file);
    for (i=0; !(line[i] == '\0' && line[i+1] == '\0'); i++)
        if (line[i] == '\0')
            line[i] = '\n';
    printf("%s",line);
    free(line);
  }
  else
  { 
  	free(line);
    perror(path); 
  }
}

/**
 * Test du bon usage du programme, puis appel de la fonction get_Env pour
 * l'affichage des données souhaitées
 * 
 */

int main (int argc, char** argv)
{
   if (argc < 2)
   {
     printf("Usage: %s <pid>\n", argv[0]);
     exit(1);
   }
	
	// appel de la fonction
	get_env(argv[1]);
   
  return 0;
}