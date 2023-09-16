/*
----------------------------------------------------------------------------------------------------------
Assignment 2
Name: Bassit Ilahi
Panther ID: 6328318
Course: COP4338 RVC 1231
Description: This program calculates the salary of an employee given hours, hourly  rate and if there is
             a percentage increase along with a bonus. However, this program parses the command line to 
             attain these information, using getopt. It does not prompt user for inputs. 
Affirmation: I affrim that I, Bassit Ilahi, wrote this program without the help of any 
             people or sources from the internet. I, Bassit Ilahi, also certify that this work 
             is solely mine abiding to FIU's policies and guidelines.
             
----------------------------------------------------------------------------------------------------------
*/

//imported libraries list
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>


//main method where code is executed
int main(int argc, char **argv) {

    //variables for flags, parsing and calculations
	extern char *optarg;
	extern int optind;
	int c, err=0;
	int pflag = 0, hflag = 0, bflag = 0;
	int check;
  	int hours = 0;
	int bonus = 0;
 	int rate = 0;
 	int salary = 0;
 	float percentage = 0.0;

    //usage statement: this is the format which the command line will be inputted. This is static 
    //because this usage statment belongs to only this code 
	static char usage[] = "Usage: %s [-p] -h hours [-b bonus] hourlyrate\n";

    //this is where getopt is utilized inorder for us to parse the command line to extrapolate the 
    //needed information
	while ((check = getopt(argc, argv, "ph:b:")) != -1) {

        //switch statement that wil check the command line
        switch (check) {
        
            //checks if p is in the command line and will set pflag to 1 if there is 
            case 'p':
	  	        pflag=1;
                break;

            //checks if h is in the command line and will set hflag to 1 if there is 
            //also read the values next to h and asign them to hours variable 
            case 'h':
	  	        hflag=1;
                hours = atoi(optarg);
                break;

            //checks if b is in the command line and will set bflag to 1 if there is 
            //also read the values next to b and asign them to bonus variable 
            case 'b':
	 	        bflag=1;
                bonus = atoi(optarg);
                break;

            //checks if there is any unknown information in the command line and will display a message 
            case '?':
				err=1;
                printf("Unknown values present");
                break;

        }//end switch 
    }//end while

	//since h is manadatory, this statement checks if there is an h variable present in the comman line
	//if there is no h variable, we will output an error message and exit the program after outputting usage
	if(hflag == 0){
		fprintf(stderr, "%s: missing -h option\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);

	//otherwise, we would need atleast one argument from the command line. This else if checks if there 
	//is an argument and if not, it will output an error message and exit program after outputting usage
	}else if ((optind+1) > argc) {	
		fprintf(stderr, "%s: Please enter the hours and rate: \n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);

	//here we will check if there is no values inputted at command line and if there are no variables, exit program
	//after outputting usage
	}else if (err) {
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

	//check if the hours enetered in the command line is valid.
	//we will ouput an error message if the hours are less than 0 or if the hours are greater than 80 as per instructions
  	if (hours < 0 || hours > 80) {
		printf("Error. Hours cannot be more than 80 or less than 0.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
  	}


	//checks optind is greater than the argc and if so we will output an error message
  	if (optind >= argc) {
		printf("Error. Invalid Entry.\n");
  	}
	//assigns rate variable with the number read from the command line using optind.
	//also, converts this value to an int value, using atoi(), since it is read from a char 
  	rate = atoi(argv[optind]);



	//salary calculation
	salary = hours * rate;

	//checks the validity of the bonus entered. If bonus is negative then we will output an error message
	//if bonus is more than 50% of the salary then we will output an error also as per instructions 
	if (bonus < 0 || bonus > (salary * 0.5)) {
		printf("Error. Bonus cannot be more than half od salary.\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
 	}

	/*this statement checks if there is a percentage and a bonus in the command line
	//if so, we will add the bonus to the salary then we will calculate the percentage increase on that 
	new salary with bonus*/	
	if(pflag==1 && bflag==1){
		percentage = 0.10;
		salary = ((salary + bonus) + (salary * percentage));
	}

	//checks if there is a percentage and not a bonus and if so we will calculate the percentage increase
	//which is 10% of the salary and add it to the salary to get a new salary 
	if(pflag==1 && bflag == 0){
		percentage = 0.10;
		salary = (salary + (salary * percentage));
	}

	//checks if there is a bonus and not a percentage increase and if there is then we will simply 
	//add that bonus to the salary 
	if(bflag==1 && pflag==0){
		salary = salary + bonus;
	}


	/*for testing purposes only. Uncomment if you need to test the values read from command line

	printf("Hours: %f\n", (float)hours);
	printf("Rate: %f\n", (float)rate);
	printf("Percentage: %.3f\n", (float)percentage);
	printf("Bonus: %f\n", (float)bonus);
	*/
	

	//sets all the locale formatting 
	setlocale(LC_ALL, "");

	//print statement which outputs the correct calculated salary based on the input received from 
	//the command line. Type cast salary to a float also since initially it is being used as a int
	printf("The salary for this period is $%'.2f\n", (float)salary);

}//end main


