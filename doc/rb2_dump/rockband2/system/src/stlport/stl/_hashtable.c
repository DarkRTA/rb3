/*
    Compile unit: C:\rockband2\system\src\stlport\stl\_hashtable.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80449680 -> 0x80449F6C
*/
// Range: 0x80449680 -> 0x804496EC
void hashtable::clear(class hashtable * const this /* r30 */) {}

// Range: 0x804496EC -> 0x80449744
struct pair & hashtable::_M_insert(class hashtable * const this /* r30 */, const struct pair & __obj /* r31 */) {}

// Range: 0x80449744 -> 0x80449968
struct pair hashtable::insert_unique_noresize(class hashtable * const this /* r29 */, const struct pair & __obj /* r30 */) {
    // Local variables
    class _Slist_iterator __cur; // r1+0x40
    class _Slist_iterator __last; // r1+0x3C

    // References
    // -> struct [anonymous] __RTTI__PP11LightPreset;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ29stlp_priv131_Slist_node<Q211stlpmtx_std100pair<C6Symbol,Q211stlpmtx_std68vector<P11LightPreset,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>>>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80449968 -> 0x80449A68
void hashtable::resize(class hashtable * const this /* r31 */, unsigned long __num_elements_hint /* r1+0x8 */) {
    // Local variables
    unsigned long __num_buckets_hint; // r0
    unsigned long __num_buckets; // r0
}

// Range: 0x80449A68 -> 0x80449C14
struct _Ht_iterator hashtable::_M_insert_noresize(class hashtable * const this /* r28 */, unsigned long __n /* r29 */, const struct pair & __obj /* r30 */) {
    // Local variables
    unsigned long __prev; // r1+0x2C
    class _Slist_iterator __pos; // r1+0x28

    // References
    // -> struct [anonymous] __RTTI__PP11LightPreset;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ29stlp_priv131_Slist_node<Q211stlpmtx_std100pair<C6Symbol,Q211stlpmtx_std68vector<P11LightPreset,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>>>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80449C14 -> 0x80449EA0
void hashtable::_M_rehash(class hashtable * const this /* r29 */, unsigned long __num_buckets /* r30 */) {
    // Local variables
    class slist __tmp_elems; // r1+0x50
    class vector __tmp; // r1+0x54
    class _Slist_iterator __cur; // r1+0x4C
    unsigned long __new_bucket; // r0
    unsigned long __prev_bucket; // r31
    class _Slist_iterator __prev; // r1+0x48
    class _Slist_iterator __pos; // r1+0x44

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PPQ29stlp_priv16_Slist_node_base;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80449EA0 -> 0x80449F6C
struct _Ht_iterator hashtable::_M_before_begin() {
    // Local variables
    class slist & __mutable_elems; // r7
    struct _Slist_node_base * const * __bpos; // r8
    class _Slist_iterator __pos; // r1+0x24
    struct _Slist_node_base * const * __bcur; // r7
    struct _Slist_node_base * __pos_node; // r0
    class _Slist_iterator __cur; // r1+0x20
    class _Slist_iterator __prev; // r1+0x1C
}


