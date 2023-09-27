#ifndef QUAZAL_UNK_800A515C_HPP
#define QUAZAL_UNK_800A515C_HPP
namespace Quazal
{

// fn_800A5368 - compiler generated function
struct unk_53B0 {
	unk_53B0();
	~unk_53B0();
};

extern unk_53B0 lbl_53B0();

class ProductSpecifics {
public:
	ProductSpecifics(); // aka fn_800A515C
	virtual ~ProductSpecifics(); // aka fn_800A516C
	virtual void unk() = 0; // 0'd in vtable, pure virtual
	virtual void fn_8076F540();
	// virtual void fn_8076F540();  // wait, why is this duplicated?
};

class NetZSpecifics : ProductSpecifics {
public:
	NetZSpecifics(); // aka fn_800A5278
	virtual ~NetZSpecifics(); // aka fn_800A52B4
	virtual int fn_800A530C();
	virtual void fn_800A5314();
	virtual void fn_800A5338();
};
} // namespace Quazal
#endif