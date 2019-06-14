#include <stdio.h>
#include <stdlib.h>
/*
This Program uses Switch-Case and Functions.
*/
void select(int x){                                               //Function to print selection
  int b;                                                          //Temporary Variable for Re-entry
  switch(x){                                                      //Define Switch variable
case 1:                                                           //Use cases to control selection flow of program
    printf("\nAn Apple a Day , Keeps the doctor away\n");
    b=scan();                                                     //Scan Again
    select(b);                                                    //Endless Input Loop - Recursion - Function calling itself
    break;
case 2:
    printf("\nApples to Oranges , eh?\n");                        // Print Message
    b=scan();
    select(b);
    break;
case 0:                                                           // Case to Exit Loop
    break;
default:
    printf("\nYou seem out of focus today.Try Again\n");          //In case input is out of range
    b=scan();                                                     //Scan Again
    select(b);
    break;
}}

int scan(){                                                       //Function to Scan Input - Return Type int
  int a;                                                          //This variable has scope only in this code block
  printf("\n\nChoose from following:\n1.Apples\n2.Oranges\n0.Exit\n");
  scanf("%d",&a);                                                 //Take User Input
  return a;
}

int main()                                                        // Comments can also be in-line
{                                                                 // Align all comments for readability
  int a;                                                          // Variable to store age , temp counter variable
  a = scan();                                                     // Use function to return value to variable
  select (a);
  return 0;                                                       // Return 0 to indicate successful execution
  }


