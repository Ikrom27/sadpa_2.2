#include "fstream"
#include "iostream"
#include "istream"
#include <string>


struct book {
	std::string group;
	std::string discipline;
	int lesson_num;
	int week_num;
	int week_day;
	std::string lesson_type;
	std::string audience_number;
};


void create_bin_file(std::ifstream& ft, std::ofstream& fb)
{
	book file;
	while (!ft.eof())
	{
		getline(ft, file.group);
		getline(ft, file.discipline);
		ft >> file.lesson_num;
		ft >> file.week_num;
		ft >> file.week_day;
		getline(ft, file.lesson_type);
		getline(ft, file.audience_number);
		fb.write((char*)&file, sizeof(book));
		fb.clear();
	}
	ft.close();
	fb.close();
}


void out_bin_file(std::ifstream& fb)
{
	book file;
	
	fb.read((char*)&file, sizeof(book));
	
	std::cout << file.group << std::endl;
	std::cout << file.discipline << std::endl;
	std::cout << file.lesson_num << std::endl;
	std::cout << file.week_num << std::endl;
	std::cout << file.week_day << std::endl;
	std::cout << file.lesson_type << std::endl;
	std::cout << file.audience_number << std::endl;

	//fb.read((char*)&file, sizeof(book));
}

void add_bin_file(char* fnameBin)
{
	book x;
	std::ofstream fadd(fnameBin, std::ios::in | std::ios::binary | std::ios::app);



	fadd.write((char*)&x, sizeof(book));
	fadd.close();
}
int main()
{
	setlocale(LC_ALL, "rus");

	std::ifstream ft;
	std::ofstream fb;

	//char fnameText[30], fnameBin[30];

	char fnameText[30] = "binar.txt";
	char fnameBin[30] = "binar.dat";
	
	//std::cout << "Name for Text "; std::cin >> fnameText;
	//std::cout << "Name for Text "; std::cin >> fnameBin;
	
	ft.open(fnameText, std::ios::out);
	fb.open(fnameBin, std::ios::out | std::ios::binary);
	std::ifstream fbb(fnameBin, std::ios::in | std::ios::binary);
	if (!ft || !fb)
	{
		std::cout << "файл не открыт";
		return 1;
	}

	int num;

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
		case 1: create_bin_file(ft, fb); break;
		case 2: 
			{
			std::ifstream fbb(fnameBin, std::ios::in | std::ios::binary);
			out_bin_file(fbb); break;
			if (!fb)
			{
				std::cout << "файл не открыт";
				system("pause");
			}
			fb.close();
			}
		case 3: add_bin_file(fnameBin); break;
		case 4: exit(0);
		}

		if(!fbb.good())
		{
			std::cout << "Ошибка ввода" << std::endl;
			return 1;
		}
	}
	return 0;
}