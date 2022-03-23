#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int saveflag=0;
typedef struct
{
    int Day;
    int Month;
    int Year;
} Date;
typedef struct
{
    int id;
    char last[20];
    char first[20];
    float salary;
    Date Birth;
    char address[40];
    char email[40];
    char Mobileno[11];
} Employee;


int nameValid(char *input)
{
    int i,n=strlen(input);
    for( i=0; i<n; i++)
    {
        if(((64>=input[i]) || (input[i]>=91))&&((96>=input[i])||(input[i]>=123))) return 0;
    }
    return 1;
}
float SalaryValid(int y)
{
    if(y==0);
    else if(y!=0) printf("Wrong Entry Try again\a\n");
    char input[20];
    scanf("%s",input);
    int n=strlen(input),i;
    for(i=0; i<n; i++)
        if((47>=input[i] || input[i]>=58) && input[i]!=46) return SalaryValid(++y);

    return atof(input);
}
int nuValid(int y)
{
    if(y==0);
    else if(y!=0) printf("Wrong Entry Try again\a\n");
    char input[20];
    scanf("%s",input);
    int n=strlen(input),i;
    for(i=0; i<n; i++)
        if(47>=input[i] || input[i]>=58) return nuValid(++y);

    return atoi(input);
}

char *emailvalid(int j,Employee *database)
{

    char input[40];
    scanf("%s",input);
    strcpy(database[j].email,input);
    if(!strstr(database[j].email,"__")&&!strstr(database[j].email," ")&&strstr(database[j].email,".com")&&strstr(database[j].email,"@")&&!strstr(database[j].email,"@.com")&&(database[j].email[0]!='@')) return database[j].email;
    else
    {
        printf("Wrong Entry Try again\a\n");
        return emailvalid(j,database);
    }
}

int Mobilevalid(int j,Employee *database)
{
    char input[12],i;
    strcpy(input,database[j].Mobileno);
    if((strlen(input)!=11) || (input[0]!='0')  || (input[1]!='1')) return 0;
    for(i=0; i<11; i++)
        if(47>=input[i] || input[i]>=58) return 0;
    return 1;
}

int bobvalid(int y,int z)
{
    int i;
    if(z==0);
    else
        printf("Wrong Entry Try again\n");
    char input[20];
    scanf("%s",input);
    for( i=0; i<2; i++)
        if(47<input[i] && input[i]<58)
        {
            int x=atoi(input);
            if(y==1)
            {
                if(0<x&&x<32) return x;
                else return bobvalid(1,1);
            }
            else if(y==2)
            {
                if(0<x&&x<13) return x;
                else return bobvalid(2,1);
            }
        }
        else return bobvalid(y,1);
}

void swaping(int j,Employee *database) // swapping elements
{
    Employee temp=database[j];
    database[j]=database[j+1];
    database[j+1]=temp;
}

void sortByLname(Employee *database,int *i) // sort by last name
{

    int k, j;
    for (k =0; k<(*i); k++)
        for (j =0; j<((*i)-1); j++)
            if (strcasecmp(database[j].last,database[j+1].last)==1)
                swaping(j,database);
}


void sortBySalary(Employee *database,int *i) // sort by salary
{
    int k, j;
    for (k=0; k<(*i); k++)
        for (j=0; j<((*i)-1); j++)
            if (database[j].salary<database[j+1].salary )
                swaping(j,database);

}


void sortByDOB(Employee *database,int *i) // sort by date of birth
{
    int k,j;
    for (k=0; k<(*i); k++)
    {
        for (j=0; j<((*i)-1); j++)
        {
            if (database[j].Birth.Year>database[j+1].Birth.Year)
                swaping(j,database);
            else if (database[j].Birth.Year==database[j+1].Birth.Year )
            {
                if (database[j].Birth.Month>database[j+1].Birth.Month)
                    swaping(j,database);
                else if (database[j].Birth.Month==database[j+1].Birth.Month)
                {
                    if (database[j].Birth.Day>database[j+1].Birth.Day)
                        swaping(j,database);
                }

            }
        }
    }
}


void sort(Employee *database,int *i) // sort and print employees
{
    int choice,k;
    do
    {
        printf("How do you to sort the Employees\nPress 1 for by last name\nPress 2 for by Date of Birth\npress 3 for by salary\nYour choice is: ");
        choice=nuValid(0);
        if(choice==1) sortByLname(database,i);
        else if(choice==2) sortByDOB(database,i);
        else if(choice==3) sortBySalary(database,i);
    }
    while(choice!=1 && choice!=2 && choice!=3);
    printf("FIRST NAME | LAST NAME | ID | SALARY | DATE OF BIRTH | ADDRESS   | MOBILE NUMBER | EMAIL\n");
    for(k=0; k<(*i); k++)
        printf("%-12s %-12s %-5d %-9.2f %d/%d/%-8d %-12s %-16s %s\n", database[k].first,database[k].last,database[k].id,database[k].salary,database[k].Birth.Day,database[k].Birth.Month,database[k].Birth.Year,database[k].address,database[k].Mobileno,database[k].email);
    saveflag=0;
}

void deleete(Employee *database,int *i) //delete employees function
{
    int choice,count=0;
    do
    {
        printf("1.Delete specific employee\n2.Delete all users\n");
        choice=nuValid(0);
        if(choice==1)
        {
            int j,k,flag1=0;
            char find1[20],find2[20];
            do
            {
                printf("Enter the Last name of employee\n");
                scanf("%s",find2);
            }
            while(nameValid(find2)!=1);
            do
            {
                printf("Enter the First name of employee\n");
                scanf("%s",find1);
            }
            while(nameValid(find1)!=1);
            for(k=0; k<(*i); k++)
            {
                if(((*i)==1)&&!strcasecmp(database[0].first,find1)&&!strcasecmp(database[0].last,find2))
                {
                    flag1=1;
                    count++;
                }
                for(j=0; j<(*i); j++)
                {
                    if(!strcasecmp(database[j].first,find1)&&!strcasecmp(database[j].last,find2))
                    {
                        flag1=1;
                        swaping(j,database);
                        if(j==(*i)-1) (*i)--;
                    }
                }
            }
            if(flag1==0) printf("This employee doesn't exist\n");
        }
        else if(choice==2) (*i)=0;
    }
    while(choice!=1 && choice!=2);
    saveflag=0;
}
void modify (Employee *a,int *j)
{
    int i,flag=0,id;
    char input[10];
    printf("Enter the ID of the desired employee's data you want to modify\n");
    id=nuValid(0);
    for(i=0; i<(*j); i++)
    {
        if(id==a[i].id)
        {
            flag=1;
            do
            {
                printf("Enter the modified Last name: ");
                scanf("%s",a[i].last);
            }
            while(nameValid(a[i].last)!=1);
            do
            {
                printf("Enter the modified First name: ");
                scanf("%s",a[i].first);
            }
            while(nameValid(a[i].first)!=1);
            printf("Enter the modified Salary: ");
            a[i].salary=SalaryValid(0);
            printf("Enter the modified Email: ");
            strcpy(a[i].email,emailvalid(i,a));
            strcat(a[i].email,"\n");
            do
            {
                printf("Enter the modified Mobile number: ");
                scanf("%s",a[i].Mobileno);
            }
            while(Mobilevalid(i,a)!=1);
            printf("Enter the modified Day of birth: ");
            a[i].Birth.Day=bobvalid(1,0);
            printf("Enter the modified Month of birth: ");
            a[i].Birth.Month=bobvalid(2,0);
            printf("Enter the modified Year of birth: ");
            a[i].Birth.Year=nuValid(0);
            printf("Enter the modified Address: ");
            getchar();
            gets(a[i].address);
            break;
        }
    }
    if(flag==0) printf("This ID doesn't exist\n");
    saveflag=0;

}

void Query(Employee *a,int *j)
{
    int i;
    char find1[20],find2[20];
    int flag=0;
    do
    {
        printf("Enter the Last name of the desired employee's data\n");
        scanf("%s",find1);
    }
    while(nameValid(find1)!=1);
    do
    {
        printf("Enter the First name of the desired employee's data\n");
        scanf("%s",find2);
    }
    while(nameValid(find2)!=1);
    for (i=0; i<*(j); i++)
    {
        if(!strcasecmp(find1,a[i].last)&&!strcasecmp(find2,a[i].first))
        {
            flag=1;
            printf("First name : %s\n", a[i].first);
            printf("Last name : %s\n", a[i].last);
            printf("Id : %d \n", a[i].id);
            printf("Salary : %.2f \n", a[i].salary);
            printf("Address : %s\n", a[i].address);
            printf("Email : %s \n", a[i].email);
            printf("Mobile : %s \n", a[i].Mobileno);
            printf("Date of birth: %d/%d/%d\n", a[i].Birth.Day,a[i].Birth.Month,a[i].Birth.Year);
            break;
        }
    }
    if(flag==0) printf("This user doesn't exist\n");

}

Employee Parse(char *line)
{
    char delimiter[2] = ",-";
    Employee E;
    char* token = strtok(line, delimiter);
    int i = 0;
    while(token != NULL)
    {
        if(i==0)
            E.id = atoi(token);
        if(i==1)
            strcpy(E.last, token);
        if(i==2)
            strcpy(E.first, token);
        if(i == 3)
            E.salary = atof(token);
        if(i==4)
            E.Birth.Day = atoi(token);
        if(i==5)
            E.Birth.Month = atoi(token);
        if(i==6)
            E.Birth.Year = atoi(token);
        if(i==7)
            strcpy(E.address, token);
        if(i==8)
            strcpy(E.Mobileno, token);
        if(i==9)
            strcpy(E.email, token);
        token = strtok(NULL, delimiter);
        i++;
    }

    return E;
}
void load(FILE *fp,Employee *E,int *i)
{
    int j=0;
    char line[200];
    fp =  fopen("Company.txt", "r");
    if(fp != NULL)
    {
        while(fgets(line, 200, fp) != NULL)
        {
            E[j++] = Parse(line);
        }
        if(!strstr(E[--j].email,"\n"))
            strcat(E[j].email,"\n");
        j++;
        (*i)=j;
        fclose(fp);
    }
    else printf("null");
}
void Add(Employee *a,int *i)
{
    int t;
    int flag;
    int x=(*i);
    do
    {
        flag=0;
        printf("Enter ID: ");
        int id=nuValid(0);
        for( t=0; t<x; t++)
            if(id==a[t].id)
            {
                flag=1;
                printf("This ID is already used\nTry again\n");
            }
            else a[x].id=id;
    }
    while(flag==1);
    do
    {
        printf("Enter Last name: ");
        scanf("%s",a[x].last);
    }
    while(nameValid(a[x].last)!=1);
    do
    {
        printf("Enter First name: ");
        scanf("%s",a[x].first);
    }
    while(nameValid(a[x].first)!=1);
    printf("Enter Salary: ");
    a[x].salary=SalaryValid(0);
    printf("Enter Email: ");
    strcpy(a[x].email,emailvalid(x,a));
    strcat(a[x].email,"\n");
    do
    {
        printf("Enter Mobile number: ");
        scanf("%s",a[x].Mobileno);
    }
    while(Mobilevalid(x,a)!=1);
    printf("Enter Day of birth: ");
    a[x].Birth.Day=bobvalid(1,0);
    printf("Enter Month of birth: ");
    a[x].Birth.Month=bobvalid(2,0);
    printf("Enter Year of birth: ");
    a[x].Birth.Year=nuValid(0);
    printf("Enter Address: ");
    getchar();
    gets(a[x].address);
    (*i)++;
    saveflag=0;
}
void Save(FILE *np,Employee *E,int *i)
{
    int k=*i,j;
    printf("%d",k);
    np = fopen("Company.txt","w");
    for(j=0; j<k; j++)
    {
        fprintf(np,"%d,%s,%s,%.2f,%d-%d-%d,%s,%s,%s",E[j].id,E[j].last,E[j].first,E[j].salary,E[j].Birth.Day,E[j].Birth.Month,E[j].Birth.Year,E[j].address,E[j].Mobileno,E[j].email);

    }
    fclose(np);
    saveflag=1;
}

int Quit(FILE *np,Employee *E,int *i)
{
    int choice;
    if(saveflag==1) return 0;
    else if(saveflag==0)
        do
        {
            printf("Are you sure you to quit without saving?\n1.Save then quit\n2.yes\n");
            choice=nuValid(0);
            if(choice==1)
            {
                Save(np,E,i);
                return 0;
            }
            else if(choice==2) return 0;
        }
        while(choice!=1 && choice!=2);

}

int main()
{
    Employee database[100];
    FILE* np;
    int x=0,choice,*i=&x;
    load(np,database,i);
    while(1)
    {
        printf("\t\t\t\tMAIN MENU\n");
        printf("1.Query\n2.Add\n3.Delete\n4.Modify\n5.Print(sort)\n6.Save\n7.Quit\nYour Choice is:");
        choice=nuValid(0);
        if(choice==1) Query(database,i);
        else if(choice==2) Add(database,i);
        else if(choice==3) deleete(database,i);
        else if(choice==4) modify(database,i);
        else if(choice==5) sort(database,i);
        else if(choice==6) Save(np,database,i);
        else if(choice==7) return Quit(np,database,i);
    }
}
