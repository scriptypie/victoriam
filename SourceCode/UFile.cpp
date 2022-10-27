//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <sys/stat.h>

#include <Victoriam/Utils/UFile.hpp>

VISRCBEG

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
	if (!m_Signal)
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
	m_Signal = true;
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
		struct stat st = {};
		struct tm* tm;
		stat(m_Filename.c_str(), &st);
		tm = localtime(&st.st_birthtimespec.tv_sec);
		view.CreateDate.Second = tm->tm_sec;
		view.CreateDate.Minute = tm->tm_min;
		view.CreateDate.Hour   = tm->tm_hour;
		view.CreateDate.Day    = tm->tm_mday;
		view.CreateDate.Month  = tm->tm_mon + 1;
		view.CreateDate.Year   = tm->tm_year + 1900;
		tm = localtime(&st.st_mtimespec.tv_sec);
		view.LastEditDate.Second = tm->tm_sec;
		view.LastEditDate.Minute = tm->tm_min;
		view.LastEditDate.Hour   = tm->tm_hour;
		view.LastEditDate.Day    = tm->tm_mday;
		view.LastEditDate.Month  = tm->tm_mon + 1;
		view.LastEditDate.Year   = tm->tm_year + 1900;
		view.Size = st.st_size;
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
