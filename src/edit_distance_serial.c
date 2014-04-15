#include <stdio.h>
#include <stdlib.h>

int edit_distance_serial(char* s1, int n1, char* s2, int n2);

int main() {

	char* test1 = (char*)malloc(4);
	test1[0] = 'a';
	test1[1] = 'b';
	test1[2] = 'c';
	test1[3] = '\0';
	
	char* test2 = (char*)malloc(4);
	test2[0] = 'b';
	test2[1] = 'c';
	test2[2] = 'd';
	test2[3] = 'e';
	test2[4] = '\0';

	printf("Distance: %d\n", edit_distance_serial(test1, 3, test2, 4));
}


int edit_distance_serial(char* s1, int n1, char* s2, int n2) {
	
	// Ensure second input is shorter
	if (n2 > n1) {
		char* tempS = s1; int tempN = n1;
		s1 = s2; n1 = n2;
		s2 = tempS; n2 = tempN;
	}
	
	// DP table initialization
	int* prevLine = (int*)malloc((n2+1) * sizeof(int));
	int* currentLine = (int*)malloc((n2+1) * sizeof(int));
	
	// Base-case values
	for (int i = 0; i < n2+1; i++)
		prevLine[i] = i;
	
	// Evaluate DP entries
	for (int r = 1; r < n1+1; r++) {
		currentLine[0] = r;
		for (int c = 1; c < n2+1; c++) {
			if (s1[r-1] == s2[c-1]) {
				currentLine[c] = prevLine[c-1];
			}
			else {
				int up = prevLine[c], left = currentLine[c-1], upLeft = prevLine[c-1];
				int min = up < left ? up : left;
				min = min < upLeft ? min : upLeft;
				
				currentLine[c] = min + 1;
			}
		}
		int* temp = prevLine;
		prevLine = currentLine;
		currentLine = temp;
	}
	
	// Extract answer, free memory
	int answer = currentLine[n2-1];
	free(prevLine); free(currentLine);
	return answer;
	
}