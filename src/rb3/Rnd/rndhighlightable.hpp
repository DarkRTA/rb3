#ifndef RB3_RNDHIGHLIGHTABLE_HPP
#define RB3_RNDHIGHLIGHTABLE_HPP
#include "rb3/hmx/object.hpp"

class RndHighlightable : public Hmx::Object {
	public:
	RndHighlightable();
	virtual ~RndHighlightable();
	virtual void Highlight() = 0;
};

#endif
