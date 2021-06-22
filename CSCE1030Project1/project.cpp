/**
    @file (filename)
    @author (author name)
    This program is implementation of simple guess game where user to guess number
    2D matrix if any number matches then the user wons the game otherwise the user 
    loses the game, user will get 5 chances to guess.
*/

#include<bits/stdc++.h>
using namespace std;

/** Size of the 2D matrix to be used */ 
#define SIZE 5

/**
    Program to display the 2D matrix on console
    @param output the 2D matrix which will be displayed on console and from where
    the user have to guess
    @return program returns void 
 */ 
void dis_board(int output[SIZE][SIZE])
{
    //Get the current row
    for(int i=0;i<SIZE;i++)
    {
        //Iterate over the columns of the row
        for(int j=0;j<SIZE;j++)
        {
            cout<<output[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

/**
    Program to take input of location and check if they are valid or not.
    @param posX number of rows of the 2D matix
    @param posY number of columns of the 2D matrix
    @param checkLocation bool variable to check if current position have element
    before hand
    @param output the 2D matrix which the hold the current elements included the 
    guessed element by the user
    @return void
*/
void guessLocation(int *posX,int *posY,bool checkLocation,int output[][SIZE])
{
    //Keep taking input taking the input given by user is correct
    while(1)
    {
        //If the output has data given by the user before hand
        if(!checkLocation)
        {
            cout<<"Enter co-ordinates to reveal: ";
        }
        else{
            cout<<"Guess the co-ordinates to reveal: ";
        }

        // Take the input positions from user
        cin>>*posX>>*posY;

        //To check if the current position is valid or not
        if( *posX>=SIZE or *posY>=SIZE or *posX<0 or *posY<0 )
        {
            cout<<"Co-ordinate are out of range. Please enter again\n";
        }
        else if(checkLocation and output[*posX][*posY]!=-1)
        {
            cout<<"You've already selected this point. Please enter again\n";
        }
        else{
            return ;
        }
    }
}


/**
    Program Starting point, implementation of the 2D matrix game
    @return 0
*/
int main()
{
    //Displays the user information
    cout<<"+-------------------------------------------------------+\n";
    cout<<"|          Computer Science and Engineering             |\n";
    cout<<"|           CSCE 1030  - Computer Science  I            |\n";
    cout<<"|      Student Name      EUID    euid@my.unt.edu        |\n";
    cout<<"+-------------------------------------------------------+\n";

    //Sets the seed time
    srand(time(0));
    
    //Declaration of the hidden and output 2D matrix
    int output[SIZE][SIZE],hidden_board[SIZE][SIZE];

    //Character variable for taking the input from user for continuation of program
    char ch;
    
    //To check if user wants to continue
    int inputYes;

    //variables to find the percentage user win rate
    float numberOfGames=0,numberOfWon=0;

    do{
        //Increments that how many games user have played
        numberOfGames++;

        //The number of times user can guess
        int cnt=SIZE;

        //Loop to set initial values in hidden and output board
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                output[i][j]=-1;
                hidden_board[i][j]= (rand()%25)+1 ;
            }
        }
        
        //Display the current position on console
        dis_board(output);

        //Positon of x and y coordinate of 2D matrix
        int posX,posY;

        //Sets of inputs user have already guessed to save them in map
        unordered_map<int,int>elementsSoFar;

        //While user have chance to guess
        while (cnt--)
        {
            // cnt==4 means it's first guess
            if(cnt==4)
            {
                guessLocation(&posX,&posY,false,output);
            }
            else{
                guessLocation(&posX,&posY,true,output);
            }

            //Check if user have found any same pair
            bool correct=false;

            //Checks if number at position is already present
            if( elementsSoFar.find(hidden_board[posX][posY]) != elementsSoFar.end())
            {
                numberOfWon++;
                cout<<"you gussesd Correctly. You win\n";
                correct = true;
            }
            else
            {
                elementsSoFar[hidden_board[posX][posY]];
                cout<<"Incorrect. you have "<<cnt<<" guesses remaining.\n";
            }

            //Set the current value to output board
            output[posX][posY] = hidden_board[posX][posY];

            //Displays the board
            dis_board(output);

            //If user have foubd the correct answer break;
            if(correct)
            {
                break;
            }
        }

        //Asks the user if he wants to play more
        cout<<"Press y or Y to play another game. Any other character to stop:";

        //Takes the character input from character for continuation
        cin>>ch;

        //Checks if input by user the y 
        if(ch=='y' or ch=='Y')
        {
            inputYes = 1;
        }
        else{
            inputYes=0;
            cout<<"\n";
        }

     //checks if inputYess==1 the continue else user don't want to play   
    }while (inputYes==1);

    //Display the win rate percentage of the user
    cout<<"You won "<<fixed<<setprecision(2)<<(numberOfWon*100)/numberOfGames<<"% of the games. Goodbye!!!\n";
    
    //program executed currectly then return 0
    return 0;
}