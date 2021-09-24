// final_ine.cpp by Bright Ine
// This file can only work on a mac because I used the ncurses library
// It can be compiled on the terminal using:
// $ g++ -o game final_ine.cpp -lncurses
// I also included a textfile named hangrocky.txt which the game relies on to work

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fstream>
// game macros
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20
#define WORD_SIZE 20
#define maxinput 25

using namespace std;
//structure for words from text-file
struct DEFINE{
    char MAX[WORD_SIZE];
};

int main() {
    initscr();  // ncurses function to start window
    cbreak();   // ncurses fucntion to directly accept input without hitting enter
    noecho();   // ncurses function to hide user inout on console

    int offsetx, offsety;   // box window
    int i, j, looped, time, Aplayed = -1, won = 0;    // game loop variables
    char choice, rocky;
    char * tempword;
    char man[6][11] = { // char array for the hanged figure
        ' ', '-', ' ', '-', ' ', '-', ' ', '-', ' ', '-', ' ',
        '|', ' ', ' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', '|',
        '|', ' ', ' ', '\\',' ', '|', ' ', '/', ' ', ' ', '|',
        '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', '|',
        '|', ' ', ' ', '/', ' ', ' ', ' ', '\\',' ', ' ', '|',
        ' ', '-', ' ', '-', ' ', '-', ' ', '-', ' ', '-', ' ',
    };
    offsetx = (COLS - WORLD_WIDTH) / 2; // width of window created
    offsety = (LINES - WORLD_HEIGHT) / 2;   // height of window created

    WINDOW * win = newwin(WORLD_HEIGHT, WORLD_WIDTH, offsety, offsetx); // ncurses window function
    refresh();
    ifstream inputFile; // accessing text file
    inputFile.open("hangword.txt");  //function to call file
    DEFINE * words = new DEFINE [WORD_SIZE];
    
    box(win, 0, 0); // box function for game border
    mvwprintw(win, 1, 1, "Do you want to play a game?");
    mvwprintw(win, 2, 1,"Press (H) to play Hang Rocky");
    mvwprintw(win, 3, 1,"Press (Q) to Quit");
    mvwprintw(win, 4, 1,"Enter your choice (H - Q)");
        wrefresh(win);  // refresh window to reflect changes
    choice = toupper(wgetch(win));  // get char input
        wclear(win);    // clear window
    
    while(1){   // True fucntion for game loop
        if(choice == 'Q'){  // if player presses 'Q', break loop and quit the game
            box(win, 0, 0);
            mvwprintw(win, 1, 1, "Game Quit.");
            mvwprintw(win, 2, 1, "@Bright Ine 2017 ECE Game Project.");
            mvwprintw(win, 3, 1, "Press ENTER to Exit.");
                wrefresh(win);  // refresh window
            break;
        }
        if(choice == 'H'){  // if user presses 'H', start the game
            start_color();  // ncurses function for colour
            init_pair(1, COLOR_BLUE, COLOR_WHITE);  // declaring ncurses color pair
            box(win, 0, 0);
                wattron(win, A_UNDERLINE);  // switching on the underline attribute
            mvwprintw(win, 1, 1, "Welcome to Hang Rocky v. 1.0");
                wattroff(win, A_UNDERLINE); // switching off the underline attribute
            
                wattron(win, COLOR_PAIR(1));    // switching on the color attribute
            for(i = 0; i < 6; i++){ // print the man array
                for(j = 0; j < 11; j++){
                    mvwprintw(win, 2+i, 10+j, "%c", man[i][j]);
                }
            }
                wattroff(win, COLOR_PAIR(1));   // switching off the color attribute
            
            if(inputFile.is_open()){   //if file is open
                for(i = 0; i < WORD_SIZE; i++){
                    inputFile >> words[i].MAX;
                }
                mvwprintw(win, 9, 1, "Guess the word/phrase before Rocky gets hung :(");
                mvwprintw(win, 11, 1, " Press (A) to select Places on Campus");
                wrefresh(win);  // refresh window
                rocky = toupper(wgetch(win));
                wclear(win);    // clear window
                while(rocky != 'A'){  // input validation
                    box(win, 0, 0);
                    mvwprintw(win, 1, 1, "Invalid input!");
                    mvwprintw(win, 2, 1, " Press (A) to select Places on Campus");
                    wrefresh(win);  // refresh window
                    rocky = toupper(wgetch(win));
                    wclear(win);    // clear window
                }
                /* ***Main Game Play Loop*** */
                for(;;){
                    if(Aplayed == 19){  // maximum amount of gameplay
                        box(win, 0, 0);
                        mvwprintw(win, 1, 1, "Amazing!");
                        mvwprintw(win, 2, 1, "You have reached the maximum amount of gameplay");
                        mvwprintw(win, 3, 1, "Your total score was: ");
                        mvwprintw(win, 4, 1, "Played: %d Won: %d Percent won: %.2f%%", Aplayed+1, won, 100*(double)won/(double)(Aplayed+1));
                        mvwprintw(win, 6, 1, "Press any button to Quit.");
                        wrefresh(win);
                        rocky = getch();
                        wclear(win);
                        break;
                    }
                   Aplayed += 1;   // updated the number of times played
                    if(Aplayed >= 1)
                        box(win, 0, 0);
                    man[1][5] = man[2][5] = man[3][5] = man[4][7] = man[4][3] = man[2][7] = man[2][3] = ' ';
                    
                    time = 0;   //initializing time variable after first play
                    looped = 0; //initializing loooped variable after first play
                    char temp[maxinput];    // temp char variable to compare user input
                    char userinput[maxinput];   // char array to get user input
                    for(i = 0; i < maxinput; i++){  // initializing temp and userinput arrays
                        temp[i] = '_';
                        userinput[i] = ' ';
                    }
        
                    do{ // mini loop that continues till user fails or completes the game
                        box(win, 0, 0);
                        tempword = words[Aplayed].MAX;   // temporary char pointer to word structure
                            mvwprintw(win, 1, 1, "Level %d:", Aplayed+1);
                        switch(time){
                            case 1:
                                man[1][5] = 'O';
                                break;
                            case 2:
                                man[2][5] = man[3][5] = '|';
                                break;
                            case 3:
                                man[4][7] = '\\';
                                break;
                            case 4:
                                man[4][3] = '/';
                                break;
                            case 5:
                                man[2][7] = '/';
                                break;
                            case 6:
                                man[2][3] = '\\';
                                break;
                        }
                            wattron(win, COLOR_PAIR(1));    //switching on color attribute
                        for(i = 0; i < 6; i++){
                            for(j = 0; j < 11; j++){
                                mvwprintw(win, 2+i, 30+j, "%c", man[i][j]);
                            }
                        }
                            wattroff(win, COLOR_PAIR(1));   // switching off color attribute
                        for(i = 0; i < strlen(tempword); i++)
                            mvwprintw(win, 3, 1+i, "%c", temp[i]);
                        
                        if(looped >= 1) // prints letters used
                            mvwprintw(win, 4, 1, "Letters Used: ");
                        
                        for(i = 0; i <= looped; i++)  // prints the user inputs
                            mvwprintw(win, 4, 16+i, "%c", userinput[i]);
    
                        mvwprintw(win, 6, 1, "You have %d Guesses Left", 6-time);
                        
                        if(time == 6)   // maximum number of plays
                            break;
                        
                        mvwprintw(win, 7, 1, "Enter a letter: ");   // displays letters used
                            wrefresh(win); //refresh window
                        userinput[looped] = toupper(getch());
                            wclear(win);    // clear window
                        // input validation if user doesn't enter a letter
                        while(!( userinput[looped] >= 'A' && userinput[looped] <= 'Z' )){
                            box(win, 0, 0);
                            mvwprintw(win, 1, 1, "Wrong Input!");
                            mvwprintw(win, 2, 1, "Enter a letter: ");
                            userinput[looped] = toupper(getch());
                                wrefresh(win);  // refresh windows
                                wclear(win);    // clear window
                        }
                        // loop to compare user input to compare user input to word structure
                        for(i = 0; i < maxinput; i++){
                            for(j = 0; j < strlen(tempword); j++){
                                if(userinput[i] == tempword[j])
                                    temp[j] = userinput[i];
                            }
                        }
                        
                        time += 1;  // adds the loops
                        
                        for(i = 0; i <= maxinput; i++){
                            if(temp[i] == userinput[looped]){
                                time-=1;
                                break;
                            }
                        }
                        
                        looped += 1;    // number of times a game has been played
                        
                        int x = time;
                        for(j = 0; j < strlen(tempword); j++){  // list _ for words
                            if(temp[j] != '_')
                                time = 7;
                            else if(temp[j] == '_'){
                                time = x;
                                break;
                            }
                        }
                        
                    }while(time != 7);
                    
                    if(time == 6){  // if player fails to guess word
                        mvwprintw(win, 7, 1, "Sorry, you have been hanged!");
                        mvwprintw(win, 8, 1,"The answer was: %s", tempword);
                    }
                    else{   // if player guessed the word correctly
                        box(win, 0, 0);
                            mvwprintw(win, 1, 1,"Level %d:", Aplayed+1);;
                        for(i = 0; i < 6; i++){
                            for(j = 0; j < 11; j++){
                                mvwprintw(win, 2+i, 30+j,"%c", man[i][j]);
                            }
                        }
                        
                        for(i = 0; i < strlen(tempword); i++)   // display user inputs
                            mvwprintw(win, 3, 1+i, "%c", temp[i]);
                        
                        if(looped >= 1)
                            mvwprintw(win, 4, 1, "Letters Used: "); // display letters used
                        for(i = 0; i <= looped; i++)
                            mvwprintw(win, 4, 16+i, "%c", userinput[i]);
                        mvwprintw(win, 8, 1, "Congratulations you have gotten the answer!");
                        won += 1;
                    }
                    mvwprintw(win, 9, 1,"Played: %d Won: %d Percent won: %.2f%%", Aplayed+1, won, 100*(double)won/(double)(Aplayed+1)); // Game Performance
                    mvwprintw(win, 12, 1,"Press (P) to play again");    // if player wants a second turn
                    mvwprintw(win, 13, 1,"Press (Q) to Quit");  // if player want's to quit game
                        wrefresh(win);
                    choice = toupper(getch());
                        wclear(win);
                    while(choice != 'P' && choice != 'Q'){  // input validation
                        box(win, 0, 0);
                        mvwprintw(win, 2, 1, "Invalid Input!");
                        mvwprintw(win, 4, 1,"Press (P) to play again");
                        mvwprintw(win, 5, 1,"Press (Q) to Quit");
                        wrefresh(win);
                        choice = toupper(getch());
                        wclear(win);
                    }
                    if(choice == 'Q')
                        break;
                }
                box(win, 0, 0); // window border
                mvwprintw(win, 1, 1,"Thanks for playing.");
                mvwprintw(win, 2, 1,"@Bright Ine 2017 ECE Game Project.");
                mvwprintw(win, 3, 1,"Press ENTER to Exit.");
                    wrefresh(win);  // refresh window
                break;
            }
            else{   // if file isn't open, quit the game
                box(win, 0, 0);
                mvwprintw(win, 1, 1,"File missing, aborting game.");
                mvwprintw(win, 3, 1,"You are missing a file of name **hangword.txt**");
                mvwprintw(win, 5, 1,"Locate it, place it next to the program file and  reload the game.");
                mvwprintw(win, 6, 1,"Press ENTER to Exit.");
                    wrefresh(win);
                    break;  // break main game loop
            }
        }
        if((choice != 'H')){   // Input validation if user doesn't enter 'H' or 'Q'
            box(win, 0, 0);
            mvwprintw(win, 1, 1,"Invalid Input!");
            mvwprintw(win, 2, 1,"Press (H) to play Hang Rocky");
            mvwprintw(win, 3, 1,"Press (Q) to Quit");
            mvwprintw(win, 4, 1,"Enter your choice (H - Q)");
                wrefresh(win);  //refresh window
            choice = toupper(getch());
                wclear(win);    // clear window
        }
    }
    
    getch();    // get enter to quit
    endwin();   // close window
    return 0;
}
