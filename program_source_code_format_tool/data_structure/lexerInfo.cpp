#include "lexerInfo.h"
using namespace std;
int num = 1;

MyList<Token> operators;
MyList<Token> keywords;

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "当前Token值："<< token.value<<" 对应类型："<<token.type<<std::endl;
    return os;
}

bool check_isalpha(char c) {
    // 检查字符是否是大写字母
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    // 检查字符是否是小写字母
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    // 如果不是字母，则返回 false
    return false;
}

bool isOperator(char value)
{
	std::string str(1, value);
	MyList<Token>::Node* node = operators.beginNode();
	while (node != NULL) {
		if(node->data.value == str)
			return true;
		node = node->next;  // 移动到下一个节点
	}
	return false;
}

void initOperators()
{
    operators.insert({"+", PLUS});
    operators.insert({"++", PLUSPLUS});
    operators.insert({"-", MINUS});
    operators.insert({"--", MINUSMINUS});
    operators.insert({"*", MULTIPLY});
    operators.insert({"/", DIVIDE});
    operators.insert({"%", MOD});
    operators.insert({"=", ASSIGN});
    operators.insert({">=", COMPARISON});
    operators.insert({"<=", COMPARISON});
    operators.insert({"==", COMPARISON});
    operators.insert({"!=", COMPARISON});
    operators.insert({"&&", AND});
    operators.insert({"||", OR});
    operators.insert({"(", LP});
    operators.insert({")", RP});
    operators.insert({"[", LBT});
    operators.insert({"]", RBT});
    operators.insert({"{", LBS});
    operators.insert({"}", RBS});
    operators.insert({";", SEMI});
    operators.insert({",", COMMA});
}

void initKeywords()
{
    keywords.insert({"_Alignas", _ALIGNAS_TOKEN});
    keywords.insert({"_Alignof", _ALIGNOF_TOKEN});
    keywords.insert({"_Atomic", _ATOMIC_TOKEN});
    keywords.insert({"_Bool", _BOOL_TOKEN});
    keywords.insert({"_Complex", _COMPLEX_TOKEN});
    keywords.insert({"_Generic", _GENERIC_TOKEN});
    keywords.insert({"_Imaginary", _IMAGINARY_TOKEN});
    keywords.insert({"_Noreturn", _NORETURN_TOKEN});
    keywords.insert({"_Static_assert", _STATIC_ASSERT_TOKEN});
    keywords.insert({"_Thread_local", _THREAD_LOCAL_TOKEN});

    keywords.insert({"auto", AUTO_TOKEN});
    keywords.insert({"break", BREAK_TOKEN});
    keywords.insert({"case", CASE_TOKEN});
    keywords.insert({"char", CHAR_TOKEN});  // 改为 CHAR_TOKEN
    keywords.insert({"const", CONST_TOKEN});
    keywords.insert({"continue", CONTINUE_TOKEN});
    keywords.insert({"default", DEFAULT_TOKEN});
    keywords.insert({"do", DO_TOKEN});
    keywords.insert({"double", DOUBLE_TOKEN});
    keywords.insert({"else", ELSE_TOKEN});
    keywords.insert({"enum", ENUM_TOKEN});
    keywords.insert({"extern", EXTERN_TOKEN});
    keywords.insert({"float", FLOAT_TOKEN});
    keywords.insert({"for", FOR_TOKEN});
    keywords.insert({"goto", GOTO_TOKEN});
    keywords.insert({"if", IF_TOKEN});
    keywords.insert({"inline", INLINE_TOKEN});
    keywords.insert({"int", INT_TOKEN});
    keywords.insert({"long", LONG_TOKEN});
    keywords.insert({"register", REGISTER_TOKEN});
    keywords.insert({"restrict", RESTRICT_TOKEN});
    keywords.insert({"return", RETURN_TOKEN});
    keywords.insert({"short", SHORT_TOKEN});
    keywords.insert({"signed", SIGNED_TOKEN});
    keywords.insert({"sizeof", SIZEOF_TOKEN});
    keywords.insert({"static", STATIC_TOKEN});
    keywords.insert({"struct", STRUCT_TOKEN});
    keywords.insert({"switch", SWITCH_TOKEN});
    keywords.insert({"typedef", TYPEDEF_TOKEN});
    keywords.insert({"union", UNION_TOKEN});
    keywords.insert({"unsigned", UNSIGNED_TOKEN});
    keywords.insert({"void", VOID_TOKEN});
    keywords.insert({"volatile", VOLATILE_TOKEN});
    keywords.insert({"while", WHILE_TOKEN});
}

