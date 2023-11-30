#ifndef HMX_OBJECT_HPP
#define HMX_OBJECT_HPP
#include "rb3/objref.hpp"
#include "rb3/data.hpp"
#include "rb3/typeprops.hpp"

// forward declarations
class DataArray;
class DataNode;

namespace Hmx {
	class Object : ObjRef {
	public:
		TypeProps props;
		const char* name;

		Object(); // fn_8033560c
		virtual ~Object(); // fn_803356ec
		virtual void RefOwner(); // links to fn_8076F540, which returns void
		virtual void Replace(); // fn_80336C88
		// ObjRef::IsDirPtr // links to fn_8077BAA0, which returns 0
		virtual void ClassName(); // fn_800103C8
		virtual void SetType(); // fn_800102A0
		virtual void Handle(); // fn_80336C94
		virtual bool SyncProperty(); // fn_80337B7C
		virtual void Save();
		virtual void Copy();
		virtual void Load();
		virtual void Print(); // links to fn_8076F540, which returns void
		virtual void Export(); // links to fn_8076F540, which returns void
		virtual void V_Unk14(); // links to fn_8076F540, which returns void
		virtual void V_Unk15(); // links to fn_8076F540, which returns void
		virtual void SetTypeDef();
		virtual void SetName(); // fn_80335904
		virtual void DataDir(); // fn_803351D0
		virtual void PreLoad(); // fn_800AB8B4
		virtual void PostLoad(); // links to fn_8076F540, which returns void
		virtual void FindPathName(); // fn_80336A84

		DataNode* Property(DataArray*, bool);
		void SetProperty(DataArray*, const DataNode&);
		int PropertySize(DataArray*);
		const char* Name() const;
	};
}

#endif

        // 80856128 80 33 56 ec     addr       fn_803356EC
        // 8085612c 80 76 f5 40     addr       fn_8076F540_stub
        // 80856130 80 33 6c 88     addr       fn_80336C88
        // 80856134 80 77 ba a0     addr       fn_8077BAA0
        // 80856138 80 01 03 c8     addr       fn_800103C8
        // 8085613c 80 01 02 a0     addr       fn_800102A0
        // 80856140 80 33 6c 94     addr       fn_80336C94
        // 80856144 80 33 7b 7c     addr       fn_80337B7C
        // 80856148 80 33 66 a0     addr       fn_803366A0
        // 8085614c 80 33 67 88     addr       fn_80336788
        // 80856150 80 33 69 f4     addr       fn_803369F4
        // 80856154 80 76 f5 40     addr       fn_8076F540_stub
        // 80856158 80 76 f5 40     addr       fn_8076F540_stub
        // 8085615c 80 76 f5 40     addr       fn_8076F540_stub
        // 80856160 80 76 f5 40     addr       fn_8076F540_stub
        // 80856164 80 33 5a 2c     addr       fn_80335A2C
        // 80856168 80 33 59 04     addr       fn_80335904
        // 8085616c 80 33 51 d0     addr       fn_803351D0
        // 80856170 80 0a b8 b4     addr       fn_800AB8B4
        // 80856174 80 76 f5 40     addr       fn_8076F540_stub
        // 80856178 80 33 6a 84     addr       fn_80336A84

