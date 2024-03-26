// MSL_C
#include <assert.h>
#include <complex.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <iso646.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <time.h>
#include <wchar.h>
#include <wctype.h>

// MSL_C++
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <exception>
#include <new>
#include <typeinfo>

// STLport
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <functional>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <rope>
#include <set>
#include <slist>
#include <stack>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

// iostreams are unsupported and not used by the target
// #include <fstream>
// #include <iomanip>
// #include <ios>
// #include <iosfwd>
// #include <iostream>
// #include <istream>
// #include <locale>
// #include <ostream>
// #include <pthread_alloc>
// #include <sstream>
// #include <streambuf>
// #include <strstream>

// Problematic with vectors currently
// Not used in the target regardless so it should be fine
// #include <hash_map>
// #include <hash_set>
// #include <queue>
// #include <unordered_map>
// #include <unordered_set>

#define STD_TEST(name) std:: name name##_test
#define STD_TEST_TEMPLATE(name, ...) std:: name < __VA_ARGS__ > name##_test

// bitset
STD_TEST_TEMPLATE(bitset, 8);

// deque
STD_TEST_TEMPLATE(deque, int);

// exception
STD_TEST(exception);
STD_TEST(bad_exception);
STD_TEST(terminate_handler);

// // hash_map
// STD_TEST_TEMPLATE(hash_map, int, int);
// STD_TEST_TEMPLATE(hash_multimap, int, int);

// // hash_set
// STD_TEST_TEMPLATE(hash_set, int);
// STD_TEST_TEMPLATE(hash_multiset, int);

// list
STD_TEST_TEMPLATE(list, int);

// map
STD_TEST_TEMPLATE(map, int, int);
STD_TEST_TEMPLATE(multimap, int, int);

// memory
STD_TEST_TEMPLATE(allocator, int);
STD_TEST_TEMPLATE(auto_ptr, int);

// new
STD_TEST(bad_alloc);
STD_TEST(nothrow_t);

// queue
// STD_TEST_TEMPLATE(queue, int);
// STD_TEST_TEMPLATE(priority_queue, int);

// rope
STD_TEST(crope);
STD_TEST(wrope);

// set
STD_TEST_TEMPLATE(set, int);
STD_TEST_TEMPLATE(multiset, int);

// slist
STD_TEST_TEMPLATE(slist, int);

// stack
STD_TEST_TEMPLATE(stack, int);

// stdexcept
#if defined(_STLP_USE_EXCEPTIONS)
STD_TEST(logic_error);
STD_TEST(runtime_error);
STD_TEST(domain_error);
STD_TEST(invalid_argument);
STD_TEST(length_error);
STD_TEST(out_of_range);
STD_TEST(range_error);
STD_TEST(overflow_error);
STD_TEST(underflow_error);
#endif

// string
STD_TEST(string);
STD_TEST(wstring);

// typeinfo
// STD_TEST(type_info); // not constructable per the standard
STD_TEST(bad_cast);
STD_TEST(bad_typeid);

// unordered_map
// STD_TEST_TEMPLATE(unordered_map, int, int);
// STD_TEST_TEMPLATE(unordered_multimap, int, int);

// unordered_set
// STD_TEST_TEMPLATE(unordered_set, int);
// STD_TEST_TEMPLATE(unordered_multiset, int);

// utility
STD_TEST_TEMPLATE(pair, int, short);

// valarray
STD_TEST_TEMPLATE(valarray, int);
STD_TEST(slice);
// STD_TEST_TEMPLATE(slice_array, int); // not default-constructable
STD_TEST(gslice);
// STD_TEST_TEMPLATE(gslice_array, int); // not default-constructable
// STD_TEST_TEMPLATE(mask_array, int); // not default-constructable
// STD_TEST_TEMPLATE(indirect_array, int); // not default-constructable

// vector
STD_TEST_TEMPLATE(vector, int);

#undef STD_TEST
#undef STD_TEST_TEMPLATE
