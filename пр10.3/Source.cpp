#pragma execution_character_set("utf-8")
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

struct Bill {
    string platnika;
    string oderz;
    double suma;
};

void createFile(const string& filename, const Bill& bill) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Cannot create file." << endl;
        return;
    }
    file << bill.platnika << "," << bill.oderz << "," << bill.suma << endl;
    file.close();
}

void displayFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Cannot open file" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void addBill(const string& filename, const Bill& bill) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Cannot open file for appending." << endl;
        return;
    }

    file << bill.platnika << "," << bill.oderz << "," << bill.suma << endl;

    file.close();
}

void searchSum(const string& filename, const double& sum) {
    ifstream file(filename);
    if (!file) {
        cerr << "Cannot open file" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string platnika, oderz;
        double suma;

        getline(ss, platnika, ',');
        getline(ss, oderz, ',');
        ss >> suma;

        if (suma == sum) {
            found = true;
            cout << "Розрахунковий рахунок платника: " << platnika << ", " << endl;
            cout << "Розрахунковий рахунок одержувача: " << oderz << ", Сума: " << suma << " грн" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Інформації про суму '" << sum << "' не знайдено." << endl;
    }

    file.close();
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    Bill bill;
    int N;
    cout << "Введіть N: "; cin >> N;
    for (int i = 0; i < N; i++) {
        cout << "Рахунок платника: ";
        cin >> bill.platnika;
        cout << "Рахунок одержувача: ";
        cin >> bill.oderz;
        cout << "Сума: ";
        cin >> bill.suma;
        createFile(filename, bill);
    }
    int found;
    string iproduct;
    double sum;
    Bill newBill;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << "  [1] - вивід даних на екран" << endl;
        cout << "  [2] - додати дані у файл" << endl;
        cout << "  [3] - пошук суми" << endl;
        cout << "  [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            displayFile(filename);
            break;
        case 2:
            cout << "Рахунок платника: ";
            cin >> newBill.platnika;
            cout << "Рахунок одержувача: ";
            cin >> newBill.oderz;
            cout << "Сума: ";
            cin >> newBill.suma;
            addBill(filename, newBill);
            break;
        case 3:
            cout << "Введіть ключі пошуку:" << endl;
            cin.get();
            cin.sync();

            cout << "    сума: "; cin >> sum;
            cout << endl;
            searchSum(filename, sum);
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    return 0;
}