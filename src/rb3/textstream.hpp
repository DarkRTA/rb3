#ifndef RB3_TEXTSTREAM_HPP
#define RB3_TEXTSTREAM_HPP

class TextStream {
public:
	TextStream();
	virtual ~TextStream(); // fn_8000DD10
	virtual void VirtualAppend(const char*) = 0;
};

#endif
