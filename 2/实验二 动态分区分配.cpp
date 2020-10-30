#include<stdio.h>
#include<stdlib.h>
struct noderoom
{
	int taskname; //作业号
	int begin;    //作业开始地址
	int size;     //占用大小
	int status;   //空间状态 0占用，1空闲
	struct noderoom *next;  //后指针
};
void InitNode(struct noderoom *p);  //分配空间
void Malloc1(int taskname,int size,struct noderoom *node);  //首次适应算法
void Malloc2(int taskname,int size,struct noderoom *node);  //最佳适应算法
void Free(int taskname,struct noderoom *node);  //释放空间
void PrintNode(struct noderoom *node);  //打印函数
void DestroyNode(struct noderoom *node);  //销毁链表

int main(){
	struct noderoom *init=(struct noderoom*)malloc(sizeof(struct noderoom));
	struct noderoom *node=NULL;
	InitNode(init);	//初始化主链
	node=init; 		//使主链指向链表头
	int option;
    printf("1.首次适应算法\n2.最佳适应算法\n3.退出\n");
    printf("请选择算法：");
    scanf("%d",&option);
    printf("\n");
    if(option==1||option==2)
        {
            printf("作业1 申请130 KB\n");
            if(option==1)
                Malloc1(1,130,node);
            else
                Malloc2(1,130,node);
            PrintNode(node);
            printf("作业2 申请60 KB\n");
            if(option==1)
                Malloc1(2,60,node);
            else
                Malloc2(2,60,node);
            PrintNode(node);
            printf("作业3 申请100 KB\n");
            if(option==1)
                Malloc1(3,100,node);
            else
                Malloc1(3,100,node);
            PrintNode(node);
            printf("作业2 释放60 KB\n");
            Free(2,node);
            PrintNode(node);
            printf("作业4 申请200 KB\n");
            if(option==1)
                Malloc1(4,200,node);
            else
                Malloc2(4,200,node);
            PrintNode(node);
            printf("作业3 释放100 KB\n");
            Free(3,node);
            PrintNode(node);
            printf("作业1 释放130 KB\n");
            Free(1,node);
            PrintNode(node);
            printf("作业5 申请140 KB\n");
            if(option==1)
                Malloc1(5,140,node);
            else
                Malloc2(5,140,node);
            PrintNode(node);
            printf("作业6 申请60 KB\n");
            if(option==1)
                Malloc1(6,60,node);
            else
                Malloc2(6,60,node);
            PrintNode(node);
            printf("作业7 申请50 KB\n");
            if(option==1)
                Malloc1(7,50,node);
            else
                Malloc2(7,50,node);
            PrintNode(node);
            printf("作业6 释放60 KB\n");
            Free(6,node);
            PrintNode(node);
            printf("动态分区分配完成。\n");
            DestroyNode(node);	//销毁链表
        }
    else if(option==3)
        return 0;
    else
        printf("您的输入有误，程序结束。\n");
    return 0;
}

void InitNode(struct noderoom *p)  //分配空间
{
	p->begin=0;   //内存空间从1开始
	p->size=640;  //实验规定可用的内存空间为640KB
	p->status=1;  //分配空间的初始状态为空闲
	p->next=NULL; //分配空间为一整个
}

void Malloc1(int taskname,int size,struct noderoom *node)  //首次适应算法
{
	while(node!=NULL)
        {
            if(node->status==1)  //空闲的空间
                {
                    if(node->size>size)  //需求小于剩余空间充足的情况
                        {
                            struct noderoom *p=(struct noderoom*)malloc(sizeof(struct noderoom)); //分配空间
                            p->begin=node->begin+size; //p指向分配空间后的空间
                            p->size=node->size-size;   //剩余空间减去已占的空间
                            p->status=1;               //p当前指向的空间为空闲
                            node->taskname=taskname;   //作业号
                            node->size=size;           //空间
                            node->status=0;            //node所指向的空间为占用
                            p->next=node->next;
                            node->next=p;
                            break;
                        }
                    else if(node->size==size)  //需求空间和空闲空间大小相等
                        {
                            node->taskname=taskname;   //作业号
                            node->size=size;           //空间
                            node->status=0;            //node所指向的空间为占用
                            break;
                        }
                }
            node=node->next;
        }
}

void Malloc2(int taskname,int size,struct noderoom *node)  //最佳适应算法
{
	struct noderoom *q=NULL;  //定义指针q以保存遍历后所得的最佳空闲块
	while(node!=NULL)   //找到第一个满足条件的空闲块
        {
            if(node->status==1&&node->size>=size)
                {
                    q=node;
                    break;
                }
            node=node->next;
        }
	while(node!=NULL)  //遍历寻找最佳的空闲块
        {
            if(node->status==1&&node->size>=size&&node->size<q->size)  //空闲的空间
                q=node;
            node=node->next;
        }
	if(q->size>size)  //最佳空闲块的大小大于需求大小
        {
            struct noderoom *p=(struct noderoom*)malloc(sizeof(struct noderoom));
            p->begin=q->begin+size;  //p指向分配空间后的空间
            p->size=q->size-size;    //剩余空间减去已占的空间
            p->status=1;             //p当前指向的空间为空闲
            q->taskname=taskname;    //作业号
            q->size=size;            //空间
            q->status=0;             //node所指向的空间为占用
            p->next=q->next;
            q->next=p;
        }
    else if(q->size==size)  //最佳空闲块空间大小和需求相等
        {
            q->taskname=taskname;    //作业号
            q->size=size;            //空间
            q->status=0;             //node所指向的空间为占用
        }
}

void Free(int taskname,struct noderoom *node)  //释放空间
{
	while(node!=NULL)
        {
            if(node->status==1&&node->next->status==0&&node->next->taskname==taskname)  //释放空间的上一块空间空闲时
                {
                    node->size=node->size+node->next->size;  //空闲空间合并
                    struct noderoom *q=node->next;
                    node->next=node->next->next;  //node指向下一块空间
                    free(q);
                    if(node->next->status==1)   //下一个空间是空闲空间时
                        {
                            node->size=node->size+node->next->size;  //空闲空间合并
                            struct noderoom *q=node->next;
                            node->next=node->next->next;  //node指向下一块空间
                            free(q);
                        }
                    break;
                }
            else if(node->status==0&&node->taskname==taskname)  //释放空间和空闲空间不连续时
                {
                    node->status=1;
                    if(node->next!=NULL&&node->next->status==1)  //下一个空间是空闲空间时
                        {
                            node->size=node->size+node->next->size;  //空闲空间合并
                            struct noderoom *q=node->next;
                            node->next=node->next->next;   //node指向下一块空间
                            free(q);
                        }
                    break;
                }
            node=node->next;
        }
}

void PrintNode(struct noderoom *node)  //打印函数
{
	printf("                        内存情况                        \n");
	printf("-------------------------------------------------------\n");
	printf("起始地址\t结束地址\t大小\t状态\t任务id\t\n");
	while(node!=NULL)
        {
            if(node->status==1)
                printf("%d\t\t%d\t\t%dKB\t空闲\t 无\t\n",node->begin+1,node->begin+node->size,node->size);
            else
                printf("%d\t\t%d\t\t%dKB\t占用\t %d\t\n",node->begin+1,node->begin+node->size,node->size,node->taskname);
            node=node->next;
        }
	printf("-------------------------------------------------------\n\n");
}

void DestroyNode(struct noderoom *node)  //销毁链表
{
	while(node!=NULL)  //遍历释放空间
        {
            free(node);
            node=node->next;
        }
}
