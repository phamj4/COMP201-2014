#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum State { INIT, FIRST, NO_MATCH };
// Concentration game model
// The model manages the state of the game
class Model {
public:
	// Constructor (instantiates object)
	// Initialize a grid of letters randomly
	Model(int w, int h);
	// Destructor deletes all dynamically allocated stuff
	~Model();
	// Methods (member functions)
	// Return the width
	int getWidth();
	// Return the height
	int getHeight();
	// Return visible stuff (invisible stuff is shown with character *)
	char get(int row, int column);
	// Flip this row/column
	void flip(int row, int column);
	// Is the game over?
	bool gameOver();
private:
	// Is the row/column valid?
	bool valid(int row, int column);
	// Did the cell at current row/column match the cell at the last row/column 
	bool matched(int row, int column);
	// Fields (member data)
	// Randomly generated grid. This has pairs of characters in it
	char ** grid;
	// What is visible to the user?
	char ** visible;
	// What's the width?
	int width;
	// What's the height?
	int height;
	// What'd we flip last?
	int lastrow;
	int lastcolumn;
	int lastrow2;
	int lastcolumn2;
	State state;
};

// Show (output) the state of the model
class View {
public:
	// Print out the visible stuff in the grid
	void show(Model * model);
};

// Handle input
class Controller {
public:
	Controller() {
		model = new Model(8, 8);
		view = new View;
	}
	~Controller()
	{
		delete model;
		delete view;
	}
	// Event loop
	void loop();
private:
	Model * model;
	View * view;
};

// Constructor initializes the object
Model::Model(int w, int h)
{
	width = w;
	height = h;
	lastrow = -1;
	lastcolumn = -1;
	state = INIT;
	grid = new char*[h];
	visible = new char*[h];
	for (int i = 0; i < height; i++) {
		grid[i] = new char[w];
		visible[i] = new char[w];
	}
	//TODO make this random-ish = done
	char letter = 'A';
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			grid[i][j] = letter;
			visible[i][j] = '*';

			if ((j) % 2 == 1) {
				if (letter == 'Z') {
					letter = 'A';
				}
				else {
					letter++;
				}
			}
		}
	}
	srand(time(0));

	// Shuffle here
	int otheri, otherj;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Pick a random spot in the grid
			otheri = rand() % height;
			otherj = rand() % width;
			// Swap here
			letter = grid[i][j];
			grid[i][j] = grid[otheri][otherj];
			grid[otheri][otherj] = letter;
		}
	}
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
	for (int i = 0; i < height; i++) {
		delete grid[i];
		delete visible[i];
	}
	delete grid;
	delete visible;
}


// TODO: Is the row/column valid?
// That is, is the row within the height, and is the column within the width?
// Return whether it is or isn't.
bool Model::valid(int row, int column) {
	return (((row >= 0) && (row < height)) && ((column >= 0) && (column < width)));
}
bool Model::matched(int row, int column) {
	return true;
}
// TODO: Flip a cell
void Model::flip(int row, int column) {
	// If the row and column are not valid, break out and don't do anythin
	if (!valid(row, column)) { return; }
	if ((row == lastrow) && (column == lastcolumn)) { return; }
	switch (state)
	{
	case NO_MATCH:
		visible[lastrow][lastcolumn] = '*';
		visible[lastrow2][lastcolumn2] = '*';
	case INIT:
		visible[row][column] = grid[row][column];
		lastrow = row;
		lastcolumn = column;
		state = FIRST;
		break;
	case FIRST:
		visible[row][column] = grid[row][column];
		lastrow2 = row;
		lastcolumn2 = column;
		if (grid[lastrow][lastcolumn] != grid[lastrow2][lastcolumn2])
		{
			state = NO_MATCH;
		}
		else
		{
			state = INIT;
		}
		break;
	}
}
// If everything is visible, then it's game over
bool Model::gameOver() {
	// Hint: assume the game is over, unless it isn't
	// Hint: Loop through the grid and see if any element is not visible
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (visible[i][j] != grid[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
int Model::getWidth() {
	return width;
}
int Model::getHeight() {
	return height;
}
char Model::get(int row, int col) {
	return visible[row][col];
}
// Show the model, one cell at a time
void View::show(Model * model) {
	cout << endl;
	for (int j = 0; j < model->getWidth(); j++) {
		cout << "\t" << j;
	}
	cout << endl;
	for (int i = 0; i < model->getHeight(); i++) {
		cout << i;
		for (int j = 0; j < model->getWidth(); j++) {
			cout << "\t" << model->get(i, j);
		}
		cout << endl;
	}
}

// Show the board
// Read in coordinates
// Until we're done
void Controller::loop() {
	int row, col;
	while (!model->gameOver()) {
		view->show(model);
		cout << "Enter row:    ";
		cin >> row;
		cout << "Enter column: ";
		cin >> col;
		model->flip(row, col);
	}
	view->show(model);
	cout << "Hooray you win!" << endl;

}

int main() {
	Controller c;
	c.loop();
	return 0;
}