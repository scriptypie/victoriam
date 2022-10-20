//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <fstream>

#include <Victoriam/Utils/UCryptogen.hpp>

VISRCBEG

#define F(x, y, z)  ((z) ^ ((x) &  ((y) ^ (z))))
#define G(x, y, z)  ((y) ^ ((z) &  ((x) ^ (y))))
#define H(x, y, z)  ((x) ^  (y) ^   (z))
#define I(x, y, z)  ((y) ^ ((x) | ~ (z))       )
#define STEP(f, a, b, c, d, x, t, s) \
                    (a) += f((b), (c), (d)) + (x) + (t); (a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); (a) += (b);

#if defined(__i386__) || defined(__x86_64__) || defined(__vax__)
	#define SET(n) (*(UInt32 *)&ptr[(n) * 4])
    #define GET(n) SET(n)
#else
#define SET(n) \
        (md5_ctx.block[(n)] = \
        (UInt32)ptr[(n) * 4] | \
        ((UInt32)ptr[(n) * 4 + 1] << 8) | \
        ((UInt32)ptr[(n) * 4 + 2] << 16) | \
        ((UInt32)ptr[(n) * 4 + 3] << 24))
#define GET(n) (md5_ctx.block[(n)])
#endif

cCryptogen::cCryptogen(const String &str, const ecHashingAlgorithm &algorithm)
	: m_Buffer(str), m_Algorithm(algorithm)
{}

cCryptogen::cCryptogen(CString dat, const UInt64 &len, const ecHashingAlgorithm &algorithm)
	: m_Buffer(dat, len), m_Algorithm(algorithm)
{}

void cCryptogen::SetInputString(const String &str)
{
	m_Buffer = str;
}

void cCryptogen::SetAlgorithm(const ecHashingAlgorithm &algorithm) {
	m_Algorithm = algorithm;
}

String cCryptogen::ProcessFromString() {
	switch (m_Algorithm)
	{
		case ecHashingAlgorithm::MD5: return GetStringFromStringMD5(m_Buffer);
		default: return "";
	}
}

String cCryptogen::ProcessFromFile() {
	switch (m_Algorithm)
	{
		case ecHashingAlgorithm::MD5: return GetStringFromFileMD5(m_Buffer);
		default: return "";
	}
}

void cCryptogen::CreateMD5Context() {
	md5_ctx = {};
	md5_ctx.a = { 0x67452301 };
	md5_ctx.b = { 0xefcdab89 };
	md5_ctx.c = { 0x98badcfe };
	md5_ctx.d = { 0x10325476 };
}

void cCryptogen::ResetMD5Context() {
	CreateMD5Context();
}

void cCryptogen::UpdateMD5(const void *data, UInt64 size) {
	UInt32 saved_lo;
	unsigned long used, free;

	saved_lo = md5_ctx.lo;
	if ((md5_ctx.lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
		md5_ctx.hi++;
	md5_ctx.hi += size >> 29;
	used = saved_lo & 0x3f;

	if (used){
		free = 64 - used;
		if (size < free) {
			memcpy(&md5_ctx.buffer[used], data, size);
			return;
		}

		memcpy(&md5_ctx.buffer[used], data, free);
		data = (UInt8*)data + free;
		size -= free;
		ProcessMD5(md5_ctx.buffer, 64);
	}

	if (size >= 64) {
		data = ProcessMD5(data, size & ~(unsigned long)0x3f);
		size &= 0x3f;
	}

	memcpy(md5_ctx.buffer, data, size);
}

void cCryptogen::EndMD5(UInt8 *result) {
	unsigned long used, free;
	used = md5_ctx.lo & 0x3f;
	md5_ctx.buffer[used++] = 0x80;
	free = 64 - used;

	if (free < 8) {
		memset(&md5_ctx.buffer[used], 0, free);
		ProcessMD5(md5_ctx.buffer, 64);
		used = 0;
		free = 64;
	}

	memset(&md5_ctx.buffer[used], 0, free - 8);

	md5_ctx.lo <<= 3;
	md5_ctx.buffer[56] = md5_ctx.lo;
	md5_ctx.buffer[57] = md5_ctx.lo >> 8;
	md5_ctx.buffer[58] = md5_ctx.lo >> 16;
	md5_ctx.buffer[59] = md5_ctx.lo >> 24;
	md5_ctx.buffer[60] = md5_ctx.hi;
	md5_ctx.buffer[61] = md5_ctx.hi >> 8;
	md5_ctx.buffer[62] = md5_ctx.hi >> 16;
	md5_ctx.buffer[63] = md5_ctx.hi >> 24;
	ProcessMD5(md5_ctx.buffer, 64);
	result[0] = md5_ctx.a;
	result[1] = md5_ctx.a >> 8;
	result[2] = md5_ctx.a >> 16;
	result[3] = md5_ctx.a >> 24;
	result[4] = md5_ctx.b;
	result[5] = md5_ctx.b >> 8;
	result[6] = md5_ctx.b >> 16;
	result[7] = md5_ctx.b >> 24;
	result[8] = md5_ctx.c;
	result[9] = md5_ctx.c >> 8;
	result[10] = md5_ctx.c >> 16;
	result[11] = md5_ctx.c >> 24;
	result[12] = md5_ctx.d;
	result[13] = md5_ctx.d >> 8;
	result[14] = md5_ctx.d >> 16;
	result[15] = md5_ctx.d >> 24;
	md5_ctx = {};
}

const void *cCryptogen::ProcessMD5(const void *data, UInt64 size) {
	const UInt8 *ptr;
	UInt32 a, b, c, d;
	UInt32 saved_a, saved_b, saved_c, saved_d;

	ptr = (const UInt8*)data;

	a = md5_ctx.a;
	b = md5_ctx.b;
	c = md5_ctx.c;
	d = md5_ctx.d;

	do {
		saved_a = a;
		saved_b = b;
		saved_c = c;
		saved_d = d;

		STEP(F, a, b, c, d, SET(0), 0xd76aa478, 7)
		STEP(F, d, a, b, c, SET(1), 0xe8c7b756, 12)
		STEP(F, c, d, a, b, SET(2), 0x242070db, 17)
		STEP(F, b, c, d, a, SET(3), 0xc1bdceee, 22)
		STEP(F, a, b, c, d, SET(4), 0xf57c0faf, 7)
		STEP(F, d, a, b, c, SET(5), 0x4787c62a, 12)
		STEP(F, c, d, a, b, SET(6), 0xa8304613, 17)
		STEP(F, b, c, d, a, SET(7), 0xfd469501, 22)
		STEP(F, a, b, c, d, SET(8), 0x698098d8, 7)
		STEP(F, d, a, b, c, SET(9), 0x8b44f7af, 12)
		STEP(F, c, d, a, b, SET(10), 0xffff5bb1, 17)
		STEP(F, b, c, d, a, SET(11), 0x895cd7be, 22)
		STEP(F, a, b, c, d, SET(12), 0x6b901122, 7)
		STEP(F, d, a, b, c, SET(13), 0xfd987193, 12)
		STEP(F, c, d, a, b, SET(14), 0xa679438e, 17)
		STEP(F, b, c, d, a, SET(15), 0x49b40821, 22)
		STEP(G, a, b, c, d, GET(1), 0xf61e2562, 5)
		STEP(G, d, a, b, c, GET(6), 0xc040b340, 9)
		STEP(G, c, d, a, b, GET(11), 0x265e5a51, 14)
		STEP(G, b, c, d, a, GET(0), 0xe9b6c7aa, 20)
		STEP(G, a, b, c, d, GET(5), 0xd62f105d, 5)
		STEP(G, d, a, b, c, GET(10), 0x02441453, 9)
		STEP(G, c, d, a, b, GET(15), 0xd8a1e681, 14)
		STEP(G, b, c, d, a, GET(4), 0xe7d3fbc8, 20)
		STEP(G, a, b, c, d, GET(9), 0x21e1cde6, 5)
		STEP(G, d, a, b, c, GET(14), 0xc33707d6, 9)
		STEP(G, c, d, a, b, GET(3), 0xf4d50d87, 14)
		STEP(G, b, c, d, a, GET(8), 0x455a14ed, 20)
		STEP(G, a, b, c, d, GET(13), 0xa9e3e905, 5)
		STEP(G, d, a, b, c, GET(2), 0xfcefa3f8, 9)
		STEP(G, c, d, a, b, GET(7), 0x676f02d9, 14)
		STEP(G, b, c, d, a, GET(12), 0x8d2a4c8a, 20)
		STEP(H, a, b, c, d, GET(5), 0xfffa3942, 4)
		STEP(H, d, a, b, c, GET(8), 0x8771f681, 11)
		STEP(H, c, d, a, b, GET(11), 0x6d9d6122, 16)
		STEP(H, b, c, d, a, GET(14), 0xfde5380c, 23)
		STEP(H, a, b, c, d, GET(1), 0xa4beea44, 4)
		STEP(H, d, a, b, c, GET(4), 0x4bdecfa9, 11)
		STEP(H, c, d, a, b, GET(7), 0xf6bb4b60, 16)
		STEP(H, b, c, d, a, GET(10), 0xbebfbc70, 23)
		STEP(H, a, b, c, d, GET(13), 0x289b7ec6, 4)
		STEP(H, d, a, b, c, GET(0), 0xeaa127fa, 11)
		STEP(H, c, d, a, b, GET(3), 0xd4ef3085, 16)
		STEP(H, b, c, d, a, GET(6), 0x04881d05, 23)
		STEP(H, a, b, c, d, GET(9), 0xd9d4d039, 4)
		STEP(H, d, a, b, c, GET(12), 0xe6db99e5, 11)
		STEP(H, c, d, a, b, GET(15), 0x1fa27cf8, 16)
		STEP(H, b, c, d, a, GET(2), 0xc4ac5665, 23)
		STEP(I, a, b, c, d, GET(0), 0xf4292244, 6)
		STEP(I, d, a, b, c, GET(7), 0x432aff97, 10)
		STEP(I, c, d, a, b, GET(14), 0xab9423a7, 15)
		STEP(I, b, c, d, a, GET(5), 0xfc93a039, 21)
		STEP(I, a, b, c, d, GET(12), 0x655b59c3, 6)
		STEP(I, d, a, b, c, GET(3), 0x8f0ccc92, 10)
		STEP(I, c, d, a, b, GET(10), 0xffeff47d, 15)
		STEP(I, b, c, d, a, GET(1), 0x85845dd1, 21)
		STEP(I, a, b, c, d, GET(8), 0x6fa87e4f, 6)
		STEP(I, d, a, b, c, GET(15), 0xfe2ce6e0, 10)
		STEP(I, c, d, a, b, GET(6), 0xa3014314, 15)
		STEP(I, b, c, d, a, GET(13), 0x4e0811a1, 21)
		STEP(I, a, b, c, d, GET(4), 0xf7537e82, 6)
		STEP(I, d, a, b, c, GET(11), 0xbd3af235, 10)
		STEP(I, c, d, a, b, GET(2), 0x2ad7d2bb, 15)
		STEP(I, b, c, d, a, GET(9), 0xeb86d391, 21)

		a += saved_a;
		b += saved_b;
		c += saved_c;
		d += saved_d;

		ptr += 64;
	} while (size -= 64);

	md5_ctx.a = a;
	md5_ctx.b = b;
	md5_ctx.c = c;
	md5_ctx.d = d;

	return ptr;
}

void cCryptogen::GetBinaryMD5(const void *dat, UInt64 len, UInt8 *out) {
	CreateMD5Context();
	UpdateMD5(dat, len);
	EndMD5(out);
	ResetMD5Context();
}

char cCryptogen::HexByteToHex(UInt8 hb) {
	hb = hb & 0xF;
	return hb < 10 ? '0' + hb : hb - 10 + 'a';
}

String cCryptogen::GetStringFromStringMD5(const void *dat, const UInt64 &len) {
	String result = {};
	UInt8 out[BLOCK_SIZE] = {};
	GetBinaryMD5(dat, len, out);
	for (UInt32 i = 0; i < 16; ++i)
	{
		result.push_back(HexByteToHex(out[i] >> 4));
		result.push_back(HexByteToHex(out[i]));
	}
	return result;
}

String cCryptogen::GetStringFromStringMD5(const String &str) {
	return GetStringFromStringMD5(str.data(), str.size());
}

String cCryptogen::GetStringFromFileMD5(const String &filename) {
	std::fstream file(filename, std::ios::in | std::ios::binary);
	String result = {};
	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		UInt64 size = file.tellg();
		file.seekg(0, std::ios::beg);
		result.resize(size);
		file.read(CCast<char*>(result.data()), result.size());
		result = GetStringFromStringMD5(result);
	}
	return result;
}

VISRCEND
