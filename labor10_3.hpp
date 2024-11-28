#ifndef NOTES_HPP
#define NOTES_HPP

#include <string>

struct Note {
    std::string lastName;
    std::string firstName;
    std::string phoneNumber;
    int birthday[3]; // [0] - день, [1] - місяць, [2] - рік
};

// Порівняння за датою народження
bool compareByBirthday(const Note& a, const Note& b);

// Введення даних
void inputNotes(Note* notes, int count);

// Сортування за датою народження
void sortNotes(Note* notes, int count);

// Пошук людини за номером телефону
void findByPhone(Note* notes, int count, const std::string& phoneNumber);

// Збереження даних у файл
void saveToFile(Note* notes, int count, const std::string& fileName);

// Завантаження даних з файлу
void loadFromFile(Note*& notes, int& count, const std::string& fileName);

// Форматований вивід масиву структур
void printNotes(Note* notes, int count);

#endif // NOTES_HPP
