#include "obj/Dir.h"

#include "obj/Object.h"

Hmx::Object* Hmx::Object::NewObject(){
    return new Hmx::Object();
}

// ObjectDir::ObjectDir() {
//     ObjectDir::Entry entry1, entry2;
//     // mHashTable = KeylessHash<const char*, ObjectDir::Entry>(0, entry1, entry2, 0);
// }
