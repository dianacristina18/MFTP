
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <pthread.h>
#include <dirent.h>
/* portul folosit */
#define PORT 2024
 #define MAXI 300000
int rasp=0,iden,citit,x,index1,index2=0;
 int ucokk=0,ucokkk=0,ucokkkk,ucokkkkk,ucokkkkkk,ucokkkkkkk,ucokkkkkkkk,ucokkkkkkkkk;
char *password1,*password2;//*check1
char *password3;
struct stat check2={0};
char *username111;
int lungime=0;
int nrp=0;
size_t size;
char m[10000];
int nro=0,pozitie=0;
int sum=0;
int pow2=0;
/* codul de eroare returnat de anumite apeluri */
extern int errno;
char mesaj[30000]=" ",check1[10]=" ",text1[30],text[30]=" ",*ls1,*sir,*j;
char cuv[100],k[100],pid[20];
char key[10]=" ",parola[30]=" ";
  char raspuns[30000],nou[30000];
       char raspuns1[MAXI],raspuns2[MAXI];
       int pid_corect=0;
 int y,uc,uc1,ucok,uc1ok;
typedef struct thData{
	int idThread; //id-ul thread-ului tinut in evidenta de acest program
	int cl; //descriptorul intors de accept
}thData;

static void *treat(void *); /* functia executata de fiecare thread ce realizeaza comunicarea cu clientii */
void raspunde(void *);
//void check_command(char*raspuns,char*mesaj);
void apel_sql(char*interogare,char*username,int verifica_username,int *ok);

void apel_sql(char*interogare,char*username,int verifica_username,int *ok)

{



   
   MYSQL *to_db;
   MYSQL_RES *rezultat;
   MYSQL_ROW from_db;

   char *server = "localhost";
   char *user = "root";
   char *password = "Student123@"; 
   char *database = "users";

   to_db = mysql_init(NULL);

   //ne conectam la baza de date 
   if (!mysql_real_connect(to_db, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(to_db));
      return 1;
   }
  if(verifica_username==0){
 
   if (mysql_query(to_db, interogare)) {
      fprintf(stderr, "%s\n", mysql_error(to_db));
     return 1;
   }

   rezultat = mysql_use_result(to_db);

   
  
  
   while ((from_db = mysql_fetch_row(rezultat)) != NULL)
      {
      if(strcmp(from_db[1],username)==0)
      {
      
      *ok=1;
      }
      }
     
     }
     else
     if(verifica_username==1)
     {
     
     
     if (mysql_query(to_db, interogare)) {
      fprintf(stderr, "%s\n", mysql_error(to_db));
      return 1;
   }

   rezultat = mysql_use_result(to_db);

  
    *ok=0;
  
   if ((from_db = mysql_fetch_row(rezultat)) != NULL)
      {
       
        strcpy(key,from_db[0]);
        int cheie=atoi(key);
        FILE *for_id;
        for_id=fopen("stocare_id","w+");
        /*verificam daca fisierul s-a deschis/creat cu succes*/
        if(for_id==NULL)
        {
          perror("Eroare la crearea/deschiderea fisierului stocare_id!\n");
          return 1;
        }
        
        /*punem in fisier id-ul*/
        putw(cheie,for_id);
        fclose(for_id);
      }
      }
      else
      if(verifica_username==2)
      {
      
      if (mysql_query(to_db, interogare)) {
      fprintf(stderr, "%s\n", mysql_error(to_db));
      return 1;
   }

   rezultat = mysql_use_result(to_db);

   
    *ok=0;
  
   if ((from_db = mysql_fetch_row(rezultat)) != NULL)
      {
       
        strcpy(parola,from_db[0]);
       
      }
      if(strcmp(parola,username)==0)
      *ok=2;
      
      }
      else
      if(verifica_username==3)
      {
      
      if (mysql_query(to_db, interogare)) {
      fprintf(stderr, "%s\n", mysql_error(to_db));
      return 1;
   }

   rezultat = mysql_use_result(to_db);

   
    *ok=0;
  
   if ((from_db = mysql_fetch_row(rezultat)) != NULL)
      {
       
        strcpy(parola,from_db[0]);
       
      }
      if(strcmp(parola,"whitelist")==0)
      *ok=3;
      
      
      }
      
      else
      if(verifica_username==10)
      {
      
      if (mysql_query(to_db, interogare)) {
      fprintf(stderr, "%s\n", mysql_error(to_db));
      return 1;
   }

   rezultat = mysql_use_result(to_db);

   
    *ok=0;
  
   if ((from_db = mysql_fetch_row(rezultat)) != NULL)
      {
       
        printf("Coloana adaugata\n");
       
      }
     
      
      
      }
     
     
     
     
      
   // incheiem conexiunea dintre server si baza de date 
   mysql_free_result(rezultat);
   mysql_close(to_db);
   


}
int main ()
{
  
  
 
  FILE * only_user;
    only_user = fopen("validare_user.txt", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
        return 1;
    }
    
    
        x = 0;
                                   
                                   
         if (fprintf(only_user, "%d", x) < 0)

         {
           printf("Error la scriere in validare_user!\n");
           return 1;
         }
         
    
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user!\n");
        return 1;
    }
    
    /*truncate*/
    FILE * validare_login;
    validare_login = fopen("valid_login.txt", "w+"); //fisierul care retine 1 daca esti logat si 0 daca te-ai delogat
    if (validare_login == NULL) {
        perror("Error at opening valid.txt\n");
        return 1;
    }
    
    
        x = 0;
                                   
                                   
         if (fprintf(validare_login, "%d", x) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
    
    if (fclose(validare_login) != 0) {
        perror("Error at closing valid.txt!\n");
        return 1;
    }
    
  
  struct sockaddr_in server;	// structura folosita de server
  struct sockaddr_in from;	
  int nr;		//mesajul primit de trimis la client 
  int sd;		//descriptorul de socket 
  int pid;
  pthread_t th[100];    //Identificatorii thread-urilor care se vor crea
	int i=0;
  

  /* crearea unui socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }
  /* utilizarea optiunii SO_REUSEADDR */
  int on=1;
  setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  
  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));
  
  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;	
  /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
  /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
  
  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 2) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }
  /* servim in mod concurent clientii...folosind thread-uri */
  while (1)
    {
      int client;
      thData * td; //parametru functia executata de thread     
      int length = sizeof (from);

      printf ("[server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);

      // client= malloc(sizeof(int));
      /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
      if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
	{
	  perror ("[server]Eroare la accept().\n");
	  continue;
	}
	
        /* s-a realizat conexiunea, se astepta mesajul */
    
	// int idThread; //id-ul threadului
	// int cl; //descriptorul intors de accept

	td=(struct thData*)malloc(sizeof(struct thData));	
	td->idThread=i++;
	td->cl=client;

	pthread_create(&th[i], NULL, &treat, td);	      
				
	}//while    
};				
static void *treat(void * arg)
{		
		struct thData tdL; 
		tdL= *((struct thData*)arg);	
		//printf ("[thread]- %d - Asteptam mesajul...\n", tdL.idThread);
		fflush (stdout);		 
		pthread_detach(pthread_self());		
		raspunde((struct thData*)arg);
		/* am terminat cu acest client, inchidem conexiunea */
		close ((intptr_t)arg);
		return(NULL);	
  		
};


void raspunde(void *arg)
{     
        int nr, i=0;
	struct thData tdL; 
	tdL= *((struct thData*)arg);
	bzero (raspuns, 100);
	if (read (tdL.cl, raspuns,3000000) <= 0)
			{
			  printf("[Thread %d]\n",tdL.idThread);
			  perror ("Eroare la read() de la client.\n");
			
			}
	              nr=0;
	              
		     bzero(raspuns1,10000);
		      bzero(pid,10000);
	           
	             if((strncmp(raspuns,"upload##",8)>0||strncmp(raspuns,"upload##",8)<0)&&(strncmp(raspuns,"uploadB##",9)>0||strncmp(raspuns,"uploadB##",9)<0)&&(strncmp(raspuns,"download##",10)>0||strncmp(raspuns,"download##",10)<0)&&(strncmp(raspuns,"downloadB##",11)>0||strncmp(raspuns,"downloadB##",11)<0)&&(strncmp(raspuns,"media##",7)>0||strncmp(raspuns,"media##",7)<0)&&(strncmp(raspuns,"dmedia##",8)>0||strncmp(raspuns,"dmedia##",8)<0)){
	             for(int i=0;i<strlen(raspuns);i++)
	             {
	             
	             if(raspuns[i]=='#')
	             { pozitie=i;
	             break;
	             }
	             else
	             pid[nr++]=raspuns[i];
	             
	             
	             
	             }
	             nr=0;
	            
	             for(int i=pozitie+2;i<strlen(raspuns);i++)
	             {
	             
	             raspuns1[nr++]=raspuns[i];
	             }
	           
		     
		      pid_corect=atoi(pid);
		      
		    
		    }
		    else
		    {strcpy(raspuns2,raspuns);
		    
		    }
		      /*aici transferul de fisier*/
		      
		      
		     
		      
		     
if(strncmp(raspuns2,"upload##",8)==0)
{
FILE *pentru_server1;
char username1[30],username11[3000];

bzero(username1,30);
bzero(username11,3000);
//bzero(username111,30000);
int nr=0,poz=0;

if(strlen(raspuns2)==8)
{

strcpy(mesaj,"Comanda invalida!");
return 1;

}
for(int i=0;i<strlen(raspuns2);i++)
{

if(raspuns2[i]=='#')
{poz=i; break;}
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username1[nr++]=raspuns2[i];
else
{poz=i;
 lungime=atoi(username1);
break;
}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username11[nr++]=raspuns2[i];
else
{poz=i;break;}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
username111=(char*)(malloc(sizeof(char)*lungime));
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{

username111[nr++]=raspuns2[i];

}
}

else
{strcpy(mesaj,"Comanda invalida!"); return 1;}

char sir8[100];
strcpy(sir8,"/home/diana/serverfiles/");
strcat(sir8,username11);
strcpy(username11,sir8);

//printf("deschidefis:%s\n",username1);
//printf("punetext:%s\n",username11);

pentru_server1=fopen(username11,"w");

fprintf(pentru_server1,"%s",username111);



strcpy(raspuns1,"Finalizat");	
fclose(pentru_server1);

}

/***************************************/



if(strncmp(raspuns2,"media##",7)==0)
{

FILE *pentru_server1,*pentru_server2;
char username1[30],username11[3000],username111[3000];

bzero(username1,30);
bzero(username11,3000);
//bzero(username111,30000);
int nr=0,poz=0;

if(strlen(raspuns2)==7)
{

strcpy(mesaj,"Comanda invalida!");
return 1;

}
for(int i=0;i<strlen(raspuns2);i++)
{

if(raspuns2[i]=='#')
{poz=i; break;}
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username1[nr++]=raspuns2[i];
else
{poz=i;
 lungime=atoi(username1);
break;
}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username11[nr++]=raspuns2[i];
else
{poz=i;break;}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;}



char sir8[100],sir9[100];
strcpy(sir8,"/home/diana/serverfiles/");
strcpy(sir9,"/home/diana/clientFiles/");
strcat(sir8,username11);
strcat(sir9,username11);
strcpy(username11,sir8);
strcpy(username111,sir9);


pentru_server1=fopen(username111,"rb");
pentru_server2=fopen(username11,"wb");





while( (size = fread(m, 1, sizeof(m), pentru_server1) ) > 0) 
    
{ 
 
 if(fwrite(m, 1, size, pentru_server2)!=size)
 {
 
 perror("error at fwrite\n");
 }
 
 
}





strcpy(raspuns1,"Finalizat");	
fclose(pentru_server1);
fclose(pentru_server2);
}

/*=========================*/

if(strncmp(raspuns2,"dmedia##",8)==0)
{

FILE *pentru_server1,*pentru_server2;
char username1[30],username11[3000],username111[3000];

bzero(username1,30);
bzero(username11,3000);
//bzero(username111,30000);
int nr=0,poz=0;

if(strlen(raspuns2)==8)
{

strcpy(mesaj,"Comanda invalida!");
return 1;

}
for(int i=0;i<strlen(raspuns2);i++)
{

if(raspuns2[i]=='#')
{poz=i; break;}
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username1[nr++]=raspuns2[i];
else
{poz=i;
 lungime=atoi(username1);
break;
}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username11[nr++]=raspuns2[i];
else
{poz=i;break;}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;}



char sir8[100],sir9[100];
strcpy(sir8,"/home/diana/clientFiles/");
strcpy(sir9,"/home/diana/serverfiles/");
strcat(sir8,username11);
strcat(sir9,username11);
strcpy(username11,sir8);
strcpy(username111,sir9);


pentru_server1=fopen(username111,"rb");
pentru_server2=fopen(username11,"wb");





while( (size = fread(m, 1, sizeof(m), pentru_server1) ) > 0) 
    
{ 
 
 if(fwrite(m, 1, size, pentru_server2)!=size)
 {
 
 perror("error at fwrite\n");
 }
 
 
}





strcpy(raspuns1,"Finalizat");	
fclose(pentru_server1);
fclose(pentru_server2);
}


/*===========================*/

/**********************************/
		      
	if(strncmp(raspuns2,"downloadB##",11)==0)
{

/*FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {
        fscanf(pid, "%ld %ld", & uc,&uc1);
    }

    printf("uc=%d\n",uc);
    printf("uc1=%d\n",uc1);
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    printf("uc=%d\n",uc);
      printf("pid=%d\n",atoi(pid)); 
    if(y==1&&pid_corect==uc){*/
FILE *pentru_server1;
char username1[30],username11[3000];

bzero(username1,30);
bzero(username11,3000);
//bzero(username111,30000);
int nr=0,poz=0;

if(strlen(raspuns2)==9)
{

strcpy(mesaj,"Comanda invalida!");
return 1;

}
for(int i=0;i<strlen(raspuns);i++)
{

if(raspuns2[i]=='#')
{poz=i; break;}
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username1[nr++]=raspuns2[i];
else
{poz=i;
 lungime=atoi(username1);
break;
}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username11[nr++]=raspuns2[i];
else
{poz=i;break;}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
username111=(char*)(malloc(sizeof(char)*lungime));
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{

username111[nr++]=raspuns2[i];

}
/*}

else
{strcpy(mesaj,"Comanda invalida!"); return 1;}
*/
char sir8[100];
strcpy(sir8,"/home/diana/clientFiles/");
strcat(sir8,username11);
strcpy(username11,sir8);

//printf("deschidefis:%s\n",username1);

int i;
pentru_server1=fopen(username11,"w");
nr=0;

for(i=0;i<strlen(username111);i++)
{
sum=0;

if(username111[i]=='\n')
{

nou[nr++]='\n';
i++;
}
else
if(username111[i]!=' ')
{

cuv[nro]=username111[i];
nro++;
cuv[nro]=NULL;
}
else
if(username111[i]==' ')
{

if(strlen(cuv)==7){
sum+=(pow(2,0)*(cuv[0]-'0'));
sum+=(pow(2,1)*(cuv[1]-'0'));
sum+=(pow(2,2)*(cuv[2]-'0'));
sum+=(pow(2,3)*(cuv[3]-'0'));
sum+=(pow(2,4)*(cuv[4]-'0'));
sum+=(pow(2,5)*(cuv[5]-'0'));
sum+=(pow(2,6)*(cuv[6]-'0'));
}
else
if(strlen(cuv)==6)
{
sum+=(pow(2,0)*(cuv[0]-'0'));
sum+=(pow(2,1)*(cuv[1]-'0'));
sum+=(pow(2,2)*(cuv[2]-'0'));
sum+=(pow(2,3)*(cuv[3]-'0'));
sum+=(pow(2,4)*(cuv[4]-'0'));
sum+=(pow(2,5)*(cuv[5]-'0'));

}
nro=0;
}
else
if(username111[i]=='`')
{nou[nr++]=' ';}
if(sum){

if(sum==96)
sum=32;

char m=sum;
nou[nr++]=m;
}

}

fprintf(pentru_server1,"%s",nou);



strcpy(raspuns1,"Finalizat");	
fclose(pentru_server1);
}
}
else
strcpy(mesaj,"Nu sunteti logat inca!\n");
		      /*---------------------------------------------------*/	      
		     
if(strncmp(raspuns2,"uploadB##",9)==0)
{
/*FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {
        fscanf(pid, "%ld %ld", & uc,&uc1);
    }

    printf("uc=%d\n",uc);
    printf("uc1=%d\n",uc1);
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    printf("uc=%d\n",uc);
      printf("pid=%d\n",atoi(pid)); 
    if(y==1&&pid_corect==uc){*/
FILE *pentru_server1;
char username1[30],username11[3000];

bzero(username1,30);
bzero(username11,3000);
//bzero(username111,30000);
int nr=0,poz=0;

if(strlen(raspuns2)==9)
{

strcpy(mesaj,"Comanda invalida!");
return 1;

}
for(int i=0;i<strlen(raspuns);i++)
{

if(raspuns2[i]=='#')
{poz=i; break;}
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username1[nr++]=raspuns2[i];
else
{poz=i;
 lungime=atoi(username1);
break;
}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username11[nr++]=raspuns2[i];
else
{poz=i;break;}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
username111=(char*)(malloc(sizeof(char)*lungime));
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{

username111[nr++]=raspuns2[i];

}
/*}

else
{strcpy(mesaj,"Comanda invalida!"); return 1;}
*/
char sir8[100];
strcpy(sir8,"/home/diana/serverfiles/");
strcat(sir8,username11);
strcpy(username11,sir8);

//printf("deschidefis:%s\n",username1);

int i;
pentru_server1=fopen(username11,"w");
nr=0;

for(i=0;i<strlen(username111);i++)
{
sum=0;

if(username111[i]=='\n')
{

nou[nr++]='\n';
i++;
}
else
if(username111[i]!=' ')
{

cuv[nro]=username111[i];
nro++;
cuv[nro]=NULL;
}
else
if(username111[i]==' ')
{

if(strlen(cuv)==7){
sum+=(pow(2,0)*(cuv[0]-'0'));
sum+=(pow(2,1)*(cuv[1]-'0'));
sum+=(pow(2,2)*(cuv[2]-'0'));
sum+=(pow(2,3)*(cuv[3]-'0'));
sum+=(pow(2,4)*(cuv[4]-'0'));
sum+=(pow(2,5)*(cuv[5]-'0'));
sum+=(pow(2,6)*(cuv[6]-'0'));
}
else
if(strlen(cuv)==6)
{
sum+=(pow(2,0)*(cuv[0]-'0'));
sum+=(pow(2,1)*(cuv[1]-'0'));
sum+=(pow(2,2)*(cuv[2]-'0'));
sum+=(pow(2,3)*(cuv[3]-'0'));
sum+=(pow(2,4)*(cuv[4]-'0'));
sum+=(pow(2,5)*(cuv[5]-'0'));

}
nro=0;
}
else
if(username111[i]=='`')
{nou[nr++]=' ';}
if(sum){

if(sum==96)
sum=32;

char m=sum;
nou[nr++]=m;
}

}

fprintf(pentru_server1,"%s",nou);



strcpy(raspuns1,"Finalizat");	
fclose(pentru_server1);
}
}
else
strcpy(mesaj,"Nu sunteti logat inca!\n");
		      /*---------------------------------------------------*/
		      		      
		      
		      
		      if(strncmp(raspuns2,"download##",10)==0)
{

/*FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {
        fscanf(pid, "%ld %ld", & uc,&uc1);
    }

    printf("uc=%d\n",uc);
    printf("uc1=%d\n",uc1);
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    printf("uc=%d\n",uc);
      printf("pid=%d\n",atoi(pid)); 
    if(y==1&&pid_corect==uc){*/
FILE *pentru_server1;
char username1[30],username11[3000];

bzero(username1,30);
bzero(username11,3000);
//bzero(username111,30000);
int nr=0,poz=0;

if(strlen(raspuns2)==10)
{

strcpy(mesaj,"Comanda invalida!");
return 1;

}
for(int i=0;i<strlen(raspuns2);i++)
{

if(raspuns2[i]=='#')
{poz=i; break;}
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username1[nr++]=raspuns2[i];
else
{poz=i;
 lungime=atoi(username1);
break;
}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;
}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{
if(raspuns2[i]!='#')
username11[nr++]=raspuns2[i];
else
{poz=i;break;}
}
}
else
{strcpy(mesaj,"Comanda invalida!");
return 1;}

if(raspuns2[poz]=='#'&&raspuns2[poz+1]=='#')

{
username111=(char*)(malloc(sizeof(char)*lungime));
nr=0;
for(int i=poz+2;i<strlen(raspuns2);i++)
{

username111[nr++]=raspuns2[i];

}
}

else
{strcpy(mesaj,"Comanda invalida!"); return 1;}

char sir8[100];
strcpy(sir8,"/home/diana/clientFiles/");
strcat(sir8,username11);
strcpy(username11,sir8);

//printf("deschidefis:%s\n",username1);
//printf("punetext:%s\n",username11);

pentru_server1=fopen(username11,"w");


fprintf(pentru_server1,"%s",username111);




strcpy(raspuns1,"Finalizat");	
fclose(pentru_server1);
}
/*}
else
strcpy(mesaj,"Nu sunteti logat inca!\n");
*/
		      /*-----------------------------------------------------*/
	      
		      //bzero (mesaj, 100);
		      check_command(raspuns1,mesaj);
		      
		      //raspuns[strcspn(mesaj,"\n")]=0;
		      
		      mesaj[strlen(mesaj)-1]=NULL;
		      
		      
	//printf("[Thread %d]Trimitem mesajul inapoi...%s\n",tdL.idThread, mesaj);
		       //bzero (raspuns, 100);
		       
		      /* returnam mesajul clientului */
	 if (write (tdL.cl,mesaj, 3000) <= 0)
		{
		 //printf("[Thread %d] ",tdL.idThread);
		 perror ("[Thread]Eroare la write() catre client.\n");
		}
	else
		{
		if((strcmp(mesaj,"Ai parasit aplicatia!")==0)||(strcmp(mesaj,"raspuns2")==0))
               {
               int nr_conectati=0;
               char m[100];
               FILE * pp;
               pp= fopen("nr_conect.txt", "a+"); 
                if (pp== NULL) {
               perror("Error la deschidere validare_login\n");
                return 1;
                          }
  
                while (!feof(pp)) {
        fscanf(pp, "%s", m);
        
        
    }
  if (fclose(pp) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
       int rezultat=0;
       int nrm=0;
       for(int i=2;i<strlen(m)-1;i++)
       {
      
       if(i%2==0)
       {
       
       if(m[i]=='+')
          {rezultat+=(m[i+1]-'0');}
          else
       if(m[i]=='-')
          {nrm++;rezultat-=(m[i+1]-'0');}
            
          
       
       }
       
       
       }
      
      if(rezultat==0||nrm==0){
      
      FILE * pp;
    pp = fopen("nr_conect.txt", "w+"); 
    if (pp == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    if (ftruncate(pp, 0) != 0)
  {
  
  int j=1;
  }
         
         
 if (fclose(pp) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
      
      FILE * pid;
    pid= fopen("pid.txt", "w+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
  
  if (ftruncate(pid, 0) != 0)
  {
  
  int j=1;
  }
  
  if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
      
                exit(0);
                
                
                
                
                }
               }
		//printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread);
		
		
		
		
		}

}

void check_command(char *raspuns,char*mesaj)
{

  

raspuns[strcspn(raspuns,"\n")]=0;

if((strcmp(raspuns,"quit")==0)||(strcmp(raspuns,"QUIT")==0))
{
strcpy(mesaj,"Ai parasit aplicatia!\n");

}

else
if(strstr(raspuns,"login:")||strstr(raspuns,"LOGIN:"))
{



FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }

if(y==0&& uc==pid_corect){

if((strncmp(raspuns,"login:",6)==0)||(strncmp(raspuns,"LOGIN:",6)==0))
{

if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida.Puteti consulta sectiunea de 'help' pentru detalii!!");
return 1;

}
else
if(strlen(raspuns)>6)
{
int index=0,nr=0,poz=0;
char *username1;

username1=(char*)(malloc(sizeof(char)*30));
for(index=6;index<strlen(raspuns);index++)
username1[nr++]=raspuns[index];
username1[nr+1]='\0';

if(poz=strchr(username1,'.')==NULL)
{

strcpy(mesaj,"Comanda invalida.Puteti consulta sectiunea de 'help' pentru detalii!!");
return 1;
}
else

if(strchr(username1,'.')!=NULL)
{

int j=0,nrpoint=0,pozitie=-1,diffch=0;
for(j=0;j<strlen(username1);j++)
{
if(username1[j]=='.')
{
++nrpoint;
pozitie=j;
}
if(isalpha(username1[j])==0&&username1[j]!='.')
{

diffch=-1;
}
if(username1[j]>='A'&&username1[j]<='Z')
{
diffch=-1;
}
if(diffch==-1)
{
break;
}


}

if(pozitie!=0&&pozitie!=strlen(username1)-1&&nrpoint==1&&pozitie!=-1 &&diffch!=-1)
{

  
   apel_sql("SELECT*FROM autentificare",username1,0,&rasp);
   if(rasp==1){
   if(strcmp(username1,"diana.ungureanu")==0)
   {apel_sql("SELECT id FROM autentificare WHERE username='diana.ungureanu'",username1,1,&rasp);
   }
   else
   if(strcmp(username1,"cristina.pichiu")==0)
   {apel_sql("SELECT id FROM autentificare WHERE username='cristina.pichiu'",username1,1,&rasp);
   }
   else
   if(strcmp(username1,"paul.ungureanu")==0)
   {apel_sql("SELECT id FROM autentificare WHERE username='paul.ungureanu'",username1,1,&rasp);
   }
   else
   if(strcmp(username1,"ana.baciu")==0)
   {apel_sql("SELECT id FROM autentificare WHERE username='ana.baciu'",username1,1,&rasp);
   
   }
   FILE * only_user;
    only_user = fopen("validare_user.txt", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
        return 1;
    }
    
    
        x = 1;
                             
         
                                   
         if (fprintf(only_user, "%d", x) < 0)

         {
           printf("Error la scriere in validare_user!\n");
           return 1;
         }
         
         
    
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user!\n");
        return 1;
    }
   
   strcpy(mesaj,"Password needed!");
  }
  else
  if(rasp==0)
  {
  
  strcpy(mesaj,"Nu sunteti inregistrat inca!!");
  }

}
}

}

}
else
strcpy(mesaj,"Comanda invalida.Puteti consulta sectiunea de 'help' pentru detalii!!");


}
else
strcpy(mesaj,"Nu iti este permis sa executi aceasta comanda!!");
}
else
if(strcmp(raspuns,"help")==0)
{
char sir1[90000]="\nlogin:prenume.nume\nlogout:deconectare\nquit:iesire\nls:1(fisierele din client),ls:2(fisierele din server)\ncrd:director curent\nrnf1:fis1#fis2(redenumire fisier din client)\nrmf1:fis(stergere fisier din client)\nmv1:fis(mutare fisier din client)\ncreate1:fis(creare director in client)\ntouch1:fis(creare fisier.txt in client)\nshow1:fis(afisare continut fis din slicent)\ngetlength1:fis(lungime fisier fis din client)\nhead1:n#fis(afisare primele n linii din fisierul fis client)\nrnf2:fis1#fis2(redenumire fisier din server)\nrmf2:fis(stergere fisier din server)\nmv2:fis(mutare fisier din server)\ncreate2:fis(creare director in server)\ntouch2:fis(creare fisier.txt in server)\nshow2:fis(afisare continut fis din server)\ngetlength2:fis(lungime fisier fis din server)\nhead2:n#fis(afisare primele n linii din fisierul fis server)\nupload:ASCII fis(transfer catre server de tip ASCII)\ndownload:ASCII fis(transfer catre client de tip ASCII)\nupload:BINARY fis(transfer catre server de tip BINAR)\ndownload:BINARY fis(transfer catre client de tip BINAR\nupload_media:fis (transfer de imagini,mp3,pdf-uri de la client la server)\ndownload_media:fis(transfer de imagini,mp3,pdf-uri de la server la client))!";
strcpy(mesaj,sir1);
}
else
if(strstr(raspuns,"passwordcheck:"))
{

password1=(char*)(malloc(sizeof(char)*30));

int uc,y;
    FILE * only_user;
    only_user = fopen("validare_user.txt", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld", & uc);
    }

    
    y = uc % 10;
   if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
    

if(strncmp(raspuns,"passwordcheck:",14)==0)
{


    
if(strlen(raspuns)==14)
{strcpy(mesaj,"Comanda invalida!");
return 1;
}
else
if(strlen(raspuns)>14)
{

int index=0,nr=0;
password1=(char*)(malloc(sizeof(char)*30));
for(index=14;index<strlen(raspuns);index++)
password1[nr++]=raspuns[index];
password1[nr+1]='\0';
/*aici vom decripta parola folosind cod ASCII*/
for(int i=0;i<strlen(password1);i++)
password1[i]-=16;
}




}
if(y==1){
/*deschidem fisierul stocare_id pentru a obtine id-ul aferent utilizatorului ce doreste sa se logheze*/
FILE *for_id;
int id; /*aici vom stoca id-ul citit din fisierul stocare_id*/
int functioneaza=0,id1;
for_id=fopen("stocare_id","r"); /*deschidem fisierul*/
while((id=getw(for_id))!=EOF)
{

id1=id;
}

fclose(for_id);
if(id1==1){
apel_sql("SELECT password FROM autentificare WHERE id=1",password1,2,&rasp);
}
else
if(id1==2)
{
apel_sql("SELECT password FROM autentificare WHERE id=2",password1,2,&rasp);
}
else
if(id1==3)
{
apel_sql("SELECT password FROM autentificare WHERE id=3",password1,2,&rasp);
}
else
if(id1==4)
{
apel_sql("SELECT password FROM autentificare WHERE id=4",password1,2,&rasp);
}
if(rasp==2){


if(id1==1){
apel_sql("SELECT status FROM autentificare WHERE id=1",password1,3,&rasp);
}
else
if(id1==2)
{
apel_sql("SELECT status FROM autentificare WHERE id=2",password1,3,&rasp);
}
else
if(id1==3)
{
apel_sql("SELECT status FROM autentificare WHERE id=3",password1,3,&rasp);
}
else
if(id1==4)
{
apel_sql("SELECT status FROM autentificare WHERE id=4",password1,4,&rasp);
}
if(rasp==3)
strcpy(mesaj,"ok!");
else
strcpy(mesaj,"Logare esuata,restrictionat de server!!");
}
else
strcpy(mesaj,"Parola incorecta!!");
}
else
strcpy(mesaj,"Comanda invalida!");
}
else
if(strstr(raspuns,"wrongpassword:"))
{


int uc,y;
    FILE * only_user;
    only_user = fopen("validare_user.txt", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld", & uc);
    }

    
    y = uc % 10;
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
    
//check1=(char*)(malloc(sizeof(char)*30));
if(strncmp(raspuns,"wrongpassword:",14)==0)
{



if(strlen(raspuns)==14)
{strcpy(mesaj,"Comanda invalida!");
return 1;
}
else
if(strlen(raspuns)>14)
{

int index=0,nr=0;
//check1=(char*)(malloc(sizeof(char)*30));
for(index=14;index<strlen(raspuns);index++)
{
check1[nr++]=raspuns[index];
}
check1[nr+1]='\0';

}

}


if(y==1){
if(strcmp(check1,"1")==0)
{

strcpy(mesaj,"raspuns1!");
}
else
if(strcmp(check1,"2")==0)
{

strcpy(mesaj,"raspuns2!");
}
else
if(strcmp(check1,"3")==0)
{

strcpy(mesaj,"raspuns3!");
}
else
strcpy(mesaj,"Optiune invalida!!");
}
else
strcpy(mesaj,"Comanda invalida!");
}
else
if((strstr(raspuns,"LOGOUT"))||(strstr(raspuns,"logout")))
{




if((strncmp(raspuns,"logout",6)==0)||(strncmp(raspuns,"LOGOUT:",6)==0))
{
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    int l=0;
    int nr8=0;
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
   
if(y==1&&pid_corect== uc){

if(strlen(raspuns)>6)
{

strcpy(mesaj,"Comanda invalida!");
return 1;
}
else
if(strlen(raspuns)==6)
{


strcpy(mesaj,"Te-ai delogat cu succes!!");
}

}
else
strcpy(mesaj,"Nu sunteti inca logat!!");
}

}
else
if(strstr(raspuns,"ls:")||strstr(raspuns,"LS:"))/*afiseaza lista de fisiere/directoare de pe directorul curent sau cel dat-path*/
{

if((strncmp(raspuns,"ls:",3)==0)||(strncmp(raspuns,"LS:",3)==0)){

    
   
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    int l=0;
    int nr8=0;
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
   
    
    
    if(strlen(raspuns)==3)
{
strcpy(mesaj,"Comanda invalida!!");
return 1;


}
else
if(strlen(raspuns)==4)
{
ls1=(char*)(malloc(sizeof(char)*30));
if(raspuns[3]=='1')
strcpy(ls1,"/home/diana/clientFiles/");
else
if(raspuns[3]=='2')
strcpy(ls1,"/home/diana/serverfiles/");
}
else
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}

    
    
    
    }
    

if(y==1&& uc==pid_corect)
{


FILE * only_dir;
    only_dir = fopen("validare_dir.txt", "w+"); 
    if (only_dir == NULL) {
        perror("Error la deschidere validare_user\n");
        return 1;
    }
    

DIR *d;
d=opendir(ls1);
struct dirent *dir;
if(d!=0)
{

while((dir=readdir(d))!=NULL){



                          
         if (fprintf(only_dir, "%s\n", dir->d_name) < 0)

         {
           printf("Error la scriere in validare_dir!\n");
           return 1;
         }

}
strcpy(mesaj,"ls!");
close(d);
if (fclose(only_dir) != 0) {
        perror("Error la inchidere validare_user!\n");
       return 1;
    }

}

}
else
if(y==0)
{strcpy(mesaj,"Nu esti logat inca!!");
return 1;
}
}
else
if(strcmp(raspuns,"crd")==0||strcmp(raspuns,"CRD")==0)/*afiseaza directorul curent*/
{
int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    

if(y==1&&pid_corect== uc){
getcwd(text,30);
strcat(text,"!.");
strcpy(mesaj,text);
}
else
strcpy(mesaj,"Nu sunteti inca logat!!");
}
else
if(strstr(raspuns,"rnf1:")||strstr(raspuns,"RNF1:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
     
    
    if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;
}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"rnf1:",5)==0)||(strncmp(raspuns,"RNF1:",5)==0))
{

if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>5)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
username2=(char*)(malloc(sizeof(char)*30));
for(index=5;index<strlen(raspuns);index++)
{
if(raspuns[index]!='#'){
username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}
else
{
pozii=index;
gasit=1;
break;
}
}
if(gasit==0)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}
nr=0;
for(index=pozii+1;index<strlen(raspuns);index++)
{
username2[nr++]=raspuns[index];
username2[nr+1]='\0';


}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username1);
strcat(sirkk,username2);

if(rename(sirk,sirkk)==0)
{

strcpy(mesaj,"Fisier redenumit cu succes!!");
}
else
{
strcpy(mesaj,"Redenumirea a esuat!!");
}
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}
else

if(strstr(raspuns,"rnf2:")||strstr(raspuns,"RNF2:"))
{


int y,uc,uc1;
FILE * pid;

    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;
}


if(y==1&&pid_corect== uc){

if((strncmp(raspuns,"rnf2:",5)==0)||(strncmp(raspuns,"RNF2:",5)==0))
{

if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>5)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
username2=(char*)(malloc(sizeof(char)*30));
for(index=5;index<strlen(raspuns);index++)
{
if(raspuns[index]!='#'){
username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}
else
{
pozii=index;
gasit=1;
break;
}
}
if(gasit==0)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}
nr=0;
for(index=pozii+1;index<strlen(raspuns);index++)
{
username2[nr++]=raspuns[index];
username2[nr+1]='\0';


}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
strcpy(sirkk,"/home/diana/serverfiles/");
strcat(sirk,username1);
strcat(sirkk,username2);

printf("lalalal=%s\n",sirk);
printf("lalalal=%s\n",sirk);

if(rename(sirk,sirkk)==0)
{

strcpy(mesaj,"Fisier redenumit cu succes!!");
}
else
{
strcpy(mesaj,"Redenumirea a esuat!!");
}
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}

else
if(strstr(raspuns,"rmf1:")||strstr(raspuns,"RMF1:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
  while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"rmf1:",5)==0)||(strncmp(raspuns,"RMF1:",5)==0))
{

if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>5)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;

password1=(char*)(malloc(sizeof(char)*30));
for(index=5;index<strlen(raspuns);index++)
{

password1[nr++]=raspuns[index];
password1[nr+1]='\0';
}



}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
strcat(sirk,password1);
if(remove(sirk)==0)
{

strcpy(mesaj,"Fisier sters cu succes!!");
}
else
{
strcpy(mesaj,"Stergerea a esuat!!");
}
}
}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}
/**********************************/



else
if(strstr(raspuns,"rmf2:")||strstr(raspuns,"RMF2:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"rmf2:",5)==0)||(strncmp(raspuns,"RMF2:",5)==0))
{

if(strlen(raspuns)==5)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>5)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;

password1=(char*)(malloc(sizeof(char)*30));
for(index=5;index<strlen(raspuns);index++)
{

password1[nr++]=raspuns[index];
password1[nr+1]='\0';
}



}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
strcat(sirk,password1);
if(remove(sirk)==0)
{

strcpy(mesaj,"Fisier sters cu succes!!");
}
else
{
strcpy(mesaj,"Stergerea a esuat!!");
}
}
}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}




/**********************************/

else

if(strstr(raspuns,"create1:")||strstr(raspuns,"create1:"))
{



int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==8)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"create1:",8)==0)||(strncmp(raspuns,"create1:",8)==0))
{

if(strlen(raspuns)==8)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>8)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;

password1=(char*)(malloc(sizeof(char)*30));
for(index=8;index<strlen(raspuns);index++)
{

password1[nr++]=raspuns[index];
password1[nr+1]='\0';
}



}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
strcat(sirk,password1);
if(stat(sirk,&check2)==-1){
if(mkdir(sirk,0777)==0)
{

strcpy(mesaj,"Director creat cu succes!!");
}
}
else
{
strcpy(mesaj,"Crearea a esuat!!");
return 1;
}
}
}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}
/**************************/



else

if(strstr(raspuns,"create2:")||strstr(raspuns,"create2:"))
{



int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==8)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"create2:",8)==0)||(strncmp(raspuns,"create2:",8)==0))
{

if(strlen(raspuns)==8)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>8)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;

password1=(char*)(malloc(sizeof(char)*30));
for(index=8;index<strlen(raspuns);index++)
{

password1[nr++]=raspuns[index];
password1[nr+1]='\0';
}



}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
strcat(sirk,password1);
if(stat(sirk,&check2)==-1){
if(mkdir(sirk,0777)==0)
{

strcpy(mesaj,"Director creat cu succes!!");
}
}
else
{
strcpy(mesaj,"Crearea a esuat!!");
return 1;
}
}
}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}


/***********************************/

else
if(strstr(raspuns,"mv1:")||strstr(raspuns,"mv1:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    if(strlen(raspuns)==4)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"mv1:",4)==0)||(strncmp(raspuns,"MV1:",4)==0))
{

if(strlen(raspuns)==4)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>4)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
for(index=4;index<strlen(raspuns);index++)
{

username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}

char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
strcpy(sirkk,"/home/diana/serverfiles/");
strcat(sirk,username1);
strcat(sirkk,username1);

if(rename(sirk,sirkk)==0)
{

strcpy(mesaj,"Fisier mutat cu succes!!");
}
else
{
strcpy(mesaj,"Mutarea a esuat!!");
}
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}
/******************************/
else
if(strstr(raspuns,"mv2:")||strstr(raspuns,"mv2:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==4)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"mv2:",4)==0)||(strncmp(raspuns,"MV2:",4)==0))
{

if(strlen(raspuns)==4)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>4)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
for(index=4;index<strlen(raspuns);index++)
{

username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}

char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username1);
strcat(sirkk,username1);

if(rename(sirk,sirkk)==0)
{

strcpy(mesaj,"Fisier mutat cu succes!!");
}
else
{
strcpy(mesaj,"Mutarea a esuat!!");
}
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}

/*----------------------------------*/


else
if(strstr(raspuns,"show1:")||strstr(raspuns,"show1:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"show1:",6)==0)||(strncmp(raspuns,"SHOW1:",4)==0))
{

if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>6)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
for(index=6;index<strlen(raspuns);index++)
{

username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}

char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
//strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username1);
//strcat(sirkk,username1);

FILE *pentru_transfer;
  pentru_transfer=fopen(sirk,"r");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  

 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file

 char msg10[lungime],msg11[lungime];
 int k=0;
 while(fgets(msg10,lungime,pentru_transfer)){
  k++;
  if(k==1)
 strcpy(msg11,msg10);
 else
 strcat(msg11,msg10);
  }



fclose(pentru_transfer);

strcpy(mesaj,"\n");
strcat(mesaj,msg11);
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}

else
if(strstr(raspuns,"show2:")||strstr(raspuns,"show2:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"show2:",6)==0)||(strncmp(raspuns,"SHOW2:",4)==0))
{

if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>6)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
for(index=6;index<strlen(raspuns);index++)
{

username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}

char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
//strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username1);
//strcat(sirkk,username1);

FILE *pentru_transfer;
  pentru_transfer=fopen(sirk,"r");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  

 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file

 char msg10[lungime],msg11[lungime];
 int k=0;
 while(fgets(msg10,lungime,pentru_transfer)){
  k++;
  if(k==1)
 strcpy(msg11,msg10);
 else
 strcat(msg11,msg10);
  }



fclose(pentru_transfer);

strcpy(mesaj,"\n");
strcat(mesaj,msg11);
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}



/*--------------------------------------*/


else
if(strstr(raspuns,"getlength2:")||strstr(raspuns,"getlength2:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==11)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"getlength2:",11)==0)||(strncmp(raspuns,"GETLENGTH2:",11)==0))
{

if(strlen(raspuns)==11)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>11)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
for(index=11;index<strlen(raspuns);index++)
{

username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}

char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
//strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username1);
//strcat(sirkk,username1);

FILE *pentru_transfer;
  pentru_transfer=fopen(sirk,"r");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  

 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file

char msg10[lungime];
fclose(pentru_transfer);
sprintf(msg10,"%d",lungime);
strcpy(mesaj,msg10);
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}


else
if(strstr(raspuns,"getlength1:")||strstr(raspuns,"getlength1:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==11)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"getlength1:",11)==0)||(strncmp(raspuns,"GETLENGTH1:",11)==0))
{

if(strlen(raspuns)==11)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>11)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
for(index=11;index<strlen(raspuns);index++)
{

username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}

char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
//strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username1);
//strcat(sirkk,username1);

FILE *pentru_transfer;
  pentru_transfer=fopen(sirk,"r");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  

 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file

char msg10[lungime];
fclose(pentru_transfer);
sprintf(msg10,"%d",lungime);
strcpy(mesaj,msg10);
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}
/**********************************/
else
if(strstr(raspuns,"head1:")||strstr(raspuns,"head1:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"head1:",6)==0)||(strncmp(raspuns,"HEAD1:",6)==0))
{


if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>6)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0,space=0;
char *username1,*username2;
 poz=0;
username1=(char*)(malloc(sizeof(char)*30));
username2=(char*)(malloc(sizeof(char)*30));
for(index=6;index<strlen(raspuns);index++)
{
if(raspuns[index]=='#')

{

poz=index;
space=1;
break;

}
else
{username1[nr++]=raspuns[index];

}


}
username1[nr+1]='\0';
nr=0;
if(space==1){
for(index=poz+1;index<strlen(raspuns);index++)
{

username2[nr++]=raspuns[index];


}

username2[nr+1]='\0';

int l=atoi(username1);
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
//strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username2);
//strcat(sirkk,username1);
printf("il=%s\n",sirk);
FILE *pentru_transfer;
  pentru_transfer=fopen(sirk,"r");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  

 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file

 char msg10[lungime],msg11[lungime];
 int k=0;
 while(fgets(msg10,lungime,pentru_transfer)){
  k++;
  if(k<=l){
  if(k==1)
 strcpy(msg11,msg10);
 else
 strcat(msg11,msg10);
 }
  }



fclose(pentru_transfer);

strcpy(mesaj,"\n");
strcat(mesaj,msg11);
}
else
strcpy(mesaj,"Comanda invalida!!");
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}

/**********************************/
else
if(strstr(raspuns,"head2:")||strstr(raspuns,"head2:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    fseek( pid, 0, SEEK_SET );
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect== uc){
if((strncmp(raspuns,"head2:",6)==0)||(strncmp(raspuns,"HEAD2:",6)==0))
{

if(strlen(raspuns)==6)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>6)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0,space=0;
char *username1,*username2;
 poz=0;
username1=(char*)(malloc(sizeof(char)*30));
username2=(char*)(malloc(sizeof(char)*30));
for(index=6;index<strlen(raspuns);index++)
{
if(raspuns[index]=='#')

{

poz=index;
space=1;
break;

}
else
{username1[nr++]=raspuns[index];

}


}
username1[nr+1]='\0';
nr=0;
if(space==1){
for(index=poz+1;index<strlen(raspuns);index++)
{

username2[nr++]=raspuns[index];


}

username2[nr+1]='\0';

int l=atoi(username1);
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
//strcpy(sirkk,"/home/diana/clientFiles/");
strcat(sirk,username2);
//strcat(sirkk,username1);

FILE *pentru_transfer;
  pentru_transfer=fopen(sirk,"r");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  

 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file

 char msg10[lungime],msg11[lungime];
 int k=0;
 while(fgets(msg10,lungime,pentru_transfer)){
  k++;
  if(k<=l){
  if(k==1)
 strcpy(msg11,msg10);
 else
 strcat(msg11,msg10);
 }
  }



fclose(pentru_transfer);

strcpy(mesaj,"\n");
strcat(mesaj,msg11);
}
else
strcpy(mesaj,"Comanda invalida!!");
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}




/***************************/
else

if(strstr(raspuns,"upload:ASCII")||strstr(raspuns,"upload:ASCII"))
{
FILE* pentru_server; //pentru transfer

if(strlen(raspuns)==12)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}

int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
   


if(y==1&&pid_corect==uc){

if((strncmp(raspuns,"upload:ASCII",12)==0)||(strncmp(raspuns,"UPLOAD:ASCII",12)==0))
{

bzero(mesaj,3000);
bzero(mesaj,3000);
password1=(char*)(malloc(sizeof(char)*30));
j=(char*)(malloc(sizeof(char)*30));
if(strlen(raspuns)==12)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>12)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char j[100];
if(raspuns[12]==' '){
password1=(char*)(malloc(sizeof(char)*30));
for(index=13;index<strlen(raspuns);index++)
{
password1[nr++]=raspuns[index];

}
password1[nr++]='\0';
strcpy(j,"/home/diana/serverfiles/");
strcat(j,password1);

pentru_server=fopen(j,"w+");
if(pentru_server==NULL)
{

strcpy(mesaj,"Eroare la reconstituirea fisierului!");
return 1;
}



sir=(char*)(malloc(sizeof(char)*30));
strcpy(sir,"upload");
strcat(sir,password1);
strcpy(mesaj,sir);
int p4=strlen(mesaj);
mesaj[p4]='!';

}
else
strcpy(mesaj,"Comanda invalida!!");

}



}

}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
fclose(pentru_server);
}


else

if(strstr(raspuns,"upload:BINARY")||strstr(raspuns,"upload:BINARY"))
{
FILE* pentru_server; //pentru transfer

int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    if(strlen(raspuns)==13)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect==uc){

if((strncmp(raspuns,"upload:BINARY",13)==0)||(strncmp(raspuns,"UPLOAD:BINARY",13)==0))
{

bzero(mesaj,3000);
bzero(mesaj,3000);
password1=(char*)(malloc(sizeof(char)*30));
j=(char*)(malloc(sizeof(char)*30));
if(strlen(raspuns)==13)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>13)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char j[100];
if(raspuns[13]==' '){
password1=(char*)(malloc(sizeof(char)*30));
for(index=14;index<strlen(raspuns);index++)
{
password1[nr++]=raspuns[index];

}
password1[nr++]='\0';
strcpy(j,"/home/diana/serverfiles/");
strcat(j,password1);

pentru_server=fopen(j,"w+");
if(pentru_server==NULL)
{

strcpy(mesaj,"Eroare la reconstituirea fisierului in server!");
return 1;
}


/*aici vom transfera cu metoda BINARY fisierul de la client la server*/
sir=(char*)(malloc(sizeof(char)*30));
strcpy(sir,"Bupload");
strcat(sir,password1);
strcpy(mesaj,sir);
int k=strlen(mesaj);
mesaj[k]='!';

}
else
strcpy(mesaj,"Comanda invalida!!");

}
}
}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
fclose(pentru_server);
}
else


if(strstr(raspuns,"download:BINARY")||strstr(raspuns,"download:BINARY"))
{

FILE* pentru_server; //pentru transfer

int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
   while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==15)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect==uc){

if((strncmp(raspuns,"download:BINARY",15)==0)||(strncmp(raspuns,"DOWNLOAD:BINARY",15)==0))
{

bzero(mesaj,3000);
bzero(mesaj,3000);
password1=(char*)(malloc(sizeof(char)*30));
j=(char*)(malloc(sizeof(char)*30));
if(strlen(raspuns)==15)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>15)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char j[100];
if(raspuns[15]==' '){
password1=(char*)(malloc(sizeof(char)*30));
for(index=16;index<strlen(raspuns);index++)
{
password1[nr++]=raspuns[index];

}
password1[nr++]='\0';
strcpy(j,"/home/diana/clientFiles/");
strcat(j,password1);

pentru_server=fopen(j,"w+");
if(pentru_server==NULL)
{

strcpy(mesaj,"Eroare la reconstituirea fisierului in server!");
return 1;
}


/*aici vom transfera cu metoda BINARY fisierul de la client la server*/
sir=(char*)(malloc(sizeof(char)*30));
strcpy(sir,"Bdownload");
strcat(sir,password1);
strcpy(mesaj,sir);
int k=strlen(mesaj);
mesaj[k]='!';

}
else
strcpy(mesaj,"Comanda invalida!!");

}
}
}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
fclose(pentru_server);
}


else

if(strstr(raspuns,"download:ASCII")||strstr(raspuns,"download:ASCII"))
{

FILE* pentru_server; //pentru transfer


  
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==14)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect==uc){

if((strncmp(raspuns,"download:ASCII",14)==0)||(strncmp(raspuns,"DOWNLOAD:ASCII",14)==0))
{

bzero(mesaj,3000);
bzero(mesaj,3000);
password1=(char*)(malloc(sizeof(char)*30));
j=(char*)(malloc(sizeof(char)*30));
if(strlen(raspuns)==14)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>14)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char j[100];
if(raspuns[14]==' '){
password1=(char*)(malloc(sizeof(char)*30));
for(index=15;index<strlen(raspuns);index++)
{
password1[nr++]=raspuns[index];

}
password1[nr++]='\0';
strcpy(j,"/home/diana/clientFiles/");
strcat(j,password1);

pentru_server=fopen(j,"w+");
if(pentru_server==NULL)
{

strcpy(mesaj,"Eroare la reconstituirea fisierului!");
return 1;
}


/*aici vom transfera cu metoda ASCII fisierul de la client la server*/
sir=(char*)(malloc(sizeof(char)*30));
strcpy(sir,"download");
strcat(sir,password1);
strcpy(mesaj,sir);
int k=strlen(mesaj);
mesaj[k]='!';

}
else
strcpy(mesaj,"Comanda invalida!!");

}
}
}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
fclose(pentru_server);
}
/*---------------------------------*/

else

if(strstr(raspuns,"touch1:")||strstr(raspuns,"touch1:"))
{



int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==7)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect==uc){
if((strncmp(raspuns,"touch1:",7)==0)||(strncmp(raspuns,"touch1:",7)==0))
{

if(strlen(raspuns)==7)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>7)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;

password1=(char*)(malloc(sizeof(char)*30));
for(index=7;index<strlen(raspuns);index++)
{

password1[nr++]=raspuns[index];
password1[nr+1]='\0';
}



}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
strcat(sirk,password1);
FILE *o;
o=fopen(sirk,"w+");
if(o!=NULL){
strcpy(mesaj,"Fisierul a fost creat!!");
}
else
{
strcpy(mesaj,"Crearea a esuat!!");
return 1;
}

if (fclose(o) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
}


}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}

else

if(strstr(raspuns,"touch2:")||strstr(raspuns,"touch2:"))
{



int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==7)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect==uc){
if((strncmp(raspuns,"touch2:",7)==0)||(strncmp(raspuns,"touch2:",7)==0))
{

if(strlen(raspuns)==7)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>7)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;

password1=(char*)(malloc(sizeof(char)*30));
for(index=7;index<strlen(raspuns);index++)
{

password1[nr++]=raspuns[index];
password1[nr+1]='\0';
}



}
char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/serverfiles/");
strcat(sirk,password1);
FILE *o;
o=fopen(sirk,"w+");
if(o!=NULL){
strcpy(mesaj,"Fisierul a fost creat!!");
}
else
{
strcpy(mesaj,"Crearea a esuat!!");
return 1;
}

if (fclose(o) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
}


}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}


/*--------------------------------------*/
else
if(strstr(raspuns,"mv:")||strstr(raspuns,"mv:"))
{


int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    if(strlen(raspuns)==4)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}


if(y==1&&pid_corect==uc){
if((strncmp(raspuns,"mv:",3)==0)||(strncmp(raspuns,"MV:",3)==0))
{

if(strlen(raspuns)==3)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>3)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char *username1,*username2;

username1=(char*)(malloc(sizeof(char)*30));
for(index=3;index<strlen(raspuns);index++)
{

username1[nr++]=raspuns[index];
username1[nr+1]='\0';

}

char sirk[100],sirkk[100];
strcpy(sirk,"/home/diana/clientFiles/");
strcpy(sirkk,"/home/diana/serverfiles/");
strcat(sirk,username1);
strcat(sirkk,username1);

if(rename(sirk,sirkk)==0)
{

strcpy(mesaj,"Fisier mutat cu succes!!");
}
else
{
strcpy(mesaj,"Mutarea a esuat!!");
}
}
}
}
else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
}
else
if(strncmp(raspuns,"iesire",6)==0)
{

strcpy(mesaj,"Ai parasit aplicatia!!");

}
/**************************************************************/

else

if(strstr(raspuns,"upload_media:")||strstr(raspuns,"upload_media:"))
{

FILE* pentru_server; //pentru transfer

if(strlen(raspuns)==13)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}

int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
  


if(y==1&&pid_corect==uc){

if((strncmp(raspuns,"upload_media:",13)==0)||(strncmp(raspuns,"UPLOAD_MEDIA:",13)==0))
{

bzero(mesaj,3000);
bzero(mesaj,3000);
password1=(char*)(malloc(sizeof(char)*30));
j=(char*)(malloc(sizeof(char)*30));
if(strlen(raspuns)==13)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>13)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char j[100];

password1=(char*)(malloc(sizeof(char)*30));
for(index=13;index<strlen(raspuns);index++)
{
password1[nr++]=raspuns[index];

}
password1[nr++]='\0';
strcpy(j,"/home/diana/serverfiles/");
strcat(j,password1);

/*pentru_server=fopen(j,"wb");
if(pentru_server==NULL)
{

strcpy(mesaj,"Eroare la reconstituirea fisierului!");
return 1;
}
*/


sir=(char*)(malloc(sizeof(char)*30));
strcpy(sir,"media");
strcat(sir,password1);
strcpy(mesaj,sir);
int p4=strlen(mesaj);
mesaj[p4]='!';



}



}

}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
//fclose(pentru_server);
}
/*-----------------------------------------------------*/

else

if(strstr(raspuns,"download_media:")||strstr(raspuns,"download_media:"))
{

FILE* pentru_server; //pentru transfer

if(strlen(raspuns)==15)
{

strcpy(mesaj,"Comanda invalida!!");
return 1;

}

int y,uc,uc1;
FILE * pid;
    pid= fopen("pid.txt", "r+"); 
    if (pid== NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    while (!feof(pid)) {ucok=0;uc1ok=0;
    
        fscanf(pid, "%ld %ld", &uc,&uc1);
      
        if(uc==pid_corect)
        {
        
         FILE * only_user;
    only_user = fopen("valid.pid", "w+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    if (fprintf(only_user, "%d " "%d\n", uc,uc1) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }

    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
        
       // printf("aici sus:%d\n",ucok);
        
        }
    }

    
       FILE * only_user;
    only_user = fopen("valid.pid", "r+"); 
    if (only_user == NULL) {
        perror("Error la deschidere validare_user\n");
       return 1;
    }
    
    while (!feof(only_user)) {
        fscanf(only_user, "%ld" "%ld", &uc,&uc1);
    }


    
  
    if (fclose(only_user) != 0) {
        perror("Error la inchidere validare_user.txt!\n");
        return 1;
    }
      
    y = uc1 % 10;
    
    
    if (fclose(pid) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
  


if(y==1&&pid_corect==uc){

if((strncmp(raspuns,"download_media:",15)==0)||(strncmp(raspuns,"DOWNLOAD_MEDIA:",15)==0))
{

bzero(mesaj,3000);
bzero(mesaj,3000);
password1=(char*)(malloc(sizeof(char)*30));
j=(char*)(malloc(sizeof(char)*30));
if(strlen(raspuns)==15)
{

strcpy(mesaj,"Comanda invalida1!!");
return 1;

}
else
if(strlen(raspuns)>15)
{
int index=0,nr=0,poz=0,pozii=0,gasit=0;
char j[100];

password1=(char*)(malloc(sizeof(char)*30));
for(index=15;index<strlen(raspuns);index++)
{
password1[nr++]=raspuns[index];

}
password1[nr++]='\0';
strcpy(j,"/home/diana/clientFiles/");
strcat(j,password1);




sir=(char*)(malloc(sizeof(char)*30));
strcpy(sir,"dmedia");
strcat(sir,password1);
strcpy(mesaj,sir);

int p4=strlen(mesaj);
mesaj[p4]='!';



}



}

}

else
if(y==0)
{

strcpy(mesaj,"Nu sunteti logat inca!!");
return 1;
}
//fclose(pentru_server);
}


/*----------------------------------------------------------*/
/****************************************************************/
else
if(strncmp("Finalizat",raspuns,9)==0)
{

strcpy(mesaj,"Fisier transferat cu succes!");
}
else
{
strcpy(mesaj,"Comanda invalida!!");

}

}
