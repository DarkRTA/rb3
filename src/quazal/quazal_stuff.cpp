// ------------------------------------
// class layouts
// ------------------------------------
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

// ------------------------------------
// fn_800A515C
// ------------------------------------
Quazal::ProductSpecifics::ProductSpecifics() {} 

// ------------------------------------
// fn_800A516C
// ------------------------------------
Quazal::ProductSpecifics::~ProductSpecifics() {}

// // ------------------------------------
// // fn_800A51AC
// // ------------------------------------

// extern "C" int fn_800179A8(int, int*, int);
// extern "C" void fn_800A49A0(int**, int);
// extern "C" int fn_800A5278();
// extern "C" int** fn_800A51AC(int**);
// extern int lbl_8082A608[];
// extern int lbl_8082A650[];

// int** fn_800A51AC(int** arg0) {
//     int temp_r3;
//     int var_r4;

//     temp_r3 = fn_800179A8(4, &lbl_8082A650[0], 0x15);
//     var_r4 = temp_r3;
//     if (temp_r3 != 0) {
//         var_r4 = fn_800A5278(); // NetZ ctor
//     }

//     // looks like another ctor
//     fn_800A49A0(arg0, var_r4);
//     *arg0 = &lbl_8082A608[0];
//     return arg0;
// }

// // ------------------------------------
// // fn_800A5214
// // ------------------------------------

// extern "C" void fn_800A4C84(int, int*);
// extern "C" int** fn_800A5214(int**,int);
// extern int lbl_8082A608[];

// int** fn_800A5214(int** arg0, int arg1) {
//     if (arg0 != '\0') {
//         *arg0 = &lbl_8082A608[0];
//         fn_800A4C84(0, &lbl_8082A608[0]);
//         if (arg1 > 0) {
//             fn_80017A8C(); // operator delete
//         }
//     }
//     return arg0;
// }

// ------------------------------------
// fn_800A5278
// ------------------------------------
Quazal::NetZSpecifics::NetZSpecifics() {}

// ------------------------------------
// fn_800A52B4
// ------------------------------------
Quazal::NetZSpecifics::~NetZSpecifics() {}

// // ------------------------------------
// // fn_800A530C
// // ------------------------------------

int Quazal::NetZSpecifics::fn_800A530C() {
    return 1;
}

// ------------------------------------
// fn_800A5314
// ------------------------------------

extern "C" void fn_8007DFD0();
extern "C" void fn_80083734();

void Quazal::NetZSpecifics::fn_800A5314(void) {
    fn_80083734();
    fn_8007DFD0();
}

// ------------------------------------
// fn_800A5338
// ------------------------------------

extern "C" void fn_8007E3C0();
extern "C" void fn_80083174();
extern "C" void fn_80084160();
extern char lbl_808E2DA0;

void Quazal::NetZSpecifics::fn_800A5338(void) {
    fn_80083174();
    lbl_808E2DA0 = 0;
    fn_8007E3C0();
    fn_80084160();
}
