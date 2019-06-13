#include <unistd.h>
#include <ncurses.h>
#include "startscr.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>


#define ESC 113
#define X_AXIS 210
#define Y_AXIS 40

void drop_alien_rocks(int* alien_x, int* alien_y, int* active, int speed, int* bullet_x_axis);
void clear_gun(int x, int y);
void print_game_scr(int x, int y);
void print_gun(int x, int y);
void show_bullet(int x, int y);
void clear_bullet(int x, int y);
void print_alien_ship(int* x, int* y);
void load_gun(int* gun_x, int* gun_y, int* bullet_x);
void clear_alien_ship(int* x, int* y);
int rand_alien_pos();
/* thread function for alien Ship*/
void* threadFunc(void *arg);

int bullet_x = 0;
pthread_mutex_t lock;
int active = 1; //check if shot down yet or q pressed

int main(void)
{

	initscr();			/* Start curses mode*/
	noecho();
    cbreak();
	raw();
	print_start_scr();

	getch();			/* receive any key*/
	clear();           /*clear*/

	refresh();

	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printw("\n mutex init failed\n");
        return 1;
    }

	/* set game dimension*/

	print_game_scr(X_AXIS,Y_AXIS);
	refresh();
	/*inital alien position*/

	/****************multithreading starts*/
	// int alien_x, alien_y;
	// int active = 1; //check if shot down yet
	// int speed = 50000;
	//drop_alien_rocks(&alien_x, &alien_y, &active, speed);
	pthread_mutex_lock(&lock);
	pthread_t tid;	// this is our thread identifier
	pthread_attr_t attr;
	refresh();
	pthread_attr_init(&attr);
	refresh();
	pthread_create(&tid, &attr , threadFunc, &bullet_x);
	refresh();
	/*gun position*/
	int gun_x = X_AXIS/2;
	int gun_y = Y_AXIS;
	load_gun(&gun_x, &gun_y, &bullet_x); // this also controls exit
	/****************multithreading ends*/
	refresh();
	pthread_mutex_unlock(&lock);
	pthread_join(tid, NULL);
	//pthread_exit(NULL);
	pthread_mutex_destroy(&lock);
	refresh();
	endwin();			/* End curses mode		  */
	return 0;
}



void print_game_scr(int x, int y){

	//print vertical boundies
	for (int i = 0; i <= y; i++) {
	   refresh();
	   mvprintw(i,0,"|");
	   refresh();
	   mvprintw(i,x, "|");

   }
	return;
}
void print_gun(int x, int y){
	     refresh();
		 y=y-2; // because of ground
		 refresh();
		 mvprintw (y-3,x, 	" ||");
		 refresh();
		 mvprintw (y-2,x,	"|##|");
		 refresh();
		 mvprintw (y-1,x,	"|##|");
		 refresh();
		 mvprintw (y,x,     "||||");
 	 	 refresh();
		 mvprintw (y+1,x,   "    ");
		 refresh();
		 curs_set(0); //hide cursor
		 refresh();

		 return;
}
void clear_gun(int x, int y){
		 y=y-2; // because of ground
		 refresh();
		 mvprintw (y-3,x, 	"   ");
		 refresh();
		 mvprintw (y-2,x,	"    ");
		 refresh();
		 mvprintw (y-1,x,	"    ");
		 refresh();
		 mvprintw (y,x,     "    ");
		 refresh();
		 curs_set(0); //hide cursor
		 refresh();
		 return;
}
void show_bullet(int x , int y){
	y=y-2; // because of ground
	refresh();
	mvprintw (y-4,x, 	"  * ");

	return;
}

void clear_bullet(int x , int y){
	y=y-2; // because of ground
	refresh();
	mvprintw (y-4,x, 	"    ");

	return;
}

void print_alien_ship(int* x, int* y){
	refresh();
	mvprintw(*y-1,*x, 	"          ");
	refresh();
  	mvprintw(*y,*x, 	" \\|/\\|/");
	refresh();
	mvprintw(*y+1,*x,	"  (  )");
	refresh();
	mvprintw(*y+2,*x,	"  (  )");
	refresh();
    mvprintw(*y+3,*x,	"   \\/ ");
    refresh();
	curs_set(0); //hide cursor
	refresh();
	return;
}

void load_gun(int* gun_x, int* gun_y, int* bullet_x) {
	refresh();
	print_gun(*gun_x, *gun_y);

	int controller = ESC;


	do {
		refresh();
	    printw("\b");
	    noecho();
	    controller = getch();
	    noecho();

		if (controller == ESC) {
			active = 0;
		}


	    if (controller == 'D') {
	        if (*gun_x > 1){

				clear_gun(*gun_x, *gun_y);
	        	print_gun(--*gun_x, *gun_y);
			}
	    }

	    if (controller == 'C') {

			if (*gun_x < X_AXIS-4) {
				refresh();
				clear_gun(*gun_x, *gun_y);
		        print_gun(++*gun_x, *gun_y);
			}
	    }
	    if (controller == 's') {
	        int bullet_y = *gun_y;
	        for (int i = 0; i < bullet_y ; bullet_y--) {
				*bullet_x = *gun_x;
	            show_bullet(*gun_x, bullet_y--);
	        }

	        refresh();
	        usleep(300000);

	        bullet_y = *gun_y;
	        for (int i = 0; i <= bullet_y ; bullet_y--) {

				clear_bullet(*gun_x, bullet_y--);
	        }
	    }



	} while(controller != ESC);

	return;
}

int rand_alien_pos(){

	int possible_alien_x [] = {X_AXIS/2, 2*X_AXIS/3, X_AXIS/4};
	return (possible_alien_x[rand() % 3]);

}

void drop_alien_rocks(int* alien_x, int* alien_y, int* active, int speed, int* bullet_x_axis) {
	pthread_mutex_lock(&lock);


	*alien_x = rand_alien_pos();
 	*alien_y = 1;

	while (*active) {
		refresh();
		print_alien_ship(alien_x, alien_y);


		*alien_y = *alien_y + 1;
		refresh();
		usleep(speed);
		refresh();
		if (*bullet_x_axis < *alien_x+5 && *bullet_x_axis > *alien_x-5) {
			clear_alien_ship(alien_x, alien_y);
			refresh();
			usleep(speed);
			refresh();

			// starts a new alien
			*alien_x = rand_alien_pos();
		 	*alien_y = 1;

			pthread_mutex_unlock(&lock);

		}
		if(*alien_y >= Y_AXIS-5){
			mvprintw(Y_AXIS/2, X_AXIS/2,"GAME OVER");

		 	return;
		}// game over you have been hit

	}
	return;
 }
 void *threadFunc(void *arg)
 {
	 pthread_mutex_unlock(&lock);
	int* bullet_x_axis = (int*) arg;
	refresh();

 	int alien_x, alien_y;
 	int speed = 150000;
	refresh();
 	drop_alien_rocks(&alien_x, &alien_y, &active, speed, bullet_x_axis);
	refresh();

	pthread_mutex_lock(&lock);
	return NULL;
 }

 void clear_alien_ship(int* x, int* y){
 	refresh();
 	mvprintw(*y-1,*x, 	"          ");
 	refresh();
   	mvprintw(*y,*x, 	"         ");
 	refresh();
 	mvprintw(*y+1,*x,	"      ");
 	refresh();
 	mvprintw(*y+2,*x,	"      ");
 	refresh();
     mvprintw(*y+3,*x,	"       ");
     refresh();
 	curs_set(0); //hide cursor
 	refresh();
 	return;
 }
