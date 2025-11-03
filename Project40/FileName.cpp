#include "Restaurant.h"
#include "AdminAndUserPanel.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void WriteToFile(DoubleLinkedList<User>& users, const string filename = "users.txt") {
    fstream fs(filename, ios::app);

    if (fs.is_open()) {
        User user = users[users.Size() - 1];
        fs << user.GetUsername() << "#" << user.GetPassword() << "#"
            << user.GetMail() << "#" << user.GetAge() << "\n";
    }
    else {
        throw string("File couldn't open !");
    }

    fs.close();
}

void ReadFromFile(DoubleLinkedList<User>& users, const string filename = "users.txt") {
    fstream fs(filename, ios::in);

    if (fs.is_open()) {
        string row;
        while (getline(fs, row)) {
            if (row.empty()) continue;

            string username, password, mail, ageStr;
            int count = 0;

            for (auto ch : row) {
                if (ch == '#') {
                    count++;
                    continue;
                }

                else if (count == 0) {
                    username += ch;
                }
                else if (count == 1) {
                    password += ch;
                }
                else if (count == 2) {
                    mail += ch;
                }
                else if (count == 3) {
                    ageStr += ch;
                }
            }

            if (!username.empty() && !password.empty() && !mail.empty() && !ageStr.empty()) {
                User user;
                user.SetUsername(username);
                user.SetPassword(password);
                user.SetMail(mail);
                user.SetAge(stoi(ageStr));
                users.AddEnd(user);
            }
        }
    }
    else {
        throw string("File couldn't open !");
    }

    fs.close();
}




int main() {
    Restaurant restaurant;
    UserManager userManager;
    AdminPanel admin;

    restaurant.AddIngredientToStock(Ingredient("Kartof", 100, 2.2));
    restaurant.AddIngredientToStock(Ingredient("Et", 50, 10));
    restaurant.AddIngredientToStock(Ingredient("Sogan", 30, 2.4));
    restaurant.AddIngredientToStock(Ingredient("Pomidor", 25, 2.5));
    restaurant.AddIngredientToStock(Ingredient("Biber", 15, 2.7));
    restaurant.AddIngredientToStock(Ingredient("Duyu", 40, 3.8));

    Food food1("Kartoflu Et", "Dadli kartoflu et yemeyi", 15);
    food1.AddIngredient("Kartof", 0.5);
    food1.AddIngredient("Et", 0.6);
    food1.AddIngredient("Sogan", 0.2);
    restaurant.AddFood(food1);

    Food food2("Etli Plov", "Dadli plov", 18);
    food2.AddIngredient("Et", 0.7);
    food2.AddIngredient("Sogan", 0.2);
    food2.AddIngredient("Duyu", 0.6);
    restaurant.AddFood(food2);


    Food food4("Biber Dolmasi", "Enenevi dolma yemeyi", 12);
    food4.AddIngredient("Biber", 0.5);
    food4.AddIngredient("Et", 0.2);
    food4.AddIngredient("Sogan", 0.1);
    food4.AddIngredient("Duyu", 0.2);
    restaurant.AddFood(food4);

    Food food5("Kartof Qizartmasi", "Xirt-xirt kartoflar", 7);
    food5.AddIngredient("Kartof", 0.5);
    restaurant.AddFood(food5);


    try {
        ReadFromFile(userManager.GetUsers());
    }
    catch (const string& error) {
        cout << "Error reading users: " << error << endl;

    }


    while (true) {
        setColor(14);
        cout << "\n<<< Restaurant System >>>\n";
        setColor(7);
        cout << "1. Admin Panel\n";
        cout << "2. User Panel\n";
        setColor(4);
        cout << "3. Exit\n";
        setColor(7);
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            setColor(4);
            cout << "Invalid input! Please enter a number\n";
            setColor(7);
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            string username, password;
            cout << "Enter admin username: ";
            getline(cin, username);
            cout << "Enter admin password: ";
            getline(cin, password);

            try {
                admin.SetUsername(username);
                admin.SetPassword(password);
            }
            catch (const string& error) {
                setColor(12);
                cout << "Error: " << error << endl;
                setColor(7);
                continue;
            }

            while (true) {
                setColor(14);
                cout << "\nAdmin Menu:\n";
                setColor(7);
                cout << "1. View Menu\n";
                cout << "2. Add Food to Menu\n";
                cout << "3. Remove Food from Menu\n";
                cout << "4. View Stock\n";
                cout << "5. Add Ingredient to Stock\n";
                cout << "6. Remove Ingredient from Stock\n";
                cout << "7. View Budget\n";
                cout << "8. Back to Main Menu\n";
                cout << "Choice: ";

                int adminChoice;
                if (!(cin >> adminChoice)) {
                    cin.clear();
                    cin.ignore();
                    setColor(4);
                    cout << "Invalid input! Please enter a number\n";
                    setColor(7);
                    continue;
                }
                cin.ignore();

                if (adminChoice == 1) {
                    restaurant.PrintMenu();
                }
                else if (adminChoice == 2) {
                    string name, about;
                    float price;
                    cout << "Food name: ";
                    getline(cin, name);
                    cout << "About: ";
                    getline(cin, about);
                    cout << "Price: ";
                    if (!(cin >> price)) {
                        cin.clear();
                        cin.ignore();
                        setColor(4);
                        cout << "Invalid price inputn !\n";
                        setColor(7);
                        continue;
                    }
                    if (price <= 0) {
                        setColor(4);
                        cout << "Price cannot be negative or zero !\n";
                        setColor(7);
                        continue;
                    }
                    cin.ignore();

                    Food food(name, about, price);

                    int ingCount;
                    cout << "Number of ingredients: ";
                    if (!(cin >> ingCount)) {
                        cin.clear();
                        cin.ignore();
                        setColor(4);
                        cout << "Invalid input !\n";
                        setColor(7);
                        continue;
                    }
                    if (ingCount <= 0) {
                        setColor(4);
                        cout << "Number of ingredients cannot be negative or zero !\n";
                        setColor(7);
                        continue;
                    }
                    cin.ignore();

                    for (int i = 0; i < ingCount; i++) {
                        string ingName;
                        float weight;
                        cout << "Ingredient " << i + 1 << " name: ";
                        getline(cin, ingName);
                        cout << "Weight (kg): ";
                        if (!(cin >> weight)) {
                            cin.clear();
                            cin.ignore();
                            setColor(4);
                            cout << "Invalid weight input !\n";
                            setColor(7);
                            i--;
                            continue;
                        }

                        cin.ignore();
                        food.AddIngredient(ingName, weight);
                    }

                    restaurant.AddFood(food);
                }
                else if (adminChoice == 3) {
                    string name;
                    cout << "Food name to remove: ";
                    getline(cin, name);
                    try {
                        restaurant.RemoveFood(name);
                    }
                    catch (const string& error) {
                        setColor(4);
                        cout << "Error: " << error << endl;
                        setColor(7);
                    }
                }
                else if (adminChoice == 4) {
                    restaurant.PrintStock();
                }
                else if (adminChoice == 5) {
                    string name;
                    float quantity, price;
                    cout << "Ingredient name: ";
                    getline(cin, name);
                    cout << "Quantity (kg): ";
                    if (!(cin >> quantity)) {
                        cin.clear();
                        cin.ignore();
                        setColor(4);
                        cout << "Invalid quantity input !\n";
                        setColor(7);
                        continue;
                    }

                    cout << "Price per kg: ";
                    if (!(cin >> price)) {
                        cin.clear();
                        cin.ignore();
                        setColor(4);
                        cout << "Invalid price input !\n";
                        setColor(7);
                        continue;
                    }

                    cin.ignore();

                    try {
                        Ingredient ing(name, quantity, price);
                        restaurant.AddIngredientToStock(ing);
                    }
                    catch (const string& error) {
                        setColor(4);
                        cout << "Error: " << error << endl;
                        setColor(7);
                    }
                }
                else if (adminChoice == 6) {
                    string name;
                    cout << "Ingredient name to remove: ";
                    getline(cin, name);
                    try {
                        restaurant.RemoveIngredientFromStock(name);
                    }
                    catch (const string& error) {
                        setColor(4);
                        cout << "Error: " << error << endl;
                        setColor(7);
                    }
                }
                else if (adminChoice == 7) {
                    setColor(14);
                    cout << "Current budget: " << restaurant.GetBudget() << " AZN\n";
                    setColor(7);
                }
                else if (adminChoice == 8) {
                    break;
                }
                else {
                    setColor(4);
                    cout << "Invalid choice! Please try again\n";
                    setColor(7);
                }
            }
        }
        else if (choice == 2) {
            while (true) {
                setColor(14);
                cout << "\nUser Menu:\n";
                setColor(7);
                cout << "1. Register\n";
                cout << "2. Login\n";
                cout << "3. Back to Main Menu\n";
                cout << "Choice: ";

                int userChoice;
                if (!(cin >> userChoice)) {
                    cin.clear();
                    cin.ignore();
                    setColor(4);
                    cout << "Invalid input! Please enter a number\n";
                    setColor(7);
                    continue;
                }
                cin.ignore();

                if (userChoice == 1) {
                    string username, password, mail;
                    int age;
                    cout << "Username (min 6 characters): ";
                    getline(cin, username);
                    cout << "Password (min 8 characters): ";
                    getline(cin, password);
                    cout << "Email (@gmail.com): ";
                    getline(cin, mail);
                    cout << "Age (min 15): ";
                    if (!(cin >> age)) {
                        cin.clear();
                        cin.ignore();
                        setColor(4);
                        cout << "Invalid age input!\n";
                        setColor(7);
                        continue;
                    }
                    if (age < 15) {
                        setColor(4);
                        cout << "Age must be at least 15 !\n";
                        setColor(7);
                        continue;
                    }
                    cin.ignore();

                    try {
                        userManager.SignUp(username, password, mail, age);
                        setColor(10);
                        cout << "Registration successful !\n";
                        setColor(7);

                        try {
                            WriteToFile(userManager.GetUsers());
                        }
                        catch (const string& error) {
                            cout << "Error saving user: " << error << endl;
                        }
                    }
                    catch (const string& error) {
                        setColor(4);
                        cout << "Error: " << error << endl;
                        setColor(7);
                    }
                }
                else if (userChoice == 2) {
                    string username, password, mail;
                    cout << "Username: ";
                    getline(cin, username);
                    cout << "Password: ";
                    getline(cin, password);
                    cout << "Email: ";
                    getline(cin, mail);

                    try {
                        userManager.SignIn(username, password, mail);


                        while (true) {
                            setColor(14);
                            cout << "\nUser Panel:\n";
                            setColor(7);
                            cout << "1. View Menu\n";
                            cout << "2. Add Food to Cart\n";
                            cout << "3. Remove Food from Cart\n";
                            cout << "4. Complete Order\n";
                            cout << "5. Change Password\n";
                            cout << "6. Logout\n";
                            cout << "Choice: ";

                            int panelChoice;
                            if (!(cin >> panelChoice)) {
                                cin.clear();
                                cin.ignore();
                                setColor(4);
                                cout << "Invalid input! Please enter a number\n";
                                setColor(7);
                                continue;
                            }
                            cin.ignore();

                            if (panelChoice == 1) {
                                restaurant.PrintMenu();
                            }
                            else if (panelChoice == 2) {
                                string name;
                                cout << "Food name to add: ";
                                getline(cin, name);
                                try {
                                    restaurant.AddFoodToCart(name);
                                }
                                catch (const string& error) {
                                    setColor(4);
                                    cout << "Error: " << error << endl;
                                    setColor(7);
                                }
                            }
                            else if (panelChoice == 3) {
                                string name;
                                cout << "Food name to remove: ";
                                getline(cin, name);
                                try {
                                    restaurant.RemoveFoodFromCart(name);
                                }
                                catch (const string& error) {
                                    setColor(4);
                                    cout << "Error: " << error << endl;
                                    setColor(7);
                                }
                            }
                            else if (panelChoice == 4) {
                                try {
                                    restaurant.CompleteOrder();
                                }
                                catch (const string& error) {
                                    setColor(4);
                                    cout << "Error: " << error << endl;
                                    setColor(7);
                                }
                            }
                            else if (panelChoice == 5) {
                                string username, password, mail;
                                cout << "Username: ";
                                getline(cin, username);
                                cout << "New Password: ";
                                getline(cin, password);
                                cout << "Email: ";
                                getline(cin, mail);
                                try {
                                    userManager.ChangePassword(username, password, mail);
                                }
                                catch (const string& error) {
                                    setColor(4);
                                    cout << "Error: " << error << endl;
                                    setColor(7);
                                }
                            }
                            else if (panelChoice == 6) {
                                break;
                            }
                            else {
                                setColor(4);
                                cout << "Invalid choice! Please try again\n";
                                setColor(7);
                            }
                        }
                    }
                    catch (const string& error) {
                        setColor(4);
                        cout << "Error: " << error << endl;
                        setColor(7);
                    }
                }
                else if (userChoice == 3) {
                    break;
                }
                else {
                    setColor(4);
                    cout << "Invalid choice! Please try again\n";
                    setColor(7);
                }
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            setColor(4);
            cout << "Invalid choice! Please try again\n";
            setColor(7);
        }
    }

    return 0;
}