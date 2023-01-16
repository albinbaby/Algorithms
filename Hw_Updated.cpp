#include <stdio.h>
#include <iostream>
#include <stack>
#include <map>

using namespace std;

class ExpressionStateMachine {
public:
    stack<double> m_numbers;
    stack<char> m_operations;
    string m_expression;
    int m_index;
    int m_error;

public:
    ExpressionStateMachine();

    void skipWhiteSpaces();
    bool isEndOfExpression();

    bool getNumber();
    bool getOperator();
    bool calculate();
    void processLastOperation();

    bool evaluate(string expression, double& result);
};


class ExpressionStateMachine;

class ExpressionState {
protected:
    virtual ExpressionState* nextState(ExpressionStateMachine &stateMachine) = 0;

public:
    ExpressionState* process(ExpressionStateMachine &stateMachine);
};

class FirstState : public ExpressionState {
private:
     ExpressionState* m_secondState;
public:
    FirstState();
    ExpressionState* nextState(ExpressionStateMachine &stateMachine);
    void setSecondState(ExpressionState* state) {
        m_secondState = state;
    }
};

class SecondState : public ExpressionState {
private:
     ExpressionState* m_firstState;

public:
    SecondState();

    ExpressionState* nextState(ExpressionStateMachine &stateMachine);
    void setFirstState(ExpressionState* state) {
        m_firstState = state;
    }
};


ExpressionState* ExpressionState::process(ExpressionStateMachine &stateMachine) {
    stateMachine.skipWhiteSpaces();
    if(stateMachine.isEndOfExpression()) {
        stateMachine.processLastOperation();
        return nullptr;
    }
    return nextState(stateMachine);
}


    ExpressionStateMachine::ExpressionStateMachine() {
        m_index = 0;
        m_error = 0;
    }

    void ExpressionStateMachine::skipWhiteSpaces() {
        while(m_index < m_expression.length() && m_expression[m_index] == ' ') {
            m_index++;
        }
    }
    bool ExpressionStateMachine::isEndOfExpression() {
        if(m_index < m_expression.length()) return false;
        return true;
    }

    bool ExpressionStateMachine::getNumber() {
        int num = 0;
        
        //Only - ve signs are accepted
        int sign = 1;
        if(m_expression[m_index] == '-') {
            sign = -1;
            m_index++;
        }

        //Check for valid digit
        if(!isdigit(m_expression[m_index])) {
            return false;
        }

        for(int i = m_index; i < m_expression.length(); ++i, ++m_index) {
            char ch = m_expression[i];
            if(isdigit(ch)) {
                num *= 10;
                num += (ch - '0');
            }
            else {
                break;
            }
        }
        num *= sign;
        m_numbers.push(num);
        return true;
    }

    bool ExpressionStateMachine::getOperator() {
        bool ret = false;

        switch(m_expression[m_index]) {
            case '-':
            case '+':
                //Process previous operations before pushing low precedence operator
                if(!m_operations.empty() && m_operations.top() != '(') {
                    if(!calculate()) {
                        m_error = 1;
                        return false;
                    }
                }
                //break statement is ignored purposefully to execute following operation push
                m_operations.push(m_expression[m_index]);
                m_index++;
                ret = true;
                break;
            case '*':
            case '/':
                while(!m_operations.empty() && (m_operations.top() == '*' || m_operations.top() == '/')) {
                    if(!calculate()) {
                        m_error = 1;
                        return false;
                    }
                }
                m_operations.push(m_expression[m_index]);
                m_index++;
                ret = true;
                break;
            default:
                break;
        }
        return ret;
    }

    bool ExpressionStateMachine::calculate() {
        double result = 0;
        if(m_operations.empty() || m_numbers.empty()) return false;
        
        double rightOperand = m_numbers.top();
        m_numbers.pop();
        //This is to handle bracket with single number eg. (9) which is a valid expression
        if(m_operations.top() == '(') {
            m_numbers.push(rightOperand);
            return true;
        }
        
        double leftOperand = m_numbers.top();
        m_numbers.pop();

        char ops = m_operations.top();
        m_operations.pop();

        switch(ops) {
            case '-':
                result = leftOperand - rightOperand;
                break;
            case '+':
                result = leftOperand + rightOperand;
                break;
            case '*':
                result = leftOperand * rightOperand;
                break;
            case '/':
                if(rightOperand == 0) {
                    cout << "Divide by Zero";
                    m_error = 1;
                    return false;
                }
                result = leftOperand / rightOperand;
                break;
        }
        m_numbers.push(result);
        return true;
    }

    void ExpressionStateMachine::processLastOperation() {
        while(!m_operations.empty() && m_operations.top() != '(' && m_operations.top() != ')' && m_numbers.size() > 1) {
            if(!calculate()) break;
        }

        if(!m_operations.empty() || m_numbers.size() != 1) {
            m_error =  1;
        }
    }

bool ExpressionStateMachine::evaluate(string expression, double& result) {
    m_expression = expression;
    FirstState* firstState = new FirstState;
    SecondState* secondState = new SecondState;
    firstState->setSecondState(secondState);
    secondState->setFirstState(firstState);
    ExpressionState* state = firstState;
    while(state) {
        state = state->process(*this);
    }
    if(m_error) return false;
    //TODO: correct this calculate do only if valid expression exist
    //if(!calculate() && m_error) return false;
    result = m_numbers.top();
    return true;
    
}


FirstState::FirstState() {
    m_secondState = nullptr;
}

ExpressionState* FirstState::nextState(ExpressionStateMachine &stateMachine) {
    if(stateMachine.m_expression[stateMachine.m_index] == '(') {
        stateMachine.m_operations.push('(');
        stateMachine.m_index++;
        return this;
    }
    else if(stateMachine.getNumber()) {
        return m_secondState;
    }
    stateMachine.m_error = 1;
    return nullptr;
}


    SecondState::SecondState() {
        m_firstState = nullptr;
    }

    ExpressionState* SecondState::nextState(ExpressionStateMachine &stateMachine) {
        if(stateMachine.m_expression[stateMachine.m_index] == ')') {
            while(!stateMachine.m_operations.empty() && stateMachine.m_operations.top() != '(') {
                if(!stateMachine.calculate()) break;
            }
            if(stateMachine.m_operations.empty() || stateMachine.m_operations.top() != '(') {
                stateMachine.m_error = 1;
                return nullptr;
            }
            stateMachine.m_index++;
            stateMachine.m_operations.pop();

            return this;
        }
        else if(stateMachine.getOperator()) {
            return m_firstState;
        }
        stateMachine.m_error = 1;
        return nullptr;
    }
    

bool evaluate(const char *expression, double &result) {

    result = 0;
    if(expression == nullptr) return false;
    ExpressionStateMachine sm;
    return sm.evaluate(expression, result);
}

int main() {
    map<const char*, double> expressions;
    expressions[" (  1 * 6 + 3 )  / 7 + ( 5 + 0)  "] =  6.2857142857142856;
    expressions["1/(9)"] = 0.1111111111111111;
    expressions["2*4*3+3"] = 27;
    expressions["8/(1+1)"] = 4;
    expressions["(4)/5"] = 0.8;
    expressions["4 + (12 / (1 * 2))"] = 10;
    expressions["-4 + (-12 / (1 * 2))"] = -10;
    expressions["2-2*4"] = -6;
    expressions["2*2+2-2*4"] = -2;
    expressions["-99-9"] = -108;
    expressions["((3*1)/343*(342)/-8/((((4)))))"] = -0.093476676384839655;
    
    double result = 0;
    cout << "VALID CASES\n";

   for( auto& test : expressions) {
        cout << "Expression: " << test.first;
        cout.precision(17);

        if(evaluate(test.first, result) && test.second == result) {
            
            cout << " Result: " << result << "\n";
        }
        else {
            cout << " Unexpected result " << result << " != " << test.second << "\n";
            break;
        }
   }

   map<const char*, double> invalid;
    invalid[" (  1 * 6 + 3 ))  / 7 + ( 5 + 0)  "] =  6.2857142857142856;
    invalid["1/(9)**"] = 0.1111111111111111;
    invalid["2*4*---3+3"] = 27;
    invalid["8/(1+1)`sd"] = 4;
    invalid["(4)/5/0"] = 0.8;
    invalid["4 + (12 / (1 * 2))("] = 10;
    invalid["-4 + ((-12 / (1 * 2))"] = -10;
    invalid["-4 + ((-12 / (1 * 2))/0"] = -10;
    invalid["2-/02*4"] = -6;
    invalid ["-99-9+"] = -108;
    invalid["((3*1)/343*(342)/-8/(((((4)))))"] = -0.093476676384839655;
    invalid["((3*1)/343*(342)/-8/((((4))))))"] = -0.093476676384839655;

    cout << "ERROR CASES\n";
   for( auto& test : invalid) {
        cout << "Expression " << test.first << " returned ";
        
        if(evaluate(test.first, result)) {
            
            cout << "unexpected result\n";
            break;
        }
        else {
            cout << " error as expected\n";
        }
   }

    return 0;
}
