#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char* output_format="%s, %s, %s, %d\n" ;
const char* input_format="%[^,], %[^,], %[^,], %d\n" ;

typedef struct Hangman{
    char word[20];
    char topic[20];
    char hint[100];
    int points;
    struct Hangman *next;

}Hangman;

int hangman_game(char word[20],char hint[100],int points)
{
    int n = strlen(word),contor;
    int mask[n],trials=5;
    for (int i=0; i < n; ++i) {
       mask[i] = 0;
    }
    int gameover = 0;
    while (trials!=0 && gameover != n) {
        contor=0;
        printf("\n\tThe word is : ");
        for(int j=0; j < n; ++j) {
          if (mask[j])
         {
            printf("%c", word[j]);
          }
          else {
            printf("*");
              }
            }
        printf("\n");

        char guess;
        printf("\n\tLetter? ");
        fflush(stdout);
        scanf(" %c", &guess);

        for(int k=0; k < n; ++k) {
          if (word[k] == guess) {
                mask[k] = 1;
                contor=1;
          }
        }
        if(contor==0)
            trials--;


        gameover = 0;
        for(int m = 0; m < n; ++m)
        {
          if (mask[m]==1)
            gameover++;

        }

        if(trials==1 )
            printf("\n\tYou have only one life left, here is a hint: %s",hint);

  }

  if(gameover)
  {printf("\n\tVictory! The word is \"%s\".\n", word);
  return points;}

  else
  {printf("Sorry,you lost...The word is \"%s\".\n", word);
  return 0;}


}


int game_setup()
{
    FILE *file;
    fopen_s(&file,"hangman_words.dat","r");
    Hangman h1;
    char topic1[20];
    printf("\n\tChoose a topic or write \"None\": ");
    scanf("%s",topic1);
    int n=0;
    while(fscanf_s(file,input_format,h1.word,20,h1.topic,20,h1.hint,100,&h1.points)!= EOF)
        if(stricmp("None",topic1)==0)
                   n++;
        else if(stricmp(h1.topic,topic1)==0)
                   n++;
   // printf("%d",n);
    if(n==0)
       {
           printf("\n\tTopic not found!");
       }
    else
    {
    srand(time(NULL));
    int random_number = rand() % n + 1;
    //printf("%d",random_number);
    while(fscanf_s(file,input_format,h1.word,20,h1.topic,20,h1.hint,100,&h1.points)!= EOF && random_number!=0)
        if(strcpy("None",topic1)==0)
            random_number--;
        else if(strcpy(h1.topic,topic1)==0)
            random_number--;
       else
         printf("\n\tSomething went wrong, check game_setup");

    hangman_game(h1.word,h1.hint,h1.points);
    fclose(file);


    }

}


void search()
{
    system("cls");
    char s[100];
    FILE *file;
    fopen_s(&file,"hangman_words.dat","r");
    Hangman h1;
    printf("\n\t[1] Search by word\t\t[2] Search by topic");
    printf("\n\tEnter your choice: ");
    int ch;
    scanf("%d",&ch);
    fflush(stdin);
     //let me read and write to it
    if (file==NULL)
    {
        return 1; //Error
    }
    printf("%d",ch);
    switch (ch)

    {

    case 1:
        system("cls");
        fflush(stdin);
        printf("\n\tWord to search:");
        scanf("%[^\n]",s);
        fflush(stdin);
        while(fscanf_s(file,input_format,h1.word,20,h1.topic,20,h1.hint,100,&h1.points)!= EOF)
        {

             if(strcmp(s,h1.word)==0)
                printf(output_format,h1.word,h1.topic,h1.hint,h1.points);

        }
        break;

     case 2:
     system("cls");
     fflush(stdin);
     printf("\n\tTopic to search:");
     scanf("%[^\n]s",s);
     fflush(stdin);
     while(fscanf_s(file,input_format,h1.word,20,h1.topic,20,h1.hint,100,&h1.points)!= EOF)
     {
         if(strcmp(s,h1.topic)==0)
             printf(output_format,h1.word,h1.topic,h1.hint,h1.points);

     }
    break;

    default:
        printf("Invalid choice");
        break;

    }
    if( fclose(file)!= 0)
        {
              printf("Error File Close");
        }

}
void add()
{
    system("cls");
    FILE *file;
    fopen_s(&file,"hangman_words.dat","a"); //let me read and write to it
    if (file==NULL)
    {
        return 1; //Error
    }
    Hangman h1;
    fflush(stdin);
    printf("Word:");
    scanf("%[^\n]s",h1.word);
    fflush(stdin);
    //gets(h1.word);

    printf("Topic:");
    scanf("%[^\n]s",h1.topic);
    fflush(stdin);

    printf("Hint:");
    scanf("%[^\n]s",h1.hint);
    fflush(stdin);
    printf("Points given:");
    scanf("%d",&h1.points);
    fflush(stdin);

    fprintf_s(file,output_format,h1.word,h1.topic,h1.hint,h1.points);

    fclose(file);
}

void update()
{
    system("cls");

     fflush(stdin);
     FILE *file,*copy;
     file=fopen("hangman_words.dat","r");
     copy=fopen("copy.dat","w");
     char s[100],s1[100],s2[100],s3[100];
     int p,contor=0;
     printf("\n\tWord to update:");
     scanf("%[^\n]s",s);
     Hangman h1;
     while(fscanf_s(file,input_format,h1.word,20,h1.topic,20,h1.hint,100,&h1.points)!= EOF)
     {
         if(stricmp(s,h1.word)==0)
         {

            contor=1;
            fflush(stdin);
            printf("Word:");
            scanf("%[^\n]s",s1);
            strcpy(h1.word,s1);
            fflush(stdin);

            printf("Topic:");
            scanf("%[^\n]s",s2);
            strcpy(h1.topic,s2);
            fflush(stdin);

            printf("Hint:");
            scanf("%[^\n]s",s3);
            strcpy(h1.hint,s3);

            fflush(stdin);
            printf("Points given:");
            scanf("%d",&p);
            h1.points=p;
            fflush(stdin);

            fprintf_s(copy,output_format,h1.word,h1.topic,h1.hint,h1.points);


         }
         else
            fprintf_s(copy,output_format,h1.word,h1.topic,h1.hint,h1.points);
     }
     if(contor==0)
        printf("\n\tThis word is not in the file");
     if( fclose(file)!= 0)
        {
              printf("Error File fp");
        }
    if( fclose(copy)!= 0)
        {
              printf("Error File ft");
        }
    if( remove("hangman_words.dat") != 0)
        {
              printf("Error Remove");
        }
     if(rename("copy.dat","hangman_words.dat") != 0)
        {
              printf("Error Rename");
        }

}


void display_words()
{
    system("cls");
    FILE *file;
    fopen_s(&file,"hangman_words.dat","r");
    Hangman h1;
    if (file==NULL)
    {
        return 1; //Error
    }

    while(fscanf_s(file,input_format,h1.word,20,h1.topic,20,h1.hint,100,&h1.points)!= EOF) //end of file
    {
        printf(output_format,h1.word,h1.topic,h1.hint,h1.points);
    }
    fclose(file);

}
void delete_word()
 {
     system("cls");

     fflush(stdin);
     FILE *file,*copy;
     file=fopen("hangman_words.dat","r");
     copy=fopen("copy.dat","w");
     char s[100];
     printf("\n\tWord to delete:");
     scanf("%[^\n]s",s);
     Hangman h1;
     while(fscanf_s(file,input_format,h1.word,20,h1.topic,20,h1.hint,100,&h1.points)!= EOF)
     {
         if(stricmp(s,h1.word)!=0)
            fprintf_s(copy,output_format,h1.word,h1.topic,h1.hint,h1.points);
     }
     if( fclose(file)!= 0)
        {
              printf("Error File fp");
        }
    if( fclose(copy)!= 0)
        {
              printf("Error File ft");
        }
    if( remove("hangman_words.dat") != 0)
        {
              printf("Error Remove");
        }
     if(rename("copy.dat","hangman_words.dat") != 0)
        {
              printf("Error Rename");
        }


 }



int main()
{
    int ch;
    char s[100];
    main:

    system("cls");

    printf("\n\t Welcome to Hangman Game ");

    printf("\n\t[0] EXIT\n\t[1] PLAY THE GAME\n\t[2] DISPLAY WORDS\n\t[3] ADD WORD\n\t[4] DELETE WORD\n\t[5] SEARCH IN FILE\n\t[6] UPDATE WORD");

    printf("\n\tEnter your choice: ");

    scanf("%d",&ch);

    switch(ch)

    {

    case 0:

        printf("\n\tAre you sure you want to exit?\n");

        break;
    case 1:
        game_setup();
        break;

    case 2:
        display_words();
        break;
    case 3:
        add();
        break;
    case 4:
        delete_word();
        break;
    case 5:
        search();
        break;
    case 6:
        update();
        break;

    default:
        printf("Invalid choice");
        break;


    }
printf("\n\t[1] Main Menu\t\t[0] Exit");
printf("\n\tEnter your choice: ");

    scanf("%d",&ch);

    switch (ch)

    {

    case 1:
        goto main;

    case 0:
        break;

    default:
        printf("Invalid choice");
        break;

    }


    return 0;
}
