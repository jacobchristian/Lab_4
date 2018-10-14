// Author:				Jacob Christian
// Assignment Number:   Lab 1
// File Name:			L3_Chrisitan.cpp 
// Course/Section:      COSC 1337 Section 014
// Date:                October 19, 2018
// Instructor:          Dr. Bernard Ku	

#include <iostream>
#include <iomanip>
#include <cstring>   

using namespace std;

//constant global variable because question lengths always constant
const int QUESTIONS = 20;


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
	double grade_percent = (((static_cast<double>(QUESTIONS) - static_cast<double>(numWrong))/static_cast<double>(QUESTIONS) )* 100);
	
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
		{
			cout << pos + 1 << " ";
		}
	}
	cout << "\n\n";
}

//Returns an int 
int TestGrader::getNumWrong(char test[])
{
	int numWrong = 0;
	for (int pos = 0; pos < QUESTIONS; pos++)
	{
		if (test[pos] != correctAnswers[pos])
		{
			numWrong++;
		} 
	}
	return numWrong;
}



int main()
{
	string name;
	char doAnother;
	char testTakerAnswers[QUESTIONS];
	string answer;

	//Instance of TestGrader	
	TestGrader DMVexam;
	//Set up master key
	DMVexam.setKey("BDAACABACDBCDADCCBDA");
	
	//Do-while to allow user to enter multiple students to check grade for their tests
	do{
		//# of attempts if user presses enter with no information
		int blankAnswerAttempts = 0;
		
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
				
				//If user presses enter with no char typed, will display error message
				if(answer == "")
				{
					//Marks incorrectly if # of attempts equals 2
					if (blankAnswerAttempts == 1)
					{
						cout << "Question " << pos + 1 << " is now marked as incorrect.\n";
						//Mark grade out of range from A-D, so it defaults to incorrect
						testTakerAnswers[pos] = 'F';
						//Resets blank inputs to zero for next question
						blankAnswerAttempts = 0;
						break;
					}
					//Warns user before making grade as incorrect. 
					cout << "Warning: No input given. If this happens once more, the answer will be marked as 'incorrect.' Please advise.\n";
					blankAnswerAttempts ++;
					continue;
				}
				//If answer's length is greater than 1, then there's too many characters, and will loop back to the top
				else if (answer.length() > 1)
				{
					cout << "Incorrect input, please enter A-D for answers.\n";
					continue;
				}
				
				else
				{
					//convert letter to uppercase (BONUS)
					answer[0] = toupper(answer[0]);
				}
				//If the letters aren't through A-D (BONUS)
				if (answer[0] < 'A' || answer[0] > 'D') 
				{
					cout << "Incorrect input, please enter A-D for answers.\n";
					continue;
				}
				else
				{
					//Set answer of user's input into an array to store
					testTakerAnswers[pos] = answer[0];
					break;
				}
			}
		}
		//Set user's entered data into array in TestGrader class
		DMVexam.grade(testTakerAnswers);
		
		//Ask the user if they would like to grade another person. 
		do{
			cout << "Grade another exam (Y/N)? ";
			cin >> doAnother;
			//convert to uppercase to simplify conditional check 
			doAnother = toupper(doAnother);
			cout << endl;
			//If user doesn't enter 'Y' or 'N', loop back through
			if (!(doAnother == 'Y' || doAnother == 'N'))
			{
				cout << "Please enter 'Y' for yes, or 'N' for no.\n ";
			}
			
		}while(!(doAnother == 'Y' || doAnother == 'N'));	
	}while(doAnother == 'Y');
	
	cout << "Goodbye!";
	return 0; 
}
