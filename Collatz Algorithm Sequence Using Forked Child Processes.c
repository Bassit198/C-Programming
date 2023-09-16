/*
Name: Bassit Ilahi

Panther ID: 6328318

Description: This program is to generate the Collatz Algorith sequence using forked child processes. This program will read an argument 
from the command line as the starting value for collatz conjecture. This argument would then be processed and 2 child processes are executed 
to achieve the collatz sequence. Finally, the collatz sequence is printed along with which child processes is running. 

Certification: I, Bassit Ilahi, certify that the submitted documents belongs to me and is the work of no other individual or sources. 
I certify that this work is my own and was not plagarized or replicated by any means. 
I affirm that this work does not fall into the category of plagarism as per abiding to FIU's guidelines and policies relating to plagarism.

Task 2: 
The processes does not always finish in the order which they are forked. This occurs due to the process scheduling policy for the OS. 
Since the CPU may be interrupted while executing these child processes, they will not finish in the order they were forked. 
Additionally, each process is allocated a core in the CPU when they are within the ready queue. So, if all the cores are allocated, and 
the child processes are forked, they will need to wait for a core. The order in which processes finish are not guaranteed but they are 
fully dependent on the process scheduling policy of that OS. These are the reasons as to why the processes will not finish in the 
order they were forked.
*/


//imported libraries 
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//this method will be used to apply the algotrithm of Collatz Conjecture
//this method takes 2 input, being: the input number recieved from the commmand line and the child number
void collatzAlgorithm(int input, int numberForChild) {
	
	//prints the necessary information and uses getpid() to get the process id currently running
    printf("From Child%d, pid=%d: number=%d\n", numberForChild, getpid(), input);
    
	//this while loop will run until 1 is returned. This is because the conjecture states that the algorithm 
	//is to be applied continuously until all positive reaches 1
    while (input != 1) {
		
		//checks if the number is positive and divide it by 2 if it is and if not then apply the arithmetic 
		//operation based on Collatz Conjecture
        if (input % 2 == 0) {  
            input = input / 2;
        } else {
            input = 3 * input + 1;
        }
        
		//prints the necessary information upon each iteration
        printf("From Child%d: number=%d\n", numberForChild, input);
    }
    
	//prints a message to let the user know that the child process is done exercuting with Collatz Conjecture
    printf("From Child%d, pid=%d: I'm done!\n", numberForChild, getpid());
}


//main method where driver code is executed
int main(int argc, char *argv[]) {
	
	//checks if any argument is made in the command line using argc
    if (argc != 2) {
        printf("Usage: ./collatz <number>\n");
        return 1;
    }
    
	//reads the number entered in the command line and converts it to an int assigned to the input variable
	//uses atoi from the stdlib.h library to convert the string (from the command line) into an integer
    int input = atoi(argv[1]);
    
	/*as per instructions, the number entered must be greater than 0 and less than 40
	this if statement handles this condition and if the number is outside of these parameters, will let 
	the user know via an error message*/
    if (input < 1 || input > 39) {
        printf("The input must be greater than zero and less than 40.\n");
        return 1;
    }
    
	
	//prints collatz and the number entered along with the message of the parrent is waiting
    printf("collatz %d\n\n", input );
    printf("This is the Parent waiting!\n");
    
	
	//variables definition for the children
	//pid_t is a signed integer type that can represent process ID hence we will use this data type for children 
    pid_t firstChild;
    pid_t secondChild;
    
	
	//first child is forked
    firstChild = fork();
    
	
    /*prints an error message if the child is not forked, but if the child is forked, we will call the 
	collatzAlgorithm function, passing the input number and the child numberr as the parameters (as described 
	above in function definition)*/
    if (firstChild < 0) {
        printf("Failed to fork firstChild.\n");
        return 1;
    } else if (firstChild == 0) {
        collatzAlgorithm(input, 1);
        exit(0);
    }
	
	
	//second child is forked
	secondChild = fork();
    
	
	/*prints an error message if the child is not forked, but if the child is forked, we will call the 
	collatzAlgorithm function, passing the input number and the child numberr as the parameters (as described 
	above in function definition)*/
    if (secondChild < 0) {
        printf("Failed to fork secondChild.\n");
        return 1;
    } else if (secondChild == 0) {
        collatzAlgorithm((input + 4), 2);
        exit(0);
    }
	
	
	//waiting twice so that the children can finish then the main program will finish 
    wait(NULL);
    wait(NULL);
    
	
	//lets user know the children is complete 
    printf("All my Children Complete\n");
    
    return 0;
	
}//end main