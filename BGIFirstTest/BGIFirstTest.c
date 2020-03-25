// BGIFirstTest.c : Example graphic application


#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Circle function creating a circle shape
void Circle(int y) {
	setfillstyle(SOLID_FILL, YELLOW);
	circle(310, 60 + y, 10);			// Vertical position is set with a variable
	floodfill(311, 61+y, WHITE);
}

// Obstacle functions creating rectangle shapes at different positions on screen
void Obstacle1(int x) {
	setfillstyle(SOLID_FILL, LIGHTRED);
	rectangle(-400 + x, 150, 0 + x, 160);		// Horizontal position is set with a variable
	floodfill(-399 + x, 151, WHITE);
}

void Obstacle2(int x) {
	setfillstyle(SOLID_FILL, LIGHTRED);
	rectangle(637 + x, 200, 1037 + x, 210);
	floodfill(638 + x, 201, WHITE);
}

void Obstacle3(int x) {
	setfillstyle(SOLID_FILL, LIGHTRED);
	rectangle(-500 + x, 250, -100 + x, 260);
	floodfill(-499 + x, 251, WHITE);
}

void Obstacle4(int x) {
	setfillstyle(SOLID_FILL, LIGHTRED);
	rectangle(800 + x, 300, 1200 + x, 310);
	floodfill(801+x, 301, WHITE);
}

// Function to create finish line rectangle shape, text and display next level number
void FinishArea(int current_level) {
	setfillstyle(SOLID_FILL, LIGHTCYAN);
	rectangle(0, 400, 637, 430);
	floodfill(1, 401, WHITE);

	char next_level[50];
	current_level++;
	char level_number[] = { '0' + current_level, '\0' };
	strcpy_s(next_level, sizeof(next_level), "NEXT LEVEL: ");
	strcat_s(next_level, sizeof(next_level), level_number);
	setcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 20);
	outtextxy(190, 401, next_level);
	setcolor(WHITE);
}

main()
{
	// Initialize the graphic interface
	int gd = DETECT, gm = 0;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	

	int x1 = 0, x2 = 0, x3 =0, x4 = 0;
	int y = 0;
	int N = 0;								// Motion loop variable
	int counter = 0;
	int G = 0;								// Entire game loop variable
	int v = 0;
	int lvl = 1;

	// Markers for the text: middle of the screen
	int midx = getmaxx() / 4;
	int midy = getmaxy() / 2;

	// Set the strings of the game
	char* game_name = "CROSSY ROAD";
	char* start_game = "Press any key to start.";
	char* game_instr = "Press \u2193 to cross the road!";
	char* play_again = "Press 'R' to play again";
	char* game_over = "GAME OVER";

	// Play again loop, resets the game
	while (G == 0)
	{
		clearviewport();
		setcolor(LIGHTCYAN);
		settextstyle(BOLD_FONT, HORIZ_DIR, 50);
		outtextxy(midx - strlen(game_name), (midy - 100), game_name);
		setcolor(WHITE);
		settextstyle(BOLD_FONT, HORIZ_DIR, 15);
		outtextxy(midx - strlen(start_game), (midy + 100), start_game);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 15);
		outtextxy(midx - strlen(game_instr), (midy + 200), game_instr);
		
		// Wait for the user to press any key
		_getch();
		

		// Restart the game from 0
		x1 = 0;
		x2 = 0;
		x3 = 0;
		x4 = 0;
		y = 0;
		N = 0;
		counter = 0;
		v = 0;
		lvl = 1;


		//Motion Loop
		while (N == 0) {

			// Make clear Motion
			setactivepage(counter % 2);

			// Set Finish Line
			FinishArea(lvl);

			// Go Down
			if (_kbhit())							// Wait for the user to hit a key
			{
				if  (_getch() == KEY_DOWN)			// Wait for the user to hit a key Down
					{y += 10+v;}					// Increase the y depending of the level (link with v) to make the circle going down
			}

			//Print the red circle
			Circle(y);


			// Set obstacle speed and loops
			
					//Motion Obstacle 1
			x1 += 10 + v;								// Initial Speed 10
			if (x1 >= 1100) { x1 = 0; }					// Obstacle 1 Loop

					//Motion Obstacle 1
			x2 += 12 + v;								// Initial Speed 12
			if (x2 >= 1100) { x2 = 0; }					// Obstacle 2 Loop

					//Motion Obstacle 1
			x3 += 14 + v;								// Initial Speed 14
			if (x3 >= 1200) { x3 = 0; }					// Obstacle 3 Loop

					//Motion Obstacle 1
			x4 += 20 + v;								// Initial Speed 20
			if (x4 >= 1200) { x4 = 0; }					// Obstacle 4 Loop
			
			// Print Obstacles
			Obstacle1(x1);
			Obstacle2(-x2);
			Obstacle3(x3);
			Obstacle4(-x4);

			// Impact
			if (((300+v <= x1) && (x1 <= 710+v)) && ((80 < y) && (y < 110))) { N = 1; }				// Impact Obstacle 1
			if (((315 + v <= x2) && (x2 <= 720 + v)) && ((130 < y) && (y < 160))) { N = 1; }		// Impact Obstacle 2
			if (((380 + v <= x3) && (x3 <= 800 + v)) && ((180 < y) && (y < 210))) { N = 1; }		// Impact Obstacle 3
			if (((460 + v <= x4) && (x4 <= 880 + v)) && ((230 < y) && (y < 260))) { N = 1; }		// Impact Obstacle 4



			// No impact and reached finish line
			if (y > 330) {
				y = 0;			// Reset the circle position
				v += 2;			// Faster for next level
				lvl++;			// Increment level
			}

			
			// Make clear Motion
			setvisualpage(counter % 2);
			counter++;

			delay(40);						// Time between each motion loop
			clearviewport();				// Delete Previous Motions

		}

	// Outputs level after losing
	printf("You reached level: %d\n", lvl);	

	//GAME OVER
	setcolor(BLUE);
	settextstyle(BOLD_FONT, HORIZ_DIR, 70);
	outtextxy(midx - strlen(game_over), (midy - 100), game_over);
	setcolor(WHITE);
	settextstyle(BOLD_FONT, HORIZ_DIR, 15);
	outtextxy(midx - strlen(play_again), (midy + 100), play_again);
	
	// Play again or stop 
	char* restart_game = _getch();
	if (restart_game == 'r') { G = 0; }		// 'r' --> Restart 
	else { G = 1; }							// else Stop
	}

	closegraph();							// End
}


