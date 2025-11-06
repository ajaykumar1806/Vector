#include "shopping.h"
#include "bank.h"
#include "bank.cpp"
#include "shopping.cpp"

int main() {
    Hdfc hdfc;
    Shopping shopping;
    int choice;
    float amt;

    while (true) {
        cout << "        MENU       \n";
        cout << "1. Add to Cart\n";
        cout << "2. View Cart\n";
        cout << "3. Delete Product\n";
        cout << "4. Proceed to Billing\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            shopping.addToCart();
            break;
        case 2:
            shopping.viewCart();
            break;
        case 3:
            shopping.deleteProduct();
            break;
        case 4: 
	    shopping.viewCart();
            if (shopping.getProductCount() == 0) {
                cout << "Your cart is empty!\n";
                break;
            }            
            if (shopping.payment(hdfc)) {
            	shopping.resetCart();
            }
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice!\n";
        }
    }
}

