#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data
{
	char *s ;
} ; typedef struct data DATA ;

struct abr
{
	DATA d ; 
	struct abr * gauche ;
	struct abr * droite ;
} ; typedef struct abr ABR ;

void insertionLigne(ABR ** racine , char ligne[])
{
	if(*racine)
	{
		if(strcmp(ligne , (*racine)->d.s) < 0)
			insertionLigne(&((* racine) -> gauche) , ligne);
		else
			insertionLigne(&((* racine) -> droite) , ligne);
	}
	else
	{
		*racine = (ABR *) malloc(sizeof(ABR)) ;
		//strcpy ((*racine)-> d.s , ligne ) ;
		(*racine)-> d.s = (char *) malloc (sizeof(char)*strlen(ligne));
		strcpy ((*racine)-> d.s , ligne ) ;
		(*racine)-> gauche = NULL;
		(*racine) -> droite = NULL ;
	}
}

ABR* load_arb(char *name_file)
{
	ABR* racine = NULL ;
	FILE* fic ;
	char ligne[499] ;
	
	fic = fopen(name_file , "r+") ;
	
	if(!fic)
	{
		printf("Fichier introuvable ! (Veiller verifier le nom...)") ;
		exit(EXIT_FAILURE);
	}
	
	while(fgets (ligne , 499 , fic ))
	{
		insertionLigne(& racine , ligne) ;
	}
	
	
	fclose(fic) ;
	
	return racine ;
}

void ecritureRecursive(FILE *f , ABR* racine)
{
	if(racine)
	{
		ecritureRecursive( f , racine->gauche);
		fputs(racine->d.s , f ) ;
		ecritureRecursive( f , racine->droite);
	}
}

void save(ABR * racine , char *name_file)
{
	FILE* fic ;
	fic = fopen(name_file , "w") ;
	if(racine)
	{
		ecritureRecursive((fic), racine);
	}
	
	fclose(fic) ;
}

void view_file(char *name_file)
{
	FILE * fp ;
	char ligne[499] ;
	
	fp = fopen( name_file , "r");
	
	while(fgets (ligne , 499 , fp ))
	{
		puts(ligne);
	}
	
	fclose(fp) ;
}

int main(int argc , char **argv)
{
	ABR *racine ;
	char nom_fichier_a_trie[100] ;
	printf("Ecrivez le nom du fichier a tier (sans oublier l'extent .txt) : ");
	scanf("%s", nom_fichier_a_trie);
	racine = load_arb(nom_fichier_a_trie) ;
	save(racine , nom_fichier_a_trie) ;
	view_file(nom_fichier_a_trie);
}



