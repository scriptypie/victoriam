//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#ifndef VICTORIAM_UCRYPTOGEN_HPP
#define VICTORIAM_UCRYPTOGEN_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

enum class ecHashingAlgorithm : UInt32
{
	None VIDECL = 0x00000000,
	MD5  VIDECL = 0x0000000f,
};

class VIDECL cCryptogen
{
	VIDECL ecHashingAlgorithm  m_Algorithm     = { ecHashingAlgorithm::None };
	VIDECL String              m_Buffer        = {};

	VIDECL inline static constexpr UInt32  BUFFER_SIZE     = 0x40;
	VIDECL inline static constexpr UInt32  BLOCK_SIZE      = 0x10;

	struct VIDECL sMD5ALGCTX
	{
		VIDECL UInt32 lo, hi;
		VIDECL UInt32 a, b, c, d;
		VIDECL UInt8  buffer[BUFFER_SIZE] = {};
		VIDECL UInt32 block [BLOCK_SIZE]  = {};
	} md5_ctx = {};

public:
	inline cCryptogen() = default;
	inline ~cCryptogen() = default;

	VIDECL cCryptogen(const String& str, const ecHashingAlgorithm& algorithm);
	VIDECL cCryptogen(CString dat, const UInt64& len, const ecHashingAlgorithm& algorithm);

	VIDECL void SetInputString(const String& str);
	VIDECL void SetAlgorithm(const ecHashingAlgorithm& algorithm);

	VIDECL String ProcessFromString();
	VIDECL String ProcessFromFile();

private:
	VIDECL void CreateMD5Context();
	VIDECL void ResetMD5Context();
	VIDECL void UpdateMD5(const void* data, UInt64 size);
	VIDECL void EndMD5(UInt8* result);
	VIDECL const void* ProcessMD5(const void* data, UInt64 size);
	VIDECL void GetBinaryMD5(const void* dat, UInt64 len, UInt8 out[BLOCK_SIZE]);
	VIDECL VIREQOUT char HexByteToHex(UInt8 hb);
	VIDECL VIREQOUT String GetStringFromStringMD5(const void* dat, const UInt64& len);
	VIDECL VIREQOUT String GetStringFromStringMD5(const String& str);
	VIDECL VIREQOUT String GetStringFromFileMD5(const String& filename);
};

VISRCEND

#endif //VICTORIAM_UCRYPTOGEN_HPP
