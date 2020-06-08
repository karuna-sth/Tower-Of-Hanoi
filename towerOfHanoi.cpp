#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>

int tower[3][10];
int top[3];
int from,to;
int diskInAir;
int l,b,u;

void push(int to, int diskno){
    tower[to-1][++top[to-1]]=diskno;
}

int pop(int from){
    return(tower[from-1][top[from-1]--]);
}

void drawStill()
{
    int j,i,disk;
    cleardevice();
    for(j=1;j<=3;j++)
    {
        //drawing tower
        setfillstyle(CLOSE_DOT_FILL,WHITE);
        bar(j*l,u,j*l+5,b);
        //drawing disks on tower
        for(i=0;i<=top[j-1];i++)
        {
            disk=tower[j-1][i];
            setfillstyle(SOLID_FILL,1+disk);
			bar(j*l-15-disk*5, b-(i+1)*10, j*l+5+15+disk*5, b-i*10);
        }
    }
}

void animator(){
    int x,y,dif,sign;
    diskInAir=pop(from);
    x=from*l;
    y=b-(top[from-1]+1)*10;
    //moving disk up from the tower
    for(;y>u-20;y-=15){
        drawStill();
        setfillstyle(SOLID_FILL,1+diskInAir);
        bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
        delay(100);
    }
    y=u-20;
    dif=to*l-x;
    sign=dif/abs(dif);
    //moving disk to th next tower
    for(;abs(x-to*l)>25;x+=sign*15){
        drawStill();
        setfillstyle(SOLID_FILL,1+diskInAir);
        bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
        delay(100);
    }
    x=to*l;
    //placing disk on a target tower
    for(;y<b-(top[to-1]+1)*10;y+=15){
        drawStill();
        setfillstyle(SOLID_FILL,1+diskInAir);
        bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
        delay(100);
    }
    push(to,diskInAir);
    drawStill();
}

void moveTopN(int n, int a, int b, int c){
    if(n>=1){
        moveTopN(n-1,a,c,b);
        drawStill();
        delay(200);
        from=a;
        to=c;
        animator();
        moveTopN(n-1,b,a,c);
    }
}

void main(){
    int i,gd=DETECT,gm,n;
    printf("Enter number of disks");
    scanf("%d",&n);
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI\\");
    for(i=0;i<3;i++){
        top[i]=-1;
    }
    for(i=n;i>0;i--){
        push(1,i);
    }
    l=getmaxx()/4;
    b=getmaxy()-50;
    u=getmaxy()/3+100;
    moveTopN(n,1,2,3);
    delay(400);
    getch();
}
