#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <sstream>
using namespace std;

struct Token  	// user-defined type called Token
{
    char kind;	// what kind of token
    bool value;	// used for propositions (p,q,r): a value
};

class Token_stream
{
public:
    // user interface:
    Token get();		// get a Token
    void putback(Token); // put a Token back into the Token_stream
    void setPQR(bool _p, bool _q, bool _r){p = _p; q = _q; r = _r;}
    void setSS(string statement){ss.clear(); ss.str(statement);}

private:
    // representation: not directly accessible to users:
    bool full {false};	// is there a Token in the buffer?
    Token buffer;       // here is where we keep a Token put back using putback()
    bool p,q,r;
    stringstream ss;
};

// Token “kind” values:
const char prop = '8';		// a propositional value (p,q,r)
const char endline = ';';	// marks the end of the logical statement

//constants for operators
const char ifThen = 21;  //arbitrary number
const char iff = 22;
const char OR = 23;
const char AND = 24;

bool getConditional();  //deal with => and <=>
bool getOR();           // deal with OR
bool getAND();	        // deal with AND
bool primary();	        // deal with propositions, negations, and parentheses

bool evaluate(bool p, bool q, bool r, string statement);

Token_stream ts;

Token Token_stream::get()	 // read a Token from the Token_stream
{
    if (full)
    {
        full=false;    // check if we already have a Token ready
        //cout << "get returning " << buffer.kind << " " << buffer.value << endl;
        return buffer;
    }

    char ch;
    ss >> ch;	// note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch)
    {
    case '(':
    case ')':
    case endline:
    case '~':
        //cout << "get returning " << ch << endl;
        return Token{ch};		// let each character represent itself
    case 'p':
    case 'q':
    case 'r':
    {
        bool val;
        if(ch == 'p') val = p;
        else if(ch == 'q') val = q;
        else val = r;
        //cout << "get returning " << prop << " " << val << endl;
        return Token{prop,val}; // rather than Token{'8',val}
    }
    case '\\':
    {
        char ch2;
        ss >> ch2;
        if(ch2 == '/')
        {
            //cout << "get returning or" << endl;
            return Token{OR};
        }
        else
        {
            throw runtime_error("Bad token");
        }
    }
    case '/':
    {
        char ch2;
        ss >> ch2;
        if(ch2 == '\\')
        {
            //cout << "get returning and" << endl;
            return Token{AND};
        }
        else
        {
            throw runtime_error("Bad token");
        }
    }
    case '=':
    {
        char ch2;
        ss >> ch2;
        if(ch2 == '>')
        {
            //cout << "get returning ifThen" << endl;
            return Token{ifThen};
        }
        else
        {
            throw runtime_error("Bad token");
        }
    }
    case '<':
    {
        char ch2, ch3;
        ss >> ch2 >> ch3;
        if(ch2 == '=' && ch3 == '>')
        {
            //cout << "get returning iff" << endl;
            return Token{iff};
        }
        else
        {
            throw runtime_error("Bad token");
        }
    }

    default:
        throw runtime_error("Bad token");
    }
    return {};
}

void Token_stream::putback(Token t)
{
    if (full)
        throw runtime_error("putback() into a full buffer");
    buffer=t;
    full=true;
}

bool getConditional()
{
    bool left = getOR(); 			// collect the Term
    while (true)
    {
        //cout << "getConditional getting token" << endl;
        Token t = ts.get();		    // get the next token…
        switch (t.kind)  			// … and do the right thing with it
        {
        case ifThen:
        {
            bool right = getOR();
            left = !left || right;
            break;
        }
        case iff:
        {
            bool right = getOR();
            left = (!left || right) && (!right || left);
            break;
        }
        default:
            ts.putback(t);
            return left;		// return the value of the expression
        }
    }
}

bool getOR()
{
    bool left = getAND(); 		// collect the Term
    while (true)
    {
        //cout << "getOR getting token" << endl;
        Token t = ts.get();		// get the next token…
        switch (t.kind)  		// … and do the right thing with it
        {
        case OR:
        {
            bool right = getAND();
            left = left || right;
            break;
        }
        default:
            ts.putback(t);
            return left;		// return the value of the expression
        }
    }
}

bool getAND()
{
    bool left = primary(); 		// get the Primary
    while (true)
    {
        //cout << "getAND getting token" << endl;
        Token t = ts.get();	// get the next Token
        switch (t.kind)
        {
        case AND:
        {
            //cout << "AND token received in getAND" << endl;
            bool right = primary();
            left = left && right;
            break;
        }
        default:
            ts.putback(t);
            return left;	// return the value
        }
    }
}

bool primary()
{
    //cout << "primary getting token" << endl;
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':			       // handle ‘(’expression ‘)’
    {
        bool d = getConditional();
        t = ts.get();
        if (t.kind != ')')
            throw runtime_error("')' expected, received: " + string{t.kind});

        return d;	// return the proposition's value
    }

    case '~':
        return !primary();

    case prop:	// rather than case '8':
    {
        return t.value;	// return the proposition's value
    }

    default:
        throw runtime_error("primary expected");
    }
    return false;
}


bool evaluate(bool p, bool q, bool r, string statement)
{
    ts.setPQR(p,q,r);
    ts.setSS(statement + ";");

    try
    {
        Token t = ts.get();
        while (t.kind == endline)
            t=ts.get();	// first discard all "endline"s
        ts.putback(t);
        bool result = getConditional();
        //cout << "Evaluate returning: " << p << q << r << result << endl;
        return result;
    }
    catch (exception& e)
    {
        cout << "Exception thrown" << endl;
        cout << e.what() << endl;		// write error message
        throw e;
    }
    return false;
}
#endif // PARSER_H_INCLUDED
