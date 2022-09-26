#include <iostream>
#include "fstream"
#include "iostream"
#include "istream"
#include <string>


struct book {
    char* group;
    char* discipline;
    int lesson_num;
    int week_num;
    int week_day;
    std::string lesson_type;
    std::string audience_number;
};


void create_bin_file(std::ifstream& ft, std::ofstream& fb)
{
    book file;
    /*
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
    } */
    ft.get(file.group, 11);
    ft.get(file.discipline, 11);
    ft >> file.lesson_num;
    ft >> file.week_num;
    ft >> file.week_day;
    getline(ft, file.lesson_type);
    getline(ft, file.audience_number);
    fb.write((char*)&file, sizeof(book));
    ft.close();
    fb.close();
}


void out_bin_file(std::ifstream& fb)
{
    book file;
    //чтение из файла всей записи 
    fb.read((char*)&file, sizeof(book));

    std::cout << file.group << std::endl;
    std::cout << file.discipline << std::endl;
    std::cout << file.lesson_num << std::endl;
    std::cout << file.week_num << std::endl;
    std::cout << file.week_day << std::endl;
    std::cout << file.lesson_type << std::endl;
    std::cout << file.audience_number << std::endl;
    
    fb.read((char*)&file, sizeof(book));
    
    if (!fb.good()) {
        std::cout << "Произошла ошибка out_bin_file : !fb.good()" << std::endl;
    }
    fb.close();
}


int main()
{
    setlocale(LC_ALL, "rus");

    //char fnameText[30], fnameBin[30];

    //std::cout << "Name for Text: "; std::cin >> fnameText;
    //std::cout << "Name for Text: "; std::cin >> fnameBin;
    
    //std::ifstream ft(fnameText);
    //std::ofstream fb(fnameBin, std::ios::out | std::ios::binary);

    std::ifstream ft("text.txt");
    std::cout << ft.rdbuf();

    std::ofstream fb("binar.dat", std::ios::out | std::ios::binary);

    if (!ft || !fb)
    {
        std::cout << "файл не открыт";
        return 1;
    }

    std::cout << ft.rdbuf();

    create_bin_file(ft, fb);
    std::ifstream fbb(fnameBin, std::ios::in | std::ios::binary);
    out_bin_file(fbb);
    return 0;
}