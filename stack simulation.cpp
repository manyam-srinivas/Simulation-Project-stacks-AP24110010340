#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class StackSimulation {
private:
    int* stackArray;
    int capacity;
    int topIndex;

public:
    StackSimulation(int size) {
        capacity = size;
        stackArray = new int[capacity];
        topIndex = -1;
    }

    ~StackSimulation() {
        delete[] stackArray;
    }

    void clearScreen() {
        cout << "\033[2J\033[1;1H";
    }

    bool isFull() {
        return topIndex == capacity - 1;
    }

    bool isEmpty() {
        return topIndex == -1;
    }

    void push(int value) {
        if (isFull()) {
            cout << "\n ERROR: Stack Overflow! Cannot push " << value << "\n";
            waitForInput();
        } else {
            stackArray[++topIndex] = value;
        }
    }

    void pop() {
        if (isEmpty()) {
            cout << "\n ERROR: Stack Underflow! Cannot pop from empty stack.\n";
            waitForInput();
        } else {
            cout << "\n SUCCESS: Popped value " << stackArray[topIndex--] << "\n";
            waitForInput();
        }
    }

    void peek() {
        if (isEmpty()) {
            cout << "\n STATUS: Stack is empty. No top element.\n";
        } else {
            cout << "\n STATUS: Top element is " << stackArray[topIndex] << "\n";
        }
        waitForInput();
    }

    int size() {
        return topIndex + 1;
    }

    void render() {
        clearScreen();
        cout << "========================================\n";
        cout << "    REAL-TIME STACK VISUALIZER v1.0    \n";
        cout << "========================================\n\n";

        cout << " Max Capacity: " << capacity << "\n";
        cout << " Current Size: " << size() << "\n\n";
        cout << "      STACK VISUALIZATION      \n";
        cout << "      -------------------      \n";

        if (isEmpty()) {
            for (int i = 0; i < 4; i++) {
                cout << "      |                 |      \n";
            }
            cout << "      |    (EMPTY)      |      \n";
        } else {
            for (int i = capacity - 1; i >= 0; i--) {
                if (i > topIndex) {
                    cout << "      |                 |      \n";
                } else {
                    cout << "      |  [" << setw(9) << stackArray[i] << "]  |";
                    if (i == topIndex) cout << " <--- TOP";
                    cout << "\n";
                }
            }
        }
        cout << "      -------------------      \n";
        cout << "      |                 |      \n";
        cout << "\n========================================\n";
    }

    void waitForInput() {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void run() {
        int choice, value;
        while (true) {
            render();
            cout << " 1. Push Element\n";
            cout << " 2. Pop Element\n";
            cout << " 3. Peek (View Top)\n";
            cout << " 4. Check Status (Empty/Full)\n";
            cout << " 5. Exit Application\n";
            cout << "========================================\n";
            cout << " Enter Operation Code: ";
            
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = 0;
            }

            switch (choice) {
                case 1:
                    cout << " Enter integer value to Push: ";
                    if (cin >> value) {
                        push(value);
                    } else {
                        cout << " Invalid input.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        waitForInput();
                    }
                    break;
                case 2:
                    pop();
                    break;
                case 3:
                    peek();
                    break;
                case 4:
                    cout << "\n STATUS REPORT:\n";
                    cout << " Is Empty? " << (isEmpty() ? "YES" : "NO") << "\n";
                    cout << " Is Full?  " << (isFull() ? "YES" : "NO") << "\n";
                    cout << " Slots Used: " << size() << " / " << capacity << "\n";
                    waitForInput();
                    break;
                case 5:
                    cout << "\n Exiting Simulation. Goodbye!\n";
                    return;
                default:
                    cout << "\n Invalid selection. Try again.\n";
                    waitForInput();
            }
        }
    }
};

int main() {
    int cap;
    cout << "\033[2J\033[1;1H";
    cout << "Initialize Stack Configuration\n";
    cout << "Enter Maximum Stack Capacity: ";
    while (!(cin >> cap) || cap <= 0) {
        cout << "Invalid capacity. Enter a positive integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    StackSimulation app(cap);
    app.run();

    return 0;
}
