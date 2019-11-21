#include <iostream>

using namespace std;

const int TRI_HEIGHT = 5;

void init_tri(int** tri, int c) {
	for (int i = 0; i < TRI_HEIGHT; ++i) {
		for (int j = 0; j < TRI_HEIGHT; ++j) {
			tri[i][j] = c;
		}
	}
}

void print_triangle(int** tri) {
	for (int i = 0; i < TRI_HEIGHT; ++i) {
		std::string space(TRI_HEIGHT-(i+1), ' ');
		std::cout << space;
		for (int j = 0; j < i+1; ++j) {
			std::cout << tri[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool in_triangle(int i, int j) {
		if (i >= 0 && j >= 0 &&
					 i < TRI_HEIGHT && j < TRI_HEIGHT &&
					 j <= i) {
			return true;
		}
		return false;
}
// A move is valid given three conditions (four if we add that the source peg must be occupied):
// 1. the destination peg is in the triangle
// 2. The destination peg is empty (==0)
// 3. The jumped peg between the source and the destination is occupied
bool is_valid_jump(int** tri, int src_i, int src_j, int dest_i, int dest_j, int jump_i, int jump_j) {
	//Condition 1: Destination must be in the triangle
	if (!in_triangle(dest_i, dest_j)) {
		return false;
	}


	//Condition 2: Destination must be empty
	if (tri[dest_i][dest_j]) {
		return false;
	}

	//Condition 3: Jumped peg must be occupied
	if (!tri[jump_i][jump_j]) {
		return false;
	}

	return true;
}

int **copy_tri(int **tri) {
	int **triangle = new int*[TRI_HEIGHT];

	for (int i = 0; i < TRI_HEIGHT; ++i) {
		triangle[i] = new int[i+1];
	}

	for (int i = 0; i < TRI_HEIGHT; ++i) {
		for (int j = 0; j < i+1; ++j) {
			triangle[i][j] = tri[i][j];
		}
	}

	return triangle;

}

bool solve_tri_rec(int** tri, int num_pegs) {
	// If there is one peg left, write down this triangle state and return true
	if (num_pegs == 1) {
		print_triangle(tri);
		return true;
	}

	
	bool made_move = false;

	// For each slot, if there is a piece, try every possible move for that piece.
	for (int i = 0; i < TRI_HEIGHT; ++i) {
		for (int j = 0; j < i+1; ++j) {

			//If there is a piece in that slot
			if (!tri[i][j]) {
				continue;
			}

			//Up-left jump: dest_i= i-2; dest_j = j-2; jump_i = i-1; jump_j = j-1
			if (is_valid_jump(tri, i, j, i-2, j-2, i-1, j-1)) {
				int** tri_cpy = copy_tri(tri);

				//Source is empty
				tri_cpy[i][j] = 0;
				//Jump piece is jumped
				tri_cpy[i-1][j-1] = 0;
				//Destination is filled
				tri_cpy[i-2][j-2] = 1;

				//Recursive call
				if (solve_tri_rec(tri_cpy, num_pegs-1)) {
					print_triangle(tri);
					return true;
				}

				delete tri_cpy;
			}
			
			//Up-right jump: 		dest_i= i-2; 	dest_j= j; 		jump_i = i-1; jump_j = j
			if (is_valid_jump(tri, i, j, i-2, j, i-1, j)) {
				int** tri_cpy = copy_tri(tri);

				//Source is empty
				tri_cpy[i][j] = 0;
				//Piece is jumped
				tri_cpy[i-1][j] = 0;
				//Destination is filled
				tri_cpy[i-2][j] = 1;

				//Recursive call
				if (solve_tri_rec(tri_cpy, num_pegs-1)) {
					print_triangle(tri);
					return true;
				}

				delete tri_cpy;
			}
	
			//Down-left jump: 	dest_i = i+2; dest_j = j; 	jump_i = i+1; jump_j = j
			if (is_valid_jump(tri, i, j, i+2, j, i+1, j)) {
				int** tri_cpy = copy_tri(tri);

				//Source is empty
				tri_cpy[i][j] = 0;
				//Piece is jumped
				tri_cpy[i+1][j] = 0;
				//Destination is filled
				tri_cpy[i+2][j] = 1;

				//Recursive call
				if (solve_tri_rec(tri_cpy, num_pegs-1)) {
					print_triangle(tri);
					return true;
				}

				delete tri_cpy;
			}
			
			//Down-right jump: 	dest_i = i+2; dest_j = j+2; jump_i = i+1; jump_j = j+1
			if (is_valid_jump(tri, i, j, i+2, j+2, i+1, j+1)) {
				int** tri_cpy = copy_tri(tri);

				//Source is empty
				tri_cpy[i][j] = 0;
				//Piece is jumped
				tri_cpy[i+1][j+1] = 0;
				//Destination is filled
				tri_cpy[i+2][j+2] = 1;

				//Recursive call
				if (solve_tri_rec(tri_cpy, num_pegs-1)) {
					print_triangle(tri);
					return true;
				}

				delete tri_cpy;
			}
	
			//Left jump: 				dest_i = i; 	dest_j = j-2; jump_i = i; 	jump_j = j-1
			if (is_valid_jump(tri, i, j, i, j-2, i, j-1)) {
				int** tri_cpy = copy_tri(tri);

				//Source is empty
				tri_cpy[i][j] = 0;
				//Piece is jumped
				tri_cpy[i][j-1] = 0;
				//Destination is filled
				tri_cpy[i][j-2] = 1;

				//Recursive call
				if (solve_tri_rec(tri_cpy, num_pegs-1)) {
					print_triangle(tri);
					return true;
				}

				delete tri_cpy;
			}
	
			//Right jump: 			dest_i = i; 	dest_j = j+2; jump_i = i;		jump_j = j+1
			if (is_valid_jump(tri, i, j, i, j+2, i, j+1)) {
				int** tri_cpy = copy_tri(tri);

				//Source is empty
				tri_cpy[i][j] = 0;
				//Piece is jumped
				tri_cpy[i][j+1] = 0;
				//Destination is filled
				tri_cpy[i][j+2] = 1;

				//Recursive call
				if (solve_tri_rec(tri_cpy, num_pegs-1)) {
					print_triangle(tri);
					return true;
				}

				delete tri_cpy;
			}
	
		}
	}
	if (num_pegs == 13) {
		//print_triangle(tri);
	}
	return false;
}

void solve_tri(int** tri) {
	// Start with just trying the top piece empty
	tri[0][0] = 0;
	solve_tri_rec(tri, 14);
}

// Triangle layout in 2D array:
// 0,0
// 1,0 1,1
// 2,0 2,1 2,2
// 3,0 3,1 3,2 3,3
// 4,0 4,1 4,2 4,3 4,4
//
// Note that an up-right diagonal jump is just "up" (and vice-versa for down-left)
// due to the way we structure our array
int main() {
		int **triangle = new int*[TRI_HEIGHT];

		for (int i = 0; i < TRI_HEIGHT; ++i) {
			triangle[i] = new int[i+1];
		}

		init_tri(triangle, 1);

		solve_tri(triangle);

		return 0;
}

