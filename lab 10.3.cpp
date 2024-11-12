#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

// Структура Note для зберігання інформації про людину
struct Note {
    string surname;        // Прізвище людини
    string name;           // Ім'я людини
    string phoneNumber;    // Номер телефону людини
    int birthDate[3];      // Дата народження [0] - день, [1] - місяць, [2] - рік
};

// Функція для введення інформації про людину
void inputNote(Note& note) {
    cout << "Enter surname: ";
    cin >> note.surname;
    cout << "Enter name: ";
    cin >> note.name;
    cout << "Enter phone number: ";
    cin >> note.phoneNumber;

    // Введення дня народження з контролем помилок
    cout << "Enter birth day: ";
    while (!(cin >> note.birthDate[0]) || note.birthDate[0] < 1 || note.birthDate[0] > 31) {
        cout << "Invalid day. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Введення місяця народження з контролем помилок
    cout << "Enter birth month: ";
    while (!(cin >> note.birthDate[1]) || note.birthDate[1] < 1 || note.birthDate[1] > 12) {
        cout << "Invalid month. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Введення року народження з контролем помилок
    cout << "Enter birth year: ";
    while (!(cin >> note.birthDate[2]) || note.birthDate[2] < 1900 || note.birthDate[2] > 2100) {
        cout << "Invalid year. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Функція для введення інформації про всіх людей
void inputNotes(vector<Note>& notes, int count) {
    for (int i = 0; i < count; ++i) {
        Note note;
        cout << "\nPerson #" << (i + 1) << endl;
        inputNote(note);  // Введення даних про окрему людину
        notes.push_back(note);  // Додавання людини до списку
    }
}

// Функція для сортування за прізвищем
bool compareBySurname(const Note& a, const Note& b) {
    return a.surname < b.surname;
}

// Функція для виведення людей, народжених у заданому місяці
void printByBirthMonth(const vector<Note>& notes, int month) {
    bool found = false; // Змінна для перевірки, чи знайдені записи
    for (const auto& note : notes) {
        if (note.birthDate[1] == month) {
            cout << "Surname: " << note.surname << ", Name: " << note.name
                << ", Phone number: " << note.phoneNumber
                << ", Birth date: " << note.birthDate[0] << "."
                << note.birthDate[1] << "." << note.birthDate[2] << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No people were born in the specified month." << endl;
    }
}

// Функція для запису даних у файл
void saveToFile(const vector<Note>& notes, const string& filename) {
    ofstream file(filename);  // Відкриття файлу для запису
    if (file.is_open()) {
        // Запис кожного запису до файлу
        for (const auto& note : notes) {
            file << note.surname << " " << note.name << " " << note.phoneNumber << " "
                << note.birthDate[0] << " " << note.birthDate[1] << " " << note.birthDate[2] << endl;
        }
        file.close();
        cout << "Data successfully saved to file " << filename << endl;
    }
    else {
        cout << "Error opening file for writing." << endl;
    }
}

// Функція для зчитування даних з файлу
void loadFromFile(vector<Note>& notes, const string& filename) {
    ifstream file(filename);  // Відкриття файлу для читання
    if (file.is_open()) {
        notes.clear();  // Очищення наявного списку перед зчитуванням
        Note note;
        // Зчитування кожного запису з файлу
        while (file >> note.surname >> note.name >> note.phoneNumber
            >> note.birthDate[0] >> note.birthDate[1] >> note.birthDate[2]) {
            notes.push_back(note);
        }
        file.close();
        cout << "Data successfully loaded from file " << filename << endl;
    }
    else {
        cout << "Error opening file for reading." << endl;
    }
}

// Функція для відображення меню
void showMenu() {
    cout << "\nChoose an action:\n";
    cout << "1. Enter data from the keyboard\n";
    cout << "2. Display data\n";
    cout << "3. Save data to a file\n";
    cout << "4. Load data from a file\n";
    cout << "5. Display people born in the specified month\n";
    cout << "0. Exit the program\n";
    cout << "Your choice: ";
}

int main() {
    vector<Note> notes;  // Список для зберігання даних про людей
    int choice;

    do {
        showMenu();
        // Перевірка коректності вибору
        while (!(cin >> choice)) {
            cout << "Invalid choice. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1: {
            int count;
            cout << "Enter the number of records: ";
            // Перевірка коректності введення кількості записів
            while (!(cin >> count) || count < 1) {
                cout << "Invalid count. Try again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            inputNotes(notes, count);  // Введення даних
            break;
        }
        case 2: {
            if (notes.empty()) {
                cout << "No data to display.\n";
            }
            else {
                sort(notes.begin(), notes.end(), compareBySurname);  // Сортування даних за прізвищем
                // Виведення кожного запису
                for (size_t i = 0; i < notes.size(); i++) {
                    cout << i + 1 << ". Surname: " << notes[i].surname
                        << ", Name: " << notes[i].name
                        << ", Phone: " << notes[i].phoneNumber
                        << ", Birth date: " << notes[i].birthDate[0] << "."
                        << notes[i].birthDate[1] << "." << notes[i].birthDate[2] << endl;
                }
            }
            break;
        }
        case 3: {
            string filename;
            cout << "Enter the filename to save: ";
            cin >> filename;
            saveToFile(notes, filename);  // Збереження даних у файл
            break;
        }
        case 4: {
            string filename;
            cout << "Enter the filename to load: ";
            cin >> filename;
            loadFromFile(notes, filename);  // Зчитування даних з файлу
            break;
        }
        case 5: {
            int month;
            cout << "Enter the month for search (1-12): ";
            // Перевірка коректності введення місяця
            while (!(cin >> month) || month < 1 || month > 12) {
                cout << "Invalid month. Try again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            printByBirthMonth(notes, month);  // Виведення людей, народжених у заданому місяці
            break;
        }
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
