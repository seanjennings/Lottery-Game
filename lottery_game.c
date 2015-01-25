/* 
    Lotto Game Assignment
    Date: 13/03/2014
    Author: Seán Jennings
*/

#include <stdio.h>
#include <conio.h>

//Symbolic name for cases refering to the amount of chosen numbers
#define NUMBERS 6

/*Declare function prototypes*/
void readin(int*,int*);             //Function to read in 6 numbers chosen by user
void display(int*);                 //Function to display the 6 numbers chosen by user
void sort(int*);                    //Function to sort the 6 numbers chosen by user in ascending order (Bubble-Sort)
void compare(int*);                 //Function to compare the 6 numbers chosen by user against the array of winning numbers and display prizes(if any)
void frequency(int*,int*);          //Function to display how many times the 6 numbers chosen by user have been chosen before
void exit();                        //Function to exit the program gracefully

main()
{
    int chosen_numbers[NUMBERS];            //Array for chosen numbers
    int loop=1;                             //Variable to loop Menu
    int choice;                             //Variable for choice to be used in switch statement
    int check=0;                            //Variable to stop users choosing Options 2-5 without completing Option 1
    int history[42];                        //History Array - Each number's counter is it's value as the position in the array minus one
    int menu_error=0;                       //Variable for option input error checking                       
    
    //Initialise all number counters in history array to zero
    int i;
    
    for(i=0;i<42;i++)
    {
        *(history+i)=0;
    }
    
    //Loop to return to menu after each option in the switch statement is finished
    while(loop==1)
    {
        //Menu Text
        printf("\n==============\n");
        printf("   Main Menu\n");
        printf("==============\n");
        printf("\n:: Options ::\n");
        
        printf("\n1. - Choose Numbers");
        printf("\n2. - Display Chosen Numbers");
        printf("\n3. - Sort Chosen Numbers");
        printf("\n4. - Compare Chosen Numbers to Winning Numbers");
        printf("\n5. - Display Frequency of Chosen Numbers");
        printf("\n6. - Exit");
        
        //Read in menu option choice
        printf("\n\nChoose an Option: ");
        scanf("%d",&choice);
        flushall();
        
        //Switch statement to call the functions associated with each option
        switch(choice)
        {
            /*Read in 6 numbers and error check them*/
            case 1:
            {
                //Read in  6 numbers
                //Call function readin()
                readin(chosen_numbers,history);
                
                //Check variable to prevent users chosing subsequent options before choosing numbers
                check=1;    //Set to one to allow user to choose other options
                
                break;
            }//end case 1
            
            case 2:
            {
                //Display contents of 1D array
                if(check==1)
                {
                    //Call function display()
                    display(chosen_numbers);
                }
                break;
            }//end case 2
            
            case 3:
            {
                //Sort in ascending order
                if(check==1)
                {
                    //Call function sort()
                    sort(chosen_numbers);
                }
                break;
            }//end case 3
            
            case 4:
            {
                //Compare chosen numbers with winning numbers
                if(check==1)
                {
                    //Call function compare()
                    compare(chosen_numbers);
                }
                break;
            }//end case 4
            
            case 5:
            {
                if(check==1)
                {
                    //Call function frequency()
                    frequency(chosen_numbers,history);
                }
                break;
            }//end case 5
            
            case 6:
            {
                //Exit
                //Call function exit()
                exit();
                
                //Change Loop Variable to exit Main Menu Loop
                loop=0;
            }//end case 6
            
            default:
            {
                printf("\nInvalid Option Input.\n");
                menu_error=1;
                break;
            }//end default
            
        }//end switch()
        
        //If loop is going to continue
        if(loop!=0)
        {
            //Error message if option 2-5 chosen before option 1
            if(check==0 && menu_error==0)
            {
                printf("\nPlease choose numbers first.\n");
            }//end inner if()
            
            //Gracefully return to top of the menu afer the chosen option completes
            printf("\nPress enter to return to the main menu...");
            getchar();
            clrscr();
            
        }//end outer if()
        
        //Reset menu error check before looping
        menu_error=0;
        
    }//end while()
    
}//end main()

/*Implement function readin()*/
void readin(int *ptr,int *ptr_history)
{
    int error;
    int i;
    int j;
    int duplicate_counter;
    
    //Do while loop to repeat number entering process if there is any error
    do
    {
        error=0;
        
        printf("\nChoose six numbers(1-42): \n");
        
        //Read in one element at a time while entering it into the number history array
        for(i=0;i<NUMBERS;i++)
        {
            scanf("%d",&*(ptr+i));
            flushall();
        }//end for()
        
        //Catch All Error Checking for every number entered
        for(i=0;i<NUMBERS;i++)
        {
            //Number range error checking
            if(*(ptr+i)<=0 || *(ptr+i)>=43)
            {
                error=1;
            }//end if()
            
            //Reset duplicate counter for each new number
            duplicate_counter=0;
            
            for(j=0;j<NUMBERS;j++)
            {
                //Compare one element with every other and check for duplicates
                if(*(ptr+i)==*(ptr+j))
                {
                    duplicate_counter++;
                }//end if()
                
                //Increment if number is found again even after comparing against itself
                if(duplicate_counter>1)
                {
                    error=2;
                }//end if()
                
            }//end inner for()
            
        }//end outer for()
        
        //Display error messages based on the error number from the checking above
        if(error==1)
        {
            printf("\nInvalid Number Input. (1 - 42)\n");
        }//end if()
        
        else if(error==2)
        {
            printf("\nYou can only enter each number once.\n");
        }//end if()
        
        //If there are no errors in the user input, proceed to enter their numbers into the history array
        //Each number's counter is it's value as the position in the array minus one
        else
        {
            for(i=0;i<NUMBERS;i++)
            {
                (*(ptr_history+*(ptr+i)-1))++;
            }//end for()
        }
    }while(error>0);
}//end readin()

/*Implement function display()*/
void display(int *ptr)
{
    int i;
    
    printf("\nThe numbers you chose are: ");
    
    //Display the contents of the chosen array using the pointer
    for(i=0;i<NUMBERS;i++)
    {
        printf("%d ",*(ptr+i));
    }//end for()
    
    printf("\n");
}//end display

/*Implement function sort()*/
void sort(int *ptr)
{
    //Bubble Sort working with pointer to the array of chosen numbers
    int i, j, a;
    
    for (i = 0; i < NUMBERS; i++) 
    { 
        for (j = i + 1; j < NUMBERS; j++) 
        { 
            if (*(ptr+i) > *(ptr+j)) 
            { 
                a =  *(ptr+i); 
                *(ptr+i) = *(ptr+j); 
                *(ptr+j) = a;
            } 
        } 
    }
    
    //Message for user upon the sort option completing
    printf("\nNumbers sorted!\n");
}

/*Implement function compare()*/
void compare(int *ptr)
{
    //Array of winning numbers to compare chosen numbers against
    int winning_numbers[6]={1,3,5,7,9,11};
    int winning_bonus=42;
    
    int matched=0;          //Matched Numbers counter
    int bonus_matched=0;    //Matches Bonus counter
    
    int i,j;
    
    //Check all chosen numbers against winning array
    for(i=0;i<NUMBERS;i++)
    {
        for(j=0;j<NUMBERS;j++)
        {
            if(*(ptr+i)==*(winning_numbers+j))
            {
                matched++;
            }//end if()
            
            else if(*(ptr+i)==winning_bonus)
            {
                bonus_matched=1;
            }//end if()
        }
        
    }//end for()
    
    //Cinema ticket
    if(matched==3 && bonus_matched==1)
    {
        printf("\nYou win! You have won a Cinema ticket.\n");
        
    }//end if()
    
    //Night out && Weekend away
    else if(matched==4)
    {
        if(bonus_matched==0)
        {
            printf("\nYou win! You have won a Night out.\n");
            
        }//end if()
        
        else if(bonus_matched==1)
        {
            printf("\nYou win! You have won a Weekend away.\n");
            
        }//end inner else if()
        
    }//end outer else if()
    
    //Holiday && New car
    else if(matched==5)
    {
        if(bonus_matched==0)
        {
            printf("\nYou win! You have won a Holiday.\n");
        }//end if()
        
        else if(bonus_matched==1)
        {
            printf("\nYou win! You have won a New car.\n");
            
        }//end inner else if()
        
    }//end outer else if()
    
    //Jackpot
    else if(matched==6)
    {
        printf("\nYou win! You have won the Jackpot!\n");
        
    }//end else if()
    
    //Default if not enough numbers match the winning array
    else
    {
        printf("\nYou did not match enough numbers to win.\n");
        
    }//end else
}

/*Implement function frequency()*/
void frequency(int *ptr,int *ptr_history)
{
    int i;
    
    //Display each number and their corresponding counter in the history array
    for(i=0;i<NUMBERS;i++)
    {
        printf("\n%2d has been chosen %d time(s).",*(ptr+i),*(ptr_history+*(ptr+i)-1));
        
    }//end for()
    
    printf("\n");
}

/*Implement function exit()*/
void exit()
{
    printf("\nThanks for playing! \n\nPress enter to quit...");
    getchar();
}