#include <unistd.h>
#include <ncurses.h>
#include "startscr.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define ESC 113
#define X_AXIS 142
#define Y_AXIS 40

void drop_alien_rocks(int* alien_x, int* alien_y, int* active, int speed);
void clean_gun(int x, int y);
void print_game_scr(int x, int y);
void print_gun(int x, int y);
void show_bullet(int x, int y);
void clean_bullet(int x, int y);
void print_alien_ship(int* x, int* y);
void load_gun(int* gun_x, int* gun_y);
int rand_alien_pos();


int main(void)
{

	initscr();			/* Start curses mode*/
	raw();
	print_start_scr();

	getch();			/* receive any key*/
	clear();           /*clear*/

	/* set game dimension*/
	print_game_scr(X_AXIS,Y_AXIS);

	/*inital alien position*/

	int alien_x, alien_y;
	int active = 1; //check if shot down yet
	int speed = 50000;
	drop_alien_rocks(&alien_x, &alien_y, &active, speed);




	/*gun position*/
	int gun_x = X_AXIS/2;
	int gun_y = Y_AXIS;
	load_gun(&gun_x, &gun_y); // this also controls exit


	refresh();
	endwin();			/* End curses mode		  */
	return 0;
}



void print_game_scr(int x, int y){
	// print horizontal boundies

	for (int i = 0; i <= x; i++) {
		mvprintw(y,i,"=");
		mvprintw(y-1,i,"=");//ground
	}
	//print vertical boundies
	for (int i = 0; i <= y; i++) {
	   mvprintw(i,0,"|");
	   mvprintw(i,x, "|");
   }

}
void print_gun(int x, int y){
		 y=y-2; // because of ground

		 mvprintw (y-3,x, 	" ||");
		 mvprintw (y-2,x,	"|##|");
		 mvprintw (y-1,x,	"|##|");
		 mvprintw (y,x,     "||||");

		 curs_set(0); //hide cursor

}
void clean_gun(int x, int y){
		 y=y-2; // because of ground

		 mvprintw (y-3,x, 	"   ");
		 mvprintw (y-2,x,	"    ");
		 mvprintw (y-1,x,	"    ");
		 mvprintw (y,x,     "    ");

		 curs_set(0); //hide cursor

}
void show_bullet(int x , int y){
	y=y-2; // because of ground
	mvprintw (y-4,x, 	"  * ");
}

void clean_bullet(int x , int y){
	y=y-2; // because of ground
	mvprintw (y-4,x, 	"    ");
}

void print_alien_ship(int* x, int* y){

	mvprintw(*y-1,*x, 	"          ");
  	mvprintw(*y,*x, 	" \\|/\\|/");
	mvprintw(*y+1,*x,	"  (  )");
	mvprintw(*y+2,*x,	"  (  )");
    mvprintw(*y+3,*x,	"   \\/ ");
	curs_set(0); //hide cursor


}

void load_gun(int* gun_x, int* gun_y) {
	print_gun(*gun_x, *gun_y);

	int controller = ESC;


	do {
	    printw("\b");
	    noecho();
	    controller = getch();
	    noecho();




	    if (controller == 'D') {
	        if (*gun_x > 1){
				clean_gun(*gun_x, *gun_y);
	        	print_gun(--*gun_x, *gun_y);
			}
	    }

	    if (controller == 'C') {

			if (*gun_x < X_AXIS-4) {
				clean_gun(*gun_x, *gun_y);
		        print_gun(++*gun_x, *gun_y);
			}
	    }
	    if (controller == 's') {
	        int bullet_y = *gun_y;
	        for (int i = 0; i < bullet_y ; bullet_y--) {
	            show_bullet(*gun_x, bullet_y--);
	        }

	        refresh();
	        usleep(50000);

	        bullet_y = *gun_y;
	        for (int i = 0; i <= bullet_y ; bullet_y--) {
	            clean_bullet(*gun_x, bullet_y--);
	        }
	    }



	} while(controller != ESC);

}

int rand_alien_pos(){

	int possible_alien_x [] = {X_AXIS/2, 2*X_AXIS/3, X_AXIS/4};
	return (possible_alien_x[rand() % 3]);
}

void drop_alien_rocks(int* alien_x, int* alien_y, int* active, int speed) {

	*alien_x = rand_alien_pos();
 	*alien_y = 1;

	while (*active) {

		print_alien_ship(alien_x, alien_y);


		*alien_y = *alien_y + 1;

		refresh();
		usleep(speed);
	}
 }
