#ifndef RB3_CACHEID_HPP
#define RB3_CACHEID_HPP

class CacheID {
public:
	CacheID(); // fn_80344350
	virtual ~CacheID(); // fn_8000DD10 - generic dtor
	virtual char* GetCachePath(const char*) = 0;
	virtual void GetCacheSearchPath(const char*) = 0;
	virtual int V_Unk3(); // fn_80344238 - returns -1
};

#endif
