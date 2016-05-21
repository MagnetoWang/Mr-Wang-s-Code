#include <stdio.h>
#include <malloc.h>  //�õ�ָ����СΪSize���ڴ����������ֽڵ�ָ��//
#include <string.h>
#include <stdlib.h>  //��׼�⺯��// 
#define NULL 0
#define LEN sizeof(struct address_list)  //�����ֽ�//
int n;
struct address_list
{
	char name[30];     //����
	char work[30];     //ְҵ
	char handset[30];  //�ֻ�
	char email[30];    //�����ʼ�
	char address[30];  //ͨѶ��ַ
	struct address_list *next;
};
struct address_list *shifang(struct address_list *head); // �ͷ��ڴ溯������
//��������������ͷ����������
struct address_list *creat(void)       
{
	struct address_list *head,*p1,*p2;
	char name[20];
	n=0;
	p1=(struct address_list *)malloc(LEN);
	p2=p1;   //ǿ���ڴ�ת��
	printf("������ͨѶ¼������!\n��������Ϊ0ʱ��ʾ��������!\n");
	printf("����������:");
	gets(name);
	if(strcmp(name,"0")!=0)
	{
		strcpy(p1->name,name);
		printf("������ְҵ:");     gets(p1->work);//�Ա� 
		printf("�������ֻ�:");     gets(p1->handset);
		printf("�����������ʼ�:"); gets(p1->email);
		printf("������ͨѶ��ַ:");  gets(p1->address);
		head=NULL;
		while(1)
		{
			n=n+1;   //��¼ͨѶ¼��������
			if(n==1)
				head=p1;
			else
				p2->next=p1;
			p2=p1;
			printf("����������:");
			gets(name);
			if(strcmp(name,"0")==0)
			{
				break;
			}
			else
			{
				p1=(struct address_list *)malloc(LEN);
				strcpy(p1->name,name);
				printf("������ְҵ:"); gets(p1->work);
				printf("�������ֻ�:"); gets(p1->handset);
				printf("�����������ʼ�:"); gets(p1->email);
				printf("������ͨѶ��ַ:");  gets(p1->address);
			}
		}
		p2->next=NULL;
		return head;
	}
	else
		return 0;
}
//��������
void print(struct address_list *head)   
{
	struct address_list *p;
	if(head!=NULL)
	{
		p=head;
		printf("��ͨѶ¼���ڹ���%d��:\n",n);
		printf("---����-------ְҵ--------�ֻ�-------Email-------ͨѶ��ַ\n");
		printf("==================================\n");
		do
		{
			printf("== %s",p->name); printf("       ");
			printf("%s",p->work); printf("       ");
			printf("%s",p->handset); printf("       ");
			printf("%s",p->email); printf("       ");
			printf("%s",p->address); printf("       \n");
			p=p->next;
		}while(p!=NULL);
		printf("==================================\n");
	}
	else
		printf("ͨѶ¼Ϊ��,�޷�����!\n");
}
//���Ӻ���
struct address_list *insert(struct address_list *head) 
{
	struct address_list *p0,*p1,*p2;
	char name[20];
	p1=head;
	printf("���������ӵ�����:\n");
	printf("����������:"); gets(name);
	if(strcmp(name,"0")==0)
	{
		printf("��������Ϊ0,����ʧ��!\n");
		return(head);
	}
	else
	{
		p0=(struct address_list *)malloc(LEN);
		strcpy(p0->name,name);
		printf("������ְҵ:"); gets(p0->work);
		printf("�������ֻ�:"); gets(p0->handset);
		printf("�����������ʼ�:"); gets(p0->email);
		printf("������ͨѶ��ַ:");  gets(p0->address);
		n=n+1;
		if(head==NULL)
		{
			head=p0;
			p0->next=NULL;
			return head;
		}
		else
		{
			while(strcmp(p0->name,p1->name)>0&&(p1->next!=NULL))
			{
				p2=p1;
				p1=p1->next;
			}
			if(strcmp(p0->name,p1->name)<0 || strcmp(p0->name,p1->name)==0)
			{
				if(head==p1)
				{
					head=p0;
				}
				else
				{
					p2->next=p0;
				}
				p0->next=p1;
			}
			else
			{
				p1->next=p0;
				p0->next=NULL;
			}
			return head;
		}
	}
}
struct address_list* delete_txl(struct address_list *head)
{
	struct address_list *p,*q;
	char name[30];
	if(head==NULL)
	{
		printf("ͨѶ¼Ϊ��,�޷���ʾ!\n");
		return head;
	}
	p=head;
	printf("��������Ҫɾ�����˵�����:");
	gets(name);
	if(strcmp(head->name,name)==0)
	{
		head=head->next;
		free(p);
		printf("ɾ�������ɹ���\n");
		return head;
	}
	else
	{
		q=head,p=head->next;
		while(p!=NULL)
		{
			if(strcmp(p->name,name)==0)
			{
				q->next=p->next;
				free(p);
				printf("ɾ�������ɹ���\n");
				return head;
			}
			p=p->next;
			q=q->next;
		}
	}
}
//��ʾ����
struct address_list *display(struct address_list *head)
{
	struct address_list *p1,*p2;
	char name[30];
	int m;
	if(head==NULL)
	{
		printf("ͨѶ¼Ϊ��,�޷���ʾ!\n");
		return head;
	}
	p1=head;
	m=0;
	printf("��������Ҫ��ʾ�˵�����:");
	gets(name);
	while(p1!=NULL)
	{
		while((strcmp(p1->name,name))!=0 && p1->next!=NULL)
		{
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p1->name,name)==0)
		{
			m++;
			printf("%s��ͨѶ��������:\n",name);
			printf("---����--------ְҵ--------�ֻ�-------Email------ͨѶ��ַ\n");
			printf("==================================\n");
			printf("== %s",p1->name);printf("       ");
			printf("%s",p1->work);printf("       ");
			printf("%s",p1->handset);printf("       ");
			printf("%s",p1->email);printf("       ");
			printf("%s",p1->address); printf("       \n");
			printf("==================================\n");
		}
		p1=p1->next;
	}
	if(m==0)
	{
		printf("����δ�ڱ�ͨѶ¼��!\n");
	}
	return(head);
}

//��������
struct address_list *paixu(struct address_list *head)
{
	struct address_list *p1,*p2;
	int i,j;
	struct address_list1
	{
		char name[30];
		char work[30];
		char handset[30];
		char email[30];
		char address[30];
	};
	struct address_list1 px[200];
	struct address_list1 temp;
	if(head==NULL)
	{
		printf("ͨѶ¼Ϊ��,�޷�����!\n");
		return(head);
	}
	p1=head;
	for(i=0;i<n,p1!=NULL;i++)
	{
		strcpy(px[i].name,p1->name);
		strcpy(px[i].work,p1->work);
		strcpy(px[i].handset,p1->handset);
		strcpy(px[i].email,p1->email);
		strcpy(px[i].address,p1->address);
		p2=p1;
		p1=p1->next;
	}
	head=shifang(head);
	for(j=0;j<n-1;j++)
	{
		for(i=j+1;i<n;i++)
		{
			if(strcmp(px[i].name,px[j].name)<0)
			{
				temp=px[i];
				px[i]=px[j];
				px[j]=temp;
			}
		}
	}
	p1=(struct address_list *)malloc(LEN);
	p2=p1;
	strcpy(p1->name,px[0].name);
	strcpy(p1->work,px[0].work);
	strcpy(p1->handset,px[0].handset);
	strcpy(p1->email,px[0].email);
	strcpy(p1->address,px[0].address);

	head=p1;
	for(i=1;i<n;i++)
	{
		p1=(struct address_list *)malloc(LEN);
		strcpy(p1->name,px[i].name);
		strcpy(p1->work,px[i].work);
		strcpy(p1->handset,px[i].handset);
		strcpy(p1->email,px[i].email);
		strcpy(p1->address,px[i].address);
		p2->next=p1;
		p2=p1;
	}
	p2->next=NULL;
	printf("������������Ϊ:\n");
	print(head);
	return(head);
}
//�������Һ���
struct address_list *search(struct address_list *head)
{
	struct address_list *p1,*p2;
	int m;
	char name[30];
	if(head==NULL)
	{
		printf("ͨѶ¼Ϊ��,�޷���������!\n");
		return(head);
	}
	p1=head;
	printf("********************\n");
	printf("**  ��������Ҫ���ҵ�����  **\n");
	printf("********************\n");
	m=0;
	gets(name);
	while(p1!=NULL)
	{
		while(strcmp(p1->name,name)!=0&&p1->next!=NULL)
		{
			p2=p1;
			p1=p1->next;
		}
		if(strcmp(p1->name,name)==0)
		{
			m++;
			printf("�����ҵ�������:\n");
			printf("+++++++++++++++++++++++++++++++++++\n");
			printf("++ %s        %s       %s       %s        %s\n",p1->name,p1->work,p1->handset,p1->email,p1->address);
			printf("+++++++++++++++++++++++++++++++++++\n");
		}
		p1=p1->next;

		if(m==0)
		{
			printf("����δ�ڱ�ͨѶ¼��!\n");
		}
		break;
	}

	return(head);
}

//�ͷ��ڴ溯��
struct address_list *shifang(struct address_list *head)
{
	struct address_list *p1;
	while(head!=NULL)
	{
		p1=head;
		head=head->next;
		free(p1);
	}
	return(head);
}

//�ļ�д�뺯��
void save(struct address_list *head)
{
	FILE *fp;
	struct address_list *p1;
	char tong[30];
	if(head==NULL)
	{
		printf("ͨѶ¼Ϊ��,�޷��洢!\n");
		return;
	}
	printf("�����뱣�������ļ���:");
	gets(tong);
	fp=fopen("(tong).txt","w");
	if(fp==NULL)
	{
		printf("cannot open file\n");
		return;
	}
	p1=head;
	fprintf(fp,"����    ְҵ      �ֻ�     Email     ͨѶ��ַ\n");
	for(;p1!=NULL;) 
	{
		fprintf(fp,"%s       %s       %s        %s       %s\n",p1->name,p1->work,p1->handset,p1->email,p1->address);
		p1=p1->next;
	}
	printf("��������!\n");
	fclose(fp);
}

//�ļ���������
struct address_list *load(struct address_list *head)
{
	FILE *fp;
	char tong[30];
	struct address_list *p1,*p2;
	printf("������Ҫ�������ļ���:");
	gets(tong);
	fp=fopen("(tong).txt","r");
	if(fp==NULL)
	{
		printf("��ͨѶ¼��������,�޷�����!\n");
		return(head);
	}
	else
	{
		head=shifang(head);
	}
	p1=(struct address_list *)malloc(LEN);
	fscanf(fp,"%s%s%s%s%s",&p1->name,&p1->work,&p1->handset,&p1->email,&p1->address);
	if(feof(fp)!=0)
	{
		printf("�ļ�Ϊ��,�޷�����!\n");
		return(head);
	}
	else
	{
		rewind(fp);
		p2=p1;
		head=p1;
		n=0;
		while(feof(fp)==0)
		{
			fscanf(fp,"%s%s%s%s%s",&p1->name,&p1->work,&p1->handset,&p1->email,&p1->address);
			if(feof(fp)!=0)
				break;
			p2->next=p1;
			p2=p1;
			p1=(struct address_list *)malloc(LEN);
			n=n+1;
		}
		p2->next=NULL;
		p1=head;
		head=head->next;
		n=n-1;
		free(p1);
		print(head);
		printf("��������!\n");
		return(head);
	}
	fclose(fp);
}

//�ۺϲ�������
struct address_list *menu(struct address_list *head)
{
	char num[10];
	while(1)
	{
		printf("*********************\n");
		printf("*** 1 ��������      ****\n");
		printf("*** 2 ������ʾ      ****\n");
		printf("*** 3 ����          ****\n");
		printf("*** 4 �˳�          ****\n");
		printf("*********************\n");
		printf("��������ѡ���Ĳ���:");
		gets(num);
		switch(*num)
		{
		case '1':
			{
				head=search(head);                          //��������
				print(head);
			}
			break;
		case '2':
			{
				head=display(head);                          //��ʾ
			}
			break;
		case '3':
			{
				head=insert(head);                           //����
				print(head);
			}
			break;
		case '4':
			return head;
		default:
			printf("�������󣬴������!\n");
			break;
		}
		if(strcmp(num,"6")==0)
			break;
	}
	return head;
}
//������
main()
{
	struct address_list *head=NULL;
	char num[10];
	printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
	printf("*=*               ����˵��                *=*\n");
	printf("*=*    �뼰ʱ���洴�����ϵ�ͨѶ¼����!    *=*\n");
	printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
	while(1)
	{
		printf("************************\n");
		printf("***     1 ����ͨѶ¼      ****\n");
		printf("***     2 ����������      ****\n");
		printf("***     3 �ۺϲ���        ****\n");
		printf("***     4 ����            ****\n");
		printf("***     5 ����            ****\n"); 
		printf("***     6 ɾ��            ****\n");
		printf("***     7 �˳�            ****\n");
		printf("************************\n");
		printf("��������ѡ���Ĳ���:");
		gets(num);
		switch(*num)
		{
		case '1':
			{
				if(head==NULL)
				{
					head=creat();                                //����
					print(head);
				}
				else
				{
					head=shifang(head);
					head=creat();                                //���´���
					print(head);
				}
			}
			break;
		case '2':
			{
				head=paixu(head);                               //����
			}
			break;
		case '3':
			{
				head=menu(head);                              //�ۺϲ���
			}
			break;
		case '4':
			{
				save(head);                                   //�ļ�����
				print(head);
			}
			break;
		case '5':
			{
				head=load(head);                              //�ļ�����
			}
			break;
		case '6':
			{
				head=delete_txl(head);                           //ɾ��
				print(head);
			}
			break;
		case '7':
			head=shifang(head);
			break;
		default:
			printf("�������󣬴������!\n");
			break;
		}
		if(strcmp(num,"7")==0)
			break;
	}
}
//http://blog.csdn.net/hackbuteer1/article/details/6573488# 
