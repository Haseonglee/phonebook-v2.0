#include <stdio.h>

#include <string.h> 
//동적 메모리 할당은 힙에 저장
 
#define CAPACITY 100 //배열의 크기 
#define BUFFER_SIZE 20
//전역변수 ->deta section이라 불리는 메모리영역에 위치 
char *names[CAPACITY];//이름 저장  배열 인덱스를 이용하여 번호와 이름을 유지 
//캐릭터 포인터 타입의 배열 
//names 배열의 각 항에 이름 배열의(포인터)의 주소를 주어야함 
char *numbers[CAPACITY];//전화번호 저장 
//전화번호를 문자열로 다루는게 편함 

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
		
		printf("명령을 입력하세요\n");//명령을 선택받음
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
	printf("찾을 이름을 입력하세요:\n"); 
	scanf("%s",buf);
	
	int index=search(buf);
	if(index==-1)
	printf("'%s' 는 존재하지 않습니다.\n",buf);
	else
		printf("%s\n",numbers[index]);
}

void status(){
	int i;
	for(i=0;i<n;i++){
		printf("%s  %s\n",names[i],numbers[i]);
	}
	printf("총 %d 명.\n",n);
}

void remover(){

	char buf[BUFFER_SIZE];
	printf("지울 사람 이름 입력\n"); 
	scanf("%s",buf);//지울 사람 입력받기 
	
	int index=search(buf);/*존재하지 않으면 -1을 리턴*/ 
	if(index==-1){
		printf("'%s'는 존재하지 않습니다.\n");
		return;
	}
	int j=index;
	for(;j<n-1;j++){
		names[j]=names[j+1];
		numbers[j]=numbers[j+1];
	}//한 칸씩 앞으로 당겨옴 
	n--;
	printf("'%s'는 성공적으로 제거되었습니다.\n",buf); 
}

void load(){
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	
	printf("파일 이름을 입력하세요:\n"); 
	scanf("%s",fileName);
	
	FILE *fp;
	
	fp=fopen(fileName,"r");
	if(fp=NULL){
		printf("파일 읽기에 실패하였습니다.\n");
		return;
	}
	
	while((fscanf(fp,"%s",buf1)!=EOF)){//파일에 끝에 도달할 때까지 반복하여 이름과 전화번호를 읽어서 배열에 저장
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
	printf("%s 는 성공적으로 추가되었습니다.\n",buf1); 
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

