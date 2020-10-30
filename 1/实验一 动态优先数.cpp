//��̬������
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<conio.h> //ͨ������̨��������������������
typedef struct pcb{
    char pname[10]; //������
    char state;     //����״̬ W(Wait)������� R(Run)�������� F(Finish)�������
    int priority;   //�������ȼ� �˴�����������Ϊ���ȼ���
    int runTime;    //���̻������е�ʱ��Ƭ
    int useTime;    //��������CPUʱ��
    struct pcb* next;
}PCB;
typedef struct func{
    char finish[10];//����ɵĽ���
};
int num; //������
PCB readyHead; //ͷ��㣬���洢����
PCB *readyEnd; //β�ڵ�ָ��
int i=0;
struct func A[10];

void createProcess();     //�������̣�����ռ��Լ��������������
void sortProcess();       //��ʼ������
void printProcessInfo();  //�����ǰ������Ϣ
void printProcessLink();  //��ʾ��ǰ���̵���˳��
void runProcess();        //��������
void finishProcess(struct func* A);     //��ʾ����ɵĽ���

int main()
{
    printf("****************************************\n");
    printf("*******ʵ��һ  ��̬�����������㷨*******\n");
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
    printf("���ˣ�������������ȴ���\n");
    return 0;
}
void createProcess()
{
    PCB *p,*prior;
    printf("����Ҫ���еĽ���������");
    scanf("%d",&num);
    printf("\n");
    p=(PCB*)malloc(sizeof(PCB));
    prior=&readyHead;
    prior->next=p;
    for(int k=0;k<num;k++)
        {
            printf("�����%d�����̵Ľ�������",k+1);
            scanf("%s",p->pname);
            printf("����ý��̵����ȼ���");
            scanf("%d",&(p->priority));
            printf("����ý��̵�����ʱ�䣺");
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
    printf("����ǰ�Ľ�����Ϣ:\n");
    printf("=================================================================\n");
    printf("������      ���ȼ� ����ʱ��   ����CPUʱ��  ״̬    ��һ������\n");
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
    printf("��ǰ���̵���˳��:\n");
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
    printf("��ǰ���еĽ���Ϊ:\n");
    printf("%s\n",p->pname);
    p->priority--;
    p->runTime--;
    p->useTime++;
    readyHead.next=p->next;
    if(p->runTime==0)
        {
            p->state='F';
            printf("����%s�������\n",p->pname);
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
    printf("Ŀǰ�Ѿ���ɵĽ����У�\n");
    for(int j=0;j<=i;j++)
        printf("%s ",A[j].finish);
}
