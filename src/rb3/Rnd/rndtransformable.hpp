#ifndef RB3_RND_TRANSFORMABLE_HPP
#define RB3_RND_TRANSFORMABLE_HPP
#include "rndhighlightable.hpp"
#include "rb3/hmx/object.hpp"
#include "data.hpp"

class RndTransformable : RndHighlightable {
	RndTransformable();
	virtual ~RndTransformable();

	virtual Symbol ClassName();
	virtual void SetType(Symbol*);
	virtual void Handle(int*, DataArray*, int);
	virtual int SyncProperty(DataNode*, DataArray*, int, int);
	virtual void Save(BinStream&);
	virtual void Copy(BinStream&);
	virtual void Load(BinStream&);
	virtual void Replace(char*, Hmx::Object*);
	virtual void Highlight();
	virtual void Print();
	virtual void UpdatedWorldXfm(); // links to fn_8076F540_stub, which returns void
	
	Symbol StaticClassName();
};

#endif
