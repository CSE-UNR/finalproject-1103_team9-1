//Authors: Kellen Strinden and Peter Hippert
//Date Due: 5/7/2024
//Purpose: CS 135 Final Project

#include <stdio.h>

#define MAX_RESOLUTION 100
#define DEFAULT_FILE "default.txt" //Added a default file
#define FILE_NAME "file.txt" //Added file for testing loadImage function
#define FILE_NAME_MAX 50

int mainMenu();
int editMenu();
int imgProcess(FILE* filePtr, int* imageX, int* imageY, int maxRes, int resultArray[][maxRes]);
void newImage(FILE* fp, int size);
void displayImage(int imageX, int imageY, int maxRes, int imgArray[][maxRes]);
void cropCurrentImage();
void dimCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]);
void brightenCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]);
//rotateCurrentImage();
void saveImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]);

int main(){
	//Variable Declaration
	int userChoice, editChoice, lengthX, lengthY, imgProcessTest, imageData[MAX_RESOLUTION][MAX_RESOLUTION], imageEdited[MAX_RESOLUTION][MAX_RESOLUTION];
	FILE* currentImage = fopen(DEFAULT_FILE, "r");
	
	//Default Image Verification and Processing
	if(currentImage == NULL){
		printf("Could not open default image file. Exiting Program.");
		return 0;
	}
	
	imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageData);
	
	//Main Program Handling
	printf("--------------------------------------------------\n");
	printf("Welcome!\n");
	printf("--------------------------------------------------\n");
	
	do{
		userChoice = mainMenu();
		
		switch(userChoice){
			case 1:
				//Load New Image
				fclose(currentImage);
				newImage(currentImage, FILE_NAME_MAX);
				imgProcessTest = imgProcess(currentImage, &lengthX, &lengthY, MAX_RESOLUTION, imageData);
				if(imgProcessTest == 1){
					currentImage = fopen(DEFAULT_FILE,"r");
				}
				break;
			case 2:
				//Display Current Image
				displayImage(lengthX, lengthY, MAX_RESOLUTION, imageData);
				break;
			case 3:
				//Edit Current Image
				editChoice = editMenu();
				
				switch(editChoice){
					case 1:
						//Crop Current Image
						cropCurrentImage(lengthX,lengthY,MAX_RESOLUTION,imageData,imageEdited);
						break;
					case 2:
						//Dim Current Image
						printf("Dimming Current Image...\n\n");\
						dimCurrentImage(lengthX, lengthY, MAX_RESOLUTION, imageData);
						displayImage(lengthX, lengthY, MAX_RESOLUTION, imageData);
						saveImage(lengthX, lengthY, MAX_RESOLUTION, imageData);
						break;
					case 3:
						//Brighten Current Image
						printf("Brightening Current Image...\n\n");\
						brightenCurrentImage(lengthX, lengthY, MAX_RESOLUTION, imageData);
						displayImage(lengthX, lengthY, MAX_RESOLUTION, imageData);
						break;
					case 4:
						//Rotate Current Image
						break;
					case 5:
						//Exit To Main Menu
						break;
					default:
						//Invalid Choice Handling
						printf("Invalid Choice. Returning to Main Menu.\n");
						printf("--------------------------------------------------\n");
						break;
				}
				
				break;
			case 4:
				//Exit Program
				printf("Goodbye!\n");
				printf("--------------------------------------------------\n");
				break;
			default:
				//Invalid Choice Handling
				printf("Invalid Choice. Please Try Again.\n");
				printf("--------------------------------------------------\n");
				break;
		}
	}while(userChoice != 4);
	
	return 0;
}

int mainMenu(){
	//Written by Peter Hippert
	int choice;
	printf("Please select an option:\n");
	printf("  1: Load Current Image\n");
	printf("  2: Display Current Image\n");
	printf("  3: Edit Image\n");
	printf("  4: Exit\n");
	printf("Choice: ");
	scanf("%d", &choice);
	printf("--------------------------------------------------\n");
	return choice;
}

int editMenu(){
	//Written by Kellen Strinden
	
	int result;
	
	//Prompts user to choose an editing option
	printf("Please select an option from the following:\n");
	printf("  1: Crop Current Image\n");
	printf("  2: Dim Current Image\n");
	printf("  3: Brighten Current Image\n");
	printf("  4: Rotate Current Image\n");
	printf("  5: Return to Main Menu\n");
	
	printf("Choice: ");
	scanf("%d", &result);
	printf("--------------------------------------------------\n");
	
	//Returns the integer value of the user's choice for menu logic
	return result;
}

int imgProcess(FILE* filePtr, int* imageX, int* imageY, int maxRes, int resultArray[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col, result;
	char tempArray[maxRes][maxRes];
	
	//Resets the image arrays to null state
	for(row = 0; row < maxRes; row++){
		for(col = 0; col < maxRes; col++){
			resultArray[col][row] = '\0';
		}
	}
	
	//Scans through the current file to get raw image data
	for(row = 0; row < maxRes; row++){
		fgets(tempArray[row], (maxRes + 1), filePtr);
	}
	
	//Calculates the image length and width
	for(row = 0; (tempArray[row][0] != '\0')&&(tempArray[row][0] != '\n'); row++){}
	*imageY = row;
	
	for(col = 0; (tempArray[0][col] != '\0')&&(tempArray[0][col] != '\n'); col++){}
	*imageX = col;
	
	/*for(row = 0; row < *imageY; row++){
    		for(col = 0; col < *imageX; col++){
      			printf("%c ", tempArray[row][col]);
    		}
    		printf("\n");
  	}*/
	
	
	//Processes the image into the desired format
	for(row = 0; row < *imageY; row++){
		for(col = 0; col < *imageX; col++){
		      	switch(tempArray[row][col]){
			        case '0':
			          resultArray[row][col] = 0;
			          break;
			        case '1':
			          resultArray[row][col] = 1;
			          break;
			        case '2':
			          resultArray[row][col] = 2;
			          break;
			        case '3':
			          resultArray[row][col] = 3;
			          break;
			        case '4':
			          resultArray[row][col] = 4;
			          break;
			        default:
			          //Returns a fail state for the function
			          return 1;
			          break;
			}
		}
	}
	
	return 0;
}

void newImage(FILE* fp, int size){
	//Written by Peter Hippert
	
	char fileName[size];
	
	printf("Enter file name:\n");
	scanf("%s", fileName);
	//printf("%s\n",fileName);
	
	fp = fopen(fileName, "r");
	
	if (fp == NULL){
		printf("Invalid File\n");
		printf("--------------------------------------------------\n");
		fp = fopen(DEFAULT_FILE, "r");
		return;
	}else if(fp != NULL){
		printf("File Loaded Successfully.\n");
		printf("--------------------------------------------------\n");
	}
}

void displayImage(int imageX, int imageY, int maxRes, int imgArray[][maxRes]){
	//Written by Peter Hippert
	
	for (int rowInd = 0;rowInd < imageX; rowInd++){
		for (int colInd= 0;colInd < imageY; colInd++){
			//printf("%c ",resultArray[rowInd][colInd]);
			switch(imgArray[rowInd][colInd]){
				case 0:
					printf("  ");
					break;
				case 1:
					printf(". ");
					break;
				case 2:
					printf("o ");
					break;
				case 3:
					printf("O ");
					break;
				case 4:
					printf("0 ");
					break;
				default:
					break;
			}
		}

		printf("\n");
	}
	
	printf("--------------------------------------------------\n");
}

void cropCurrentImage(int row,int column,int maxRes,int ogArray[][maxRes],int newArray[][maxRes]){
	int minCol,maxCol,minRow,maxRow;
	int rowCount=0,colCount=0;
	
	printf(" 1");
	for (int i = 0; i<(column-1)*2;i++){
		printf(" ");
	}
	printf("%d\n",row);
	printf("1 ");
	displayImage(row,column,MAX_RESOLUTION,ogArray);
	printf("%d\n",row);
	printf("The image you want to crop is %d x %d.\n",row,column);
	printf("The row and column values start in the upper lefthand corner.\n\n");
	printf("Which column do you want to be the new left side? ");
	scanf("%d",&minCol);
	printf("\nWhich column do you want to be the new right side? ");
	scanf("%d",&maxCol);
	printf("\nWhich row do you want to be the new top? ");
	scanf("%d",&minRow);
	printf("\nWhich row do you want to be the new bottom? ");
	scanf("%d",&maxRow);
	
	for (int i = minRow-1;i<maxRow;i++){
		colCount = 0;
		for (int j = minCol-1;j<maxCol;j++){
			newArray[rowCount][colCount] = ogArray[i][j]; 
			//printf("%d ",ogArray[i][j]);
			//printf("%d ",newArray[rowCount][colCount]);
			colCount++;
			//printf("%d ",colCount);
		}
		rowCount++;
		//printf("%d ",rowCount);
	}
	printf("\n");
	displayImage(rowCount,colCount,MAX_RESOLUTION,newArray);
	saveImage(rowCount,colCount,maxRes,newArray);
}

void dimCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col;

  	for(row = 0; row < lengthY; row++){
    		for(col = 0; col < lengthX; col++){
      			imgArray[row][col]--;

      			if(imgArray[row][col] < 0){
        			imgArray[row][col] = 0;
      			}
    		}
  	}
}

void brightenCurrentImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]){
	//Written by Kellen Strinden
	
	int row, col;

  	for(row = 0; row < lengthY; row++){
    		for(col = 0; col < lengthX; col++){
      			imgArray[row][col]++;

      			if(imgArray[row][col] > 4){
        			imgArray[row][col] = 4;
      			}
    		}
  	}
}

void saveImage(int lengthX, int lengthY, int maxRes, int imgArray[][maxRes]){
	//Written by Kellen Strinden
	
	char fileName[FILE_NAME_MAX], saveChoice;
	int row, col;
	
	printf("Would you like to save the edited image (Y/N): ");
	scanf(" %c", &saveChoice);
	switch(saveChoice){
		case 'Y':
		case 'y':
			printf("Enter the save file name: ");
			scanf("%s", fileName);
			
			FILE* saveFile = fopen(fileName, "w");
			
			for(row = 0; row < lengthY; row++){
				for(col = 0; col < lengthX; col++){
					fprintf(saveFile, "%d", imgArray[row][col]);
				}
				fprintf(saveFile, "\n");
			}
			fclose(saveFile);
			break;
		default:
			break;
	}
	
	printf("--------------------------------------------------\n");
}





