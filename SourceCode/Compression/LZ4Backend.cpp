//
// Created by Вячеслав Кривенко on 16.11.2022.
//
#include "LZ4Backend.h"

VISRCBEG

UInt64 CLZ4Backend::Compress(char *src, char *dst, const UInt64& inputSize) {
	UInt8 *ip = CCast<UInt8*>(src), *anchor = ip, *incompressible = anchor + 0x80, *iend = ip + inputSize, *ilimit = iend - 4;
	UInt8 *op = CCast<UInt8*>(dst), *ref, *orun, *l_end;
	UInt64 len, length;
	UInt32 step = 1;
	UInt8** HashTable = ctx.HashTable;
	memset(HashTable, 0, sizeof(ctx.HashTable)); // TODO: is this really required???
	while (ip < ilimit) {
		ref = HashTable[((Cast<UInt32>(ip) * 0x9E3779B1) >> 0x13)];
		HashTable[((Cast<UInt32>(ip) * 0x9E3779B1) >> 0x13)] = ip;
		if ((ref < ip - 0x0FFFF) || (*(UInt32 *) ref != *(UInt32 *) ip)) {
			if (ip > incompressible) {
				incompressible += 0x80 << (step >> 1);
				step++;
			}
			ip += step;
			continue;
		}
		step = 1;
		while ((ip > anchor) && (ip[-1] == ref[-1])) {
			ip--;
			ref--;
		}
		length = ip - anchor;
		orun = op++;
		if (length >= (int) 0xF) {
			*orun = (0xF << 4);
			len = length - 0xF;
			for (; len > 0x0FE; len -= 0x0FF) *op++ = 0x0FF;
			*op++ = (UInt8) len;
		}
		else *orun = (length << 4);
		l_end = op + length;
		while (op < l_end) {
			Cast<UInt32>(op) = Cast<UInt32>(anchor);
			op += 4;
			anchor += 4;
		}
		op = l_end;
		Cast<UInt16>(op) = (ip - ref);
		op += 2;
		ip += 4;
		ref += 4;
		anchor = ip;
		while (ip < (iend - 3)) {
			if (Cast<UInt32>(ref) == Cast<UInt32>(ip)) {
				ip += 4;
				ref += 4;
				continue;
			}
			if (Cast<UInt16>(ref) == Cast<UInt16>(ip)) {
				ip += 2;
				ref += 2;
			}
			if (*ref == *ip) ip++;
			goto _endCount;
		}
		if ((ip < (iend - 1)) && (Cast<UInt16>(ref) == Cast<UInt16>(ip))) {
			ip += 2;
			ref += 2;
		}
		if ((ip < iend) && (*ref == *ip)) ip++;
_endCount:
		len = (ip - anchor);
		if (len >= (int) 0xF) {
			*orun += 0xF;
			len -= 0xF;
			for (; len > 509; len -= 510) {
				*op++ = 0x0FF;
				*op++ = 0x0FF;
			}
			if (len > 0x0FE) {
				len -= 0x0FF;
				*op++ = 0x0FF;
			}
			*op++ = (UInt8)len;
		}
		else *orun += len;
		anchor = ip;
		incompressible = anchor + 0x80;
	}
	len = length = iend - anchor;
	if (length) {
		orun = op++;
		if (len >= (int) 0xF) {
			*orun = (0xF << 4);
			len -= 0xF;
			for (; len > 0x0FE; len -= 0x0FF) *op++ = 0x0FF;
			*op++ = (UInt8) len;
		}
		else *orun = (len << 4);
		for (; length > 0; length -= 4) {
			*(UInt32 *) op = *(UInt32 *) anchor;
			op += 4;
			anchor += 4;
		}
		op += length;
	}
	return CCast<Int32>(((char *) op) - dst);
}

UInt64 CLZ4Backend::Decompress(char *src, char *dst, const UInt64& outputSize) {
	auto ip = (UInt8 *) src;
	UInt8 *op = (UInt8 *) dst, *olimit = op + outputSize - 4, *ref, *cpy, runcode;
	UInt32 dec[4] = {0, 3, 2, 3};
	UInt64 length;
	while (true) {
		runcode = *ip++;
		if ((length = (runcode >> 4)) == 0xF) {
			for (; *ip == 0x0FF; length += 0x0FF) { ip++; }
			length += *ip++;
		}
		ref = op + length;
		if (ref > olimit) {
			if (ref > olimit + 4) goto _output_error;
			while (op <= olimit) {
				Cast<UInt32>(op) = Cast<UInt32>(ip);
				op += 4;
				ip += 4;
			}
			while (op < ref) *op++ = *ip++;
			break;
		}
		do {
			Cast<UInt32>(op) = Cast<UInt32>(ip);
			op += 4;
			ip += 4;
		}
		while (op < ref);
		ip -= (op - ref);
		op = ref;
		ref -= Cast<UInt16>(ip);
		ip += 2;
		if ((length = (runcode & 0xF)) == 0xF) {
			for (; *ip == 0x0FF; length += 0x0FF) { ip++; }
			length += *ip++;
		}
		length += 4;
		cpy = op + length;
		if (op - ref < 4) {
			*op++ = *ref++;
			*op++ = *ref++;
			*op++ = *ref++;
			*op++ = *ref++;
			ref -= dec[op - ref];
		} else {
			Cast<UInt32>(op) = Cast<UInt32>(ref);
			op += 4;
			ref += 4;
		}
		if (cpy > olimit) {
			if (cpy > olimit + 4) goto _output_error;
			while (op < cpy - 3) {
				Cast<UInt32>(op) = Cast<UInt32>(ref);
				op += 4;
				ref += 4;
			}
			while (op < cpy) *op++ = *ref++;
			if (op >= olimit + 4) break;
			continue;
		}
		do {
			Cast<UInt32>(op) = Cast<UInt32>(ref);
			op += 4;
			ref += 4;
		}
		while (op < cpy);
		op = cpy;
	}
	return CCast<UInt64>(  ((char *) ip) - src);
_output_error:
	return CCast<UInt64>(-(((char *) ip) - src));
}

VISRCEND
