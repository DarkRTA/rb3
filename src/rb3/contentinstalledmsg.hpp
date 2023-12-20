#ifndef RB3_CONTENTINSTALLEDMSG_HPP
#define RB3_CONTENTINSTALLEDMSG_HPP
#include "message.hpp"
#include "data.hpp"
#include "symbol.hpp"

class ContentInstalledMsg : Message {
public:
	ContentInstalledMsg(DataArray*);
	ContentInstalledMsg();
	virtual ~ContentInstalledMsg(); // fn_800A7FF4

	Symbol Type();
};

#endif
