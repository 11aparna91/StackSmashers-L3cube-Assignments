/******************************************************************
*Author: StackSmashers                                            *
*Title : Simple Version control                                   *
*Notes: use of Diff and Patcher is done.                          *  
******************************************************************/

#include<stdio.h>
#include<stdlib.h>
//for checking wheather directory present
#include<sys/types.h>
#include<sys/stat.h>

#include<string.h>
#include<ctype.h>

//counter is used is restore is done then counter is set to 'Zero'
//last commit points to where the last restore has been done
//so that the patches can be created from that point
char file_name[30];
int last_commit,total_commit,counter;

void init();
int make_commit();
void restore_commit(char *);
int get_head_version(int );
int main(int argc,char *argv[])
{
	
	struct stat s;
	char str[100];
	int is_versioned = stat("./svc",&s);
	int is_commit,i=0;
	
	if(argc==1){
		printf("\n\tUsage :\n\tTo commit - ./svc.o file.text\n\tTo restore ./svc.o VERSION_NUMBER ");
		return 0;
	}
//if this is 1st commit then if will get executed and it will create required directories and files
	if(!S_ISDIR(s.st_mode)){
		if(fopen(argv[1],"r")!=NULL){
			system("mkdir svc");
			system("cd svc && touch head manifest && mkdir commit ");
			system("cd svc && echo 0 > manifest");
			strcpy(str,"cd svc && echo ");
			strcat(str,argv[1]);
			strcat(str," >> manifest && echo 0 >> manifest && echo 1 >> manifest");
			system(str);
			strcpy(str,"cp ");
			strcat(str,argv[1]);
			strcat(str," svc/head");
			system(str);
			strcpy(str,"cp ");
			strcat(str,argv[1]);
			strcat(str," svc/commit/0.text");
			system(str);
			return 0;
		}
		else{
			printf("\n\t%s file not found ",argv[1]);
			printf("\n\tUsage :\n\tTo commit - ./svc.o file.text\n\tTo restore ./svc.o VERSION_NUMBER ");
			return 0;
		}
	}
	init();
	is_commit=1;				//this loops check whether to commit or to restore
	while(argv[1][i]!='\0'){		//if there is commit we specify .text file thus using '.' it recognizes that it needs to commit
		if(argv[1][i]=='.'){
			is_commit=0;
			break;
		}
		i++;
	}
	
	if(is_commit==0){
		make_commit(argv[1]);
	}
	else if(is_commit==1){
		if(!isdigit(argv[1][0])){		//validation
			printf("\n\tUsage :\n\tTo commit - ./svc.o file.text\n\tTo restore ./svc.o VERSION_NUMBER ");
			return 0;
		}
		if(atoi(argv[1]) > total_commit){
			printf("\n\tVersion till %d available \n\tUnable to restore",total_commit);
			return 0;
		}
		restore_commit(argv[1]);
	}
	return 1;
}

void init()
{
	char str[100];				//load data from manifest file to respective fields
	FILE *fp=fopen("svc/manifest","r");	
	fgets(str,100,fp);
	total_commit=atoi(str);
	fgets(file_name,100,fp);
	file_name[strlen(file_name) - 1]='\0';
	fgets(str,100,fp);
	last_commit=atoi(str);
	fgets(str,100,fp);
	counter=atoi(str);

}


int make_commit(char *argv)			//function which commits
{
	char str[100],str_version[10],str_head_version[10];
	int version,head_version;	
	total_commit++;				//increment total_commit pointer
	sprintf(str_version,"%d",total_commit);
	if(counter==0){				//counter = 0 means file have been restored in last operation
		strcpy(str,"echo ");		//so directy copy file contents to version.text file in svc/commit folder
		strcat(str,str_version);	//update manifest file 
		strcat(str," > svc/manifest");
		system(str);
		strcpy(str,"echo ");
		strcat(str,file_name);
		strcat(str," >> svc/manifest");
		system(str);
		strcpy(str,"echo ");
		strcat(str,str_version);
		strcat(str," >> svc/manifest");				
		system(str);
		system("echo 1 >> svc/manifest");
		strcpy(str,"cp ");
		strcat(str,argv);
		strcat(str," svc/commit/");
		strcat(str,str_version);
		strcat(str,".text");
		system(str);	
	}
	else{							//if file has not been restored then make a version.patch file from last restored file
		sprintf(str_head_version,"%d",last_commit);
		strcpy(str,"diff -u svc/commit/");
		strcat(str,str_head_version);
		strcat(str,".text ");
		strcat(str,argv);
		strcat(str," > svc/commit/");
		strcat(str,str_version);
		strcat(str,".patch");
		system(str);

		strcpy(str,"echo ");			//update the manifest
		strcat(str,str_version);
		strcat(str," > svc/manifest");
		system(str);
		strcpy(str,"echo ");
		strcat(str,file_name);
		strcat(str," >> svc/manifest");
		system(str);
		strcpy(str,"echo ");
		strcat(str,str_head_version);
		strcat(str," >> svc/manifest");				
		system(str);
		counter++;
		sprintf(str_head_version,"%d",counter);
		strcpy(str,"echo ");
		strcat(str,str_head_version);
		strcat(str," >> svc/manifest");				
		system(str);
	}
}	

void restore_commit(char *argv)
{
	
	char str[100],str_version[10],str_head_version[10];
	int version = atoi(argv);
	int head_version = get_head_version(version);
	sprintf(str_version,"%d",version);
	sprintf(str_head_version,"%d",head_version);
	if(version == head_version){			//if head verison and version required are same
		strcpy(str,"cp svc/commit/");		//then copy the contents from version.text to head file under svc folder
		strcat(str,str_version);
		strcat(str,".text svc/head");
		system(str);		
	}
	else{						//else copy head_version file to svc/head file and then patch with version.patch
		strcpy(str,"cp svc/commit/");		
		strcat(str,str_head_version);
		strcat(str,".text svc/head");
		system(str);
		strcpy(str,"patch svc/head svc/commit/");
		strcat(str,argv);
		strcat(str,".patch");
		system(str);	
		
	}
	strcpy(str,"rm ");			//then copy its content to our_file.text
	strcat(str,file_name);
	system(str);
	strcpy(str,"touch ");
	strcat(str,file_name);
	system(str);
	strcpy(str,"cp svc/head ");
	strcat(str,file_name);
	system(str);		
		
}

int get_head_version(int version)		//get head version so that it can be patched
{						//logic is to find .text file in reverse order from our required verison
	FILE *fp=NULL;
	char str[100],str1[100];
	while(version >= 0){
		strcpy(str,"svc/commit/");
		sprintf(str1,"%d",version);
		strcat(str,str1);
		strcat(str,".text");
		fp=fopen(str,"r");
		if(fp!=NULL)
			return version;	
		version--;
	}	
	return 0;	
}
