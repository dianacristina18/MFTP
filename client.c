
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
  #define MAXI 300000
/* codul de eroare returnat de anumite apeluri */
extern int errno;
size_t size;
int trimite_diferit;
int lg_de_trimis=12,lg_de_trimis1=14,lg_de_trimis2=13,lg_de_trimis3=15,signall=-1,lg_de_trimis4=11;
/* portul de conectare la server*/
 char matrix[3000][3000];
  char l;
  char m1[MAXI];
int port,x,index1=0,index2=0,produs=1,produs1=1,i,ok_fisier=1,bin;
long long lungime=0;
char *password,*password1,p;
int o,k,vv=1,bin;
char pid1[20],pidok[20];
char copy[100];
char msg1[MAXI],msg2[MAXI],msg3[MAXI],msg10[MAXI],text1[100],text[100000],binar[100000],binar1[100000];
int restrictie=0,iden;
 char sir9[MAXI],copy2[100];;
void semnal(int *a);
int main (int argc, char *argv[])
{
 

int pid;
int k=0;
char pid1[20],pidok[20];
 pid=getpid();
 int pid2=pid;
 
 while(pid2)
 {
 
 pid1[k++]=(pid2%10)+'0';
 pid2/=10;
 }
 pid1[k]=NULL;
 int kk=0;
 for(int i=k-1;i>=0;i--)
 pidok[kk++]=pid1[i];
 
 pidok[kk]=NULL;
 
  FILE * p;
    p = fopen("pid.txt", "a+"); 
    if (p == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    if (fprintf(p, "%d ", pid) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
         int x=0;
         if (fprintf(p, "%d\n", x) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
 if (fclose(p) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    
    FILE * pp;
    pp = fopen("nr_conect.txt", "a+"); 
    if (pp == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    if (fprintf(pp, "%s", "+0") < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
         
 if (fclose(pp) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
 
while(1){
int pid;
int k=0;
char pid1[20],pidok[20];
 pid=getpid();
 int pid2=pid;
 
 while(pid2)
 {
 
 pid1[k++]=(pid2%10)+'0';
 pid2/=10;
 }
 pid1[k]=NULL;
 int kk=0;
 for(int i=k-1;i>=0;i--)
 pidok[kk++]=pid1[i];
 
 pidok[kk]=NULL;
 
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  char msg[ MAXI ];		// mesajul trimis

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

  /* citirea mesajului */
  bzero (msg, MAXI);
 
 
 /*CTRL+C <=> quit */
  
 
  //msg[strcspn(msg,"\n")]=0;
  if(restrictie==0){
  
  printf ("[client]Introduceti o comanda: ");
  fflush (stdout);
  read (0, msg, MAXI);
  
  strcat(pidok,"##");
  strcat(pidok,msg);
  strcpy(msg,pidok);
  /* trimiterea mesajului la server */
  if (write (sd, msg, MAXI) <= 0)
    {
      
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
    }
   else
    if(restrictie==1)
    {
    
    strcat(pidok,"##");
  strcat(pidok,msg1);
  strcpy(msg1,pidok);
 
    /* trimiterea mesajului la server */
  if (write (sd, msg1, MAXI) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
    restrictie=0;
    }
    else
    if(restrictie==2)
    {
    
    strcat(pidok,"##");
  strcat(pidok,msg2);
  strcpy(msg2,pidok);
  
    /* trimiterea mesajului la server */
    if (write (sd, msg2, MAXI) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
    restrictie=0;
     
    }
    while(restrictie==5)
    {
  
    if (write (sd, msg10, lg_de_trimis) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
   restrictie=0;
   lg_de_trimis=12;
    }
     while(restrictie==9)
    {

    if (write (sd, msg10, lg_de_trimis1) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
   restrictie=0;
   lg_de_trimis1=14;
    }
     
    while(restrictie==10)
    {

    if (write (sd, msg10, lg_de_trimis2) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
   restrictie=0;
   lg_de_trimis2=13;
    }
     while(restrictie==11)
    {

    if (write (sd, msg10, lg_de_trimis3) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
   restrictie=0;
   lg_de_trimis3=15;
    }
   
   
   while(restrictie==78)
    {

    if (write (sd, msg10, lg_de_trimis4) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
   restrictie=0;
   lg_de_trimis4=11;
    }
    
  /* citirea raspunsului dat de server 
     (apel blocant pina cind serverul raspunde) */
  if (read (sd, msg, MAXI) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    }
  /* afisam mesajul primit */
  if(strcmp("raspuns2",msg)==0)
  printf("[client]Mesajul primit este:Ai parasit aplicatia!\n");
  else
  if(strcmp("raspuns3",msg)==0)
  printf("[client]Mesajul primit este:Revenim la meniul principal!\n");
  else
  if(strcmp(msg,"ok")==0)
  {
  
  printf("[client]Mesajul primit este:Te-ai autentificat cu succes!\n");
  }
  else
  if(strcmp("raspuns1",msg)==0||strncmp("upload",msg,6)==0||strncmp(msg,"media",5)==0||strncmp(msg,"dmedia",6)==0)
  {
  
  int k=1;
  }
  else
  if(strcmp("ls",msg)==0)
  {
   
   char m[100];
    FILE * validare_dir;
    validare_dir= fopen("validare_dir.txt", "r+"); 
    if (validare_dir == NULL) {
        perror("Error la deschidere validare_dir\n");
        return 1;
    }
    
    while (!feof(validare_dir)) {
        fscanf(validare_dir, "%s", m);
        printf("%s\n",m);
        
    }

    
   
    if (fclose(validare_dir) != 0) {
        perror("Error la inchidere validare_dir.txt!\n");
        return 1;
    }
  
  }
  else
  if((strcmp(msg,"Password needed")>0||strcmp(msg,"Password needed")<0)&&(strncmp(msg,"Bupload",7)<0||strncmp(msg,"Bupload",7)>0)&&(strncmp(msg,"download",8)<0||strncmp(msg,"download",8)>0)&&(strncmp(msg,"Bdownload",9)<0||strncmp(msg,"Bdownload",9)>0)){
  
  printf ("[client]Mesajul primit este: %s\n", msg);
  }
  
  if(strcmp(msg,"Ai parasit aplicatia!")==0)
  {
    
    
   return 1;
  }
  else
  if(strcmp(msg,"Password needed")==0)
  {
  
  
  
  password=getpass("[client]Introduceti parola: "); 
  strcpy(msg1,password);
 /*aici vom cripta parola folosind cod ASCII*/
 
  for(i=0;i<strlen(msg1);i++)
  msg1[i]+=16;
  
  char sir1[30]="passwordcheck:";
  strcat(sir1,msg1);
  strcpy(msg1,sir1);
  restrictie=1;
  
  
  }
  else
  if(strcmp(msg,"Parola incorecta!")==0)
  {
    printf("[client]Alegeti o optiune: 1-introdu iar parola, 2-quit, 3-introdu o noua comanda:");
    fflush (stdout);
    bzero (msg, 100);
    read (0, msg, 100);
    char sir2[30]="wrongpassword:";
    strcat(sir2,msg);
    strcpy(msg2,sir2);
    restrictie=2;
  
  }
  else
  if(strcmp(msg,"raspuns1")==0)
  {
  
  
  password=getpass("[client]Introduceti parola: "); 
  strcpy(msg1,password);
  char sir1[30]="passwordcheck:";
  for(i=0;i<strlen(msg1);i++)
  msg1[i]+=16;
  strcat(sir1,msg1);
  strcpy(msg1,sir1);
  restrictie=1;
  
  }
  else
  if(strcmp(msg,"raspuns2")==0)
  {
  FILE * p;
    p = fopen("pid.txt", "w+"); 
    if (p == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    if (fclose(p) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
  return 1;
  
  }
  else
  if(strcmp(msg,"raspuns3")==0)
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
  restrictie=0;
  }
  else
  if(strcmp(msg,"ok")==0)
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
    /*FILE * validare_login;
    validare_login = fopen("valid_login.txt", "w+"); //fisierul care retine 1 daca esti logat si 0 daca te-ai delogat
    if (validare_login == NULL) {
        perror("Error at opening valid.txt\n");
        return 1;
    }
    
    
        x = 1;
                                   
                                   
         if (fprintf(validare_login, "%d", x) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
    
    if (fclose(validare_login) != 0) {
        perror("Error at closing valid.txt!\n");
        return 1;
    }
    */
    int pid;
 pid=getpid();
 
  FILE * p;
    p = fopen("pid.txt", "a+"); 
    if (p == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    if (fprintf(p, "%d ", pid) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
         int x=1;
         if (fprintf(p, "%d\n", x) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
         
         
 if (fclose(p) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    
    FILE * pp;
    pp = fopen("nr_conect.txt", "a+"); 
    if (pp == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    
    if (fprintf(pp, "%s", "+1") < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
        
         
         
 if (fclose(pp) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
  
  }
  else
  if(strncmp("download",msg,8)==0)
  {
 
  password1=(char*)(malloc(sizeof(char)*100));
 
  
   int nr=0;
 
  for(i=8;i<strlen(msg);i++)
  {
  
  password1[nr++]=msg[i];
 
  } 
 
  password1[nr]='\0';
  
 
  strcpy(copy2,"/home/diana/serverfiles/");
 
  strcpy(copy,password1);
  strcat(copy2,copy);
  
  
  
  FILE *pentru_transfer;
  pentru_transfer=fopen(copy2,"r");
  if(pentru_transfer==NULL)
  {
  printf("Nu exista acest fisier!\n");
  
  
  }
  
 
 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file
 
   char lg[100000];
   sprintf(lg,"%d",lungime);
  
  
  strcpy(sir9,"download");
  strcat(sir9,"##");
   strcat(sir9,lg);
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
  lg_de_trimis1+=lungime;
  lg_de_trimis1+=strlen(lg);
  lg_de_trimis1+=strlen(password1);
  
  while(fgets(msg10,3000,pentru_transfer)){
  k++;
  
  strcat(sir9,msg10);
  restrictie=9;
  
  strcpy(msg10,sir9);
  strcat(msg10,"\0");
  
 
  }
  
    bzero(msg,3000);
    

 

  fclose(pentru_transfer);
  }
  
   else
  if(strncmp("upload",msg,6)==0)
  {
 
  password1=(char*)(malloc(sizeof(char)*100));
 
  
   int nr=0;
 
  for(i=6;i<strlen(msg);i++)
  {
  
  password1[nr++]=msg[i];
 
  } 
 
  password1[nr]='\0';
  
 
  strcpy(copy2,"/home/diana/clientFiles/");
 
  strcpy(copy,password1);
  strcat(copy2,copy);
  
  
 
  FILE *pentru_transfer;
  pentru_transfer=fopen(copy2,"r");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  
 if(vv==0)
 {
  
  printf("Nu exista fisierul selectat!\n");
 
 }
 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file
  
   char lg[100000];
   sprintf(lg,"%d",lungime);
   
  
  strcpy(sir9,"upload");
  strcat(sir9,"##");
   strcat(sir9,lg);
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
  lg_de_trimis+=lungime;
  lg_de_trimis+=strlen(lg);
  lg_de_trimis+=strlen(password1);
  
  while(fgets(msg10,3000,pentru_transfer)){
  k++;
  
  strcat(sir9,msg10);
  restrictie=5;
  
  strcpy(msg10,sir9);
  strcat(msg10,"\0");
  
 
  }
  

    bzero(msg,3000);
    

 

  fclose(pentru_transfer);
  }
  /************************************/
  
  
  
  
  else
  if(strncmp("media",msg,5)==0)
  {
 
  password1=(char*)(malloc(sizeof(char)*100));
 
  
   int nr=0;
 
  for(i=5;i<strlen(msg);i++)
  {
  
  password1[nr++]=msg[i];
 
  } 
 
  password1[nr]='\0';
  
 
  strcpy(copy2,"/home/diana/clientFiles/");
 
  strcpy(copy,password1);
  strcat(copy2,copy);
  
  
 
  FILE *pentru_transfer;
  pentru_transfer=fopen(copy2,"rb");
  if(pentru_transfer==NULL)
  { 
  printf("Nu exista acest fisier!\n");
  
  
  }
  
 
 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
  long long lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file
  
   char lg[100000];
   sprintf(lg,"%d",lungime);
   
  
  strcpy(sir9,"media");
  strcat(sir9,"##");
   strcat(sir9,lg);
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
  lg_de_trimis4+=lungime;
  lg_de_trimis4+=strlen(lg);
  lg_de_trimis4+=strlen(password1);
  
  /*while(fgets(msg10,3000,pentru_transfer)){
  k++;
  
  strcat(sir9,msg10);
  restrictie=5;
  
  strcpy(msg10,sir9);
  strcat(msg10,"\0");
  
 
  }
  */
  


strcpy(msg10,sir9);
strcat(msg10,"\0");

restrictie=78;




    bzero(msg,3000);
    

 

  fclose(pentru_transfer);
  }
  
  else
  if(strncmp("dmedia",msg,6)==0)
  {
 
  password1=(char*)(malloc(sizeof(char)*100));
 
  
   int nr=0;
 
  for(i=6;i<strlen(msg);i++)
  {
  
  password1[nr++]=msg[i];
 
  } 
 
  password1[nr]='\0';
  
 
  strcpy(copy2,"/home/diana/serverFiles/");
 
  strcpy(copy,password1);
  strcat(copy2,copy);
  
  
 
  
  
  
   
  
  strcpy(sir9,"dmedia");
  strcat(sir9,"##");
  strcat(sir9,"rdc");
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
  lg_de_trimis4+=lungime;
  lg_de_trimis4+=strlen("rdc");
  lg_de_trimis4+=strlen(password1);
  
  /*while(fgets(msg10,3000,pentru_transfer)){
  k++;
  
  strcat(sir9,msg10);
  restrictie=5;
  
  strcpy(msg10,sir9);
  strcat(msg10,"\0");
  
 
  }
  */
  


strcpy(msg10,sir9);
strcat(msg10,"\0");

restrictie=78;




    bzero(msg,3000);
    

 

 
  }
  
  /************************************/
   else
  if(strncmp("Bupload",msg,7)==0)
  {
  
 
  password1=(char*)(malloc(sizeof(char)*100));
 
  
   int nr=0;
 
  for(i=7;i<strlen(msg);i++)
  {
  
  password1[nr++]=msg[i];
 
  } 
 
  password1[nr]='\0';
  
 
  strcpy(copy2,"/home/diana/clientFiles/");
 
  strcpy(copy,password1);
  strcat(copy2,copy);
  
  
  
  FILE *pentru_transfer;
  pentru_transfer=fopen(copy2,"rb");
  if(pentru_transfer==NULL)
  {
 
  printf("Nu exista acest fisier!\n");
  ok_fisier=0;
  
  }
  
 if(ok_fisier==1){
 
 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
   lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file
  
   char lg[100000];
   sprintf(lg,"%d",lungime);
   bzero(msg10,100000);
  
  strcpy(sir9,"upload");
  strcat(sir9,"##");
   strcat(sir9,lg);
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
  lg_de_trimis2+=lungime;
  lg_de_trimis2+=strlen(lg);
  lg_de_trimis2+=strlen(password1);
  
  while(fgets(msg10,3000,pentru_transfer)){
  k++;
  
  strcat(sir9,msg10);
  //restrictie=5;
  
  strcpy(msg10,sir9);
  strcat(msg10,"\0");
  
 
  }
  nr=0;
  
  for(int i=lg_de_trimis2-lungime-1;i<strlen(msg10)-1;i++)
  {
    if(msg10[i]!='\n'){
  
  if(msg10[i]=='#')
  bin=35;
  else
  if(msg[10]=='%')
  bin=25;
  else
  {
 
 
  l=msg10[i];
   bin=l;
 
   p=bin;
   }
 }
 else
 {
 
 binar[nr++]='\n';
 }
  while(bin)
  {
 
  if(bin%2)
  binar[nr++]='1';
  else
  binar[nr++]='0';
  bin/=2;
  
  }
  if(i!=strlen(msg10))
  binar[nr++]=' ';
 
 
  }
  
  binar[nr]=NULL;
  
 
   
    bzero(msg,3000);
    fclose(pentru_transfer);
    
    
}

 int nr1=0;
 nr=0;
 
  
  lg_de_trimis2=13;
  lungime=strlen(binar);
  char lg[100000];
  sprintf(lg,"%d",lungime);
  lg_de_trimis2+=lungime;
  lg_de_trimis2+=strlen(lg);
  lg_de_trimis2+=strlen(password1);
    
    
     strcpy(sir9,"uploadB");
  strcat(sir9,"##");
   strcat(sir9,lg);
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
  strcpy(msg10,sir9);
  strcat(msg10,binar);
  strcat(msg10,"\0");
 
  restrictie=10;
 
  
  
  }
  
  
  else
  if(strncmp("Bdownload",msg,9)==0)
  {
  
 
  password1=(char*)(malloc(sizeof(char)*100));
 
  
   int nr=0;
 
  for(i=9;i<strlen(msg);i++)
  {
  
  password1[nr++]=msg[i];
 
  } 
 
  password1[nr]='\0';
  
 
  strcpy(copy2,"/home/diana/serverfiles/");
 
  strcpy(copy,password1);
  strcat(copy2,copy);
  
  
  
  FILE *pentru_transfer;
  pentru_transfer=fopen(copy2,"rb");
  
  if(pentru_transfer==NULL)
  {
 
  printf("Nu exista acest fisier!\n");
  ok_fisier=0;
  
  }
  
 if(ok_fisier==1){
  
 fseek(pentru_transfer, 0, SEEK_END); // seek to end of file
   lungime = ftell(pentru_transfer); // get current file pointer
fseek(pentru_transfer, 0, SEEK_SET); // seek back to beginning of file
  
   char lg[100000];
   sprintf(lg,"%d",lungime);
   bzero(msg10,100000);
  
  strcpy(sir9,"download");
  strcat(sir9,"##");
   strcat(sir9,lg);
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
 
  lg_de_trimis3+=lungime;
  lg_de_trimis3+=strlen(lg);
  lg_de_trimis3+=strlen(password1);
  
  while(fgets(msg10,3000,pentru_transfer)){
  k++;
  
  strcat(sir9,msg10);
  //restrictie=5;
  
  strcpy(msg10,sir9);
  strcat(msg10,"\0");
  
 
  }
  
  nr=0;
  
  for(int i=lg_de_trimis3-lungime-1;i<strlen(msg10)-1;i++)
  {
    if(msg10[i]!='\n'){
  
  if(msg10[i]=='#')
  bin=35;
  else
  if(msg[10]=='%')
  bin=25;
  else
  {
 
 
  l=msg10[i];
   bin=l;
 
   p=bin;
   }
 }
 else
 {
 
 binar[nr++]='\n';
 }
  while(bin)
  {
 
  if(bin%2)
  binar[nr++]='1';
  else
  binar[nr++]='0';
  bin/=2;
  
  }
  if(i!=strlen(msg10))
  binar[nr++]=' ';
 
 
  }
  
  binar[nr]=NULL;
  
 
   
    bzero(msg,3000);
    fclose(pentru_transfer);
    
    
}

 int nr1=0;
 nr=0;
 
  
  lg_de_trimis3=15;
  lungime=strlen(binar);
  char lg[100000];
  sprintf(lg,"%d",lungime);
  lg_de_trimis3+=lungime;
  lg_de_trimis3+=strlen(lg);
  lg_de_trimis3+=strlen(password1);
    
     
     strcpy(sir9,"downloadB");
  strcat(sir9,"##");
   strcat(sir9,lg);
   strcat(sir9,"##");
  strcat(sir9,password1);
  strcat(sir9,"##");
  strcpy(msg10,sir9);
  strcat(msg10,binar);
  strcat(msg10,"\0");
 
  restrictie=11;
 
  
  
  }
  
  
  else
  if(strncmp(msg,"Te-ai delogat cu succes!",24)==0)
  {
  
  int uc,uc1;
  int pid;
  int pid2;
 pid=getpid();

  FILE * ppp,*pp;
 pid=getpid();
 pid2=pid;
  
    ppp = fopen("pid.txt", "a+"); 
    if (p == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    if (fprintf(ppp, "%d ", pid2) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
         int x=0;
         if (fprintf(ppp, "%d\n", x) < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
         
 if (fclose(ppp) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
    
    pp = fopen("nr_conect.txt", "a+"); 
    if (pp == NULL) {
        perror("Error la deschidere validare_login\n");
        return 1;
    }
    if (fprintf(pp, "%s", "-1") < 0)

         {
           printf("Error at writing in valid.txt!\n");
           return 1;
         }
         
         
 if (fclose(pp) != 0) {
        perror("Error la inchidere validare_login.txt!\n");
        return 1;
    }
  
  
  }
   
  /* inchidem conexiunea, am terminat */
  close (sd);
  }
}

