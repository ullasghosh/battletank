#include<iostream>
#include<fstream>
#include<conio.h>
#include<ctime>
#define firet 1
#define tankt 30
#define enemyt 300
using namespace std;

char s[121][121];
int first=0,fireorient=0,firecord[3],tankorient,tankcordx[8],tankcordy[8],w,h,val[121][121],xstart,ystart,level,countdot=0,useddot,dot[30000][3]={};
int enemycordxy[10000][3],botdir,nextenemypoint[3],valdist[121][121];

void left(int,int);
void right(int,int);
void up(int,int);
void down(int,int);
inline void initial(int,int);
inline void orienttank(int,int,int);
void getmaze();
inline void movetank(char);
inline void fire(void);
inline void enemycord(int);
void bringenemy(int);
inline void enemyapproachtank(int);
inline void getroute(int,int,int,int);

void left(int x, int y)
{
if(y-1>=0 && valdist[x][y-1]>=0)
{
          if(valdist[x][y-1]==0)
          {
                            valdist[x][y-1]=valdist[x][y]+1;
                            up(x,y-1);
                            down(x,y-1);
                            left(x,y-1);
              }
          else if(valdist[x][y]+1>=valdist[x][y-1])
                                         return;
          else
          {
              valdist[x][y-1]=valdist[x][y]+1;
              up(x,y-1);
              down(x,y-1);
              left(x,y-1);
              }
}
else
return;
}

void right(int x, int y)
{
if(y+1<w && valdist[x][y+1]>=0)
{
          if(valdist[x][y+1]==0)
          {
                            valdist[x][y+1]=valdist[x][y]+1;
                            up(x,y+1);
                            down(x,y+1);
                            right(x,y+1);
              }
          else if(valdist[x][y]+1>=valdist[x][y+1])
                                         return;
          else
          {
              valdist[x][y+1]=valdist[x][y]+1;
              up(x,y+1);
              down(x,y+1);
              right(x,y+1);
              }
}
else
return;
}

void up(int x, int y)
{
if(x-1>=0 && valdist[x-1][y]>=0)
{
          if(valdist[x-1][y]==0)
          {
                            valdist[x-1][y]=valdist[x][y]+1;
                            up(x-1,y);
                            right(x-1,y);
                            left(x-1,y);
              }
          else if(valdist[x][y]+1>=valdist[x-1][y])
                                         return;
          else
          {
              valdist[x-1][y]=valdist[x][y]+1;
              up(x-1,y);
              right(x-1,y);
              left(x-1,y);
              }
}
else
return;
}

void down(int x, int y)
{
if(x+1<h && valdist[x+1][y]>=0)
{
          if(valdist[x+1][y]==0)
          {
                            valdist[x+1][y]=valdist[x][y]+1;
                            down(x+1,y);
                            right(x+1,y);
                            left(x+1,y);
              }
          else if(valdist[x][y]+1>=valdist[x+1][y])
                                         return;
          else
          {
              valdist[x+1][y]=valdist[x][y]+1;
              down(x+1,y);
              right(x+1,y);
              left(x+1,y);
              }
}
else
return;
}

void initial(int x, int y)
{
            up(x,y);
            valdist[x][y]=0;
            down(x,y);
            valdist[x][y]=0;
            right(x,y);
            valdist[x][y]=0;
            left(x,y);
            valdist[x][y]=0;
}

void getmaze()
{
     int i,j;
     ifstream fin;
     fin.open("tank_txt.txt");
     fin>>w;
     fin>>h;
     char empty[101];
     fin.getline(empty,w+1);
     for(i=0;i<h;i++)
     fin.getline(s[i],w+1);
     fin.close();
    for(i=0;i<h;i++)
    for(j=0;j<w;j++)
    {
                    if(s[i][j]=='X')
                    {
                                    val[i][j]=-1;
                                    valdist[i][j]=-999999;
                    }
                    if(s[i][j]=='.' || s[i][j]==' ')
                    {

                                    val[i][j]=0;
                                    countdot++;
                                    valdist[i][j]=0;
                                    dot[countdot][1]=i;
                                    dot[countdot][2]=j;
                    }

                    if(s[i][j]=='S')
                    {
                                    val[i][j]=0;
                                    valdist[i][j]=0;
                                    xstart=i;
                                    ystart=j;
                    }
    }
    for(i=0;i<h+1;i++)
    cout<<s[i]<<endl;
}

void orienttank(int i,int j,int orient)
{
    switch(orient)
    {
    case 72:
        tankorient=1;
        if(i-1==0)
        {
            s[i-1][j-1]='.';
            s[i-1][j+1]='.';
        }
        else if(j-1==0)
            s[i-1][j-1]='.';
        else if(j+1==w-1)
            s[i-1][j+1]='.';
        else
        {
            s[i-1][j-1]=' ';
            s[i-1][j+1]=' ';
        }
        tankcordx[1]=i;
        tankcordy[1]=j;
        s[tankcordx[1]][tankcordy[1]]='X';
        tankcordx[2]=i-1;
        tankcordy[2]=j;
        s[tankcordx[2]][tankcordy[2]]='|';
        tankcordx[3]=i;
        tankcordy[3]=j-1;
        s[tankcordx[3]][tankcordy[3]]='O';
        tankcordx[4]=i;
        tankcordy[4]=j+1;
        s[tankcordx[4]][tankcordy[4]]='O';
        tankcordx[5]=i+1;
        tankcordy[5]=j-1;
        s[tankcordx[5]][tankcordy[5]]='O';
        tankcordx[6]=i+1;
        tankcordy[6]=j;
        s[tankcordx[6]][tankcordy[6]]='^';
        tankcordx[7]=i+1;
        tankcordy[7]=j+1;
        s[tankcordx[7]][tankcordy[7]]='O';
        break;
    case 77:
        tankorient=2;
        if(i-1==0 || j+1==w-1)
            s[i-1][j+1]='.';
        else
            s[i-1][j+1]=' ';
        if(i+1==h-1 || j+1==w-1)
            s[i+1][j+1]='.';
        else
            s[i+1][j+1]=' ';
        tankcordx[1]=i;
        tankcordy[1]=j;
        s[tankcordx[1]][tankcordy[1]]='X';
        tankcordx[2]=i;
        tankcordy[2]=j+1;
        s[tankcordx[2]][tankcordy[2]]='-';
        tankcordx[3]=i-1;
        tankcordy[3]=j;
        s[tankcordx[3]][tankcordy[3]]='O';
        tankcordx[4]=i+1;
        tankcordy[4]=j;
        s[tankcordx[4]][tankcordy[4]]='O';
        tankcordx[5]=i-1;
        tankcordy[5]=j-1;
        s[tankcordx[5]][tankcordy[5]]='O';
        tankcordx[6]=i;
        tankcordy[6]=j-1;
        s[tankcordx[6]][tankcordy[6]]='>';
        tankcordx[7]=i+1;
        tankcordy[7]=j-1;
        s[tankcordx[7]][tankcordy[7]]='O';
        break;
    case 80:
        tankorient=3;
        if(i+1==h-1)
        {
            s[i+1][j-1]='.';
            s[i+1][j+1]='.';
        }
        else if(j-1==0)
            s[i+1][j-1]='.';
        else if(j+1==w-1)
            s[i+1][j+1]='.';
        else
        {
            s[i+1][j-1]=' ';
            s[i+1][j+1]=' ';
        }
        tankcordx[1]=i;
        tankcordy[1]=j;
        s[tankcordx[1]][tankcordy[1]]='X';
        tankcordx[2]=i+1;
        tankcordy[2]=j;
        s[tankcordx[2]][tankcordy[2]]='|';
        tankcordx[3]=i;
        tankcordy[3]=j+1;
        s[tankcordx[3]][tankcordy[3]]='O';
        tankcordx[4]=i;
        tankcordy[4]=j-1;
        s[tankcordx[4]][tankcordy[4]]='O';
        tankcordx[5]=i-1;
        tankcordy[5]=j+1;
        s[tankcordx[5]][tankcordy[5]]='O';
        tankcordx[6]=i-1;
        tankcordy[6]=j;
        s[tankcordx[6]][tankcordy[6]]='V';
        tankcordx[7]=i-1;
        tankcordy[7]=j-1;
        s[tankcordx[7]][tankcordy[7]]='O';
        break;
    case 75:
        tankorient=4;
        if(i-1==0 || j-1==0)
            s[i-1][j-1]='.';
        else
            s[i-1][j-1]=' ';
        if(i+1==h-1 || j-1==0)
            s[i+1][j-1]='.';
        else
            s[i+1][j-1]=' ';
        tankcordx[1]=i;
        tankcordy[1]=j;
        s[tankcordx[1]][tankcordy[1]]='X';
        tankcordx[2]=i;
        tankcordy[2]=j-1;
        s[tankcordx[2]][tankcordy[2]]='-';
        tankcordx[3]=i+1;
        tankcordy[3]=j;
        s[tankcordx[3]][tankcordy[3]]='O';
        tankcordx[4]=i-1;
        tankcordy[4]=j;
        s[tankcordx[4]][tankcordy[4]]='O';
        tankcordx[5]=i+1;
        tankcordy[5]=j+1;
        s[tankcordx[5]][tankcordy[5]]='O';
        tankcordx[6]=i;
        tankcordy[6]=j+1;
        s[tankcordx[6]][tankcordy[6]]='<';
        tankcordx[7]=i-1;
        tankcordy[7]=j+1;
        s[tankcordx[7]][tankcordy[7]]='O';
        break;
    }
}

void movetank(char c)
{
    int flag,xpos,ypos,i,j;
    flag=0;
    xpos=tankcordx[1];
    ypos=tankcordy[1];
    i=tankcordx[1];
    j=tankcordy[1];
    if(c==72)
    {
        xpos=xpos-1;
        if(val[xpos-1][ypos+1]!=0 || val[xpos-1][ypos-1]!=0 || val[xpos-1][ypos]!=0 || (xpos-1)<0)
            xpos++;
        else
        {
            flag=1;
            if(i+1==h-1 || j-1==0)
                s[i+1][j-1]='.';
            else
                s[i+1][j-1]=' ';
            if(i+1==h-1)
                s[i+1][j]='.';
            else
                s[i+1][j]=' ';
            if(i+1==h-1 || j+1==w-1)
                s[i+1][j+1]='.';
            else
                s[i+1][j+1]=' ';

        }
    }
    if(c==77)
    {
        ypos=ypos+1;
        if(val[xpos+1][ypos+1]!=0 || val[xpos-1][ypos+1]!=0 || val[xpos][ypos+1]!=0 || (ypos+1)>=w)
            ypos--;
        else
        {
            flag=1;
            if(j-1==0 || i-1==0)
                s[i-1][j-1]='.';
            else
                s[i-1][j-1]=' ';
            if(j-1==0)
                s[i][j-1]='.';
            else
                s[i][j-1]=' ';
            if(i+1==h-1 || j-1==0)
                s[i+1][j-1]='.';
            else
                s[i+1][j-1]=' ';
        }
    }
    if(c==80)
    {
        xpos=xpos+1;
        if(val[xpos+1][ypos+1]!=0 || val[xpos+1][ypos-1]!=0 || val[xpos+1][ypos]!=0 || (xpos+1)>=h)
            xpos--;
        else
        {
            flag=1;
            if(i-1==0 || j-1==0)
                s[i-1][j-1]='.';
            else
                s[i-1][j-1]=' ';
            if(i-1==0)
                s[i-1][j]='.';
            else
                s[i-1][j]=' ';
            if(i-1==0 || j+1==w-1)
                s[i-1][j+1]='.';
            else
                s[i-1][j+1]=' ';
        }
    }
    if(c==75)
    {
        ypos=ypos-1;
        if(val[xpos+1][ypos-1]!=0 || val[xpos-1][ypos-1]!=0 || val[xpos][ypos-1]!=0 || (ypos-1)<0)
            ypos++;
        else
        {
            flag=1;
            if(i-1==0 || j+1==w-1)
                s[i-1][j+1]='.';
            else
                s[i-1][j+1]=' ';
            if(j+1==w-1)
                s[i][j+1]='.';
            else
                s[i][j+1]=' ';
            if(i+1==h-1 || j+1==w-1)
                s[i+1][j+1]='.';
            else
                s[i+1][j+1]=' ';
        }
    }
    if(flag==1)
        orienttank(xpos,ypos,(int) c);      ///this fuctn changes tankcord x & y
    return;
}

void fire(void)
{
    int i;
    switch (fireorient)
    {
        case 1:
            if(firecord[1]-1>=0 && val[firecord[1]-1][firecord[2]]>=0)      ///feasible next fire cord & no enemy/X there
            {
            s[firecord[1]-1][firecord[2]]='o';
            if(first==1)                ///if not a first shot cord
            s[firecord[1]][firecord[2]]=' ';
            first=1;
            firecord[1]=firecord[1]-1;
            }
            else            ///either next cord out of boundary or enemy/X present
            {
                if(firecord[1]-1>=0 && val[firecord[1]-1][firecord[2]]<0)       ///next cord feasible but enemy/X there
                {
                    if(s[firecord[1]-1][firecord[2]]=='@')
                       {
                           for(i=1;i<=level;i++)
                            if(enemycordxy[i][1]==(firecord[1]-1) && enemycordxy[i][2]==firecord[2])
                                break;
                            enemycordxy[i][1]=enemycordxy[level][1];
                            enemycordxy[i][2]=enemycordxy[level][2];
                            level--;
                            cout<<"\a";
                       }
                       if(firecord[1]-1==0)
                            s[firecord[1]-1][firecord[2]]='.';
                        else
                            s[firecord[1]-1][firecord[2]]=' ';
                       val[firecord[1]-1][firecord[2]]=0;
                       valdist[firecord[1]-1][firecord[2]]=0;
                }
                if(first==1)            ///if not a first shot cord
                {
                    if(firecord[1]==0)
                        s[firecord[1]][firecord[2]]='.';
                    else
                        s[firecord[1]][firecord[2]]=' ';
                }
                first=0;
                return;
            }
            break;
        case 2:
            if(firecord[2]+1<w && val[firecord[1]][firecord[2]+1]>=0)           ///feasible next fire cord & no enemy/X there
            {
            s[firecord[1]][firecord[2]+1]='o';
            if(first==1)
                s[firecord[1]][firecord[2]]=' ';
            first=1;
            firecord[2]+=1;
            }
            else            ///either next cord out of boundary or enemy/X present
            {
                if(firecord[2]+1<w && val[firecord[1]][firecord[2]+1]<0)       ///next cord feasible but enemy/X there
                {
                    if(s[firecord[1]][firecord[2]+1]=='@')
                       {
                           for(i=1;i<=level;i++)
                            if(enemycordxy[i][1]==firecord[1] && enemycordxy[i][2]==(firecord[2]+1))
                                break;
                            enemycordxy[i][1]=enemycordxy[level][1];
                            enemycordxy[i][2]=enemycordxy[level][2];
                            level--;
                            cout<<"\a";
                       }
                       if(firecord[2]+1==w-1)
                            s[firecord[1]][firecord[2]+1]='.';
                        else
                            s[firecord[1]][firecord[2]+1]=' ';
                    val[firecord[1]][firecord[2]+1]=0;
                    valdist[firecord[1]][firecord[2]+1]=0;
                }
                if(first==1)
                {
                    if(firecord[2]==w-1)
                        s[firecord[1]][firecord[2]]='.';
                    else
                        s[firecord[1]][firecord[2]]=' ';
                }
                first=0;
                return;
            }
            break;
        case 3:
            if(firecord[1]+1<h && val[firecord[1]+1][firecord[2]]>=0)
            {
            s[firecord[1]+1][firecord[2]]='o';
            if(first==1)
                s[firecord[1]][firecord[2]]=' ';
            first=1;
            firecord[1]+=1;
            }
            else
            {
                if(firecord[1]+1<h && val[firecord[1]+1][firecord[2]]<0)
                {
                    if(s[firecord[1]+1][firecord[2]]=='@')
                       {
                           for(i=1;i<=level;i++)
                            if(enemycordxy[i][1]==firecord[1]+1 && enemycordxy[i][2]==firecord[2])
                                break;
                            enemycordxy[i][1]=enemycordxy[level][1];
                            enemycordxy[i][2]=enemycordxy[level][2];
                            level--;
                            cout<<"\a";
                       }
                val[firecord[1]+1][firecord[2]]=0;
                valdist[firecord[1]+1][firecord[2]]=0;
                if(firecord[1]+1==h-1)
                    s[firecord[1]+1][firecord[2]]='.';
                else
                    s[firecord[1]+1][firecord[2]]=' ';
                }
                if(first==1)
                {
                    if(firecord[1]==h-1)
                        s[firecord[1]][firecord[2]]='.';
                    else
                        s[firecord[1]][firecord[2]]=' ';
                }
                first=0;
                return;
            }
            break;
        case 4:
            if(firecord[2]-1>=0 && val[firecord[1]][firecord[2]-1]>=0)
            {
            s[firecord[1]][firecord[2]-1]='o';
            if(first==1)
                s[firecord[1]][firecord[2]]=' ';
            first=1;
            firecord[2]-=1;
            }
            else
            {
                if(firecord[2]-1>=0 && val[firecord[1]][firecord[2]-1]<0)
                {
                    if(s[firecord[1]][firecord[2]-1]=='@')
                       {
                           for(i=1;i<=level;i++)
                            if(enemycordxy[i][1]==firecord[1] && enemycordxy[i][2]==firecord[2]-1)
                                break;
                            enemycordxy[i][1]=enemycordxy[level][1];
                            enemycordxy[i][2]=enemycordxy[level][2];
                            level--;
                            cout<<"\a";
                       }
                       if(firecord[2]-1==0)
                            s[firecord[1]][firecord[2]-1]='.';
                        else
                            s[firecord[1]][firecord[2]-1]=' ';
                    val[firecord[1]][firecord[2]-1]=0;
                    valdist[firecord[1]][firecord[2]-1]=0;
                }
                if(first==1)
                {
                    if(firecord[2]==0)
                        s[firecord[1]][firecord[2]]='.';
                    else
                        s[firecord[1]][firecord[2]]=' ';
                }
                first=0;
                return;
            }
            break;
    }
}

void enemycord(int k)       ///generates enemy's starting point, used by bringenemy
{
int rnum,i,j,dist,l,m,n;
srand (k*time(NULL));
rnum=rand()%useddot+1;
i=dot[rnum][1];
j=dot[rnum][2];

DOIT:
for(n=1;n<=k-1;n++)
        if(enemycordxy[n][1]==i && enemycordxy[n][2]==j)
        {
            srand (k*(i+1)*n*time(NULL));
            rnum=rand()%useddot+1;
            i=dot[rnum][1];
            j=dot[rnum][2];
            goto DOIT;
        }

    enemycordxy[k][1]=i;
    enemycordxy[k][2]=j;
    initial(enemycordxy[k][1],enemycordxy[k][2]);
    dist=valdist[tankcordx[1]][tankcordy[1]];
    for(l=0;l<h;l++)
    for(m=0;m<w;m++)
    if(valdist[l][m]>=0)
    valdist[l][m]=0;
    if(dist>10)
    {
        dot[rnum][1]=dot[useddot][1];
        dot[rnum][2]=dot[useddot][2];
        useddot--;
        return;
    }
    else
    {
        dot[rnum][1]=dot[useddot][1];
        dot[rnum][2]=dot[useddot][2];
        useddot--;
        enemycord(k);
    }
}

void bringenemy(int k)
{
int i,j;
enemycord(k);
i=enemycordxy[k][1];
j=enemycordxy[k][2];
s[i][j]='@';
val[i][j]=-1;
}

void enemyapproachtank(int k)
{
    int i,j,l;
    initial(enemycordxy[k][1],enemycordxy[k][2]);
    getroute(enemycordxy[k][1],enemycordxy[k][2],tankcordx[1],tankcordy[1]);
    if(s[nextenemypoint[1]][nextenemypoint[2]]=='@')
    {
         for(i=0;i<h;i++)
         for(j=0;j<w;j++)
            if(valdist[i][j]>=0)
                valdist[i][j]=0;
        return;
    }
    if(enemycordxy[k][1]==0 || enemycordxy[k][1]==h-1 || enemycordxy[k][2]==0 || enemycordxy[k][2]==w-1)
        s[enemycordxy[k][1]][enemycordxy[k][2]]='.';
    else
        s[enemycordxy[k][1]][enemycordxy[k][2]]=' ';
    val[enemycordxy[k][1]][enemycordxy[k][2]]=0;
    enemycordxy[k][1]=nextenemypoint[1];
    enemycordxy[k][2]=nextenemypoint[2];
    s[enemycordxy[k][1]][enemycordxy[k][2]]='@';
    val[enemycordxy[k][1]][enemycordxy[k][2]]=-1;
    for(i=0;i<h;i++)
    for(j=0;j<w;j++)
        if(valdist[i][j]>=0)
            valdist[i][j]=0;
}

void getroute(int x1,int y1,int x2, int y2)
{
    int dist,k;
     dist=valdist[x2][y2];
     for(k=1;k<dist;k++)
    {
                    if(valdist[x2-1][y2]==dist-k)
                    x2=x2-1;
                    else if(valdist[x2+1][y2]==dist-k)
                    x2=x2+1;
                    else if(valdist[x2][y2-1]==dist-k)
                    y2=y2-1;
                    else if(valdist[x2][y2+1]==dist-k)
                    y2=y2+1;
    }
    if((x2==x1-1 && y2==y1) || (x2==x1 && y2==y1+1) || (x2==x1+1 && y2==y1) || (x2==x1 && y2==y1-1))
    {
        nextenemypoint[2]=y2;
        nextenemypoint[1]=x2;
    }
    else
    {
        nextenemypoint[2]=y1;
        nextenemypoint[1]=x1;
    }
}

int main()
{
system("mode 650");
RESTART:
first=0;
fireorient=0;
countdot=0;
int i,score=1,j,k,count=1,tough=1,count2=1,tough2=10;
long double t_fire,t_tank,t_enemy;
char c,f;
getmaze();
cout<<"\nObjective: Kill all the zombies' '@'\nYou will start from 'S'\nDirection control by arrow keys and fire by space\n";
level=-1;
while(level<0)
{
cout<<"Enter number of zombies: ";
cin>>level;
if(level>10)
    {
        cout<<"Enter less than 11 zombies\n";
        level=-1;
    }
else if(level<1)
{
        cout<<"Enter positive number of zombie   \n";
        level=-1;
}
}

cout<<"\nTo play press any direction key";
while(c!=72 && c!=75 && c!=77 && c!=80)
c=_getch();

useddot=countdot;
orienttank(xstart,ystart,72);

for(i=1;i<=level;i++)
{
    bringenemy(i);
    system("cls");
    cout<<"Loading   "<<i*100/level<<"%";
}
system("cls");
for(i=0;i<h+1;i++)
        cout<<s[i]<<endl;
t_fire=clock();
t_tank=t_fire;
t_enemy=t_fire;
while(score>0)
{
if(level==0)
    {
        score=-2;
        break;
    }

    if(first==1)
    {
        if(clock()-t_fire>=firet)
        {
            t_fire=clock();
            fire();
        }
        system("cls");
        for(i=0;i<h+1;i++)
            puts(s[i]);
    }

    if(clock()-t_tank>=tankt)
    {
        t_tank=clock();
        if(kbhit())
        c=_getch();
        if(c==' ' && first==0)
        {
            firecord[1]=tankcordx[2];
            firecord[2]=tankcordy[2];
            fireorient=tankorient;
            fire();
            c='a';
        }
        if(c==72 || c==75 ||c==80 || c==77)
        {
            orienttank(tankcordx[1],tankcordy[1],(int)c);
            movetank(c);
            for(i=1;i<=level;i++)
                for(j=1;j<=7;j++)
                    if(tankcordx[j]==enemycordxy[i][1] && tankcordy[j]==enemycordxy[i][2])
                    {
                        s[enemycordxy[i][1]][enemycordxy[i][2]]='@';
                        score=-1;
                        break;
                    }
            system("cls");
            for(i=0;i<h+1;i++)
                puts(s[i]);
        }
        c='a';
    }

if(clock()-t_enemy>=enemyt)
{
    t_enemy=clock();
    count2=2;
    for(i=1;i<=level;i++)
    {
        enemyapproachtank(i);
                for(j=1;j<=7;j++)
                    if(tankcordx[j]==enemycordxy[i][1] && tankcordy[j]==enemycordxy[i][2])
                    {
                        score=-1;
                        break;
                    }
    }
    system("cls");
    for(i=0;i<h+1;i++)
        puts(s[i]);
}

}
if(score==-2)
    cout<<"\nYou won!";
    else
    cout<<"\nYou lose!";
cout<<"\nTo play again press 'r', to quit press 'q', press 'c' for credit";
AGAIN:
while(c!='r' && c!='q' && c!='c')
c=_getch();
if(c=='r')
{
    system("cls");
    goto RESTART;
}
if(c=='c')
{
    system("cls");
    cout<<"\n\nDeveloped by Ullas\n\n\n";
    cout<<"\nTo play again press 'r', to quit press 'q'";
    c='z';
    goto AGAIN;
}
}
