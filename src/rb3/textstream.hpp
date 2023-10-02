#ifndef RB3_TEXTSTREAM_HPP
#define RB3_TEXTSTREAM_HPP

class TextStream {
public:
	TextStream();
	virtual ~TextStream(); // fn_8000DD10
	// virtual TextStream* VirtualAppend() = 0; // turns out there's a void fxn here, given VirtualAppend in String, this must be some sort of appending/operator+= overload fn
};

#endif
