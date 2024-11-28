#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Структура Note
struct Note {
    string lastName;
    string firstName;
    string phoneNumber;
    int birthday[3]; // [0] - день, [1] - місяць, [2] - рік
};

// Функція для порівняння дат народження
bool compareByBirthday(const Note& a, const Note& b) {
    if (a.birthday[2] != b.birthday[2])
        return a.birthday[2] < b.birthday[2];
    if (a.birthday[1] != b.birthday[1])
        return a.birthday[1] < b.birthday[1];
    return a.birthday[0] < b.birthday[0];
}

// Функція для сортування за датою народження
void sortNotes(Note* notes, int count) {
    sort(notes, notes + count, compareByBirthday);
}

// Функція для пошуку людини за номером телефону
void findByPhone(Note* notes, int count, const string& phoneNumber) {
    for (int i = 0; i < count; ++i) {
        if (notes[i].phoneNumber == phoneNumber) {
            cout << "Знайдено людину:\n";
            cout << "Прізвище: " << notes[i].lastName << "\n";
            cout << "Ім'я: " << notes[i].firstName << "\n";
            cout << "Дата народження: "
                 << notes[i].birthday[0] << "."
                 << notes[i].birthday[1] << "."
                 << notes[i].birthday[2] << "\n";
            return;
        }
    }
    cout << "Людину з таким номером телефону не знайдено.\n";
}

// Функція для збереження даних у файл
void saveToFile(Note* notes, int count, const string& fileName) {
    ofstream outFile(fileName);
    if (!outFile) {
        cout << "Не вдалося відкрити файл для запису.\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        outFile << notes[i].lastName << " "
                << notes[i].firstName << " "
                << notes[i].phoneNumber << " "
                << notes[i].birthday[0] << " "
                << notes[i].birthday[1] << " "
                << notes[i].birthday[2] << "\n";
    }
    outFile.close();
}

// Функція для зчитування даних з файлу
void loadFromFile(Note*& notes, int& count, const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Не вдалося відкрити файл для читання.\n";
        return;
    }

    // Рахуємо кількість рядків у файлі
    count = 0;
    string line;
    while (getline(inFile, line)) {
        count++;
    }

    // Повертаємося до початку файлу
    inFile.clear();
    inFile.seekg(0);

    // Виділяємо пам'ять і зчитуємо дані
    notes = new Note[count];
    for (int i = 0; i < count; ++i) {
        inFile >> notes[i].lastName >> notes[i].firstName
               >> notes[i].phoneNumber
               >> notes[i].birthday[0] >> notes[i].birthday[1] >> notes[i].birthday[2];
    }
    inFile.close();
}

// Тест для функції сортування за датою народження
TEST(SortNotesTest, CorrectOrder) {
    Note notes[3] = {
        {"Ivanov", "Ivan", "123456789", {15, 5, 1995}},
        {"Petrov", "Petr", "987654321", {20, 12, 1990}},
        {"Sidorov", "Sidr", "555555555", {5, 1, 2000}}
    };
    
    sortNotes(notes, 3);
    
    EXPECT_EQ(notes[0].lastName, "Petrov");
    EXPECT_EQ(notes[1].lastName, "Ivanov");
    EXPECT_EQ(notes[2].lastName, "Sidorov");
}

// Тест для функції пошуку за номером телефону
TEST(FindByPhoneTest, PhoneNumberFound) {
    Note notes[2] = {
        {"Ivanov", "Ivan", "123456789", {15, 5, 1995}},
        {"Petrov", "Petr", "987654321", {20, 12, 1990}}
    };
    
    testing::internal::CaptureStdout();
    findByPhone(notes, 2, "987654321");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Petrov"), std::string::npos);
}

TEST(FindByPhoneTest, PhoneNumberNotFound) {
    Note notes[2] = {
        {"Ivanov", "Ivan", "123456789", {15, 5, 1995}},
        {"Petrov", "Petr", "987654321", {20, 12, 1990}}
    };
    
    testing::internal::CaptureStdout();
    findByPhone(notes, 2, "555555555");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Людину з таким номером телефону не знайдено"), std::string::npos);
}

// Тест для збереження та завантаження даних
TEST(FileIOTest, SaveAndLoad) {
    Note notesToSave[2] = {
        {"Ivanov", "Ivan", "123456789", {15, 5, 1995}},
        {"Petrov", "Petr", "987654321", {20, 12, 1990}}
    };
    
    const std::string testFileName = "test_notes.txt";
    
    // Зберігаємо дані у файл
    saveToFile(notesToSave, 2, testFileName);
    
    // Завантажуємо дані з файлу
    Note* notesLoaded = nullptr;
    int count = 0;
    loadFromFile(notesLoaded, count, testFileName);
    
    ASSERT_EQ(count, 2);
    EXPECT_EQ(notesLoaded[0].lastName, "Ivanov");
    EXPECT_EQ(notesLoaded[1].lastName, "Petrov");
    
    // Очищення
    delete[] notesLoaded;
    std::remove(testFileName.c_str());
}

