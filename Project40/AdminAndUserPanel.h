#include<iostream>
#include<cassert>
#include<string>
using namespace std;

class AdminPanel {
    string username;
    string password;
public:
    AdminPanel() {
        this->username = "";
        this->password = "";
    }
    AdminPanel(string username, string password) {
        SetUsername(username);
        SetPassword(password);
    }

    string GetUsername() const {
        return username;
    }
    string GetPassword() const {
        return password;
    }

    void SetUsername(string username) {
        if (username == "admin") {
            this->username = username;
        }
        else {
            throw string("Username is Wrong !");
        }
    }

    void SetPassword(string password) {
        if (password == "admin") {
            this->password = password;
        }
        else {
            throw string("Password is Wrong !");
        }
    }
};


template<class T>
class DoubleLinkedList {
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;
        Node(const T& data) {
            this->data = data;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;
public:
    void AddBegin(const T& data) {
        Node* node = new Node(data);
        if (head == nullptr) {
            head = tail = node;
        }
        else {
            head->prev = node;
            node->next = head;
            head = node;
        }
        size++;
    }

    void AddEnd(const T& data) {
        Node* node = new Node(data);
        if (tail == nullptr) {
            head = tail = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        size++;
    }

    void DeleteBegin() {
        if (head == nullptr) {
            assert(!"List is empty");
        }
        else {
            Node* temp = head;
            if (head == tail) {
                head = tail = nullptr;
            }
            else {
                head = head->next;
                head->prev = nullptr;
            }
            delete temp;
            size--;
        }
    }

    void DeleteEnd() {
        if (tail == nullptr) {
            assert(!"List is empty");
        }
        else {
            Node* temp = tail;
            if (head == tail) {
                head = tail = nullptr;
            }
            else {
                tail = tail->prev;
                tail->next = nullptr;
            }
            delete temp;
            size--;
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            assert(!"Index out of bounds");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            assert(!"Index out of bounds");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }


    int Size() const {
        return size;
    }

    void Print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~DoubleLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};




class User {
    string username;
    string password;
    string mail;
    int age;
public:
    User() {
        this->username = "";
        this->password = "";
        this->mail = "";
        this->age = 0;
    }
    User(string username, string password, string mail, int age) {
        SetUsername(username);
        SetPassword(password);
        SetMail(mail);
        SetAge(age);
    }

    string GetUsername() const {
        return username;
    }
    string GetPassword() const {
        return password;
    }
    string GetMail() const {
        return mail;
    }
    int GetAge() const {
        return age;
    }

    void SetUsername(string username) {
        if (username.length() >= 6) {
            this->username = username;
        }
        else {
            throw string("Username is short...");
        }
    }

    void SetPassword(string password) {
        if (password.length() >= 8) {
            this->password = password;
        }
        else {
            throw string("Password is short...");
        }
    }
    void SetMail(string mail) {
        if (mail.length() < 11) {
            throw string("Mail is wrong...");
        }
        if (mail.substr(mail.length() - 10, 10) != "@gmail.com") {
            throw string("Mail is wrong...");
        }
        this->mail = mail;
    }

    void SetAge(int age) {
        if (age >= 15) {
            this->age = age;
        }
        else {
            throw string("Age is lower than 15...");
        }
    }
};

class UserManager {
    DoubleLinkedList<User> users;
    static int count;
public:
    UserManager() {
        count++;
    }

    void SignUp(string username, string password, string mail, int age) {
        int index = SearchUser(username, mail);
        if (index != -1) {
            throw string("This username or mail already exists...");
        }
        else {
            User* user = new User(username, password, mail, age);
            users.AddEnd(*user);
        }
    }
    void SignIn(string username, string password, string mail) {
        for (size_t i = 0; i < users.Size(); i++) {
            if (users[i].GetUsername() == username &&
                users[i].GetMail() == mail &&
                users[i].GetPassword() == password) {
                setColor(10);
                cout << "Welcome " << username << "!" << endl;
                setColor(7);
                return;
            }
        }
        throw string("This user not found..");
    }


    void ChangePassword(string username, string password, string mail) {
        int index = SearchUser(username, mail);
        if (index == -1) {
            throw string("This user not found !");
        }
        if (users[index].GetUsername() != username || users[index].GetMail() != mail) {
            throw string("Username or email is incorrect !");
        }
        users[index].SetPassword(password);
        setColor(10);
        cout << "Password changed successfully !\n";
        setColor(7);
    }

    int SearchUser(string username, string mail) {
        for (size_t i = 0; i < users.Size(); i++)
        {
            if (users[i].GetUsername() == username || users[i].GetMail() == mail) {
                return i;
            }
        }
        return -1;
    }

    DoubleLinkedList<User>& GetUsers() {
        return users;
    }

    ~UserManager() {
        count--;
    }
};

int UserManager::count = 0;