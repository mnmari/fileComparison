#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//defines list
typedef struct List
{
    char *word;
    int freq;
    struct List *prox;
} list;

//function headers
list* initialize(void);
list* addToList(list*, char*);
list* searchAndAdd(list*, char t[]);
list* addElementToList(list*, FILE *);
list* removeIndex(list*, list*);
int listsProjection(list*, list*);
float listsExtent(list*);
float listsAngle(list*, list*);
float percentage(float);
void printFile(list*, list*, FILE*);
void printOnScreen(float);
void deallocate(list*);
void order(list*);

//main
int main(int argc, char *argv[])
{
    FILE *arq1, *arq2, *arqFinal;
    list *l1, *l2;
    list *p;

    //opens files via command line (using main function arguments)
    if (argc != 3)
    {
        printf("Error!\nPlease verify filename.\n");
        exit(1);
    }

    arq1 = fopen(argv[1], "r");
    arq2 = fopen(argv[2], "r");

    if (arq1 == NULL || arq2 == NULL)
    {
        printf("Error!\nThere was a problem opening the file.\n");
        exit(2);
    }

    l1 =  initialize();
    l2 =  initialize();

    l1 = addElementToList(l1, arq1);
    l2 = addElementToList(l2, arq2);

    order(l1);
    order(l2);

    arqFinal = fopen("compareProg.txt", "w");
    printFile(l1, l2, arqFinal);

    printf("\nFile comparison '%s' e '%s': ", argv[1], argv[2]);
    printOnScreen(listsAngle(l1, l2));

    free(l1);
    free(l2);

    fclose(arq2);
    fclose(arq1);
    fclose(arqFinal);

    return 0;
}

//initializing list
list* initialize(void)
{
    return NULL;
}

//adds list elements
list* addElementToList(list *l, FILE *arq)
{
    list *novo;
    char  p[40], temp;
    int check, i;

    do
    {
        //check: variable used to enter/exit the loop when needed
        check = 1;
        i = 0;
        do
        {
            //starts reading file
            fscanf(arq, "%c", &temp);

           //verifies if there are comments and, if that's the case, ignores them; copies "//", "/*" e "*/" to list
            if (temp == '/')
            {
                fscanf(arq, "%c", &temp);
                if (temp == '/')
                {
                    l = searchAndAdd(l, (char*)"//");

                    //reads all comments until '\n', but it doesn't include '\n' to list
                    while (temp != '\n')
                        fscanf(arq, "%c", &temp);
                }

                else if (temp == '*')
                {
                    l = searchAndAdd(l, (char*)"/*");
                    temp = 1;

                    while (temp)
                    {
                        fscanf(arq, "%c", &temp);
                        if (temp == '*')
                        {
                            fscanf(arq, "%c", &temp);
                            if( temp == '/')
                            {
                                l = searchAndAdd(l, (char*)"*/");
                                temp = 0;
                            }
                        }
                    }
                }

                else //adds division
                {
                    l = searchAndAdd(l, (char*)"/");
                    check = 0;
                }
            }

            //ignored characters
            if (temp == 32  ||
                temp == 10  ||
                temp == 9   ||
                temp == '(' ||
                temp == ')' ||
                temp == '"' ||
                temp == ',' ||
                temp == ';' ||
                temp == ':' ||
                temp == '{' ||
                temp == '}')
                check = 0;

            //valid characters
            else if (temp == '+' ||
                     temp == '-' ||
                     temp == '*' ||
                     temp == '%' ||
                     temp == '#')
                     {
                         l = searchAndAdd(l, (char*)"temp");
                         check = 0;
                     }

            else if (temp == '=')
            {
                fscanf(arq, "%c", &temp);

                if (temp == '=')
                {
                    l = searchAndAdd(l, (char*)"==");
                    check = 0;
                }

                else
                {
                    l = searchAndAdd(l, (char*)"=");
                    check = 0;
                }
            }

            else if (temp == '<')
            {
                fscanf(arq, "%c", &temp);

                if (temp == '=')
                {
                    l = searchAndAdd(l, (char*)"<=");
                    check = 0;
                }

                else
                {
                    l = searchAndAdd(l, (char*)"<");
                    
                    p[i] = temp;
                    i++;
                }
            }

            else if (temp == '>')
            {
                fscanf(arq, "%c", &temp);

                if (temp == '=')
                {
                    l = searchAndAdd(l, (char*)">=");
                    check = 0;
                }

                else
                {    l = searchAndAdd(l, (char*)">");
                    
                     p[i] = temp;
                     i++;
                }
            }

            else if (temp == '!')
            {
                fscanf(arq, "%c", &temp);

                if (temp == '=')
                {
                    l = searchAndAdd(l, (char*)"!=");
                    check = 0;
                }

                else
                {
                    l = searchAndAdd(l, (char*)"!");
                   
                    p[i] = temp;
                    i++;
                }
            }

            else if (temp == '|')
            {
                fscanf (arq, "%c", &temp);

                if (temp == '|')
                {
                    l = searchAndAdd(l, (char*)"||");
                    check = 0;
                }

                else
                {
                    l = searchAndAdd(l, (char*)"|");
                    
                    p[i] = temp;
                    i++;
                }
            }

            else if (temp == '&')
            {
                fscanf(arq, "%c", &temp);

                if (temp == '&')
                {
                    l = searchAndAdd(l, (char*)"&&");
                    check = 0;
                }

                else
                {
                    l = searchAndAdd(l, (char*)"&");
                   
                    p[i] = temp;
                    i++;
                }
            }

            else
            {
                p[i] = temp;
                i++;
            }

        } while (check);

        if(i!=0)
        {
            p[i] = '\0'; //end of string
            l = searchAndAdd(l, p);
        }
    } while (!feof(arq));

    return l;
}

//add elements to the list
list* addToList(list *l, char *t)
{
    list *new = (list*) malloc(sizeof(list));
    new->word = (char *) malloc(sizeof(char)*(strlen(t)+ 1)); //allocate memory for each string element of the list
    strcpy (new->word, t);
    
    new->prox = l;
    new->freq = 1; //new element
    return new;
}

//searches and adds elements to the list
list* searchAndAdd(list *l, char *t)
{
        list *point, *novo;

        //string comparison
        for (point = l; point != NULL; point = point->prox)
        {
            if (!(strcmp(point->word, t)))
            {
                point->freq++; //identical strings, so it increments frequency
                return l;
            }
        }
        novo = addToList(l, t); //adds new element as it was not found on the list
        return novo;
}

//orders list
void order(list* l)
{
    list *point1, *point2;
    int freqTemp, check = 1;
    char *wordTemp;

    while (check)
    {
        check = 0;

        for(point1 = l; point1->prox != NULL; point1 = point1->prox)
        {
            point2 = point1->prox;

            if(point1->freq < point2->freq)
            {
                check = 1;
                freqTemp = point1->freq;
                point1->freq = point2->freq;
                point2->freq = freqTemp;

                wordTemp = point1->word;
                point1->word = point2->word;
                point2->word = wordTemp;
            }
        }
    }
}

//projection evaluation
int listsProjection(list *l1, list *l2)
{
    list *point1, *point2;
    int projection = 0;

    for (point1 = l1; point1 != NULL; point1 = point1->prox)
        for (point2 = l2; point2 != NULL; point2 = point2->prox)
            if (!(strcmp(point1->word, point2->word)))
                projection += point1->freq * point2->freq;

    return projection;
}

//calculates the list extent
float listsExtent(list *l)
{
    list *point;
    float sum = 0, mag;

    for (point = l; point != NULL; point = point->prox)
         sum += pow(point->freq, 2);

    mag = sqrt(sum);
    return mag;
}

//calculates the angle between lists
float listsAngle(list *l1, list *l2)
{
    float ratio, angle;
    int projection;

    projection = listsProjection(l1, l2);
    ratio = abs(((float)projection)/(listsExtent (l1)*listsExtent (l2)));

    if((ratio < -1) || (ratio > 1))
    {
        printf("ERROR.\n");
        exit(3);
    }

    angle = acos(ratio);
    return angle;
}

//evaluates the difference between lists as a percentage
float percentage(float angle)
{
    float por;

    por = cos(angle);
    por *= 100;

    return por;
}

//prints output on screen
void printOnScreen(float angle)
{
    float por;

    printf("\n\nAngle between documents: %f degrees.\n", angle*180/M_PI);

    por = percentage(angle);
    if (por >= 50)
        printf("There was plagiarism!\n");

    else
        printf("There was not plagiarism!\n");
}

//prints on file 'compareProg.txt'
void printFile(list *l1, list *l2, FILE *file)
{
    list *point;

    fprintf(file, "First file:\n\n");
    for (point = l1; point != NULL; point = point->prox)
    {
        fprintf(file, "String: '%s'\n", point->word);
        fprintf(file, "Frequency: %d\n\n", point->freq);
    }

    fprintf(file, "\n\nSecond file:\n\n");
    for (point = l2; point != NULL; point = point->prox)
    {
        fprintf(file, "String: '%s'\n", point->word);
        fprintf(file, "Frequency: %d\n\n", point->freq);
    }
}

//deallocates memory of list
void deallocate(list *l)
{
    list *point = l, *t;
    while (point != NULL)
    {
        t = point->prox;
        free(point->word);
        free(point);
        point = t;
    }
}
