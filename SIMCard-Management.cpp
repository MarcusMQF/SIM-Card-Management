#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;


class SIMCard{
    private:
        string phoneNumber;
        string ownerNIC;
        string simType;
        double balance;
        double dataBalance;
        bool isActive;

    public:
        SIMCard(string phoneNumber, string ownerNIC, string simType, double initialBalance, double initialData):
            phoneNumber(phoneNumber), ownerNIC(ownerNIC), simType(simType), balance(initialBalance), dataBalance(initialData), isActive(false) {} 
        string getPhoneNumber() const {return phoneNumber;}

        bool activate(){
            isActive = true;
            cout << "SIM Card with number " << phoneNumber << " has been activated." << endl;
            return isActive;
        }

        bool deactivate(){
            isActive = false;
            cout << "SIM Card with number " << phoneNumber << " has been deactivated." << endl;
            return isActive;
        }

        void addBalance(double amount){
            balance += amount;
            cout << "Balance of " << amount << " has been added to SIM Card " << phoneNumber << "." << endl << "Current Balance: " << balance << endl;
        }

        void CheckBalance(){
            cout << "Balance of SIM Card " << phoneNumber << ": " << balance << endl;
        }

        void transferOwnership(string newNIC){
            ownerNIC = newNIC;
            cout << "Ownership of SIM Card " << phoneNumber << " has been transfereed to " << newNIC << "." << endl;

        }

        void checkActivationStatus(){
            string status = isActive ? "Active" : "Inactive";
            cout << "SIM Card " << phoneNumber << " is " << status << "." << endl;
        }

        void deductDataUsage(double dataUsed){
            if(dataUsed > dataBalance){
                cout << "Insufficient Data Balance for SIM Card " << phoneNumber << "." << endl;
            }else{
                dataBalance -= dataUsed;
                cout << "Data usage of " << dataUsed << " has been deducted from SIM Card " << phoneNumber << "." << endl << "Remaining Data Balance: " << dataBalance << endl;
            }
        }

        void rechargeData(double dataAmount){
            dataBalance += dataAmount;
            cout << "Data Balance of " << dataAmount << " has been added to SIM Card " << phoneNumber << "." << endl << "Current Data Balance: " << dataBalance << endl;
        }
};

void clearInputBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(){
    vector<SIMCard> simCard;
    int choice; 
    char action;
    string phoneNumber, ownerNIC, simType;
    double initialBalance, initialData, amount, dataUsed, dataAmount;

    do{
        cout << endl << "[SIM MANAGEMENT SYSTEM]" << endl << endl;
        cout << "1. Make a new SIM Card" << endl;
        cout << "2. Add Balance" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Transfer Ownership" << endl;
        cout << "5. Activate/Deactivate SIM Card" << endl;
        cout << "6. Check Activation Status" << endl;
        cout << "7. Deduct mobile data usage" << endl;
        cout << "8. Recharge Mobile Data" << endl;
        cout << "9. Exit" << endl << endl;
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        switch(choice){
            case 1:
                clearInputBuffer();
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);

                cout << "Enter owner NIC: ";
                getline(cin, ownerNIC);

                cout << "Enter SIM type: ";
                getline(cin, simType);

                cout << "Enter initial balance: ";
                cin >> initialBalance;

                cout << "Enter initial data balance (Type 0 if not data SIM): ";
                cin >> initialData;
                simCard.emplace_back(phoneNumber, ownerNIC, simType, initialBalance, initialData);
                
                cout << "New SIM Card created succesfully" << endl;
                clearInputBuffer();
                break; 
            
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            {
                clearInputBuffer();
                if(simCard.empty()){
                    cout << "No SIM Card available. Please create a SIM Card first." << endl;
                    break;
                }
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                
                bool found = false;

                for(auto &sim : simCard){
                    if(sim.getPhoneNumber() == phoneNumber){
                        found = true;
                        switch(choice){
                            case 2:
                                cout << "Enter amount to add: ";
                                cin >> amount;
                                cout << "Added successfully." << endl;
                                sim.addBalance(amount);
                                clearInputBuffer();
                                break;

                            case 3:
                                sim.CheckBalance();
                                break;

                            case 4:
                                cout << "Enter new owner NIC: ";
                                getline(cin, ownerNIC);
                                sim.transferOwnership(ownerNIC);
                                break;

                            case 5:
                                cout << "a. Activate SIM Card" << endl;
                                cout << "b. Deactivate SIM Card" << endl;
                                cout << "Choose your action (a/b): ";
                                cin >> action;
                                clearInputBuffer();

                                if(action == 'a'){
                                    sim.activate();
                                }else if(action == 'b'){
                                    sim.deactivate();
                                }else{
                                    cout << "Invalid action." << endl;
                                }
                                break;

                            case 6:
                                sim.checkActivationStatus();
                                break;
                            
                            case 7: 
                                cout << "Enter data usage: ";
                                cin >> dataUsed;
                                sim.deductDataUsage(dataUsed);
                                clearInputBuffer();
                                break;
                            
                            case 8:
                                cout << "Enter data amount to recharge: ";
                                cin >> dataAmount;
                                sim.rechargeData(dataAmount);
                                clearInputBuffer();
                                break;
                        }
                        break;
                    }
                }

                /*for(auto &sim: simCard){
                    if(sim.getPhoneNumber() != phoneNumber){
                        bool found = false;
                        cout << "SIM Card with number " << phoneNumber << " not found." << endl;
                    }
                    break;
                }*/
               
                if(!found){
                    cout << "SIM Card with number " << phoneNumber << " not found." << endl;
                }
                break;
            }
            
            case 9:
                cout << endl << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice. Please Try Again." << endl;
                break;
        }

        cout << endl << "Press Enter to continue...";
        cin.get();
        system("cls");

    }while(choice != 9);

    return 0;
}