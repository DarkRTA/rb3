#include <types.h>

class String {
public:
	int len;
	char * text;

	String();
//	String(char * src);
//	String(String * src);
//	~String();

	void fn_80361F88(String * src); // clone?
	void operator=(char * src);
//	bool operator==(char * src);
};
