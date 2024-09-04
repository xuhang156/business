#include "lexerInfo.h"

MyList<Token> operators;
MyList<Token> keywords;

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "��ǰTokenֵ��"<< token.value<<" ��Ӧ���ͣ�"<<token.type<<std::endl;
    return os;
}

std::string Token::description()
{
	std::string text = "";
    switch (type) {
    	case ERROR_TOKEN:
            return "���� Token: " + value;
        case AUTO_TOKEN:
        case BREAK_TOKEN:
        case CASE_TOKEN:
        case CHAR_TOKEN:
        case CONST_TOKEN:
        case CONTINUE_TOKEN:
        case DEFAULT_TOKEN:
        case DO_TOKEN:
        case DOUBLE_TOKEN:
        case ELSE_TOKEN:
        case ENUM_TOKEN:
        case EXTERN_TOKEN:
        case FLOAT_TOKEN:
        case FOR_TOKEN:
        case GOTO_TOKEN:
        case IF_TOKEN:
        case INLINE_TOKEN:
        case INT_TOKEN:
        case LONG_TOKEN:
        case REGISTER_TOKEN:
        case RESTRICT_TOKEN:
        case RETURN_TOKEN:
        case SHORT_TOKEN:
        case SIGNED_TOKEN:
        case SIZEOF_TOKEN:
        case STATIC_TOKEN:
        case STRUCT_TOKEN:
        case SWITCH_TOKEN:
        case TYPEDEF_TOKEN:
        case UNION_TOKEN:
        case UNSIGNED_TOKEN:
        case VOID_TOKEN:
        case VOLATILE_TOKEN:
        case WHILE_TOKEN:
        case _ALIGNAS_TOKEN:
        case _ALIGNOF_TOKEN:
        case _ATOMIC_TOKEN:
        case _BOOL_TOKEN:
        case _COMPLEX_TOKEN:
        case _GENERIC_TOKEN:
        case _IMAGINARY_TOKEN:
        case _NORETURN_TOKEN:
        case _STATIC_ASSERT_TOKEN:
        case _THREAD_LOCAL_TOKEN:
            text = "�ؼ���:     	";
            break;
        case IDENT:
            text = "��ʶ��:     	";
            break;
        case INT_CONST:
            text = "��������:   	";
            break;
        case DOUBLE_CONST:
            text = "˫���ȸ��㳣��: ";
            break;
        case FLOAT_CONST:
            text = "�����ȸ��㳣��: ";
            break;
        case LONG_DOUBLE_CONST:
            text = "��˫���ȸ��㳣��:";
            break;
        case CHAR_CONST:
        	text = "�ַ�����: 		";
        	break;
        case STRING_CONST:
            text = "�ַ�������: 	";
            break;
        case ASSIGN:
            text = "��ֵ�����: 	";
            break;
        case PLUS:
            text = "�ӷ������: 	";
            break;
        case PLUSPLUS:
            text = "���������: 	";
            break;
        case MINUS:
            text = "���������: 	";
            break;
        case MINUSMINUS:
            text = "�Լ������: 	";
            break;
        case MULTIPLY:
            text = "�˷������: 	";
            break;
        case DIVIDE:
            text = "���������: 	";
            break;
        case MOD:
            text = "ȡģ�����: 	";
            break;
        case COMPARISON:
            text = "�Ƚ������: 	";
            break;
        case AND:
            text = "�߼��������: 	";
            break;
        case OR:
            text = "�߼��������: 	";
            break;
        case LP:
            text = "������: 		";
            break;
        case RP:
            text = "������: 		";
            break;
        case LBT:
            text = "��������: 		";
            break;
        case RBT:
            text = "��������: 		";
            break;
        case LBS:
            text = "������: 		";
            break;
        case RBS:
            text = "�һ�����: 		";
            break;
        case SEMI:
            text = "�ֺ�: 			";
            break;
        case COMMA:
            text = "����:			";
            break;
        default:
            text = "δ֪ Token: 	";
            break;
    }
    return text;
}

bool check_isalpha(char c) {
    // ����ַ��Ƿ��Ǵ�д��ĸ
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    // ����ַ��Ƿ���Сд��ĸ
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    // ���������ĸ���򷵻� false
    return false;
}

bool isOperator(char value)
{
	std::string str(1, value);
	MyList<Token>::Node* node = operators.beginNode();
	while (node != NULL) {
		if(node->data.value == str)
			return true;
		node = node->next;  // �ƶ�����һ���ڵ�
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
    operators.insert({">", COMPARISON});
    operators.insert({"<", COMPARISON});
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
    keywords.insert({"char", CHAR_TOKEN});  // ��Ϊ CHAR_TOKEN
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

