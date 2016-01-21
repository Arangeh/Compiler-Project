#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>


 typedef struct token{
    char *tok;
  struct token* next;
    int li;
    int tp;
}token;

typedef struct line
{
char *ls;
struct line *next;
int parent;
} line ;

typedef struct table
{
    /*name identifier*/
    char att[200][20];
    char typ[200][20];
    char value[200][20];
}table;

FILE* result;
char ide[100][50];/*identifier in table for IR Code*/
char numb[100][50];/*Number in Table For IR Code*/
int usedid[100],usednum[100];
token *tm;
table st;
int searchtan(token *a);
int searchtai(token *a);
bool ncheck(token *a);
bool used_id(token *a);
bool used_num(token *a);
int searchtan(token *a);
int state(int a);
int inat();
int typecast(token *a,token *b,char f[10]);
int searchtaatt(token *a);
int searchtatype(token *a);
int searchtaval(token *a);
int searchta(token *a);
int lin=1;
int error=0;
int block = 0;
int cblock = 0;
void IR_code(int a,token *b);
void showtan();
void showtai();
void writetan();
void writetai();
void nahaii(token *a);
void writeta();
void trueline();
void show();
void prp();
void delinc();
void insert(token *z);
void gettoken();
void add(token *a);
void type(token *a);
int machine(void);
FILE *inc,*p;
token* start;
char key[15][20]={{" "},{"main"},{"if"},{"else"},{"while"},{"int"},{"char"},{"bool"},{"NULL"},{"void"},{"float"}};
enum type{keyword=1,identifier,operate,chr,punc,num,bol};
int main()
{
    int e=1,time=0;
    for(time=0;time<2;time++)
    {
        printf("prosecing");
        usleep(500000);
        system("cls");
        printf("prosecing.");
        usleep(500000);
        system("cls");
        printf("prosecing..");
        usleep(500000);
        system("cls");
        printf("prosecing...");
        usleep(500000);
        system("cls");
    }
    start=(token *)malloc(sizeof(token));
    start->next=NULL;
    gettoken();
    e=inat();
    if(e!=1)
    trueline();
    tm=start->next;
    machine();
    writeta();
    javab();
    writetai();
    writetan();
  //  showtable();
    result=fopen("result.txt","w+");
    if(error!=-1)
    IR_make();
    else
    printf("\nWARNING : IR CODE can't be made.There should be some problems with code\ns");
//  showtai();
// showtan();
    //show();
 // handelmain();
 // handwhile();
}

void add(token* a)
{
    if(strcmp(a->tok," ")!=0)
    {
        token *p,*temp;
        p=(token*)malloc(sizeof(token));
        p->tok=strdup(a->tok);
        type(a);
        p->li=a->li;
        p->tp=a->tp;
        p->next=NULL;
        temp=start;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=p;
    }
}
void type(token *a)
{

    int digit=0,y=0;
    char s[20];
    strcpy(s,a->tok);
    int j;
    int dot=0;
    for(j=1;j<=10;j++)
    {
    if(strcmp(key[j],s)==0)
    {
    a->tp=keyword;
    y=1;
    }
    }
    for(j=0;j<=strlen(s)-1;j++)
    {
    if(!((isdigit(s[j])) || (s[j]=='.')))
    {
    break;
    }
    if(s[j]=='.')
    {
    dot++;
    }

    }
    if((j==strlen(s)) && (dot<=1)&&(s[0]!=NULL))
    {
    a->tp=num;
    digit=1;
    }

    if(strcmpi(s,"true")==0 || strcmpi(s,"false")==0)
    {
    a->tp=bol;
    }
    if((strcmpi(s,"{")==0)||(strcmpi(s,"}")==0)||(strcmpi(s,"(")==0)||(strcmpi(s,")")==0)||(strcmp(s,";")==0)||(strcmp(s,",")==0))
    {
    a->tp=punc;
    }

    if(digit!=1)
    {
    for(j=0;j<=strlen(s)-1;j++)
    {
    if(!((isupper(s[j]))||(islower(s[j]))||(isdigit(s[j]))))
    {
    break;
    }
    }
    if(j==strlen(s) && y!=1 && strcmpi(s,"true")!=0 && strcmpi(s,"false")!=0 && strcmp(s,"max")!=0 && strcmp(s,"min")!=0)
    {
    a->tp=identifier;
    }
    }

    if((strcmpi(s,"+")==0)||(strcmpi(s,"*")==0)||
       (strcmpi(s,"/")==0)||(strcmpi(s,"-")==0)||
       (strcmpi(s,"<")==0)||(strcmpi(s,">")==0)||
       (strcmpi(s,"&&")==0)||(strcmpi(s,"||")==0)||
       (strcmpi(s,"==")==0)||(strcmpi(s,"!=")==0)||(strcmpi(s,"=")==0)||(strcmpi(s,">=")==0)||(strcmpi(s,"<=")==0))
    {
    a->tp=operate;
    }

    if((strlen(s)==3)&&(s[0]=='\'')&&(s[2]=='\''))
    {
        a->tp=chr;
    }
    return 0;
}

void gettoken()
{
    int i=1,o,j=0;
    p=fopen("input.c","r+");
    if(p==NULL)
    {
        printf("Can Not Open File");
        exit(1);
    }
    token *a;
    char str[100],b[15],c[15];
    for(o=0;o<15;o++)
        b[o]='\0';
    a=(token*)malloc(sizeof(token));
    a->next=NULL;

    while(!feof(p))
    {
        fgets(str,100,p);
       if(feof(p))
            break;
        for(j=0;j<strlen(str);j++)
            {
                if(str[j]!=' ' && str[j]!='\n' && str[j]!='\t')
                {
                        b[o]=str[j];
                        c[o]=b[o];
                        o++;
                    if(j==strlen(str)-1 && feof(p))
                    {
                        if(strcmp(a->tok," ")!=0)
                       {
                            strcpy(a->tok,b);
                            a->li=i;
                            add(a);
                        }
                    }
                }
                else
                {
                    if(strcmp(b," ")!=0 && strcmp(b,"\0")!=0)
                    {
                        strcpy(a->tok,b);
                        a->li=i;
                        add(a);
                        for(o=0;o<15;o++)
                        {b[o]=0;}
                        o=0;
                    }
                }
            }
        j=0;
        i++;
    }
}

void showtable()
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        printf("%s\t",st.att[i]);
        printf("%s\t",st.typ[i]);
        printf("%s\n",st.value[i]);
        i++;
    }
}

void show()
{
    token *p;
    p=start->next;
    while(p!=NULL)
    {
        printf("%s\t",p->tok);
        printf("%d\t",p->li);
        printf("%d\n",p->tp);
        p=p->next;
    }
}

void prp(char b[])
{
    token *p,*q;
    int i,j=0,t=0,y=0;
    char f[25];
    for(i=0;i<25;i++)
        f[i]=0;
    p=start;
    while(p!=NULL)
    {
        if(strcmp(p->tok,"#include")==0)
        {
            q=p->next;
            y=1;
            break;
        }
        if(strcmp(p->tok,"include")==0)
        {
            error=-1;
            printf("ERROR : In Line %d Your include is not completed needed '#'\n",lin);
            break;
        }
        /*if(strcmp(p->next->tok,"<")!=0)
        {
            error=-1;
            printf("ERROR : Line %d expected see \" < \" ",p->next->tok);
            break;
        }*/
        p=p->next;
    }
    if(y==1)
    {
        for(i=1;i<strlen(q->tok)-1;i++,j++)
        {
            f[j]=q->tok[i];
        }
    }
    if(y==1)
    strcpy(b,f);
    else
    strcpy(b,"empety");
}

int inat()
{
    int j,o=0;
    char f[20];
    prp(f);
    if(!strcmp(f,"empety"))
        return 1;
    inc=fopen((const char*)f,"r+");
    if(inc==NULL)
    {
        printf("Can Not Open Your include\n");
        return 1;
    }
    token *a,*temp,*m;
    m->tok="*end*";
    temp=start;
    char str[100],b[15],c[15];
    for(o=0;o<15;o++)
    b[o]=0;
    a=(token*)malloc(sizeof(token));
    a->next=NULL;
    delinc();
    while(!feof(inc))
    {
    fgets(str,100,inc);
    if(feof(inc))
        break;
    for(j=0;j<strlen(str);j++)
        {
            if(str[j]!=' ' && str[j]!='\n')
            {
            b[o]=str[j];
            c[o]=b[o];
            o++;
            }

            else
            {
                if(strcmp(b," ")!=0 && strcmp(b,"\0")!=0)
                    {
                        a->tok=strdup(b);
                        a->li=lin;
                        addafadr(a,temp);
                        temp=temp->next;
                        for(o=0;o<15;o++)
                        {b[o]=0;}
                        o=0;
                    }
            }
        }
        lin++;
        j=0;
    }
addafadr(m,temp);
    return 5;
}

void addafadr(token *c,token *e)
{
    token *p,*temp;
    p=(token*)malloc(sizeof(token));
    p->tok=strdup(c->tok);
    type(c);
    p->li=c->li;
    p->tp=c->tp;
    p->next=NULL;
    temp=e->next;
    e->next=p;
    p->next=temp;
}

void delinc()
{
    token *a,*b,*c;
    a=start->next;
    b=a->next;
    start->next=b->next;

}

void trueline()
{
    int c=0,d=0,fla=0;
    token *z,*befor,*aval;
    z=start->next;

    while(strcmpi(z->tok,"*end*")!=0)
    {
        befor=z;
        z=z->next;
    }
    aval=z->next;
    befor->next=aval;
    c=aval->li;

    while(aval!=NULL)
    {

        while(aval->li==c)
        {
            aval->li=lin;
            if(aval->next!=NULL)
            aval=aval->next;
            else
                {fla=1;
                break;
                }

        }
        if(fla==1)
            break;
        c++;
        lin++;
    }
}

void writeta()
{
    int i=0;
    int d;
    token *a;
    char r[10];
    a=start->next;
    while(a->next!=NULL)
    {
        if(strcmp(a->tok,"char")==0 || strcmp(a->tok,"float")==0 || strcmp(a->tok,"int")==0 || strcmp(a->tok,"bool")==0)
         {
            strcpy(r,a->tok);
            if(a->next==NULL && a->next->next==NULL)
            break;
            a=a->next;
            if(ncheck(a->next))
            {
                break;
            }
            while(strcmp(a->tok,";")!=0 && ( strcmp(a->tok,"=")!=0 || !strcmp(a->next->next->tok,",")!=0 ) )
            {
                if(a->tp==identifier)
                {
                    if(searchta(a)==-1 || strcmp(r,"char")==0)
                    {
                        for(d=0;d<strlen(a->tok);d++)
                        {
                            st.att[i][d]=a->tok[d];
                        }
                        for(d=0;d<strlen(r);d++)
                        {
                            st.typ[i][d]=r[d];
                        }

                        if(strcmp(a->next->tok,"=")==0)
                        {
                            {
                                if(strcmp(a->next->next->tok,"'")==0 && strcmp(r,"char")==0)
                                {
                                    for(d=0;d<strlen(a->next->next->tok);d++)
                                    st.value[i][d]=a->next->next->next->tok[d];
                                    a=a->next->next->next->next;
                                }
                                else
                                {
                                    for(d=0;d<strlen(a->next->next->tok);d++)
                                    st.value[i][d]=a->next->next->tok[d];
                                }
                            }
                        }
                    i++;
                    }
                }
                if(a->next==NULL)
                    {
                        break;
                    }
                a=a->next;
            }
         }
         if(a->next==NULL)
            break;
    a=a->next;
    }
}

int searchta(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.att[i])==0)
            {
                error=-1;
                printf("ERROR : In Line %d This identifier '%s' Used  Repeated\n",a->li,a->tok);
                return i;
            }
            i++;
    }
    i=0;
    return -1;
}

int searchtaatt(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.att[i])==0)
            {
                return i;
            }
            i++;
    }
    i=0;
    return -1;
}

int searchtatype(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.typ[i])==0)
            {
                return i;
            }
            i++;
    }
    i=0;
    return 2;
}

int searchtaval(token *a)
{
    int i=0;
    while(strcmpi(st.att[i],"\0")!=0)
    {
        if(strcmp(a->tok,st.att[i])==0 && strcmp(st.value[i],"\0")!=0)
            {
                return i;
            }
            i++;
    }
    i=0;
    return 2;
}

void nahaii(token *a)
{
    char b[10],w[10],v[10];
    token *k;
    int i,g,u,j;
    i=searchtaatt(a);

    if(i==-1)
    {
        error=-1;
        printf("ERROR : In Line %d Unknow identifier '%s' \n",a->li,a->tok);
        return;
    }

    if(a->next==NULL || a->next->next==NULL)
    {
           return ;
    }
    k=a->next->next;

    if(k->next==NULL || k->next->next==NULL)
        {
            return;
        }

    if(strcmp(k->tok,"'")==0)
    {
        strcpy(st.value[i],k->next->tok);
        return;
    }

    if(k->tp==identifier)
    {
        u=searchtaatt(k);

        if(u==-1)
        {
            error=-1;
            printf("ERROR : In Line %d Unknow identifier '%s' \n",a->li,k->tok);
            return;
        }
    }

    if(k->next->next->tp==identifier && (strcmp(k->next->tok,";")!=0 && strcmp(k->next->tok,",")!=0))
    {
        u=searchtaatt(k->next->next);

        if(u==-1)
        {
            error=-1;
            printf("ERROR : In Line %d Unknow identifier '%s' \n",a->li,k->next->next->tok);
            return;
        }
    }

    if(k->tp==num && (strcmp(k->next->tok,";")==0 || strcmp(k->next->tok,",")==0))
        {
            if(typecast(a,k,v)!=-1)
            {
                strcpy(st.value[i],k->tok);
                return ;
            }
            else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is %s BUT type of Num '%s(%s)' is different\n",a->li,a->tok,st.typ[i],k->tok,v);
                strcpy(st.value[i],"unknown");
                return;
            }
        }

    if(k->tp==identifier && (strcmp(k->next->tok,";")==0 || strcmp(k->next->tok,",")==0))
        {
            g=searchtaatt(k);

            if(strcmp(st.value[g],"\0")==0)
            {
                error=-1;
                printf("ERROR : In Line %d the value of '%s' is unknown now\n",a->li,k->tok);
                return;
            }

            if(!strcmp(st.typ[i],st.typ[g]))
            {
                strcpy(st.value[i],st.value[g]);
                return ;
            }

            else
                {
                    error=-1;
                    printf("ERROR : In Line %d type of  '%s' is %s BUT type of '%s' is '%s'\n",a->li,a->tok,st.typ[i],k->tok,st.typ[g]);
                    return ;
                }
        }


    if(k->next->next==NULL)
        {
            return;
        }

    if(k->tp==num)
       {
           if(typecast(a,k,v)!=-1)
            {
                strcpy(b,k->tok);
            }
            else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is %s BUT type of Num '%s(%s)' is different\n",a->li,a->tok,st.typ[i],k->tok,v);
                strcpy(st.value[i],"unknown");
                return;
            }

       }

    if(k->tp==identifier)
        {
            j=searchtaatt(k);

            if(strcmp(st.value[j],"\0")==0)
                {
                    error=-1;
                    printf("ERROR : In Line %d the value of '%s' is unknown now\n",a->li,k->tok);
                    return ;
                }
            if(!strcmp(st.typ[i],st.typ[j]))
                {
                    strcpy(b,st.value[j]);
                }
            else
                {
                    error=-1;
                    printf("ERROR : In Line %d type of  '%s' is '%s' BUT type of '%s' is '%s'\n",a->li,a->tok,st.typ[i],k->tok,st.typ[j]);
                    return ;
                }

        }

    if(k->next->next->tp==num)
        {
            if(typecast(a,k->next->next,v)!=-1)
            {
                strcpy(w,k->next->next->tok);
            }
            else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is %s BUT type of Num '%s(%s)' is different\n",a->li,a->tok,st.typ[i],k->next->next->tok,v);
                strcpy(st.value[i],"unknown");
                return;
            }
        }

    if(k->next->next->tp==identifier)
    {
        j=searchtaatt(k->next->next);
        if(strcmp(st.value[j],"\0")==0)
        {
            error=-1;
            printf("ERROR : In Line %d the value of '%s' is unknown now\n",a->li,k->tok);
            return;
        }
        if(!strcmp(st.typ[i],st.typ[j]))
            {
                strcpy(w,st.value[j]);
            }
        else
            {
                error=-1;
                printf("ERROR : In Line %d type of  '%s' is '%s' BUT type of '%s' is '%s'\n",a->li,a->tok,st.typ[i],k->next->next->tok,st.typ[j]);
                return ;
            }

    }

    if(strcmp(k->next->tok,"+")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        sprintf(st.value[i],"%f",atof(w)+atof(b));
        if(strcmp(st.typ[i],"int")==0)
        sprintf(st.value[i],"%d",atoi(w)+atoi(b));
        return;
    }

    if(strcmp(k->next->tok,"*")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        sprintf(st.value[i],"%f",atof(w)*atof(b));
        if(strcmp(st.typ[i],"int")==0)
        sprintf(st.value[i],"%d",atoi(w)*atoi(b));
        return;
    }

    if(strcmp(k->next->tok,"-")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        sprintf(st.value[i],"%f",atof(w)-atof(b));
        if(strcmp(st.typ[i],"int")==0)
        sprintf(st.value[i],"%d",atoi(w)-atoi(b));
        return;
    }

    if(strcmp(k->next->tok,"/")==0)
    {
        if(strcmp(st.typ[i],"float")==0)
        {
            if(strcmp(w,"0"))
            sprintf(st.value[i],"%f",atof(b)/atof(w));
            else
                {
                    error=-1;
                    printf("ERROR : In Line %d devision by zero isnot permited\n",a->li);
                    return;
                }
        }

        if(strcmp(st.typ[i],"int")==0)
        {
            if(strcmp(w,"0"))
            sprintf(st.value[i],"%d",atoi(b)/atoi(w));
            else
            {
                error=-1;
                printf("ERROR : In Line %d devision by zero isnot permited\n",a->li);
                return 0;
            }
        }
    }
}

void javab()
{
    token *t,*befor;
    t=start->next;
    while(t->next!=NULL)
    {
        befor=t;
        t=t->next;
        if(!strcmp(t->tok,"="))
            {
                nahaii(befor);
            }
    }
}

int typecast(token *a,token *b,char f[15])
{
    int i,j,fla=1;
    i=searchtaatt(a);
    if(strcmp(st.typ[i],"int")==0)
    {
        strcpy(f,"float");
        for(j=0;j<strlen(b->tok);j++)
        {
            if(b->tok[j]=='.')
            {
                fla=-1;
                break;
            }
        }
    }
    if(strcmp(st.typ[i],"float")==0)
    {
        strcpy(f,"int");
        fla=-1;
        for(j=0;j<strlen(b->tok);j++)
        {
            if(b->tok[j]=='.')
            {
                fla=1;
                break;
            }
        }
    }
    if(strcmp(st.typ[i],"bool")==0)
    {
        if(strcmpi(b->tok,"true")==0 || strcmpi(b->tok,"false")==0)
        {
         fla=1;
        }
        else
        {
            strcpy(f,"int or float");
            fla=-1;
        }
    }

    return fla;
}

int state(int a)
{
int res;
if(tm->tp==a)
{
res=1;
}else
{
res=0;
}
return res;
}

bool ncheck(token *a)
{
bool res;
if(a==NULL)
{
res=true;
}else{
res=false;
}
return res;
}

int machine (void)
{
tm=start->next;
int sg;
int flag;
int tag;
int chh;
int bhh;
STATEMACHINE:

sg=state(keyword)+state(identifier);
flag=0;
tag=0;
chh=0;

if(!ncheck(tm))
{

if(strcmp(tm->tok,";")==0)
{
tm=tm->next;
goto STATEMACHINE;
}

}



if(strcmp(tm->tok,"return")==0)
{
    if(ncheck(tm->next))
    {
        error=-1;
       goto END;
    }
    else if(strcmp(tm->next->tok,";")==0)
    {
        if(!ncheck(tm->next->next))
        {
        tm=tm->next->next;
        //printf("##");
        flag=2;
        goto END;
        }else
        {
            error=-1;
            goto END;
        }

    }else
    {
       if(!ncheck(tm))
       {
       if(tm->tp==num)
       {
       goto LABEL_IDID;
       }
       }
        error=-1;

        goto END;
    }
}
if((strcmp(tm->tok,"if")==0)||(strcmp(tm->tok,"while")==0))
{
if(ncheck(tm))
{

goto END;
}

tm=tm->next;

if (strcmp(tm->tok,"(")==0)
{

if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;

if(tm->tp==identifier)
{

    if(ncheck(tm->next))
    {
    goto END;
    }

tm=tm->next;
//switch(tm->tok)
{
if(tm->tp==operate)
{
    if(ncheck(tm->next))
    {
    goto END;
    }

tm=tm->next;

sg=state(num)+state(identifier);
if(sg==1)
{
    if(ncheck(tm->next))
    {
    goto END;
    }

tm=tm->next;
if(strcmp(tm->tok,")")==0)
{

flag=2;
tag=3;
goto END;
}else
{
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" ) \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
goto END;
}

}else
{

error=-1;
printf("ERROR : In  Line %d\nexpected to see number or identifier \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
goto END;
}

}else
{

    error=-1;
    printf("ERROR : In  Line %d\nexpected to see operator \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
goto END;
}

}

}else
{
    error=-1;
printf("ERROR : In Line %d\nexpected to see identifier \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    }
}else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ( \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    }
}

if(strcmp(tm->tok,"void")==0)
{
//void=1;

if(ncheck(tm->next))
{
goto END;
}
tm=tm->next;
if (strcmp(tm->tok,"main")==0)
    {
        if(ncheck(tm->next))
        {
        goto END;
        }

    tm=tm->next;
   if(strcmp(tm->tok,"(")==0)
   {
            if(ncheck(tm->next))
            {
            goto END;
            }

   tm=tm->next;

   if(strcmp(tm->tok,")")==0)
   {
   flag=2;
   tag=3;
   goto END;
   }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ) \"\n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    }


   }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ( \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    }

    }
}

//sg=state(num)+state(identifier);

switch(sg)
{
case 0:
{
tag=1;
if(strcmp(tm->tok,"{")==0 || strcmp(tm->tok,"}")==0)
    {
        goto LAST;
    }
error=-1;
printf("ERROR : Line %d is not completed \n",tm->li);
goto END;
break;
}

case 1 :
{

if(strcmp(tm->tok,"else")==0)
{
    if(ncheck(tm->next))
    {
        error=-1;
        goto END;
    }
    tm=tm->next;
    goto STATEMACHINE;
}
if(tm->tp==num)
{

error=-1;
printf("ERROR : In Line %d expected to see keyword with identifier or assigning\n ",tm->li);
}

if( strcmp(tm->tok,"char")==0)
{
chh=1;
}
if( strcmp(tm->tok,"bool")==0)
{
bhh=1;
}

if(tm->tp==keyword)
{
flag=1;
}

INT:

if(ncheck(tm->next))
{
    goto END;
}

tm=tm->next;

//switch(tm->tp)
{
if (tm->tp==identifier && flag==1)// id5:
{
if(ncheck(tm->next))
{
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" = \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);
}

goto END;
}

if(ncheck(tm))
{
error=-1;
goto END;
}
tm=tm->next;
//switch(tm->tp)
{
if (strcmp(tm->tok,";")==0)// case ;1:
{
flag=2;
goto END;
break;
}else if (strcmp(tm->tok,"=")==0)//case =2:
{

if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;

switch(tm->tp)
{
//bayad 5 shode bashe!
case num ://num1:
{
LABEL_IDID :
    if (bhh==1)
{
printf("ERROR : %s can not be assigned to variable of type BOOL\n",tm->tok);
error=-1;
bhh=0;
goto END;
}
if(chh==1)
{
    error=-1;
    printf("\nERROR :  Line %d :Conflicting types for char \n",tm->li);
goto END;
}
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
//switch(tm->tp)
{
if (strcmp(tm->tok,"+")==0)//case +1:
{

if(ncheck(tm->next))
{
    goto END;
}

tm=tm->next;
sg=state(2)+state(6);
switch(sg)
{
case 1 :
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//tm=";4")
    {
        flag=2;
        goto END;
    }else if (strcmp(tm->tok,",")==0)
    {
    chh=0;
    goto INT;
    }else {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
        goto END;
    }

    break;
    }

case 0:

    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see number or identifier \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
        goto END;
        break;
    }
}
break;
}else if(strcmp(tm->tok,"-")==0)//case -1:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//;4
    {
        flag=2;
        goto END;
    }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    }

    break;
    }

case 0:
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" identifier \" or \" number \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    break;
    }
}

}else if(strcmp(tm->tok,"*")==0)//case *1:
{
if(ncheck(tm->next))
{
goto END;
}
tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";4")
    {
        flag=2;
        goto END;
    }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    }
        break;
    }
case 0:
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);
}
        goto END;
        break;
    }
}
break;
}else if(strcmp(tm->tok,"/")==0)//case /1:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(2)+state(6);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}
        tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";4")
    {
        flag=2;
        goto END;
    }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    }
    break;
    }
case 0:
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);

}
        goto END;
        break;
    }
}
break;
}else if (strcmp(tm->tok,",")==0)
{
goto INT;
}else if (strcmp(tm->tok,";")==0)
{
flag=2;
goto END ;
} else
{
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
goto END;
}
}
break;
}
case identifier : //id4:
{
if (bhh==1)
{
printf("ERROR : %s can not be assigned to variable of type BOOL\n",tm->tok);
error=-1;
bhh=0;
goto END;
}

if(chh==1)
{
    error=-1;
printf("\nERROR :  Line %d :Conflicting types for char \n",tm->li);
goto END;
}


if(ncheck(tm ))
{
goto END;
}

tm=tm->next;

//switch(tm->tp)
{
if(strcmp(tm->tok,"+")==0)//case +2:
{

if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}

    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//";4")

    {
        flag=2;
        goto END;
    //final
    }else if (strcmp(tm->tok,",")==0)
    {
        goto INT;
    }else
        {
            error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
        }
    break;
    }

case 0:
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" identifier \" or \" number \" \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    break;
    }
}
break;
}else if(strcmp(tm->tok,"-")==0)//case -2:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}

    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//(tm=";4")

    {
        flag=2;
        goto END;
    }else
    {
            error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    }
    break;
    }
case 0:
    {
            error=-1;
printf("ERROR : In  Line %d\nexpected to see \" identifier \" or \" number \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    break;
    }
}
break;
}else if (strcmp(tm->tok,"*")==0)//case *2:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//;4
    {
        flag=2;
        goto END;
    }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    }
    break;
    }

case 0:
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
        goto END;
        break;
    }
}
break;
}else if(strcmp(tm->tok,"/")==0)//case /2:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);

switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";4")
    {
        flag=2;
        goto END;
    }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    }
    break;
    }

case 0:
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);
if(ncheck(tm->next))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    break;
    }
}
break;
}else if(strcmp(tm->tok,";")==0)//case ;3
{
    flag=2;
    goto END;
    break;
} else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" or operator\n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    break;
    }
}
break;
}
default:
    {
if (strcmp(tm->tok,"\'")==0)//case '1:
{
if (bhh==1)
{
printf("ERROR : %s can not be assigned to variable of type BOOL\n",tm->tok);
error=-1;
bhh=0;
goto END;
}
if(ncheck(tm->next))
{
    goto END;
}

tm=tm->next;

switch(tm->tp)
{
case identifier : //id3:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;

{
//switch(tm->tp)
{
if(strcmp(tm->tok,"\'")==0)//case '2:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;

    if (strcmp(tm->tok,";")==0)//tm==;2)
        {
            flag=2;
            goto END;
        }
        else if(strcmp(tm->tok,",")==0)
        {
            goto INT;
        }
        else
        {
            error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
        goto END;
    }
    break;
    } else
{
    error=-1;
printf("ERROR : In  Line %d\nexpected to see single quotation",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
goto END;
}

}

}
break;
}

case num :
    {

if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;

{
//switch(tm->tp)
{
if(strcmp(tm->tok,"\'")==0)//case '2:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if (strcmp(tm->tok,";")==0)//tm==;2)
        {
            flag=2;
        goto END;
        }
        else if(strcmp(tm->tok,",")==0){
        goto INT;
        }else
        {
        error=-1;
        printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" , \" \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
        goto END;
    }
        break;
    } else
{
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see single quotation\n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

goto END;
}

}

}

}

default:
{
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);
if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

goto END;
}

}

}else if(bhh==1)
{
 if (tm->tp==bol)
{
if(ncheck(tm ))
{
goto END;
}

tm=tm->next;

if(ncheck(tm))
{
 error=-1;
 goto END;
}
if(strcmp(tm->tok,";")==0)
{
bhh=0;
flag=2;
goto END;
}else
{
printf("ERROR : Line %d expected to see \" ; \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}

error=-1;
goto END;
}
}else
{
if(ncheck(tm))
   {
   error=-1;
   goto END;
   }
printf("ERROR : Line %d expected to see \" true \" or \" false \" \n  ",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
error=-1;
goto END;
}
}else
{
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see single quotation , number , or identifier",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}

goto END;
}
    }
}
}else if(strcmp(tm->tok,",")==0)
{
chh=0;
goto INT;
}else{
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" ; \" or \" = \" or \" , \" \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    }
}
}else if(strcmp(tm->tok,"=")==0 && flag==0)//case =1:
{

if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;

//switch(tm->tp)

{
if(strcmp(tm->tok,"\'")==0)//case '3:
{

if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;

if(ncheck(tm->next))
{
goto END;
}
tm=tm->next;
if(strcmp(tm->tok,"\'")==0)
{
if(ncheck(tm->next))
{
goto END;
}
tm=tm->next;
if(strcmp(tm->tok,";")==0)
{
    flag=2;
    goto END;
}else
{
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" ; \"\n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
}

}else
{
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see single quotation \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
}

}else if(tm->tp==num)//case num: //num6:
{

if(ncheck(tm->next))
{
    goto END;
}

tm=tm->next;

//switch(tm->tp)
{
if(strcmp(tm->tok,"+")==0)//case +4:
{
if(ncheck(tm->next))
{
    goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);

switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";8")

    {
    flag=2;
    goto END;
    }
    else
    {
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" ; \"\n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
        goto END;
    }
        break;
    }
case 0:
    {
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    break;
    }
}

}else if(strcmp(tm->tok,"-")==0)//case -4:
{
if(ncheck(tm->next))
{
    goto END;
}

tm=tm->next;

switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
    goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";8")
    {
        flag=2;
        goto END;
    }
    else
    {
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" ; \"  \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
        goto END;
    }
        break;
    }

case 0:
    {
    error=-1;
    printf("ERROR : In  Line %d\nexpected to see \" ; \"  \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
    break;
    }
}

break;
}else if (strcmp(tm->tok,"*")==0)//case *4:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}

    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//";8")
    {
        flag=2;
        goto END;
    }
    else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }

    break;
    }

case 0:
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier\" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    break;
    }
}

break;
}else if(strcmp(tm->tok,"/")==0)//case /4:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {

if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//";8")
    {
        flag=2;
        goto END;
    }
    else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \"  \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }

    break;
    }

case 0:
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
        goto END;
        break;
    }
}

break;
}if(strcmp(tm->tok,";")==0)
{
 flag=2;
 goto END;
    }else
    {
   printf("error\n");

   error=-1;
printf("ERROR : In  Line %d\nexpected to see operator or \" ; \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    break;
    }
}

break;
}else if(tm->tp==identifier)//case identifier ://id10:
{

if(ncheck(tm->next))
{
goto END;
}
tm=tm->next;

//switch(tm->tp)
{
    if(strcmp(tm->tok,";")==0)//case ;8:
{
    flag=2;
    goto END;
    break;
}else if(strcmp(tm->tok,"+")==0)//case +3:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {

if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";7")

    {
        flag=2;
        goto END;
    }
    else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
        goto END;
    }
        break;
    }
case 0:
    {
      error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    break;
    }
}

break;
}else if(strcmp(tm->tok,"-")==0)//case -3:

{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";7")
    {
        flag=2;
        goto END;
    }
    else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }

    break;
    }

case 0:
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    break;
    }
}
break;
}else if(strcmp(tm->tok,"*")==0)//case *3:
{
if(ncheck(tm))
{
goto END;
}
tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:
    {
if(ncheck(tm->next))
{
goto END;
}

    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";7")

    {
        flag=2;
        goto END;
    }
    else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \"  \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);
}
    goto END;
    }

    break;
    }

case 0:
    {
       error=-1;
printf("ERROR : In  Line %d\nexpected to see \" number \" or \" identifier \" \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}

        goto END;
        break;
    }
}
break;
}else if(strcmp(tm->tok,"/")==0)//case /3:
{
if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
sg=state(num)+state(identifier);
switch(sg)
{
case 1:

    {
if(ncheck(tm->next))
{
goto END;
}
    tm=tm->next;
    if(strcmp(tm->tok,";")==0)//=";7")

    {
        flag=2;
        goto END;
    }
    else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \"  \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }

    break;
    }

case 0:
    {
 error=-1;
printf("ERROR : In  Line %d\nexpected to see number or identifier \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    break;
    }
}
break;
}else
    {
     error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \" or operator \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    break;
    }
}

break;
}else if(strcmp(tm->tok,"max")==0)//case max:

{

if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
if(strcmp(tm->tok,"(")==0)
{

if(ncheck(tm->next))
{
goto END;
}

   tm=tm->next;
   if(tm->tp==num)
   {

if(ncheck(tm->next))
{
goto END;
}

   tm=tm->next;
   if(strcmp(tm->tok,",")==0)
   {

if(ncheck(tm->next))
{
goto END;
}

   tm=tm->next;
       if(tm->tp==num)
       {
if(ncheck(tm->next))
{
goto END;
}
       tm=tm->next;
           if(strcmp(tm->tok,")")==0)
           {
if(ncheck(tm->next))
{
goto END;
}

             tm=tm->next;
                 if(strcmp(tm->tok,";")==0)//=";6")
                 {
                    flag=2;
                    goto END;
                 }else
                        {
                            error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \"  \n",tm->li);

if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}
                        goto END;
                        }

           }else
            {
           error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ) \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);
}
            goto END;
            }
       }
   }else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" , \"  \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    }

   }
}else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ( \"  \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }

}else if(strcmp(tm->tok,"min")==0)//case min:
{


if(ncheck(tm->next))
{
goto END;
}

tm=tm->next;
if(strcmp(tm->tok,"(")==0)//="(")
{
if(ncheck(tm->next))
{
goto END;
}

   tm=tm->next;
   if(tm->tp==num)
   {

if(ncheck(tm->next))
{
goto END;
}

   tm=tm->next;
   if(strcmp(tm->tok,",")==0)//=",")
   {
if(ncheck(tm->next))
{
goto END;
}

   tm=tm->next;
       if(tm->tp==num)
       {

if(ncheck(tm->next))
{
goto END;
}

       tm=tm->next;
           if(strcmp(tm->tok,")")==0)//=")")
           {

if(ncheck(tm->next))
{
goto END;
}
             tm=tm->next;
                 if(strcmp(tm->tok,";")==0)//=";6")
                {
                    flag=2;
                    goto END;
                 }else
                    {
                                            error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ; \"  \n",tm->li);

                        if(ncheck(tm))
                        {
                        printf("\nBut nothing is observed\n");
                        }else
                        {
                        printf("\nBut \" %s \" is observed\n",tm->tok);

                        }

                    goto END;
                    }

           }else
            {
            error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ) \"  \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

            goto END;
            }
       }else
    {
        error=-1;
printf("ERROR : In  Line %d\nexpected to see number \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }
   }else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" , \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }

   }else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see number \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    }
}else
    {
    error=-1;
printf("ERROR : In  Line %d\nexpected to see \" ( \"  \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}
    goto END;
    }
}else  if (tm->tp==bol)
{
if(ncheck(tm ))
{
goto END;
}

tm=tm->next;

if(ncheck(tm))
{
 error=-1;
 goto END;
}
if(strcmp(tm->tok,";")==0)
{
bhh=0;
flag=2;
goto END;
}else
{
printf("ERROR : Line %d expected to see \" ; \" \n",tm->li);
if(ncheck(tm))
{
    printf("\nBut nothing is observed\n");
}else
{
    printf("\nBut \" %s \" is observed\n",tm->tok);
}

error=-1;
goto END;
}
}else
{
     error=-1;
printf("ERROR : In  Line %d\nexpected to see \" max \" , \" min \" , \" identifier \" , \" number \" or \" single quotation \" or \" TRUE \" or \" FALSE \" \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

    goto END;
    break;
    }
}

//break;
}else
{
error=-1;
printf("ERROR : In  Line %d expected to see keyword with identifier or assigning \n",tm->li);

if(ncheck(tm))
{
printf("\nBut nothing is observed\n");
}else
{
printf("\nBut \" %s \" is observed\n",tm->tok);

}

goto END;
}


}

}

}


END :

 if(flag!=2)
 {
LAST :

if(tag==1)
{
if(strcmp(tm->tok,"{")==0)
{

block++;
    if(ncheck(tm->next))
    {

        error=-1;
        printf("ERROR : In Line %d \" { \" is not terminated \n",tm->li);

        goto ENDD;
    }else{
           //printf("$");
           tm=tm->next;
           tag=0;
           goto STATEMACHINE;
            }

}else if(strcmp(tm->tok,"}")==0  )
{

block--;
 if(ncheck(tm->next))
    {
         if(block==0)
        {
        goto ENDD;
        }else{

    if(block>0)
     {
     error=-1;
printf("ERROR : In Line %d extra  \" } \" needed \n",tm->li);
     }

     if(block<0)
     {
     error=-1;
printf("ERROR : In Line %d extra  \" { \" needed \n",tm->li);
     }
            }

    }else{
           tm=tm->next;
           tag=0;
           goto STATEMACHINE;
            }
}else{
error=-1;
printf("ERROR : Line %d is not completed\n",tm->li);
}
}else {

        error=-1;
printf("ERROR : Line %d is not completed\n",tm->li);
        }
 }else
 {

if(!ncheck(tm->next))
{

{
tm=tm->next;
tag=0;
goto STATEMACHINE;

}
}

 if(!ncheck(tm->next))
     {


 if(strcmp(tm->next->tok,"{")==0 && tag==3)
         {
         block++;
         tm=tm->next;


             if(ncheck(tm->next))
             {

             error=-1;
printf("ERROR : In Line %d \" { \" is not terminated \n",tm->li);


             goto ENDD;
             }else
             {
             tm=tm->next;
             tag=0;
             goto STATEMACHINE;
             }

                 }else if(strcmp(tm->next->tok,"}")==0 && tag==3)
        {
        block--;
        tm=tm->next;

        if(ncheck(tm->next))
        {
            if(block==0)
            {
            goto ENDD;
            }else
            {

            error=-1;
printf("ERROR : In Line %d extra  \" } \" needed \n",tm->li);
            goto ENDD;
            }

                }else
                {
                tm=tm->next;
                tag=0;
                goto STATEMACHINE;

                }

        }

     }

 if(ncheck(tm->next))
 {
 //printf("##");
 goto ENDD ;

 }
 tm=tm->next;
 while(tm->next!=NULL)
 {
     if(strcmp(tm->tok,"\n")!=0)
     {
     tag=0;
     goto STATEMACHINE;
     }
 tm=tm->next;
 }

 }
int t=0;

ENDD :

    if(ncheck(tm))
    {
        return error;
    }
    while(strcmp(tm->tok,";")!=0)
    {
    if(!ncheck(tm->next))
    {
    tm=tm->next;
    }else return error;
    }
    if(strcmp(tm->tok,";")==0)
    {
        if(ncheck(tm->next))
        {
            error=-1;
            printf("ERROR : Line %d is not completed\n",tm->li);
            return error;
        }
        tm=tm->next;
        goto STATEMACHINE;
    }
//return t;
return error;
}

void writetan()
{
    token *a;
    int i=0;
    a=start->next;
    while(a->next!=NULL)
    {
        if(a->tp==num)
        {
            strcpy(numb[i],a->tok);
            i++;
        }
        a=a->next;
    }

}

int searchtan(token *a)
{
    int j=0;
    while(strcmp(numb[j],"\0")!=0)
    {
        if(strcmp(a->tok,numb[j])==0)
            return j;
        j++;
    }
    return -2;
}

void showtan()
{
    int i=0;
    while(strcmp(numb[i],"\0")!=0)
    {
     printf("%s\t%d\n",numb[i],i);
     i++;
    }
}

void writetai()
{
    token *a;
    int i=0;
    a=start->next;
    while(a->next!=NULL)
    {
        if(a->tp==identifier)
        {
            strcpy(ide[i],a->tok);
            i++;
        }
        a=a->next;
    }

}

int searchtai(token *a)
{
    int j=0;
    while(strcmp(ide[j],"\0")!=0)
    {
        if(strcmp(a->tok,ide[j])==0)
            return j;
        j++;
    }
    return -1;
}

void showtai()
{
    int i=0;
    while(strcmp(ide[i],"\0")!=0)
    {
     printf("%s\t%d\n",ide[i],i);
     i++;
    }
}

bool used_id(token *a)
{
    bool res;
int i;
i=searchtai(a);
if(usedid[i]==1)
{
res=true;
}else{
usedid[i]=1;
res=false;
}
return res;
}

bool used_num(token *a)
{
    bool res;
int i;
i=searchtan(a);
if(usednum[i]==1)
{
res=true;
}else{
usednum[i]=1;
res=false;
}
return res;

}

void IR_code(int a,token *b)
{
    if(a==num)
    {
    printf("T_%d",searchtan(b));
    }

    if(a==identifier)
    {
    printf("T%d",searchtai(b));
    }
}

void IR_make(void)
{
tm=start->next;
writetai();
writetan();
tm=start->next;
token *h,*sep,*sas;
int keep=0,sha=0;
int flap=0;
int j;
while(tm!=NULL)
   {
        LABEL_KEY:

       if(ncheck(tm))
       {
       goto IR_END;
       }

       while(strcmp(tm->tok,"\n")==0)//="\n")
       {
       if(ncheck(tm->next))
       {
       goto IR_END;
       }
       tm=tm->next;
       }
       if(ncheck(tm))
       {
       goto IR_END;
       }
      if(strcmp(tm->tok,"{")==0 || strcmp(tm->tok,"}")==0)
        {
       cblock++;
       if(cblock-keep!=2)
        {
       printf("L%d\n",cblock);
        }else
        {
        if(flap==1)
        {
        printf("GOTO L%d\n",cblock+2);
        flap=0;
        }
        if(flap==3)
        {
        sep=sas;
        while(strcmp(sep->tok,")")!=0)
           {
                if(sep->tp==num)
                {
                    if(!used_num(sep))
                    {
                        IR_code(num,sep);
                        printf(" := ");
                        printf("%s\n",sep->tok);
                    }

                }
            sep=sep->next;
           }
            printf("L%d\n IF ",cblock);
            while(strcmp(sas->tok,")")!=0)
            {
            if(sas->tp==identifier)
            {
                IR_code(identifier,sas);
            }
            if(sas->tp==num)
            {
                IR_code(num,sas);
            }
            if(sas->tp==operate && strcmp(sas->tok,"=")!=0)
            {
            printf(" %s ",sas->tok);
            }
            if(strcmp(sas->tok,"=")==0)
            {
             printf(" := ");
            }
            sas=sas->next;
            }
            flap=0;
            printf(" GOTO L%d\n",cblock-1);
        }

        }
        tm=tm->next;
        goto LABEL_KEY;
        }

    if(strcmp(tm->tok,"while")==0)
    {
        printf(" GOTO L%d\n",cblock+2);
        flap=3;
        sas=tm;
        tm=tm->next;
        keep=cblock;
        goto LABEL_KEY;
        WHILE:
        while(strcmp(tm->tok,"{")!=0)
            tm=tm->next;
        while(strcmp(tm->tok,"}")!=0)

        {
            if(tm->tp==identifier)
            {
                IR_code(identifier,tm);
            }
            if(tm->tp==num)
            {
                if(used_num(tm))
                {
                    IR_code(num,tm);
                }
                else
                {
                    printf("\t");
                 IR_code(num,tm);
                printf(" := %s \n",tm->tok);
                }
            }
            if(tm->tp==bol)
               {
                  for(j=0;j<strlen(tm->tok);j++)
                  {
                      printf("%c",toupper(tm->tok[j]));

                  }
               }
            if(tm->tp==operate && strcmp(tm->tok,"=")!=0)
            {
            printf(" %s ",tm->tok);
            }
            if(strcmp(tm->tok,"=")==0)
            {
            printf(" := ",tm->tok);
            }
            tm=tm->next;
        }

    }else if(strcmp(tm->tok,"main")==0)
        {
            printf("PROCEDURE MAIN\nBEGIN\n");
        }else if(strcmp(tm->tok,"return")==0)
        {
            printf("RETURN\nCALL MAIN\n");
        }else if(strcmp(tm->tok,"if")==0)///="if") ///tm IS "if" token THE IF CASE
        {
        h=tm;
        while(strcmp(h->next->tok,"}")!=0)///h!="}"
        {
        usleep(50000);
        h=h->next;
        if(h->tp==num)
        {
         if(!used_num(h))
         {
             IR_code(num,h);
             printf(" := %s\n",h->tok);
         }
        }
        }
        if(ncheck(h->next->next))///when if is the last part of the program
        {

        ///tm is still "if" token!
        goto ONLY_IF;
        goto IR_END;
        }
        if(strcmp(h->next->next->tok,"else")==0)///tm is still "if" token
        {
        ///tarjomeye if else
        flap=1;
        printf(" IF ");
        while(strcmp(tm->tok,")")!=0)///3 cases:id,num, and operator
        {
            if(tm->tp==identifier)
            {
            IR_code(tm->tp,tm);
            }

            if(tm->tp==num)
            {
            IR_code(tm->tp,tm);
            }

            if(tm->tp==operate)
            {
            printf(" %s ",tm->tok);
            }
            if(tm->tp==bol)
               {
                  for(j=0;j<strlen(tm->tok);j++)
                  {
                      printf("%c",toupper(tm->tok[j]));

                  }
               }
        tm=tm->next;
        }///tm=")"
        keep=cblock;

        printf(" GOTO L%d ELSE L%d\n",cblock+1,cblock+3);
        goto LABEL_KEY;

        }else
        {
       ONLY_IF:
        ///tm is "if " token
        ///tarjomeye if khales
        printf(" IF ");
        while(strcmp(tm->tok,")")!=0)//!=")")
        {
        tm=tm->next;

         if(tm->tp==identifier)
            {
            IR_code(tm->tp,tm);
            }

            if(tm->tp==num)
            {
            IR_code(tm->tp,tm);
            }

            if(tm->tp==operate)
            {
            printf(" %s ",tm->tok);
            }

        }///tm=")"
       printf(" GOTO L%d\n",cblock+1);

       }

        }else if(tm->tp==keyword && strcmp(tm->tok,"if")!=0 && strcmp(tm->tok,"else")!=0 && strcmp(tm->tok,"while")!=0
     && strcmp(tm->tok,"void")!=0 && strcmp(tm->tok,"main")!=0 )//!=if)
       {
       tm=tm->next;///tm identifier
       LABEL_ID:

           if(strcmp(tm->next->tok,"=")==0)//="=")
           {
           h=tm->next->next;///h identifier or number
           ///somthing to do with h
           ///something to do tm
           ///printf("#");
           while(strcmp(h->tok,";")!=0 && strcmp(h->tok,",")!=0)
           {
                if(h->tp==num)
                {
                    if(!used_num(h))
                    {
                        IR_code(num,h);
                        printf(" := ");
                        printf("%s\n",h->tok);
                    }

                }
            h=h->next;
           }

           IR_code(identifier,tm);
while(strcmp(tm->next->tok,";")!=0 && strcmp(tm->next->tok,",")!=0)//!=";" || tm->next!=",")
           {
           tm=tm->next;///tm="="
               if(tm->tp==operate && strcmp(tm->tok,"=")!=0)
               {
               printf(" %s ",tm->tok);
               }
               if(tm->tp==num)
               {
               IR_code(num,tm);
               }
               if(tm->tp==identifier)
               {
               IR_code(identifier,tm);
               }
               if(strcmp(tm->tok,"=")==0)
               {
               printf(" := ");
               }
               if(tm->tp==bol)
               {
                  for(j=0;j<strlen(tm->tok);j++)
                  {
                      printf("%c",toupper(tm->tok[j]));

                  }
               }
           usleep(90000);
        }
           if(strcmp(tm->next->tok,";")==0)
           {

           goto SEMICOLON;
           }
           if(strcmp(tm->next->tok,",")==0)
           {
           goto COMMA;
           }

           }else if (strcmp(tm->next->tok,";")==0)//=";")
           {
    SEMICOLON :
           printf("\n");
           tm=tm->next;///tm=;
               if(ncheck(tm->next))
               {
               goto IR_END;
               }else
               {
               tm=tm->next;
               goto LABEL_KEY ;
               }

           }else if (strcmp(tm->next->tok,",")==0)//=",")
           {
    COMMA :
               if(strcmp(tm->next->next->next->tok,"=")==0)
               {
               printf("\n");
               }
           tm=tm->next->next;
           goto LABEL_ID;
           }


       }else if (tm->tp==identifier)
       {
       goto LABEL_ID;
       }
           if(ncheck(tm))
           {
           break;
           }
tm=tm->next;
    }
        IR_END :
return;
}
