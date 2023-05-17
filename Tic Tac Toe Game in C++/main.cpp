#include <iostream>
#include<stdlib.h>
#include<chrono>
using namespace std;
using namespace std::chrono;
//  decalring the global variabbles  to  access in whole program
int r = 0;// initialize for the row of the  board
int c = 0;// inintialze for column of the board
int score = 0;
char player1 = 'X';
char player2 = 'O';
char draw = '/';
//creating  class for making easy to access memebr functions inside the class
//
class TicTacToe {
public:
    //  iassigned  x for playerand  o for computer  but we can choose which
    // we want  to take as player
    char player = 'X';
    char computer = '0';
    // the board  of  tic tac toe games is  3x3 multidimentional array or matrix
    // which  has three rows and three coluns and 9 space to moeve
    // it is squre  board
    char game_board[3][3];
    TicTacToe()
    {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //firstly it should be empty or
            // before making any  move in, field should  be empty
            game_board[i][j] = ' ';
        }
    }
    }
    // function to draw the board of the game which is 3x3
    //which is int rhe form of text based
    /*        A  B  C
     *         D  E  F
     *         G  H  I
     *  player need to press any letter of  board to make move
     */
    void draw_Board()
    {
    system("cls");
    cout << "Tic Tac Toe" << endl << endl << endl;
    for (int i = 0; i < 3; i++) {
        if (i)
            {
            std::cout << "---+---+---\n";
            }
        for (int j = 0; j < 3; j++) {
            if (j) {
                cout << "|";
            }
            std::cout << ' ';
            if (game_board[i][j] == ' ') {
                
                int ramesh = 3 * i + j + 1;
                char r;
                r = (char)ramesh + 64;// converting integer into uppercase ccharacter by adding 64
                cout << r;
            }
            else {
                cout << game_board[i][j];
            }
            cout << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
    }
    //the function to check either which player win  the game
    /* for winning
     *               0  1  2
     *               3  4  5
     *               6  7  8
     where winning state will be  when the player mover in straght line  like vertial or horizontal or diagonal
     if player  ove in  0  4 8  position  then it will win
     // if we  check all winging state  its  like 8x3 matrix
     */
    bool check_winning() {
        int win_states[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
        for (int i = 0; i < 8; i++) {
            bool check_winning = true;
            int first_r = win_states[i][0] / 3, first_c = win_states[i][0] % 3;
            for (int j = 0; j < 3; j++) {
                int r = win_states[i][j] / 3, c = win_states[i][j] % 3;
                //we need to check the field  is emopty  or not and iteratively check theevery  state of winning
                if (game_board[first_r][first_c] == ' ' || game_board[first_r][first_c] != game_board[r][c]) {
                    check_winning = false;
                }
            }
            if (check_winning)
                return true;
        }
        return false;
    }
    // aftering movinng all 9 space of board or no player win then
    // it need to delcare as game draw
    // for  that we need to check all space first and
    //check no player  win the game then we can declare the game draw
    bool check_draw()
    {
    if (check_winning())
        return false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game_board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
    }
    //for the player vs palyer mode we need to make the seperate move of  player
    // this function makes the first player  move in  baard and give turns to move
    //for other playeror computer
    void player1_move()
    {
    while (true)
        {
        cout << player1 << "turn: ";
        char turn;
        //we read the input as  capital character  but we need to convert it intor integer
        // according to ASCII, A=65 so to make it as 1 we  need to  decrease it by 64
        /* its  like
         A  B  C
         D  E  F
         G  H  I
         BUT
         after converting it
         1  2  3
         4  5  6
         7  8  9
         */
        cin >> turn;
        int p;
        p = (int)turn - 64;// converting  uppercase character into integer
        r = (p - 1) / 3;
        c = (p - 1) % 3;
        //when player move the field first we need  to check the
        //space  is field by palyer or emmty if the sopace is  emptythen
        // player can move  if not the n show error
        if (p >= 1 && p <= 9 && game_board[r][c] != 'X' && game_board[r][c] != 'O' && game_board[r][c] == ' ')
            {
            game_board[r][c] = player1;
            break;
            }
        else
            cout << "field is already field or wrong input! try again please!" << endl;
        }
    }
    //function for player 2 similarly as  player1
    void player2_move()
    {
    while (true)
        {
        cout << player2 << "turn: ";
        char play;
        cin >> play;
        int p;
        p = (int)play - 64;// convertinng uppercase  to integer
        r = (p - 1) / 3;
        c = (p - 1) % 3;
        //check for empty space
        if (p >= 1 && p <= 9 && game_board[r][c] != 'X' && game_board[r][c] != 'O' && game_board[r][c] == ' ') {
            game_board[r][c] = player2;
            break;
        }
        
        else
            cout << "field is already field or wrong input! try again please!" << endl;
        }
    }
    // to make the computer intelligent,   i implement minimax algortithm
    //reference:https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
    // the alogorithm  is  used form reference.
    // this algorithm  used recusion techniques for recurisive functions
    // which return best move to minimize the opponent winning chance
    int minimax(bool maximizing_player = true)
    {
    int  best_move = 0;
    if (check_winning()) {
        if (maximizing_player) {
            best_move = -1;
        }
        else {
            best_move = 1;
        }
        return best_move;
    }
    else if (check_draw()) {
        
        best_move = 0;
        return best_move;
    }
    
    best_move = maximizing_player ? -2 : 2;
    for (int i = 0; i < 3; i++)
        {
        for (int j = 0; j < 3; j++)
            {
            if (game_board[i][j] == ' ')
                {
                game_board[i][j] = maximizing_player ? computer : player;
                int board_state = minimax(!maximizing_player);// using recursive fucntion technique
                if (maximizing_player)
                    {
                    if (board_state > best_move)
                        {
                        best_move = board_state;
                        r = i;
                        c = j;
                        
                        }
                    }
                else
                    {
                    if (board_state < best_move) {
                        best_move = board_state;
                        r = i;
                        c = j;
                    }
                    }
                game_board[i][j] = ' ';
                }
            }
        }
    return best_move;
    }
    //function for computer move which use the minimax algorithm to move
    // after using minimax it become highly optimal move
    void computer_move()
    {
    int best_move = minimax();// functioned called
    game_board[r][c] = computer;
    }
    // function to design the mode to play with computer
    // opponent of the  computer will be human
    // computer moves according to human move
    void playwith_computer()
    {
    int computer_score = 0;
    int player_score = 0;
    while (true)
        {
        cout << "Which X|O: ";
        cin >> player;
        if (player == 'X' || player == 'O' || player == 'x' || player == 'o')
            {
            break;
            }
        else
            cout << "please enter either x or o to continue" << endl;
        }
    computer = player == 'X' ? 'O' : 'X';
    if (player == 'O')
        {
        computer_move();
        
        }
    //after first move  of computer the board should be redraw for human move so draw function called
    draw_Board();
    cout << "player turn!" << endl;
    while (true)
        {
        player1_move();
        draw_Board();
        if (check_winning())
            {
            std::cout << "Player wins!\n";
            player_score++;
            cout << "player score:" << player_score << endl;
            // if the player win then the games should exit
            break;
            }
        else if (check_draw())
            {
            cout << "Tie!\n";
            break;
            }
        cout << "Computer is making a move...\n";
        computer_move();
        draw_Board();
        if (check_winning())
            {
            cout << "Computer wins!\n";
            computer_score++;
            cout << "computer score:" << computer_score << endl;
            break;
            }
        else if (check_draw())
            {
            cout << "Tie!\n";
            break;
            }
        }
    }
    // function to playe the game with human to human or player toplayer
    // opponent of the one  pplayer will be  another  player
    void playwith_player()
    {
    int wining_ofPlayer1 = 0;
    int wining_ofPlayer2 = 0;
    while (true)
        {
        cout << "X|O: ";
        cin >> player1;
        // player can choose either x or o for making polayer
        if (player1 == 'X' || player1 == 'O' || player1 == 'x' || player1 == 'o')
            {
            break;
            }
        else
            cout << "please enter either x or o to continue" << endl;
        }
    player2 = player1 == 'X' ? 'O' : 'X';
    if (player1 == 'O') {
        player1_move();
    }
    draw_Board();
    while (true)
        {
        player2_move();
        draw_Board();
        if (check_winning())
            {
            cout << "Player1 wins!\n";
            wining_ofPlayer1++;
            cout << "player1 score:" << wining_ofPlayer1 << endl;
            break;
            }
        else if (check_draw())
            {
            cout << "Tie!\n";
            break;
            }
        
        player1_move();
        draw_Board();
        if (check_winning())
            {
            cout << "player2 wins!\n";
            wining_ofPlayer2++;
            cout << "player2 score:" << wining_ofPlayer2 << endl;
            break;
            }
        else if (check_draw())
            {
            cout << "Tie!\n";
            break;
            }
        }
    }
    //function  to show the  menu mode  for player to choose mode
    // it shows the mode 1. player Vs player
    //                   2. playerVs computer,
    void menu_player()
    {
    
    draw_Board();
    cout << "  1: Player Vs  player" << endl;
    cout << "  2: Player Vs Computer" << endl;
    cout << "do you wantto play:1|2" << endl;
    int c;
    cin >> c;
    if (c == 1)
        {
        cout << "player Vs player" << endl;
        playwith_player();
        }
    else if (c == 2)
        {
        cout << " player Vs computer" << endl;
        playwith_computer();
        
        }
    else
        cout << " wrong mode!! enter again....." << endl;
    }
    // function to measures the time  and  check
    void time_check()
    {
    bool whomoveFirst;
    time_point<steady_clock>start, end;
    duration<float>duration;
    
    player1_move();
    start = high_resolution_clock::now();
    player2_move();
    end = high_resolution_clock::now();
    duration = end - start;
    float time = duration.count() / 1000000;// converting the  microsecond to second
    if (time > 10)
        {
        cout << " the time  limit cross" << endl;
        cout << player1 << "win!!!!" << endl;
        exit(0);
        }
    
    }
    // function to restart the game again after either win  or loose or draw
    // which shoud  male empty space in all field and  allow to play again
    
    void restarting()
    {
    system("cls");// clearing the screen
    // after winning or lossing  we should ask player
    // do you  want to play again or no
    cout << "do you want to play again?(YES|NO):" << endl;
    char repeat;
    cin >> repeat;
    cout << "Tic Tac Toe" << endl << endl << endl;
    
    for (int i = 0; i < 3; i++)
        {
        for (int j = 0; j < 9; j++)
            {
            if (game_board[i][j] == ' ')
                {
                
                int ramesh = 3 * i + j + 1;
                char a;
                a = (char)ramesh + 64;
                game_board[i][j] = a;
                }
            }
        }
    cout << '\n';
    
    
    }
};

int main()
{
    // obejct  of  tictactoe  type iscreated  which  helps to access the all member function
    // of  class tic tac toe
    TicTacToe game;
    game.menu_player();
    return 0;
}
