#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * recevoir les informations de /proc/mounts
 */
char** partInfo (char* partition)
{
	FILE* file_mount = fopen("/proc/mounts", "r");
	
	if (file_mount == NULL)
		perror("/proc/mounts");
	
	char line_mount[2048];
	char* tok;
	char** res;
	res = malloc(2*sizeof(char*));
	
	while (fgets(line_mount, 2048, file_mount) != NULL)
	{
	  if (strstr(line_mount, partition) != NULL)
	  {
	    tok = strtok(line_mount," ");
	    tok = strtok(NULL, " ");
	    res[0] = tok;
	    tok = strtok(NULL, " ");
	    res[1] = tok;
	    fclose(file_mount);
	    return res;
	  }
	}
	fclose(file_mount);
	return NULL;    
}

/**
 * recevoir les informations de /proc/partitions
 */
int countDisks ()
{
	int disks = 0;
	int i, j = 0;
	
	char line_part[2048];
	char part[1024];
	char temp[1024];
	char taille[11];
	
	char* tok;
	char** info;
	
	FILE* file_part = fopen("/proc/partitions", "r");
	
	if (file_part == NULL)
		perror("/proc/partitions");
	
	while (fgets(line_part, 2048, file_part) != NULL)
	{
	  if (j++ < 2)
	  	continue;
	           
	  memset(part, '\0', 1024);
	  strcpy(part, line_part+24);
	  part[strlen(part)-1] = '\0';
	  
	  if (strlen(temp) == 0)
	  {
	    strcpy(temp, part);
	    disks++;
	  }
	  else
	  {
	    if (strstr(part, temp) == part)
	    {
	      info = partInfo(part+1);
	      memset(taille, '\0', 11);
	      strncpy(taille+13, line_part, 11);
	      if (info != NULL)
	      	printf("%s %s %s %s\n", part, info[0], info[1], taille);
	      else
	        printf("%s - - %s\n", part, taille);
	    }
	    else
	    {
	    	disks++;   
	      memset(temp, '\0', 1024);
	      strcpy(temp, part);
	    }    
	  }
	}
	fclose(file_part);
	return disks;
}

/**
 * main
 */
int main()
{
    printf("Nombre de disques: %d\n", countDisks());
    exit(EXIT_SUCCESS);
    
    return 0;
}