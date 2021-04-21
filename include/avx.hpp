#ifndef AVX_HPP
#define AVX_HPP
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <immintrin.h>
#include <iostream> //Sorry
#if __cplusplus >= 201703L
#define IF_CONSTEXPR if constexpr
#else
#define IF_CONSTEXPR if
#warning If you can -std=c++17 or newer, please do so
#endif
struct vec4i{
	__m256i data;
	vec4i() = default;
	vec4i(__m256i d) : data(d){
		
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
	vec4i& amul_64x32(const vec4i& o){
		data = (o.mul_64x32(*this)).data;
		return *this;
	}
	vec4i mul_64x32(const vec4i& o)const{
		vec4i ret;
		vec4i thisshift(data);
		ret.data = _mm256_mul_epu32(data, o.data);
		thisshift >>= 32;
		thisshift.data = _mm256_mul_epu32(thisshift.data,o.data);
		ret += (thisshift << 32);
		return ret;
	}
	vec4i& operator*=(const vec4i& o){
		data = (o ** this).data;
		return *this;
	}
	vec4i operator*(const vec4i& o)const{
		vec4i ret;
		vec4i oshift(o.data), thisshift(data);
		ret.data = _mm256_mul_epu32(data, o.data);
		oshift >>= 32;
		thisshift >>= 32;
		oshift.data    = _mm256_mul_epu32(oshift.data   ,data  );
		thisshift.data = _mm256_mul_epu32(thisshift.data,o.data);
		ret += (oshift << 32   );
		ret += (thisshift << 32);
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
	vec4i operator==(const vec4i& o)const{
		return vec4i(_mm256_cmpeq_epi64(data, o.data));
	}
	vec4i operator>(const vec4i& o)const{
		return vec4i(_mm256_cmpgt_epi64(data, o.data));
	}
	vec4i operator>=(const vec4i& o)const{
		return operator>(o) | operator==(o);
	}
	vec4i operator<(const vec4i& o)const{
		return ~(operator>(o) | operator==(o));
	}
	vec4i operator<=(const vec4i& o)const{
		return ~operator>(o);
	}
	bool is_zero()const{
		vec4i z(0);
		return (~_mm256_movemask_epi8(_mm256_cmpeq_epi64(data, z.data))) == 0;
	}
	#include "integer_include.inl"
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
	uint64_t operator[](unsigned i)const{
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
	vec8i(__m256i d) : data(d){

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
	vec4d(__m256d d) : data(d){}
	vec4d(int a) : data(_mm256_set1_pd(double(a))){}
	vec4d(float a) : data(_mm256_set1_pd(double(a))){}
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
	vec4d operator-()const{
		return *this ^ vec4d(-0.0f);
		vec4d ret(0);
		ret.data = _mm256_sub_pd(ret.data, data);
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
	vec4d& operator&=(const vec4d& o){
		data = _mm256_and_pd(data, o.data);
		return *this;
	}
	vec4d operator&(const vec4d& o)const{
		vec4d ret;
		ret.data = _mm256_and_pd(data, o.data);
		return ret;
	}
	vec4d& operator|=(const vec4d& o){
		data = _mm256_or_pd(data, o.data);
		return *this;
	}
	vec4d operator|(const vec4d& o)const{
		vec4d ret;
		ret.data = _mm256_or_pd(data, o.data);
		return ret;
	}
	vec4d& operator^=(const vec4d& o){
		data = _mm256_xor_pd(data, o.data);
		return *this;
	}
	vec4d operator^(const vec4d& o)const{
		vec4d ret;
		ret.data = _mm256_xor_pd(data, o.data);
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
	vec4d relu()const{
		vec4d ret;
		vec4d z(0.0f);
		vec4i comp = *this > ret;
		ret.data = _mm256_castsi256_pd((comp & vec4i(_mm256_castpd_si256(data))).data);
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
	void storeu(double* db)const{
		_mm256_storeu_pd(db, data);
	}
	void load(const double* db){
		assert((((size_t)db) % 32 == 0) && "Load pointer not aligned!");
		data = _mm256_load_pd(db);
	}
	void loadu(const double* db){
		data = _mm256_loadu_pd(db);
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
	#include "double_include.inl"
};
struct vec8f{
	__m256 data;
	vec8f(__m256 d) : data(d){}
	vec8f(int a) : data(_mm256_set1_ps(float(a))){}
	vec8f(float a) : data(_mm256_set1_ps(a)){}
	vec8f(double a) : data(_mm256_set1_ps(float(a))){}
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
	vec8f operator-()const{
		return *this ^ vec8f(-0.0f);
		vec8f ret(0);
		ret.data = _mm256_sub_ps(ret.data, data);
		return ret;
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
	vec8f& operator&=(const vec8f& o){
		data = _mm256_and_ps(data, o.data);
		return *this;
	}
	vec8f operator&(const vec8f& o)const{
		vec8f ret;
		ret.data = _mm256_and_ps(data, o.data);
		return ret;
	}
	vec8f& operator|=(const vec8f& o){
		data = _mm256_or_ps(data, o.data);
		return *this;
	}
	vec8f operator|(const vec8f& o)const{
		vec8f ret;
		ret.data = _mm256_or_ps(data, o.data);
		return ret;
	}
	vec8f& operator^=(const vec8f& o){
		data = _mm256_xor_ps(data, o.data);
		return *this;
	}
	vec8f operator^(const vec8f& o)const{
		vec8f ret;
		ret.data = _mm256_xor_ps(data, o.data);
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
	vec8f relu()const{
		vec8f ret;
		vec8f z(0.0f);
		vec8i comp = *this > ret;
		ret.data = _mm256_castsi256_ps((comp & vec8i(_mm256_castps_si256(data))).data);
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
			const int imm8 = a1 | (a2 << 2) | (a3 << 4) | (a4 << 6);
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
	void load(const float* db){
		assert((((size_t)db) % 32 == 0) && "Load pointer not aligned!");
		data = _mm256_load_ps(db);
	}
	void storeu(float* db)const{
		_mm256_storeu_ps(db, data);
	}
	void loadu(const float* db){
		data = _mm256_loadu_ps(db);
	}
	template<typename stream_t>
	friend stream_t& operator<<(stream_t& str, const vec8f& o){
		for(int i = 0;i < 8;i++){
			str << o[i] << (i < 7 ? ", " : "");
		}
		return str;
	}
};
const static vec8f _ps256_0p5(0.5f);
const static vec8f exp_hi(88.3762626647949f);
const static vec8f exp_lo(-88.3762626647949f);
const static vec8f cephes_LOG2EF(1.44269504088896341);
const static vec8f cephes_exp_C1(0.693359375);
const static vec8f cephes_exp_C2(-2.12194440e-4);
const static vec8f cephes_exp_p0(1.9875691500E-4);
const static vec8f cephes_exp_p1(1.3981999507E-3);
const static vec8f cephes_exp_p2(8.3334519073E-3);
const static vec8f cephes_exp_p3(4.1665795894E-2);
const static vec8f cephes_exp_p4(1.6666665459E-1);
const static vec8f cephes_exp_p5(5.0000001201E-1);
inline vec8f exp(vec8f x) {
	vec8f tmp(0.0f), fx;
	vec8i imm0;
	vec8f one(1);
	x.data = _mm256_min_ps(x.data, exp_hi.data);
	x.data = _mm256_max_ps(x.data, exp_lo.data);
	fx = x * cephes_LOG2EF;
	fx = fx + _ps256_0p5;
	tmp.data = _mm256_floor_ps(fx.data);  
	vec8f mask;
	mask.data = (_mm256_cmp_ps(tmp.data, fx.data, _CMP_GT_OQ));    
	mask.data = _mm256_and_ps(mask.data, one.data);
	fx.data = _mm256_sub_ps(tmp.data, mask.data);
	tmp = (fx * cephes_exp_C1);
	vec8f z = (fx * cephes_exp_C2);
	x -= tmp;
	x -= z;
	z = x * x;
	vec8f y = cephes_exp_p0;
	y.fmaa(x, cephes_exp_p1);
	y.fmaa(x, cephes_exp_p2);
	y.fmaa(x, cephes_exp_p3);
	y.fmaa(x, cephes_exp_p4);
	y.fmaa(x, cephes_exp_p5);
	y.fmaa(z, x + one);
	imm0.data = _mm256_cvttps_epi32(fx.data);
	imm0.data = _mm256_add_epi32(imm0.data, vec8i(127).data);
	imm0.data = _mm256_slli_epi32(imm0.data, 23);
	vec8f pow2n;
	pow2n.data = (_mm256_castsi256_ps(imm0.data));
	y *= pow2n;
	return y;
}
vec8f bitcast_to_float(vec8i x){
	vec8f ret;
	ret.data = _mm256_castsi256_ps(x.data);
	return ret;
}
vec4d bitcast_to_float(vec4i x){
	vec4d ret;
	ret.data = _mm256_castsi256_pd(x.data);
	return ret;
}
inline vec4d abs(vec4d x){
	vec4d signbits(-0.0f);
	return vec4d(_mm256_andnot_pd(signbits.data, x.data));
}
inline vec8f abs(vec8f x){
	vec8f signbits(-0.0f);
	return vec8f(_mm256_andnot_ps(signbits.data, x.data));
}
inline vec8f max(vec8f x, vec8f y){
	vec8f ret;
	ret = _mm256_max_ps(x.data, y.data);
	return ret;
}
inline vec8f min(vec8f x, vec8f y){
	vec8f ret;
	ret = _mm256_min_ps(x.data, y.data);
	return ret;
}
inline vec4d max(vec4d x, vec4d y){
	vec4d ret;
	ret = _mm256_max_pd(x.data, y.data);
	return ret;
}
inline vec4d min(vec4d x, vec4d y){
	vec4d ret;
	ret = _mm256_min_pd(x.data, y.data);
	return ret;
}
#endif