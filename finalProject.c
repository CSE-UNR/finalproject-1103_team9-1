//Authors: Kellen Strinden and Peter Hippert
//Date Due: 5/7/2024
//Purpose: CS 135 Final Project

#include <stdio.h>

int mainMenu();
int editMenu();

int main(){
	//Variable Declaration
	int userChoice, editChoice;
	
	//Main Program Handling
	printf("--------------------------------------------------\n");
	printf("Welcome!\n");
	printf("--------------------------------------------------\n");
	
	do{
		userChoice = mainMenu();
		
		switch(userChoice){
			case 1:
				//Load New Image
				break;
			case 2:
				//Display Current Image
				break;
			case 3:
				//Edit Current Image
				editChoice = editMenu();
				
				switch(editChoice){
					case 1:
						//Crop Current Image
						break;
					case 2:
						//Dim Current Image
						break;
					case 3:
						//Brighten Current Image
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
	printf("1: Load Current Image\n");
	printf("2: Display Current Image\n");
	printf("3: Edit Image\n");
	printf("4: Exit\n");
	printf("Enter number of your choice: ");
	scanf("%d",&choice);
	printf("\n");
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
	
	//Returns the integer value of the user's choice for menu logic
	return result;
}





