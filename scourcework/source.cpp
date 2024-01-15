#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class LibraryResource {
    char resourceCode[6];
    string title;
    string author;

public:
    void createResource() {
        cout << "Enter Resource Code: ";
        cin >> resourceCode;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
    }

    const char* getResourceCode() const {
        return resourceCode;
    }

    void displayResource() const {
        cout << "Resource Code: " << resourceCode << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
    }
};

class LibraryMember {
    char memberID[6];
    string memberName;
    int borrowedItems;
    char borrowedItemCode[6];

public:
    void createMember() {
        cout << "Enter Member ID: ";
        cin >> memberID;
        cin.ignore();
        cout << "Enter Member Name: ";
        getline(cin, memberName);
        borrowedItems = 0;
        borrowedItemCode[0] = '\0';
    }

    const char* getMemberID() const {
        return memberID;
    }

    int getBorrowedItems() const {
        return borrowedItems;
    }

    const char* getBorrowedItemCode() const {
        return borrowedItemCode;
    }

    void borrowItem() {
        cout << "Enter Item Code to borrow: ";
        cin >> borrowedItemCode;
        borrowedItems = 1;
    }

    void returnItem() {
        borrowedItemCode[0] = '\0';
        borrowedItems = 0;
    }

    void displayMember() const {
        cout << "Member ID: " << memberID << endl;
        cout << "Member Name: " << memberName << endl;
        cout << "Number of Items Borrowed: " << borrowedItems << endl;
        if (borrowedItems == 1) {
            cout << "Borrowed Item Code: " << borrowedItemCode << endl;
        }
    }
};

fstream file, file1;
vector<LibraryResource> resources;
vector<LibraryMember> members;

void writeResource() {
    LibraryResource resource;
    resource.createResource();
    file.open("resources.dat", ios::out | ios::app);
    file.write(reinterpret_cast<char*>(&resource), sizeof(LibraryResource));
    file.close();
}

void writeMember() {
    LibraryMember member;
    member.createMember();
    file.open("members.dat", ios::out | ios::app);
    file.write(reinterpret_cast<char*>(&member), sizeof(LibraryMember));
    file.close();
}

void displayResource(LibraryResource& resource) {
    resource.displayResource();
    cout << "-------------------------------\n";
}

void displayMember(LibraryMember& member) {
    member.displayMember();
    cout << "-------------------------------\n";
}

void modifyResource() {
    char resourceCode[6];
    cout << "Enter Resource Code to be modified: ";
    cin >> resourceCode;
    bool found = false;
    file.open("resources.dat", ios::in | ios::out);
    while (file.read(reinterpret_cast<char*>(&resources[0]), sizeof(LibraryResource))) {
        if (strcmp(resources[0].getResourceCode(), resourceCode) == 0) {
            displayResource(resources[0]);
            cout << "Enter new details:" << endl;
            resources[0].createResource();
            int pos = -1 * static_cast<int>(sizeof(LibraryResource));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&resources[0]), sizeof(LibraryResource));
            cout << "Record Updated!" << endl;
            found = true;
        }
    }
    file.close();
    if (!found) {
        cout << "Record Not Found!" << endl;
    }
}

void modifyMember() {
    char memberID[6];
    cout << "Enter Member ID to be modified: ";
    cin >> memberID;
    bool found = false;
    file.open("members.dat", ios::in | ios::out);
    while (file.read(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember))) {
        if (strcmp(members[0].getMemberID(), memberID) == 0) {
            displayMember(members[0]);
            cout << "Enter new details:" << endl;
            members[0].createMember();
            int pos = -1 * static_cast<int>(sizeof(LibraryMember));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember));
            cout << "Record Updated!" << endl;
            found = true;
        }
    }
    file.close();
    if (!found) {
        cout << "Record Not Found!" << endl;
    }
}

void deleteResource() {
    char resourceCode[6];
    cout << "Enter Resource Code to be deleted: ";
    cin >> resourceCode;
    file.open("resources.dat", ios::in | ios::out);
    fstream file2;
    file2.open("Temp.dat", ios::out);
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(&resources[0]), sizeof(LibraryResource))) {
        if (strcmp(resources[0].getResourceCode(), resourceCode) != 0) {
            file2.write(reinterpret_cast<char*>(&resources[0]), sizeof(LibraryResource));
        }
    }
    file2.close();
    file.close();
    remove("resources.dat");
    rename("Temp.dat", "resources.dat");
    cout << "Record Deleted!" << endl;
}

void deleteMember() {
    char memberID[6];
    cout << "Enter Member ID to be deleted: ";
    cin >> memberID;
    file.open("members.dat", ios::in | ios::out);
    fstream file2;
    file2.open("Temp.dat", ios::out);
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember))) {
        if (strcmp(members[0].getMemberID(), memberID) != 0) {
            file2.write(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember));
        }
    }
    file2.close();
    file.close();
    remove("members.dat");
    rename("Temp.dat", "members.dat");
    cout << "Record Deleted!" << endl;
}

void displayAllResources() {
    cout << "\n\n\n\t\tDisplay All Resources\n\n";
    file.open("resources.dat", ios::in);
    if (!file) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tResource List\n\n";
    while (file.read(reinterpret_cast<char*>(&resources[0]), sizeof(LibraryResource))) {
        displayResource(resources[0]);
    }
    file.close();
}

void displayAllMembers() {
    cout << "\n\n\n\t\tDisplay All Members\n\n";
    file.open("members.dat", ios::in);
    if (!file) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tMember List\n\n";
    while (file.read(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember))) {
        displayMember(members[0]);
    }
    file.close();
}

void itemBorrow() {
    char memberID[6], itemCode[6];
    int found = 0, flag = 0;
    cout << "\n\nItem Borrow ...";
    cout << "\n\n\tEnter Member ID: ";
    cin >> memberID;
    file.open("members.dat", ios::in | ios::out);
    file1.open("resources.dat", ios::in | ios::out);
    while (file.read(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember)) && found == 0) {
        if (strcmp(members[0].getMemberID(), memberID) == 0) {
            found = 1;
            if (members[0].getBorrowedItems() == 0) {
                cout << "\n\n\tEnter Item Code: ";
                cin >> itemCode;
                while (file1.read(reinterpret_cast<char*>(&resources[0]), sizeof(LibraryResource)) && flag == 0) {
                    if (strcmp(resources[0].getResourceCode(), itemCode) == 0) {
                        displayResource(resources[0]);
                        flag = 1;
                        members[0].borrowItem();
                        members[0].displayMember();
                        int pos = -1 * static_cast<int>(sizeof(LibraryMember));
                        file.seekp(pos, ios::cur);
                        file.write(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember));
                        cout << "\n\n\t Item borrowed successfully!";
                    }
                }
                if (flag == 0) {
                    cout << "Item does not exist...";
                }
            } else {
                cout << "You have not returned the last item!";
            }
        }
    }
    if (found == 0) {
        cout << "Member record not exist...";
    }
    file.close();
    file1.close();
}

void itemReturn() {
    char memberID[6], itemCode[6];
    int found = 0, flag = 0;
    cout << "\n\nItem Return ...";
    cout << "\n\n\tEnter Member ID: ";
    cin >> memberID;
    file.open("members.dat", ios::in | ios::out);
    file1.open("resources.dat", ios::in | ios::out);
    while (file.read(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember)) && found == 0) {
        if (strcmp(members[0].getMemberID(), memberID) == 0) {
            found = 1;
            if (members[0].getBorrowedItems() == 1) {
                while (file1.read(reinterpret_cast<char*>(&resources[0]), sizeof(LibraryResource)) && flag == 0) {
                    if (strcmp(resources[0].getResourceCode(), members[0].getBorrowedItemCode()) == 0) {
                        displayResource(resources[0]);
                        flag = 1;
                        cout << "\n\nItem returned!";
                        members[0].returnItem();
                        int pos = -1 * static_cast<int>(sizeof(LibraryMember));
                        file.seekp(pos, ios::cur);
                        file.write(reinterpret_cast<char*>(&members[0]), sizeof(LibraryMember));
                    }
                }
                if (flag == 0) {
                    cout << "Item does not exist...";
                }
            } else {
                cout << "No item borrowed!";
            }
        }
    }
    if (found == 0) {
        cout << "Member record not exist...";
    }
    file.close();
    file1.close();
}

int main() {
    while (true) {
        cout << "\n\n\n\tLIBRARY MANAGEMENT SYSTEM";
        cout << "\n\n\t1. Add Resource";
        cout << "\n\n\t2. Add Member";
        cout << "\n\n\t3. Display All Resources";
        cout << "\n\n\t4. Display All Members";
        cout << "\n\n\t5. Modify Resource";
        cout << "\n\n\t6. Modify Member";
        cout << "\n\n\t7. Delete Resource";
        cout << "\n\n\t8. Delete Member";
        cout << "\n\n\t9. Borrow Item";
        cout << "\n\n\t10. Return Item";
        cout << "\n\n\t11. Exit";
        cout << "\n\n\tEnter your Choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                writeResource();
                break;
            case 2:
                writeMember();
                break;
            case 3:
                displayAllResources();
                break;
            case 4:
                displayAllMembers();
                break;
            case 5:
                modifyResource();
                break;
            case 6:
                modifyMember();
                break;
            case 7:
                deleteResource();
                break;
            case 8:
                deleteMember();
                break;
            case 9:
                itemBorrow();
                break;
            case 10:
                itemReturn();
                break;
            case 11:
                exit(0);
        }
    }
}

