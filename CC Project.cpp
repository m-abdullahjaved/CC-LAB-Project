// UPDATED by M. Abdullah Javed 
// 01:17 AM [31/12/2022]

#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string> 
#include <stack> 
#include <vector> 

#define EQUAL_TO "->" 
#define COMMA ","
#define DOT "."
#define OPEN_PAREN "(" 
#define CLOS_PAREN ")" 
#define OPEN_BRACE "{" 
#define CLOS_BRACE "}"
using namespace std;

bool isOperator(string str) {
	vector<string> operators = { "plus", "minus", "mul", "div",
	"equal", "lesser", "gte", "lte",
	"greater", "neq", "not", "or", "and",
   "plus->", "minus->", "div->", "mul->" };
	for (auto x : operators) {
		if (x == str)
			return true;
	}
	return false;
}
bool isKeyword(string str) {
	vector<string> keywords = { "agar", "warna agar",
	"fixed", "warna",
	 "karo", "jab_tak" };
	for (auto x : keywords) {
		if (str == x)
			return true;
	}
	return false;
}
bool isDataType(string var) {
	vector<string> dataType = { "dec", "num",
	"alpha", "logical", "text" };
	for (auto x : dataType) {
		if (x == var)
			return true;
	}
	return false;
}
bool isConstant(string str) {
	for (auto x : str) {
		if (!isdigit(x))
			return false;
	}
	return true;
}
bool isSpecialChar(char str) {
	vector<char> voc = { '~', '!', '_', '#', '%', '^', '&', '*',
   '<', '>', '?', '`', '.', ',', ':', '"' };
	for (auto x : voc) {
		if (x == str)
			return true;
	}
	return false;
}
bool isIdentifier(string pTok) {
	if (isDataType(pTok)) {
		return false;
	}
	if (pTok[0] == '@' || pTok[0] == '$' || isalpha(pTok[0])) {
		for (int i = 0; i < pTok.length(); i++) {
			string temp(1, pTok[i]);
			if (isSpecialChar(pTok[i]) || isOperator(temp)) {
				return false;
			}
			else if (i == pTok.length()) {
				return true;
			}
		}
		return true;
	}
	return false;
}
string evaluateExp(string a, string b, string op) {
	int op1 = stoi(a);
	int op2 = stoi(b);
	if (op == "plus")
		return to_string(op1 + op2);
	else if (op == "minus")
		return to_string(op1 - op2);
	else if (op == "mul")
		return to_string(op1 * op2);
	else if (op == "div")
		return to_string(op1 / op2);

	return "-1";
}
bool evaluateCondition(string op1, string op2, string op) {
	int Op1 = stoi(op1);
	int Op2 = stoi(op2);
	if (op == "greater") {
		return Op1 > Op2;
	}
	else if (op == "lesser") {
		return Op1 < Op2;
	}
	else if (op == "gte") {
		return Op1 >= Op2;
	}
	else if (op == "lte") {
		return Op1 <= Op2;
	}
	else if (op == "equal") {
		return Op1 == Op2;
	}
	else if (op == "neq") {
		return Op1 != Op2;
	}
	return false;
}

class Node {
	string Identifer, Type, Value;
	int line_no;
	Node* ref, * next;
	friend class SymbolTable;
public:
	Node() :Identifer{}, Type{}, Value{}, line_no{} {
		next = NULL;
		ref = NULL;
	}
	Node(string Id, string value, string type, int line, Node*
		refer = NULL) {
		this->Identifer = Id;
		this->Value = value;
		this->Type = type;
		this->line_no = line;
		this->next = NULL;
		this->ref = refer;
	}
	void print() {
		cout << left << setw(12) << line_no << setw(10) << Type
			<< setw(18) <<
			Identifer << setw(15) << Value << setw(20) << ref
			<< endl;
	}
	// Getters 
	string getIdentifier() const { return Identifer; }
	string getValue() const { return Value; }
	string getType() const { return Type; }
	int getLineNo() const { return line_no; }
	// Setters 
	void setIdentifer(string id) {
		this->Identifer = id;
	}
	void setValue(string val) {
		this->Value = val;
	}
	void setType(string typ) {
		this->Type = typ;
	}
	void setLineNo(int line) {
		this->line_no = line;
	}
};
class Token {
	string mtoken;
	bool mValid;
public:
	Token() {
		mtoken = "";
		mValid = false;
	}
	Token(string tok) {
		mtoken = tok;
		mValid = false;
	}
	Token(const Token& RHS) {
		this->mtoken = RHS.mtoken;
		this->mValid = RHS.mValid;
	}
	Token(string pTok, bool pV) {
		mtoken = pTok;
		mValid = pV;
	}
	string getToken() { return mtoken; }
	bool isValid() { return mValid; }
	void setToken(string pV) { mtoken = pV; }
	void setValid(bool pV) { mValid = pV; }
};
class SymbolTable {
	Node* head;
public:
	SymbolTable() {
		head = NULL;
	}
	void printList() {
		cout << left << setw(12) << "Line No" << setw(10) <<
			"Type" << setw(18) <<
			"Identifier" << setw(15) << "Value" << "Reference"
			<< endl;
		Node* temp = head;
		while (temp != NULL) {
			temp->print();
			temp = temp->next;
		}
		cout << endl;
	}
	bool insertNode(string type, string id, string value, int
		line, Node* ref = NULL) {
		Node* newNode = new Node(id, value, type, line, ref);
		newNode->next = head;
		head = newNode;
		return true;
	}

	Node* searchIdentifier(string id) {
		Node* temp = head;
		while (temp != NULL && temp->Identifer != id) {
			temp = temp->next;
		}
		return temp;
	}
	bool deleteIdentifier(string id) {
		if (head == NULL)
			return false;
		else if (head->Identifer == id) {
			head = head->next;
			return true;
		}
		else {
			Node* prev = head;
			Node* temp = head->next;
			while (temp != NULL && temp->Identifer != id) {
				prev = temp;
				temp = temp->next;
			}
			if (temp == NULL)
				return false;
			prev->next = temp->next;
			delete temp;
			return true;
		}
		return false;
	}
	bool updateIdentifier(string p_id, string type, string id,
		string val, int line) {
		Node* temp = head;
		while (temp != NULL) {
			if (temp->Identifer == p_id) {
				temp->Identifer = id;
				temp->line_no = line;
				temp->Value = val;
				temp->Type = type;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
};
vector<Token> tokenizeInstruction(string mData) {
	vector<Token> tokens;
	string token = "";
	for (auto x : mData)
	{
		if (x == ' ')
		{
			Token t = Token(token, false);
			tokens.push_back(t);
			token = "";
		}
		else {
			token = token + x;
		}
	}
	Token t = Token(token, false);
	tokens.push_back(t);
	return tokens;
}
class Lexer {
	vector<string> mInstructions;
public:
	Lexer() {
		mInstructions = {};
	}
	Lexer(vector<string> pTokens) {
		mInstructions = pTokens;
	}
	bool validateToken(Token pTok) {
		string tok = pTok.getToken();
		if (isDataType(tok)) {
			//cout << "Data Type: " << tok << endl; 
			pTok.setValid(true);
		}
		else if (isKeyword(tok)) {
			//cout << "Keyword: " << tok << endl; 
			pTok.setValid(true);
		}
		else if (isOperator(tok)) {
			//cout << "Operator: " << tok << endl; 
			pTok.setValid(true);
		}
		else if (isConstant(tok)) {
			//cout << "Digit: " << tok << endl; 
			pTok.setValid(true);
		}
		else if (tok == DOT) {
			//cout << "DOT: " << tok << endl; 
			pTok.setValid(true);
		}
		else if (isIdentifier(tok)) {
			//cout << "Identifier: " << tok << endl; 
			pTok.setValid(true);
		}

		else if (tok[0] == '"' && tok[tok.length() - 1] == '"') {
			//cout << "String: " << tok << endl;
			pTok.setValid(true);
		}
		else if (tok == OPEN_BRACE || tok == CLOS_BRACE || tok
			== OPEN_PAREN
			|| tok == CLOS_PAREN || tok == COMMA || tok ==
			EQUAL_TO ) {
			pTok.setValid(true);
		}
		else
			return false;
		return true;
	}

	vector<string> lexicalAnalysis() {
		bool check = false;
		vector<string> lexResult;
		for (auto ins : mInstructions) {
			vector<Token>tokens = tokenizeInstruction(ins);
			for (auto t : tokens) {
				if (validateToken(t)) {
					check = true;
				}
				else {
					check = false;
					break;
				}
			}
			if (check)
				lexResult.push_back(ins);
		}
		return lexResult;
	}
};

class Semantic {
	vector<string> mInstruction;
	bool isDeclaration(string pInst) {
		vector<Token>mTokens = tokenizeInstruction(pInst);
		int DFA = 0;
		for (auto x : mTokens) {
			if (DFA == 0 && isDataType(x.getToken())) {
				DFA = 1;
			}
			else if (DFA == 1 && isIdentifier(x.getToken())) {
				DFA = 2;
			}
			else if (DFA == 2) {
				if (x.getToken() == DOT) {
					DFA = 0;
					return true;
				}
				else if (x.getToken() == COMMA) {
					DFA = 4;
				}
				else {
					DFA = 0;
					return false;
				}
			}
			else if (DFA == 4 && isIdentifier(x.getToken())) {
				DFA = 2;
			}
			else {
				DFA = 0;
				return false;
			}
		}
		return false;
	}
	bool isDefinition_Declaration(string pInst) {
		vector<Token>mTokens = tokenizeInstruction(pInst);
		int DFA = 0;
		for (auto x : mTokens) {
			if (DFA == 0 && isDataType(x.getToken())) {
				DFA = 1;
			}
			else if (DFA == 1 && isIdentifier(x.getToken())) {
				DFA = 2;
			}
			else if (DFA == 2 && x.getToken() == EQUAL_TO) {
				DFA = 3;
			}
			else if (DFA == 3 && (isConstant(x.getToken()) ||
				isIdentifier(x.getToken()))) {
				DFA = 4;
			}
			else if (DFA == 4) {
				if (x.getToken() == DOT) {
					DFA = 5;
					return true;
				}
				else if (x.getToken() == COMMA) {
					DFA = 1;
				}
				else if (x.getToken() == EQUAL_TO) {
					DFA = 3;
				}
				else
					return false;
			}
			else {
				DFA = 0;
				return false;
			}
		}
		return false;
	}
	bool isDefinition(string pInst) {
		vector<Token>mTokens = tokenizeInstruction(pInst);
		int DFA = 0;
		for (auto x : mTokens) {
			if (DFA == 0 && isIdentifier(x.getToken())) {
				DFA = 1;
			}
			else if (DFA == 1 && x.getToken() == EQUAL_TO) {
				DFA = 2;
			}
			else if (DFA == 2 && (isIdentifier(x.getToken()) ||
				isConstant(x.getToken()))) {
				DFA = 3;
			}
			else if (DFA == 3) {
				if (x.getToken() == DOT) {
					DFA = 4;
					return true;
				}
				else if (x.getToken() == COMMA) {
					DFA = 0;
				}
				else if (x.getToken() == EQUAL_TO) {
					DFA = 2;
				}
				else
					return false;
			}
			else {
				DFA = 0;
				return false;
			}
		}
		return false;
	}
	bool isManupulation(string pInst) {
		vector<Token>mTokens = tokenizeInstruction(pInst);
		int DFA = 0;
		for (auto x : mTokens) {
			if (DFA == 0 && isIdentifier(x.getToken())) {
				DFA = 1;
			}
			else if (DFA == 1 && x.getToken() == EQUAL_TO) {
				DFA = 2;
			}
			else if (DFA == 2 && (isIdentifier(x.getToken()) ||
				isConstant(x.getToken()))) {
				DFA = 3;
			}
			else if (DFA == 3 && isOperator(x.getToken())) {
				DFA = 4;
			}
			else if (DFA == 4 && (isIdentifier(x.getToken()) ||
				isConstant(x.getToken()))) {
				DFA = 5;
			}
			else if (DFA == 5) {
				if (x.getToken() == DOT) {
					DFA = 0;
					return true;
				}
				else if (isOperator(x.getToken())) {
					DFA = 4;
				}
				else {
					DFA = 0;
					return false;
				}
			}
			else {
				DFA = 0;
				return false;
			}
		}
		return false;
	}
	bool isDecDefMan(string pInst) {
		vector<Token>mTokens = tokenizeInstruction(pInst);
		int DFA = -1;
		for (auto x : mTokens) {
			if (DFA == -1 && isDataType(x.getToken())) {
				DFA = 0;
			}
			else if (DFA == 0 && isIdentifier(x.getToken())) {
				DFA = 1;
			}
			else if (DFA == 1 && x.getToken() == EQUAL_TO) {
				DFA = 2;
			}
			else if (DFA == 2 && (isIdentifier(x.getToken()) ||
				isConstant(x.getToken()))) {
				DFA = 3;
			}
			else if (DFA == 3 && isOperator(x.getToken())) {
				DFA = 4;
			}
			else if (DFA == 4 && (isIdentifier(x.getToken()) ||
				isConstant(x.getToken()))) {
				DFA = 5;
			}
			else if (DFA == 5) {
				if (x.getToken() == DOT) {
					DFA = 0;
					return true;
				}
				else if (isOperator(x.getToken())) {
					DFA = 4;
				}
				else {
					DFA = 0;
					return false;
				}
			}
			else {
				DFA = 0;
				return false;
			}
		}
		return false;
	}
	bool Condition(string pInst, string word) {
		vector<Token>mTokens = tokenizeInstruction(pInst);
		int DFA = 0;
		for (Token x : mTokens) {
			if (DFA == 0 && x.getToken() == word) {
				DFA = 1;
			}
			else if (DFA == 1 && x.getToken() == OPEN_PAREN) {
				DFA = 2;
			}
			else if (DFA == 2 && (isIdentifier(x.getToken()) || isConstant(x.getToken()))) {
				DFA = 3;
			}
			else if (DFA == 3 && isOperator(x.getToken())) {
				DFA = 4;
			}
			else if (DFA == 4 && (isIdentifier(x.getToken()) || isConstant(x.getToken()))) {
				DFA = 5;
			}
			else if (DFA == 5 && isOperator(x.getToken())) {
				DFA = 4;
			}
			else if (DFA == 5 && x.getToken() == CLOS_PAREN) {
				DFA = 6;
			}
			else if (DFA == 6 && x.getToken() == OPEN_BRACE) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
	bool warnaCondition(string pInst) {
		vector<Token>mTokens = tokenizeInstruction(pInst);
		int DFA = 0;
		for (Token x : mTokens) {
			if (DFA == 0 && x.getToken() == "warna") {
				DFA = 1;
			}
			else if (DFA == 1 && x.getToken() == OPEN_BRACE) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
	SymbolTable Table;
public:
	Semantic() { mInstruction = {}; }
	Semantic(vector<string> pIns) { mInstruction = pIns; }
	void semanticAnalysis() {
		bool agarCond = false; // for printing
		bool warnaCond = false; // for printing
		bool karoCond = false;
		//bool isCondTrue = false; // for checking condition (then or else part)
		int i = 1;
		//for (auto ins : mInstruction) {
		for (int j = 0; j < mInstruction.size(); j++) {
			string ins = mInstruction[j];
			if (isDeclaration(ins)) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Declaration Statement]" <<
					endl;
				createSymbolTable(ins, i);
			}
			else if (isDefinition(ins)) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Definition Statement]" << endl;
				createSymbolTable(ins, i);
			}
			else if (isDefinition_Declaration(ins)) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Declare + Define Statement]"
					<< endl;
				createSymbolTable(ins, i);
			}
			else if (isDecDefMan(ins)) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Dec + Def + Manup Statement]"
					<< endl;
				createSymbolTable(ins, i);
			}
			else if (isManupulation(ins)) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Manupulation Statement]" <<
					endl;
				createSymbolTable(ins, i);
			}
			else if (Condition(ins, "agar")) {
				agarCond = true;
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Condition Starts]"
					<< endl;

				vector<Token> mTokens = tokenizeInstruction(ins);
				string op1 = mTokens[2].getToken();
				string op2 = mTokens[4].getToken();
				string op = mTokens[3].getToken();
				if (isIdentifier(op1)) {
					Node* ref = Table.searchIdentifier(op1);
					if (ref)
						op1 = ref->getValue();
					else {
						cout << "ERROR=> " << op1 << " not declared\n";
						return;
					}
				}
				if (isIdentifier(op2)) {
					Node* ref = Table.searchIdentifier(op2);
					if (ref)
						op2 = ref->getValue();
					else {
						cout << "ERROR=> " << op2 << " not declared\n";
						return;
					}
				}

				bool isCondTrue = evaluateCondition(op1, op2, op);
				if (!isCondTrue) {
					agarCond = false;
					warnaCond = true; // Run else Part by ignoring then part
					while (mInstruction[j] != CLOS_BRACE) {
						j++; // Statement Incremented
						i++; // Line Incremented
						cout << left << setw(3) << i << setfill(' ')
							<< ": ";
						cout << setw(50) << mInstruction[j] << "[Not Executed]" <<
							endl;
					}
					
				}
			}
			else if (ins == CLOS_BRACE && agarCond && !warnaCond) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Condition Ends]"
					<< endl;
				agarCond = false;
			}		
			else if (warnaCondition(ins)) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Warna Start]"
					<< endl;
				if (!warnaCond) {
					while (mInstruction[j] != CLOS_BRACE) {
						j++; // Statement Incremented
						i++; // Line Incremented
						cout << left << setw(3) << i << setfill(' ')
							<< ": ";
						cout << setw(50) << mInstruction[j] << "[Not Executed]" <<
							endl;
					}
				}
				
			}
			else if (ins == CLOS_BRACE && warnaCond == true) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Warna Ends]"
					<< endl;
				warnaCond = false;
			}
			else if (Condition(ins, "jab_tak")) {
				karoCond = true;
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Loop Starts]"
					<< endl;
			}
			else if (ins == CLOS_BRACE && karoCond) {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Loop Ends]"
					<< endl;
				karoCond = false;
			}
			else {
				cout << left << setw(3) << i << setfill(' ')
					<< ": ";
				cout << setw(50) << ins << "[Something Else]"
					<< endl;
			}
			i++;
		}
	}
	void createSymbolTable(string line, int line_no) {
		vector<Token> mTokens = tokenizeInstruction(line);
		Node* temp = new Node;
		if (isDeclaration(line)) {
			Table.insertNode(mTokens[0].getToken(),
				mTokens[1].getToken(), "", line_no);
		}
		else if (isDefinition_Declaration(line)) {
			Table.insertNode(mTokens[0].getToken(),
				mTokens[1].getToken(), mTokens[3].getToken(),
				line_no);
		}
		else if (isDefinition(line)) {
			string identifier = mTokens[0].getToken();
			string value = mTokens[2].getToken();
			Node* reference =
				Table.searchIdentifier(identifier);
			if (reference) {
				Table.insertNode("", identifier, value,
					line_no, reference);
			}
			else
				cout << "ERROR: Identifier is not declared\n";
		}
		else if (isManupulation(line)) {
			string identifier = mTokens[0].getToken();
			Node* line_ref = Table.searchIdentifier(identifier);
			if (line_ref) {
				string op1 = mTokens[2].getToken();
				string op2 = mTokens[4].getToken();
				string op = mTokens[3].getToken(); //operator
				if (isIdentifier(op1)) {
					Node* ref = Table.searchIdentifier(op1);
					if (ref)
						op1 = ref->getValue();
					else {
						cout << "ERROR: " << op1 << " is not declared\n";
						return;
					}
					
				}
				if (isIdentifier(op2)) {
					Node* ref = Table.searchIdentifier(op2);
					if (ref)
						op2 = ref->getValue();
					else {
						cout << "ERROR: " << op2 << " is not declared\n";
						return;
					}
				}
				string val = evaluateExp(op1, op2, op);
				Table.insertNode("", identifier, val, line_no, line_ref);
			}
			else
				cout << "ERROR: Identifier is not declared\n";
		}
		line_no++;
	}
	void printSymbolTable() {
		Table.printList();
	}
};
string removeSpace(string line) {
	string line2 = "";
	int i = 0;
	while (i < line.length() && isspace(line[i])) {
		i++;
	}
	while (i < line.length() && (line[i] != '.')) {
		line2 += line[i];
		i++;
	}
	if (i < line.length())
		line2 += line[i];
	return line2;
}
void readFile(string fileName) {
	//create ifstream object 
	ifstream file;
	//open a text file using ifstream object 
	file.open(fileName, ios::in);
	vector<string> mInstruction;
	//check if file is opened or not 
	if (file.is_open()) {
		string line, newString;
		while (!file.eof()) {
			getline(file, line);
			line = removeSpace(line);
			bool comment = false, multiComment = false;
			if (line[0] == '/') {
				if (line[1] == '/') {
					comment = true;
				}
				else if (line[1] == '*')
				{
					multiComment = true;
					getline(file, line);
					while (line[line.length() - 2] != '*' &&
						line[line.length() - 1] != '/')
					{
						getline(file, line);
					}
				}
			}
			if (!comment && !multiComment)
			{
				//newString += line;
				if (line != "")
					mInstruction.push_back(line);
			}
		}

		// Lexer will generate lexemes of instructions 
		Lexer lex(mInstruction);
		mInstruction = lex.lexicalAnalysis();
		Semantic Sem(mInstruction);
		Sem.semanticAnalysis();
		cout << endl << endl;
		Sem.printSymbolTable();
		//close the file 
		file.close();
	}
	else {
		cout << "File is not opened!\n";
	}
}


int main() {
	readFile("src1.txt");
	return 0;
}