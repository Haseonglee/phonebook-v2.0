#include <stdio.h>

#include <string.h> 
//���� �޸� �Ҵ��� ���� ����
 
#define CAPACITY 100 //�迭�� ũ�� 
#define BUFFER_SIZE 20
//�������� ->deta section�̶� �Ҹ��� �޸𸮿����� ��ġ 
char *names[CAPACITY];//�̸� ����  �迭 �ε����� �̿��Ͽ� ��ȣ�� �̸��� ���� 
//ĳ���� ������ Ÿ���� �迭 
//names �迭�� �� �׿� �̸� �迭��(������)�� �ּҸ� �־���� 
char *numbers[CAPACITY];//��ȭ��ȣ ���� 
//��ȭ��ȣ�� ���ڿ��� �ٷ�°� ���� 

int n=0;

void add();
void find();
void status();
void remover(); 
void load();
void save();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char command[BUFFER_SIZE];
	while(1){
		
		printf("����� �Է��ϼ���\n");//����� ���ù���
		scanf("%s",command);
		
		if(strcmp(command,"add")==0)
		add();
		else if(strcmp(command,"find")==0)
		find();
		else if(strcmp(command,"status")==0)
		status();
		else if(strcmp(command,"delete")==0)
		remover();
		else if(strcmp(command,"save")==0)
		save();
		else if(strcmp(command,"read")==0)
		load();
		else if(strcmp(command,"exit")==0)
		break;
	}
	return 0;
}


void find(){
	char buf[BUFFER_SIZE];
	printf("ã�� �̸��� �Է��ϼ���:\n"); 
	scanf("%s",buf);
	
	int index=search(buf);
	if(index==-1)
	printf("'%s' �� �������� �ʽ��ϴ�.\n",buf);
	else
		printf("%s\n",numbers[index]);
}

void status(){
	int i;
	for(i=0;i<n;i++){
		printf("%s  %s\n",names[i],numbers[i]);
	}
	printf("�� %d ��.\n",n);
}

void remover(){

	char buf[BUFFER_SIZE];
	printf("���� ��� �̸� �Է�\n"); 
	scanf("%s",buf);//���� ��� �Է¹ޱ� 
	
	int index=search(buf);/*�������� ������ -1�� ����*/ 
	if(index==-1){
		printf("'%s'�� �������� �ʽ��ϴ�.\n");
		return;
	}
	int j=index;
	for(;j<n-1;j++){
		names[j]=names[j+1];
		numbers[j]=numbers[j+1];
	}//�� ĭ�� ������ ��ܿ� 
	n--;
	printf("'%s'�� ���������� ���ŵǾ����ϴ�.\n",buf); 
}

void load(){
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	
	printf("���� �̸��� �Է��ϼ���:\n"); 
	scanf("%s",fileName);
	
	FILE *fp;
	
	fp=fopen(fileName,"r");
	if(fp=NULL){
		printf("���� �б⿡ �����Ͽ����ϴ�.\n");
		return;
	}
	
	while((fscanf(fp,"%s",buf1)!=EOF)){//���Ͽ� ���� ������ ������ �ݺ��Ͽ� �̸��� ��ȭ��ȣ�� �о �迭�� ����
	fscanf(fp,"%s",buf2);
	names[n]=strdup(buf1);
	numbers[n]=strdup(buf2);
	n++;
}
fclose(fp);
}

void save(){
	int i;
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];
	
	scanf("%s",tmp); //which is "as", discarded
	scanf("%s",fileName);
	
	FILE *fp;
	fp=fopen(fileName,"w");
	if(fp==NULL){
	printf("Open failed.\n");
	return;
}

	for(i=0;i<n;i++){
		fprintf(fp,"%s %s\n",names[i],numbers[i]);
	}
	fclose(fp);
}

void add(){
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	scanf("%s",buf1);
	scanf("%s",buf2);
	
	int i=n-1;
	while(i>=0&&strcmp(names[i],buf1)>0){
		names[i+1]=names[i];
		numbers[i+1]=numbers[i];
		i--;
	}
	names[i+1]=strdup(buf1);
	numbers[i+1]=strdup(buf2);
	n++;
	printf("%s �� ���������� �߰��Ǿ����ϴ�.\n",buf1); 
}

int search(char *name){
	int i;
	for(i=0;i<n;i++){
		if(strcmp(name,names[i])==0){
			return i;
		}
	}
	return -1;
}

