#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct subdomain {
	char* file;
	int count;
} subdomain_t;

int benson_index = 0;
int rigby_index = 0;
int mordecai_index = 0;

int benson_Total = 0;
int rigby_Total = 0;
int mordecai_Total = 0;


void Print(int index, int total, subdomain_t **Subs, char* subdomain) {

	printf("%s: %d\n",subdomain,total);
	for(int i = 0; i < index; i++){
		printf("\t%02d %s",Subs[i]->count,Subs[i]->file);
	};
	printf("\n");

}

void addFileToSubDomain(char* path, int key, subdomain_t **benson, subdomain_t **rigby, subdomain_t **mordecai) {

	int didAdd = 0;		//Flag for if a file has the count added to or not

	switch(key) {
	
		case 0:		//The key is for benson
			for(int i = 0; i < benson_index; i++){

				if (strcmp(benson[i]->file,path) == 0){
					
					benson[i]->count++;	//If file path matches any file paths already in benson
					benson_Total++;		//Add to the count and also the total count
					didAdd++;
					break;
				}
			
			}

			if (didAdd == 0){
				benson[benson_index] = malloc(sizeof(subdomain_t));		//Create new index
				subdomain_t *subdomain = malloc(sizeof(subdomain_t));		//Create subdomain
				benson[benson_index] = subdomain;				//Connect them
				subdomain->file = malloc(strlen(path));
				strncpy(subdomain->file,path,strlen(path));
				benson[benson_index]->count = 1;
				benson_index++;
				benson_Total++;
			}
			break;
		case 1:		//Same as other case just for rigby
			for(int i = 0; i < rigby_index; i++){

				if (strcmp(rigby[i]->file,path) == 0){		
					
					rigby[i]->count++;
					rigby_Total++;
					didAdd++;
					break;
				}
			
			}

			if (didAdd == 0){
				rigby[rigby_index] = malloc(sizeof(subdomain_t));
				subdomain_t *subdomain = malloc(sizeof(subdomain_t));
				rigby[rigby_index] = subdomain;
				subdomain->file = malloc(strlen(path));
				strncpy(subdomain->file,path,strlen(path));
				rigby[rigby_index]->count = 1;
				rigby_index++;
				rigby_Total++;
			}
			break;
		case 2:				//Same as other case just for mordecai
			
			for(int i = 0; i < mordecai_index; i++){

				if (strcmp(mordecai[i]->file,path) == 0){
					
					mordecai[i]->count++;
					mordecai_Total++;
					didAdd++;
					break;
				}
			
			}

			if (didAdd == 0){
				mordecai[benson_index] = malloc(sizeof(subdomain_t));
				subdomain_t *subdomain = malloc(sizeof(subdomain_t));
				mordecai[mordecai_index] = subdomain;
				subdomain->file = malloc(strlen(path));
				strncpy(subdomain->file,path,strlen(path));
				mordecai[mordecai_index]->count = 1;
				mordecai_index++;
				mordecai_Total++;
			}
			break;
	}

}
int EvaluateSubDomain(char* path){

	if (strncmp(path,"benson",6) == 0) {
		return 0;	//Key for benson
	}

	if (strncmp(path,"rigby",5) == 0) {
		return 1;	//Key for rigby
	}

	if (strncmp(path,"mordecai",8) == 0) {
		return 2;	//Key for mordecai
	}

}

int main (int argc, char* argv[]){


	char *buf = malloc(1024);
	int flag = 0;

	subdomain_t **mordecai;
	subdomain_t **rigby;
	subdomain_t **benson;

	benson = malloc(50 * sizeof(subdomain_t));
	rigby = malloc(50 * sizeof(subdomain_t));
	mordecai = malloc(50 * sizeof(subdomain_t));

	FILE *csv;

	csv = fopen("requests.csv","r");
	if(!csv) {
		printf("ERROR\n");
		return -1;
	}

	fgets(buf,1024,csv);

	while(fgets(buf,1024,csv)){
		char *token;
		token = strtok(buf, ",");	//Split on commas to get each field
		while(token != NULL) {

      			token = strtok(NULL, ",");

			if (token == NULL) {}

			else if (strncmp(token,"GET",3) == 0){		//Only grab the strings with "GET"
				token = strtok(NULL, ",");		
				token = token + 8;			//Removes the https://
				int subDomainKey = EvaluateSubDomain(token);
				token = strtok(token,"/");		//Split the path on /
				while(token != NULL){

					if((strchr(token, '.') != NULL) && (flag > 1)) {	//If it has a dot it means its a file
						addFileToSubDomain(token,subDomainKey,benson,rigby,mordecai);
  					}
					flag++;
					token = strtok(NULL, "/");
				}
				
			}
   		}
		flag = 0;
	}
	
	Print(benson_index,benson_Total,benson,"benson");
	Print(rigby_index,rigby_Total,rigby,"rigby");
	Print(mordecai_index,mordecai_Total,mordecai,"mordecai");

	return 0;
}
