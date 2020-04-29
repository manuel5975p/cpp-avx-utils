#include <immintrin.h>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream> //Sorry
#if __cplusplus >= 201703L
#define IF_CONSTEXPR if constexpr
#else
#define IF_CONSTEXPR if
#warning If you can -std=c++17 or newer, please do so
#endif
struct vec4i{
	__m256i data;
	vec4i() : data (_mm256_set1_epi64x(0)){
		
	}
	vec4i(long long a) : data (_mm256_set1_epi64x(a)){
		
	}
	vec4i(long long a, long long b, long long c, long long d) : data (_mm256_set_epi64x(d, c, b, a)){
		
	}
	vec4i& operator+=(const vec4i& o){
		data = _mm256_add_epi64(data, o.data);
		return *this;
	}
	vec4i operator+(const vec4i& o)const{
		vec4i ret;
		ret.data = _mm256_add_epi64(data, o.data);
		return ret;
	}
	vec4i& operator-=(const vec4i& o){
		data = _mm256_sub_epi64(data, o.data);
		return *this;
	}
	vec4i operator-(const vec4i& o)const{
		vec4i ret;
		ret.data = _mm256_sub_epi64(data, o.data);
		return ret;
	}
	vec4i& operator&=(const vec4i& o){
		data = _mm256_and_si256(data, o.data);
		return *this;
	}
	vec4i operator&(const vec4i& o)const{
		vec4i ret;
		ret.data = _mm256_and_si256(data, o.data);
		return ret;
	}
	vec4i& operator|=(const vec4i& o){
		data = _mm256_or_si256(data, o.data);
		return *this;
	}
	vec4i operator|(const vec4i& o)const{
		vec4i ret;
		ret.data = _mm256_or_si256(data, o.data);
		return ret;
	}
	vec4i& operator^=(const vec4i& o){
		data = _mm256_xor_si256(data, o.data);
		return *this;
	}
	vec4i operator^(const vec4i& o)const{
		vec4i ret;
		ret.data = _mm256_xor_si256(data, o.data);
		return ret;
	}
	vec4i operator!()const{
		vec4i z(0);
		z.data = _mm256_cmpeq_epi64(data, z.data);
		return z;
	}
	vec4i operator~()const{
		vec4i xm(~(0ull));
		xm ^= *this;
		return xm;
	}
	int movemask()const{
		return _mm256_movemask_epi8(data);
	}
	bool all()const{
		vec4i z(0);
		return (_mm256_movemask_epi8(_mm256_cmpeq_epi32(data, z.data))) == 0;
	}
	bool is_zero()const{
		vec4i z(0);
		return (~_mm256_movemask_epi8(_mm256_cmpeq_epi64(data, z.data))) == 0;
	}
	vec4i xxxx()const{
		return swizzle<0, 0, 0, 0>();
	}
	vec4i xxxy()const{
		return swizzle<0, 0, 0, 1>();
	}
	vec4i xxxz()const{
		return swizzle<0, 0, 0, 2>();
	}
	vec4i xxxw()const{
		return swizzle<0, 0, 0, 3>();
	}
	vec4i xxyx()const{
		return swizzle<0, 0, 1, 0>();
	}
	vec4i xxyy()const{
		return swizzle<0, 0, 1, 1>();
	}
	vec4i xxyz()const{
		return swizzle<0, 0, 1, 2>();
	}
	vec4i xxyw()const{
		return swizzle<0, 0, 1, 3>();
	}
	vec4i xxzx()const{
		return swizzle<0, 0, 2, 0>();
	}
	vec4i xxzy()const{
		return swizzle<0, 0, 2, 1>();
	}
	vec4i xxzz()const{
		return swizzle<0, 0, 2, 2>();
	}
	vec4i xxzw()const{
		return swizzle<0, 0, 2, 3>();
	}
	vec4i xxwx()const{
		return swizzle<0, 0, 3, 0>();
	}
	vec4i xxwy()const{
		return swizzle<0, 0, 3, 1>();
	}
	vec4i xxwz()const{
		return swizzle<0, 0, 3, 2>();
	}
	vec4i xxww()const{
		return swizzle<0, 0, 3, 3>();
	}
	vec4i xyxx()const{
		return swizzle<0, 1, 0, 0>();
	}
	vec4i xyxy()const{
		return swizzle<0, 1, 0, 1>();
	}
	vec4i xyxz()const{
		return swizzle<0, 1, 0, 2>();
	}
	vec4i xyxw()const{
		return swizzle<0, 1, 0, 3>();
	}
	vec4i xyyx()const{
		return swizzle<0, 1, 1, 0>();
	}
	vec4i xyyy()const{
		return swizzle<0, 1, 1, 1>();
	}
	vec4i xyyz()const{
		return swizzle<0, 1, 1, 2>();
	}
	vec4i xyyw()const{
		return swizzle<0, 1, 1, 3>();
	}
	vec4i xyzx()const{
		return swizzle<0, 1, 2, 0>();
	}
	vec4i xyzy()const{
		return swizzle<0, 1, 2, 1>();
	}
	vec4i xyzz()const{
		return swizzle<0, 1, 2, 2>();
	}
	vec4i xyzw()const{
		return swizzle<0, 1, 2, 3>();
	}
	vec4i xywx()const{
		return swizzle<0, 1, 3, 0>();
	}
	vec4i xywy()const{
		return swizzle<0, 1, 3, 1>();
	}
	vec4i xywz()const{
		return swizzle<0, 1, 3, 2>();
	}
	vec4i xyww()const{
		return swizzle<0, 1, 3, 3>();
	}
	vec4i xzxx()const{
		return swizzle<0, 2, 0, 0>();
	}
	vec4i xzxy()const{
		return swizzle<0, 2, 0, 1>();
	}
	vec4i xzxz()const{
		return swizzle<0, 2, 0, 2>();
	}
	vec4i xzxw()const{
		return swizzle<0, 2, 0, 3>();
	}
	vec4i xzyx()const{
		return swizzle<0, 2, 1, 0>();
	}
	vec4i xzyy()const{
		return swizzle<0, 2, 1, 1>();
	}
	vec4i xzyz()const{
		return swizzle<0, 2, 1, 2>();
	}
	vec4i xzyw()const{
		return swizzle<0, 2, 1, 3>();
	}
	vec4i xzzx()const{
		return swizzle<0, 2, 2, 0>();
	}
	vec4i xzzy()const{
		return swizzle<0, 2, 2, 1>();
	}
	vec4i xzzz()const{
		return swizzle<0, 2, 2, 2>();
	}
	vec4i xzzw()const{
		return swizzle<0, 2, 2, 3>();
	}
	vec4i xzwx()const{
		return swizzle<0, 2, 3, 0>();
	}
	vec4i xzwy()const{
		return swizzle<0, 2, 3, 1>();
	}
	vec4i xzwz()const{
		return swizzle<0, 2, 3, 2>();
	}
	vec4i xzww()const{
		return swizzle<0, 2, 3, 3>();
	}
	vec4i xwxx()const{
		return swizzle<0, 3, 0, 0>();
	}
	vec4i xwxy()const{
		return swizzle<0, 3, 0, 1>();
	}
	vec4i xwxz()const{
		return swizzle<0, 3, 0, 2>();
	}
	vec4i xwxw()const{
		return swizzle<0, 3, 0, 3>();
	}
	vec4i xwyx()const{
		return swizzle<0, 3, 1, 0>();
	}
	vec4i xwyy()const{
		return swizzle<0, 3, 1, 1>();
	}
	vec4i xwyz()const{
		return swizzle<0, 3, 1, 2>();
	}
	vec4i xwyw()const{
		return swizzle<0, 3, 1, 3>();
	}
	vec4i xwzx()const{
		return swizzle<0, 3, 2, 0>();
	}
	vec4i xwzy()const{
		return swizzle<0, 3, 2, 1>();
	}
	vec4i xwzz()const{
		return swizzle<0, 3, 2, 2>();
	}
	vec4i xwzw()const{
		return swizzle<0, 3, 2, 3>();
	}
	vec4i xwwx()const{
		return swizzle<0, 3, 3, 0>();
	}
	vec4i xwwy()const{
		return swizzle<0, 3, 3, 1>();
	}
	vec4i xwwz()const{
		return swizzle<0, 3, 3, 2>();
	}
	vec4i xwww()const{
		return swizzle<0, 3, 3, 3>();
	}
	vec4i yxxx()const{
		return swizzle<1, 0, 0, 0>();
	}
	vec4i yxxy()const{
		return swizzle<1, 0, 0, 1>();
	}
	vec4i yxxz()const{
		return swizzle<1, 0, 0, 2>();
	}
	vec4i yxxw()const{
		return swizzle<1, 0, 0, 3>();
	}
	vec4i yxyx()const{
		return swizzle<1, 0, 1, 0>();
	}
	vec4i yxyy()const{
		return swizzle<1, 0, 1, 1>();
	}
	vec4i yxyz()const{
		return swizzle<1, 0, 1, 2>();
	}
	vec4i yxyw()const{
		return swizzle<1, 0, 1, 3>();
	}
	vec4i yxzx()const{
		return swizzle<1, 0, 2, 0>();
	}
	vec4i yxzy()const{
		return swizzle<1, 0, 2, 1>();
	}
	vec4i yxzz()const{
		return swizzle<1, 0, 2, 2>();
	}
	vec4i yxzw()const{
		return swizzle<1, 0, 2, 3>();
	}
	vec4i yxwx()const{
		return swizzle<1, 0, 3, 0>();
	}
	vec4i yxwy()const{
		return swizzle<1, 0, 3, 1>();
	}
	vec4i yxwz()const{
		return swizzle<1, 0, 3, 2>();
	}
	vec4i yxww()const{
		return swizzle<1, 0, 3, 3>();
	}
	vec4i yyxx()const{
		return swizzle<1, 1, 0, 0>();
	}
	vec4i yyxy()const{
		return swizzle<1, 1, 0, 1>();
	}
	vec4i yyxz()const{
		return swizzle<1, 1, 0, 2>();
	}
	vec4i yyxw()const{
		return swizzle<1, 1, 0, 3>();
	}
	vec4i yyyx()const{
		return swizzle<1, 1, 1, 0>();
	}
	vec4i yyyy()const{
		return swizzle<1, 1, 1, 1>();
	}
	vec4i yyyz()const{
		return swizzle<1, 1, 1, 2>();
	}
	vec4i yyyw()const{
		return swizzle<1, 1, 1, 3>();
	}
	vec4i yyzx()const{
		return swizzle<1, 1, 2, 0>();
	}
	vec4i yyzy()const{
		return swizzle<1, 1, 2, 1>();
	}
	vec4i yyzz()const{
		return swizzle<1, 1, 2, 2>();
	}
	vec4i yyzw()const{
		return swizzle<1, 1, 2, 3>();
	}
	vec4i yywx()const{
		return swizzle<1, 1, 3, 0>();
	}
	vec4i yywy()const{
		return swizzle<1, 1, 3, 1>();
	}
	vec4i yywz()const{
		return swizzle<1, 1, 3, 2>();
	}
	vec4i yyww()const{
		return swizzle<1, 1, 3, 3>();
	}
	vec4i yzxx()const{
		return swizzle<1, 2, 0, 0>();
	}
	vec4i yzxy()const{
		return swizzle<1, 2, 0, 1>();
	}
	vec4i yzxz()const{
		return swizzle<1, 2, 0, 2>();
	}
	vec4i yzxw()const{
		return swizzle<1, 2, 0, 3>();
	}
	vec4i yzyx()const{
		return swizzle<1, 2, 1, 0>();
	}
	vec4i yzyy()const{
		return swizzle<1, 2, 1, 1>();
	}
	vec4i yzyz()const{
		return swizzle<1, 2, 1, 2>();
	}
	vec4i yzyw()const{
		return swizzle<1, 2, 1, 3>();
	}
	vec4i yzzx()const{
		return swizzle<1, 2, 2, 0>();
	}
	vec4i yzzy()const{
		return swizzle<1, 2, 2, 1>();
	}
	vec4i yzzz()const{
		return swizzle<1, 2, 2, 2>();
	}
	vec4i yzzw()const{
		return swizzle<1, 2, 2, 3>();
	}
	vec4i yzwx()const{
		return swizzle<1, 2, 3, 0>();
	}
	vec4i yzwy()const{
		return swizzle<1, 2, 3, 1>();
	}
	vec4i yzwz()const{
		return swizzle<1, 2, 3, 2>();
	}
	vec4i yzww()const{
		return swizzle<1, 2, 3, 3>();
	}
	vec4i ywxx()const{
		return swizzle<1, 3, 0, 0>();
	}
	vec4i ywxy()const{
		return swizzle<1, 3, 0, 1>();
	}
	vec4i ywxz()const{
		return swizzle<1, 3, 0, 2>();
	}
	vec4i ywxw()const{
		return swizzle<1, 3, 0, 3>();
	}
	vec4i ywyx()const{
		return swizzle<1, 3, 1, 0>();
	}
	vec4i ywyy()const{
		return swizzle<1, 3, 1, 1>();
	}
	vec4i ywyz()const{
		return swizzle<1, 3, 1, 2>();
	}
	vec4i ywyw()const{
		return swizzle<1, 3, 1, 3>();
	}
	vec4i ywzx()const{
		return swizzle<1, 3, 2, 0>();
	}
	vec4i ywzy()const{
		return swizzle<1, 3, 2, 1>();
	}
	vec4i ywzz()const{
		return swizzle<1, 3, 2, 2>();
	}
	vec4i ywzw()const{
		return swizzle<1, 3, 2, 3>();
	}
	vec4i ywwx()const{
		return swizzle<1, 3, 3, 0>();
	}
	vec4i ywwy()const{
		return swizzle<1, 3, 3, 1>();
	}
	vec4i ywwz()const{
		return swizzle<1, 3, 3, 2>();
	}
	vec4i ywww()const{
		return swizzle<1, 3, 3, 3>();
	}
	vec4i zxxx()const{
		return swizzle<2, 0, 0, 0>();
	}
	vec4i zxxy()const{
		return swizzle<2, 0, 0, 1>();
	}
	vec4i zxxz()const{
		return swizzle<2, 0, 0, 2>();
	}
	vec4i zxxw()const{
		return swizzle<2, 0, 0, 3>();
	}
	vec4i zxyx()const{
		return swizzle<2, 0, 1, 0>();
	}
	vec4i zxyy()const{
		return swizzle<2, 0, 1, 1>();
	}
	vec4i zxyz()const{
		return swizzle<2, 0, 1, 2>();
	}
	vec4i zxyw()const{
		return swizzle<2, 0, 1, 3>();
	}
	vec4i zxzx()const{
		return swizzle<2, 0, 2, 0>();
	}
	vec4i zxzy()const{
		return swizzle<2, 0, 2, 1>();
	}
	vec4i zxzz()const{
		return swizzle<2, 0, 2, 2>();
	}
	vec4i zxzw()const{
		return swizzle<2, 0, 2, 3>();
	}
	vec4i zxwx()const{
		return swizzle<2, 0, 3, 0>();
	}
	vec4i zxwy()const{
		return swizzle<2, 0, 3, 1>();
	}
	vec4i zxwz()const{
		return swizzle<2, 0, 3, 2>();
	}
	vec4i zxww()const{
		return swizzle<2, 0, 3, 3>();
	}
	vec4i zyxx()const{
		return swizzle<2, 1, 0, 0>();
	}
	vec4i zyxy()const{
		return swizzle<2, 1, 0, 1>();
	}
	vec4i zyxz()const{
		return swizzle<2, 1, 0, 2>();
	}
	vec4i zyxw()const{
		return swizzle<2, 1, 0, 3>();
	}
	vec4i zyyx()const{
		return swizzle<2, 1, 1, 0>();
	}
	vec4i zyyy()const{
		return swizzle<2, 1, 1, 1>();
	}
	vec4i zyyz()const{
		return swizzle<2, 1, 1, 2>();
	}
	vec4i zyyw()const{
		return swizzle<2, 1, 1, 3>();
	}
	vec4i zyzx()const{
		return swizzle<2, 1, 2, 0>();
	}
	vec4i zyzy()const{
		return swizzle<2, 1, 2, 1>();
	}
	vec4i zyzz()const{
		return swizzle<2, 1, 2, 2>();
	}
	vec4i zyzw()const{
		return swizzle<2, 1, 2, 3>();
	}
	vec4i zywx()const{
		return swizzle<2, 1, 3, 0>();
	}
	vec4i zywy()const{
		return swizzle<2, 1, 3, 1>();
	}
	vec4i zywz()const{
		return swizzle<2, 1, 3, 2>();
	}
	vec4i zyww()const{
		return swizzle<2, 1, 3, 3>();
	}
	vec4i zzxx()const{
		return swizzle<2, 2, 0, 0>();
	}
	vec4i zzxy()const{
		return swizzle<2, 2, 0, 1>();
	}
	vec4i zzxz()const{
		return swizzle<2, 2, 0, 2>();
	}
	vec4i zzxw()const{
		return swizzle<2, 2, 0, 3>();
	}
	vec4i zzyx()const{
		return swizzle<2, 2, 1, 0>();
	}
	vec4i zzyy()const{
		return swizzle<2, 2, 1, 1>();
	}
	vec4i zzyz()const{
		return swizzle<2, 2, 1, 2>();
	}
	vec4i zzyw()const{
		return swizzle<2, 2, 1, 3>();
	}
	vec4i zzzx()const{
		return swizzle<2, 2, 2, 0>();
	}
	vec4i zzzy()const{
		return swizzle<2, 2, 2, 1>();
	}
	vec4i zzzz()const{
		return swizzle<2, 2, 2, 2>();
	}
	vec4i zzzw()const{
		return swizzle<2, 2, 2, 3>();
	}
	vec4i zzwx()const{
		return swizzle<2, 2, 3, 0>();
	}
	vec4i zzwy()const{
		return swizzle<2, 2, 3, 1>();
	}
	vec4i zzwz()const{
		return swizzle<2, 2, 3, 2>();
	}
	vec4i zzww()const{
		return swizzle<2, 2, 3, 3>();
	}
	vec4i zwxx()const{
		return swizzle<2, 3, 0, 0>();
	}
	vec4i zwxy()const{
		return swizzle<2, 3, 0, 1>();
	}
	vec4i zwxz()const{
		return swizzle<2, 3, 0, 2>();
	}
	vec4i zwxw()const{
		return swizzle<2, 3, 0, 3>();
	}
	vec4i zwyx()const{
		return swizzle<2, 3, 1, 0>();
	}
	vec4i zwyy()const{
		return swizzle<2, 3, 1, 1>();
	}
	vec4i zwyz()const{
		return swizzle<2, 3, 1, 2>();
	}
	vec4i zwyw()const{
		return swizzle<2, 3, 1, 3>();
	}
	vec4i zwzx()const{
		return swizzle<2, 3, 2, 0>();
	}
	vec4i zwzy()const{
		return swizzle<2, 3, 2, 1>();
	}
	vec4i zwzz()const{
		return swizzle<2, 3, 2, 2>();
	}
	vec4i zwzw()const{
		return swizzle<2, 3, 2, 3>();
	}
	vec4i zwwx()const{
		return swizzle<2, 3, 3, 0>();
	}
	vec4i zwwy()const{
		return swizzle<2, 3, 3, 1>();
	}
	vec4i zwwz()const{
		return swizzle<2, 3, 3, 2>();
	}
	vec4i zwww()const{
		return swizzle<2, 3, 3, 3>();
	}
	vec4i wxxx()const{
		return swizzle<3, 0, 0, 0>();
	}
	vec4i wxxy()const{
		return swizzle<3, 0, 0, 1>();
	}
	vec4i wxxz()const{
		return swizzle<3, 0, 0, 2>();
	}
	vec4i wxxw()const{
		return swizzle<3, 0, 0, 3>();
	}
	vec4i wxyx()const{
		return swizzle<3, 0, 1, 0>();
	}
	vec4i wxyy()const{
		return swizzle<3, 0, 1, 1>();
	}
	vec4i wxyz()const{
		return swizzle<3, 0, 1, 2>();
	}
	vec4i wxyw()const{
		return swizzle<3, 0, 1, 3>();
	}
	vec4i wxzx()const{
		return swizzle<3, 0, 2, 0>();
	}
	vec4i wxzy()const{
		return swizzle<3, 0, 2, 1>();
	}
	vec4i wxzz()const{
		return swizzle<3, 0, 2, 2>();
	}
	vec4i wxzw()const{
		return swizzle<3, 0, 2, 3>();
	}
	vec4i wxwx()const{
		return swizzle<3, 0, 3, 0>();
	}
	vec4i wxwy()const{
		return swizzle<3, 0, 3, 1>();
	}
	vec4i wxwz()const{
		return swizzle<3, 0, 3, 2>();
	}
	vec4i wxww()const{
		return swizzle<3, 0, 3, 3>();
	}
	vec4i wyxx()const{
		return swizzle<3, 1, 0, 0>();
	}
	vec4i wyxy()const{
		return swizzle<3, 1, 0, 1>();
	}
	vec4i wyxz()const{
		return swizzle<3, 1, 0, 2>();
	}
	vec4i wyxw()const{
		return swizzle<3, 1, 0, 3>();
	}
	vec4i wyyx()const{
		return swizzle<3, 1, 1, 0>();
	}
	vec4i wyyy()const{
		return swizzle<3, 1, 1, 1>();
	}
	vec4i wyyz()const{
		return swizzle<3, 1, 1, 2>();
	}
	vec4i wyyw()const{
		return swizzle<3, 1, 1, 3>();
	}
	vec4i wyzx()const{
		return swizzle<3, 1, 2, 0>();
	}
	vec4i wyzy()const{
		return swizzle<3, 1, 2, 1>();
	}
	vec4i wyzz()const{
		return swizzle<3, 1, 2, 2>();
	}
	vec4i wyzw()const{
		return swizzle<3, 1, 2, 3>();
	}
	vec4i wywx()const{
		return swizzle<3, 1, 3, 0>();
	}
	vec4i wywy()const{
		return swizzle<3, 1, 3, 1>();
	}
	vec4i wywz()const{
		return swizzle<3, 1, 3, 2>();
	}
	vec4i wyww()const{
		return swizzle<3, 1, 3, 3>();
	}
	vec4i wzxx()const{
		return swizzle<3, 2, 0, 0>();
	}
	vec4i wzxy()const{
		return swizzle<3, 2, 0, 1>();
	}
	vec4i wzxz()const{
		return swizzle<3, 2, 0, 2>();
	}
	vec4i wzxw()const{
		return swizzle<3, 2, 0, 3>();
	}
	vec4i wzyx()const{
		return swizzle<3, 2, 1, 0>();
	}
	vec4i wzyy()const{
		return swizzle<3, 2, 1, 1>();
	}
	vec4i wzyz()const{
		return swizzle<3, 2, 1, 2>();
	}
	vec4i wzyw()const{
		return swizzle<3, 2, 1, 3>();
	}
	vec4i wzzx()const{
		return swizzle<3, 2, 2, 0>();
	}
	vec4i wzzy()const{
		return swizzle<3, 2, 2, 1>();
	}
	vec4i wzzz()const{
		return swizzle<3, 2, 2, 2>();
	}
	vec4i wzzw()const{
		return swizzle<3, 2, 2, 3>();
	}
	vec4i wzwx()const{
		return swizzle<3, 2, 3, 0>();
	}
	vec4i wzwy()const{
		return swizzle<3, 2, 3, 1>();
	}
	vec4i wzwz()const{
		return swizzle<3, 2, 3, 2>();
	}
	vec4i wzww()const{
		return swizzle<3, 2, 3, 3>();
	}
	vec4i wwxx()const{
		return swizzle<3, 3, 0, 0>();
	}
	vec4i wwxy()const{
		return swizzle<3, 3, 0, 1>();
	}
	vec4i wwxz()const{
		return swizzle<3, 3, 0, 2>();
	}
	vec4i wwxw()const{
		return swizzle<3, 3, 0, 3>();
	}
	vec4i wwyx()const{
		return swizzle<3, 3, 1, 0>();
	}
	vec4i wwyy()const{
		return swizzle<3, 3, 1, 1>();
	}
	vec4i wwyz()const{
		return swizzle<3, 3, 1, 2>();
	}
	vec4i wwyw()const{
		return swizzle<3, 3, 1, 3>();
	}
	vec4i wwzx()const{
		return swizzle<3, 3, 2, 0>();
	}
	vec4i wwzy()const{
		return swizzle<3, 3, 2, 1>();
	}
	vec4i wwzz()const{
		return swizzle<3, 3, 2, 2>();
	}
	vec4i wwzw()const{
		return swizzle<3, 3, 2, 3>();
	}
	vec4i wwwx()const{
		return swizzle<3, 3, 3, 0>();
	}
	vec4i wwwy()const{
		return swizzle<3, 3, 3, 1>();
	}
	vec4i wwwz()const{
		return swizzle<3, 3, 3, 2>();
	}
	vec4i wwww()const{
		return swizzle<3, 3, 3, 3>();
	}
	template<unsigned a1, unsigned a2 = a1, unsigned a3 = a2, unsigned a4 = a3>
	vec4i swizzle()const{
		static_assert(a1 < 4, "Swizzle argument out of range (>= 4)");
		static_assert(a2 < 4, "Swizzle argument out of range (>= 4)");
		static_assert(a3 < 4, "Swizzle argument out of range (>= 4)");
		static_assert(a4 < 4, "Swizzle argument out of range (>= 4)");
		constexpr int imm8 = a1 | a2 << 2 | a3 << 4 | a4 << 6;
		vec4i ret;
		ret.data = (_mm256_permute4x64_epi64(data, imm8));
		return ret;
	}
	vec4i& operator<<=(int o){
		data = _mm256_slli_epi64(data, o);
		return *this;
	}
	vec4i operator<<(int o)const{
		vec4i ret;
		ret.data = _mm256_slli_epi64(data, o);
		return ret;
	}
	vec4i& operator>>=(int o){
		data = _mm256_srli_epi64(data, o);
		return *this;
	}
	vec4i operator>>(int o)const{
		vec4i ret;
		ret.data = _mm256_srli_epi64(data, o);
		return ret;
	}
	int64_t operator[](unsigned i)const{
		assert(i < 4);
		alignas(32) uint64_t a[4];
		_mm256_store_si256((__m256i*)a, data);
		return a[i];
	}
	//int64_t& operator[](unsigned i){
	//	assert(i < 4);
	//	return ((int64_t*)&data)[i];
	//}
	template<typename stream_t>
	friend std::enable_if_t<!std::is_same<stream_t, vec4i>::value, stream_t>& operator<<(stream_t& str, const vec4i& o){
		alignas(32) uint64_t a[4];
		_mm256_store_si256((__m256i*)a, o.data);
		for(int i = 0;i < 4;i++){
			str << a[i] << (i < 3 ? ", " : "");
		}
		return str;
	}
};

struct vec8i{
	__m256i data;
	vec8i() : data (_mm256_set1_epi32(0)){
		
	}
	vec8i(int a) : data (_mm256_set1_epi32(a)){
		
	}
	vec8i(int a, int b, int c, int d, int e, int f, int g, int h) : data(_mm256_set_epi32(h,g,f,e,d,c,b,a)){
		
	}
	vec8i& operator+=(const vec8i& o){
		data = _mm256_add_epi32(data, o.data);
		return *this;
	}
	vec8i operator+(const vec8i& o)const{
		vec8i ret;
		ret.data = _mm256_add_epi32(data, o.data);
		return ret;
	}
	vec8i& operator-=(const vec8i& o){
		data = _mm256_sub_epi32(data, o.data);
		return *this;
	}
	vec8i operator-(const vec8i& o)const{
		vec8i ret;
		ret.data = _mm256_sub_epi32(data, o.data);
		return ret;
	}
	vec8i& operator&=(const vec8i& o){
		data = _mm256_and_si256(data, o.data);
		return *this;
	}
	vec8i operator&(const vec8i& o)const{
		vec8i ret;
		ret.data = _mm256_and_si256(data, o.data);
		return ret;
	}
	vec8i& operator|=(const vec8i& o){
		data = _mm256_or_si256(data, o.data);
		return *this;
	}
	vec8i operator|(const vec8i& o)const{
		vec8i ret;
		ret.data = _mm256_or_si256(data, o.data);
		return ret;
	}
	vec8i& operator^=(const vec8i& o){
		data = _mm256_xor_si256(data, o.data);
		return *this;
	}
	vec8i operator^(const vec8i& o)const{
		vec8i ret;
		ret.data = _mm256_xor_si256(data, o.data);
		return ret;
	}
	vec8i operator!()const{
		vec8i z(0);
		z.data = _mm256_cmpeq_epi32(data, z.data);
		return z;
	}
	vec8i operator~()const{
		vec8i xm(~0);
		xm ^= *this;
		return xm;
	}
	bool all()const{
		vec8i z(0);
		return (_mm256_movemask_epi8(_mm256_cmpeq_epi32(data, z.data))) == 0;
	}
	int movemask()const{
		return _mm256_movemask_epi8(data);
	}
	bool is_zero()const{
		vec8i z(0);
		return (~_mm256_movemask_epi8(_mm256_cmpeq_epi32(data, z.data))) == 0;
	}
	template<unsigned a1, unsigned a2 = a1,unsigned a3 = a2, unsigned a4 = a3, unsigned a5 = a4, unsigned a6 = a5, unsigned a7 = a6, unsigned a8 = a7>
	vec8i swizzle()const{
		static_assert(a1 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a2 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a3 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a4 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a5 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a6 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a7 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a8 < 8, "Swizzle argument out of range (>= 8)");
		__m256i idx = _mm256_set_epi32(a8, a7, a6, a5, a4, a3, a2, a1);
		vec8i ret;
		ret.data = _mm256_permutevar8x32_epi32(data, idx);
		return ret;
	}
	vec8i sum()const{
		vec8i ret = *this;
		ret += ret.swizzle<1,0,3,2,5,4,7,6>();
		ret += ret.swizzle<2,3,0,1,6,7,4,5>();
		ret += ret.swizzle<4,5,6,7,0,1,2,3>();
		return ret;
	}
	vec8i& operator<<=(int o){
		data = _mm256_slli_epi32(data, o);
		return *this;
	}
	vec8i operator<<(int o)const{
		vec8i ret;
		ret.data = _mm256_slli_epi32(data, o);
		return ret;
	}
	vec8i& operator>>=(int o){
		data = _mm256_srli_epi32(data, o);
		return *this;
	}
	vec8i operator>>(int o)const{
		vec8i ret;
		ret.data = _mm256_srli_epi32(data, o);
		return ret;
	}
	int64_t operator[](unsigned i)const{
		assert(i < 4);
		alignas(32) uint64_t a[4];
		_mm256_store_si256((__m256i*)a, data);
		return a[i];
	}
	//int64_t& operator[](unsigned i){
	//	assert(i < 4);
	//	return ((int64_t*)&data)[i];
	//}
	template<typename stream_t>
	friend std::enable_if_t<!std::is_same<stream_t, vec8i>::value, stream_t>& operator<<(stream_t& str, const vec8i& o){
		alignas(32) unsigned a[8];
		_mm256_store_si256((__m256i*)a, o.data);
		for(int i = 0;i < 8;i++){
			str << a[i] << (i < 7 ? ", " : "");
		}
		return str;
	}
};

struct vec4d{
	__m256d data;
	vec4d(double a) : data(_mm256_set1_pd(a)){}
	vec4d(double a, double b, double c, double d) : data(_mm256_set_pd(d,c,b,a)){}
	vec4d() : data(){}
	#ifdef NDEBUG
	vec4d(const double* ptr) : data(_mm256_load_pd(ptr)){}
	#else
	vec4d(const double* ptr){
		assert((((size_t)ptr) % 32) == 0 && "Pointer not aligned!");
		data = _mm256_load_pd(ptr);
	}
	#endif
	vec4d& operator+=(const vec4d& o){
		data = _mm256_add_pd(data, o.data);
		return *this;
	}
	vec4d operator+(const vec4d& o)const{
		vec4d ret;
		ret.data = _mm256_add_pd(data, o.data);
		return ret;
	}
	vec4d& operator-=(const vec4d& o){
		data = _mm256_sub_pd(data, o.data);
		return *this;
	}
	vec4d operator-(const vec4d& o)const{
		vec4d ret;
		ret.data = _mm256_sub_pd(data, o.data);
		return ret;
	}
	vec4d& operator*=(const vec4d& o){
		data = _mm256_mul_pd(data, o.data);
		return *this;
	}
	vec4d operator*(const vec4d& o)const{
		vec4d ret;
		ret.data = _mm256_mul_pd(data, o.data);
		return ret;
	}
	vec4d& operator/=(const vec4d& o){
		data = _mm256_div_pd(data, o.data);
		return *this;
	}
	vec4d operator/(const vec4d& o)const{
		vec4d ret;
		ret.data = _mm256_div_pd(data, o.data);
		return ret;
	}
	vec4d& fmsa(const vec4d& o, const vec4d& p){
		data = _mm256_fmsub_pd(data, o.data, p.data);
		return *this;
	}
	vec4d fms(const vec4d& o, const vec4d& p)const{
		vec4d ret;
		ret.data = _mm256_fmsub_pd(data, o.data, p.data);
		return ret;
	}
	vec4d& fmaa(const vec4d& o, const vec4d& p){
		data = _mm256_fmadd_pd(data, o.data, p.data);
		return *this;
	}
	vec4d fma(const vec4d& o, const vec4d& p)const{
		vec4d ret;
		ret.data = _mm256_fmadd_pd(data, o.data, p.data);
		return ret;
	}
	vec4d sum()const{
		vec4d ret = *this;
		ret += ret.swizzle<1,0,3,2>();
		ret += ret.swizzle<2,3,0,1>();
		return ret;
	}
	vec4d dp1(const vec4d& o)const{
		vec4d ret;
		__m128d p1 = _mm256_castpd256_pd128(data);
		__m128d p2 = _mm256_extractf128_pd(data, 1);
		__m128d op1 = _mm256_castpd256_pd128(o.data);
		__m128d op2 = _mm256_extractf128_pd(o.data, 1);
		p1 = _mm_dp_pd(p1, op1, 255);
		p2 = _mm_dp_pd(p2, op2, 255);
		p1 = _mm_add_pd(p1, p2);
		ret.data = _mm256_setr_m128d(p1, p1);
		return ret;
	}
	vec4d dp2(const vec4d& o)const{
		vec4d ret = (*this) * o;
		ret += ret.swizzle<1,0,3,2>();
		ret += ret.swizzle<2,3,0,1>();
		return ret;
	}
	vec4d dp3(const vec4d& o)const{
		double r = 0;
		for(unsigned i = 0;i < 4;i++){
			r += this->operator[](i) * o[i];
		}
		return vec4d(r);
	}
	double operator[](unsigned i)const{
		assert(i < 4);
		return ((double*)&data)[i];
	}
	double& operator[](unsigned i){
		assert(i < 4);
		return ((double*)&data)[i];
	}
	vec4i operator<(const vec4d& o)const{
		vec4i ret;
		ret.data = _mm256_castpd_si256(_mm256_cmp_pd(data, o.data, _CMP_LT_OQ));
		return ret;
	}
	vec4i operator>(const vec4d& o)const{
		vec4i ret;
		ret.data = _mm256_castpd_si256(_mm256_cmp_pd(data, o.data, _CMP_GT_OQ));
		return ret;
	}
	vec4i operator<=(const vec4d& o)const{
		vec4i ret;
		ret.data = _mm256_castpd_si256(_mm256_cmp_pd(data, o.data, _CMP_LE_OQ));
		return ret;
	}
	vec4i operator>=(const vec4d& o)const{
		vec4i ret;
		ret.data = _mm256_castpd_si256(_mm256_cmp_pd(data, o.data, _CMP_GE_OQ));
		return ret;
	}
	vec4i operator!=(const vec4d& o)const{
		vec4i ret;
		ret.data = _mm256_castpd_si256(_mm256_cmp_pd(data, o.data, _CMP_NEQ_OQ));
		return ret;
	}
	vec4i operator==(const vec4d& o)const{
		vec4i ret;
		ret.data = _mm256_castpd_si256(_mm256_cmp_pd(data, o.data, _CMP_EQ_OQ));
		return ret;
	}
	template<unsigned a1, unsigned a2 = a1, unsigned a3 = a2, unsigned a4 = a3>
	vec4d swizzle()const{
		static_assert(a1 < 4, "Swizzle argument out of range (>= 4)");
		static_assert(a2 < 4, "Swizzle argument out of range (>= 4)");
		static_assert(a3 < 4, "Swizzle argument out of range (>= 4)");
		static_assert(a4 < 4, "Swizzle argument out of range (>= 4)");
		IF_CONSTEXPR(a1 < 2 && a2 < 2 && a3 >= 2 && a4 >= 2){
			constexpr int imm8 = a1 | a2 << 1 | (a3 & 1) << 2 | (a4 & 1) << 3;
			vec4d ret;
			ret.data = _mm256_permute_pd(data, imm8);
			return ret;
		}
		else{
			constexpr int imm8 = a1 | a2 << 2 | a3 << 4 | a4 << 6;
			vec4d ret;
			ret.data = (_mm256_permute4x64_pd(data, imm8));
			return ret;
		}
	}
	void store(double* db)const{
		assert((((size_t)db) % 32 == 0) && "Store pointer not aligned!");
		_mm256_store_pd(db, data);
	}
	template<typename stream_t>
	friend stream_t& operator<<(stream_t& str, const vec4d& o){
		for(int i = 0;i < 4;i++){
			str << o[i] << (i < 3 ? ", " : "");
		}
		return str;
	}
	operator vec4i()const{
		vec4i ret;
		ret.data = _mm256_cvtepi32_epi64(_mm256_cvtpd_epi32(_mm256_floor_pd(data)));
		return ret;
	}
	vec4d xxxx()const{
		return swizzle<0, 0, 0, 0>();
	}
	vec4d xxxy()const{
		return swizzle<0, 0, 0, 1>();
	}
	vec4d xxxz()const{
		return swizzle<0, 0, 0, 2>();
	}
	vec4d xxxw()const{
		return swizzle<0, 0, 0, 3>();
	}
	vec4d xxyx()const{
		return swizzle<0, 0, 1, 0>();
	}
	vec4d xxyy()const{
		return swizzle<0, 0, 1, 1>();
	}
	vec4d xxyz()const{
		return swizzle<0, 0, 1, 2>();
	}
	vec4d xxyw()const{
		return swizzle<0, 0, 1, 3>();
	}
	vec4d xxzx()const{
		return swizzle<0, 0, 2, 0>();
	}
	vec4d xxzy()const{
		return swizzle<0, 0, 2, 1>();
	}
	vec4d xxzz()const{
		return swizzle<0, 0, 2, 2>();
	}
	vec4d xxzw()const{
		return swizzle<0, 0, 2, 3>();
	}
	vec4d xxwx()const{
		return swizzle<0, 0, 3, 0>();
	}
	vec4d xxwy()const{
		return swizzle<0, 0, 3, 1>();
	}
	vec4d xxwz()const{
		return swizzle<0, 0, 3, 2>();
	}
	vec4d xxww()const{
		return swizzle<0, 0, 3, 3>();
	}
	vec4d xyxx()const{
		return swizzle<0, 1, 0, 0>();
	}
	vec4d xyxy()const{
		return swizzle<0, 1, 0, 1>();
	}
	vec4d xyxz()const{
		return swizzle<0, 1, 0, 2>();
	}
	vec4d xyxw()const{
		return swizzle<0, 1, 0, 3>();
	}
	vec4d xyyx()const{
		return swizzle<0, 1, 1, 0>();
	}
	vec4d xyyy()const{
		return swizzle<0, 1, 1, 1>();
	}
	vec4d xyyz()const{
		return swizzle<0, 1, 1, 2>();
	}
	vec4d xyyw()const{
		return swizzle<0, 1, 1, 3>();
	}
	vec4d xyzx()const{
		return swizzle<0, 1, 2, 0>();
	}
	vec4d xyzy()const{
		return swizzle<0, 1, 2, 1>();
	}
	vec4d xyzz()const{
		return swizzle<0, 1, 2, 2>();
	}
	vec4d xyzw()const{
		return swizzle<0, 1, 2, 3>();
	}
	vec4d xywx()const{
		return swizzle<0, 1, 3, 0>();
	}
	vec4d xywy()const{
		return swizzle<0, 1, 3, 1>();
	}
	vec4d xywz()const{
		return swizzle<0, 1, 3, 2>();
	}
	vec4d xyww()const{
		return swizzle<0, 1, 3, 3>();
	}
	vec4d xzxx()const{
		return swizzle<0, 2, 0, 0>();
	}
	vec4d xzxy()const{
		return swizzle<0, 2, 0, 1>();
	}
	vec4d xzxz()const{
		return swizzle<0, 2, 0, 2>();
	}
	vec4d xzxw()const{
		return swizzle<0, 2, 0, 3>();
	}
	vec4d xzyx()const{
		return swizzle<0, 2, 1, 0>();
	}
	vec4d xzyy()const{
		return swizzle<0, 2, 1, 1>();
	}
	vec4d xzyz()const{
		return swizzle<0, 2, 1, 2>();
	}
	vec4d xzyw()const{
		return swizzle<0, 2, 1, 3>();
	}
	vec4d xzzx()const{
		return swizzle<0, 2, 2, 0>();
	}
	vec4d xzzy()const{
		return swizzle<0, 2, 2, 1>();
	}
	vec4d xzzz()const{
		return swizzle<0, 2, 2, 2>();
	}
	vec4d xzzw()const{
		return swizzle<0, 2, 2, 3>();
	}
	vec4d xzwx()const{
		return swizzle<0, 2, 3, 0>();
	}
	vec4d xzwy()const{
		return swizzle<0, 2, 3, 1>();
	}
	vec4d xzwz()const{
		return swizzle<0, 2, 3, 2>();
	}
	vec4d xzww()const{
		return swizzle<0, 2, 3, 3>();
	}
	vec4d xwxx()const{
		return swizzle<0, 3, 0, 0>();
	}
	vec4d xwxy()const{
		return swizzle<0, 3, 0, 1>();
	}
	vec4d xwxz()const{
		return swizzle<0, 3, 0, 2>();
	}
	vec4d xwxw()const{
		return swizzle<0, 3, 0, 3>();
	}
	vec4d xwyx()const{
		return swizzle<0, 3, 1, 0>();
	}
	vec4d xwyy()const{
		return swizzle<0, 3, 1, 1>();
	}
	vec4d xwyz()const{
		return swizzle<0, 3, 1, 2>();
	}
	vec4d xwyw()const{
		return swizzle<0, 3, 1, 3>();
	}
	vec4d xwzx()const{
		return swizzle<0, 3, 2, 0>();
	}
	vec4d xwzy()const{
		return swizzle<0, 3, 2, 1>();
	}
	vec4d xwzz()const{
		return swizzle<0, 3, 2, 2>();
	}
	vec4d xwzw()const{
		return swizzle<0, 3, 2, 3>();
	}
	vec4d xwwx()const{
		return swizzle<0, 3, 3, 0>();
	}
	vec4d xwwy()const{
		return swizzle<0, 3, 3, 1>();
	}
	vec4d xwwz()const{
		return swizzle<0, 3, 3, 2>();
	}
	vec4d xwww()const{
		return swizzle<0, 3, 3, 3>();
	}
	vec4d yxxx()const{
		return swizzle<1, 0, 0, 0>();
	}
	vec4d yxxy()const{
		return swizzle<1, 0, 0, 1>();
	}
	vec4d yxxz()const{
		return swizzle<1, 0, 0, 2>();
	}
	vec4d yxxw()const{
		return swizzle<1, 0, 0, 3>();
	}
	vec4d yxyx()const{
		return swizzle<1, 0, 1, 0>();
	}
	vec4d yxyy()const{
		return swizzle<1, 0, 1, 1>();
	}
	vec4d yxyz()const{
		return swizzle<1, 0, 1, 2>();
	}
	vec4d yxyw()const{
		return swizzle<1, 0, 1, 3>();
	}
	vec4d yxzx()const{
		return swizzle<1, 0, 2, 0>();
	}
	vec4d yxzy()const{
		return swizzle<1, 0, 2, 1>();
	}
	vec4d yxzz()const{
		return swizzle<1, 0, 2, 2>();
	}
	vec4d yxzw()const{
		return swizzle<1, 0, 2, 3>();
	}
	vec4d yxwx()const{
		return swizzle<1, 0, 3, 0>();
	}
	vec4d yxwy()const{
		return swizzle<1, 0, 3, 1>();
	}
	vec4d yxwz()const{
		return swizzle<1, 0, 3, 2>();
	}
	vec4d yxww()const{
		return swizzle<1, 0, 3, 3>();
	}
	vec4d yyxx()const{
		return swizzle<1, 1, 0, 0>();
	}
	vec4d yyxy()const{
		return swizzle<1, 1, 0, 1>();
	}
	vec4d yyxz()const{
		return swizzle<1, 1, 0, 2>();
	}
	vec4d yyxw()const{
		return swizzle<1, 1, 0, 3>();
	}
	vec4d yyyx()const{
		return swizzle<1, 1, 1, 0>();
	}
	vec4d yyyy()const{
		return swizzle<1, 1, 1, 1>();
	}
	vec4d yyyz()const{
		return swizzle<1, 1, 1, 2>();
	}
	vec4d yyyw()const{
		return swizzle<1, 1, 1, 3>();
	}
	vec4d yyzx()const{
		return swizzle<1, 1, 2, 0>();
	}
	vec4d yyzy()const{
		return swizzle<1, 1, 2, 1>();
	}
	vec4d yyzz()const{
		return swizzle<1, 1, 2, 2>();
	}
	vec4d yyzw()const{
		return swizzle<1, 1, 2, 3>();
	}
	vec4d yywx()const{
		return swizzle<1, 1, 3, 0>();
	}
	vec4d yywy()const{
		return swizzle<1, 1, 3, 1>();
	}
	vec4d yywz()const{
		return swizzle<1, 1, 3, 2>();
	}
	vec4d yyww()const{
		return swizzle<1, 1, 3, 3>();
	}
	vec4d yzxx()const{
		return swizzle<1, 2, 0, 0>();
	}
	vec4d yzxy()const{
		return swizzle<1, 2, 0, 1>();
	}
	vec4d yzxz()const{
		return swizzle<1, 2, 0, 2>();
	}
	vec4d yzxw()const{
		return swizzle<1, 2, 0, 3>();
	}
	vec4d yzyx()const{
		return swizzle<1, 2, 1, 0>();
	}
	vec4d yzyy()const{
		return swizzle<1, 2, 1, 1>();
	}
	vec4d yzyz()const{
		return swizzle<1, 2, 1, 2>();
	}
	vec4d yzyw()const{
		return swizzle<1, 2, 1, 3>();
	}
	vec4d yzzx()const{
		return swizzle<1, 2, 2, 0>();
	}
	vec4d yzzy()const{
		return swizzle<1, 2, 2, 1>();
	}
	vec4d yzzz()const{
		return swizzle<1, 2, 2, 2>();
	}
	vec4d yzzw()const{
		return swizzle<1, 2, 2, 3>();
	}
	vec4d yzwx()const{
		return swizzle<1, 2, 3, 0>();
	}
	vec4d yzwy()const{
		return swizzle<1, 2, 3, 1>();
	}
	vec4d yzwz()const{
		return swizzle<1, 2, 3, 2>();
	}
	vec4d yzww()const{
		return swizzle<1, 2, 3, 3>();
	}
	vec4d ywxx()const{
		return swizzle<1, 3, 0, 0>();
	}
	vec4d ywxy()const{
		return swizzle<1, 3, 0, 1>();
	}
	vec4d ywxz()const{
		return swizzle<1, 3, 0, 2>();
	}
	vec4d ywxw()const{
		return swizzle<1, 3, 0, 3>();
	}
	vec4d ywyx()const{
		return swizzle<1, 3, 1, 0>();
	}
	vec4d ywyy()const{
		return swizzle<1, 3, 1, 1>();
	}
	vec4d ywyz()const{
		return swizzle<1, 3, 1, 2>();
	}
	vec4d ywyw()const{
		return swizzle<1, 3, 1, 3>();
	}
	vec4d ywzx()const{
		return swizzle<1, 3, 2, 0>();
	}
	vec4d ywzy()const{
		return swizzle<1, 3, 2, 1>();
	}
	vec4d ywzz()const{
		return swizzle<1, 3, 2, 2>();
	}
	vec4d ywzw()const{
		return swizzle<1, 3, 2, 3>();
	}
	vec4d ywwx()const{
		return swizzle<1, 3, 3, 0>();
	}
	vec4d ywwy()const{
		return swizzle<1, 3, 3, 1>();
	}
	vec4d ywwz()const{
		return swizzle<1, 3, 3, 2>();
	}
	vec4d ywww()const{
		return swizzle<1, 3, 3, 3>();
	}
	vec4d zxxx()const{
		return swizzle<2, 0, 0, 0>();
	}
	vec4d zxxy()const{
		return swizzle<2, 0, 0, 1>();
	}
	vec4d zxxz()const{
		return swizzle<2, 0, 0, 2>();
	}
	vec4d zxxw()const{
		return swizzle<2, 0, 0, 3>();
	}
	vec4d zxyx()const{
		return swizzle<2, 0, 1, 0>();
	}
	vec4d zxyy()const{
		return swizzle<2, 0, 1, 1>();
	}
	vec4d zxyz()const{
		return swizzle<2, 0, 1, 2>();
	}
	vec4d zxyw()const{
		return swizzle<2, 0, 1, 3>();
	}
	vec4d zxzx()const{
		return swizzle<2, 0, 2, 0>();
	}
	vec4d zxzy()const{
		return swizzle<2, 0, 2, 1>();
	}
	vec4d zxzz()const{
		return swizzle<2, 0, 2, 2>();
	}
	vec4d zxzw()const{
		return swizzle<2, 0, 2, 3>();
	}
	vec4d zxwx()const{
		return swizzle<2, 0, 3, 0>();
	}
	vec4d zxwy()const{
		return swizzle<2, 0, 3, 1>();
	}
	vec4d zxwz()const{
		return swizzle<2, 0, 3, 2>();
	}
	vec4d zxww()const{
		return swizzle<2, 0, 3, 3>();
	}
	vec4d zyxx()const{
		return swizzle<2, 1, 0, 0>();
	}
	vec4d zyxy()const{
		return swizzle<2, 1, 0, 1>();
	}
	vec4d zyxz()const{
		return swizzle<2, 1, 0, 2>();
	}
	vec4d zyxw()const{
		return swizzle<2, 1, 0, 3>();
	}
	vec4d zyyx()const{
		return swizzle<2, 1, 1, 0>();
	}
	vec4d zyyy()const{
		return swizzle<2, 1, 1, 1>();
	}
	vec4d zyyz()const{
		return swizzle<2, 1, 1, 2>();
	}
	vec4d zyyw()const{
		return swizzle<2, 1, 1, 3>();
	}
	vec4d zyzx()const{
		return swizzle<2, 1, 2, 0>();
	}
	vec4d zyzy()const{
		return swizzle<2, 1, 2, 1>();
	}
	vec4d zyzz()const{
		return swizzle<2, 1, 2, 2>();
	}
	vec4d zyzw()const{
		return swizzle<2, 1, 2, 3>();
	}
	vec4d zywx()const{
		return swizzle<2, 1, 3, 0>();
	}
	vec4d zywy()const{
		return swizzle<2, 1, 3, 1>();
	}
	vec4d zywz()const{
		return swizzle<2, 1, 3, 2>();
	}
	vec4d zyww()const{
		return swizzle<2, 1, 3, 3>();
	}
	vec4d zzxx()const{
		return swizzle<2, 2, 0, 0>();
	}
	vec4d zzxy()const{
		return swizzle<2, 2, 0, 1>();
	}
	vec4d zzxz()const{
		return swizzle<2, 2, 0, 2>();
	}
	vec4d zzxw()const{
		return swizzle<2, 2, 0, 3>();
	}
	vec4d zzyx()const{
		return swizzle<2, 2, 1, 0>();
	}
	vec4d zzyy()const{
		return swizzle<2, 2, 1, 1>();
	}
	vec4d zzyz()const{
		return swizzle<2, 2, 1, 2>();
	}
	vec4d zzyw()const{
		return swizzle<2, 2, 1, 3>();
	}
	vec4d zzzx()const{
		return swizzle<2, 2, 2, 0>();
	}
	vec4d zzzy()const{
		return swizzle<2, 2, 2, 1>();
	}
	vec4d zzzz()const{
		return swizzle<2, 2, 2, 2>();
	}
	vec4d zzzw()const{
		return swizzle<2, 2, 2, 3>();
	}
	vec4d zzwx()const{
		return swizzle<2, 2, 3, 0>();
	}
	vec4d zzwy()const{
		return swizzle<2, 2, 3, 1>();
	}
	vec4d zzwz()const{
		return swizzle<2, 2, 3, 2>();
	}
	vec4d zzww()const{
		return swizzle<2, 2, 3, 3>();
	}
	vec4d zwxx()const{
		return swizzle<2, 3, 0, 0>();
	}
	vec4d zwxy()const{
		return swizzle<2, 3, 0, 1>();
	}
	vec4d zwxz()const{
		return swizzle<2, 3, 0, 2>();
	}
	vec4d zwxw()const{
		return swizzle<2, 3, 0, 3>();
	}
	vec4d zwyx()const{
		return swizzle<2, 3, 1, 0>();
	}
	vec4d zwyy()const{
		return swizzle<2, 3, 1, 1>();
	}
	vec4d zwyz()const{
		return swizzle<2, 3, 1, 2>();
	}
	vec4d zwyw()const{
		return swizzle<2, 3, 1, 3>();
	}
	vec4d zwzx()const{
		return swizzle<2, 3, 2, 0>();
	}
	vec4d zwzy()const{
		return swizzle<2, 3, 2, 1>();
	}
	vec4d zwzz()const{
		return swizzle<2, 3, 2, 2>();
	}
	vec4d zwzw()const{
		return swizzle<2, 3, 2, 3>();
	}
	vec4d zwwx()const{
		return swizzle<2, 3, 3, 0>();
	}
	vec4d zwwy()const{
		return swizzle<2, 3, 3, 1>();
	}
	vec4d zwwz()const{
		return swizzle<2, 3, 3, 2>();
	}
	vec4d zwww()const{
		return swizzle<2, 3, 3, 3>();
	}
	vec4d wxxx()const{
		return swizzle<3, 0, 0, 0>();
	}
	vec4d wxxy()const{
		return swizzle<3, 0, 0, 1>();
	}
	vec4d wxxz()const{
		return swizzle<3, 0, 0, 2>();
	}
	vec4d wxxw()const{
		return swizzle<3, 0, 0, 3>();
	}
	vec4d wxyx()const{
		return swizzle<3, 0, 1, 0>();
	}
	vec4d wxyy()const{
		return swizzle<3, 0, 1, 1>();
	}
	vec4d wxyz()const{
		return swizzle<3, 0, 1, 2>();
	}
	vec4d wxyw()const{
		return swizzle<3, 0, 1, 3>();
	}
	vec4d wxzx()const{
		return swizzle<3, 0, 2, 0>();
	}
	vec4d wxzy()const{
		return swizzle<3, 0, 2, 1>();
	}
	vec4d wxzz()const{
		return swizzle<3, 0, 2, 2>();
	}
	vec4d wxzw()const{
		return swizzle<3, 0, 2, 3>();
	}
	vec4d wxwx()const{
		return swizzle<3, 0, 3, 0>();
	}
	vec4d wxwy()const{
		return swizzle<3, 0, 3, 1>();
	}
	vec4d wxwz()const{
		return swizzle<3, 0, 3, 2>();
	}
	vec4d wxww()const{
		return swizzle<3, 0, 3, 3>();
	}
	vec4d wyxx()const{
		return swizzle<3, 1, 0, 0>();
	}
	vec4d wyxy()const{
		return swizzle<3, 1, 0, 1>();
	}
	vec4d wyxz()const{
		return swizzle<3, 1, 0, 2>();
	}
	vec4d wyxw()const{
		return swizzle<3, 1, 0, 3>();
	}
	vec4d wyyx()const{
		return swizzle<3, 1, 1, 0>();
	}
	vec4d wyyy()const{
		return swizzle<3, 1, 1, 1>();
	}
	vec4d wyyz()const{
		return swizzle<3, 1, 1, 2>();
	}
	vec4d wyyw()const{
		return swizzle<3, 1, 1, 3>();
	}
	vec4d wyzx()const{
		return swizzle<3, 1, 2, 0>();
	}
	vec4d wyzy()const{
		return swizzle<3, 1, 2, 1>();
	}
	vec4d wyzz()const{
		return swizzle<3, 1, 2, 2>();
	}
	vec4d wyzw()const{
		return swizzle<3, 1, 2, 3>();
	}
	vec4d wywx()const{
		return swizzle<3, 1, 3, 0>();
	}
	vec4d wywy()const{
		return swizzle<3, 1, 3, 1>();
	}
	vec4d wywz()const{
		return swizzle<3, 1, 3, 2>();
	}
	vec4d wyww()const{
		return swizzle<3, 1, 3, 3>();
	}
	vec4d wzxx()const{
		return swizzle<3, 2, 0, 0>();
	}
	vec4d wzxy()const{
		return swizzle<3, 2, 0, 1>();
	}
	vec4d wzxz()const{
		return swizzle<3, 2, 0, 2>();
	}
	vec4d wzxw()const{
		return swizzle<3, 2, 0, 3>();
	}
	vec4d wzyx()const{
		return swizzle<3, 2, 1, 0>();
	}
	vec4d wzyy()const{
		return swizzle<3, 2, 1, 1>();
	}
	vec4d wzyz()const{
		return swizzle<3, 2, 1, 2>();
	}
	vec4d wzyw()const{
		return swizzle<3, 2, 1, 3>();
	}
	vec4d wzzx()const{
		return swizzle<3, 2, 2, 0>();
	}
	vec4d wzzy()const{
		return swizzle<3, 2, 2, 1>();
	}
	vec4d wzzz()const{
		return swizzle<3, 2, 2, 2>();
	}
	vec4d wzzw()const{
		return swizzle<3, 2, 2, 3>();
	}
	vec4d wzwx()const{
		return swizzle<3, 2, 3, 0>();
	}
	vec4d wzwy()const{
		return swizzle<3, 2, 3, 1>();
	}
	vec4d wzwz()const{
		return swizzle<3, 2, 3, 2>();
	}
	vec4d wzww()const{
		return swizzle<3, 2, 3, 3>();
	}
	vec4d wwxx()const{
		return swizzle<3, 3, 0, 0>();
	}
	vec4d wwxy()const{
		return swizzle<3, 3, 0, 1>();
	}
	vec4d wwxz()const{
		return swizzle<3, 3, 0, 2>();
	}
	vec4d wwxw()const{
		return swizzle<3, 3, 0, 3>();
	}
	vec4d wwyx()const{
		return swizzle<3, 3, 1, 0>();
	}
	vec4d wwyy()const{
		return swizzle<3, 3, 1, 1>();
	}
	vec4d wwyz()const{
		return swizzle<3, 3, 1, 2>();
	}
	vec4d wwyw()const{
		return swizzle<3, 3, 1, 3>();
	}
	vec4d wwzx()const{
		return swizzle<3, 3, 2, 0>();
	}
	vec4d wwzy()const{
		return swizzle<3, 3, 2, 1>();
	}
	vec4d wwzz()const{
		return swizzle<3, 3, 2, 2>();
	}
	vec4d wwzw()const{
		return swizzle<3, 3, 2, 3>();
	}
	vec4d wwwx()const{
		return swizzle<3, 3, 3, 0>();
	}
	vec4d wwwy()const{
		return swizzle<3, 3, 3, 1>();
	}
	vec4d wwwz()const{
		return swizzle<3, 3, 3, 2>();
	}
	vec4d wwww()const{
		return swizzle<3, 3, 3, 3>();
	}
};
struct vec8f{
	__m256 data;
	vec8f(float a) : data(_mm256_set1_ps(a)){}
	vec8f(float a, float b, float c, float d, float e, float f, float g, float h) : data(_mm256_set_ps(h,g,f,e,d,c,b,a)){}
	vec8f() : data(){}
	#ifdef NDEBUG
	vec8f(const float* ptr) : data(_mm256_load_ps(ptr)){

	}
	#else
	vec8f(const float* ptr){
		assert((((size_t)ptr) % 32) == 0 && "Pointer not aligned!");
		data = _mm256_load_ps(ptr);
	}
	#endif
	vec8f& operator+=(const vec8f& o){
		data = _mm256_add_ps(data, o.data);
		return *this;
	}
	vec8f operator+(const vec8f& o)const{
		vec8f ret;
		ret.data = _mm256_add_ps(data, o.data);
		return ret;
	}
	vec8f& operator-=(const vec8f& o){
		data = _mm256_sub_ps(data, o.data);
		return *this;
	}
	vec8f operator-(const vec8f& o)const{
		vec8f ret;
		ret.data = _mm256_sub_ps(data, o.data);
		return ret;
	}
	vec8f& operator*=(const vec8f& o){
		data = _mm256_mul_ps(data, o.data);
		return *this;
	}
	vec8f operator*(const vec8f& o)const{
		vec8f ret;
		ret.data = _mm256_mul_ps(data, o.data);
		return ret;
	}
	vec8f& operator/=(const vec8f& o){
		data = _mm256_div_ps(data, o.data);
		return *this;
	}
	vec8f operator/(const vec8f& o)const{
		vec8f ret;
		ret.data = _mm256_div_ps(data, o.data);
		return ret;
	}
	vec8f& fmsa(const vec8f& o, const vec8f& p){
		data = _mm256_fmsub_ps(data, o.data, p.data);
		return *this;
	}
	vec8f fms(const vec8f& o, const vec8f& p)const{
		vec8f ret;
		ret.data = _mm256_fmsub_ps(data, o.data, p.data);
		return ret;
	}
	vec8f& fmaa(const vec8f& o, const vec8f& p){
		data = _mm256_fmadd_ps(data, o.data, p.data);
		return *this;
	}
	vec8f fma(const vec8f& o, const vec8f& p)const{
		vec8f ret;
		ret.data = _mm256_fmadd_ps(data, o.data, p.data);
		return ret;
	}
	operator vec8i()const{
		vec8i ret;
		ret.data = _mm256_cvtps_epi32(_mm256_floor_ps(data));
		return ret;
	}
	template<unsigned a1, unsigned a2 = a1,unsigned a3 = a2, unsigned a4 = a3, unsigned a5 = a4, unsigned a6 = a5, unsigned a7 = a6, unsigned a8 = a7>
	vec8f swizzle()const{
		static_assert(a1 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a2 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a3 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a4 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a5 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a6 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a7 < 8, "Swizzle argument out of range (>= 8)");
		static_assert(a8 < 8, "Swizzle argument out of range (>= 8)");
		IF_CONSTEXPR(a1 < 4 && a2 < 4 && a3 < 4 && a4 < 4 && a5 == a1 + 4 && a6 == a2 + 4 && a7 == a3 + 4 && a8 == a4 + 4){
			int imm8 = a1 | (a2 << 2) | (a3 << 4) | (a4 << 6);
			vec8f ret;
			ret.data = _mm256_permute_ps(data, imm8);
			return ret;
		}
		else{
			__m256i idx = _mm256_set_epi32(a8, a7, a6, a5, a4, a3, a2, a1);
			vec8f ret;
			ret.data = _mm256_permutevar8x32_ps(data, idx);
			return ret;
		}
	}
	vec8f sum()const{
		vec8f ret = *this;
		ret += ret.swizzle<1,0,3,2,5,4,7,6>();
		ret += ret.swizzle<2,3,0,1,6,7,4,5>();
		ret += ret.swizzle<4,5,6,7,0,1,2,3>();
		return ret;
	}
	float operator[](unsigned i)const{
		assert(i < 8);
		return ((float*)&data)[i];
	}
	float& operator[](unsigned i){
		assert(i < 8);
		return ((float*)&data)[i];
	}
	vec8i operator<(const vec8f& o)const{
		vec8i ret;
		ret.data = _mm256_castps_si256(_mm256_cmp_ps(data, o.data, _CMP_LT_OQ));
		return ret;
	}
	vec8i operator>(const vec8f& o)const{
		vec8i ret;
		ret.data = _mm256_castps_si256(_mm256_cmp_ps(data, o.data, _CMP_GT_OQ));
		return ret;
	}
	vec8i operator<=(const vec8f& o)const{
		vec8i ret;
		ret.data = _mm256_castps_si256(_mm256_cmp_ps(data, o.data, _CMP_LE_OQ));
		return ret;
	}
	vec8i operator>=(const vec8f& o)const{
		vec8i ret;
		ret.data = _mm256_castps_si256(_mm256_cmp_ps(data, o.data, _CMP_GE_OQ));
		return ret;
	}
	vec8i operator!=(const vec8f& o)const{
		vec8i ret;
		ret.data = _mm256_castps_si256(_mm256_cmp_ps(data, o.data, _CMP_NEQ_OQ));
		return ret;
	}
	vec8i operator==(const vec8f& o)const{
		vec8i ret;
		ret.data = _mm256_castps_si256(_mm256_cmp_ps(data, o.data, _CMP_EQ_OQ));
		return ret;
	}
	void store(float* db)const{
		assert((((size_t)db) % 32 == 0) && "Store pointer not aligned!");
		_mm256_store_ps(db, data);
	}
	template<typename stream_t>
	friend stream_t& operator<<(stream_t& str, const vec8f& o){
		for(int i = 0;i < 8;i++){
			str << o[i] << (i < 7 ? ", " : "");
		}
		return str;
	}
};