#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

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

// Функція для введення даних
void inputNotes(Note* notes, int count) {
    for (int i = 0; i < count; ++i) {
        cout << "Введіть дані для запису " << i + 1 << ":\n";
        cout << "Прізвище: ";
        cin >> notes[i].lastName;
        cout << "Ім'я: ";
        cin >> notes[i].firstName;
        cout << "Номер телефону: ";
        cin >> notes[i].phoneNumber;
        cout << "Дата народження (день, місяць, рік через пробіл): ";
        cin >> notes[i].birthday[0] >> notes[i].birthday[1] >> notes[i].birthday[2];
    }
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
    cout << "Дані збережено у файл " << fileName << ".\n";
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
    cout << "Дані з файлу " << fileName << " успішно завантажено.\n";
}

// Функція для форматованого виводу масиву структур
void printNotes(Note* notes, int count) {
    cout << "=====================================================================================\n";
    cout << "| №  | Прізвище       | Ім'я           | Номер телефону    | Дата народження      |\n";
    cout << "-------------------------------------------------------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(14) << left << notes[i].lastName;
        cout << "| " << setw(14) << left << notes[i].firstName;
        cout << "| " << setw(17) << left << notes[i].phoneNumber;
        cout << "| " << setw(2)  << notes[i].birthday[0] << "." 
             << setw(2)  << notes[i].birthday[1] << "."
             << setw(4) << notes[i].birthday[2] << "       |\n";
    }

    cout << "=====================================================================================\n";
}

// Головне меню програми
void menu() {
    Note* notes = nullptr;
    int count = 0;
    bool running = true;

    while (running) {
        cout << "\nМеню:\n";
        cout << "1. Ввести дані\n";
        cout << "2. Відсортувати дані за датою народження\n";
        cout << "3. Знайти людину за номером телефону\n";
        cout << "4. Зберегти дані у файл\n";
        cout << "5. Завантажити дані з файлу\n";
        cout << "6. Вивести дані у вигляді таблиці\n";
        cout << "7. Вийти\n";
        cout << "Ваш вибір: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Введіть кількість записів: ";
                cin >> count;
                if (count > 0) {
                    delete[] notes; // Видаляємо попередні дані
                    notes = new Note[count];
                    inputNotes(notes, count);
                } else {
                    cout << "Кількість записів має бути більше 0.\n";
                }
                break;
            }
            case 2:
                if (notes) {
                    sortNotes(notes, count);
                    cout << "Дані відсортовано.\n";
                } else {
                    cout << "Немає даних для сортування.\n";
                }
                break;
            case 3: {
                if (notes) {
                    string phoneNumber;
                    cout << "Введіть номер телефону для пошуку: ";
                    cin >> phoneNumber;
                    findByPhone(notes, count, phoneNumber);
                } else {
                    cout << "Немає даних для пошуку.\n";
                }
                break;
            }
            case 4: {
                if (notes) {
                    string fileName;
                    cout << "Введіть ім'я файлу для збереження: ";
                    cin >> fileName;
                    saveToFile(notes, count, fileName);
                } else {
                    cout << "Немає даних для збереження.\n";
                }
                break;
            }
            case 5: {
                string fileName;
                cout << "Введіть ім'я файлу для завантаження: ";
                cin >> fileName;
                loadFromFile(notes, count, fileName);
                break;
            }
            case 6:
                if (notes) {
                    printNotes(notes, count);
                } else {
                    cout << "Немає даних для виводу.\n";
                }
                break;
            case 7:
                running = false;
                break;
            default:
                cout << "Неправильний вибір. Спробуйте ще раз.\n";
                break;
        }
    }

    delete[] notes; // Звільняємо пам'ять перед виходом
}

int main() {
    menu();
    return 0;
}