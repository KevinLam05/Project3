#include<iostream>
#include<vector> //for Stack and Queue
#include<map> // for expression map
#include<algorithm> // for std::reverse
// Add class Stack here
class Stack {
    public:
        std::map<char, char> expression_map = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
        bool validPara(const std::string& expression) {
            for (char ch : expression) {
                if (expression_map.count(ch)) { //find para and add to stack
                    stack.push_back(ch);
                } else {
                    if (stack.empty()) { // check if stack is empty, if yes return false
                        return false;
                    }
                    if (expression_map[stack.back()] != ch) {//check if para exist in map if no then return false
                        return false;
                    }
                }
                stack.pop_back();//pop para
            }
            return stack.empty(); //return empty means valid para, if not empty then not valid
        }
        int indexError(const std::string& expression) {
            int index_error = -1; //create a base return index
            for (int i = 0; i < expression.size(); i++) { //iterate through the expression
                std::vector<char> temp_stack;
                bool isValid = true; //create a base valid 
                for (int ii = i; ii < expression.size(); ii++) { //inner loop to go through the expression
                    if(expression_map.count(expression[ii])) {
                        temp_stack.push_back(expression[ii]);
                    } else {
                        if (temp_stack.empty() || expression_map[temp_stack.back()] != expression[ii]) { //ifstack is empty then valid is false
                            isValid = false;
                            break; //stop inner loop
                        } else {
                            temp_stack.pop_back();//balanced expression
                        }
                    }
                }
                if (isValid == false) {
                    index_error = i;
                } else {
                    isValid = true;
                }
            }
            return index_error;//return -1 if balanced, or index i at the point where it breaks
        }
        int minPara(const std::string& expression) {
            int missing = 0;
            for ( char ch: expression) { //iterate through expression
                if(expression_map.count(ch)) {
                    stack.push_back(ch);
                } else if (stack.empty() == false && expression_map[stack.back()] == ch) { //ifstack isnt empty and para matches, then popback
                    stack.pop_back();
                } else { //if missing or unbalanced para missing +1
                    missing++;
                }
            }
            missing += stack.size();
            return missing;
        }
        int scorePara(const std::string& expression) {
            int valid_para_count = 0; //number of balanced para
            int close_count = 0; // number of expected closing para when theres an open para
            for ( char ch : expression) {
                if (expression_map.count(ch)) {
                    close_count++;
                } else if (stack.empty() == false && expression_map[stack.back()] == ch) { // if stack isnt empty and para matches, then pop back to increase balance count
                    stack.pop_back();
                    close_count--;
                    valid_para_count++;
                }
            }
            return valid_para_count;
        }
    private:
    std::vector<char> stack;
};
class Queue {
    public:
        void enqueue(std::string message) {
            for (int i = 0; i <message.length(); i+=8) {
                std::string msgChunk = message.substr(i, 8);
                std::reverse(msgChunk.begin(), msgChunk.end()); //reverse function to be ready to pushback into queue
                queue.push_back(msgChunk);
            }
        }
        void processMsg() {
            std::string afterMsg = "";
            if (!queue.empty()) { // check if queue is empty
                for (std::string chunk : queue) {
                    std::reverse(chunk.begin(), chunk.end()); // reverse chunk back to original message
                    afterMsg += chunk;
                    queue.pop_back();
                }
            }
            std::cout << "The message is: " << afterMsg << std::endl;
}
    private: 
        std::vector<std::string> queue;
};
// Add class Queue here
// Remove comments before testing and do not change anything in main function
int main(){
Stack s1;
s1.validPara("(([]))");
s1.minPara("(([]))");
s1.scorePara("(([]))");
s1.validPara("(([])");
std::cout<<s1.indexError("(([))")<<std::endl;
s1.minPara("(([])");
s1.validPara("(([{}))");
std::cout<<s1.indexError("(([[}])")<<std::endl;
s1.minPara("(([{}))");
s1.scorePara("(([{}))");
std::cout<<s1.indexError("({}[]()[)")<<std::endl;
s1.validPara("(([))");
s1.minPara("(([))");
std::cout<<s1.indexError("[({)]")<<std::endl;
s1.validPara("(([{[{({})}]}]))");
s1.minPara("(([{[{({})}]}]))");
s1.scorePara("(([{[{({})}]}]))");
s1.validPara("(([[{[{({})}]))");
s1.validPara("(([[{[{({})}]}])]))");
s1.scorePara("(([[{[{({})}]}])]))");
std::cout<<s1.indexError("(([[{{({})]}])]))")<<std::endl;
s1.validPara("(())");
s1.validPara("(())");
s1.validPara("void function(){}");
s1.scorePara("void function(){}");
s1.validPara("void function(");
s1.minPara("void function(");
s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
s1.scorePara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}");
s1.validPara("void function(std::string expre){if(expre){return 1;else{return 0;");
s1.minPara("void function(std::string expre){if(expre){return 1;else{return 0;");
std::cout<<s1.indexError("void function(std::string expre){if(expre){return 1;else{return 0;")<<std::endl;
Queue q1;
q1.enqueue("This is a secure message.");
q1.processMsg();
q1.enqueue("The product I received is damaged. What should I do?");
q1.processMsg();
q1.enqueue("I need assistance with setting up my new device");
q1.processMsg();
q1.enqueue("The website is not loading properly on my browser.");
q1.processMsg();
q1.enqueue("I accidentally placed the wrong order. Can it be canceled?");
q1.processMsg();
q1.enqueue("This is your project3. Have a happy thanksgiving!!! Hahaha");
q1.processMsg();
q1.enqueue("I forgot my password and can't reset it. Help, please! Do you provide technical support for mobile devices?");
q1.processMsg();
q1.enqueue("The software update is causing issues on my computer. The response time on your website is very slow.");
q1.processMsg();
return 0;
}