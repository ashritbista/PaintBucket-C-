#include <iostream>
#include <cstdlib>
#include <sstream>
#include "CImg.h"
#include "Pair.h"
#include "Queue.h"

using namespace std;
using namespace cimg_library;

string getUserInput(string prompt)
{
	string t = "";
	cout << prompt;
	getline(cin, t);
	return t;
}

bool canGoUp(int r, int c, int rows, int cols, CImg<unsigned char> grid)
{
	if (r <= rows && c <= cols && (r - 1) >= 0)
	{
		if (
			grid(c, r - 1, 0, 0) == grid(c, r, 0, 0) &&
			grid(c, r - 1, 0, 1) == grid(c, r, 0, 1) &&
			grid(c, r - 1, 0, 2) == grid(c, r, 0, 2)
		)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool canGoRight(int r, int c, int rows, int cols, CImg<unsigned char> grid)
{
	if (r <= rows && c <= cols && (c + 1) < cols)
	{
		if (
			grid(c + 1, r, 0, 0) == grid(c, r, 0, 0) &&
			grid(c + 1, r, 0, 1) == grid(c, r, 0, 1) &&
			grid(c + 1, r, 0, 2) == grid(c, r, 0, 2)
		)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool canGoDown(int r, int c, int rows, int cols, CImg<unsigned char> grid)
{
	if (r <= rows && c <= cols && (r + 1) < rows)
	{
		if (
			grid(c, r + 1, 0, 0) == grid(c, r, 0, 0) &&
			grid(c, r + 1, 0, 1) == grid(c, r, 0, 1) &&
			grid(c, r + 1, 0, 2) == grid(c, r, 0, 2)
		)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool canGoLeft(int r, int c, int rows, int cols, CImg<unsigned char> grid)
{
	if (r <= rows && c <= cols && (c - 1) >= 0)
	{
		if (
			grid(c - 1, r, 0, 0) == grid(c, r, 0, 0) &&
			grid(c - 1, r, 0, 1) == grid(c, r, 0, 1) &&
			grid(c - 1, r, 0, 2) == grid(c, r, 0, 2)
		)
			return true;
		else
			return false;
	}
	else
		return false;
}

// This function checks to see if the cell has already been colored.
bool isValidPosition(
	int r, int c,
	int rows, int cols,
	CImg<unsigned char> grid,
	int red_channel, int green_channel, int blue_channel)
{
	if (
		r < rows && c < cols && r >= 0 && c >= 0 &&
		(
			grid(c, r, 0, 0) == red_channel &&
			grid(c, r, 0, 1) == green_channel &&
			grid(c, r, 0, 2) == blue_channel
		)
	)
		return true;

	else
		return false;
}


int main(int argc, char *argv[])
{
	int rows, cols;
	int curr_r = 0, curr_c = 0;
	Queue<Pair<int, int>*> mq;

	//This array will be our color choice
	int colors[9][3] =
	{
		{ 0, 0, 255 },		// Blue
		{ 0, 255, 0 },		// Green
		{ 255, 0, 0 },		// Red
		{ 255, 128, 0 },	// Orange
		{ 0, 255, 255 },	// Cyan
		{ 0, 128, 128 },	// Teal
		{ 255, 255, 0 },	// Yellow
		{ 255, 0, 255 },	// Magenta
		{ 128, 128, 0 }		// Olive
	};


	string filename = getUserInput("Enter image filename: ");
	CImg<unsigned char>workimage(filename.c_str());
	rows = workimage.height();
	cols = workimage.width();
	cout << '(' << rows << ", " << cols << ')' << endl;

	CImgDisplay mainwindow(workimage, "Paint bucket");

	int color_index = 0;

	while (!mainwindow.is_closed())
	{
		mainwindow.wait();
		if (mainwindow.button() && mainwindow.mouse_x() >= 0 && mainwindow.mouse_y() >= 0)
		{
			// Get the x and the y coordinates (x = # of cols & y = # of rows)
			curr_c = mainwindow.mouse_x();
			curr_r = mainwindow.mouse_y();

			// Drop the color channel value to a check variable for checking purposes
			int red_channel = workimage(curr_c, curr_r, 0, 0),
				green_channel = workimage(curr_c, curr_r, 0, 1),
				blue_channel = workimage(curr_c, curr_r, 0, 2);

			cout << "Mouse clicked at: " << '(' << curr_r << ',' << curr_c << ')' << endl;

			// We now set up the color to paint the cells
			int color_red = colors[color_index][0],
				color_green = colors[color_index][1],
				color_blue = colors[color_index][2];


			// Colors will rotate every time a region is painted and the mouse is clicked
			if (color_index == 8)
				color_index = 0;
			else
				color_index++;

			// Now we start the breadth first search
			do
			{
				// This condition will weed out the cells that have been already colored
				if (isValidPosition(curr_r, curr_c, rows, cols, workimage, red_channel, green_channel, blue_channel))
				{
					if (canGoUp(curr_r, curr_c, rows, cols, workimage))
					{
						Pair<int, int>* myPair = new Pair<int, int>(curr_r - 1, curr_c);
						mq.enQ(myPair);
					}
					if (canGoRight(curr_r, curr_c, rows, cols, workimage))
					{
						Pair<int, int>* myPair = new Pair<int, int>(curr_r, curr_c + 1);
						mq.enQ(myPair);
					}
					if (canGoDown(curr_r, curr_c, rows, cols, workimage))
					{
						Pair<int, int>* myPair = new Pair<int, int>(curr_r + 1, curr_c);
						mq.enQ(myPair);
					}
					if (canGoLeft(curr_r, curr_c, rows, cols, workimage))
					{
						Pair<int, int>* myPair = new Pair<int, int>(curr_r, curr_c - 1);
						mq.enQ(myPair);
					}
				}

				// Color the current cell so it's not visited again
				workimage(curr_c, curr_r, 0, 0) = color_red;
				workimage(curr_c, curr_r, 0, 1) = color_green;
				workimage(curr_c, curr_r, 0, 2) = color_blue;

				// Update the image
				mainwindow.display(workimage);

				// For when queue is not empty, deQ the neighboring cells
				if (!mq.isEmpty())
				{
					Pair<int, int>* next;
					mq.deQ(next);

					curr_r = *(next->getFirst());
					curr_c = *(next->getSecond());

					delete next;
					cout << "next: " << '(' << curr_r << ',' << curr_c << ')' << endl;
				}
			} while (!mq.isEmpty());

			// Save the image for later
			workimage.save("donkey.bmp");
			cout << "Done!" << endl;
		}
	}
}