//动态优先数
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<conio.h> //通过控制台进行数据输入和数据输出
typedef struct pcb{
    char pname[10]; //进程名
    char state;     //进程状态 W(Wait)代表就绪 R(Run)代表运行 F(Finish)代表完成
    int priority;   //进程优先级 此处以优先数大为优先级高
    int runTime;    //进程还需运行的时间片
    int useTime;    //进程已用CPU时间
    struct pcb* next;
}PCB;
typedef struct func{
    char finish[10];//已完成的进程
};
int num; //进程数
PCB readyHead; //头结点，不存储进程
PCB *readyEnd; //尾节点指针
int i=0;
struct func A[10];

void createProcess();     //创建进程，分配空间以及输入各进程数据
void sortProcess();       //初始化进程
void printProcessInfo();  //输出当前进程信息
void printProcessLink();  //显示当前进程调度顺序
void runProcess();        //进程运行
void finishProcess(struct func* A);     //显示已完成的进程

int main()
{
    printf("****************************************\n");
    printf("*******实验一  动态优先数调度算法*******\n");
    printf("****************************************\n\n");
    createProcess();
    if(readyHead.next==NULL)
        return false;
    while(readyHead.next!=NULL)
        {
            sortProcess();
            printProcessInfo();
            printProcessLink();
            runProcess();
        }
    printf("至此，已无需排序与等待。\n");
    return 0;
}
void createProcess()
{
    PCB *p,*prior;
    printf("你想要运行的进程数量：");
    scanf("%d",&num);
    printf("\n");
    p=(PCB*)malloc(sizeof(PCB));
    prior=&readyHead;
    prior->next=p;
    for(int k=0;k<num;k++)
        {
            printf("输入第%d个进程的进程名：",k+1);
            scanf("%s",p->pname);
            printf("输入该进程的优先级：");
            scanf("%d",&(p->priority));
            printf("输入该进程的运行时间：");
            scanf("%d",&(p->runTime));
            p->useTime=0;
            printf("\n");
            p->state='W';
            p->next=(PCB*)malloc(sizeof(PCB));
            prior=p;
            p=p->next;
        }
    free(p);
    p=NULL;
    prior->next=NULL;
    readyEnd=prior;
    printf("\n");
}
void sortProcess()
{
    char name[10];
    int i,j,priorityNum,timeNum,useTimeNum;
    PCB *p,*rear;
    for(p=readyHead.next;p!=NULL;p=p->next)
        for(rear=p->next;rear!=NULL;rear=rear->next)
            if(p->priority<rear->priority)
                {
                    strcpy(name,p->pname);
                    priorityNum=p->priority;
                    timeNum=p->runTime;
                    useTimeNum=p->useTime;
                    strcpy(p->pname,rear->pname);
                    p->priority=rear->priority;
                    p->runTime=rear->runTime;
                    p->useTime=rear->useTime;
                    strcpy(rear->pname,name);
                    rear->priority=priorityNum;
                    rear->runTime=timeNum;
                    rear->useTime=useTimeNum;
                }
}
void printProcessInfo()
{
    PCB *p=readyHead.next;
    printf("运行前的进程信息:\n");
    printf("=================================================================\n");
    printf("进程名      优先级 运行时间   已用CPU时间  状态    下一个进程\n");
    printf("=================================================================\n");
    while(p!=NULL)
        {
            printf("  %-11s %-8d %-8d %-8d   %-8s    %-10s\n",p->pname,p->priority,p->runTime,p->useTime,(p->state=='W')?"Wait":"Finish",p->next->pname);
            p=p->next;
        }
}
void printProcessLink()
{
    PCB *p=readyHead.next;
    printf("当前进程调度顺序:\n");
    while(p!=NULL)
        {
            printf("%s",p->pname);
            p=p->next;
            if(p!=NULL)
                printf("->");
        }
    printf("\n");
}
void runProcess()
{
    PCB *p=readyHead.next;
    printf("当前运行的进程为:\n");
    printf("%s\n",p->pname);
    p->priority--;
    p->runTime--;
    p->useTime++;
    readyHead.next=p->next;
    if(p->runTime==0)
        {
            p->state='F';
            printf("进程%s运行完成\n",p->pname);
            strcpy(A[i].finish,p->pname);
            finishProcess(A);
            printf("\n");
            free(p);
        }
    else
        {
            readyEnd->next=p;
            p->next=NULL;
            readyEnd=p;
        }
    printf("\n");
}
void finishProcess(struct func* A)
{
    i++;
    printf("目前已经完成的进程有：\n");
    for(int j=0;j<=i;j++)
        printf("%s ",A[j].finish);
}
