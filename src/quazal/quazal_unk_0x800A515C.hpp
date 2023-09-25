#ifndef QUAZAL_HPP
#define QUAZAL_HPP
namespace Quazal {
    class ProductSpecifics {
        public:
            ProductSpecifics();             // aka fn_800A515C
            virtual ~ProductSpecifics();    // aka fn_800A516C
            virtual void unk() = 0;         // 0'd in vtable, pure virtual
            virtual void fn_8076F540();
            // virtual void fn_8076F540();  // wait, why is this duplicated?
    };

    class NetZSpecifics : ProductSpecifics {
        public:
            NetZSpecifics();                // aka fn_800A5278
            virtual ~NetZSpecifics();       // aka fn_800A52B4
            virtual int fn_800A530C();
            virtual void fn_800A5314();
            virtual void fn_800A5338();
    };
}
#endif