#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include <string>
#include <regex>
#include <bits/stdc++.h>


using namespace std;

// The precidence is of () ^ / * + -
// The associativity of ^ = R-L / * + - = L-R

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0;
}

// Works fine except for spacing issues need to fix those. ---------------------
// Spacee issues fixed need to fix case 3 core dumped error.    
string InfixToPostfix(string instr) {
    string postFix = "";
    stack<char> operators;

    // regex r("\\s");
    // instr = regex_replace(instr, r, "");

    for (int i = 0; i < instr.length(); i++) {
        if (instr[i] == '%' || instr[i] == '/' || instr[i] == '*' || instr[i] == '+' || instr[i] == '-' || instr[i] == '^') {

            while (!operators.empty() && precedence(operators.top()) >= precedence(instr[i])) {
                postFix += " ";
                postFix += operators.top();
                operators.pop();
            }
            operators.push(instr[i]);
        }

        else if (instr[i] == '(') {
            operators.push(instr[i]);
        }
        else if (instr[i] == ')') {
            while ((!operators.empty() && operators.top() != '(')) {
                postFix += " ";
                postFix += operators.top();
                operators.pop();
            }
            operators.pop();

        }
        else if (isalnum(instr[i])) {
            if (postFix.empty()) {
                postFix += instr[i];
            }
            else {
                postFix += " ";
                postFix += instr[i];
            }
        }
    }
    while (!operators.empty()) {
        postFix += " ";
        postFix += operators.top();
        operators.pop();
    }
    
    if(postFix.compare("") == 0) {
        return postFix;
    }
    postFix += " ";
    return postFix;
}

string PostfixToInfix(string token){
    stack<string> s;
 
    for (int i=0; token[i]!='\0'; i++)
    {
        // Push operands
        if (isOperand(token[i]))
        {
           string op(1, token[i]);
           s.push(op);
        }
 

        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push("(" + op2 + token[i] +
                   op1 + ")");
        }
    }
    return s.top();
}

int main(int argc, char *argv [])
{
	string sentence, outStr;
	
	int Lcount=0;
	bool toinfix = false, topost=false;
	
	ifstream file;
	if( argc >= 2 ) {
		file.open(argv[1]);
		if( !file) 
		{
			/* error */ 
			cerr << "File cannot be opened: " << argv[1] << endl;
			exit (1);
        }
        
        string arg( argv[2] );
		if( arg == "-toinfix" )
		toinfix = true;
		else if( arg == "-topost" )
		topost = true;
			
		else {
			cerr << "UNRECOGNIZED FLAG " << arg << endl;
			return 0;
		}
				
	}
	else
	{
		cerr << "No file is found" << endl;
		exit (1);
	}
	
	getline(file, sentence);
	  
    while ( !file.eof()) {
       	Lcount++;
       	if (toinfix)
       	{
       		outStr = PostfixToInfix(sentence);
       		cout << "Result of convering Postfix expression \"" << sentence 
			   << "\" to Infix notation: \"" << outStr << "\"" << endl;
	   }
       	else if(topost)
       	{
       		outStr = InfixToPostfix(sentence);
       		cout << "Result of convering Infix expression \"" << sentence 
			   << "\" to Postfix notation: \"" << outStr << "\"" << endl;
		}
       		
       	else
		   break;
		    	 	
		getline(file, sentence); 
	}
	
	return 0;
}

