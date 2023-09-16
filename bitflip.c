/*
----------------------------------------------------------------------------------------------------------
Assignment 4
Name: Bassit Ilahi
Panther ID: 6328318
Course: COP4338 RVC 1231
Description: This program will output a new set of values based on the command the user inputs. These 
			 values would flip evenFlip, oddFlip or allFlip bits, switch bits around from right to left and 
			 output to a file instead of standard output.
Affirmation: I affrim that I, Bassit Ilahi, wrote this program without the help of any 
             people or sources from the internet. I, Bassit Ilahi, also certify that this work 
             is solely mine abiding to FIU's policies and guidelines.
             
----------------------------------------------------------------------------------------------------------
*/

//imported libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

//main method where code is executed
int main(int argc, char **argv){
	
	//variables that will be used to parse command
	int opt;
	int evenFlip = 0;
	int oddFlip = 0;
	int allFlip = 0;
	int rightLeftSwitch = 0;
	int flipValue = 0;
	
	//variable that will be used to store user input
	int userInput;
	
	//variables that will be used to store bits
	uint16_t inputConvertedBinary;
	uint16_t resultBinary;
	
	//char variable for output file
	char *outfile = NULL;
	int outputCreation = 0;
	
	
	//this is where getopt is utilized inorder for us to parse the command line to extrapolate the 
    //needed information (the request of the user)
	while ((opt = getopt(argc, argv, "efaso:")) != -1){
		
		//switch statement used to parse and assign values from the command line provided by user
		switch (opt) {
			case 'e':
				evenFlip = 1;
				break;
			case 'f':
				oddFlip = 1;
				break;
			case 'a':
				allFlip = 1;
				break;
			case 's':
				rightLeftSwitch = 1;
				break;
			case 'o':
				outputCreation = 1;
				outfile = optarg;
				break;
			default:
				fprintf(stderr, "Usage: %s [-e] [-f] [-a] [-s] [-o] [outfileName] userInput\n", argv[0]);
				exit(EXIT_FAILURE);
		}// end switch
	}//end while
	
	//checks if there is an input value for us to flip bits of. If not, prints an error message
	if (optind >= argc){
        fprintf(stderr, "Error. Try Again.");
        exit(EXIT_FAILURE);
    }
	
	//get user input from command line using optind and assign it to userInput variable
	userInput = atoi (argv[optind]);
	printf("Value: %d\n", userInput);
	
	
	//condition as to whihc the user input should be, if statement will check if userInput is between 
	//1 and 20000 if userInput is not, print error message
	if(userInput < 1 || userInput > 20000){
		fprintf(stderr, "Error: Value must be between 1 and 20000\n");
		exit(EXIT_FAILURE);
	}//end if
	
	
	//creation of the new file (output) using the filename from command line
	//prints an error message if the file was not created successfully
	FILE *file = outputCreation ? fopen(outfile, "w") : stdout;
		if(file == NULL){
			fprintf(stderr, "Unable to open file %s\n", outfile);
			exit(EXIT_FAILURE);
		}
	
	
	//converts the user input number to binary so we can process bits
	inputConvertedBinary = userInput;
	resultBinary = inputConvertedBinary;

	
	//flips the even bits if 'e' present in command line by iterating to very 2nd bits to get the even bits
	if(evenFlip){
		for(int i=0; i<16; i+=2){
			resultBinary ^= (1UL << i);
		}
		fprintf(file, "Even bits flipped: %d\n", resultBinary);
	}//end even if
	
	
	
	//flips the odd bits if 'f' present in command line
	if(oddFlip){
		for(int i=0; i<16; i++){
			resultBinary ^= (1UL << i);
		}
		fprintf(file, "Odd bits flipped: %d\n", resultBinary);
	}//end odd if
	
	
	//flips all the bit if 'a' present in command line using the hexadecimal of 0xFFFF and multiplying 
	//it by the input binary number then assigning it to the resultBinary variable
	if(allFlip){
		resultBinary = ~inputConvertedBinary; 
		fprintf(file, "All bits flipped: %d\n", resultBinary);
	}//end all if
	
	
	//switches the bits from right to left if 's' present in command line
	if(rightLeftSwitch){
		uint16_t switchBinary = 0;
		for (int i = 0; i < 16; i++) {
			switchBinary |= ((inputConvertedBinary>> i) & 1) << (15 - i);
		}
		fprintf(file, "Switched all bits: %d\n", switchBinary);
	}//end switch if
	
	
	//produces results in an output file if 'o' present in command line
	if(outfile){
		printf("Output file created successfully.\n");
		fclose(file); //writes to the file then closes it so as to prevent corruption or data loss
	}//end outfile if
	
	return 0;
}//end main

