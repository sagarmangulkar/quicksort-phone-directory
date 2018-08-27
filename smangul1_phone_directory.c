#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//stucture to store each record
typedef struct directory{
    int id;
    char firstName[50];
    char lastName[50];
    char phoneNumber[20];
}Directory;

Directory * dir = NULL;
int dirLength = 0;

//displays complete phone directory
void display(){
    int i;
    printf("\n-----------------Phone Directory--------------- Size of Directory: %d\n", dirLength+1);
    for(i = 0; i <= dirLength; i++){
        printf("%d   ",i+1);
        printf("%s\t", dir[i].firstName);
        printf("%s\t\t", dir[i].lastName);
        printf("%s\n", dir[i].phoneNumber);
    }
    printf("-----------------------------------------------\n");
}

//create phone directory by fetching data from txt file
int create(char *fileName[]){
    dir =  malloc(100 * sizeof(Directory));
    int i = 0;
    int allocatedSize = 100;
    FILE * file;
    file = fopen(fileName[1], "r");
    if(file){
        while(!feof(file)){
            fscanf(file, "%s %s %s", dir[i].firstName, dir[i].lastName, dir[i].phoneNumber);
            if(!feof(file)){
                
strcpy(dir[i].lastName,strtok(dir[i].lastName,","));
                dir[i].id = i + 1;
                i++;
                if(i >= allocatedSize-1){
                    allocatedSize = allocatedSize + 100;
                    dir = realloc(dir, allocatedSize * sizeof(Directory));
                }
            }
        }
        fclose(file);
        return i-1;
    }
    else{
        printf("please check the file name or no such file is present.\n");
    }
    return -1;
}

//lower the case of string
void lowerCase(char value[], char *temp){
    int i;
    for(i = 0; value[i]; i++){
        temp[i] = tolower(value[i]);
    }
    temp[i] = '\0';
}

//swaps two struct element
void swap(int i, int j)
{
    Directory *dirTemp = malloc(10 * sizeof(Directory));
    dirTemp[0] = dir[i];
    dir[i] = dir[j];
    dir[j] = dirTemp[0];
    free(dirTemp);
}

//provides the partition stuct element dependind on random pivot
int partition(int p, int r)
{
    int pivotIndex = p + rand()%(r - p + 1);    //generate random number
    char pivot[50];
    char pivotLastName[50];
    char pivotPhoneNumber[20];
    int i = p - 1;
    int j;
    char tempFirstName[50];
    char tempLastName[50];
    char tempPivot[50];
    char tempPivotLastName[50];
    strcpy(pivot,dir[pivotIndex].firstName);
    strcpy(pivotLastName,dir[pivotIndex].lastName);
    strcpy(pivotPhoneNumber, dir[pivotIndex].phoneNumber);
    swap(pivotIndex, r);
    for (j = p; j < r; j++)
    {
        strcpy(tempFirstName,"");
        strcpy(tempLastName,"");
        strcpy(tempPivot,"");
        strcpy(tempPivotLastName,"");
        lowerCase(dir[j].firstName, tempFirstName);
        lowerCase(pivot, tempPivot);
        lowerCase(dir[j].lastName, tempLastName);
        lowerCase(pivotLastName, tempPivotLastName);
        if (strcmp(tempFirstName, tempPivot) < 0)
        {
            i++;
            swap(i, j);
        }
        else if ((strcmp(tempFirstName, tempPivot) == 0) && (strcmp(tempLastName, tempPivotLastName) < 0)) 
        {
            i++;
            swap(i, j);
        }
        else if ((strcmp(tempFirstName, tempPivot) == 0) && (strcmp(tempLastName, tempPivotLastName) == 0) 
                && (strcmp(dir[j].phoneNumber,pivotPhoneNumber) < 0)) 
        {
            i++;
            swap(i, j);
        }
    }
    swap(i+1, r);
    return i + 1;
}

//sorts the array - quick sort
void Sort_contact(int p, int q)
{
    int j;
    if (p < q)
    {
        j = partition(p, q);
        Sort_contact(p, j-1);
        Sort_contact(j+1, q);
    }
}

//binary search algorithm
int search(char* name) {
    int lowerBound = 0;
    int upperBound = dirLength;
    int midPoint = -1;
    int comparisons = 0;      
    int index = -1;
    char fullName0[100] = "";
    char fullName1[100] = "";
    char fullName2[100] = "";
    char fullName3[100] = "";

    while(lowerBound <= upperBound) {
        comparisons++;
        midPoint = lowerBound + (upperBound - lowerBound) / 2;	
        strcpy(fullName0,"");
        strcat(fullName0, dir[midPoint].firstName);
        strcat(fullName0, " ");
        strcat(fullName0, dir[midPoint].lastName);

        strcpy(fullName1,"");
        strcat(fullName1, dir[midPoint].firstName);
        strcat(fullName1, " ");
        strcat(fullName1, dir[midPoint].lastName);
        strcat(fullName1, " ");
        strcat(fullName1, dir[midPoint].phoneNumber);

        strcpy(fullName2,"");
        strcat(fullName2, dir[midPoint].firstName);
        strcat(fullName2, " ");
        strcat(fullName2, dir[midPoint].lastName);
        strcat(fullName2, ", ");
        strcat(fullName2, dir[midPoint].phoneNumber);

        strcpy(fullName3,"");
        strcat(fullName3, dir[midPoint].firstName);
        strcat(fullName3, " ");
        strcat(fullName3, dir[midPoint].lastName);
        strcat(fullName3, " , ");
        strcat(fullName3, dir[midPoint].phoneNumber);

        //Name found
        if((strcmp(fullName0, name) == 0) || (strcmp(fullName1, name) == 0) || strcmp(fullName2, name) == 0 || strcmp(fullName3, name) == 0){
            index = midPoint;
            break;
        } 
        else {
            //if Name is greater 
            if((strcmp(fullName0, name) == 0) || (strcmp(fullName1, name) < 0) 
                    || strcmp(fullName2, name) < 0 || strcmp(fullName3, name) < 0){
                //name is in upper half
                lowerBound = midPoint + 1;
            }
            //if Name is smaller 
            else {
                //name is in lower half 
                upperBound = midPoint -1;
            }
        }               
    }
    return index;
}

//delete the record
void delete(char* name){
    int index;
    index = search(name);
    if(index == -1){
        printf("No such name present in directory.\n");
        return;
    }
    int i;
    printf("Deletion Successful, Deleted Record: %s %s, %s\n", dir[index].firstName, dir[index].lastName, dir[index].phoneNumber);
    for(i = index; i <= dirLength; i++){
        dir[i] = dir[i+1];
    }
    dirLength--;
    display();
}

//insert the record
void insert(char* name, char* phone_number){
    int index;
    char fullName[100];
    char firstName[50];
    char lastName[50];
    char tempName[100];
    strcpy(fullName,"");
    strcat(fullName, name);
    strcat(fullName, " ");
    strcat(fullName, phone_number);

    index = search(fullName);
    if(index != -1){
        printf("Unable to insert record: %s, because same record already present in directory.\n", fullName);
        return;
    }
    //spliting name and surname
    strcpy(tempName, name);
    strcpy(firstName, strtok(tempName, " "));
    strcpy(lastName, strtok(NULL, ","));

    //inserting new record
    strcpy(dir[dirLength+1].firstName, firstName);
    strcpy(dir[dirLength+1].lastName, lastName);
    strcpy(dir[dirLength+1].phoneNumber, phone_number);
    dirLength++;
    printf("Insersion Successful, Inserted Record: %s %s, %s\n", dir[dirLength].firstName, 
            dir[dirLength].lastName, dir[dirLength].phoneNumber);
    Sort_contact(0 , dirLength);
    display();
}

int main(int argc, char *argv[])
{
    if(argc == 2){ 
        int choice;
        char name[100];
        char phoneNumber[20];
        int location;
        dirLength = create(argv);   //directory created
        while(choice != 5){
            printf("\n1) sort_contact\n2) search\n3) delete\n4) insert\n5) Exit\nEnter a choice:\n");
            scanf("%d", &choice);
            switch(choice){
                case 1 :
                    if(dirLength == -1){
                        printf("Phone Directory is empty.");
                    }
                    else{
                        Sort_contact(0, dirLength);
                        display();
                    }
                    break;
                case 2 :
                    if(dirLength == -1){
                        printf("Phone Directory is empty.");
                    }
                    else{
                        printf("\nEnter the Name -> ");
                        getc(stdin);
                        scanf("%[^\n]s",name);
                        location = search(name);
                        if(location != -1){
                            printf("Search Result:- (Record found)\nIndex: %d, Name: %s, Phone Number: %s\n", 
                                (location+1), name, dir[location].phoneNumber);
                        }
                        else{
                            printf("Search Result:- Name(%s) not found.\n", name);
                        }
                    }
                    break;
                case 3 :
                    if(dirLength == -1){
                        printf("Phone Directory is empty.");
                    }
                    else{ 
                        printf("\nEnter the Name -> ");
                        getc(stdin);
                        scanf("%[^\n]s",name);
                        delete(name);
                    }
                    break;
                case 4 :
                    printf("\nEnter the Name -> ");
                    getc(stdin);
                    scanf("%[^\n]s",name); 
                    printf("\nEnter the Phone Number -> ");
                    getc(stdin);
                    scanf("%[^\n]s",phoneNumber);
                    insert(name, phoneNumber);
                    break;
                case 5 :
                    printf("\nThank You...!\n");
                    break;
                default :
                    printf("\nInvalid choice.\n");
            }
        }
    }
    else{
        printf("Only one file name is required.\n");
    }
    free(dir);
    return 0;
}
