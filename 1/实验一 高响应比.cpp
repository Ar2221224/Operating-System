//高响应比
#include<cstdio>
#include<cstdlib>
#include<cstring>
#define WAIT "Wait"//就绪状态
#define RUN "Run"//运行状态
#define FINISH "Finish"//完成状态
#define JOBNUMBER 5 //对5个进程进行调度
typedef struct PCB{
    char jobName[10];//作业名
	int arriveTime;//到达时间
	int runTime;//需要运行时间
	int startTime;//开始时间
	int endTime;//完成时间
	int turnoverTime;//周转时间
	float useWeightTurnoverTime;//带权周转时间
	char processStatus[10];//进程状态
	int useTime;//进程已用CPU时间
};
static int currentTime=0;//当前时间
static int finishNumber=0;//进程完成数量
char JobArray[JOBNUMBER][10];//存放数组名信息的二元数组
float priority[JOBNUMBER];//存放进程优先级的一元数组

void createPCB(struct PCB* pcb);//创建PCB
void printJob(struct PCB* pcb);//打印每个时间片各进程的信息
float weightTurnoverTimeCount(struct PCB* pcb);//计算平均带权周转时间
float turnOverTimeCount(struct PCB* pcb);//计算平均周转时间
void compare(struct PCB* pcb);//比较各个进程之间的到达时间,按升序排列
void printInfo(struct PCB* pcb);//打印进程调度顺序，平均周转时间及平均带权周转时间
void loop(struct PCB* pcb, int i);//循环遍历
void highestResponseRatioNext(struct PCB* pcb);//高响应比调度算法

int main(){
	struct PCB pcb[JOBNUMBER];
    printf("****************************************\n");
    printf("*******实验一  动态优先数调度算法*******\n");
    printf("****************************************\n\n");
    highestResponseRatioNext(pcb);
    system("pause");
	return 0;
}
void createPCB(struct PCB* pcb){
    freopen("input.txt","r",stdin); //从源文件夹中读取文件 stdin标准输入
 	printf("从文件中读入三个参数的数据：\n");
 	printf("进程名 到达时间 需要运行时间\n");
 	for(int i=0;i<5;i++)
        {
            scanf("%s",&pcb[i].jobName);//进程名
            scanf("%d",&pcb[i].arriveTime);//到达时间
            scanf("%d",&pcb[i].runTime);//需要运行时间
            pcb[i].startTime=0;
            pcb[i].endTime=0;
            pcb[i].turnoverTime=0;
            pcb[i].useWeightTurnoverTime=0.0;
            pcb[i].useTime=0;
            strcpy(pcb[i].processStatus,WAIT);//进程刚被读取时状态都为WAIT
            printf("%s\t  %d\t     %d\n",pcb[i].jobName,pcb[i].arriveTime,pcb[i].runTime);
        }
	printf("-----------------------------------------------------------------------------\n");
}
void printJob(struct PCB* pcb){
	printf("当前时间为%d\n",currentTime);
	printf("进程名 到达时间 需要运行时间 开始时间 已用CPU时间 完成时间 周转时间 带权周转时间 进程状态\n");
	for(int i=0;i<JOBNUMBER;i++)
        {
            if(strcmp(pcb[i].processStatus,FINISH)==0)//如果进程为finish状态，这样输出
                printf("%s\t%d\t%4d\t\t%d\t  %d\t     %d\t      %d \t%.2f\t  %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].useTime,
                       pcb[i].endTime, pcb[i].turnoverTime, pcb[i].useWeightTurnoverTime, pcb[i].processStatus);
            else if(strcmp(pcb[i].processStatus,RUN)==0)//如果进程为run状态，这样输出
                printf("%s\t%d\t%4d\t\t%d\t  %d\t   运行中    none       none       %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].startTime, pcb[i].useTime, pcb[i].processStatus);
            else //如果进程为wait状态，这样输出
                printf("%s\t%d\t%4d\t      未运行      %d\t    none     none       none\t   %s\n", pcb[i].jobName, pcb[i].arriveTime, pcb[i].runTime, pcb[i].useTime, pcb[i].processStatus);
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
	printf("进程调度顺序为：%s -> %s -> %s -> %s -> %s\n",JobArray[0],JobArray[1],JobArray[2],JobArray[3],JobArray[4]);
	printf("平均周转时间为：%.2f\n",turnOverTimeCount(pcb));
	printf("平均带权周转时间为：%.2f\n",weightTurnoverTimeCount(pcb));
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
            if(currentTime<pcb[0].arriveTime)//当前时间小于第一个节点到来时间时，直接打印
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
	printInfo(pcb);//打印进程调度顺序，平均周转时间及平均带权周转时间
	currentTime=0;//当前时间置位
	finishNumber=0;//完成进程数量置位
}
