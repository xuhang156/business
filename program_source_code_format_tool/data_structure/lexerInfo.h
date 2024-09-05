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
    COMPARISON,  // "�Ƚ�������� >= != <= == < >��"
    AND,     
    OR, 
    LP, 		//������"(" 
    RP, 		//������")" 
    LBT, 		//"["
    RBT, 		//"]"
    LBS, 		//"{"
    RBS, 		//"}"
    SEMI, 		//";" 
    COMMA,		//","
    END_OF_FILE	//
};

// �ʷ���Ԫ
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

// �ʷ�������
class Lexer {
public:
    Lexer(const std::string& src) : src(src), index(0) {}
    
    MyList<Token> tokenize() {
        MyList<Token> tokens;
        while (index < src.size()) {
        	//����ǿհ��ַ����磺�ո��Ʊ�����з�����ֱ������ 
        	std::cout<<"����ַ�: "<<src[index]<<std::endl;
            if (std::isspace(src[index])) {
                ++index;
            }
            // ����Ԥ����ָ��
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
                cout<<"��ѯ�����ݣ�"<<tt.value<<tt.type<< endl;
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
    	// ��������Ԥ����ָ��ֱ�����з�
    	while (index < src.size() && src[index] != '\n') {
	        ++index;
    	}
    	// �������з�
    	if (index < src.size() && src[index] == '\n') {
        	++index;
	    }
	}

private:
    std::string src;
    size_t index;

	Token identifierOrKeyword() {
	    size_t start = index; // ��¼��ʶ��/�ؼ��ֵ���ʼλ��
	    while (index < src.size() && (std::isalnum(src[index]) || src[index] == '_')) {
	        ++index; // ��չ����һ���ַ���ֱ����������ĸ�����ַ�
	    }
	    std::string value = src.substr(start, index - start); // ��ȡ��ʶ��/�ؼ��ֵ��ַ���
	    cout<<"identifierOrKeyword ��ȡ�ؼ�����Ϣ����ȡ�����ʣ�"<<value<<endl;
	    Token token = {value,IDENT };
	    MyList<Token>::Node* node = keywords.beginNode();  // ��ͷ���ڵ㿪ʼ
		while (node != NULL) {
			if(node->data.value == value)
			{
				token.type = node->data.type;
				cout<<"����ؼ��֣�"<<token<<endl;
				return token;
			}	
			node = node->next;  // �ƶ�����һ���ڵ�
		}
		
		cout<<"Ĭ�Ϸ��عؼ��֣�"<<token<<endl;
	    return token; // ���ر�ʶ�� Token
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
        	cout<<"��ȡ�����֣�"<<token<<endl;
            return token;
        }
        return { value, INT_CONST };
    }

	//c/c++�еĲ����������λ�������Ҫ�������
	//��һ��ȥ��һ���ַ����ж��Ƿ��ǲ�����
	//�ڶ���ȡ��һ���͵ڶ����ϲ����ַ����ٴ��ж�
	//���������
	//    1        2 
	//    �ɹ�    ʧ��   
	//    �ɹ�    �ɹ�
	//    ʧ��    �ɹ�  �磺!=
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
		cout<<"û�м�⵽��������"<< value<<endl; 
		return token;
    }
};
