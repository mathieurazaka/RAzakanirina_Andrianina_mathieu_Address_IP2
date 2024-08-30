#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Prototype2.h"

void accueil(int *choix)
{
	printf("Bonjour,veuiller entrer votre choix parmi les propositions suivants :\n");
	printf("1-Se connecter\n");
	printf("2-S'inscrire\n");
	printf("3-Quittez\n");
	do
	{
		printf("choix >>>> ");
		scanf("%d",choix);
	}
	while(*choix < 1 || *choix > 3);
}

void connection(FILE *fichier,int *valide2)
{
	char *nom = NULL;
	char *passwd = NULL;
	char *nomtmp = NULL;
	char *passwdtmp = NULL;
	char *tmp = NULL;
	int i = 0,j = 0,k = 0;
	char c = 'A';
	
	nom = allocationTab(50);
	passwd = allocationTab(50);
	tmp = allocationTab(200);
	nomtmp = allocationTab(50);
	passwdtmp = allocationTab(50);
	
	printf("Veuiller a ne pas mettre d'espace\n");
	
	printf("Veuiller entrer votre nom :");
	scanf("%s",nom);
	printf("\nVeuiller entrer votre mot de passe :");
	scanf("%s",passwd);
	do
	{
		c = fgetc(fichier);
		tmp[i] = c;
		if (tmp[i] == '\n')
		{
			tmp[i] = '\0';
			//sscanf(tmp,"nom=%s&+passwd=%s",nomtmp,passwdtmp);
			j = 4;
			k = 0;
			do
			{
				if(tmp[j] != '&')
					nomtmp [k] = tmp[j];
				else
				{
					nomtmp [k] = '\0';
					j=j + 9;
					k = 0;
					do
					{
						if(tmp[j] != '\0')
							passwdtmp [k] = tmp[j];
						else
						{
							passwdtmp [k] = '\0';
						}
						j++;
						k++;
					}
					while(tmp[j] != '\0');
				}
				j++;
				k++;
			}
			while (tmp[j] != '&');
			if((strcmp(nom,nomtmp)) == 0 )
			{
				*valide2=*valide2+1;
				break;
			}
			i = 0;
		}
		
		i++;
	}
	while (c != EOF);
	
	free(nom);
	free(passwd);
	free(nomtmp);
	free(passwdtmp);
}

void inscription(FILE *fichier)
{
	char *nom = NULL;
	char *passwd = NULL;
	
	nom = allocationTab(50);
	passwd = allocationTab(50);
	
	printf("Veuiller a ne pas mettre d'espace\n");
	
	printf("Veuiller entrer votre nom :");
	scanf("%s",nom);
	printf("\nVeuiller entrer votre mot de passe :");
	scanf("%s",passwd);
	
	fprintf(fichier,"nom=%s&+passwd=%s\n",nom,passwd);
	free(nom);
	free(passwd);
}

char *allocationTab(int dimension)
{
	char *tmp  = NULL;
	
	tmp = (char *)malloc(dimension *sizeof(char));
	if (tmp == NULL)
	{
		printf("Probleme d'allocation memoire \n");
		exit(0);
	}
	return tmp;
}

void entrer_donner_IP (char *IP)
{
	printf("Entrer l'address IP : ");
	scanf("%s",IP);
}

void verification_par_octet(char *tmp,int Byte)
{
	if(Byte < 0 ||  255 < Byte)
	{
		printf("Address IP invalide %s\n",tmp);
		exit(0);
	}
}

void Verifiaction_donner_IP(char *tmp,int *Octet1_IP,int *Octet2_IP,int *Octet3_IP,int *Octet4_IP,int *Nombre_decoupage,int *valide)
{
	int i = 0,point = 0;
	
	//Verification du longueur de donner
	if (strlen(tmp) > 18 || strlen(tmp) < 7)
	{
		printf("Address IP invalide %s\n",tmp);
		exit(0);
	}
	//Verification s'il y a des choses differents des nombres {0...9}
	for(i = 0 ; i < strlen(tmp) ; i++)
	{
		if ((int)tmp[i] < 46 || (int)tmp[i] > 57)
		{
			printf("Address IP invalide %s\n",tmp);
			exit(0);
		}
	}
	//Verification si le donner n'est pas complet ex:1.1.1./n
	i = 0;
	do
	{
		if((tmp[i] == '.' && tmp[i+1] == '.') || (tmp[i] == '.' && tmp[i+1] == '/'))
		{
		printf("Address IP invalide %s\n",tmp);
		exit(0);
		}	
		if(tmp[i] == '.')
			point++;
		i++;
	}
	while(tmp[i]!= '\0');
	//Verification si le donner est de trop 
	if (point != 3)
	{
		printf("Address IP invalide %s\n",tmp);
		exit(0);
	}
	sscanf(tmp,"%d.%d.%d.%d/%d",Octet1_IP,Octet2_IP,Octet3_IP,Octet4_IP,Nombre_decoupage);
	//Verification si le nombre de decoupage est positif
	if (*Nombre_decoupage  < 0)
	{
		printf("Nombre de decoupage incorrect %d\n",*Nombre_decoupage);
		exit(0);
	}
	verification_par_octet(tmp,*Octet1_IP);
	verification_par_octet(tmp,*Octet2_IP);
	verification_par_octet(tmp,*Octet3_IP);
	verification_par_octet(tmp,*Octet4_IP);
	if (*Nombre_decoupage != 0)
		*valide=*valide+1;
}

char Verification_Class_IP(int Byte)
{
	char class;
	if(0 <= Byte && Byte < 128)
	{	
		class = 'A';
	}
	if(128 <= Byte  && Byte < 192)
	{
		class = 'B';
	}
	if(192 <= Byte && Byte < 224)
	{
		class = 'C';
	}
	if(224 <= Byte && Byte < 240)
	{
		class = 'D';
	}
	if(240 <= Byte   && Byte < 256)
	{
		class = 'E';
	}
	return class;
}

void address_reseau_sans_decoupe(char Classe_IP,int Octet1_IP,int Octet2_IP,int Octet3_IP,int Octet4_IP)
{
	if (Classe_IP == 'A')	//8/24
	{
		printf("\nL address IP est de une address de Classe %c\n",Classe_IP);
		printf("Le masque de sous reseau est de 255.0.0.0\n");
		printf("L'addresse de broadcast est de %d.255.255.255\n",Octet1_IP);
		printf("\nL'addresse reseau est de %d.0.0.0\n",Octet1_IP);
		printf("Nombre de machine est de %.0f\n",(pow(2,24)-2));
	}
	if (Classe_IP == 'B')	//16/16
	{
		printf("\nL address IP est de une address de Classe %c\n",Classe_IP);
		printf("Le masque de sous reseau est de 255.255.0.0\n");
		printf("L'addresse de broadcast est de %d.%d.255.255\n",Octet1_IP,Octet2_IP);
		printf("\nL'addresse reseau est de %d.%d.0.0\n",Octet1_IP,Octet2_IP);
		printf("Nombre de machine est de %.0f\n",(pow(2,16)-2));
	}
	if (Classe_IP == 'C')	//24/8
	{
		printf("\nL address IP est de une address de Classe %c\n",Classe_IP);
		printf("Le masque de sous reseau est de 255.255.255.0\n");
		printf("L'addresse reseau est de %d.%d.%d.0\n",Octet1_IP,Octet2_IP,Octet3_IP);
		printf("L'saddresse de broadcast est de %d.%d.%d.255\n",Octet1_IP,Octet2_IP,Octet3_IP);
		printf("Nombre de machine est de %.0f\n",(pow(2,8)-2));
	}
	if (Classe_IP == 'D')	//32/0
	{
		printf("\nL address IP est de une address de Classe %c\n",Classe_IP);
		printf("L'addresse reseau est de %d.%d.%d.%d\n",Octet1_IP,Octet2_IP,Octet3_IP,Octet4_IP);
	}
	if (Classe_IP == 'E')	
		printf("L address IP est de une address de Classe %c\n",Classe_IP);
}

void decoupage_IP(char Classe_IP,int Nombre_decoupage,int Octet1_IP,int Octet2_IP,int Octet3_IP,int Octet4_IP)
{
	int i = 0;
	if (Classe_IP == 'A')	//8/24
	{
		printf("\nL address IP est de une address de Classe %c\n",Classe_IP);
		float Octet_par_decoupe_reseau = 0;
		for (i=0;i < pow(2,Nombre_decoupage);i++)
		{
			printf("\nL'addresse reseau est de %d.0.0.%.0f\n",Octet1_IP,Octet_par_decoupe_reseau);
			Octet_par_decoupe_reseau += 256 / pow(2,Nombre_decoupage);
			printf("L'addresse de broadcast est de %d.255.255.%.0f\n",Octet1_IP,Octet_par_decoupe_reseau-1);
			printf("Nombre de machine est de %.0f\n",pow(2,24-Nombre_decoupage)-2);
		}
	}
	if (Classe_IP == 'B')	//16/16
	{
		printf("\nL address IP est de une address de Classe %c\n",Classe_IP);
		float Octet_par_decoupe_reseau = 0;
		for (i=0;i < pow(2,Nombre_decoupage);i++)
		{
			printf("\nL'addresse reseau est de %d.%d.0.%.0f\n",Octet1_IP,Octet2_IP,Octet_par_decoupe_reseau);
			Octet_par_decoupe_reseau += 256 / pow(2,Nombre_decoupage);
			printf("L'addresse de broadcast est de %d.%d.255.%.0f\n",Octet1_IP,Octet2_IP,Octet_par_decoupe_reseau-1);
			printf("Nombre de machine est de %.0f\n",pow(2,16-Nombre_decoupage)-2);
		}
	}
	if (Classe_IP == 'C')	//24/8
	{
		printf("\nL address IP est de une address de Classe %c\n",Classe_IP);
		float Octet_par_decoupe_reseau = 0;
		for (i=0;i < pow(2,Nombre_decoupage);i++)
		{		
			printf("\nL'addresse reseau est de %d.%d.%d.%.0f\n",Octet1_IP,Octet2_IP,Octet3_IP,Octet_par_decoupe_reseau);
			Octet_par_decoupe_reseau += 256 / pow(2,Nombre_decoupage);
			printf("L'saddresse de broadcast est de %d.%d.%d.%.0f\n",Octet1_IP,Octet2_IP,Octet3_IP,Octet_par_decoupe_reseau-1);
			printf("Nombre de machine est de %.0f\n",pow(2,8-Nombre_decoupage)-2);
		}
	}
	if (Classe_IP == 'D')	//32/0
	{
		printf("L address IP est de une address de Classe %c\n",Classe_IP);
		printf("\nL'addresse reseau est de %d.%d.%d.%d\n",Octet1_IP,Octet2_IP,Octet3_IP,Octet4_IP);
	}
}

void address_reseau_avec_decoupe(char *Classe_IP,int *Nombre_decoupage,int *Octet1_IP,int *Octet2_IP,int *Octet3_IP,int *Octet4_IP)
{
	if (*Classe_IP == 'A' && *Nombre_decoupage <= 24)
		decoupage_IP(*Classe_IP,*Nombre_decoupage,*Octet1_IP,*Octet2_IP,*Octet3_IP,*Octet4_IP);
	else if (*Classe_IP == 'B' && *Nombre_decoupage <= 16)
			decoupage_IP(*Classe_IP,*Nombre_decoupage,*Octet1_IP,*Octet2_IP,*Octet3_IP,*Octet4_IP);
		else if (*Classe_IP == 'C' && *Nombre_decoupage <= 8)
				decoupage_IP(*Classe_IP,*Nombre_decoupage,*Octet1_IP,*Octet2_IP,*Octet3_IP,*Octet4_IP);
			else 
			{
				printf("Nombre de decoupage incorrect %d\n",*Nombre_decoupage);
				exit(0);
			}
}
	
