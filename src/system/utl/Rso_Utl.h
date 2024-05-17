#ifndef UTL_RSOUTL_H
#define UTL_RSOUTL_H

typedef bool (*RsoInitFunc)(struct RSOObjectHeader*);
typedef void (*RsoDeinitFunc)(void);

void RsoAddIniter(RsoInitFunc, RsoDeinitFunc);

#endif // UTL_RSOUTL_H