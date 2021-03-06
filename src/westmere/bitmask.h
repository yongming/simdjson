#ifndef SIMDJSON_WESTMERE_BITMASK_H
#define SIMDJSON_WESTMERE_BITMASK_H

#include "simdjson.h"

#ifdef IS_X86_64

#include "westmere/intrinsics.h"

TARGET_WESTMERE
namespace simdjson::westmere {

//
// Perform a "cumulative bitwise xor," flipping bits each time a 1 is encountered.
//
// For example, prefix_xor(00100100) == 00011100
//
really_inline uint64_t prefix_xor(const uint64_t bitmask) {
  // There should be no such thing with a processing supporting avx2
  // but not clmul.
  __m128i all_ones = _mm_set1_epi8('\xFF');
  __m128i result = _mm_clmulepi64_si128(_mm_set_epi64x(0ULL, bitmask), all_ones, 0);
  return _mm_cvtsi128_si64(result);
}

} // namespace simdjson::westmere
UNTARGET_REGION

#endif // IS_X86_64

#endif // SIMDJSON_WESTMERE_BITMASK_H
