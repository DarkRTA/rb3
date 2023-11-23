#ifndef RB3_OBJREF_HPP
#define RB3_OBJREF_HPP

class ObjRef {
	ObjRef();
	virtual ~ObjRef(); //fn_8000DD10
	virtual void RefOwner() = 0;
	virtual void Replace() = 0;
	virtual int IsDirPtr(); // links to fn_8077BAA0, which returns 0
};

#endif
