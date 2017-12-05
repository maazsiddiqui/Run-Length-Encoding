#include <iostream>
#include <fstream> // class necessary to read files
using namespace std;

class runLengthEncoding {

	private:
		int numRows, numCols, minVal, maxVal;
		int** arr; // dynamic array
		char* inFile; // pointer to argv[1]
		char* outFile; // pointer to argv[2]

	public:
		runLengthEncoding(char* inFile, char* outFile) {  // Constructor
			
			this->inFile = inFile;
			this->outFile = outFile;
			
			ifstream myfile(inFile);	// input file reader from argument
			
			myfile >> numRows;
			myfile >> numCols;
			myfile >> minVal;
			myfile >> maxVal;

			arr = new int*[numRows];
			for(int i = 0; i < numRows; i++) arr[i] = new int[numCols];
	 
	  		for(int i = 0; i < numRows; i++) {
	  			for(int j = 0; j < numCols; j++)
	      			myfile >> arr[i][j];
			}
			
			myfile.close(); // close input file
		}
		
		void runLengthPrint() {
			
			ofstream myoutfile(outFile);
			
			myoutfile	<< numRows << " "
						<< numCols << " "
						<< minVal << " "
						<< maxVal << endl;

			int pixelLength = 0;
			int pixelColor = -1;
			int row, col;
							
			for(int i = 0; i < numRows; i++) {
				  				
				for(int j = 0; j < numCols; j++) {
					
					if (arr[i][j] > 0) {
						
						row = i;
						col = j;
						pixelColor = arr[i][j];
						pixelLength = 1;
						
						int temp = j + 1;
						
						while (temp < numCols && arr[i][temp] == pixelColor) {
							pixelLength++;
							temp++;
						}
						
						myoutfile	<< row << " "
									<< col << " "
									<< pixelColor << " "
									<< pixelLength << endl;
									
						j = temp - 1;
						pixelLength = 0;
						pixelColor = -1;					
					}	
				}
			}
			myoutfile.close();
		}
};

int main(int argc, char *argv[]) {

	runLengthEncoding myRLE(argv[1], argv[2]);
	myRLE.runLengthPrint();

	return 0;

} // end of main

