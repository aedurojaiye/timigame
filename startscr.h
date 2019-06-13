void print_start_scr(void){

	int x = 20;
	int y = 85;
	move(x,y);
	start_color();

	init_pair(1, COLOR_BLUE,COLOR_BLACK);
	init_pair(2, COLOR_RED,COLOR_BLACK);
	init_pair(3, COLOR_WHITE,COLOR_BLACK);



	//logo
	attron(COLOR_PAIR(1));
	printw(" _____ _   _ _____  _____ _____ ___________ ");
	printw("\n"); move(++x,y);
	printw( "/  ___| | | |  _  ||  _  |_   _|  ___| ___ \\");
	printw("\n"); move(++x,y);
	printw( "\\ \\`--.| |_| | | | || | | | | | | |__ | |_/ /");
	printw("\n"); move(++x,y);
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(2));
	printw( " \\`--. \\  _  | | | || | | | | | |  __||    / ");
	printw("\n"); move(++x,y);
	printw( "/\\__/ / | | \\ \\_/ /\\ \\_/ / | | | |___| |\\ \\_ ");
	printw("\n"); move(++x,y);
	printw( "\\____/\\_| |_/\\___/ \\___/  \\_/ \\____/\\_| \\__|");
	printw("\n"); move(++x,y);
	printw( "                                            ");
	printw("\n"); move(++x,y);
	printw( "                                            ");
	attroff(COLOR_PAIR(2));
	y= y+10;
	printw("\n"); move(++x,y);


	// name

	printw("By Oluwatimilehin Akogun");
	printw("\n"); move(++x,y);
	printw("Github: FunctionofFunction");


	move(++x,y);
	move(++x,y);
	move(++x,y);
	move(++x,y);
	attroff(COLOR_PAIR(3));
	attron(A_STANDOUT);
	refresh();
	printw("Press Any Key to Start!");
	attroff(A_STANDOUT);
	attroff(COLOR_PAIR(3));
	endwin();
	return;

}
