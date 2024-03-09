#include <bits/stdc++.h>

using namespace std;

class ArithemeticEvaluator
{
protected:
     // this indicates priorities of two operators
     map<char, int> operator_priority = {
         {'-', 1},
         {'+', 2},
         {'/', 3},
         {'*', 4},
         {'^', 5},
     };
     // postfix inner evaluator or helper

     void postFix_h(char i, stack<char> *stack, string *postfix)
     {
          int t = i - '0'; // an initial value out of i to check whether this i is an integer or not
          if (t >= 0 && t <= 9)
               *postfix += i; // if integer simply add it to the string
          else
          {
               if (stack->empty()) // else check whether stack is empty (which ensures that ther is no precedence conflict)
               {
                    stack->push(i); // if empty just push
               }
               else
               {
                    // if not empty chech if top of stack has more more priority than the i, in which case lower priority cannot go over higher one,
                    // in worst case there might be many higher priority stacked on and on
                    // if higher priority is found on top of the stack then pop it out and add to string
                    while (!stack->empty() && (operator_priority[i] < operator_priority[stack->top()]))
                    {
                         *postfix += stack->top();
                         stack->pop();
                    }
                    // finally push i into stack if no conflict remains
                    stack->push(i);
               }
          }
     }
     // function to create postfix
     // main function of postfix
     string postFix()
     {
          // to store postfix string
          string postfix = "";
          // stack to keep track of operators
          stack<char> stack;
          // to keep eye on ()
          bool is_Sub_Exp = false;
          // iterate over input
          for (auto i : this->input)
          {
               // if sub expression is encountered
               if (is_Sub_Exp || (i == '(' || i == ')'))
               {
                    // handle sub expression in separate case
                    if (i == '(')
                    {
                         // initialy push open bracket '('
                         stack.push(i);
                         is_Sub_Exp = true;
                    }
                    else if (i == ')')
                    {
                         // if ')' close is encountered pop until '(' also pop '('
                         while (!stack.empty() && stack.top() != '(')
                         {
                              postfix += stack.top();
                              stack.pop();
                         }
                         stack.pop();
                         is_Sub_Exp = false;
                    }
                    else
                    {
                         // push rest sub expression until ')'
                         postFix_h(i, &stack, &postfix);
                    }
               }
               else
               {
                    // in case of normal expression create postfix and maintain stack
                    postFix_h(i, &stack, &postfix);
               }
          }
          // after iterating over string if any operator is left in stack then pop until and add into postfix
          while (!stack.empty())
          {
               postfix += stack.top();
               stack.pop();
          }
          return postfix;
     }
     // Supporiting Function
     int add(int a, int b)
     {
          return a + b;
     }
     int sub(int a, int b)
     {
          return a - b;
     }
     int mul(int a, int b)
     {
          return a * b;
     }
     int div(int a, int b)
     {
          return a / b;
     }
     // end of supporting functions
     string input; // this will hold given input string
public:
     ArithemeticEvaluator(string a)
     {
          this->input = a;
     }
     // actual evaluator function
     int evaluate()
     {
          string postfix = this->postFix();
          // to maintain operands
          stack<char> stack;
          for (auto i : postfix)
          {
               int t = i - '0';
               if (t >= 0 && t <= 9)
               {
                    stack.push(i);
               }
               else
               {
                    int operand2 = stack.top() - '0';
                    stack.pop();
                    int operand1 = stack.top() - '0';
                    stack.pop();

                    int ans;
                    // switch between various operation
                    switch (i)
                    {
                    case '+':
                         ans = this->add(operand1, operand2);
                         break;
                    case '-':
                         ans = this->sub(operand1, operand2);
                         break;
                    case '*':
                         ans = this->mul(operand1, operand2);
                         break;
                    case '/':
                         ans = this->div(operand1, operand2);
                         break;
                    case '^':
                         ans = pow(operand1, operand2);
                         break;
                    }
                    // adding the soln of sub expression into stack for further calculation
                    stack.push(ans + '0');
               }
          }
          cout << postfix;
          return stack.top() - '0';
     }
};

int main()
{
     ArithemeticEvaluator a("(3+4)*(5-2)*(8*2-5*3)");
     int ans = a.evaluate();
     cout << endl
          << "Answer:- " << ans;
}

// this code has some problem with ^ power at times