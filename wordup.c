// Date: Apr.29,2025
// Author: Shota Kida
// Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>
#define SIZE 10

void getWord(FILE *fp1, char word[]){
	fp1 = fopen("mystery.txt", "r");

	if(fp1 == NULL){
		printf("Can't open file\n");
	}else{
		fscanf(fp1, "%s", word);
		fclose(fp1);
	}
}

void checkLength(char userImp[], int *letterCount, int itrCount, _Bool *isValid1){
	*isValid1 = 1;
	*letterCount = 0;
	for(int i = 0; i < SIZE; i++){
		if(userImp[i] != '\0'){
			(*letterCount)++;
		}
	}
	//printf("%d", *letterCount);
	if(*letterCount != 5){
		printf("Your guess must be 5 letters long.");
		*isValid1 = 0;
		//printf("isValid1: %d", *isValid1);
	}else{
		*isValid1 = 1;
		//printf("isValid1: %d", *isValid1);
	}
}

int checkLetter(char userImp[], int letterCount, int itrCount, _Bool isValid2){
	isValid2 = 1;
	for(int i = 0; i < letterCount; i++){
		if(userImp[i] < 97 || 122 < userImp[i]){
			printf("Your guess must contain only letters.");
			//printf("has non letter.");
			isValid2 = 0;
			break;
		}
	}
	return isValid2;
}

_Bool checkIfCorrect(char userImp[], char word[], int itrCount){
	_Bool isCorrect = 1;
	for(int i = 0; i < 5; i++){
		if(userImp[i] != word[i]){
			isCorrect = 0;
		}
	}
	return isCorrect;
}

void dispHint(char word[], char userImp[][SIZE], int letterCount, char hint[][SIZE], int itrCount){
	_Bool is[5];

	//check if there is correct letter and if the userImp include a letter of the answer
	for(int i = 0; i < 5; i++){
		if(userImp[itrCount - 1][i] == word[i]){
			is[i] == 1;
			userImp[itrCount - 1][i] = userImp[itrCount - 1][i] - 32;
			hint[itrCount - 1][i] = ' ';
		}else{
			is[i] == 0;
			if((userImp[itrCount - 1][i] == word[0]) || 
			   (userImp[itrCount - 1][i] == word[1]) || 
			   (userImp[itrCount - 1][i] == word[2]) || 
			   (userImp[itrCount - 1][i] == word[3]) || 
			   (userImp[itrCount - 1][i] == word[4])){
				hint[itrCount - 1][i] = '^';
			}else{
				hint[itrCount - 1][i] = ' ';
			}
		}
	}

	//disp hint
	for(int i = 0; i < itrCount; i++){
		printf("%s\n", userImp[i]);
		printf("%s\n", hint[i]);
	}
}

void lastComment(char word[], int itrCount){
	printf("		%s\n", word);
	printf("	You won in %d guesses!\n", itrCount);

	switch(itrCount){
		case 1:
			printf("		GOATED!\n");
			break;
		case 2: case 3:
			printf("		Amazing!\n");
			break;
		case 4: case 5:
			printf("		Nice!\n");
			break;
		case 6:
			break;
	}
}

int main(){
	int itrCount = 1, letterCount;
	char word[SIZE], userImp[6][SIZE], hint[6][SIZE];
	_Bool isCorrect = 1, isValid1, isValid2;
	FILE *fp1;

	getWord(fp1, word);

	do{
		printf("GUESS %d! Enter your guess: ", itrCount);
		scanf("%s", &userImp[itrCount - 1]);
		
		for(int i = 0; i < 5; i++){
			if(word[i] == userImp[itrCount][i]){
				userImp[itrCount][i] - 32;
			}
		}

		//valid check
		checkLength(userImp[itrCount - 1], &letterCount, itrCount, &isValid1);
		isValid2 = checkLetter(userImp[itrCount - 1], letterCount, itrCount, isValid2);
		if(isValid1 == 0 || isValid2 == 0){
			printf("\n");
		}

		//if the input is invalid
		while(!isValid1 || !isValid2){
			printf("Please try again: ");
			scanf("%s", &userImp[itrCount - 1]);
			checkLength(userImp[itrCount - 1], &letterCount, itrCount, &isValid1);
			isValid2 = checkLetter(userImp[itrCount - 1], letterCount, itrCount, isValid2);
		}

		printf("================================\n");

		isCorrect = checkIfCorrect(userImp[itrCount - 1], word, itrCount);
		if(!isCorrect){
				dispHint(word, userImp, letterCount, hint, itrCount);
		}else{
			lastComment(word, itrCount);
			return 0;
		}
		itrCount++;

	}while(isCorrect == 0 && itrCount <= 6);
	return 0;
}
