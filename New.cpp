#include "Simple.h"

using Simple::Cstring;
using Simple::Int8;
using Simple::Regex;
using Simple::String;
using Simple::Uint32;
using Simple::Vector;
using Simple::System::BinaryFile;
using Simple::System::Color;
using Simple::System::ConsoleColor;
using Simple::System::Console;
using Simple::System::Exception;
using Simple::Utility::ConsoleMenu;
using Simple::Utility::ConsoleTable;
using Simple::Utility::Message;
using Simple::Utility::Result;
using Simple::Utility::Tools;

const Regex nikEx{ "\\b(2021)([^ ]*)" };
const ConsoleColor CursorColor
{
	Color::Green,
	Color::Black
};
struct DataSiswa
{
	Uint32 NIK;
	Int8 Nama[32];
	Int8 Alamat[64];
	Int8 TanggalLahir[32];
	Int8 TempatLahir[32];
	Int8 Agama[16];
	Int8 JenisKelamin[16];
	Int8 Jurusan[64];
};
class Siswa : public BinaryFile<DataSiswa>
{
public:
	Siswa() :BinaryFile("Data Siswa.bin") {}
	Uint32 GetNik()
	{
		Vector<DataSiswa> data = Read();
		
		if (data.empty()) return 0;
		else return data.back().NIK;
	}
} File;

void Registrasi()
{
	ConsoleMenu mJurusan
	{
		{
			"Seni Industri Kreatif",
			"Agribisnis Agroteknologi",
			"Kesehatan dan Pekerjaan Sosial",
			"Pariwisata",
			"Bisnis Manajemen",
			"Teknologi dan Rekayasa",
			"Kemaritiman",
			"Teknologi Informasi",
			"Energi Pertambangan"
		},
		CursorColor,
		{ 18, 12 },
		true
	};
	ConsoleMenu mJList[]
	{
		// Seni Industri Kreatif
		{
			{
				"Seni Tari",
				"Seni Pedalangan",
				"Seni Teater",
				"Seni Karawitan",
				"Seni Broadcastring dan Film"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Agribisnis Agroteknologi
		{
			{
				"Agribisnis Pengolahan Hasil Pertanian",
				"Teknik Pertanian",
				"Kesehatan Hewan",
				"Kehutanan",
				"Agribisnis Tanaman"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Kesehatan dan Pekerjaan Sosial
		{
			{
				"Pekerjaan Sosial",
				"Kesehatan Gigi",
				"Keperawatan",
				"Farmasi"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Pariwisata
		{
			{
				"Tata Kecantikan",
				"Tata Busana",
				"Kuliner",
				"Perhotelan dan Jasa Pariwisata"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Bisnis Manajemen
		{
			{
				"Akuntansi dan Keuangan",
				"Bisnis dan Pemasaran",
				"Manajemen Perkantoran"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Teknologi dan Rekayasa
		{
			{
				"Teknik Elektronika",
				"Teknik Ketenagalistrikan",
				"Teknik Perkapalan",
				"Teknologi Tekstil",
				"Teknologi Pesawat Udara",
				"Teknik Grafika",
				"Teknik Otomotif",
				"Teknik Mesin",
				"Teknik Konstruksi Properti",
				"Teknik Kimia",
				"Teknik Industri",
				"Instrumental Industri"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Kemaritiman
		{
			{
				"Perikanan",
				"Pengolahan Hasil Perikanan",
				"Pelayaran Kapal Niaga"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Teknologi Informasi
		{
			{
				"Teknik Telekomunikasi",
				"Teknik Komputer Informatika"
			},
			CursorColor,
			{ 49, 12 },
			true
		},

		// Energi Pertambangan
		{
			{
				"Geologi Pertambangan",
				"Teknik Perminyakan"
			},
			CursorColor,
			{ 49, 12 },
			true
		}
	};
	ConsoleMenu mTanggal
	{
		{
			"1"	, "2"	, "3"	, "4"	, "5"	, "6"	, "7"	, "8"	, "9"	, "10",
			"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
			"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
			"31"
		},
		CursorColor,
		{ 18, 8 },
		true
	};
	ConsoleMenu mBulan
	{
		{
			"Januari"		, "Februari"	, "Maret"		, "April",
			"Mei"				, "Juni"			, "Juli"		, "Agustus",
			"September"	, "Oktober"		, "November", "Desember"
		},
		CursorColor,
		{ 21, 8 },
		true
	};
	ConsoleMenu mTahun
	{
		{
			"1971",	"1972",	"1973",	"1974",	"1975",	"1976",	"1977",	"1978",	"1979",	"1980",
			"1981",	"1982",	"1983",	"1984",	"1985",	"1986",	"1987",	"1988",	"1989",	"1990",
			"1991",	"1992",	"1993",	"1994",	"1995",	"1996",	"1997",	"1998",	"1999",	"2000",
			"2001",	"2002",	"2003",	"2004",	"2005",	"2006",	"2007",	"2008",	"2009",	"2010"
		},
		CursorColor,
		{ 31, 8 }
	};
	ConsoleMenu mAgama
	{
		{
			"Islam",
			"Katolik",
			"Protestan",
			"Hindu",
			"Budha",
			"Khonghucu"
		},
		CursorColor,
		{ 18, 10 },
		true
	};
	ConsoleMenu mJk
	{
		{
			"Pria",
			"Wanita"
		},
		CursorColor,
		{ 18, 11 },
		true
	};
	ConsoleMenu mRegistrasi
	{
		{
			"Nama siswa    :",
			"Alamat        :",
			"Tanggal lahir :",
			"Tempat lahir  :",
			"Agama         :",
			"Jenis kelamin :",
			"Jurusan       :",
			"[Registrasi]",
			"[Kembali]"
		},
		CursorColor,
		{2, 6}
	};
	ConsoleMenu::Selection sRegistrasi;
	String nama;
	String alamat;
	String tanggal;
	String tempat;
	String agama;
	String jk;
	String jurusan;

	Console::SetCursorPosition(2, 2); Console::Print("======================");
	Console::SetCursorPosition(2, 3); Console::Print("   REGISTRASI SISWA");
	Console::SetCursorPosition(2, 4); Console::Print("======================");

	do
	{
		Console::SetCursorPosition(18, 6);	Console::Print(nama);
		Console::SetCursorPosition(18, 7);	Console::Print(alamat);
		Console::SetCursorPosition(18, 8);	Console::Print(tanggal);
		Console::SetCursorPosition(18, 9);	Console::Print(tempat);
		Console::SetCursorPosition(18, 10); Console::Print(agama);
		Console::SetCursorPosition(18, 11); Console::Print(jk);
		Console::SetCursorPosition(18, 12); Console::Print(jurusan);
		sRegistrasi = mRegistrasi.Print();

		switch (sRegistrasi.Index)
		{
		case 0:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), nama);
			nama = Console::GetLine();
			break;
		case 1:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), alamat);
			alamat = Console::GetLine();
			break;
		case 2:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), tanggal);
			tanggal += mTanggal.Print(7).Value + " ";
			tanggal += mBulan.Print(7).Value + " ";
			tanggal += mTahun.Print(7).Value;

			mTanggal.Clear();
			mBulan.Clear();
			mTahun.Clear();
			break;
		case 3:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), tempat);
			tempat = Console::GetLine();
			break;
		case 4:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), agama);
			agama = mAgama.Print().Value;
			
			mAgama.Clear();
			break;
		case 5:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), jk);
			jk = mJk.Print().Value;

			mJk.Clear();
			break;
		case 6:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), jurusan);
			
			ConsoleMenu::Selection rJurusan = mJurusan.Print();
			jurusan += rJurusan.Value + ": ";
			jurusan += mJList[rJurusan.Index].Print().Value;

			mJurusan.Clear();
			mJList[rJurusan.Index].Clear();
			break;
		}

		if (sRegistrasi.Value == "[Registrasi]")
		{
			if
			(
				nama.empty() ||
				alamat.empty() ||
				tanggal.empty() ||
				tempat.empty() ||
				agama.empty() ||
				jk.empty() ||
				jurusan.empty()
			) Tools::PrintMessage(2, 16, Message::Warning, "Silakan lengkapi seluruh data");
			else
			{
				DataSiswa siswa;
				Uint32 iNik = File.GetNik();
				String sNik = std::to_string(iNik);

				siswa.NIK = iNik == 0 ? 20211 : std::stoi(sNik.replace(4, -1, std::to_string(std::stoi(sNik.substr(4)) + 1)));
				strcpy_s(siswa.Nama, nama.c_str());
				strcpy_s(siswa.Alamat, alamat.c_str());
				strcpy_s(siswa.TanggalLahir, tanggal.c_str());
				strcpy_s(siswa.TempatLahir, tempat.c_str());
				strcpy_s(siswa.Agama, agama.c_str());
				strcpy_s(siswa.JenisKelamin, jk.c_str());
				strcpy_s(siswa.Jurusan, jurusan.c_str());

				File.Write(siswa);
				Tools::PrintMessage(2, 16, Message::Information, "Registrasi siswa berhasil");
				break;
			}
		}
	} while (sRegistrasi.Value != "[Kembali]");
}
void List()
{
	ConsoleTable tShow
	{
		"No",
		"Nomor Induk Siswa",
		"Nama Siswa",
		"Alamat",
		"Tanggal lahir",
		"Tempat lahir",
		"Agama",
		"Jenis kelamin",
		"Jurusan"
	};
	Vector<DataSiswa> stored = File.Read();

	for (Uint32 i = 0, no = 1; i < stored.size(); i++, no++) tShow +=
	{
		std::to_string(no),
		std::to_string(stored[i].NIK),
		stored[i].Nama,
		stored[i].Alamat,
		stored[i].TanggalLahir,
		stored[i].TempatLahir,
		stored[i].Agama,
		stored[i].JenisKelamin,
		stored[i].Jurusan
	};

	Console::SetCursorPosition(2, 2); Console::Print("==========================");
	Console::SetCursorPosition(2, 3); Console::Print("   SISWA YANG TERDAFTAR");
	Console::SetCursorPosition(2, 4); Console::Print("==========================");
	Console::SetCursorPosition(0, 6); tShow.Print();
}
void Cari()
{
	ConsoleMenu mCari
	{
		{
			"Nama atau NIK Siswa :",
			"[Cari]",
			"[Kembali]"
		},
		CursorColor,
		{ 2, 7 }
	};
	ConsoleMenu::Selection sCari;
	String cari;
	Vector<DataSiswa> data;

	do
	{
		Console::SetCursorPosition(2, 2); Console::Print("=====================");
		Console::SetCursorPosition(2, 3); Console::Print("   CARI DATA SISWA");
		Console::SetCursorPosition(2, 4); Console::Print("=====================");
		Console::SetCursorPosition(2, 5); Console::Print("Masukkan Nama atau NIK Siswa");
		sCari = mCari.Print();

		switch (sCari.Index)
		{
		case 0:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), cari);
			cari = Console::GetLine();
			break;
		}

		if (sCari.Value == "[Cari]")
		{
			Vector<DataSiswa> found;
			ConsoleTable tShow
			{
				"No",
				"Nomor Induk Siswa",
				"Nama Siswa",
				"Alamat",
				"Tanggal lahir",
				"Tempat lahir",
				"Agama",
				"Jenis kelamin",
				"Jurusan"
			};

			if (Tools::IsNumber(cari))
			{
				if (!std::regex_search(cari, nikEx)) Tools::PrintMessage(2, 11, Message::Information, "NIK Siswa salah");
				else
				{
					data = File.Read();
					for (DataSiswa siswa : data)
					{
						if (siswa.NIK == stoi(cari))
						{
							found.push_back(siswa);
							break;
						}
					}
					if (!found.empty())	tShow +=
					{
						"1",
						std::to_string(found[0].NIK),
						found[0].Nama,
						found[0].Alamat,
						found[0].TanggalLahir,
						found[0].TempatLahir,
						found[0].Agama,
						found[0].JenisKelamin,
						found[0].Jurusan
					};
					Console::SetCursorPosition(0, 11); tShow.Print();
				}
			}
			else
			{
				String lowCari = cari;
				String lowData;

				std::transform(lowCari.begin(), lowCari.end(), lowCari.begin(), ::tolower);
				data = File.Read();
				for (DataSiswa siswa : data)
				{
					lowData = siswa.Nama;
					std::transform(lowData.begin(), lowData.end(), lowData.begin(), ::tolower);

					if (lowData.find(lowCari) != -1) found.push_back(siswa);
				}
				for (Uint32 i = 0, no = 1; i < found.size(); i++, no++) tShow +=
				{
					std::to_string(no),
					std::to_string(found[i].NIK),
					found[i].Nama,
					found[i].Alamat,
					found[i].TanggalLahir,
					found[i].TempatLahir,
					found[i].Agama,
					found[i].JenisKelamin,
					found[i].Jurusan
				};
				Console::SetCursorPosition(0, 11); tShow.Print();
			}
		}
	} while (sCari.Value != "[Kembali]");
}
void Update()
{
	ConsoleMenu mJurusan
	{
		{
			"Seni Industri Kreatif",
			"Agribisnis Agroteknologi",
			"Kesehatan dan Pekerjaan Sosial",
			"Pariwisata",
			"Bisnis Manajemen",
			"Teknologi dan Rekayasa",
			"Kemaritiman",
			"Teknologi Informasi",
			"Energi Pertambangan"
		},
		CursorColor,
		{ 18, 13 },
		true
	};
	ConsoleMenu mJList[]
	{
		// Seni Industri Kreatif
		{
			{
				"Seni Tari",
				"Seni Pedalangan",
				"Seni Teater",
				"Seni Karawitan",
				"Seni Broadcastring dan Film"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Agribisnis Agroteknologi
		{
			{
				"Agribisnis Pengolahan Hasil Pertanian",
				"Teknik Pertanian",
				"Kesehatan Hewan",
				"Kehutanan",
				"Agribisnis Tanaman"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Kesehatan dan Pekerjaan Sosial
		{
			{
				"Pekerjaan Sosial",
				"Kesehatan Gigi",
				"Keperawatan",
				"Farmasi"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Pariwisata
		{
			{
				"Tata Kecantikan",
				"Tata Busana",
				"Kuliner",
				"Perhotelan dan Jasa Pariwisata"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Bisnis Manajemen
		{
			{
				"Akuntansi dan Keuangan",
				"Bisnis dan Pemasaran",
				"Manajemen Perkantoran"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Teknologi dan Rekayasa
		{
			{
				"Teknik Elektronika",
				"Teknik Ketenagalistrikan",
				"Teknik Perkapalan",
				"Teknologi Tekstil",
				"Teknologi Pesawat Udara",
				"Teknik Grafika",
				"Teknik Otomotif",
				"Teknik Mesin",
				"Teknik Konstruksi Properti",
				"Teknik Kimia",
				"Teknik Industri",
				"Instrumental Industri"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Kemaritiman
		{
			{
				"Perikanan",
				"Pengolahan Hasil Perikanan",
				"Pelayaran Kapal Niaga"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Teknologi Informasi
		{
			{
				"Teknik Telekomunikasi",
				"Teknik Komputer Informatika"
			},
			CursorColor,
			{ 49, 13 },
			true
		},

		// Energi Pertambangan
		{
			{
				"Geologi Pertambangan",
				"Teknik Perminyakan"
			},
			CursorColor,
			{ 49, 13 },
			true
		}
	};
	ConsoleMenu mTanggal
	{
		{
			"1"	, "2"	, "3"	, "4"	, "5"	, "6"	, "7"	, "8"	, "9"	, "10",
			"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
			"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
			"31"
		},
		CursorColor,
		{ 18, 9 },
		true
	};
	ConsoleMenu mBulan
	{
		{
			"Januari"		, "Februari"	, "Maret"		, "April",
			"Mei"				, "Juni"			, "Juli"		, "Agustus",
			"September"	, "Oktober"		, "November", "Desember"
		},
		CursorColor,
		{ 21, 9 },
		true
	};
	ConsoleMenu mTahun
	{
		{
			"1971",	"1972",	"1973",	"1974",	"1975",	"1976",	"1977",	"1978",	"1979",	"1980",
			"1981",	"1982",	"1983",	"1984",	"1985",	"1986",	"1987",	"1988",	"1989",	"1990",
			"1991",	"1992",	"1993",	"1994",	"1995",	"1996",	"1997",	"1998",	"1999",	"2000",
			"2001",	"2002",	"2003",	"2004",	"2005",	"2006",	"2007",	"2008",	"2009",	"2010"
		},
		CursorColor,
		{ 31, 9 }
	};
	ConsoleMenu mAgama
	{
		{
			"Islam",
			"Katolik",
			"Protestan",
			"Hindu",
			"Budha",
			"Khonghucu"
		},
		CursorColor,
		{ 18, 11 },
		true
	};
	ConsoleMenu mJk
	{
		{
			"Pria",
			"Wanita"
		},
		CursorColor,
		{ 18, 12 },
		true
	};
	ConsoleMenu mCari
	{
		{
			"Nomor Induk Siswa :",
			"[Cari]",
			"[Kembali]"
		},
		CursorColor,
		{ 2, 7 }
	};
	ConsoleMenu::Selection sCari;
	String cari;

	do
	{
		Console::SetCursorPosition(2, 2); Console::Print("=======================");
		Console::SetCursorPosition(2, 3); Console::Print("   UPDATE DATA SISWA");
		Console::SetCursorPosition(2, 4); Console::Print("=======================");
		Console::SetCursorPosition(2, 5); Console::Print("Masukkan NIK Siswa yang akan diupdate");

		sCari = mCari.Print();

		switch (sCari.Index)
		{
		case 0:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), cari);
			cari = Console::GetLine();
			break;
		}

		if (sCari.Value == "[Cari]")
		{
			if (cari.empty()) Tools::PrintMessage(2, 11, Message::Warning, "Silakan masukkan NIK Siswa");
			else if (!Tools::IsNumber(cari)) Tools::PrintMessage(2, 11, Message::Information, "NIK Salah");
			else if (!std::regex_search(cari, nikEx)) Tools::PrintMessage(2, 11, Message::Information, "NIK Salah");
			else
			{
				Vector<DataSiswa> data = File.Read();
				Result<bool, Result<Uint32, DataSiswa>> found = [&data, &cari]() -> Result<bool, Result<Uint32, DataSiswa>>
				{
					for (Uint32 i = 0; i < data.size(); i++)
						if (data[i].NIK == std::stoi(cari)) return{ true, {i, data[i]} };
					return { false, {0, {}} };
				}();

				if (!found.Index) Tools::PrintMessage(2, 11, Message::Information, "Siswa dengan NIK " + cari + " tidak ditemukan");
				else
				{
					ConsoleMenu mUpdate
					{
						{
							"Nama Siswa    :",
							"Alamat        :",
							"Tanggal lahir :",
							"Tempat lahir  :",
							"Agama         :",
							"Jenis kelamin :",
							"Jurusan       :",
							"[Update]",
							"[Kembali]"
						},
						CursorColor,
						{ 2, 7 }
					};
					ConsoleMenu::Selection sUpdate;
					String nik = std::to_string(found.Value.Value.NIK);
					String nama = found.Value.Value.Nama;
					String alamat = found.Value.Value.Alamat;
					String tanggal = found.Value.Value.TanggalLahir;
					String tempat = found.Value.Value.TempatLahir;
					String agama = found.Value.Value.Agama;
					String jk = found.Value.Value.JenisKelamin;
					String jurusan = found.Value.Value.Jurusan;

					Console::Clear();
					Console::SetCursorPosition(2, 2); Console::Print("=======================");
					Console::SetCursorPosition(2, 3); Console::Print("   UPDATE DATA SISWA");
					Console::SetCursorPosition(2, 4); Console::Print("=======================");
					Console::SetCursorPosition(2, 5); Console::Print("NIK Siswa: " + nik + ", Masukkan data baru");

					do
					{
						Console::SetCursorPosition(18, 7);	Console::Print(nama);
						Console::SetCursorPosition(18, 8);	Console::Print(alamat);
						Console::SetCursorPosition(18, 9);	Console::Print(tanggal);
						Console::SetCursorPosition(18, 10); Console::Print(tempat);
						Console::SetCursorPosition(18, 11); Console::Print(agama);
						Console::SetCursorPosition(18, 12); Console::Print(jk);
						Console::SetCursorPosition(18, 13); Console::Print(jurusan);

						sUpdate = mUpdate.Print();

						switch (sUpdate.Index)
						{
						case 0:
							Console::Print(" ");
							Tools::Clear(Console::GetCursorPosition(), nama);
							nama = Console::GetLine();
							break;
						case 1:
							Console::Print(" ");
							Tools::Clear(Console::GetCursorPosition(), alamat);
							alamat = Console::GetLine();
							break;
						case 2:
							Console::Print(" ");
							Tools::Clear(Console::GetCursorPosition(), tanggal);
							tanggal += mTanggal.Print(7).Value + " ";
							tanggal += mBulan.Print(7).Value + " ";
							tanggal += mTahun.Print(7).Value;

							mTanggal.Clear();
							mBulan.Clear();
							mTahun.Clear();
							break;
						case 3:
							Console::Print(" ");
							Tools::Clear(Console::GetCursorPosition(), tempat);
							tempat = Console::GetLine();
							break;
						case 4:
							Console::Print(" ");
							Tools::Clear(Console::GetCursorPosition(), agama);
							agama = mAgama.Print().Value;

							mAgama.Clear();
							break;
						case 5:
							Console::Print(" ");
							Tools::Clear(Console::GetCursorPosition(), jk);
							jk = mJk.Print().Value;

							mJk.Clear();
							break;
						case 6:
							Console::Print(" ");
							Tools::Clear(Console::GetCursorPosition(), jurusan);

							ConsoleMenu::Selection rJurusan = mJurusan.Print();
							jurusan += rJurusan.Value + ": ";
							jurusan += mJList[rJurusan.Index].Print().Value;

							mJurusan.Clear();
							mJList[rJurusan.Index].Clear();
							break;
						}

						if (sUpdate.Value == "[Update]")
						{
							if
								(
									nama.empty() ||
									alamat.empty() ||
									tanggal.empty() ||
									tempat.empty() ||
									agama.empty() ||
									jk.empty() ||
									jurusan.empty()
								) Tools::PrintMessage(2, 17, Message::Warning, "Silakan lengkapi seluruh data");
							else
							{
								strcpy_s(found.Value.Value.Nama, nama.c_str());
								strcpy_s(found.Value.Value.Alamat, alamat.c_str());
								strcpy_s(found.Value.Value.TanggalLahir, tanggal.c_str());
								strcpy_s(found.Value.Value.TempatLahir, tempat.c_str());
								strcpy_s(found.Value.Value.Agama, agama.c_str());
								strcpy_s(found.Value.Value.JenisKelamin, jk.c_str());
								strcpy_s(found.Value.Value.Jurusan, jurusan.c_str());

								File.Update(found.Value.Index, found.Value.Value);
								Tools::PrintMessage(2, 17, Message::Information, "Data Siswa berhasil diupdate");
								break;
							}
						}
					} while (sUpdate.Value != "[Kembali]");
					Console::Clear();
				}
			}
		}
	} while (sCari.Value != "[Kembali]");
}
void Hapus()
{
	ConsoleMenu mCari
	{
		{
			"Nomor Induk Siswa :",
			"[Cari]",
			"[Kembali]"
		},
		CursorColor,
		{ 2, 7 }
	};
	ConsoleMenu::Selection sCari;
	String cari;

	do
	{
		Console::SetCursorPosition(2, 2); Console::Print("======================");
		Console::SetCursorPosition(2, 3); Console::Print("   HAPUS DATA SISWA");
		Console::SetCursorPosition(2, 4); Console::Print("======================");
		Console::SetCursorPosition(2, 5); Console::Print("Masukkan NIK Siswa yang akan dihapus");
		sCari = mCari.Print();

		switch (sCari.Index)
		{
		case 0:
			Console::Print(" ");
			Tools::Clear(Console::GetCursorPosition(), cari);
			cari = Console::GetLine();
			break;
		}

		if (sCari.Value == "[Cari]")
		{
			if (!Tools::IsNumber(cari)) Tools::PrintMessage(2, 11, Message::Information, "NIK salah");
			else if(!std::regex_search(cari, nikEx)) Tools::PrintMessage(2, 11, Message::Information, "NIK salah");
			else
			{
				Vector<DataSiswa> data = File.Read();
				Result<bool, Uint32> found = [&data, &cari]() ->Result<bool, Uint32>
				{
					for (Uint32 i = 0; i < data.size(); i++)
						if (data[i].NIK == std::stoi(cari)) return{ true, i };
					return { false, 0 };
				}();

				if (!found.Index) Tools::PrintMessage(2, 11, Message::Information, "Data Siswa tidak ditemukan");
				else
				{
					Console::SetCursorPosition(2, 11); Console::Print("Nomor Induk Siswa : ", data[found.Value].NIK);
					Console::SetCursorPosition(2, 12); Console::Print("Nama Siswa        : ", data[found.Value].Nama);
					Console::SetCursorPosition(2, 13); Console::Print("Alamat            : ", data[found.Value].Alamat);
					Console::SetCursorPosition(2, 14); Console::Print("Tanggal lahir     : ", data[found.Value].TanggalLahir);
					Console::SetCursorPosition(2, 15); Console::Print("Tempat lahir      : ", data[found.Value].TempatLahir);
					Console::SetCursorPosition(2, 16); Console::Print("Agama             : ", data[found.Value].Agama);
					Console::SetCursorPosition(2, 17); Console::Print("Jenis kelamin     : ", data[found.Value].JenisKelamin);
					Console::SetCursorPosition(2, 18); Console::Print("Jurusan           : ", data[found.Value].Jurusan);

					ConsoleMenu mQuestion
					{
						{
							"[Ya]",
							"[Tidak]"
						},
						CursorColor,
						{ 2, 21 }
					};

					Console::SetCursorPosition(2, 20); Console::Print("Apakah anda yakin?");
					switch (mQuestion.Print().Index)
					{
					case 0:
						File.Delete(found.Value);
						Tools::PrintMessage(2, 24, Message::Information, "Data siswa berhasil dihapus");
						break;
					}
				}
			}
			break;
		}
	} while (sCari.Value != "[Kembali]");
}
int main()
{
	try
	{
		Console::SetSize(100, 30);
		Console::DisableMaximizeButton();
		Console::DisableResize();
		Console::SetPositionToCenter();

		ConsoleMenu mHome
		{
			{
				"1. Registrasi siswa",
				"2. List data siswa",
				"3. Cari data siswa",
				"4. Update data siswa",
				"5. Hapus data siswa",
				"[Keluar]"
			},
			CursorColor,
			{2, 6}
		};
		ConsoleMenu::Selection sHome;

		do
		{
			Console::SetCursorPosition(2, 2); Console::Print("===============");
			Console::SetCursorPosition(2, 3); Console::Print("   LOCALHOST");
			Console::SetCursorPosition(2, 4); Console::Print("===============");
			sHome = mHome.Print();

			switch (sHome.Index)
			{
			case 0:
				Console::Clear();
				Registrasi();
				Console::Clear();
				break;
			case 1:
				Console::Clear();
				List();
				Console::Clear();
				break;
			case 2:
				Console::Clear();
				Cari();
				Console::Clear();
				break;
			case 3:
				Console::Clear();
				Update();
				Console::Clear();
				break;
			case 4:
				Console::Clear();
				Hapus();
				Console::Clear();
				break;
			}
		} while (sHome.Value != "[Keluar]");
	}
	catch (Exception& e)
	{
		Console::Clear();
		Console::Print
		(
			"Program mengalami error!\n",
			"File: "				, e.File()		, "\n",
			"Line: "				, e.Line()		, "\n",
			"Function: "		, e.Function(), "\n",
			"Description: "	, e.Message()	, "\n"
		);
		Console::GetKey();
		return EXIT_FAILURE;
	}
	catch (std::exception& e)
	{
		Console::Clear();
		Console::Print
		(
			"Program mengalami error!\n",
			"Description: ", e.what(), "\n"
		);
		Console::GetKey();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}