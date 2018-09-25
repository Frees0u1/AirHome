/*
849. 基础计算器III
实现一个基本的计算器来计算一个简单的表达式字符串。

表达式字符串可以包含左括号 (和右括号 )、加号+或减号-、non-negative 整数和空格。

表达式字符串只包含非负整数、+, -, *, /操作符、左括号 (，右括号 )和空格。

您可以假设给定的表达式总是有效的。所有中间结果将在“[-2147483648,2147483647]”范围内。

样例
"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12
*/
#include "../LeetcodeTools.h"
using namespace leetcode;

// 左括号无脑入栈, 右括号无脑计算直到左括号
// 当前操作符优先级严格大于栈顶操作符,入栈；否则,计算栈直到栈顶操作符优先级低于当前
class Solution {
public:
    int calculate(string &s) {
        stack<int> numStk;
        stack<char> opStk;
        int num = 0, sign = 1, res = 0;
        bool hasNumber = false;
        for(char c : s) {
            if(isdigit(c)) {
                num = num * 10 + c - '0';
                hasNumber = true;
            }
            else {
                if(hasNumber) numStk.push(num); num = 0; hasNumber = false;
                if(c == ' ') continue;                
                else if(c == '(' || opStk.empty() || opPriority(c) > opPriority(opStk.top())) {                   
                    opStk.push(c);
                }
                else {
                    if(c == ')') { // calculate untill '('                        
                        calcUntill(numStk, opStk, [&numStk, &opStk]() { 
                            return opStk.top() != '('; 
                        });

                        opStk.pop();
                    }
                    else {
                        calcUntill(numStk, opStk, [&numStk, &opStk, this, &c]() { 
                            return !opStk.empty() && opPriority(opStk.top()) >= opPriority(c); 
                        });
                        opStk.push(c);
                    }
                }
            }
        }

        // last number
        if(hasNumber) numStk.push(num); num = 0; hasNumber = false;
        while(!opStk.empty()) {
            int num2 = numStk.top(); numStk.pop();
            int num1 = numStk.top(); numStk.pop();
            numStk.push(calc(num1, num2, opStk.top()));
            opStk.pop();
        }

        return numStk.top();
    }
private: 
    int opPriority(char op){
        switch(op) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            default:
                return 0;
        }
    }

    int calc(int num1, int num2, char op){
        switch(op) {
            case '+':
                return num1 + num2;
            case '-':
                return num1 - num2;
            case '*':
                return num1 * num2;
            case '/':
                return num1 / num2;
        }
    }

    void calcUntill(stack<int>& numStk, stack<char>& opStk, std::function<bool(void)> pred) {
        while(!opStk.empty() && !numStk.empty() && pred()) {
            int num2 = numStk.top(); numStk.pop();
            int num1 = numStk.top(); numStk.pop();
            numStk.push(calc(num1, num2, opStk.top()));
            opStk.pop();
        }
    }
};

int main() {
   string s = "(2+6* 3+5- (3*14/7+2)*5)+3";
   Solution sol;

   cout << sol.calculate(s) << endl; 
}