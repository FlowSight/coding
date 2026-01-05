
// Design a simple compiler for a custom programming language using your preferred language (Python, TypeScript, C++, etc.).

// Language Specification
// Define the basic syntax of the language, including:

// Variable Declarations: Support declaring variables (e.g., let x = 5).
// Arithmetic Operations: Basic math (+, -, *, /).
// Conditionals: if-else structures.
// Loops: while loops.
// Requirements
// Implement a compiler that translates the source code of this custom language into target code (e.g., Python code, assembly, or a simple bytecode interpreted by a VM you write).

// Deliverables
// Source code for the compiler (lexer, parser, code generator/interpreter).
// At least three code examples in your custom language.
// Expected execution results for those examples.
// Example Idea
// let a = 10;
// let b = 20;
// if (a < b) {
//   while (a < b) {
//     a = a + 1;
//   }
// }
// print(a);

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <cctype>

using namespace std;

// ==================== LEXER ====================
enum class TokenType {
    LET, IF, ELSE, WHILE, PRINT,
    IDENTIFIER, NUMBER,
    ASSIGN, PLUS, MINUS, STAR, SLASH, MOD,
    LT, GT, LE, GE, EQ, NE,
    LPAREN, RPAREN, LBRACE, RBRACE,
    SEMICOLON, EOF_TOKEN
};

struct Token {
    TokenType type;
    string value;
    int line;
    
    Token(TokenType t, const string& v, int l = 0) : type(t), value(v), line(l) {}
};

class Lexer {
private:
    string input;
    size_t pos;
    int line;
    
    char current() {
        return pos < input.length() ? input[pos] : '\0';
    }
    
    void advance() {
        if (current() == '\n') line++;
        pos++;
    }
    
    void skipWhitespace() {
        while (isspace(current())) advance();
    }
    
    void skipComment() {
        if (current() == '/' && pos + 1 < input.length() && input[pos + 1] == '/') {
            while (current() != '\n' && current() != '\0') advance();
        }
    }
    
public:
    Lexer(const string& src) : input(src), pos(0), line(1) {}
    
    vector<Token> tokenize() {
        vector<Token> tokens;
        
        while (pos < input.length()) {
            skipWhitespace();
            skipComment();
            
            if (current() == '\0') break;
            
            // Keywords and identifiers
            if (isalpha(current()) || current() == '_') {
                string word;
                while (isalnum(current()) || current() == '_') {
                    word += current();
                    advance();
                }
                
                if (word == "let") tokens.emplace_back(TokenType::LET, word, line);
                else if (word == "if") tokens.emplace_back(TokenType::IF, word, line);
                else if (word == "else") tokens.emplace_back(TokenType::ELSE, word, line);
                else if (word == "while") tokens.emplace_back(TokenType::WHILE, word, line);
                else if (word == "print") tokens.emplace_back(TokenType::PRINT, word, line);
                else tokens.emplace_back(TokenType::IDENTIFIER, word, line);
                continue;
            }
            
            // Numbers
            if (isdigit(current())) {
                string num;
                while (isdigit(current())) {
                    num += current();
                    advance();
                }
                tokens.emplace_back(TokenType::NUMBER, num, line);
                continue;
            }
            
            // Operators and punctuation
            char ch = current();
            advance();
            
            if (ch == '=') {
                if (current() == '=') {
                    advance();
                    tokens.emplace_back(TokenType::EQ, "==", line);
                } else {
                    tokens.emplace_back(TokenType::ASSIGN, "=", line);
                }
            } else if (ch == '!') {
                if (current() == '=') {
                    advance();
                    tokens.emplace_back(TokenType::NE, "!=", line);
                }
            } else if (ch == '<') {
                if (current() == '=') {
                    advance();
                    tokens.emplace_back(TokenType::LE, "<=", line);
                } else {
                    tokens.emplace_back(TokenType::LT, "<", line);
                }
            } else if (ch == '>') {
                if (current() == '=') {
                    advance();
                    tokens.emplace_back(TokenType::GE, ">=", line);
                } else {
                    tokens.emplace_back(TokenType::GT, ">", line);
                }
            } else if (ch == '+') tokens.emplace_back(TokenType::PLUS, "+", line);
            else if (ch == '-') tokens.emplace_back(TokenType::MINUS, "-", line);
            else if (ch == '*') tokens.emplace_back(TokenType::STAR, "*", line);
            else if (ch == '/') tokens.emplace_back(TokenType::SLASH, "/", line);
            else if (ch == '%') tokens.emplace_back(TokenType::MOD, "%", line);
            else if (ch == '(') tokens.emplace_back(TokenType::LPAREN, "(", line);
            else if (ch == ')') tokens.emplace_back(TokenType::RPAREN, ")", line);
            else if (ch == '{') tokens.emplace_back(TokenType::LBRACE, "{", line);
            else if (ch == '}') tokens.emplace_back(TokenType::RBRACE, "}", line);
            else if (ch == ';') tokens.emplace_back(TokenType::SEMICOLON, ";", line);
        }
        
        tokens.emplace_back(TokenType::EOF_TOKEN, "", line);
        return tokens;
    }
};

// ==================== AST NODES ====================
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class Expr : public ASTNode {};
class Stmt : public ASTNode {};

class NumberExpr : public Expr {
public:
    int value;
    NumberExpr(int v) : value(v) {}
};

class VarExpr : public Expr {
public:
    string name;
    VarExpr(const string& n) : name(n) {}
};

class BinaryExpr : public Expr {
public:
    shared_ptr<Expr> left, right;
    string op;
    BinaryExpr(shared_ptr<Expr> l, const string& o, shared_ptr<Expr> r) 
        : left(l), op(o), right(r) {}
};

class PrintStmt : public Stmt {
public:
    shared_ptr<Expr> expr;
    PrintStmt(shared_ptr<Expr> e) : expr(e) {}
};

class VarDeclStmt : public Stmt {
public:
    string name;
    shared_ptr<Expr> value;
    VarDeclStmt(const string& n, shared_ptr<Expr> v) : name(n), value(v) {}
};

class AssignStmt : public Stmt {
public:
    string name;
    shared_ptr<Expr> value;
    AssignStmt(const string& n, shared_ptr<Expr> v) : name(n), value(v) {}
};

class IfStmt : public Stmt {
public:
    shared_ptr<Expr> cond;
    vector<shared_ptr<Stmt>> thenBranch, elseBranch;
    IfStmt(shared_ptr<Expr> c, vector<shared_ptr<Stmt>> t, vector<shared_ptr<Stmt>> e = {})
        : cond(c), thenBranch(t), elseBranch(e) {}
};

class WhileStmt : public Stmt {
public:
    shared_ptr<Expr> cond;
    vector<shared_ptr<Stmt>> body;
    WhileStmt(shared_ptr<Expr> c, vector<shared_ptr<Stmt>> b) : cond(c), body(b) {}
};

// ==================== PARSER ====================
class Parser {
private:
    vector<Token> tokens;
    size_t pos;
    
    Token current() {
        return pos < tokens.size() ? tokens[pos] : tokens.back();
    }
    
    void advance() {
        if (pos < tokens.size()) pos++;
    }
    
    bool check(TokenType type) {
        return current().type == type;
    }
    
    bool match(TokenType type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }
    
    Token consume(TokenType type, const string& msg) {
        if (check(type)) {
            Token t = current();
            advance();
            return t;
        }
        throw runtime_error(msg);
    }
    
public:
    Parser(const vector<Token>& t) : tokens(t), pos(0) {}
    
    vector<shared_ptr<Stmt>> parse() {
        vector<shared_ptr<Stmt>> stmts;
        while (!check(TokenType::EOF_TOKEN)) {
            stmts.push_back(parseStatement());
        }
        return stmts;
    }
    
private:
    shared_ptr<Stmt> parseStatement() {
        if (match(TokenType::LET)) return parseVarDecl();
        if (match(TokenType::IF)) return parseIf();
        if (match(TokenType::WHILE)) return parseWhile();
        if (match(TokenType::PRINT)) return parsePrint();
        
        // Assignment or error
        if (check(TokenType::IDENTIFIER)) {
            string name = current().value;
            advance();
            if (match(TokenType::ASSIGN)) {
                auto expr = parseExpression();
                consume(TokenType::SEMICOLON, "Expected ';'");
                return make_shared<AssignStmt>(name, expr);
            }
        }
        throw runtime_error("Unexpected token");
    }
    
    shared_ptr<Stmt> parseVarDecl() {
        string name = consume(TokenType::IDENTIFIER, "Expected identifier").value;
        consume(TokenType::ASSIGN, "Expected '='");
        auto expr = parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';'");
        return make_shared<VarDeclStmt>(name, expr);
    }
    
    shared_ptr<Stmt> parseIf() {
        consume(TokenType::LPAREN, "Expected '('");
        auto cond = parseExpression();
        consume(TokenType::RPAREN, "Expected ')'");
        
        consume(TokenType::LBRACE, "Expected '{'");
        auto thenBranch = parseBlock();
        consume(TokenType::RBRACE, "Expected '}'");
        
        vector<shared_ptr<Stmt>> elseBranch;
        if (match(TokenType::ELSE)) {
            consume(TokenType::LBRACE, "Expected '{'");
            elseBranch = parseBlock();
            consume(TokenType::RBRACE, "Expected '}'");
        }
        
        return make_shared<IfStmt>(cond, thenBranch, elseBranch);
    }
    
    shared_ptr<Stmt> parseWhile() {
        consume(TokenType::LPAREN, "Expected '('");
        auto cond = parseExpression();
        consume(TokenType::RPAREN, "Expected ')'");
        
        consume(TokenType::LBRACE, "Expected '{'");
        auto body = parseBlock();
        consume(TokenType::RBRACE, "Expected '}'");
        
        return make_shared<WhileStmt>(cond, body);
    }
    
    shared_ptr<Stmt> parsePrint() {
        consume(TokenType::LPAREN, "Expected '('");
        auto expr = parseExpression();
        consume(TokenType::RPAREN, "Expected ')'");
        consume(TokenType::SEMICOLON, "Expected ';'");
        return make_shared<PrintStmt>(expr);
    }
    
    vector<shared_ptr<Stmt>> parseBlock() {
        vector<shared_ptr<Stmt>> stmts;
        while (!check(TokenType::RBRACE) && !check(TokenType::EOF_TOKEN)) {
            stmts.push_back(parseStatement());
        }
        return stmts;
    }
    
    shared_ptr<Expr> parseExpression() {
        return parseComparison();
    }
    
    shared_ptr<Expr> parseComparison() {
        auto expr = parseAdditive();
        
        while (check(TokenType::LT) || check(TokenType::GT) || 
               check(TokenType::LE) || check(TokenType::GE) ||
               check(TokenType::EQ) || check(TokenType::NE)) {
            string op = current().value;
            advance();
            auto right = parseAdditive();
            expr = make_shared<BinaryExpr>(expr, op, right);
        }
        
        return expr;
    }
    
    shared_ptr<Expr> parseAdditive() {
        auto expr = parseMultiplicative();
        
        while (check(TokenType::PLUS) || check(TokenType::MINUS)) {
            string op = current().value;
            advance();
            auto right = parseMultiplicative();
            expr = make_shared<BinaryExpr>(expr, op, right);
        }
        
        return expr;
    }
    
    shared_ptr<Expr> parseMultiplicative() {
        auto expr = parsePrimary();
        
        while (check(TokenType::STAR) || check(TokenType::SLASH) || check(TokenType::MOD)) {
            string op = current().value;
            advance();
            auto right = parsePrimary();
            expr = make_shared<BinaryExpr>(expr, op, right);
        }
        
        return expr;
    }
    
    shared_ptr<Expr> parsePrimary() {
        if (check(TokenType::NUMBER)) {
            int val = stoi(current().value);
            advance();
            return make_shared<NumberExpr>(val);
        }
        
        if (check(TokenType::IDENTIFIER)) {
            string name = current().value;
            advance();
            return make_shared<VarExpr>(name);
        }
        
        if (match(TokenType::LPAREN)) {
            auto expr = parseExpression();
            consume(TokenType::RPAREN, "Expected ')'");
            return expr;
        }
        
        throw runtime_error("Expected expression");
    }
};

// ==================== INTERPRETER ====================
class Interpreter {
private:
    unordered_map<string, int> variables;
    
public:
    int evalExpr(shared_ptr<Expr> expr) {
        if (auto num = dynamic_pointer_cast<NumberExpr>(expr)) {
            return num->value;
        }
        
        if (auto var = dynamic_pointer_cast<VarExpr>(expr)) {
            if (variables.find(var->name) == variables.end()) {
                throw runtime_error("Undefined variable: " + var->name);
            }
            return variables[var->name];
        }
        
        if (auto bin = dynamic_pointer_cast<BinaryExpr>(expr)) {
            int left = evalExpr(bin->left);
            int right = evalExpr(bin->right);
            
            if (bin->op == "+") return left + right;
            if (bin->op == "-") return left - right;
            if (bin->op == "*") return left * right;
            if (bin->op == "/") {
                if (right == 0) throw runtime_error("Division by zero");
                return left / right;
            }
            if (bin->op == "%") return left % right;
            if (bin->op == "<") return left < right ? 1 : 0;
            if (bin->op == ">") return left > right ? 1 : 0;
            if (bin->op == "<=") return left <= right ? 1 : 0;
            if (bin->op == ">=") return left >= right ? 1 : 0;
            if (bin->op == "==") return left == right ? 1 : 0;
            if (bin->op == "!=") return left != right ? 1 : 0;
        }
        
        throw runtime_error("Unknown expression type");
    }
    
    void execute(const vector<shared_ptr<Stmt>>& stmts) {
        for (auto& stmt : stmts) {
            if (auto print = dynamic_pointer_cast<PrintStmt>(stmt)) {
                cout << evalExpr(print->expr) << endl;
            } else if (auto decl = dynamic_pointer_cast<VarDeclStmt>(stmt)) {
                variables[decl->name] = evalExpr(decl->value);
            } else if (auto assign = dynamic_pointer_cast<AssignStmt>(stmt)) {
                variables[assign->name] = evalExpr(assign->value);
            } else if (auto ifStmt = dynamic_pointer_cast<IfStmt>(stmt)) {
                if (evalExpr(ifStmt->cond) != 0) {
                    execute(ifStmt->thenBranch);
                } else {
                    execute(ifStmt->elseBranch);
                }
            } else if (auto whileStmt = dynamic_pointer_cast<WhileStmt>(stmt)) {
                while (evalExpr(whileStmt->cond) != 0) {
                    execute(whileStmt->body);
                }
            }
        }
    }
};

// ==================== TEST METHODS ====================
void testExample1() {
    cout << "=== Example 1: If + While ===" << endl;
    string code = R"(
        let a = 10;
        let b = 20;
        if (a < b) {
            while (a < b) {
                a = a + 1;
            }
        }
        print(a);
    )";
    
    Lexer lexer(code);
    Parser parser(lexer.tokenize());
    Interpreter interpreter;
    interpreter.execute(parser.parse());
}

void testExample2() {
    cout << "=== Example 2: Arithmetic Operations ===" << endl;
    string code = R"(
        let x = 5;
        let y = 3;
        let result = x * y + 2;
        print(result);
    )";
    
    Lexer lexer(code);
    Parser parser(lexer.tokenize());
    Interpreter interpreter;
    interpreter.execute(parser.parse());
}

void testExample3() {
    cout << "=== Example 3: Factorial ===" << endl;
    string code = R"(
        let n = 5;
        let fact = 1;
        while (n > 1) {
            fact = fact * n;
            n = n - 1;
        }
        print(fact);
    )";
    
    Lexer lexer(code);
    Parser parser(lexer.tokenize());
    Interpreter interpreter;
    interpreter.execute(parser.parse());
}

// ==================== MAIN ====================
int main() {
    testExample1();
    cout << endl;
    testExample2();
    cout << endl;
    testExample3();
    
    return 0;
}

