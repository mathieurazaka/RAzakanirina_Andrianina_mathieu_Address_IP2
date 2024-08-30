#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prototype2.h"
#define dimension 20

int main ()
{
	char *IP = NULL;
	char Classe_IP;
	int Octet1_IP = 0,Octet2_IP = 0,Octet3_IP = 0,Octet4_IP = 0,Nombre_decoupage = 0,valide = 0,choix = 0,valide2 = 0;
	FILE *fichier = NULL;
	
	
	//Accueil ou choix
	accueil(&choix);
	
	//Ouverture fichier
	fichier = fopen ("Base.txt","a+");
	
	switch (choix)
	{
		case 1:
			connection(fichier,&valide2);
			fclose(fichier);
			printf("%d",valide2);
			if (valide2 == 1)
				goto suite;
			else
				exit(0);
			break;
		case 2:
		{
			inscription(fichier);
			fclose(fichier);
			goto suite;
			break;
		}
		case 3:
			exit(0);
	}
	suite :
		{
			//Allocation memoire
			IP = allocationTab(dimension);
			
			//Entrer de donner et verification IP
			entrer_donner_IP (IP);
			Verifiaction_donner_IP(IP,&Octet1_IP,&Octet2_IP,&Octet3_IP,&Octet4_IP,&Nombre_decoupage,&valide);
			Classe_IP = Verification_Class_IP(Octet1_IP);
			if(valide == 0)
			{
				address_reseau_sans_decoupe(Classe_IP,Octet1_IP,Octet2_IP,Octet3_IP,Octet4_IP);
			}
			else 
			{
				address_reseau_avec_decoupe(&Classe_IP,&Nombre_decoupage,&Octet1_IP,&Octet2_IP,&Octet3_IP,&Octet4_IP);
			}
			free (IP);
		}
	return (0);
}
