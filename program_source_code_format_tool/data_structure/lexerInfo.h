#pragma once
#include "MyList.h" 

enum TokenType
{
    ERROR_TOKEN,
    AUTO_TOKEN, 
    BREAK_TOKEN, 
    CASE_TOKEN, 
    CHAR_TOKEN,
    CONST_TOKEN, 
    CONTINUE_TOKEN, 
    DEFAULT_TOKEN, 
    DO_TOKEN, 
    DOUBLE_TOKEN, 
    ELSE_TOKEN, 
    ENUM_TOKEN, 
    EXTERN_TOKEN,
    FLOAT_TOKEN, 
    FOR_TOKEN, 
    GOTO_TOKEN, 
    IF_TOKEN, 
    INLINE_TOKEN, 
    INT_TOKEN, 
    LONG_TOKEN, 
    REGISTER_TOKEN, 
    RESTRICT_TOKEN, 
    RETURN_TOKEN, 
    SHORT_TOKEN, 
    SIGNED_TOKEN, 
    SIZEOF_TOKEN,
    STATIC_TOKEN, 
    STRUCT_TOKEN, 
    SWITCH_TOKEN, 
    TYPEDEF_TOKEN, 
    UNION_TOKEN, 
    UNSIGNED_TOKEN, 
    VOID_TOKEN, 
    VOLATILE_TOKEN, 
    WHILE_TOKEN, 
    _ALIGNAS_TOKEN, 
    _ALIGNOF_TOKEN,
    _ATOMIC_TOKEN, 
    _BOOL_TOKEN, 
    _COMPLEX_TOKEN, 
    _GENERIC_TOKEN, 
    _IMAGINARY_TOKEN, 
    _NORETURN_TOKEN, 
    _STATIC_ASSERT_TOKEN, 
    _THREAD_LOCAL_TOKEN, 
    IDENT,
    INT_CONST, 
    UNSIGNED_CONST, 
    LONG_CONST, 
    UNSIGNED_LONG_CONST, 
    DOUBLE_CONST, 
    FLOAT_CONST,
    LONG_DOUBLE_CONST, 
    CHAR_CONST, 
    STRING_CONST, 
    ASSIGN, 
    PLUS,       //"+"
    PLUSPLUS,   //"++"
    MINUS,      //"-"
    MINUSMINUS, //"--"  
    MULTIPLY,   //"*"
    DIVIDE, 	//"/" 
    MOD, 		//"%" 
    COMPARISON,  // "比较运算符： >= != <= == < >等"
    AND,     
    OR, 
    LP, 		//左括号"(" 
    RP, 		//右括号")" 
    LBT, 		//"["
    RBT, 		//"]"
    LBS, 		//"{"
    RBS, 		//"}"
    SEMI, 		//";" 
    COMMA,		//","
    END_OF_FILE	//
};

// 词法单元
struct Token
{
	std::string value;
    enum TokenType type;
    std::string description();
    
    Token() : value(""), type(ERROR_TOKEN) {}
    Token(const std::string& val,enum TokenType t) : value(val), type(t) {}
};

std::ostream& operator<<(std::ostream& os, const Token& token);
extern MyList<Token> keywords;
extern MyList<Token> operators;


bool check_isalpha(char c);
bool isOperator(char value); 
void initOperators();
void initKeywords();

// 词法分析器
class Lexer {
public:
    Lexer(const std::string& src) : src(src), index(0) {}
    
    MyList<Token> tokenize() {
        MyList<Token> tokens;
        while (index < src.size()) {
        	//如果是空白字符，如：空格、制表符或换行符，则直接跳过 
        	std::cout<<"检测字符: "<<src[index]<<std::endl;
            if (std::isspace(src[index])) {
                ++index;
            }
            // 处理预处理指令
        	else if (src[index] == '#') {
            	skipPreprocessorDirective();
	        }
            else if (check_isalpha(src[index])) {
                tokens.insert(identifierOrKeyword());
            }
            else if (std::isdigit(src[index])) {
                tokens.insert(constant());
            }
            else if (isOperator(src[index])) {
            	Token tt = operatorToken();
                tokens.insert(tt);
                cout<<"查询到数据："<<tt.value<<tt.type<< endl;
            }
            else {
            	Token token = {std::string(1, src[index]),ERROR_TOKEN};
//                tokens.insert(token);
                ++index;
            }
        }
        return tokens;
    }
    
    void skipPreprocessorDirective() {
    	// 跳过整个预处理指令直到换行符
    	while (index < src.size() && src[index] != '\n') {
	        ++index;
    	}
    	// 跳过换行符
    	if (index < src.size() && src[index] == '\n') {
        	++index;
	    }
	}

private:
    std::string src;
    size_t index;

	Token identifierOrKeyword() {
	    size_t start = index; // 记录标识符/关键字的起始位置
	    while (index < src.size() && (std::isalnum(src[index]) || src[index] == '_')) {
	        ++index; // 扩展到下一个字符，直到遇到非字母数字字符
	    }
	    std::string value = src.substr(start, index - start); // 提取标识符/关键字的字符串
	    cout<<"identifierOrKeyword 提取关键字信息：获取到单词："<<value<<endl;
	    Token token = {value,IDENT };
	    MyList<Token>::Node* node = keywords.beginNode();  // 从头部节点开始
		while (node != NULL) {
			if(node->data.value == value)
			{
				token.type = node->data.type;
				cout<<"插入关键字："<<token<<endl;
				return token;
			}	
			node = node->next;  // 移动到下一个节点
		}
		
		cout<<"默认返回关键字："<<token<<endl;
	    return token; // 返回标识符 Token
	}

    Token constant() {
        size_t start = index;
        bool hasDot = false;
        bool hasE = false;
        while (index < src.size() && (std::isdigit(src[index]) || src[index] == '.' || src[index] == 'e' || src[index] == 'E')) {
            if (src[index] == '.') {
                hasDot = true;
            }
            if (src[index] == 'e' || src[index] == 'E') {
                hasE = true;
            }
            ++index;
        }
        std::string value = src.substr(start, index - start);
        if (hasDot) {
        	Token token = { value, hasE ? DOUBLE_CONST : FLOAT_CONST };
        	cout<<"获取到数字："<<token<<endl;
            return token;
        }
        return { value, INT_CONST };
    }

	//c/c++中的操作符最多两位，因此需要检测两次
	//第一次去第一个字符，判断是否是操作符
	//第二次取第一个和第二个合并的字符，再次判断
	//三种情况：
	//    1        2 
	//    成功    失败   
	//    成功    成功
	//    失败    成功  如：!=
    Token operatorToken() {
        std::string value(1, src[index]);
        std::string  withTheNextValue = value;
        if(index + 1 < src.size())
			withTheNextValue += src[index + 1];
    
        ++index;
   	    Token token = {withTheNextValue,ERROR_TOKEN };
        for (auto* node = operators.beginNode(); node != NULL; node = node->next) {
            if(node->data.value == withTheNextValue)
            {
            	token.type = node->data.type;
            	++index;
            	return token;
			}
        }
        
        for (auto* node = operators.beginNode(); node != NULL; node = node->next) {
            if(node->data.value == value)
            {
            	token.type = node->data.type;
            	token.value = value;
            	return token;
			}
        }
		cout<<"没有检测到操作符："<< value<<endl; 
		return token;
    }
};
