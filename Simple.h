/* Fahri Synyster 2020
* Penjelasan:
*		Tujuan pembuatan library ini yaitu untuk pembelajaran.
*		Masih terdapat bug atau penggunaan yang tidak tepat pada library ini,
*		jadi berhati-hatilah dalam menggunakannya. Tidak semua kode yang
*		terdapat disini buatan sendiri, namun ada juga yang diambil dari
*		beberapa sumber di internet. Jika ingin menambahkan, mengurangi, atau memodifikasi
*		kode silakan, saya harap dengan kontribusi anda library ini menjadi lebih baik lagi.
* 
* Referensi:
*		https://docs.microsoft.com/en-us/
*		https://en.cppreference.com/w/
*		https://stackoverflow.com/
*		https://www.cplusplus.com/
*		https://www.geeksforgeeks.org/
*		https://github.com/
*		https://www.youtube.com/user/TheChernoProject
*		https://www.quora.com
* 
* Update terakhir:
*		10/12/2020
*			- Perbaikan kode
*		5/12/2020
*			- Perbaikan kode
*		3/12/2020
*			- Perbaikan kode
*		2/12/2020
*			- Perbaikan kode
*		1/12/2020
*			- Perbaikan kode
*		29/11/2020
*			- Perbaikan kode
*		28/11/2020
*			- Library dibuat
* 
* Membutuhkan C++17
* Ditulis di Visual Studio 2019
*/

#pragma once
#ifndef _SIMPLE_H_
#define _SIMPLE_H_

#include <algorithm>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <thread>
#include <time.h>
#include <vector>
#include <Windows.h>

#define NOMINMAX

namespace Simple
{
	using BufferInfo	= CONSOLE_SCREEN_BUFFER_INFO;
	using Cstring			= const char*;
	using Cwstring		= const wchar_t*;
	using Coord				= COORD;
	using CursorInfo	= CONSOLE_CURSOR_INFO;
	using Dword				= DWORD;
	using Fstream			= std::fstream;
	using FontInfo		= CONSOLE_FONT_INFOEX;
	template<typename Type>
	using Greater			= std::greater<Type>;
	using Handle			= HANDLE;
	using Hwnd				= HWND;
	using Ifstream		= std::ifstream;
	template<typename Type>
	using Initializer	= std::initializer_list<Type>;
	using Int8				= char;
	using Int16				= short;
	using Int32				= int;
	using Int64				= long long;
	template<typename Type>
	using Less				= std::less<Type>;
	using Mode				= std::ios;
	using Ofstream		= std::ofstream;
	using Rect				= RECT;
	using Regex				= std::regex;
	using SmallRect = SMALL_RECT;
	using String			= std::string;
	using Sstream			= std::stringstream;
	using Uint8				= unsigned char;
	using Uint16			= unsigned short;
	using Uint32			= unsigned int;
	using Uint64			= unsigned long long;
	template<typename Type>
	using Vector			= std::vector<Type>;
}
namespace Simple::System
{
	enum class Color
	{
		Black				= 0,
		DarkBlue		= 1,
		DarkGreen		= 2,
		DarkCyan		= 3,
		DarkRed			= 4,
		DarkMagenta	= 5,
		DarkYellow	= 6,
		Gray				= 7,
		DarkGray		= 8,
		Blue				= 9,
		Green				= 10,
		Cyan				= 11,
		Red					= 12,
		Magenta			= 13,
		Yellow			= 14,
		White				= 15
	};
}
namespace Simple::System
{
	struct ConsoleColor
	{
		Color Background;
		Color Foreground;
	};
}
namespace Simple::System
{
	class Exception
	{
	private:
		int Line_;
		Cstring File_;
		Cstring Function_;
		Cstring Message_;

	public:
		Exception(Cstring file, int line, Cstring function, Cstring message) :File_(file), Line_(line), Function_(function), Message_(message) {}
		virtual ~Exception() throw() {}
		int Line() const { return Line_; }
		Cstring File() const { return File_; }
		Cstring Function() const { return Function_; }
		Cstring Message() const { return Message_; }
	};

#define Error(value) throw Exception(__FILE__, __LINE__, __FUNCTION__, value)
}
namespace Simple::System
{
	template<typename Type>
	class BinaryFile
	{
	private:
		Cstring FileName_;

	public:
		BinaryFile() :FileName_("BinaryFile.bin")
		{
			Ofstream ofs(FileName_, Mode::app);

			if (!ofs) Error("Gagal membuat file");
			ofs.close();
		}
		BinaryFile(Cstring fileName) :FileName_(fileName)
		{
			Ofstream ofs(FileName_, Mode::app);

			if (!ofs) Error("Gagal membuat file");
			ofs.close();
		}
		void Delete(Uint32 position)
		{
			Vector<Type> stored = Read();
			stored.erase(stored.begin() + position);

			Ofstream ofs(FileName_, Mode::binary);
			if (!ofs) Error("Gagal membuka file");
			for (Type data : stored) ofs.write((Int8*)&data, sizeof(Type));
			ofs.close();
		}
		Vector<Type> Read() const
		{
			Type temp;
			Vector<Type> stored;

			Ifstream ifs(FileName_, Mode::binary);
			if (!ifs) Error("Gagal membuka file");
			while (ifs.read((Int8*)&temp, sizeof(Type))) stored.push_back(temp);
			ifs.close();
			return stored;
		}
		void Update(Uint32 position, Type newData)
		{
			Fstream fs(FileName_, Mode::in | Mode::out | Mode::binary);
			if (!fs) Error("Gagal membuka file");
			fs.seekp(position * sizeof(Type), Mode::beg);
			fs.write((Int8*)&newData, sizeof(Type));
			fs.close();
		}
		void Write(Type value)
		{
			Ofstream ofs(FileName_, Mode::binary | Mode::app);
			if (!ofs) Error("Gagal membuka file");
			ofs.write((Int8*)&value, sizeof(Type));
			ofs.close();
		}
	};
}
namespace Simple::System
{
	class Console final
	{
	public:
		static void Clear()
		{
			system("cls");
		}
		static void CursorVisible(bool visible)
		{
			CursorInfo cursor;
			Handle handle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (!GetConsoleCursorInfo(handle, &cursor)) Error("Gagal mendapatkan informasi cursor");
			cursor.bVisible = visible;
			if (!SetConsoleCursorInfo(handle, &cursor)) Error("Gagal mengatur eksistensi cursor");
		}
		static void DisableCloseButton()
		{
			if (!EnableMenuItem(GetSystemMenu(GetConsoleWindow(), false), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED)) Error("Gagal menonaktifkan tombol close");
		}
		static void DisableMaximizeButton()
		{
			Hwnd hwnd = GetConsoleWindow();

			SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
		}
		static void DisableMinimizeButton()
		{
			Hwnd hwnd = GetConsoleWindow();

			SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
		}
		static void DisableResize()
		{
			Hwnd hwnd = GetConsoleWindow();

			SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX);
		}
		static Int32 Get()
		{
			return std::cin.get();
		}
		static Coord GetBufferSize()
		{
			BufferInfo buffer;

			if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer)) Error("Gagal mendapatkan informasi buffer");
			return buffer.dwSize;
		}
		static ConsoleColor GetColor()
		{
			BufferInfo buffer;
			const std::map<int, Color> color
			{
				{ 0,	Color::Black				},
				{ 1,	Color::DarkBlue			},
				{ 2,	Color::DarkGreen		},
				{ 3,	Color::DarkCyan			},
				{ 4,	Color::DarkRed			},
				{ 5,	Color::DarkMagenta	},
				{ 6,	Color::DarkYellow		},
				{ 7,	Color::Gray					},
				{ 8,	Color::DarkGray			},
				{ 9,	Color::Blue					},
				{ 10,	Color::Green				},
				{ 11,	Color::Cyan					},
				{ 12,	Color::Red					},
				{ 13,	Color::Magenta			},
				{ 14,	Color::Yellow				},
				{ 15,	Color::White				}
			};

			if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer)) Error("Gagal mendapatkan informasi buffer");
			return { color.find(buffer.wAttributes / 16)->second, color.find(buffer.wAttributes % 16)->second };
		}
		static Coord GetCursorPosition()
		{
			BufferInfo buffer;

			if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer)) Error("Gagal mendapatkan informasi buffer");
			return buffer.dwCursorPosition;
		}
		static Int32 GetKey()
		{
			return _getch();
		}
		static String GetLine()
		{
			String result;

			std::getline(std::cin, result);
			return result;
		}
		static void Sleep(Int64 milisecond)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(milisecond));
		}
		template<typename... Type>
		static void Print(Type... value)
		{
			((std::cout << value), ...);
		}
		template<typename... Type>
		static void PrintLine(Type... value)
		{
			((std::cout << value), ...) << "\n";
		}
		static void SetBufferSize(Coord size)
		{
			if (!SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size)) Error("Gagal mengatur ukuran buffer");
		}
		static void SetBufferSize(Int16 width, Int16 height)
		{
			if (!SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { width, height })) Error("Gagal mengatur ukuran buffer");
		}
		static void SetColor(ConsoleColor color)
		{
			if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (Int16)color.Background << 4 | (Int16)color.Foreground)) Error("Gagal mengatur warna console");
		}
		static void SetColor(Color background, Color foreground)
		{
			if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (Int16)background << 4 | (Int16)foreground)) Error("Gagal mengatur warna console");
		}
		static void SetCursorPosition(Coord position)
		{
			if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position)) Error("Gagal mengatur posisi cursor");
		}
		static void SetCursorPosition(Int16 x, Int16 y)
		{
			if (!SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y })) Error("Gagal mengatur posisi cursor");
		}
		static void SetCursorSize(Int16 size)
		{
			if (size < 0 || size>100) Error("Ukuran cursor diluar batas");

			CursorInfo cursor;
			Handle handle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (!GetConsoleCursorInfo(handle, &cursor)) Error("Gagal mendapatkan informasi cursor");
			cursor.dwSize = size;
			if (!SetConsoleCursorInfo(handle, &cursor)) Error("Gagal mengatur ukuran cursor");
		}
		static void SetFont(Cwstring faceName, Int16 fontSize)
		{
			FontInfo font;
			
			font.cbSize				= sizeof(FontInfo);
			font.nFont				= 0;
			font.dwFontSize.X = 0;
			font.dwFontSize.Y = fontSize;
			font.FontFamily		= FF_DONTCARE;
			font.FontWeight		= FW_NORMAL;
			wcscpy_s(font.FaceName, faceName);

			if (!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &font)) Error("Gagal mengatur font");
		}
		static void SetPositionToCenter()
		{
			Rect rScreen;
			Hwnd hScreen = GetDesktopWindow();
			if (!GetWindowRect(hScreen, &rScreen)) Error("Gagal mendapatkan ukuran layar");

			Rect rWindow;
			Hwnd hWindow = GetForegroundWindow();
			if (!GetWindowRect(hWindow, &rWindow)) Error("Gagal mendapatkan ukuran latar depan");

			Int32 width		= rWindow.right - rWindow.left;
			Int32 height	= rWindow.bottom - rWindow.top;
			Int32 x				= ((rScreen.right - rScreen.left) / 2 - width / 2);
			Int32 y				= ((rScreen.bottom - rScreen.top) / 2 - height / 2);

			if (!SetWindowPos(hWindow, 0, x, y, width, height, SWP_SHOWWINDOW || SWP_NOSIZE)) Error("Gagal mengatur posisi console");
		}
		static void SetSize(Coord size)
		{
			Handle handle = GetStdHandle(STD_OUTPUT_HANDLE);

			Coord maxSize = GetLargestConsoleWindowSize(handle);
			if (size.X > maxSize.X) Error("Ukuran lebar diluar batas");
			else if (size.Y > maxSize.Y) Error("Ukuran tinggi diluar batas");

			BufferInfo buffer;
			if (!GetConsoleScreenBufferInfo(handle, &buffer)) Error("Gagal mendapatkan informasi buffer");

			SmallRect wInfo = buffer.srWindow;
			Coord wSize
			{
				wInfo.Right - wInfo.Left + 1,
				wInfo.Bottom - wInfo.Top + 1
			};

			if (wSize.X > size.X || wSize.Y > size.Y)
			{
				SmallRect window
				{
					0,
					0,
					size.X < wSize.X ? size.X - 1 : wSize.X - 1,
					size.Y < wSize.Y ? size.Y - 1 : wSize.Y - 1
				};

				if (!SetConsoleWindowInfo(handle, true, &window)) Error("Gagal mengubah ukuran window");
			}

			SetBufferSize(size);

			SmallRect window
			{
				0,
				0,
				size.X - 1,
				size.Y - 1
			};

			if (!SetConsoleWindowInfo(handle, true, &window)) Error("Gagal mengubah ukuran window");
		}
		static void SetSize(Int16 width, Int16 height)
		{
			Handle handle = GetStdHandle(STD_OUTPUT_HANDLE);

			Coord maxSize = GetLargestConsoleWindowSize(handle);
			if (width > maxSize.X) Error("Ukuran lebar diluar batas");
			else if (height > maxSize.Y) Error("Ukuran tinggi diluar batas");

			BufferInfo buffer;
			if (!GetConsoleScreenBufferInfo(handle, &buffer)) Error("Gagal mendapatkan informasi buffer");

			SmallRect wInfo = buffer.srWindow;
			Coord wSize
			{
				wInfo.Right - wInfo.Left + 1,
				wInfo.Bottom - wInfo.Top + 1
			};

			if (wSize.X > width || wSize.Y > height)
			{
				SmallRect window
				{
					0,
					0,
					width < wSize.X ? width - 1 : wSize.X - 1,
					height < wSize.Y ? height - 1 : wSize.Y - 1
				};

				if (!SetConsoleWindowInfo(handle, true, &window)) Error("Gagal mengubah ukuran window");
			}

			SetBufferSize(width, height);

			SmallRect window
			{
				0,
				0,
				width - 1,
				height - 1
			};

			if (!SetConsoleWindowInfo(handle, true, &window)) Error("Gagal mengubah ukuran window");
		}
	};
}
namespace Simple::System
{
	struct DateTime
	{
		Int32 Second				= 0;
		Int32 Minute				= 0;
		Int32 Hour					= 0;
		Int32 DayOfTheWeek	= 0;
		Int32 DayOfTheMonth	= 0;
		Int32 DayOfTheYear	= 0;
		Int32 Month					= 0;
		Int32 Year					= 0;
		Int32 Dst						= 0;
		String DayShort			= "";
		String DayLong			= "";
		String MonthShort		= "";
		String MonthLong		= "";

		friend std::ostream& operator<<(std::ostream& out, DateTime value)
		{
			out << value.DayOfTheMonth << "/" << value.Month << "/" << value.Year << " ";
			value.Hour		< 10 ? out << 0 << value.Hour		<< ":"	: out << value.Hour		<< ":";
			value.Minute	< 10 ? out << 0 << value.Minute << ":"	: out << value.Minute << ":";
			value.Second	< 10 ? out << 0 << value.Second					: out << value.Second;
			return out;
		}
	};
}
namespace Simple::System
{
	class SystemTime final
	{
	private:
		static const String Days_[];
		static const String Months_[];

	public:
		static DateTime Current()
		{
			time_t now = time(0);
			tm time;
			DateTime res;

			localtime_s(&time, &now);

			res.Second	= time.tm_sec;
			res.Minute	= time.tm_min;
			res.Hour		= time.tm_hour;
			res.Dst			= time.tm_isdst;
			return res;
		}
		static DateTime Now()
		{
			time_t now = time(0);
			tm time;
			DateTime res;

			localtime_s(&time, &now);

			res.Second				= time.tm_sec;
			res.Minute				= time.tm_min;
			res.Hour					= time.tm_hour;
			res.DayOfTheWeek	= time.tm_wday;
			res.DayOfTheMonth	= time.tm_mday;
			res.DayOfTheYear	= time.tm_yday;
			res.Month					= time.tm_mon + 1;
			res.Year					= time.tm_year + 1900;
			res.Dst						= time.tm_isdst;
			res.DayShort			= Days_[time.tm_wday].substr(0, 3);
			res.DayLong				= Days_[time.tm_wday];
			res.MonthShort		= Months_[time.tm_mon].substr(0, 3);
			res.MonthLong			= Months_[time.tm_mon];
			return res;
		}
		static DateTime Today()
		{
			time_t now = time(0);
			tm time;
			DateTime res;

			localtime_s(&time, &now);

			res.DayOfTheWeek	= time.tm_wday;
			res.DayOfTheMonth	= time.tm_mday;
			res.DayOfTheYear	= time.tm_yday;
			res.Month					= time.tm_mon + 1;
			res.Year					= time.tm_year + 1900;
			res.DayShort			= Days_[time.tm_wday].substr(0, 3);
			res.DayLong				= Days_[time.tm_wday];
			res.MonthShort		= Months_[time.tm_mon].substr(0, 3);
			res.MonthLong			= Months_[time.tm_mon];
			return res;
		}
	};

	const String SystemTime::Days_[]
	{
		"Sunday"	, "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday"
	};
	const String SystemTime::Months_[]
	{
		"January"		, "February"	, "March"		, "April",
		"May"				, "June"			, "July"		, "August",
		"September"	, "October"		, "November", "December"
	};
}
namespace Simple::Utility
{
	template<typename Type1, typename Type2>
	struct Result
	{
		Type1 Index;
		Type2 Value;
	};
}
namespace Simple::Utility
{
	enum class Message
	{
		Information = 0,
		Warning			= 1,
		Danger			= 3
	};
}
namespace Simple::Utility
{
	class Cipher final
	{
	public:
		static String XOR(String value, Int8 key)
		{
			String res;

			for (Int8 ch : value) res += ch ^ key;
			return res;
		}
	};
}
namespace Simple::Utility
{
	class Tools final
	{
	private:
		using Color					= System::Color;
		using ConsoleColor	= System::ConsoleColor;
		using Console				= System::Console;
		using Exception			= System::Exception;

	public:
		static void Clear(Coord position, String& value)
		{
			if (!value.empty())
			{
				DeleteText(position, value.length());
				value.clear();
			}
		}
		static void Clear(Int16 x, Int16 y, String& value)
		{
			if (!value.empty())
			{
				DeleteText(x, y, value.length());
				value.clear();
			}
		}
		static void DeleteText(Coord position, Uint32 length)
		{
			Dword ch;
			BufferInfo buffer;
			Handle handle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (!GetConsoleScreenBufferInfo(handle, &buffer)) Error("Gagal mendapatkan informasi buffer");
			if (!FillConsoleOutputCharacter(handle, ' ', length, position, &ch)) Error("Gagal menghapus text");
			if (!GetConsoleScreenBufferInfo(handle, &buffer)) Error("Gagal mendapatkan informasi buffer");
			if (!FillConsoleOutputAttribute(handle, buffer.wAttributes, length, position, &ch)) Error("Gagal mengisi buffer");
		}
		static void DeleteText(Int16 x, Int16 y, Uint32 length)
		{
			Dword ch;
			BufferInfo buffer;
			Handle handle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (!GetConsoleScreenBufferInfo(handle, &buffer)) Error("Gagal mendapatkan informasi buffer");
			if (!FillConsoleOutputCharacter(handle, ' ', length, { x, y }, &ch)) Error("Gagal menghapus text");
			if (!GetConsoleScreenBufferInfo(handle, &buffer)) Error("Gagal mendapatkan informasi buffer");
			if (!FillConsoleOutputAttribute(handle, buffer.wAttributes, length, { x, y }, &ch)) Error("Gagal mengisi buffer");
		}
		static String GenerateRandomKey(Uint32 numberOfKey)
		{
			const Int8 keyList[] = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
			String key;

			srand((Uint32)time(0));
			for (Uint32 i = 0; i < numberOfKey; i++) key += key[rand() % strlen(keyList)];
			return key;
		}
		static String GetPassword()
		{
			String password;
			Int8 ch;

			while ((ch = Console::GetKey()) != '\r')
			{
				switch (ch)
				{
				case 0:
				case 224:
					Console::GetKey();
					break;
				case '\b':
					if (password.size() > 0)
					{
						password.erase(password.end() - 1);
						Console::Print("\b \b");
					}
					break;
				default:
					password += ch;
					Console::Print("*");
				}
			}
			return password;
		}
		static bool IsNumber(String& value)
		{
			return !value.empty() && std::find_if(value.begin(), value.end(), [](Uint8 ch) {return !std::isdigit(ch); }) == value.end();
		}
		template<typename Type>
		static Type Max(Type a, Type b)
		{
			return a > b ? a : b;
		}
		template<typename Type>
		static Type Min(Type a, Type b)
		{
			return a < b ? a : b;
		}
		template<typename... Type>
		static void PrintColor(ConsoleColor color, Type... value)
		{
			ConsoleColor defaultColor = Console::GetColor();

			Console::SetColor(color);
			Console::Print(value...);
			Console::SetColor(defaultColor);
		}
		template<typename... Type>
		static void PrintColor(Color background, Color foreground, Type... value)
		{
			ConsoleColor defaultColor = Console::GetColor();

			Console::SetColor(background, foreground);
			Console::Print(value...);
			Console::SetColor(defaultColor);
		}
		template<typename... Type>
		static void PrintLineColor(ConsoleColor color, Type... value)
		{
			ConsoleColor defaultColor = Console::GetColor();

			Console::SetColor(color);
			Console::PrintLine(value...);
			Console::SetColor(defaultColor);
		}
		template<typename... Type>
		static void PrintLineColor(Color background, Color foreground, Type... value)
		{
			ConsoleColor defaultColor = Console::GetColor();

			Console::SetColor(background, foreground);
			Console::PrintLine(value...);
			Console::SetColor(defaultColor);
		}
		static void PrintMessage(Coord position, Message type, String message)
		{
			String level[]{ "[INFORMATION]", "[WARNING]", "[DANGER]" };

			Console::SetCursorPosition(position);
			switch (type)
			{
			case Message::Information:	PrintColor(Color::Cyan,				Color::Black, level[(Int16)type]); break;
			case Message::Warning:			PrintColor(Color::DarkYellow, Color::Black, level[(Int16)type]); break;
			case Message::Danger:				PrintColor(Color::DarkRed,		Color::Black, level[(Int16)type]); break;
			}
			Console::Print(" ", message);
			Console::GetKey();
			DeleteText(position, level[(Int16)type].length() + message.length() + 1);
		}
		static void PrintMessage(Int16 x, Int16 y, Message type, String message)
		{
			String level[]{ "[INFORMATION]", "[WARNING]", "[DANGER]" };

			Console::SetCursorPosition({ x, y });
			switch (type)
			{
			case Message::Information:	PrintColor(Color::Cyan,				Color::Black, level[(Int16)type]); break;
			case Message::Warning:			PrintColor(Color::DarkYellow, Color::Black, level[(Int16)type]); break;
			case Message::Danger:				PrintColor(Color::DarkRed,		Color::Black, level[(Int16)type]); break;
			}
			Console::Print(" ", message);
			Console::GetKey();
			DeleteText({ x, y }, level[(Int16)type].length() + message.length() + 1);
		}
	};
}
namespace Simple::Utility
{
	class ConsoleMenu final
	{
	private:
		using Color					= System::Color;
		using ConsoleColor	= System::ConsoleColor;
		using Console				= System::Console;

		Vector<String> StoredMenu_;
		Vector<String> Menu_;

		ConsoleColor Color_;

		Uint32	Bind_;
		Uint32	Eind_;
		Uint32	Cind_;
		Int16		Xpos_;
		Int16		Ypos_;
		Int16		Bpos_;
		Int16		Epos_;
		Int16		Cpos_;
		Int16		Limit_;

	public:
		using Selection = Result<Uint32, String>;

		ConsoleMenu(Initializer<String> menu, ConsoleColor cursorColor, Coord position, bool fillSpace = false) :StoredMenu_(menu), Menu_(menu), Color_(cursorColor)
		{
			if (fillSpace)
			{
				Uint32 max = 0;

				for (String data : menu) max = Tools::Max(data.length(), max);
				for (String& data : StoredMenu_) data += String(max - data.length(), ' ');
			}

			Bind_ = 0;
			Eind_ = menu.size() - 1;
			Cind_ = 0;
			Xpos_ = position.X;
			Ypos_ = position.Y;
			Bpos_ = position.Y;
			Epos_ = Ypos_ + Eind_ + 1;
			Cpos_ = position.Y;
		}
		void Clear()
		{
			Int16 y = Ypos_;
			Uint32 index = Bind_;

			for (Uint32 i = 0; i < Limit_; i++, y++, index++)	Tools::DeleteText(Xpos_, y, StoredMenu_[index].length());
		}
		Selection Print()
		{
			Int16 bufferY = Console::GetBufferSize().Y;

			Console::CursorVisible(false);
			if ((Ypos_ + Size()) < bufferY)
			{
				Int16 y = Ypos_;
				Int16 in;

				Limit_ = Size();

				for (Uint32 i = 0; i <= Eind_; i++, y++)
				{
					Console::SetCursorPosition(Xpos_, y); Console::Print(StoredMenu_[i]);
				}

				do
				{
					Console::SetCursorPosition(Xpos_, Cpos_); Tools::PrintColor(Color_, StoredMenu_[Cind_]);
					in = Console::GetKey();
					Console::SetCursorPosition(Xpos_, Cpos_); Console::Print(StoredMenu_[Cind_]);

					switch (in)
					{
					case 80:
						if (Cpos_ != Epos_ && Cind_ < Eind_)
						{
							Cpos_++;
							Cind_++;
						}
						break;
					case 72:
						if (Cpos_ != Bpos_ && Cind_ > Bind_)
						{
							Cpos_--;
							Cind_--;
						}
						break;
					}
				} while (in != 13);
			}
			else
			{
				Int16 limit = bufferY - Ypos_;
				Int16 in;

				Limit_ = limit;
				Epos_ = Ypos_ + limit - 1;

				do
				{
					Int16 y = Ypos_;
					Uint32 index = Bind_;

					for (Uint16 i = 0; i < limit; i++, y++, index++)
					{
						Console::SetCursorPosition(Xpos_, y); Console::Print(StoredMenu_[index]);
					}

					Console::SetCursorPosition(Xpos_, Cpos_); Tools::PrintColor(Color_, StoredMenu_[Cind_]);
					in = Console::GetKey();
					Console::SetCursorPosition(Xpos_, Cpos_); Console::Print(StoredMenu_[Cind_]);

					switch (in)
					{
					case 80:
						if (Cpos_ != Epos_)
						{
							Cpos_++;
							Cind_++;
						}
						else if (Cind_ < Eind_)
						{
							Bind_++;
							Cind_++;
						}
						break;
					case 72:
						if (Cpos_ != Bpos_)
						{
							Cpos_--;
							Cind_--;
						}
						else if (Cind_ > 0)
						{
							Bind_--;
							Cind_--;
						}
						break;
					}
				} while (in != 13);
			}
			Console::CursorVisible(true);
			return { Cind_, Menu_[Cind_] };
		}
		Selection Print(Uint16 limit)
		{
			Limit_ = limit;
			Epos_ = Ypos_ + limit - 1;
			Int16 in;

			Console::CursorVisible(false);
			do
			{
				Int16 y = Ypos_;
				Uint32 index = Bind_;

				for (Uint16 i = 0; i < limit; i++, y++, index++)
				{
					Console::SetCursorPosition(Xpos_, y); Console::Print(StoredMenu_[index]);
				}

				Console::SetCursorPosition(Xpos_, Cpos_); Tools::PrintColor(Color_, StoredMenu_[Cind_]);
				in = Console::GetKey();
				Console::SetCursorPosition(Xpos_, Cpos_); Console::Print(StoredMenu_[Cind_]);

				switch (in)
				{
				case 80:
					if (Cpos_ != Epos_)
					{
						Cpos_++;
						Cind_++;
					}
					else if (Cind_ < Eind_)
					{
						Bind_++;
						Cind_++;
					}
					break;
				case 72:
					if (Cpos_ != Bpos_)
					{
						Cpos_--;
						Cind_--;
					}
					else if (Cind_ > 0)
					{
						Bind_--;
						Cind_--;
					}
					break;
				}

			} while (in != 13);
			Console::CursorVisible(true);
			return { Cind_, Menu_[Cind_] };
		}
		Uint32 Size()
		{
			return StoredMenu_.size();
		}
	};
}
namespace Simple::Utility
{
	enum class TableStyle
	{
		Basic				= 0,
		Line				= 1,
		DoubleLine	= 2,
		Invisible		= 3
	};
}
namespace Simple::Utility
{
	class ConsoleTable final
	{
	private:
		using Console		= System::Console;
		using Exception = System::Exception;
		using Header		= Vector<String>;
		using Row				= Vector<Vector<String>>;
		using Width			= Vector<Uint32>;

		Header	StoredHeader_;
		Row			StoredRow_;
		Width		StoredWidth_;

		struct RowType
		{
			String Left;
			String Intersect;
			String Right;
		};

		struct Border
		{
			String	Horizontal;
			String	Vertical;
			RowType Top;
			RowType Middle;
			RowType Bottom;
		};

		Border Basic_				{ "-", "|", {"+", "+", "+"}, {"+", "+", "+"}, {"+", "+", "+"} };
		Border Line_				{ "━", "┃", {"┏", "┳", "┓"}, {"┣", "╋", "┫"}, {"┗", "┻", "┛"} };
		Border DoubleLine_	{ "═", "║", {"╔", "╦", "╗"}, {"╠", "╬", "╣"}, {"╚", "╩", "╝"} };
		Border Invisible_		{ " ", " ", {" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "} };
		Border Border_ = Basic_;

		String GetHeader(Header header) const
		{
			Sstream line;
			String data;

			line << Border_.Vertical;
			for (Uint32 i = 0; i < StoredHeader_.size(); ++i)
			{
				data = StoredHeader_[i];
				line << String(Padding, ' ') + data + String((StoredWidth_[i] - data.length()), ' ') + String(Padding, ' ');
				line << Border_.Vertical;
			}
			line << "\n";
			return line.str();
		}
		String GetLine(RowType position) const
		{
			Sstream line;

			line << position.Left;
			for (Uint32 i = 0; i < StoredWidth_.size(); ++i)
			{
				for (Uint32 j = 0; j < (StoredWidth_[i] + Padding + Padding); ++j)
				{
					line << Border_.Horizontal;
				}
				line << (i == StoredWidth_.size() - 1 ? position.Right : position.Intersect);
			}
			line << "\n";
			return line.str();
		}
		String GetRow(Row row) const
		{
			Sstream line;
			String data;

			for (auto& dataRow : row)
			{
				line << Border_.Vertical;

				for (Uint32 j = 0; j < dataRow.size(); ++j)
				{
					data = dataRow[j];
					line << String(Padding, ' ') + data + String((StoredWidth_[j] - data.length()), ' ') + String(Padding, ' ');
					line << Border_.Vertical;
				}
				line << "\n";
			}
			return line.str();
		}
		Uint32 GetHeight()
		{
			return StoredRow_.size() + 5;
		}
		Uint32 GetWidth()
		{
			Uint32 size = 2;

			for (Uint32 length : StoredWidth_) size += (length + Padding + Padding + 1);
			return size;
		}

		friend std::ostream& operator<<(std::ostream& out, const ConsoleTable& table)
		{
			return out
				<< table.GetLine(table.Border_.Top)
				<< table.GetHeader(table.StoredHeader_)
				<< table.GetLine(table.Border_.Middle)
				<< table.GetRow(table.StoredRow_)
				<< table.GetLine(table.Border_.Bottom);
		}

	public:
		Uint16 Padding = 1;

		ConsoleTable(Initializer<String> header) :StoredHeader_(header)
		{
			for (const String& data : header) StoredWidth_.push_back(data.length());
		}
		ConsoleTable& operator+=(Initializer<String> row)
		{
			AddRow(row);
			return *this;
		}
		ConsoleTable& operator-=(Uint32 index)
		{
			RemoveRow(index);
			return *this;
		}
		bool AddRow(Initializer<String> row)
		{
			if (row.size() > StoredWidth_.size()) Error("Penambahan baris harus sama dengan header");

			Header res = Vector<String>{ row };

			StoredRow_.push_back(res);
			for (Uint32 i = 0; i < res.size(); ++i) StoredWidth_[i] = Tools::Max(res[i].size(), StoredWidth_[i]);
			return true;
		}
		void Print()
		{
			Coord buffer = Console::GetBufferSize();
			Coord cursor = Console::GetCursorPosition();

			Uint32 width	= GetWidth();
			Uint32 height = GetHeight();

			Console::SetBufferSize
			(
				(Int16)width	> buffer.X ? (Int16)width		: buffer.X,
				(Int16)height > buffer.Y ? (Int16)height	: buffer.Y
			);
			Console::SetCursorPosition(0, cursor.Y);
			Console::Print(*this);
			Console::GetKey();
			Console::Clear();
			Console::SetBufferSize(buffer);
		}
		bool RemoveRow(Uint32 index)
		{
			if (index > StoredRow_.size()) return false;

			StoredRow_.erase(StoredRow_.begin() + index);
			return true;
		}
		void Style(TableStyle style)
		{
			switch (style)
			{
			case TableStyle::Basic:				Border_ = Basic_;				break;
			case TableStyle::Line:				Border_ = Line_;				break;
			case TableStyle::DoubleLine:	Border_ = DoubleLine_;	break;
			case TableStyle::Invisible:		Border_ = Invisible_;		break;
			}
		}
		bool Sort(bool ascending)
		{
			if (ascending) std::sort(StoredRow_.begin(), StoredRow_.end(), Less<Vector<String>>());
			else std::sort(StoredRow_.begin(), StoredRow_.end(), Greater<Vector<String>>());

			return true;
		}
		void UpdateHeader(Uint32 index, String newHeader)
		{
			if (index > StoredHeader_.size()) Error("Index header diluar batas");

			Uint32 length = newHeader.length();
			Uint32 max = StoredWidth_[index];

			StoredHeader_[index] = newHeader;
			StoredWidth_[index] = length > max ? length : max;
		}
		void UpdateRow(Uint32 rowIndex, Uint32 headerIndex, String newRow)
		{
			if (rowIndex > StoredRow_.size()) Error("Index row diluar batas");
			else if (headerIndex > StoredHeader_.size()) Error("Index header diluar batas");

			Uint32 length = newRow.length();
			Uint32 max = StoredWidth_[headerIndex];

			StoredRow_[rowIndex][headerIndex] = newRow;
			StoredWidth_[headerIndex] = length > max ? length : max;
		}
	};
}

#endif // !_SIMPLE_H_