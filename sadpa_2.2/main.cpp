#include "fstream"
#include "iostream"
#include "istream"
#include <string>
#include <optional>


struct book {
	char group[20];
	char discipline[30];
	int lesson_num;
	int week_num;
	int week_day;
	char lesson_type[20];
	char audience_number[20];
};


void create_bin_file(std::string fnameText, std::string fnameBin)
{
	book file;

	std::ifstream ft;
	std::ofstream fb;

	ft.open(fnameText, std::ios::out);
	fb.open(fnameBin, std::ios::out | std::ios::binary);

	if (!ft || !fb)
	{
		std::cout << "файл не открыт";
		return;
	}

	while (!ft.eof()) {		
		ft.getline(file.group, sizeof(file.group));
		ft.getline(file.discipline, sizeof(file.discipline));
		ft >> file.lesson_num;
		ft >> file.week_num;
		ft >> file.week_day;
		ft.get();
		ft.getline(file.lesson_type, sizeof(file.lesson_type));
		ft.getline(file.audience_number, sizeof(file.lesson_type));
		fb.write((char*)&file, sizeof(book));
		fb.clear();
	}

	ft.close();
	fb.close();
}


void out_bin_file(std::string fnameBin)
{

	book file;

	std::ifstream fb;
	fb.open(fnameBin, std::ios::out | std::ios::binary);

	if (!fb)
	{
		std::cout << "файл не открыт";
		return;
	}

	fb.read((char*)&file, sizeof(book));
	while (!fb.eof()) {
		std::cout << file.group << std::endl;
		std::cout << file.discipline << std::endl;
		std::cout << file.lesson_num << std::endl;
		std::cout << file.week_num << std::endl;
		std::cout << file.week_day << std::endl;
		std::cout << file.lesson_type << std::endl;
		std::cout << file.audience_number << std::endl;
		fb.read((char*)&file, sizeof(book));
	}
	
	fb.clear();
	fb.close();
}


void out_bin_file_by_key(std::string fnameBin)
{
	book file;
	std::ifstream fb;
	int key = 1;
	int note_num;

	std::cout << "Print note number: "; std::cin >> note_num;

	fb.open(fnameBin, std::ios::out | std::ios::binary);
	if (!fb)
	{
		std::cout << "файл не открыт";
		return;
	}
	fb.read((char*)&file, sizeof(book));

	while (!fb.eof()) {
		if (key == note_num) {
			std::cout << file.group << std::endl;
			std::cout << file.discipline << std::endl;
			std::cout << file.lesson_num << std::endl;
			std::cout << file.week_num << std::endl;
			std::cout << file.week_day << std::endl;
			std::cout << file.lesson_type << std::endl;
			std::cout << file.audience_number << std::endl;
			return;
		}
		key += 1;
		fb.read((char*)&file, sizeof(book));
	}

	std::cout << "Введено неверное значение";

	fb.clear();
	fb.close();
	return;
}


void delete_note_by_key(std::string bin_path, int key)
{
	std::fstream fs(bin_path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);

	book last_record;

	fs.seekg(-static_cast<int>(sizeof(book)), std::ios_base::end);
	if (fs.tellg() != -1)
	{
		fs.read(reinterpret_cast<char*>(&last_record), sizeof(book));
	}
	else
	{
		throw std::runtime_error("No information in file");
	}
	fs.seekg(0);

	book card_buffer;
	int current_position = 0;
	while (true)
	{
		current_position = fs.tellg();
		fs.read(reinterpret_cast<char*>(&card_buffer), sizeof(book));
		if (card_buffer.key == key)
		{
			fs.seekg(current_position);
			fs.write(reinterpret_cast<char*>(&last_record), sizeof(book));

			fs.close();

			return;
		}
		if (fs.eof())
		{
			fs.close();
			throw std::runtime_error("Can't find record with such key");
		}
	}
}



int main()
{
	setlocale(LC_ALL, "rus");

	//char fnameText[30], fnameBin[30];

	char fnameText[30] = "binar.txt";
	char fnameBin[30] = "binar.dat";
	
	//std::cout << "Name for Text "; std::cin >> fnameText;
	//std::cout << "Name for Text "; std::cin >> fnameBin;


	int num;
	int key;

	while (1)
	{
		std::cout << " Operation for files" << std::endl;
		std::cout << " 1. Create for TextFile inBinFile" << std::endl;
		std::cout << " 2. OUT for BinFile" << std::endl;
		std::cout << " 3. Add record in BinFile" << std::endl;
		std::cout << " 4. EXIT" << std::endl;
		std::cout << "numPunkt= "; std::cin >> num;

		switch (num)
		{
		case 1: create_bin_file(fnameText, fnameBin); break;
		case 2: 
			{
			out_bin_file(fnameBin);
			break;
			}
		case 3:
			out_bin_file_by_key(fnameBin);
			break;
		case 4: 
			delete_note_by_key(fnameBin, 2);
			break;
		}
	}
	return 0;
}