#include<stdio.h>
#include<stdlib.h>
struct noderoom
{
	int taskname; //��ҵ��
	int begin;    //��ҵ��ʼ��ַ
	int size;     //ռ�ô�С
	int status;   //�ռ�״̬ 0ռ�ã�1����
	struct noderoom *next;  //��ָ��
};
void InitNode(struct noderoom *p);  //����ռ�
void Malloc1(int taskname,int size,struct noderoom *node);  //�״���Ӧ�㷨
void Malloc2(int taskname,int size,struct noderoom *node);  //�����Ӧ�㷨
void Free(int taskname,struct noderoom *node);  //�ͷſռ�
void PrintNode(struct noderoom *node);  //��ӡ����
void DestroyNode(struct noderoom *node);  //��������

int main(){
	struct noderoom *init=(struct noderoom*)malloc(sizeof(struct noderoom));
	struct noderoom *node=NULL;
	InitNode(init);	//��ʼ������
	node=init; 		//ʹ����ָ������ͷ
	int option;
    printf("1.�״���Ӧ�㷨\n2.�����Ӧ�㷨\n3.�˳�\n");
    printf("��ѡ���㷨��");
    scanf("%d",&option);
    printf("\n");
    if(option==1||option==2)
        {
            printf("��ҵ1 ����130 KB\n");
            if(option==1)
                Malloc1(1,130,node);
            else
                Malloc2(1,130,node);
            PrintNode(node);
            printf("��ҵ2 ����60 KB\n");
            if(option==1)
                Malloc1(2,60,node);
            else
                Malloc2(2,60,node);
            PrintNode(node);
            printf("��ҵ3 ����100 KB\n");
            if(option==1)
                Malloc1(3,100,node);
            else
                Malloc1(3,100,node);
            PrintNode(node);
            printf("��ҵ2 �ͷ�60 KB\n");
            Free(2,node);
            PrintNode(node);
            printf("��ҵ4 ����200 KB\n");
            if(option==1)
                Malloc1(4,200,node);
            else
                Malloc2(4,200,node);
            PrintNode(node);
            printf("��ҵ3 �ͷ�100 KB\n");
            Free(3,node);
            PrintNode(node);
            printf("��ҵ1 �ͷ�130 KB\n");
            Free(1,node);
            PrintNode(node);
            printf("��ҵ5 ����140 KB\n");
            if(option==1)
                Malloc1(5,140,node);
            else
                Malloc2(5,140,node);
            PrintNode(node);
            printf("��ҵ6 ����60 KB\n");
            if(option==1)
                Malloc1(6,60,node);
            else
                Malloc2(6,60,node);
            PrintNode(node);
            printf("��ҵ7 ����50 KB\n");
            if(option==1)
                Malloc1(7,50,node);
            else
                Malloc2(7,50,node);
            PrintNode(node);
            printf("��ҵ6 �ͷ�60 KB\n");
            Free(6,node);
            PrintNode(node);
            printf("��̬����������ɡ�\n");
            DestroyNode(node);	//��������
        }
    else if(option==3)
        return 0;
    else
        printf("�����������󣬳��������\n");
    return 0;
}

void InitNode(struct noderoom *p)  //����ռ�
{
	p->begin=0;   //�ڴ�ռ��1��ʼ
	p->size=640;  //ʵ��涨���õ��ڴ�ռ�Ϊ640KB
	p->status=1;  //����ռ�ĳ�ʼ״̬Ϊ����
	p->next=NULL; //����ռ�Ϊһ����
}

void Malloc1(int taskname,int size,struct noderoom *node)  //�״���Ӧ�㷨
{
	while(node!=NULL)
        {
            if(node->status==1)  //���еĿռ�
                {
                    if(node->size>size)  //����С��ʣ��ռ��������
                        {
                            struct noderoom *p=(struct noderoom*)malloc(sizeof(struct noderoom)); //����ռ�
                            p->begin=node->begin+size; //pָ�����ռ��Ŀռ�
                            p->size=node->size-size;   //ʣ��ռ��ȥ��ռ�Ŀռ�
                            p->status=1;               //p��ǰָ��Ŀռ�Ϊ����
                            node->taskname=taskname;   //��ҵ��
                            node->size=size;           //�ռ�
                            node->status=0;            //node��ָ��Ŀռ�Ϊռ��
                            p->next=node->next;
                            node->next=p;
                            break;
                        }
                    else if(node->size==size)  //����ռ�Ϳ��пռ��С���
                        {
                            node->taskname=taskname;   //��ҵ��
                            node->size=size;           //�ռ�
                            node->status=0;            //node��ָ��Ŀռ�Ϊռ��
                            break;
                        }
                }
            node=node->next;
        }
}

void Malloc2(int taskname,int size,struct noderoom *node)  //�����Ӧ�㷨
{
	struct noderoom *q=NULL;  //����ָ��q�Ա�����������õ���ѿ��п�
	while(node!=NULL)   //�ҵ���һ�����������Ŀ��п�
        {
            if(node->status==1&&node->size>=size)
                {
                    q=node;
                    break;
                }
            node=node->next;
        }
	while(node!=NULL)  //����Ѱ����ѵĿ��п�
        {
            if(node->status==1&&node->size>=size&&node->size<q->size)  //���еĿռ�
                q=node;
            node=node->next;
        }
	if(q->size>size)  //��ѿ��п�Ĵ�С���������С
        {
            struct noderoom *p=(struct noderoom*)malloc(sizeof(struct noderoom));
            p->begin=q->begin+size;  //pָ�����ռ��Ŀռ�
            p->size=q->size-size;    //ʣ��ռ��ȥ��ռ�Ŀռ�
            p->status=1;             //p��ǰָ��Ŀռ�Ϊ����
            q->taskname=taskname;    //��ҵ��
            q->size=size;            //�ռ�
            q->status=0;             //node��ָ��Ŀռ�Ϊռ��
            p->next=q->next;
            q->next=p;
        }
    else if(q->size==size)  //��ѿ��п�ռ��С���������
        {
            q->taskname=taskname;    //��ҵ��
            q->size=size;            //�ռ�
            q->status=0;             //node��ָ��Ŀռ�Ϊռ��
        }
}

void Free(int taskname,struct noderoom *node)  //�ͷſռ�
{
	while(node!=NULL)
        {
            if(node->status==1&&node->next->status==0&&node->next->taskname==taskname)  //�ͷſռ����һ��ռ����ʱ
                {
                    node->size=node->size+node->next->size;  //���пռ�ϲ�
                    struct noderoom *q=node->next;
                    node->next=node->next->next;  //nodeָ����һ��ռ�
                    free(q);
                    if(node->next->status==1)   //��һ���ռ��ǿ��пռ�ʱ
                        {
                            node->size=node->size+node->next->size;  //���пռ�ϲ�
                            struct noderoom *q=node->next;
                            node->next=node->next->next;  //nodeָ����һ��ռ�
                            free(q);
                        }
                    break;
                }
            else if(node->status==0&&node->taskname==taskname)  //�ͷſռ�Ϳ��пռ䲻����ʱ
                {
                    node->status=1;
                    if(node->next!=NULL&&node->next->status==1)  //��һ���ռ��ǿ��пռ�ʱ
                        {
                            node->size=node->size+node->next->size;  //���пռ�ϲ�
                            struct noderoom *q=node->next;
                            node->next=node->next->next;   //nodeָ����һ��ռ�
                            free(q);
                        }
                    break;
                }
            node=node->next;
        }
}

void PrintNode(struct noderoom *node)  //��ӡ����
{
	printf("                        �ڴ����                        \n");
	printf("-------------------------------------------------------\n");
	printf("��ʼ��ַ\t������ַ\t��С\t״̬\t����id\t\n");
	while(node!=NULL)
        {
            if(node->status==1)
                printf("%d\t\t%d\t\t%dKB\t����\t ��\t\n",node->begin+1,node->begin+node->size,node->size);
            else
                printf("%d\t\t%d\t\t%dKB\tռ��\t %d\t\n",node->begin+1,node->begin+node->size,node->size,node->taskname);
            node=node->next;
        }
	printf("-------------------------------------------------------\n\n");
}

void DestroyNode(struct noderoom *node)  //��������
{
	while(node!=NULL)  //�����ͷſռ�
        {
            free(node);
            node=node->next;
        }
}
