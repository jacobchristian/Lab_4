
#include <iostream>
#include <iomanip>
#include <cstring>   

using namespace std;

//constant global variable because question lengths always constant
const int QUESTIONS = 20;

//Function Prototypes
bool gradeAnotherTest();
bool secondBlankQuestionCheck(int);
bool checkLengthandValue(string &);
//Class definition
class TestGrader 
{
	private:
		char correctAnswers[QUESTIONS];
		int getNumWrong(char []);
		void missedQuestions(const char []); 		 
	public:		
		void setKey(string key);
		void grade(char []);
};

//Sets the key to the correct answers
void TestGrader::setKey(string key)
{
	if (key.length() != QUESTIONS)
	{
		cout << "Error in data.\n";
		return;
	}
	for (int pos = 0; pos < QUESTIONS; pos++)
	{
		correctAnswers[pos] = key[pos];
	}
}

/* Calls getNumWrong to find out the number of incorrect answers, turns that into a grade percentage, and lets the user know 
   whether or not they passed the exam. It will also iterate through the loop to get the incorrect questions and display 
   to the user which ones were missed. */
void TestGrader::grade(char test[])
{
	int numWrong = getNumWrong(test);
	//Find percentage grade
	double grade_percent = (((QUESTIONS - numWrong)/static_cast<double>(QUESTIONS) )* 100);
	
	if (numWrong <= 5)
	{
		cout << "Congradulations, you passed the exam with a " << grade_percent << "%! \n";
	}
	else
	{
		cout << "Sorry, you failed the exam with a " << grade_percent <<"%.\n";
	}
	cout << "You got " << (QUESTIONS - numWrong) << "out of " << QUESTIONS << " questions correct.\n";
	if (numWrong > 0)
	{
		cout << "You missed the following " << numWrong << " questions:\n";
		missedQuestions(test);
	}
}
//Loops through any that user questions that don't match with answerkey will be displayed. 
void TestGrader::missedQuestions(const char studentAnswers[])
{
	for (int pos = 0; pos < QUESTIONS; pos++)
	{
		if (studentAnswers[pos] != correctAnswers[pos])
		{ cout << pos + 1 << " "; }
	}
	cout << "\n\n";
}

//Returns an integer value of the number of questions wrong
int TestGrader::getNumWrong(char test[])
{
	int numWrong = 0;
	for (int pos = 0; pos < QUESTIONS; pos++)
	{
		if (test[pos] != correctAnswers[pos])
		{ numWrong++; } 
	}
	return numWrong;
}



int main()
{
	string name;
	char testTakerAnswers[QUESTIONS]; //keeps track of student answers
	bool isBlankTwice; //bool flag to keep track of blank 'ENTER' entries
	string answer; //input for student
	TestGrader DMVexam; //Instance of TestGrader
	DMVexam.setKey("BDAACABACDBCDADCCBDA"); //Set up master key
	
	//Do-while to allow user to enter multiple students to check grade for their tests
	do{		
		cout << "\nApplicant Name: ";
		getline(cin, name);
		
		cout << "\nEnter answers for " << name <<".\n";
		cout << "Use only the letters A, B, C, D.\n\n";
		
		//Iterate through 20 times 
		for (int pos = 0; pos < QUESTIONS; pos++)
		{
			while (true)
			{
				cout << "Question " << right << setw(2) << pos + 1 << ": ";
				getline(cin, answer);
				
				if(answer == "") //If user presses enter with no char typed, will display error message
				{
					isBlankTwice = secondBlankQuestionCheck(pos);
					if (isBlankTwice)
					{
						testTakerAnswers[pos] = 'F'; //if 'ENTER' w/ no value 2x, sets question to automatic wrong answer. 
						break;
					}
					continue; //continue back through loop after secondBlankQuestionCheck marked it as first 'ENTER'. 
				}
					
				if(checkLengthandValue(answer))
					break; //breaks out of while loop, starts next iteration through for loop
				else
					continue; //input not valid, goes through the loop again with same question. 
			}
			testTakerAnswers[pos] = answer[0]; //If all tests pass, enter answer into student's answer array
		}
		DMVexam.grade(testTakerAnswers); //Set user's entered data into array in TestGrader class	
		
	}while(gradeAnotherTest()); //Run function to ask the user if they want to grade another test
	
	cout << "Goodbye!";
	return 0; 
}

bool gradeAnotherTest()
{
//Ask the user if they would like to grade another person. 
	string answer;
	cout << "Grade another exam (Y/N)? ";
	cin >> answer;
		//convert to uppercase to simplify conditional check 
		answer[0] = toupper(answer[0]);
		cout << endl;
		//If user doesn't enter 'Y' or 'N', loop back through
		while (!(answer[0] == 'Y' || answer[0] == 'N'))
		{
			cout << "Please enter 'Y' for yes, or 'N' for no.\n ";
			cin >> answer;
		}	
	if (answer[0] == 'Y')
		return true;
	//If the answer isn't yes, then return false. 	
	return false;
}

bool secondBlankQuestionCheck(int position)
{	
	static int blankAnswerAttempts = 1; //static variable keeps track of the number of attempts	
	
	static int lastPosition; //Keeps track of the position of the question, to confirm double mark
							 
	//If the user is on their first attempt on a different question, it resets the answer attempts back to 1.
	if (blankAnswerAttempts == 2 && lastPosition != position)
		{ blankAnswerAttempts = 1; }
	
	//Marks incorrectly if # of attempts equals 2
	else if (blankAnswerAttempts == 2 && lastPosition == position)
	{
		cout << "Question " << position + 1 << " is now marked as incorrect.\n\n";	
		//Reset back to one so when the function is called, it's auto-marked
		blankAnswerAttempts = 1;
		return true;
	}
	
	cout << "Warning: No input given. If this happens once more, the answer will be marked as 'incorrect.' Please advise.\n";
	
	blankAnswerAttempts++; //increments number of attempts to 1. IF it happens again, the answer will be marked as incorrect.
	lastPosition = position; //Set position to confirm the that the question is being asked a second time.
		
	return false; //Return false if true wasn't returned above, so the question can be asked again.
}

bool checkLengthandValue(string &answer)
{
	answer[0] = toupper(answer[0]); /*convert letter to uppercase by reference, changing the variable in main (BONUS)*/ 

		
	if ((answer[0] < 'A' || answer[0] > 'D') || answer.length() > 1) //If the letters aren't through A-D (BONUS)	
	{
		cout << "Incorrect input, please enter A-D for answers.\n";
		return false;
	}			
	else
	{ return true; } //Return as true if input is valid and the length is correctly only 1
}
