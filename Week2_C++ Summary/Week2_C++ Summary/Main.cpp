#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std ���

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BookManager {
private:
    vector<Book> books; // å ��� ����

    Book* findBookByTitle(string title)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].title == title)
            {
                return &(books[i]);
            }
        }
        return nullptr;
    }

    Book* findBookByAuthor(string author)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].author == author)
            {
                return &(books[i]);
            }
        }
        return nullptr;
    }

public:
    // å �߰� �޼���
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back ���
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    // ��� å ��� �޼���
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // �������� å �˻� �޼���
    void searchByTitle(string title)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if ((books[i].title == title))
            {
                cout << "1���� �˻��Ǿ����ϴ�: " << books[i].title << " by " << books[i].author << endl;
                return;
            }
        }
        cout << "�˻��� ������ �����ϴ�." << endl;
        return;
    }

    // ���ڸ����� å �˻� �޼���
    void searchByAuthor(string author)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].author == author)
            {
                cout << "1���� �˻��Ǿ����ϴ�: " << books[i].title << " by " << books[i].author << endl;
                return;
            }
        }
        cout << "�˻��� ������ �����ϴ�." << endl;
        return;
    }

    Book* getBookByTitle(string title)
    {
        return findBookByTitle(title);
    }

    Book* getBookByAuthor(string author)
    {
        return findBookByAuthor(author);
    }
};

class BorrowManager
{
private:
    unordered_map<string, int> stock;
public:
    // ��� �ʱ�ȭ �޼���
    void initializeStock(const Book& book, int quantity = 3)
    {
        stock.insert({ book.title, quantity });
    }

    // å �뿩 �޼���
    void borrowBook(string title)
    {
        // å�� ������ ���
        if (stock.find(title) != stock.end())
        {
            // ��� �ִ� ���
            if (stock[title] > 0)
            {
                stock[title] -= 1;
                cout << "å�� 1�� �뿩�߽��ϴ�. ��� ������Ʈ�մϴ�." << endl;
            }
            else // ��� ���� ���
            {
                cout << "��� ���� �뿩�� �� �����ϴ�." << endl;
            }
        }
        else // å�� �������� �ʴ� ���
        {
            cout << "å�� �������� �ʽ��ϴ�." << endl;
        }
    }

    // å �ݳ� �޼���
    void returnBook(string title)
    {
        // å�� ������ ���
        if (stock.find(title) != stock.end())
        {
            if (stock[title] < 3)
            {
                stock[title] += 1;
            }
            else
            {
                cout << "��� ���� á���ϴ�." << endl;
            }
        }
        else
        {
            cout << "å�� �������� �ʽ��ϴ�." << endl;
        }
    }

    // ��� ��� �޼���
    void displayStock()
    {
        if (stock.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ��� ���:" << endl;
        for (auto iter : stock)
        {
            cout << "- " << iter.first << " : " << iter.second << "��" << endl;
        }
    }
};

int main() {
    BookManager manager;
    BorrowManager borrow_manager;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. �������� å �˻�" << endl;
        cout << "4. ���ڸ����� å �˻�" << endl;
        cout << "5. �������� å �뿩" << endl;
        cout << "6. ���ڸ����� å �뿩" << endl;
        cout << "7. å �ݳ�" << endl;
        cout << "8. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�
            borrow_manager.initializeStock({ title, author });
        }
        else if (choice == 2) {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
            borrow_manager.displayStock();
        }
        else if (choice == 3) {
            // 3�� ����: �������� å �˻�
            // ����ڷκ��� å ������ �Է¹޾� 
            string title;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            manager.searchByTitle(title);
        }
        else if (choice == 4){
            // 4�� ����: ���ڸ����� å �˻�
            // ����ڷκ��� ���ڸ��� �Է¹޾�
            string author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, author); // ���� �Է� (���� ����)
            manager.searchByAuthor(author);
        }
        else if (choice == 5){
            // 5�� ����: �������� å �뿩
            // ����ڷκ��� å ������ �Է¹޾� å�� �뿩�մϴ�.
            string title;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            borrow_manager.borrowBook(title);
        }
        else if (choice == 6){
            // 6�� ����: ���ڸ����� å �뿩
            // ����ڷκ��� ���ڸ��� �Է¹޾� å�� �뿩�մϴ�.
            string author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, author); // ���� �Է� (���� ����)
            borrow_manager.borrowBook(manager.getBookByAuthor(author)->title);
        }
        else if (choice == 7){
            // 7�� ����: �������� å �ݳ�
            // ����ڷκ��� å ������ �Է¹޾� å�� �ݳ��մϴ�.
            string title;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            borrow_manager.returnBook(title);
        }
        else if (choice == 8){
            // 8�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}
