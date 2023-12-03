#include "operator.h"
#include "history.h"
#include <conio.h>

int main ()
{
    string inputEquation;
    double result;
    int command;
    int prompt = 1;
    Node* head = NULL;
    int test;
    string tempHistory;

    while (prompt != 0)
    {
            cout
        << "                 Scientific Calculator              \n"
        << "Engineered by Axel, Gerald, Krisna, Abdi, and Marlon\n"
        << "\nInstructions to calculate:\n"
        << " - trigonomentry do sinN or cosN or tanN where N is degree\n"
        << " - logarithmic do logN(I) or ln(I) where N is the base and I is a number\n"
        << " - exponent do N^J where N and J are numbers\n"
        << " - square root do VN where N is number\n"
        << " - multiply/divide/add/sub do N*J or N/J or N+j or N-J where N and J are numbers\n"

		<< "\nWe try using these equations:"
		<< "\n - 1 + 1 - 2 / 2 + sin90 + cos0 + tan45 + V4 + 2^2 + log(100) = 12"
		<< "\n - 1 + (1 - 2) / 2 + sin90 + cos(1-1) + tan(15*3) + V(8/2) + log(100)^2 + log2(2^2) = 11.5"
		<< "\n - 1 + (2 + 4/(1+1))/2 + sin90 + cos(10*0) + tan((3*5)*3) + V((2*6)+V16) + log(50*2)^2 + log2((2^2)*4)\n\n";
        cout << "Welcome!\n";
        cout << "Command: \n"
		     << " 1: Calculate\n"
		     << " 2: Show History\n"
		     << " 0: Exit Program\n"
             << "Enter: ";
		cin >> prompt;
        system("cls");
	
		//to do a calculation
		if (prompt == 1)
        {
            cout << "Enter the equation: ";
            cin.ignore();
            getline(cin, inputEquation);
            Calculator Calculator(inputEquation);
            // result = Calculator.calculate(); // input equation result after testing
            cout << "Result: " << Calculator.calculate() << endl;  
			
			string calcResult = to_string(Calculator.calculate());
			tempHistory = inputEquation + " = " + calcResult;
			push(&head, tempHistory);
						
			prompt = 3;
            Calculator.finalResult = 0;
            cout << "Continue...";
            getche();
            system("cls");
		}
        else if (prompt == 2) //to look at history
        {
			int historyPrompt = 3;
			
            while (historyPrompt != 0)
            {
				printHistory(head);
				
                cout << "Command: \n"
					 << " 1: Delete History\n"
					 << " 0: Go back to Main Menu\n"
                     << "Enter... ";	
				cin >> historyPrompt;
				system("cls");
                
				if(historyPrompt == 1) //delete history
                {
    				int index = 0;
                    printHistory(head);

                    cout << "Enter the position: ";
                    cin >> index;

					deleteNode(&head, index);
					historyPrompt = 3;
                    system("cls");
				}
				else if(historyPrompt == 0){
                    system("cls");
					continue;
				}
			}
			
		}
		else if (prompt == 0)
			return 0;

        
	}

}