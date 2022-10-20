//
// Created by Вячеслав Кривенко on 19.10.2022.
//

#include <sys/stat.h>

#include <Victoriam/Utils/UFile.hpp>

VISRCBEG

cFile::cFile(const String& filename, const ecOpenMode& omode, const ecFileFormat& fformat)
		: m_Filename(filename)
{
	Open(filename, omode, fformat);
}

cFile::cFile(const char* filename, const ecOpenMode& omode, const ecFileFormat& fformat)
		: m_Filename(filename)
{
	Open(filename, omode, fformat);
}

cFile::~cFile()
{
	if (!m_Signal)
		Release();
}

void cFile::Close()
{
	Release();
}

void cFile::Clear()
{
	m_Handle.clear();
}

void cFile::Release()
{
	m_Handle.close();
	m_Filename.clear();
	m_Signal = true;
}

bool cFile::Valid() const
{
	return m_Handle.is_open();
}

UInt32 cFile::ToStandardOpenMode(const ecOpenMode& omode)
{
	return CCast<UInt32>(omode);
}

UInt32 cFile::ToStandardFormat(const ecFileFormat& format)
{
	return CCast<UInt32>(format);
}

sFileView cFile::View()
{
	sFileView view = {};
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

void cFile::Open(const String& filename, const ecOpenMode& omode, const ecFileFormat& fformat)
{
	m_Handle.open(filename, ToStandardOpenMode(omode) | ToStandardFormat(fformat));
}

void cFile::Open(const char* filename, const ecOpenMode& omode, const ecFileFormat& fformat)
{
	m_Handle.open(filename, ToStandardOpenMode(omode) | ToStandardFormat(fformat));
}


ecFileResult cFile::Read(String& output)
{
	if (!Valid())
		return ecFileResult::FileNotFound;

	sFileView view = View();
	output.resize(view.Size);
	m_Handle.read(CCast<char*>(output.data()), CCast<long>(output.size()));
	Clear();

	return ecFileResult::Ok;
}

ecFileResult cFile::Write(const String& data)
{
	if (data.empty())
		return ecFileResult::NullInput;

	m_Handle.write(data.data(), CCast<long>(data.size()));
	Clear();

	return ecFileResult::Ok;
}

ecFileResult cFile::Write(const char* data, const UInt64& size)
{
	if (!size || !data)
		return ecFileResult::NullInput;

	m_Handle.write(data, CCast<long>(size));
	Clear();

	return ecFileResult::Ok;
}

VISRCEND
