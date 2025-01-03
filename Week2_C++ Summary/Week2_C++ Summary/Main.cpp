#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장

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
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    // 제목으로 책 검색 메서드
    void searchByTitle(string title)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if ((books[i].title == title))
            {
                cout << "1건이 검색되었습니다: " << books[i].title << " by " << books[i].author << endl;
                return;
            }
        }
        cout << "검색된 도서가 없습니다." << endl;
        return;
    }

    // 저자명으로 책 검색 메서드
    void searchByAuthor(string author)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].author == author)
            {
                cout << "1건이 검색되었습니다: " << books[i].title << " by " << books[i].author << endl;
                return;
            }
        }
        cout << "검색된 도서가 없습니다." << endl;
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
    // 재고 초기화 메서드
    void initializeStock(const Book& book, int quantity = 3)
    {
        stock.insert({ book.title, quantity });
    }

    // 책 대여 메서드
    void borrowBook(string title)
    {
        // 책이 존재할 경우
        if (stock.find(title) != stock.end())
        {
            // 재고가 있는 경우
            if (stock[title] > 0)
            {
                stock[title] -= 1;
                cout << "책을 1권 대여했습니다. 재고를 업데이트합니다." << endl;
            }
            else // 재고가 없는 경우
            {
                cout << "재고가 없어 대여할 수 없습니다." << endl;
            }
        }
        else // 책이 존재하지 않는 경우
        {
            cout << "책이 존재하지 않습니다." << endl;
        }
    }

    // 책 반납 메서드
    void returnBook(string title)
    {
        // 책이 존재할 경우
        if (stock.find(title) != stock.end())
        {
            if (stock[title] < 3)
            {
                stock[title] += 1;
            }
            else
            {
                cout << "재고가 가득 찼습니다." << endl;
            }
        }
        else
        {
            cout << "책이 존재하지 않습니다." << endl;
        }
    }

    // 재고 출력 메서드
    void displayStock()
    {
        if (stock.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 재고 목록:" << endl;
        for (auto iter : stock)
        {
            cout << "- " << iter.first << " : " << iter.second << "권" << endl;
        }
    }
};

int main() {
    BookManager manager;
    BorrowManager borrow_manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 제목으로 책 검색" << endl;
        cout << "4. 저자명으로 책 검색" << endl;
        cout << "5. 제목으로 책 대여" << endl;
        cout << "6. 저자명으로 책 대여" << endl;
        cout << "7. 책 반납" << endl;
        cout << "8. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            borrow_manager.initializeStock({ title, author });
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
            borrow_manager.displayStock();
        }
        else if (choice == 3) {
            // 3번 선택: 제목으로 책 검색
            // 사용자로부터 책 제목을 입력받아 
            string title;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            manager.searchByTitle(title);
        }
        else if (choice == 4){
            // 4번 선택: 저자명으로 책 검색
            // 사용자로부터 저자명을 입력받아
            string author;
            cout << "책 저자: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author); // 제목 입력 (공백 포함)
            manager.searchByAuthor(author);
        }
        else if (choice == 5){
            // 5번 선택: 제목으로 책 대여
            // 사용자로부터 책 제목을 입력받아 책을 대여합니다.
            string title;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            borrow_manager.borrowBook(title);
        }
        else if (choice == 6){
            // 6번 선택: 저자명으로 책 대여
            // 사용자로부터 저자명을 입력받아 책을 대여합니다.
            string author;
            cout << "책 저자: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, author); // 제목 입력 (공백 포함)
            borrow_manager.borrowBook(manager.getBookByAuthor(author)->title);
        }
        else if (choice == 7){
            // 7번 선택: 제목으로 책 반납
            // 사용자로부터 책 제목을 입력받아 책을 반납합니다.
            string title;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            borrow_manager.returnBook(title);
        }
        else if (choice == 8){
            // 8번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0; // 프로그램 정상 종료
}
