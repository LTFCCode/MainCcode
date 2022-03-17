#include "stdafx.h"
class Solution {
public:
	int totalNQueens(int n) {
		unordered_set<int> columns, diagonals1, diagonals2;
		return backtrack(n, 0, columns, diagonals1, diagonals2);
	}

	int backtrack(int n, int row, unordered_set<int>& columns, unordered_set<int>& diagonals1, unordered_set<int>& diagonals2) {
		if (row == n) {
			return 1;
		}
		else {
			int count = 0;
			for (int i = 0; i < n; i++) {
				if (columns.find(i) != columns.end()) {
					continue;
				}
				int diagonal1 = row - i;
				if (diagonals1.find(diagonal1) != diagonals1.end()) {
					continue;
				}
				int diagonal2 = row + i;
				if (diagonals2.find(diagonal2) != diagonals2.end()) {
					continue;
				}
				columns.insert(i);
				diagonals1.insert(diagonal1);
				diagonals2.insert(diagonal2);
				count += backtrack(n, row + 1, columns, diagonals1, diagonals2);
				columns.erase(i);
				diagonals1.erase(diagonal1);
				diagonals2.erase(diagonal2);
			}
			return count;
		}
	}

	int totalNQueensByByte(int n) {
		return solve(n, 0, 0, 0, 0);
	}

	int solve(int n, int row, int columns, int diagonals1, int diagonals2) {
		if (row == n) {
			return 1;
		}
		else {
			int count = 0;
			int availablePositions = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));
			while (availablePositions != 0) {
				int position = availablePositions & (-availablePositions);
				availablePositions = availablePositions & (availablePositions - 1);
				count += solve(n, row + 1, columns | position, (diagonals1 | position) << 1, (diagonals2 | position) >> 1);
			}
			return count;
		}
	}
};
void NQueen(int n){
	Solution test;
	cout <<"方法一"<< test.totalNQueens(n) << endl;
	cout <<"方法二"<<test.totalNQueensByByte(n) << endl;
}