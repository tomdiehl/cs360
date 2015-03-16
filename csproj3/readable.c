#define _BSD_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#define MAXDIRSIZE 4096

int isDirectory(char *pathname){
	struct stat area, *s = &area;
	return(lstat(pathname,s)== 0) && S_ISDIR(s->st_mode);
}

int traverse(char* path){
	int isDir;
	DIR *newDir;
	struct dirent *dit;
	char newPath[MAXDIRSIZE];
	
	if(access(path,R_OK) < 0 ) return 0;
	isDir = isDirectory(path);
	if(!isDir){     				//is file	
	}
	else{ 				            //is directory
		newDir = opendir(path);	
		if(newDir < 0){
			fprintf(stderr,"%s", strerror(errno));
			exit(1);
		}
		while((dit = readdir(newDir)) != NULL){
			if((strcmp(dit->d_name,".") && (strcmp(dit->d_name,"..")))){
				strcpy(newPath,path);
				strcat(newPath,"/");
				strcat(newPath, dit->d_name);	
				if(isDirectory(newPath))printf("%s\n", newPath);
				traverse(newPath);
			}	
		}
		closedir(newDir);
	}
	return 0;
}

int main(int argc, char *argv[]){
	char *inDir;

	if(!argv[1]){
		inDir = getcwd(NULL, 4096);	
	}
	else inDir = argv[1];
	
	traverse(inDir);
	
	return 0;	
}

//if(){
//	fprintf(stderr,"", strerror(errno))
//	exit(1);
//}
