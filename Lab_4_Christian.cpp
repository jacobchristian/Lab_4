#include <iostream>
#include <iomanip>
#include <string>

#include <limits>    // For clearing the max spaces 

/*	INSTRUCTIONS
 Make sure the following requirements are met.
Write a program that grades the written portion of a Department of Motor Vehicles (DMV) driver's license exam.  The exam has 20 multiple choice questions.  
The correct answers are: 1-B,2-D,3-A,4-A,5-C,6-A,7-B,8-A,9-C,10-D,11-B,12-C,13-D,14-A,15-D,16-C,17-C,18-B,19-D,20-A. 

    Create a TestGrader class that includes an answers array of 20 characters (or string) which holds the correct test answers. 
    The class will have two public member functions that enable user programs to interact with the class: setKey and grade. 
    The setKey function receives a 20-character string holding the correct answers and copies this information into its answers array. 
    Hint: can use string copy method to copy a string to a character array
    The grade function receives a 20-character string holding the test taker's answers and compares each of their answers to the correct ones. 
    After grading the exam the function should display a message indicating whether the applicant passed or failed the exam. 15 or more correct answers are required to pass. 
    The function should then display the total number of correctly answered questions, the total number of incorrectly answered questions, and a list of the question numbers for all incorrectly answered questions. 
    The client program that creates and uses a TestGrader object should first make a single call to setKey, passing it a string containing the 20 correct answers. 
    After the above step, the client program should allow a test taker's 20 answers to be entered, store them in a 20-character array (or string), and then call the grade function to grade the exam. 
    The program should loop to allow additional tests to be entered and graded until the user indicates a desire to stop. 
    Input validation: Only accept the letters A, B, C, and D for test answers.
    Hint: could use the char function toupper from <cctype>
*/
using namespace std;

const int QUESTIONS = 20;

class TestGrader 
{
	private:
		char correctAnswers[QUESTIONS];
		int getNumWrong(char []);
//		void missedQuestions(char []); 
		 
	public:
		
		void setKey(string key);
		void grade(char []);


};


void TestGrader::setKey(string key)
{
	if (key.length() != QUESTIONS)
	{
		cout << "Error in data.\n";
		return;
	}
	for (int pos; pos < QUESTIONS; pos++)
	{
		correctAnswers[pos] = key[pos];
	}
}

void TestGrader::grade(char test[])
{
	int numWrong = getNumWrong(test);
	if (numWrong <= 5)
	{
		cout << "Congratulations, you passed the exam!\n";
	}
	else
	{
		cout << "Sorry, you did not pass the exam.\n";
	}
	cout << "You got " << (QUESTIONS - numWrong) << "questions correct.";
	if (numWrong > 0)
	{
		cout << "You missed the following " << numWrong << " questions:\n";
//		missedQuestions(test);
	}
}


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
	char answer;
	char testTakerAnswers[QUESTIONS];
		
	TestGrader DMVexam;
	
	DMVexam.setKey("BDAACABACDBCDADCCBDA");
	
	do{
		int blankAnswerAttempts = 0;
		
		cout << "\nApplicant Name: ";
		getline(cin, name);
		
		cout << "\nEnter answers for " << name <<".\n";
		cout << "Use only the letters A, B, C, D.\n\n";
		
		for (int pos = 0; pos < QUESTIONS; pos++)
		{
			while (true)
			{
				cout << "Question " << pos + 1 << ": ";
				cin >> answer;
				if(answer == '\n' || isspace(answer))
				{
					
					if (blankAnswerAttempts == 1)
					{
						cout << "Question " << pos + 1 << " is now marked as incorrect.\n";
						testTakerAnswers[pos] = 'F';
						blankAnswerAttempts = 0;
						break;
					}
					cout << "Warning: No input given. If this happens once more, the answer will be marked as 'incorrect.' Please advise.\n";
					blankAnswerAttempts ++;
					continue;
				}
				else
				{
					answer = toupper(answer);
				}
				
				if (answer < 65 || answer > 68 ) 
				{
					cin.clear();
					cin.ignore(numeric_limits<int> ::max(), '\n');
					cout << "Incorrect input, please enter A-D for answers.\n";
					continue;
				}
				else
				{
					testTakerAnswers[pos] = answer;
					break;
				}
			}
		}
		for(char letter : testTakerAnswers)
			cout << letter << " ";
		cout << "Grade another exam (Y/N) ?";
		cin >> doAnother;
		cout << endl;
		cin.ignore(numeric_limits<int> ::max(), '\n');
		
	}while(toupper(doAnother == 'Y'));
	
	return 0; 
}
