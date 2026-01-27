#include <iostream>

using namespace std;

enum TokenType {
    IF,ELSE,WHILE,LET,SEMICOLON,OPEN_1,CLOSE_1,
    OPEN_2,CLOSE_2, NUMBER, ASSIGN, PLUS, MINUS, MULT,
    DIV, LT, GT, EQ, NE, EOF_TOKEN,IDENTIFIER, PRINT
};

struct Token {
    public:
    TokenType type;
    string val;
    Token(TokenType _type, string _val) {
        type = _type;
        val = _val;
    }
};

class Ast {
    public:
    virtual ~Ast() = default;
};

class Expr : public Ast {};
class Statement : public Ast {
    public:
    int val;
};

class NumExpr : public Expr {
    public:
    string val;
    NumExpr(string _val){
        val = _val;
    }
};

class VarExpr : public Expr {
    public:
    string name;
    VarExpr(string _name){
        name = _name;
    }
};

class BinaryExpr : public Expr {
    public:
    Expr* left;
    Expr* right;
    string op;
    BinaryExpr(Expr* _left,string _op, Expr* _right){
        left = _left;
        right = _right;
        op = _op;
    }
};

class VarDeclStatement : public Statement {
    public:
    Expr* expr;
    string var;
    VarDeclStatement(string _var, Expr* _expr){
        var = _var;
        expr = _expr;
        val = 0;
    }
};

class IfStatement : public Statement {
    public:
    Expr* cond;
    vector<Statement*> ifBlock, elseBlock;
    IfStatement(Expr* _cond,  vector<Statement*> _ifBlock,  vector<Statement*> _elseBlock = {}){
        cond = _cond;
        ifBlock = _ifBlock;
        elseBlock = _elseBlock;
        val = 1;
    } 
};

class WhileStatement : public Statement {
    public:
    Expr* cond;
    vector<Statement*> body;
    WhileStatement(Expr* _cond,  vector<Statement*> _body){
        cond = _cond;
        body = _body;
        val = 2;
    }
};

class PrintStatement : public Statement {
    public:
    Expr* expr;
    PrintStatement(Expr* _expr){
        expr = _expr;
        val = 3;
    }
};

class AssignStatement : public Statement {
    public:
    string name;
    Expr* expr;
    AssignStatement(string _name,  Expr* _expr){
        name = _name;
        expr = _expr;
        val = 4;
    }
};

class Lexer {
    public:
    string code;
    int len;
    vector<Token> tokens;
    Lexer(string s){
        code = s;
        len = code.size();
    }
    bool isDigit(int idx){
        return (code[idx] >='0') && (code[idx]<='9');
    }
    bool isOp(int idx){
        return (code[idx] =='+') ||  (code[idx] =='-') 
            || (code[idx] =='*') ||  (code[idx] =='/')
            || (code[idx] =='=') ||  (code[idx] =='<')
            || (code[idx] =='>');
    }
    bool isAlpha(int idx){
        return ((code[idx] >='a') &&  (code[idx] <= 'z'))
            || ((code[idx] >='A') &&  (code[idx] <= 'Z')) ;
    }
    
    void getDigit(int& idx){
        int val = 0;
        while((idx<len) && (isDigit(idx))) {
            val = val*10 + (code[idx++]-'0');
        }
        tokens.push_back(Token(TokenType::NUMBER,to_string(val)));
    }
    void getOp(int& idx){
        auto op = code[idx++];
        if (op == '+') tokens.push_back(Token(TokenType::PLUS,"+"));
        else if (op == '-') tokens.push_back(Token(TokenType::MINUS,"-"));
        else if (op == '*') tokens.push_back(Token(TokenType::MULT,"*"));
        else if (op == '/')  tokens.push_back(Token(TokenType::DIV,"/"));
        else if (op == '=')  tokens.push_back(Token(TokenType::EQ,"="));
        else if (op == '<')  {
            tokens.push_back(Token(TokenType::LT,"<"));
        }
        else if (op == '>')  tokens.push_back(Token(TokenType::GT,">"));
     }

    void getKeyword(int& idx){
        string word = "";
        while((idx<len) && (isAlpha(idx))) {
            word.push_back(code[idx++]);
        }
        if(word == "let") tokens.push_back(Token(TokenType::LET,"LET"));
        else if(word == "if") tokens.push_back(Token(TokenType::IF,"IF"));
        else if(word == "while") tokens.push_back(Token(TokenType::WHILE,"WHILE"));
         else if(word == "print") tokens.push_back(Token(TokenType::PRINT,"PRINT"));
        else tokens.push_back(Token(TokenType::IDENTIFIER,word));
        //word<<" "<<idx<<endl;
    }

    vector<Token> lex(){
       int idx = 0;
       while(idx<len){
        skipWhiteSpace(idx);
        skipComments(idx);
        if(isDigit(idx)) getDigit(idx);
        else if(isOp(idx)) getOp(idx);
        else if(code[idx] == ';') {
            tokens.push_back(Token(TokenType::SEMICOLON,";"));
            idx++;
        }
        else if(code[idx] == '(') {
            tokens.push_back(Token(TokenType::OPEN_1,"("));
            idx++;
        }
        else if(code[idx] == ')') {
            tokens.push_back(Token(TokenType::CLOSE_1,")"));
            idx++;
        }
        else if(code[idx] == '{') {
            tokens.push_back(Token(TokenType::OPEN_2,"{"));
            idx++;
        }
        else if(code[idx] == '}') {
            tokens.push_back(Token(TokenType::CLOSE_2,"}"));
            idx++;
        }
        else if(isAlpha(idx)) getKeyword(idx);
        else idx++;
       }
       return tokens;
    }
    void skipWhiteSpace(int& idx){
        while((idx<len) && (code[idx] == ' '))idx++;
    }
    void skipComments(int& idx){
        if((code[idx] == '/') && (idx+1<len) && (code[idx+1]=='/')) {
            idx+=2;
            while((idx<len) && (code[idx] == '\n')) idx++;
        }
    }
};

class Parser{
    public:
    vector<Token> tokens;
    vector<Statement*> statements;
    int len;
    Parser(vector<Token> _tokens){
        tokens = _tokens;
        len = tokens.size();
    }
    void parse(){
        int idx = 0;
        while(idx<len) {
            // cout<<idx<<endl;
            statements.push_back(parseStatement(idx));
        }
    }

    Statement* parseVarDecl(int &idx){
        if(idx+2 >= len) throw runtime_error("out of index in parsing");
        if(tokens[idx].type != TokenType::IDENTIFIER) throw runtime_error("wrong declare/assign statement");
        auto id = tokens[idx++].val;
        if(tokens[idx].type != TokenType::EQ) throw runtime_error("wrong declare/assign statement");
        idx++;
        auto expr = parseExpression(idx);
        if((idx>= len) || (tokens[idx].type != TokenType::SEMICOLON)) throw runtime_error("; not found");
        idx++;
        return new VarDeclStatement(id,expr);
    }
    Statement* parseIf(int &idx){
        if((idx >= len) || (tokens[idx].type != TokenType::OPEN_1)) throw runtime_error("wrong if statement");
        idx++;
        auto cond = parseExpression(idx);
        if((idx >= len) || (tokens[idx].type != TokenType::CLOSE_1)) throw runtime_error("wrong if statement");

        if((idx >= len) || (tokens[idx].type != TokenType::OPEN_2)) throw runtime_error("wrong if statement");
        idx++;
        auto ifblock = parseBlock(idx);
        if((idx >= len) || (tokens[idx].type != TokenType::CLOSE_2)) throw runtime_error("wrong if statement");

        vector<Statement*> elseBlock;
        if((idx < len) && (tokens[idx].type == TokenType::ELSE)) {
            idx++;
            if((idx >= len) || (tokens[idx].type != TokenType::OPEN_2)) throw runtime_error("wrong else statement");
            idx++;
            elseBlock = parseBlock(idx);
            if((idx >= len) || (tokens[idx].type != TokenType::CLOSE_2)) throw runtime_error("wrong else statement");
        }
        return new IfStatement(cond,ifblock,elseBlock);
    }
        
    Statement* parseWhile(int &idx){
        if((idx >= len) || (tokens[idx].type != TokenType::WHILE)) throw runtime_error("wrong while statement");
        idx++; // at (
        if((idx >= len) || (tokens[idx].type != TokenType::OPEN_1)) throw runtime_error("wrong while statement");
        idx++; // at cond
        auto cond = parseExpression(idx);
        if((idx >= len) || (tokens[idx].type != TokenType::CLOSE_1)) throw runtime_error("wrong while statement");
        idx++; // at {
        if((idx >= len) || (tokens[idx].type != TokenType::OPEN_2)) throw runtime_error("wrong while statement");
        idx++; // at expr
        auto block = parseBlock(idx);
        if((idx >= len) || (tokens[idx].type != TokenType::CLOSE_2)) throw runtime_error("wrong while statement");
        idx++;
        return new WhileStatement(cond,block);
    }

    Statement* parsePrint(int &idx){
        if((idx >= len) || (tokens[idx].type != TokenType::OPEN_1)) throw runtime_error("wrong print statement");
        idx++;
        auto expr = parseExpression(idx);
        if((idx >= len) || (tokens[idx].type != TokenType::CLOSE_1)) throw runtime_error("wrong print statement");
        idx++;
        if((idx >= len) || (tokens[idx].type != TokenType::SEMICOLON)) throw runtime_error("wrong print statement");
        idx++;
        return new PrintStatement(expr);
    }

    vector<Statement*> parseBlock(int &idx){
        if(idx>=len) throw runtime_error("index errror");
        vector<Statement*> stmt;
        while((idx<len) && (tokens[idx].type != TokenType::CLOSE_2)){
            stmt.push_back(parseStatement(idx));
            //cout<<idx<<"while"<<endl;
        }
        return stmt;
    }

    Expr* parseExpression(int &idx){
        auto left = parseAdditive(idx);
        if(idx>=len) throw runtime_error("parsing error");
        while((idx<len) && 
            ((tokens[idx].type == TokenType::GT) || (tokens[idx].type == TokenType::LT)
            || (tokens[idx].type == TokenType::EQ))) {
            auto op = tokens[idx++].val;
            auto right = parseExpression(idx);
            left = new BinaryExpr(left,op,right);
        }
        return left;
    }

    Expr* parseAdditive(int &idx){
        if(idx>=len) throw runtime_error("parsing error");
        auto left = parseMultiplicative(idx);
        if(idx>=len) throw runtime_error("parsing error");
        while((idx<len) && 
            ((tokens[idx].type == TokenType::PLUS) || (tokens[idx].type == TokenType::MINUS))) {
            auto op = tokens[idx++].val;
            auto right = parseMultiplicative(idx);
            left = new BinaryExpr(left,op,right);
        }
        return left;
    }
    
    Expr* parseMultiplicative(int &idx){
        if(idx>=len) throw runtime_error("parsing error");
        auto left = parsePrimary(idx);
        if(idx>=len) throw runtime_error("parsing error");
        while((idx<len) && 
            ((tokens[idx].type == TokenType::MULT) || (tokens[idx].type == TokenType::DIV))) {
            auto op = tokens[idx++].val;
            auto right = parsePrimary(idx);
            left = new BinaryExpr(left,op,right);
        }
        return left;
    }

    Expr* parsePrimary(int &idx){
        if(idx>=len) throw runtime_error("parsing error");
        if((idx<len) && 
            ((tokens[idx].type == TokenType::IDENTIFIER))) {
            auto expr = new VarExpr(tokens[idx++].val);
            return expr;
        }
        if((idx<len) && 
            ((tokens[idx].type == TokenType::NUMBER))) {
            auto expr = new NumExpr(tokens[idx++].val);
            return expr;
        }
        if((tokens[idx].type == TokenType::OPEN_1)) {
            auto expr = parseExpression(++idx);
            if((idx>=len) ||
            (tokens[idx].type != TokenType::CLOSE_1)) throw runtime_error("parse error");
            idx++;
            return expr;
        }
        throw runtime_error("parse error");
    }
    


    Statement* parseStatement(int& idx){
        if(tokens[idx].type == TokenType::LET) return parseVarDecl(++idx);
        if(tokens[idx].type == TokenType::IF)return parseIf(++idx);
        if(tokens[idx].type == TokenType::WHILE) return parseWhile(idx);
        if(tokens[idx].type == TokenType::PRINT) return parsePrint(++idx);
        string name = "";
        Expr* expr;
        if(tokens[idx].type == TokenType::IDENTIFIER) {
            name = tokens[idx].val;
            idx++;
            if((idx >=len) || (tokens[idx].type != TokenType::EQ)) {
                throw runtime_error("wrongly ingested code");
            }
            idx++;
            expr = parseExpression(idx);
            if((idx >=len) || (tokens[idx].type != TokenType::SEMICOLON)) throw runtime_error("parse error");
            idx++;
            return new AssignStatement(name,expr);
        }
        throw runtime_error("parse error");
    }

};

class Interpreter {
    public:
    unordered_map<string,int> mm;
    //vector<Statement> statements;
    Interpreter(){
    }

    int eval(Expr* expr){
        if(auto numExpr = dynamic_cast<NumExpr*>(expr)) {
            return stoi(numExpr->val);
        }
        if(auto varExpr =  dynamic_cast<VarExpr*>(expr)) {
            return mm[varExpr->name];
        }
        if(auto binaryExpr = dynamic_cast<BinaryExpr*>(expr)) {
            auto left = eval(binaryExpr->left);
            auto right = eval(binaryExpr->right);
            auto op = binaryExpr->op;
            if(op == "+") return left + right;
            if(op == "-") return left - right;
            if(op == "*") return left * right;
            if(op == "/") {
                if(right == 0) throw runtime_error("div by 0");
                return left / right;
            }
            if(op == "<") return left < right;
            return left > right;
        }
        throw runtime_error("unknown expr error");
    }

    void run(vector<Statement*> statements) {
        for(auto it : statements){
            if(auto stmt =  dynamic_cast<IfStatement*>(it)) {
                if(eval(stmt->cond)) run(stmt->ifBlock);
                else run(stmt->elseBlock);
            }
            else if(it->val == 3) {
                auto stmtRaw = dynamic_cast<PrintStatement*>(it);
                cout<<eval(stmtRaw->expr)<<endl;
            }
            else  if(auto stmt =  dynamic_cast<WhileStatement*>(it)) {
                while(eval(stmt->cond)) run(stmt->body);
            }
            else  if(auto stmt = dynamic_cast<VarDeclStatement*>(it)) {
                mm[stmt->var] = eval(stmt->expr);
            }
            else  if(auto stmt = dynamic_cast<AssignStatement*>(it)) {
                if(mm.find(stmt->name) == mm.end()) throw runtime_error("undefined var");
                mm[stmt->name] = eval(stmt->expr);
            }
        }
    }
};

void testExample1(){
    string code = R"(
        let a = 10;
        let b = 20;
        while(a<b) {
            a = a+1;
        }
        print(a);
    )";
    Lexer lex(code);
    auto tokens = lex.lex();
    // for(auto it :tokens) cout<<it.val<<" ";
    // cout<<endl;
    Parser parser(tokens);
    parser.parse();
    Interpreter interpreter;
    interpreter.run(parser.statements);
}

int main(){
    testExample1();
    return 0;
}



