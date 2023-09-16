/*
----------------------------------------------------------------------------------------------------------
Assignment 3
Name: Bassit Ilahi
Panther ID: 6328318
Course: COP4338 RVC 1231
Description: This program will take the words from an input file and sort these words. The sorted list 
			 is then printed to an outputfile if the user requested an outputfile. This program will also 
			 use command line arguments to determine how the output will be (standard, reversed or new output file)
Affirmation: I affrim that I, Bassit Ilahi, wrote this program without the help of any 
             people or sources from the internet. I, Bassit Ilahi, also certify that this work 
             is solely mine abiding to FIU's policies and guidelines.
             
----------------------------------------------------------------------------------------------------------
*/

//imported libraries 
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



// this struct definition is used to define the nodes for the doubly linked list that will be used to sort file
struct listNode {
    char* word;
    struct listNode* nextNode;
    struct listNode* previousNode;
};


// code for the defined function above. This function will insert the new node (word) so as to populate the sorted list
// also this function has input parameters as a list node and a char
void listNodeInsertion(struct listNode** referencingHeadNode, char* newWord) {
    // this is where the check is done to verify that the word is not in the list already
    struct listNode* current = *referencingHeadNode;
	
	// this loop until the list is empty 
    while (current != NULL) {
        if (strcmp(current->word, newWord) == 0) {
            return;
        }
		
		//reassignment of the node (word)in alphabethical order
        current = current->nextNode;
    }

    // a new node is created using the above defined struct 
    struct listNode* newNode = malloc(sizeof(struct listNode));
	
	// checks if the newly created node is null and if so, print an error message and exit 
    if (newNode == NULL) {
        fprintf(stderr, "newWord is null. Out of memory \n");
        exit(EXIT_FAILURE);
    }
	
	// using node pointer, assign the newNode with the word attained from sorting above
    newNode->word = strdup(newWord);
    newNode->previousNode = NULL;
    newNode->nextNode = NULL;

    // search the doubly linked list and verify where to insert the new word
    struct listNode* previousNode = NULL;
    current = *referencingHeadNode;
    while (current != NULL && strcmp(current->word, newWord) < 0) {
		
		// assign the previous node with the current node and then point the current node to the next node 
        previousNode = current;
        current = current->nextNode;
    }

    // the new node is inserted into the doubly linked list at the determined position
    if (previousNode == NULL) {
        *referencingHeadNode = newNode;
    } else {
        previousNode->nextNode = newNode;
        newNode->previousNode = previousNode;
    }
    newNode->nextNode = current;
    if (current != NULL) {
        current->previousNode = newNode;
    }
	
}// end listNodeInsertion function


// function used to print the doubly linked list 
// will print the list of sorted words and has input parameters as a list node and an int
void printList(struct listNode* head, int reverse) {
	
	// if the head was found to be null then we will exit this function (retunr)
	if (head == NULL) {
	return;
	}
	
	//if reverse(that is determined from parsing the command line if -d is entered) then the list will be printed in reverse. If no -d then the list will be printed alphabethically 
	if (reverse) {
		while (head->nextNode != NULL) {
			head = head->nextNode;
		}
		while (head != NULL) {
			printf("%s\n", head->word);
			head = head->previousNode;
		}
	} else {
		while (head != NULL) {
			printf("%s\n", head->word);
			head = head->nextNode;
		}
	}
	
}// end printList function	


// this funtion will free the memory of the list with an input parameter of a listNode struct
void releaseList(struct listNode* head) {
	while (head != NULL) {
		struct listNode* temp = head;
		head = head->nextNode;
		free(temp->word);
		free(temp);
	}
	
}// end releaseList function



// main method where main code is executed
int main(int argc, char *argv[]) {
	
    // variables that will be used to parse comman line arguments 
    int reverse = 0;
    char* inputFile = NULL;
    char* outputFile = NULL;

    // getopt is used to parse the command line 
    int opt;
    while ((opt = getopt(argc, argv, "do:")) != -1) {
        switch (opt) {
            case 'd':
                reverse = 1;
                break;
            case 'o':
                outputFile = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-d] [-o outputFile] inputFile\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // here we will check if an input file name is entered in the command line and if it is then we will assign that file name to the inputFile variable defined above
    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-d] [-o outputFile] inputFile\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        inputFile = argv[optind];
    }

    // we will use the FILE library to open the file with the name as assigned above 
    FILE* fileInputted = fopen(inputFile, "r");
    if (fileInputted == NULL) {
        fprintf(stderr, "Unable to open input file %s\n", inputFile);
        exit(EXIT_FAILURE);
    }

    // doubly linked list is created here 
    struct listNode* head = NULL;

    // we will read the words from the input file and inset them into the doubly linked list just created
    char buffer[100];
    while (fscanf(fileInputted, "%s", buffer) == 1) {
		
        // this for loop is used to covert the words to all lowercase as per instructions
        for (int i = 0; buffer[i]; i++) {
            buffer[i] = tolower(buffer[i]);
        }

        // insert word to list by calling listNodeInsertion function
        listNodeInsertion(&head, buffer);
    }

    // close fileInoutted (close file that was opened above)
    fclose(fileInputted);

    // if there was no output file mentioned from the command line, then the print list function is called with input parameters as head node and reverse (taken from command line if -d is present)
    if (outputFile == NULL) {
        printList(head, reverse);
		
	// otherwise, create an output file and assign that file with the name taken from the command line 
    } else {
        FILE* fileOutputted = fopen(outputFile, "w");
        if (fileOutputted == NULL) {
            fprintf(stderr, "Unable to open output file %s\n", outputFile);
            exit(EXIT_FAILURE);
        }

        printList(head, reverse);

		// close the file that was open to prevent data corruption (close fileOutputted)
        fclose(fileOutputted);
    }

    // call to the releaseList function that is used to free the memory of  the linked list that was created
    releaseList(head);

    return 0;
}// end main



	
