#ifndef RB3_SYMBOL_H
#define RB3_SYMBOL_H

class Symbol {
public:
	char* m_string;
	Symbol(); // ctor pulled from RB2
	Symbol(char*); //ctor pulled from gdrb

	// methods found in RB2
	bool operator!=(const char*);
	Symbol* operator=(const Symbol&);
	char* Str() const;
	void PreInit(int, int);
	void Init();
	void Terminate();
};

#endif
