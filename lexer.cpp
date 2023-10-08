#include <stdio.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

typedef long long int lint;

set<string> keywords = { "space", "lines", "times" ,"print", "eol", "hold" };
set<string> modifiers = { "randomstring", "lowercase", "uppercase", "toggled", "increasing", "decreasing", "strictly", "prime", "binary", "random", "nonrepeating","reset", "current" };
set<string> setters = { "between", "length", "set" };

unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

lint randomInt(lint min, lint max)
{
    return rand() % (min - max) + min;
}

string randomString(lint n, lint cap)
{
    string str = "";
    char ref;

    if (cap == 0)
	ref = 'a';
    else if (cap == 1)
	ref = 'A';

    for (lint i = 0;i < n;++i)
    {
	if (cap == -1)
	{
	    lint lower = rand() % 2;

	    if (lower)
		ref = 'a';
	    else
		ref = 'A';
	}

	char ch = rand() % 26 + ref;
	str += ch;
    }


    return str;
}

string randomString(lint min, lint max, lint cap)
{
    lint length = randomInt(min, max);
    return randomString(length, cap);
}

class Token
{
    public:
	string type;
	string value;

	Token *next;
	Token *previous;
};

class Variable
{
    public:
	string name;
	string type;
	string value;

	lint length = 1;

	vector<string> history;

	bool isPrime = false;
	bool isBinary = false;
	bool isRandom = true;
	bool isRandomLength = true;
	bool isIncreasing = false;
	bool isDecreasing = false;
	bool isStrictly = false;
	bool isLowerCase = true;
	bool isToggled = false;
	bool isSet = false;
	bool current = false;
	bool isString = false;

	lint count = 0;

	pair<lint, lint> between = {INT_MIN, INT_MAX};

	lint getValue()
	{
	    if (isSet)
	    {

	    }
	    else if (current)
	    {
		current = false;
		value = history[count - 1];
	    }
	    else if (count == history.size())
	    {
		++count;
		value = to_string(newValue());
		history.push_back(value);
	    }
	    else
	    {
		value = history[count];
		++count;
	    }

	    return stoll(value);
	}

	lint newValue()
	{
	    return randomInt(between.first, between.second);
	}

	string getStringValue()
	{
	    if (!isString)
	    {
		return "";
	    }

	    if (isRandomLength)
	    {
		if (isLowerCase && !isToggled)
		{
		    return randomString(between.first, between.second, 0);
		}
		else if (!isLowerCase && isToggled)
		{

		    return randomString(between.first, between.second, -1);
		}
		else
		{

		    return randomString(between.first, between.second, 1);
		}
	    }
	    else
	    {

		if (isLowerCase && !isToggled)
		{
		    return randomString(length, 0);
		}
		else if (!isLowerCase && isToggled)
		{
		    return randomString(length, -1);
		}
		else
		{
		    return randomString(length, 1);
		}
	    }
	}
};

map<string, Variable> variables;

bool has_only_digits(const string s)
{
    return s.find_first_not_of( "0123456789" ) == string::npos;
}


    template <typename Out>
void split(const string &s, char delim, Out result)
{
    istringstream iss(s);
    string item;
    while (getline(iss, item, delim)) {
	*result++ = item;
    }
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

vector<Token> tokenizer(string line)
{
    vector<string> splitted = split(line, ' ');

    vector<Token> tokens;

    for (string i : splitted)
    {
	Token token;
	token.value = i;
	if (i[0] == '$')
	{
	    token.type = "declaration";

	    Variable var;

	    var.name = i.substr(1);

	    if (variables.find(var.name) == variables.end())
	    {
		variables[var.name] = var;
	    }
	}
	else if (has_only_digits(i))
	{
	    token.type = "literal";
	}
	else if (keywords.count(i))
	{
	    token.type = "keyword";
	}
	else if (modifiers.count(i))
	{
	    token.type = "modifier";
	}
	else if (setters.count(i))
	{
	    token.type = "setter";
	}
	else
	{
	    if (variables.find(token.value) == variables.end())
	    {
		cout << "error: unknown token " << token.value << endl;
		tokens.clear();
		return tokens;
	    }
	    token.type = "variable";
	}

	tokens.push_back(token);
    }

    return tokens;
}

void parser(vector<Token>& tokens, void* ptr);

void lines(vector<Token>& tokens, void* ptr)
{
    vector<Token> copy;

    for (lint i = 0;i < *(lint*) ptr;++i)
    {
	copy = tokens;
	parser(copy, ptr);
	cout << endl;
    }

    tokens.clear();
}

void times(vector<Token>& tokens, void* ptr )
{
    vector<Token> copy;

    for (lint i = 0;i < *(lint*) ptr;++i)
    {
	copy = tokens;
	parser(copy, NULL);
    }
    tokens.clear();
}


lint getVariableValue(string name)
{
    Variable& var = variables[name];
    return var.getValue();
}

Variable getVariable(string name)
{
    Variable& var = variables[name];
    return var;
}

void eatDeclaration(vector<Token>& tokens);
void eatKeyword(vector<Token>& tokens, void* ptr);
void eatModifier(vector<Token>& tokens, Variable& var);

void parser(vector<Token>& tokens, void* ptr)
{
    if (tokens.size() <= 0)
    {
	return;
    }

    Token token = *tokens.begin();

    if (token.type == "declaration")
    {
	eatDeclaration(tokens);
    }
    else if (token.type == "variable")
    {
	lint n = variables[token.value].getValue();
	ptr = &n;
	tokens.erase(tokens.begin());
    }
    else if (token.type == "keyword")
    {
	//cout << "keyword" << endl;
	eatKeyword(tokens, ptr);
    }
    else if (token.type == "literal")
    {
	lint n = stoll(token.value);
	ptr = &n;
	tokens.erase(tokens.begin());
    }

    //cout << "parsing done " << tokens.size() << endl;

    parser (tokens, ptr);
}

void eatKeyword(vector<Token>& tokens, void* ptr)
{

    Token key_token = *tokens.begin();

    if (key_token.value == "lines")
    {
	tokens.erase(tokens.begin());
	lines(tokens, ptr);
    }
    else if (key_token.value == "space")
    {
	tokens.erase(tokens.begin());
	cout << " ";
    }
    else if (key_token.value == "times")
    {
	tokens.erase(tokens.begin());
	times(tokens, ptr);
    }
    else if (key_token.value == "print")
    {
	tokens.erase(tokens.begin());

	Token t1 = *tokens.begin();
	lint t1_value;
	string value;

	if (t1.type == "variable")
	{
	    Variable& t1_var = variables[t1.value];

	    if (t1_var.isString)
	    {
		value = t1_var.getStringValue();
	    }
	    else
	    {
		t1_value = t1_var.getValue();
		value = to_string(t1_value);
	    }
	}
	else if (t1.type == "literal")
	{
	    t1_value = stoll(t1.value);
	}
	else
	{
	    cout << "\nerror: " << t1.value << " is not compatible here" << endl;
	}

	tokens.erase(tokens.begin());

	cout << value;
    }
    else if (key_token.value == "eol")
    {
	tokens.erase(tokens.begin());
	cout << "\n";
    }
    else if (key_token.value == "hold")
    {
	tokens.erase(tokens.begin());

	Token t1 = *tokens.begin();

	if (t1.type == "variable")
	{
	    Variable& var = variables[t1.value];

	    --var.count;
	}
	else
	{
	    cout << "\nerror: " << t1.value << " is not compatible here" << endl;
	}

	tokens.erase(tokens.begin());
    }

}

void eatSetter(vector<Token>& tokens, Variable& var);

void eatDeclaration(vector<Token>& tokens)
{
    Variable& local = variables[(*tokens.begin()).value.substr(1)];

    tokens.erase(tokens.begin());

    for (Token token : tokens)
    {
	if (token.type == "setter")
	{
	    eatSetter(tokens, local);
	}
	else if (token.type == "modifier")
	{
	    eatModifier(tokens, local);
	}
    }
}

void eatModifier(vector<Token>& tokens, Variable& var)
{
    Token token = *tokens.begin();

    tokens.erase(tokens.begin());

    if (token.value == "reset")
    {
	var.count = 0;
    }
    else if (token.value == "current")
    {
	var.current = true;
    }
    else if (token.value == "randomstring")
    {
	var.isString = true;
    }
    else if (token.value == "toggled")
    {
	var.isToggled = true;
	var.isLowerCase = false;
    }
    else if (token.value == "lowercase")
    {
	var.isToggled = false;
	var.isLowerCase = true;
    }
    else if (token.value == "uppercase")
    {
	var.isToggled = false;
	var.isLowerCase = false;
    }
}

void eatSetter(vector<Token>& tokens, Variable& var)
{
    Token token = *tokens.begin();

    if (token.value == "between")
    {
	tokens.erase(tokens.begin());

	Token t1 = *tokens.begin();
	lint t1_value;

	if (t1.type == "variable")
	{
	    Variable& t1_var = variables[t1.value];

	    t1_value = t1_var.getValue();
	}
	else if (t1.type == "literal")
	{
	    t1_value = stoll(t1.value);
	}
	else
	{
	    cout << "\nerror: " << t1.value << " is not compatible here" << endl;
	}

	tokens.erase(tokens.begin());

	Token t2 = *tokens.begin();
	lint t2_value;

	if (t2.type == "variable")
	{
	    Variable& t2_var = variables[t2.value];

	    t2_value = t2_var.getValue();
	}
	else if (t2.type == "literal")
	{
	    t2_value = stoll(t2.value);
	}
	else
	{
	    cout << "\nerror: " << t2.value << " is not compatible here" << endl;
	    tokens.clear();
	    return;
	}

	tokens.erase(tokens.begin());

	var.between.first = t1_value;
	var.between.second = t2_value;

    }
    else
    {
	tokens.erase(tokens.begin());

	Token t1 = *tokens.begin();
	lint t1_value;

	if (t1.type == "variable")
	{
	    Variable t1_var = variables[t1.value];

	    t1_value = t1_var.getValue();
	}
	else if (t1.type == "literal")
	{
	    t1_value = stoll(t1.value);
	}
	else
	{
	    cout << "\nerror: " << t1.value << " is not compatible here" << endl;
	    tokens.clear();
	    return;
	}

	if (token.value == "set")
	{
	    var.isSet = true;
	    var.value = to_string(t1_value);
	}
	else if (token.value == "length")
	{
	    var.isRandomLength = false;
	    var.length = t1_value;
	}

	tokens.erase(tokens.begin());
    }
}

int main()
{
    unsigned long seed = mix(clock(), time(NULL), getpid());
    srand(seed);

    string line;

    while(getline(cin, line))
    {
	vector<Token> tokens = tokenizer(line);
	parser(tokens, NULL);
    }

    /*for (auto i : variables)
      {
      cout << i.first << endl;
      cout << i.second.between.first << " " << i.second.between.second << endl;
      }*/
}
