#include <iostream>
#include <random>
#include <fstream>
#include <Windows.h>
#include <chrono>

using namespace std;

const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int N[] = {100, 1000, 10000};

random_device r;
default_random_engine generator(r());
uniform_int_distribution<int> number_distribution(0, INT_MAX);
uniform_int_distribution<int> char_index_distribution(0, (int) strlen(alphabet) - 1);

struct ClinicPatient {
    int card_number;
    int disease_code;
    char doctors_name[20];
};

struct TableEntry {
    int key;
    int offset;
};

bool IsCardNumberExists(auto &arr, const int &n, const int &card_number) {
    for (int i = 0; i < n; ++i)
        if (arr[i].card_number == card_number) return true;
    return false;
}

void GenerateArray(auto &arr, const int &n) {
    for (int i = 0; i < n; ++i) {
        int card_number = number_distribution(generator);
        while (IsCardNumberExists(arr, n, card_number))
            card_number = number_distribution(generator);
        arr[i].card_number = card_number;
        arr[i].disease_code = number_distribution(generator);
        for (int j = 0; j < 19; ++j) {
            arr[i].doctors_name[j] = alphabet[char_index_distribution(generator)];
        }
        arr[i].doctors_name[19] = '\0';
    }
}

ClinicPatient GetLastRecord(auto file, const int &n) {
    fseek(file, (n - 1) * sizeof(ClinicPatient), SEEK_SET);
    ClinicPatient temp = {};
    fread(&temp, sizeof(ClinicPatient), 1, file);
    return temp;
}

inline void Task1() {
    FILE *file;
    fopen_s(&file, "data.bin", "wb");
    auto arr = new ClinicPatient[N[0]];
    GenerateArray(arr, N[0]);
    fwrite(arr, sizeof(ClinicPatient), N[0], file);
    fclose(file);
    fopen_s(&file, "data.bin", "rb");
    auto last_record = GetLastRecord(file, N[0]);
    cout << "Total records: " << N << "\n";
    cout << "Total bytes: " << N[0] * sizeof(ClinicPatient) << "\n";
    cout << "Last record: " << "\n";
    cout << "   card_number: " << last_record.card_number << "\n";
    cout << "   disease_code: " << last_record.disease_code << "\n";
    cout << "   doctors_name: " << last_record.doctors_name << "\n";
}

ClinicPatient LinearSearch(auto file, const int n, auto key) {
    ClinicPatient temp = {};
    for (int i = 0; i < n; ++i) {
        auto read = fread(&temp, sizeof(ClinicPatient), 1, file);
        if (read == 0)
            return {};
        if (temp.card_number == key) {
            return temp;
        }
    }
    return {};
}

size_t InterpolationSearch(const vector<TableEntry> &table, const int &key) {
    size_t left = 0;
    size_t right = table.size() - 1;
    while (left <= right && key >= table[left].key && key <= table[right].key) {
        cout << left << " " << right << " " << key << "\n";
        size_t mid = left + ((key - table[left].key) * (right - left)) / (table[right].key - table[left].key);
        if (table[mid].key == key) {
            return mid;
        }
        if (table[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (table[left].key == key) {
        return left;
    } else if (table[right].key == key) {
        return right;
    } else {
        return -1;
    }
}

inline void Task2() {
    for (int i: N) {
        FILE *file;
        fopen_s(&file, "data.bin", "wb");
        auto arr = new ClinicPatient[i];
        GenerateArray(arr, i);
        fwrite(arr, sizeof(ClinicPatient), i, file);
        fclose(file);

        fopen_s(&file, "data.bin", "rb");

        auto last_record = GetLastRecord(file, i);

        cout << "Total records: " << i << "\n";
        cout << "Total bytes: " << i * sizeof(ClinicPatient) << "\n";
        cout << "Last record: " << "\n";
        cout << "   card_number: " << last_record.card_number << "\n";
        cout << "   disease_code: " << last_record.disease_code << "\n";
        cout << "   doctors_name: " << last_record.doctors_name << "\n";
        cout << "\n";
        cout << "Enter key for search:\n";
        int key;
        cin >> key;
        fseek(file, 0, SEEK_SET);
        auto start_time = chrono::high_resolution_clock::now();
        auto record = LinearSearch(file, i, key);
        ClinicPatient emptyPatient = {};
        if (record.card_number == emptyPatient.card_number &&
            record.disease_code == emptyPatient.disease_code &&
            strcmp(record.doctors_name, emptyPatient.doctors_name) == 0) {
            cout << "No such key exists\n\n";
            fclose(file);
            delete[] arr;
            continue;
        }
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Found record: " << "\n";
        cout << "   card_number: " << record.card_number << "\n";
        cout << "   disease_code: " << record.disease_code << "\n";
        cout << "   doctors_name: " << record.doctors_name << "\n";
        cout << "Search time: " << duration.count() << " nanoseconds \n\n";
        fclose(file);
        delete[] arr;
    }
}

ClinicPatient ReadRecordFromFile(auto file, const int &offset) {
    fseek(file, offset, SEEK_SET);
    ClinicPatient temp = {};
    fread(&temp, sizeof(ClinicPatient), 1, file);
    return temp;
}

inline void Task3() {
    for (int i: N) {
        vector<TableEntry> table(i);
        FILE *file;
        fopen_s(&file, "data.bin", "wb");
        auto arr = new ClinicPatient[i];
        GenerateArray(arr, i);
        for (int j = 0; j < i; ++j) {
            table[j].key = arr[j].card_number;
            table[j].offset = j * int(sizeof(ClinicPatient));
        }
        fwrite(arr, sizeof(ClinicPatient), i, file);
        fclose(file);

        fopen_s(&file, "data.bin", "rb");

        auto last_record = GetLastRecord(file, i);

        cout << "Total records: " << i << "\n";
        cout << "Total bytes: " << i * sizeof(ClinicPatient) << "\n";
        cout << "Last record: " << "\n";
        cout << "   card_number: " << last_record.card_number << "\n";
        cout << "   disease_code: " << last_record.disease_code << "\n";
        cout << "   doctors_name: " << last_record.doctors_name << "\n";
        cout << "\n";
        cout << "Enter key for search:\n";
        int key;
        cin >> key;
        fseek(file, 0, SEEK_SET);
        auto start_time = chrono::high_resolution_clock::now();
        sort(table.begin(), table.end(), [](const TableEntry &a, const TableEntry &b) {
            return a.key < b.key;
        });
        int found_record_index = int(InterpolationSearch(table, key));
        if (found_record_index == -1) {
            cout << "No such key exists\n\n";
            fclose(file);
            delete[] arr;
            continue;
        }
        ClinicPatient record = ReadRecordFromFile(file, table[found_record_index].offset);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
        cout << "Found record: " << "\n";
        cout << "   card_number: " << record.card_number << "\n";
        cout << "   disease_code: " << record.disease_code << "\n";
        cout << "   doctors_name: " << record.doctors_name << "\n";
        cout << "Search time: " << duration.count() << " nanoseconds \n\n";
        fclose(file);
        delete[] arr;
    }
}

int main() {
    int task_number;
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    cout << "Task 1 - 1\n"
            "Task 2 - 2\n"
            "Task 3 - 3\n"
            "Input task number:";
    cin >> task_number;
    switch (task_number) {
        case 1:
            Task1();
            break;
        case 2:
            Task2();
            break;
        case 3:
            Task3();
            break;
        default:
            cout << "You entered an incorrect number";
    }
    return 0;
}