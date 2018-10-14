/*********************************************************************
	Name : Jack Mullen
	Date: April 26, 2018
	Description: Implementation for the mancala.h class. Includes a constructor, making moves, checking if the move is legal, displaying the status, evaluating the current
	winner, "cloning" the board, and now an AI that will play  the computer's move.
**********************************************************************/


#include "mancala.h"
#include "colors.h"
#include <climits>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>
using namespace std;
using namespace main_savitch_14;

Mancala::Mancala(){
	for(int j = 0; j < 14; j++){
		if(j == 6 || j == 13){//players "point" bins at 6 and 13
			board[j] = 0;
		}
		else{
			board[j]= 4;
		}
	}
}

Mancala::~Mancala(){//nothing to deconstruct
	//
}

void Mancala::make_human_move( ){
        std::string move;
	move = get_user_move( );
	while (!is_legal(move))
	{
	    display_message("Illegal move.\n");
	    move = get_user_move( );
        }
	make_move(move);
    }

bool Mancala::is_legal(const std::string& move)const{
	int intmove;
	std::stringstream s(move);
	s >> intmove;

    if(next_mover() == HUMAN){//for human
        intmove -=1;
        if(board[intmove] != 0){
            if(intmove >= 0 && intmove <= 5){
                return true;
            }
        }
    }
    if(next_mover() == COMPUTER){//for computer
        intmove = -intmove + 13;
        if(board[intmove] != 0){
            if(intmove >= 7 && intmove <= 12){
                return true;
            }
        }
    }
    return false;
}

void Mancala::make_move(const std::string& move){
	int intmove = 0;
    int curpos = 0;
	stringstream s(move);
	s >> intmove;

	if(next_mover() == HUMAN){//human's move
		intmove -= 1;
		int hand = board[intmove];
		board[intmove] = 0;

		for(int i = 1; hand > 0; i++){
		        curpos = intmove + i;
		    if((curpos) == 13){//if at computer's bin
		        //skip
		    }
		    else if((curpos) >= 14){//if beyond array size
		        i = (-intmove);
		        curpos = intmove + i;
		        hand -= 1;
		        board[curpos] += 1;
		    }
		    else{
		        hand -= 1;
		        board[curpos] += 1;
		    }
		}
		if(board[curpos]== 1 && curpos >= 0 && curpos <= 5){//capturing opposite stones
			board[curpos]= 0;
		   curpos = -curpos +12;
		   board[6] += board[curpos]+1;
		   board[curpos] = 0;
		}
    }

    if(next_mover()== COMPUTER){//computer's move
        intmove = -intmove + 13;
        int hand = board[intmove];
        board[intmove] = 0;

        for(int i = 1; hand > 0; i++){
                curpos = intmove + i;
            if((curpos) == 6){//if at player's bin
                //skip
            }
            else if((curpos) >= 14){//if beyond array size
                i = (-intmove);
                curpos = intmove + i;
                hand -= 1;
                board[curpos] += 1;
            }
            else{
                hand -= 1;
                board[curpos] += 1;
            }
        }
        if(board[curpos]== 1 && curpos >= 7 && curpos <= 12){//capturing opposite stones
		board[curpos] = 0;
           curpos = -curpos +12;
           board[13] += board[curpos] + 1;
           board[curpos] = 0;
        }
    }
	if(curpos == 6 || curpos == 13){//the "extra turn" case
	}else{
    		game::make_move(move);
	}

	if(is_game_over() == true){//empties all bins on winner's side into mancala
		int total_hman = 0;
		int total_comp = 0;
		for(int i = 0; i < 6; i++){
			total_hman += board[i];
		}
		for(int i = 7; i < 13; i++){
			total_comp += board[i];
		}
		if(total_hman == 0)
			board[13] += total_comp;
			for(int i = 7; i < 13; i++){
				board[i] = 0;
			}
		if(total_comp == 0)
			board[6] += total_hman;
			for(int i = 0; i < 6; i++){
				board[i] = 0;
			}
	}
}
Mancala* Mancala::clone( ) const{
    return new Mancala(*this);
}

void Mancala::compute_moves(std::queue<std::string>& moves)const{
	string istring = "";
	for(int i = 1; i < 7; i++){
		stringstream s;
		s << i;
		istring =s.str();
		if(is_legal(istring)){
			moves.push(istring);
		}
	}
}

int Mancala::evaluate( ) const{
	int total_hman = board[6];
	int total_comp = board[13];
    return total_comp - total_hman;
}

bool Mancala::is_game_over( ) const{
	int total_hman = 0;
	int total_comp = 0;
	for(int i = 0; i < 6; i++){
		total_hman += board[i];
	}
	for(int i = 7; i < 13; i++){
		total_comp += board[i];
	}
	if(total_hman == 0 || total_comp == 0){
		return true;
	}
	else{
		return false;
	}
    
}

void Mancala::display_status()const{
	cout << endl;

	cout << "  ";
	for(int i = 1; i < 7; ++i){
		cout << "  " << i;
	}
	cout << endl;//end of first line

	cout <<B_RED<<"  " << RESET;	
	for(int i = 12; i > 6; --i){
		cout << "  " << B_RED << WHITE << board[i] << RESET;
	}
	cout << "  " << B_GREEN<<"  " << RESET;
	cout << endl;//end of second line

	
	if(board[13] >= 10){
		cout << B_RED << YELLOW << board[13] << RESET;
	}else{
		cout << B_RED << YELLOW << board[13] <<  " "<< RESET;
	}
	cout << "                    " ;
	if(board[6] >= 10){
		cout << B_GREEN << YELLOW << board[6] << RESET;
	}else{
		cout << B_GREEN << YELLOW << board[6] <<  " "<< RESET;
	}
	cout<< endl;//end of third line

	cout <<B_RED<<"  " << RESET;	
	for(int i = 0; i < 6; ++i){
		cout << "  " << B_GREEN  << WHITE << board[i] << RESET;
	}
	cout << "  " << B_GREEN<<"  " << RESET;
	cout << endl;//end of fourth line

	cout << "  ";
	for(int i = 1; i < 7; ++i){
		cout << "  " << i;
	}
	cout << endl;//end of fifth line
}

void Mancala::restart(){
	Mancala();
}

std::string Mancala::get_user_move()const{
	string answer;
	display_message("Your move: ");
	getline(cin, answer);
	return answer;
}


game::who Mancala::winning( ) const{
	int value = evaluate( ); // Evaluate based on move that was just made.

	if (value > 0){//greater than 0, computer's winning
	    return COMPUTER;
	}
	else if (value < 0){//less than 0, human's winning
	    return HUMAN;
	}
	else{
	    return NEUTRAL;
	}
}

 void Mancala::make_computer_move( )
    {
	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	Mancala* future;
	
	// Compute all legal moves that the computer could make.
	compute_moves(moves);
	//assert(!moves.empty( ));
	
	// Evaluate each possible legal move, saving the index of the best
	// in best_index and saving its value in best_value.
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
	    delete future;
	    if (value >= best_value)
	    {
		best_value = value;
		best_move = moves.front( );
	    }
	    moves.pop( );
	}
	    
	// Make the best move.
	make_move(best_move);
    }

int Mancala::eval_with_lookahead(int look_ahead, int beat_this)
    // Evaluate a board position with lookahead.
    // --int look_aheads:  How deep the lookahead should go to evaluate the move.5 
    // --int beat_this: Value of another move that we?re considering. If the
    // current board position can't beat this, then cut it short.
    // The return value is large if the position is good for the player who just
    // moved. 
    {
    	queue<string> moves;   // All possible opponent moves
	int value;             // Value of a board position after opponent moves
    	int best_value;        // Evaluation of best opponent move
    	Mancala* future;          // Pointer to a future version of this game
	
        // Base case:
	if (look_ahead == 0 || is_game_over( ))
	{
	    if (last_mover( ) == COMPUTER)
	            return evaluate( );
	    else
		return -evaluate( );
	}

        // Recursive case:
        // The level is above 0, so try all possible opponent moves. Keep the
	// value of the best of these moves from the opponent's perspective.
    	compute_moves(moves); 
	 //assert(!moves.empty( ));
    	best_value = INT_MIN;
    	while (!moves.empty( ))
    	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(look_ahead-1, best_value);
	    delete future;
	    if (value > best_value)
	    {
		best_value = value;
	    }
	    moves.pop( );
    	}

    	// The value was calculated from the opponent's perspective.
    	// The answer we return should be from player's perspective, so multiply times -1:
    	return -best_value;
    }


