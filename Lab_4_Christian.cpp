#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>    // For clearing the max spaces 

using namespace std;

const int QUESTIONS = 20;

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

void TestGrader::grade(char test[])
{
	int numWrong = getNumWrong(test);
	double grade_percent = (((static_cast<double>(QUESTIONS) - static_cast<double>(numWrong))/static_cast<double>(QUESTIONS) )* 100);
	
	if (numWrong <= 5)
	{
		cout << "Congratulations, you passed the exam with a " << grade_percent << "%! \n";
	}
	else
	{
		cout << "Sorry, you failed the exam with a " << grade_percent <<"%.\n";
	}
	cout << "You got " << (QUESTIONS - numWrong) << " questions correct. ";
	if (numWrong > 0)
	{
		cout << "You missed the following " << numWrong << " questions:\n";
		missedQuestions(test);
	}
}

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
	string answer;
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
				
				cout << "Question " << right << setw(2) << pos + 1 << ": ";
				getline(cin, answer);
				if(answer == "")
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
				
				else if (answer.length() > 1)
				{
					cout << "Incorrect input, please enter A-D for answers.\n";
					continue;
				}
				
				else
				{
					answer[0] = toupper(answer[0]);
				}
				
				if (answer[0] < 'A' || answer[0] > 'D') 
				{
					//cin.clear();
					//cin.ignore(numeric_limits<int> ::max(), '\n');
					cout << "Incorrect input, please enter A-D for answers.\n";
					continue;
				}
				else
				{
					
					testTakerAnswers[pos] = answer[0];
					break;
				}
			}
		}
		DMVexam.grade(testTakerAnswers);
		do{
			cout << "Grade another exam (Y/N) ?";
			cin >> doAnother;
			doAnother = toupper(doAnother);
			cout << endl;
			if (!(doAnother == 'Y' || doAnother == 'N'))
			{
				cout << "Please enter 'Y' for yes, or 'N' for no.\n ";
			}
			cin.ignore(numeric_limits<int> ::max(), '\n');
		}while(!(doAnother == 'Y' || doAnother == 'N'));
		
	}while(doAnother == 'Y');
	cout << "Goodbye!";
	return 0; 
}
