//����Ӧ��
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define WAIT "Wait"//����״̬
#define RUN "Run"//����״̬
#define FINISH "Finish"//���״̬
#define JOBNUMBER 5 //��5�����̽��е���
typedef struct PCB{
    char jobName[10];//��ҵ��
	int arriveTime;//����ʱ��
	int runTime;//��Ҫ����ʱ��
	int startTime;//��ʼʱ��
	int endTime;//���ʱ��
	int turnoverTime;//��תʱ��
	float useWeightTurnoverTime;//��Ȩ��תʱ��
	char processStatus[10];//����״̬
	int useTime;//��������CPUʱ��
};
static int currentTime=0;//��ǰʱ��
static int finishNumber=0;//�����������
char JobArray[JOBNUMBER][10];//�����������Ϣ�Ķ�Ԫ����
float priority[JOBNUMBER];//��Ž������ȼ���һԪ����

void createPCB(struct PCB* pcb);//����PCB
void printJob(struct PCB* pcb);//��ӡÿ��ʱ��Ƭ�����̵���Ϣ
float weightTurnoverTimeCount(struct PCB* pcb);//����ƽ����Ȩ��תʱ��
float turnOverTimeCount(struct PCB* pcb);//����ƽ����תʱ��
void compare(struct PCB* pcb);//�Ƚϸ�������֮��ĵ���ʱ��,����������
void printInfo(struct PCB* pcb);//��ӡ���̵���˳��ƽ����תʱ�估ƽ����Ȩ��תʱ��
void loop(struct PCB* pcb, int i);//ѭ������
void highestResponseRatioNext(struct PCB* pcb);//����Ӧ�ȵ����㷨

int main(){
	struct PCB pcb[JOBNUMBER];
    printf("****************************************\n");
    printf("*******ʵ��һ  ��̬�����������㷨*******\n");
    printf("****************************************\n\n");
    highestResponseRatioNext(pcb);
    system("pause");
	return 0;
}
void createPCB(struct PCB* pcb){
    freopen("input.txt","r",stdin); //��Դ�ļ����ж�ȡ�ļ� stdin��׼����
 	printf("���ļ��ж����������������ݣ�\n");
 	printf("������ ����ʱ�� ��Ҫ����ʱ��\n");
 	for(int i=0;i<5;i++)
        {
            scanf("%s",&pcb[i].jobName);//������
            scanf("%d",&pcb[i].arriveTime);//����ʱ��
            scanf("%d",&pcb[i].runTime);//��Ҫ����ʱ��
            pcb[i].startTime=0;
            pcb[i].endTime=0;
            pcb[i].turnoverTime=0;
            pcb[i].useWeightTurnoverTime=0.0;
            pcb[i].useTime=0;
            strcpy(pcb[i].processStatus,WAIT);//���̸ձ���ȡʱ״̬��ΪWAIT
            printf("%s\t  %d\t     %d\n",pcb[i].jobName,pcb[i].arriveTime,pcb[i].runTime);
        }
	printf("-----------------------------------------------------------------------------\n");
}
void printJob(struct PCB* pcb){
	printf("��ǰʱ��Ϊ%d\n",currentTime);
	printf("������ ����ʱ�� ��Ҫ����ʱ�� ��ʼʱ�� ����CPUʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ�� ����״̬\n");
	for(int i=0;i<JOBNUMBER;i++)
        {
            if(strcmp(pcb[i].processStatus,FINISH)==0)//�������Ϊfinish״̬���������
                printf("%s\t%d\t%4d\t\t%d\t  %d\t     %d\t      %d \t%.2f\t  %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].useTime,
                       pcb[i].endTime, pcb[i].turnoverTime, pcb[i].useWeightTurnoverTime, pcb[i].processStatus);
            else if(strcmp(pcb[i].processStatus,RUN)==0)//�������Ϊrun״̬���������
                printf("%s\t%d\t%4d\t\t%d\t  %d\t   ������    none       none       %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].useTime, pcb[i].processStatus);
            else //�������Ϊwait״̬���������
                printf("%s\t%d\t%4d\t      δ����      %d\t    none     none       none\t   %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].useTime, pcb[i].processStatus);
        }
	printf("-----------------------------------------------------------------------------\n");
}
float weightTurnoverTimeCount(struct PCB* pcb){
	float sum=0.0;
	for(int i=0;i<JOBNUMBER;i++)
		sum+=pcb[i].useWeightTurnoverTime;
	return sum/JOBNUMBER;
}
float turnOverTimeCount(struct PCB* pcb){
	float sum=0.0;
	for(int i=0;i<JOBNUMBER;i++)
		sum+=pcb[i].turnoverTime;
	return sum/JOBNUMBER;
}
void compare(struct PCB* pcb){
	for(int i=0;i<JOBNUMBER;i++)
        {
            int min=pcb[i].arriveTime,minIndex=i;
            for(int j=i+1;j<JOBNUMBER;j++)
                {
                    if(pcb[j].arriveTime<min)
                    {
                        min=pcb[j].arriveTime;
                        minIndex=j;
                    }
                }
            struct PCB temp=pcb[i];
            pcb[i]=pcb[minIndex];
            pcb[minIndex]=temp;
        }
}
void printInfo(struct PCB* pcb){
	printf("���̵���˳��Ϊ��%s -> %s -> %s -> %s -> %s\n",JobArray[0],JobArray[1],JobArray[2],JobArray[3],JobArray[4]);
	printf("ƽ����תʱ��Ϊ��%.2f\n",turnOverTimeCount(pcb));
	printf("ƽ����Ȩ��תʱ��Ϊ��%.2f\n",weightTurnoverTimeCount(pcb));
}
void loop(struct PCB* pcb, int i){
	pcb[i].startTime=currentTime;
	pcb[i].endTime=pcb[i].startTime+pcb[i].runTime;
	pcb[i].turnoverTime=pcb[i].endTime-pcb[i].arriveTime;
	pcb[i].useWeightTurnoverTime=pcb[i].turnoverTime*1.0/pcb[i].runTime;
	strcpy(pcb[i].processStatus, RUN);
	while(true)
        {
            if(currentTime==pcb[i].endTime)
                {
                    strcpy(pcb[i].processStatus,FINISH);
                    finishNumber++;
                    if(finishNumber==JOBNUMBER)
                        printJob(pcb);
                    currentTime--;
                    break;
                }
            else
                {
                    printJob(pcb);
                    currentTime++;
                    pcb[i].useTime++;
                }
        }
}
void highestResponseRatioNext(struct PCB* pcb){
	createPCB(pcb);
	compare(pcb);
	int i=0,j=0;
	for( ;finishNumber!=JOBNUMBER;currentTime++)
        {
            float maxPriority=0.0;
            int indexPriority=0;
            if(currentTime<pcb[0].arriveTime)//��ǰʱ��С�ڵ�һ���ڵ㵽��ʱ��ʱ��ֱ�Ӵ�ӡ
                printJob(pcb);
            else
                {
                    for(int i=0;i<JOBNUMBER;i++)
                        {
                            if(strcmp(pcb[i].processStatus,FINISH)!= 0)
                                {
                                    int waitTime=currentTime-pcb[i].arriveTime;
                                    priority[i]=(waitTime+pcb[i].runTime)*1.0/pcb[i].runTime;
                                    if(priority[i]>maxPriority)
                                        {
                                            maxPriority=priority[i];
                                            indexPriority=i;
                                        }
                                }
                        }
                    strcpy(JobArray[j++],pcb[indexPriority].jobName);
                    loop(pcb,indexPriority);
                }
        }
	printInfo(pcb);//��ӡ���̵���˳��ƽ����תʱ�估ƽ����Ȩ��תʱ��
	currentTime=0;//��ǰʱ����λ
	finishNumber=0;//��ɽ���������λ
}
