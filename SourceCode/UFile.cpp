//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <sys/stat.h>

#include "Victoriam/IO/IOFile.hpp"

VISRCBEG

namespace {

	inline SFileTimestamp GetFileBirthday(const String &filename) {
		struct stat st = {};
		struct tm *tm;
		stat(filename.c_str(), &st);
		tm = localtime(&st.st_birthtimespec.tv_sec);
		SFileTimestamp Date = {};
		Date.Second = tm->tm_sec;
		Date.Minute = tm->tm_min;
		Date.Hour = tm->tm_hour;
		Date.Day = tm->tm_mday;
		Date.Month = tm->tm_mon + 1;
		Date.Year = tm->tm_year + 1900;
		return Date;
	}

	inline UInt64 GetFileSize(const String &filename) {
		struct stat st = {};
		stat(filename.c_str(), &st);
		return st.st_size;
	}

	inline SFileTimestamp GetFileLastModify(const String &filename) {
		struct stat st = {};
		struct tm *tm;
		stat(filename.c_str(), &st);
		tm = localtime(&st.st_mtimespec.tv_sec);
		SFileTimestamp Date = {};
		Date.Second = tm->tm_sec;
		Date.Minute = tm->tm_min;
		Date.Hour = tm->tm_hour;
		Date.Day = tm->tm_mday;
		Date.Month = tm->tm_mon + 1;
		Date.Year = tm->tm_year + 1900;
		return Date;
	}

}

CFile::CFile(const String& filename, const ECOpenMode& omode, const ECFileFormat& fformat)
	: m_Filename(filename)
{
	Open(filename, omode, fformat);
}

CFile::CFile(const char* filename, const ECOpenMode& omode, const ECFileFormat& fformat)
		: m_Filename(filename)
{
	Open(filename, omode, fformat);
}

CFile::~CFile()
{
	if (!m_Empty)
		Release();
}

void CFile::Close()
{
	Release();
}

void CFile::Clear()
{
	m_Handle.clear();
}

void CFile::Release()
{
	m_Handle.close();
	m_Filename.clear();
	m_Empty = true;
}

bool CFile::Valid() const
{
	return m_Handle.is_open();
}

UInt32 CFile::ToStandardOpenMode(const ECOpenMode& omode)
{
	return CCast<UInt32>(omode);
}

UInt32 CFile::ToStandardFormat(const ECFileFormat& format)
{
	return CCast<UInt32>(format);
}

SFileView CFile::View()
{
	SFileView view = {};
	if (Valid())
	{
		view.CreateDate = GetFileBirthday(m_Filename);
		view.LastEditDate = GetFileLastModify(m_Filename);
		view.Size = GetFileSize(m_Filename);
		m_Handle.read(view.FirstFourBytes, 4);
		m_Handle.seekg(0, std::ios::beg);
	}
	return view;
}

void CFile::Open(const String& filename, const ECOpenMode& omode, const ECFileFormat& fformat)
{
	m_Handle.open(filename, ToStandardOpenMode(omode) | ToStandardFormat(fformat));
}

void CFile::Open(const char* filename, const ECOpenMode& omode, const ECFileFormat& fformat)
{
	m_Handle.open(filename, ToStandardOpenMode(omode) | ToStandardFormat(fformat));
}

ECFileResult CFile::Read(char *outdata, size_t sizedata)
{
	if (!Valid())
		return ECFileResult::FileNotFound;

	m_Handle.read(outdata, CCast<long>(sizedata));
	Clear();

	return ECFileResult::Ok;
}

	ECFileResult CFile::Read(String& output)
{
	if (!Valid())
		return ECFileResult::FileNotFound;

	SFileView view = View();
	output.resize(view.Size);
	m_Handle.read(CCast<char*>(output.data()), CCast<long>(output.size()));
	Clear();

	return ECFileResult::Ok;
}

ECFileResult CFile::Write(const String& data)
{
	if (data.empty())
		return ECFileResult::NullInput;

	m_Handle.write(data.data(), CCast<long>(data.size()));
	Clear();

	return ECFileResult::Ok;
}

ECFileResult CFile::Write(const char* data, const UInt64& size)
{
	if (!size || !data)
		return ECFileResult::NullInput;

	m_Handle.write(data, CCast<long>(size));
	Clear();

	return ECFileResult::Ok;
}

VISRCEND
