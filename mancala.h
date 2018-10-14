/*********************************************************************
	Name : Jack Mullen
	Date: April 26, 2018
	Description: Declaration for the mancala.h class, a child of game.h
**********************************************************************/
#ifndef MANCALA_H
#define MANCALA_H
#include <iostream>
#include <string>
#include "game.h"
namespace main_savitch_14{

class Mancala:public game{
	public:
		Mancala();
		~Mancala();
		void restart();
		void display_status()const;
		void make_human_move();
		void make_move(const std::string& move);
		bool is_legal(const std::string& move)const;
		std::string get_user_move()const;
		game::who winning()const;
		void make_computer_move( );
		int eval_with_lookahead(int look_ahead, int beat_this);

		//purely
		Mancala* clone( ) const;
    		void compute_moves(std::queue<std::string>& moves) const;
    		int evaluate( ) const;
    		bool is_game_over( ) const;


	private:
		static const int SEARCH_LEVELS = 4; 
		int board[14];
		
};

}





#endif
