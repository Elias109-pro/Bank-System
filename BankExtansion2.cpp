
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string ClienstFileName = "Clients.txt";


const string UserFileName = "Users.txt";


enum enMainMenuOption
{

	eClientsList  = 1    , eAddNewClients = 2,
	eDeleteClient = 3    , eUpdateClient  = 4,
	eFindClient   = 5    , eTransaction   = 6,
	eManageUsers  = 7    , Logout         = 8

};


enum enTranseactionMenuOption
{
	eDeposit = 1,
	eWithDraw = 2,
	eTotalBalances = 3,
	eMainMenu = 4


};


enum enManageUsersOption
{

	eUsersList  = 1  ,  eAddNewUsers = 2,

	eDeleteUser = 3  ,  eUpdateUser  = 4,

	eFindUser   = 5  ,  enMainMenu    = 6

};


enum enSystemPermissions
{
	pClientlist = 1, pAddNewClient = 2,

	pDeleteClient = 4, pUpdateClient = 8,

	pFindClient = 16, pTranseaction = 32,

	pManageUser = 64, pAll = -1

};



struct stClientData
{

	string AccountNumber;
	string PINCode;
	string ClientName;
	string PhoneNumber;
	double AccountBalance;
	bool DeleteMark = false;

};


struct stUserData
{

	string Username;
	string Password;
	int permissions;
	bool DeleteMark = false;

};


//Declaretion

vector<stClientData> LoadClientsDataFromFileToVector(string);

vector<stUserData> LoadUsersDataFromFileToVector(string);

void Show_MainMenu();

void ShowTransaction_Menu();

void ShowManageUsers_Menu();

void ShowDeleteClientScreen();

void Login();

////////


/// Global
vector<stClientData> vClients = LoadClientsDataFromFileToVector(ClienstFileName);

vector<stUserData> vUsers = LoadUsersDataFromFileToVector(UserFileName);

stUserData CurrentUser;

/// 


string Line(short LineLength, char LineType = '=')
{

	string line = "";
	for (short i = 0; i < LineLength; i++)
		line += LineType;

	return line;

}


string Tab(short TabNumber)
{

	string tab = "";
	for (short i = 0; i < TabNumber; i++)
		tab += "\t";

	return tab;

}


short ReadMainMenuOption()
{
	short Option = 0;
	cout << "\nEnter your Option? [1 to 8]...";
	cin >> Option;

	while (cin.fail() || Option < 1 || Option > 8)
	{

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input please Enter Avalide Option: ";
		cin >> Option;

	}


	return Option;

}


void GoBackTo_MainMenu()
{

	cout << "\nEnter Any key to go back to Main Menu...";
	system("pause>0");
	Show_MainMenu();

}


void GoBackTo_ManageUsersMenu()
{

	cout << "\nEnter Any key to go back to Manage User Screen...";
	system("pause>0");
	ShowManageUsers_Menu();

}


void GobackTo_TranseactionMenu()
{
	cout << "\nEnter any key to go back to Transeaction Menu\n";
	system("pause>0");
	ShowTransaction_Menu();

}


vector <string> SplitString(string DataLine, string Seperetor = "#//#")
{
	short Pos = 0;
	vector<string> vClients;
	string sWord;

	while ((Pos = DataLine.find(Seperetor)) != string::npos)
	{
		sWord = DataLine.substr(0, Pos);

		if (sWord != "")
			vClients.push_back(sWord);

		DataLine.erase(0, Pos + Seperetor.length());
	}

	if (DataLine != "")
		vClients.push_back(DataLine);

	return vClients;

}


stClientData ConvertDataLineToRecord(string DataLine)
{

	vector <string> vClients = SplitString(DataLine);
	stClientData Client;

	Client.AccountNumber = vClients.at(0);
	Client.PINCode = vClients.at(1);
	Client.ClientName = vClients.at(2);
	Client.PhoneNumber = vClients.at(3);
	Client.AccountBalance = stod(vClients.at(4));

	return Client;
}


stUserData ConvertUserDataLineToRecord(string DataLine)
{
	stUserData UserRecord;
	vector<string> vUser = SplitString(DataLine);

	UserRecord.Username = vUser.at(0);
	UserRecord.Password = vUser.at(1);
	UserRecord.permissions = stoi(vUser.at(2));

	return UserRecord;

}


string ConvertClientRecordToDataline(stClientData Client, string Seperetor = "#//#")
{

	string DataLine;

	DataLine += Client.AccountNumber + Seperetor
		+ Client.PINCode + Seperetor
		+ Client.ClientName + Seperetor
		+ Client.PhoneNumber + Seperetor
		+ to_string(Client.AccountBalance);

	return DataLine;

}


string ConvertUserRecordToDataLine(stUserData User, string Seperetor = "#//#")
{
	string UserString = "";

	UserString += User.Username + Seperetor
		+ User.Password + Seperetor
		+ to_string(User.permissions);

	return UserString;
}


vector<stClientData> LoadClientsDataFromFileToVector(string FileName)
{
	vector<stClientData> vClients;
	fstream ClientsFile;
	ClientsFile.open(FileName, ios::in);

	if (ClientsFile.is_open())
	{
		string FileLine;

		while (getline(ClientsFile, FileLine))
		{

			vClients.push_back(ConvertDataLineToRecord(FileLine));

		}

		ClientsFile.close();

	}
	return vClients;
}


vector<stUserData> LoadUsersDataFromFileToVector(string FileName)
{

	vector<stUserData> vUsers;
	fstream UsersFileVariable;

	UsersFileVariable.open(FileName, ios::in);

	if (UsersFileVariable.is_open())
	{
		string Line;
		while (getline(UsersFileVariable, Line))
		{

			vUsers.push_back(ConvertUserDataLineToRecord(Line));

		}
		UsersFileVariable.close();
	}
	
	return vUsers;

}



void DisplayHeaderClientsListScreen()
{

	cout << Line(85) << "\n";
	cout << Tab(3) << "Clients List (" << vClients.size() << ") Client(S).\n";
	cout << Line(85) << "\n";
	cout << left << "| " << setw(10) << "Account Number"
		<< " | " << setw(8) << "PIN Code"
		<< " | " << setw(20) << "Client Name"
		<< " | " << setw(12) << "Phone Number"
		<< " | " << setw(15) << "Account Balance" << " |\n";
	cout << Line(85) << endl;

}


void DisplayHeaderAddNewUsersScreen()
{

	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Add New Users Screen\n";
	cout << Line(40, '_') << "\n";

}


void DisplayHeaderDeleteClientScreen()
{

	cout << Line(40, '-') << "\n";
	cout << Tab(1) << "Delete Client Number\n";
	cout << Line(40, '-') << "\n";


}


void DisplayHeaderAddNewClientScreen()
{

	cout << Line(40, '-') << "\n";
	cout << Tab(1) << "Add New Client Screen\n";
	cout << Line(40, '-') << "\n";
	cout << "\nAdding New Client:\n\n";

}


void DisplayHeaderUserslistScreen()
{
	cout << Line(50) << "\n";
	cout << Tab(2) << "Users List (" << vUsers.size() << ") User(s)\n";
	cout << Line(50) << "\n";

	cout << left << "| " << setw(20) << "User Name"
		<< " | " << setw(10) << "Password"
		<< " | " << setw(10) << "Permissions"
		<< "| \n";
	cout << Line(50) << endl;
}



void PrintClientRecord(stClientData Client)
{

	cout << left << "| " << setw(14) << Client.AccountNumber
		<< " | " << setw(8) << Client.PINCode
		<< " | " << setw(20) << Client.ClientName
		<< " | " << setw(12) << Client.PhoneNumber
		<< " | " << setw(15) << Client.AccountBalance << " |\n";

	cout << Line(85, '-') << endl;

}


void PrintUserRecord(stUserData User)
{
	cout << left << "| " << setw(20) << User.Username
		<< " | " << setw(10) << User.Password
		<< " | " << setw(10) << User.permissions << " | \n";

	cout << Line(50, '_') << "\n";

}


void ShowClientsListScreen()
{

	DisplayHeaderClientsListScreen();

	for (stClientData& Cl : vClients)
		PrintClientRecord(Cl);

}


void ShowAllUsers()
{

	if (vUsers.size() == 0)
	{
		cout << Tab(2) << "\nNo Users Found!\n";
		return;
	}

	for (stUserData &Us : vUsers)
	{
		PrintUserRecord(Us);
	}

}


void ShowUsersListScreen()
{
	DisplayHeaderUserslistScreen();
	ShowAllUsers();
}



bool FindClientByAccountNumber(string AccountNumber)
{

	for (stClientData& Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
			return true;

	return false;
}

//Overloding
bool FindClientByAccountNumber(string AccountNumber, stClientData& Client)
{

	for (stClientData& Cl : vClients)
	{
		if (Cl.AccountNumber == AccountNumber)
		{
			Client = Cl;
			return true;
		}
	}
	return false;

}


bool FindUserByUserNameAndPassword(string Username,string Password,stUserData &User)
{

	for(stUserData Us : vUsers)
		if (Us.Username == Username && Us.Password == Password)
		{
			User = Us;
			return true;
		}
	return false;
}


bool FindUserByUserName(string UserName)
{

	for (stUserData& Us : vUsers)
		if (Us.Username == UserName)
			return true;

	return false;
}


bool FindUserByUserName(string Username,stUserData &User)
{

	for (stUserData Us : vUsers)
	{
		if (Us.Username == Username)
		{
			User = Us;
			return true;
		}
	}
	return false;

}


bool FindClientByPINCode(string PinCode)
{

	for (stClientData& Cl : vClients)
		if (Cl.PINCode == PinCode)
			return true;

	return false;
}


bool CheckAccessPermission(enSystemPermissions Permission)
{
	return (CurrentUser.permissions & Permission) == Permission;
}


stClientData ReadNewClientData()
{
	stClientData NewClient;

	printf("Enter Account Number: ");
	getline(cin >> ws, NewClient.AccountNumber);

	while (FindClientByAccountNumber(NewClient.AccountNumber))
	{

		cout << "\nAccount Number is alrady used Enter another one: ";
		getline(cin >> ws, NewClient.AccountNumber);

	}

	printf("Enter PIN Code: ");
	getline(cin, NewClient.PINCode);
	while (FindClientByPINCode(NewClient.PINCode))
	{

		cout << "PIN Code is alrady used Enter another one: ";
		getline(cin, NewClient.PINCode);

	}

	printf("Enter Client Name: ");
	getline(cin, NewClient.ClientName);

	printf("Enter Phone Number: ");
	getline(cin, NewClient.PhoneNumber);

	printf("Enter Account Balance: ");
	cin >> NewClient.AccountBalance;

	return NewClient;

}


void AddClient()
{

	fstream ClientsFile;

	ClientsFile.open(ClienstFileName, ios::out | ios::app);

	if (ClientsFile.is_open())
	{

		ClientsFile << ConvertClientRecordToDataline(ReadNewClientData()) << endl;


		ClientsFile.close();

	}
	//Refresh vector
	vClients = LoadClientsDataFromFileToVector(ClienstFileName);

}


void AddNewClients()
{

	char AddMore = 'Y';
	do
	{


		AddClient();
		cout << "\nClient Adding Successfully\n";

		cout << "Do you want to add more? (N/Y)...";
		cin >> AddMore;


	} while (toupper(AddMore) == 'Y');


}


void ShowAddNewClientScreen()
{
	DisplayHeaderAddNewClientScreen();
	AddNewClients();

}


int ReadPermissionsToSet()
{
	int Permissions = 0;
	char GiveAccess;

	cout << "\nDo you want to give User Full Access on System? [N/Y]...";
	cin >> GiveAccess;

	if (toupper(GiveAccess) == 'Y')
		return -1;

	string arrPermissionsOption[] = { "","Client List","Add Client","Delete Client","Update Client","Find Client","Transeaction","Manage Users" };

	cout << "\nDo You want to give access to:\n";

	for (short i = 1; i <= 7; i++)
	{
		cout << arrPermissionsOption[i] << "?[Y/N]...";
		cin >> GiveAccess;

		Permissions += (toupper(GiveAccess) == 'Y') ? pow(2, i - 1) : 0;

	}

	return Permissions;

}


stUserData ReadNewUserData()
{

	stUserData User;

	cout << "\nEnter Username : ";
	getline(cin >> ws, User.Username);

	while (FindUserByUserName(User.Username))
	{

		cout << "\nUser With Name [" << User.Username << "] is already exists.\nEnter Another one: ";
		getline(cin >> ws, User.Username);

	}

	cout << "Enter User Password: ";
	cin >> User.Password;

	User.permissions = ReadPermissionsToSet();

	return User;
}


bool AddUser(string UserFile)
{

	fstream UserFileVariable;

	UserFileVariable.open(UserFile, ios::out | ios::app);

	if (UserFileVariable.is_open())
	{

		UserFileVariable << ConvertUserRecordToDataLine(ReadNewUserData()) << endl;

		UserFileVariable.close();
		vUsers = LoadUsersDataFromFileToVector(UserFileName);

		return true;

	}



	return false;

}


void AddUsers()
{

	char AddMore = 'N';

	do
	{
		if (toupper(AddMore) == 'Y')
		{
			system("cls");
			DisplayHeaderAddNewUsersScreen();
		}

		cout << "\nAdding New User: \n";
		AddUser(UserFileName);

		cout << "\nClient Added Successfully.\nDo You Want to Add More? [Y/N]...";
		cin >> AddMore;


	} while (toupper(AddMore) == 'Y');

}


void ShowAddNewUsersScreen()
{
	DisplayHeaderAddNewUsersScreen();
	AddUsers();

}



string ReadAccountNumber()
{
	string AccountNumber;
	cout << "\nEnter Account Number: ";
	cin >> AccountNumber;
	return AccountNumber;
}


string ReadUsername()
{
	string Username;
	cout << "\nPlease Enter Username: ";
	getline(cin >> ws, Username);
	return Username;
}


void PrintClientCard(stClientData Client)
{
	cout << "\nThe Following are the client details:\n";
	cout << Line(50, '_');
	cout << "\nAccount Number: " << Client.AccountNumber;
	cout << "\nPIN Code      : " << Client.PINCode;
	cout << "\nClient Name   : " << Client.ClientName;
	cout << "\nPhone Number  : " << Client.PhoneNumber;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n" << Line(50, '_') << endl;

}


void PrintUserCard(stUserData User)
{
	cout << "\nUser Card: \n";
	cout << Line(40, '_') << "\n";

	cout << "User Name    : " << User.Username;
	cout << "\nPassword   : " << User.Password;
	cout << "\nPermissions: " << User.permissions;
	
	cout << "\n" << Line(40, '_') << "\n";

}



bool PutMarkForDelete_Client(string AccountNumber)
{

	for (stClientData& Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
		{
			Cl.DeleteMark = true;
			return true;
		}
	return false;
}


bool PutMarkForDelete_User(stUserData User)
{
	for(stUserData &Us : vUsers)
		if (Us.Username == User.Username)
		{
			Us.DeleteMark = true;
			return true;
		}
	return false;
}


void SaveClientsDataToFile(string FileName)
{

	fstream ClientsFile;
	ClientsFile.open(ClienstFileName, ios::out);

	if (ClientsFile.is_open())
	{

		for (stClientData& Cl : vClients)
			if (Cl.DeleteMark != true)
				ClientsFile << ConvertClientRecordToDataline(Cl) << endl;


		ClientsFile.close();

	}
	vClients = LoadClientsDataFromFileToVector(ClienstFileName);

}


void SaveUserDataToFile(string FileName)
{
	fstream FileVariable;

	FileVariable.open(FileName, ios::out);

	if (FileVariable.is_open())
	{
		for (stUserData Us : vUsers)
			if (Us.DeleteMark != true)
				FileVariable << ConvertUserRecordToDataLine(Us) << endl;

		FileVariable.close();
	}
}


bool DeleteClientByAccountNumber(string AccountNumber)
{

	stClientData ClientToDelete;
	char Answer;

	if (FindClientByAccountNumber(AccountNumber, ClientToDelete))
	{
		PrintClientCard(ClientToDelete);
		cout << "\nAre sure you want to Delete this Client? (N/Y)....";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			PutMarkForDelete_Client(AccountNumber);
			SaveClientsDataToFile(ClienstFileName);

			cout << "\nClient has been Deleted Successfully.\n\nDo Want to Delete More? (Y/N)...";
			cin >> Answer;
			if (toupper(Answer) == 'Y')
			{
				system("cls");
				ShowDeleteClientScreen();
			}
			else
				return true;


		}
		else
			cout << "\nThe Request has been Canceld.\n";

	}
	else
	{
		cout << "\nAccount Number Not Found.\n";
		cout << "\nDo you want to Enter another one? (N/Y)..."; \
			cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			system("cls");
			ShowDeleteClientScreen();
		}

	}
	return false;

}


void ShowDeleteClientScreen()
{

	DisplayHeaderDeleteClientScreen();
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber);


}


void DisplayHeaderDeleteUserScreen()
{

	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Delete Users Screen\n";
	cout << Line(40, '_') << "\n";

}


void ImplementDeleteUser(stUserData User)
{

	PutMarkForDelete_User(User);
	SaveUserDataToFile(UserFileName);
	vUsers = LoadUsersDataFromFileToVector(UserFileName);

}


void DeleteUser()
{

	stUserData UserForDelete;
	char Acception = 'N';


	if (FindUserByUserName(ReadUsername(), UserForDelete))
	{

		if (UserForDelete.Username == "Admin" || UserForDelete.Username == CurrentUser.Username)
		{
			cout << "\nYou can't Delete this User.";
			return;
		}

		PrintUserCard(UserForDelete);
		cout << "\nAre yiu Sure You want To Delete this User?[N/Y]...";
		cin >> Acception;

		if (toupper(Acception) == 'Y')
		{
			ImplementDeleteUser(UserForDelete);
			cout << "\nUser Deleted Successfully.\n";

		}
		else
			cout << "\nThe request has been canceld.\n";
	}

	else
	{
		cout << "\nUser Not Found!\nDo you want to Enter Another One?[N/Y]...";
		cin >> Acception;

		if (toupper(Acception) == 'Y')
		{
			system("cls");
			DisplayHeaderDeleteUserScreen();
			DeleteUser();
		}
	}

}


void ShowDeleteUserScreen()
{
	DisplayHeaderDeleteUserScreen();
	DeleteUser();

}



void DisplayHeaderUpdateClientScreen()
{
	cout << Line(40) << "\n";
	cout << Tab(1) << "Update Client Screen\n";
	cout << Line(40) << "\n";

}


void DisplayHeaderUpdateUserScreen()
{
	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Update User Screen\n";
	cout << Line(40, '_') << "\n";
}


stClientData ChangeClientDataRecord(string AccouontNumber)
{
	stClientData Client;
	Client.AccountNumber = AccouontNumber;

	printf("\nEnter PIN Code: ");
	getline(cin >> ws, Client.PINCode);

	printf("Enter Client Name: ");
	getline(cin, Client.ClientName);

	printf("Enter Phone Number: ");
	getline(cin, Client.PhoneNumber);

	printf("Enter Account Balance: ");
	cin >> Client.AccountBalance;

	return Client;

}


bool UpdateClientDataByAccountNumber(string AccountNumber)
{

	stClientData Client;
	char Answer;


	if (FindClientByAccountNumber(AccountNumber, Client))
	{

		PrintClientCard(Client);
		cout << "\nDo want to update this Client data? (N/Y)...";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{

			for (stClientData& Cl : vClients)
				if (Cl.AccountNumber == AccountNumber)
				{
					Cl = ChangeClientDataRecord(AccountNumber);
					break;
				}

			SaveClientsDataToFile(ClienstFileName);
			cout << "\n\nData Changed Successfully.";

			return true;

		}

	}
	else
	{
		cout << "\nClient with Account (" << AccountNumber << ") is Not found\n\nDo you want to Enter Onther one? (N/Y)...";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			UpdateClientDataByAccountNumber(ReadAccountNumber());
		}
		else
			cout << "\nThe Request has been Canceld.";
		return false;

	}

}


void UpdateClients()
{

	string AccountNumber = ReadAccountNumber();
	UpdateClientDataByAccountNumber(AccountNumber);


}


void ShowUpdateClientScreen()
{

	DisplayHeaderUpdateClientScreen();
	UpdateClients();


}


stUserData ChangeUserDataRecord(stUserData User)
{
	stUserData UserUpdate;

	UserUpdate.Username = User.Username;

	cout << "Enter User Password: ";
	cin >> UserUpdate.Password;

	UserUpdate.permissions = ReadPermissionsToSet();

	return UserUpdate;

}


void UpdateUserByUserName(string Username)
{

	stUserData User;
	char Acception;

	if (FindUserByUserName(Username, User))
	{

		PrintUserCard(User);

		cout << "\nAre you Sure you want to Update this user?[N/Y]...";
		cin >> Acception;


		if (toupper(Acception) == 'Y')
		{



			for (stUserData& Us : vUsers)
			{
				if (Us.Username == User.Username)
				{
					Us = ChangeUserDataRecord(Us);
					break;
				}
			}

			SaveUserDataToFile(UserFileName);
			LoadUsersDataFromFileToVector(UserFileName);


			cout << "\nUser Data Updated Successfully.\n";
		}
		else
			cout << "\nThe request has been canceld.\n";

	}
	else
	{
		cout << "\nUser Not Found!\nDo you want to enter Another User Name?[N/Y]...";
		cin >> Acception;

		if (toupper(Acception) == 'Y')
		{
			system("cls");
			DisplayHeaderUpdateUserScreen();
			UpdateUserByUserName(ReadUsername());

		}
	}


}


void ShowUpdateUserScreen()
{
	DisplayHeaderUpdateUserScreen();
	string Username = ReadUsername();
	UpdateUserByUserName(Username);
}



void DispalyHeaderFindScreen()
{
	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Find Client Screen\n";
	cout << Line(40, '_') << endl;
}


void ShowFindClientScreen()
{

	DispalyHeaderFindScreen();

	stClientData Client;
	string AccountNumber = ReadAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account (" << AccountNumber << ") is Not Found.\n";


}


void ShowEndScreen()
{

	cout << Line(40) << "\n";
	cout << Tab(1) << "End Of System\n";
	cout << Line(40) << "\n";

}


short ReadTranseactionOption()
{

	short Option = 0;
	cout << "\nEnter Your Option? [1 to 4]....";
	cin >> Option;
	while (cin.fail() || Option < 1 || Option >4)
	{

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input please Enter Avalide Option: ";
		cin >> Option;

	}

	return Option;

}


short ReadManageUsersOption()
{
	short Option;

	cout << "\nEnter Your Option? [1 to 5]....";
	cin >> Option;

	while (cin.fail() || Option < 1 || Option > 6)
	{

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input please Enter Avalide Option: ";
		cin >> Option;

	}

	return Option;

}


void DispalyHeaderDepositScreen()
{
	cout << Line(40, '-') << "\n";
	cout << Tab(1) << "Deposit Screen\n";
	cout << Line(40, '-') << "\n";
}


double ReadAmount()
{
	unsigned int Amount;
	//cout << "\nPlease Enter deposit amount: ";
	cin >> Amount;

	return Amount;

}


bool DepositAmountToClientBalanceByAccountNumber(string AccountNumber, double Balance)
{


	for (stClientData& Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
		{
			Cl.AccountBalance += Balance;
			SaveClientsDataToFile(ClienstFileName);
			return true;
		}
	return false;

}


bool DepositBalance()
{

	string AccountNumber = ReadAccountNumber();
	stClientData Client;
	char Answer;


	if (FindClientByAccountNumber(AccountNumber, Client))
	{
		PrintClientCard(Client);
		cout << "\nPlease Enter deposit Amount\n";
		double Amount = ReadAmount();

		cout << "\nAre you sure you want perform this transeaction? (N/Y)...";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{

			DepositAmountToClientBalanceByAccountNumber(AccountNumber, Amount);

			cout << "\nDone Successfully The new balnce is: " << Client.AccountBalance + Amount << "\n";
			return true;

		}
		else
		{
			cout << "\nThe request has been Canceld.\n";
			return false;
		}
	}
	else
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist\n\n";

		cout << "\nDo you want to Enter another Account? (N/Y)...";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
			DepositBalance();

		else
			cout << "\nThe Request has been canceld.";
	}




}


void ShowDepositScreen()
{

	DispalyHeaderDepositScreen();
	DepositBalance();

}


void DispalyHeaderClientsBalancesScreen()
{
	cout << Line(55) << "\n";
	cout << Tab(1) << "  Balances List (" << vClients.size() << ") Client(s).\n";
	cout << Line(55) << "\n";
	cout << left << "| " << setw(10) << "Account Number"
		<< " | " << setw(20) << "Client Name"
		<< " | " << setw(11) << "Balance " << " | " << endl;
	cout << Line(55) << "\n";


}


void PrintClientBalance(stClientData Client)
{

	cout << left << "| " << setw(14) << Client.AccountNumber
		<< " | " << setw(20) << Client.ClientName
		<< " | " << setw(11) << Client.AccountBalance << " | " << endl;
	cout << Line(55, '-') << "\n";
}


void ShowClientsBalancesScreen()
{

	double TotalBalances = 0;

	DispalyHeaderClientsBalancesScreen();

	if (vClients.size() == 0)
		cout << Tab(3) << "No Clients Available In the System\n";

	for (stClientData& Cl : vClients)
	{
		PrintClientBalance(Cl);
		TotalBalances += Cl.AccountBalance;
	}
	cout << "\n" << Tab(1) << "  Total Balances = " << TotalBalances << "\n";

}


void DisplayHeaderWithDrawScreen()
{
	cout << Line(40) << "\n";
	cout << Tab(1) << "WithDraw Screen\n";
	cout << Line(40) << "\n";

}


bool WithDrawFromClientAmount()
{


	string AccountNumber = ReadAccountNumber();
	stClientData Client;
	char Answer;


	while (!FindClientByAccountNumber(AccountNumber, Client))
	{

		cout << "\nClient with [" << AccountNumber << "] does not exist\n\n";
		WithDrawFromClientAmount();

	}

	PrintClientCard(Client);

	cout << "\nPlease Enter WithDraw Amount: ";
	double Amount = ReadAmount();


	while (Amount > Client.AccountBalance)
	{

		cout << "\nAmount Exceeds the balance ,you can withDraw up to : " << Client.AccountBalance << endl;
		cout << "\nPlease enter another amount: ";
		cin >> Amount;

	}

	cout << "\nAre you sure you want perform this transeaction? (N/Y)...";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{


		DepositAmountToClientBalanceByAccountNumber(AccountNumber, Amount * -1);
		cout << "\nDone Successfully The new balance is (" << Client.AccountBalance - Amount << ")\n";
		return true;

	}
	else
	{
		cout << "\nThe request has been Canceld.\n";
		return false;
	}


}


void ShowWithDrawScreen()
{

	DisplayHeaderWithDrawScreen();
	WithDrawFromClientAmount();
}


void PerformTranseactionMenuOption(enTranseactionMenuOption Option)
{
	system("cls");
	switch (Option)
	{

	case enTranseactionMenuOption::eDeposit:
		ShowDepositScreen();
		GobackTo_TranseactionMenu();
		break;

	case enTranseactionMenuOption::eWithDraw:
		ShowWithDrawScreen();
		GobackTo_TranseactionMenu();
		break;


	case enTranseactionMenuOption::eTotalBalances:
		ShowClientsBalancesScreen();
		GobackTo_TranseactionMenu();
		break;

	case enTranseactionMenuOption::eMainMenu:
		Show_MainMenu();
		break;

	}

}


void DisplayHeaderFindUserScreen()
{

	cout << Line(40, '_') << "\n";
	cout << Tab(1) << "Find User Screen\n";
	cout << Line(40, '_') << "\n";

}


void ShowFindUserScreen()
{
	DisplayHeaderFindUserScreen();

	stUserData User;
	string Username = ReadUsername();

	if (FindUserByUserName(Username, User))
	{
		PrintUserCard(User);
	}
	else
		cout << "\nUser Not Found.\n";

}


void PerformManageUserScreen(enManageUsersOption Option)
{
	system("cls");
	switch (Option)
	{

	case enManageUsersOption::eUsersList:
		ShowUsersListScreen();
		GoBackTo_ManageUsersMenu();
		break;

	case enManageUsersOption::eAddNewUsers:
		ShowAddNewUsersScreen();
		GoBackTo_ManageUsersMenu();
		break;
	case enManageUsersOption::eDeleteUser:
		ShowDeleteUserScreen();
		GoBackTo_ManageUsersMenu();
		break;

	case enManageUsersOption::eUpdateUser:
		ShowUpdateUserScreen();
		GoBackTo_ManageUsersMenu();
		break;

	case enManageUsersOption::eFindUser:
		ShowFindUserScreen();
		GoBackTo_ManageUsersMenu();
		break;
	case enManageUsersOption::enMainMenu:
		Show_MainMenu();

	}
}


void ShowTransaction_Menu()
{
	system("cls");
	cout << Line(40) << "\n";
	cout << Tab(1) << "Transaction Menu Screen\n";
	cout << Line(40) << "\n";

	cout << Tab(1) << "[1] Deposit\n";
	cout << Tab(1) << "[2] WithDraw\n";
	cout << Tab(1) << "[3] Total Balance\n";
	cout << Tab(1) << "[4] Main Menu\n";
	cout << Line(40) << "\n";

	PerformTranseactionMenuOption((enTranseactionMenuOption)ReadTranseactionOption());

}


void ShowManageUsers_Menu()
{

	system("cls");

	cout << Line(40) << "\n";
	cout << Tab(1) << "Manage User Screen\n";
	cout << Line(40) << "\n";

	cout << Tab(1) << "[1] Users List.\n";
	cout << Tab(1) << "[2] Add New Users.\n";
	cout << Tab(1) << "[3] Delete User.\n";
	cout << Tab(1) << "[4] Update User.\n";
	cout << Tab(1) << "[5] Find User.\n";
	cout << Tab(1) << "[6] Main Menu.\n";

	cout << Line(40) << "\n";

	PerformManageUserScreen((enManageUsersOption)ReadManageUsersOption());
}


void ShowAccessDeniedMessage()
{
	cout << Line(40, '-') << endl;
	cout << "Access Denied, \nYou Dont Have Permission To Do this,\nPlease Contact the Admin.\n";
	cout << Line(40, '-') << endl;
}


void PerformMainMenuOption(enMainMenuOption Option)
{
	system("cls");
	switch (Option)
	{
	case enMainMenuOption::eClientsList:
		
		if (!CheckAccessPermission(enSystemPermissions::pClientlist))
		{
			ShowAccessDeniedMessage();
			GoBackTo_MainMenu();
		}

		ShowClientsListScreen();
		GoBackTo_MainMenu();
		break;

	case enMainMenuOption::eAddNewClients:

		if (!CheckAccessPermission(enSystemPermissions::pAddNewClient))
		{
			ShowAccessDeniedMessage();
			GoBackTo_MainMenu();
		}

		ShowAddNewClientScreen();
		GoBackTo_MainMenu();
		break;

	case enMainMenuOption::eDeleteClient:

		if (!CheckAccessPermission(enSystemPermissions::pDeleteClient))
		{
			ShowAccessDeniedMessage();
			GoBackTo_MainMenu();
		}

		ShowDeleteClientScreen();
		GoBackTo_MainMenu();
		break;

	case enMainMenuOption::eUpdateClient:

		if (!CheckAccessPermission(enSystemPermissions::pUpdateClient))
		{
			ShowAccessDeniedMessage();
			GoBackTo_MainMenu();
		}

		ShowUpdateClientScreen();
		GoBackTo_MainMenu();
		break;
	case enMainMenuOption::eFindClient:

		if (!CheckAccessPermission(enSystemPermissions::pFindClient))
		{
			ShowAccessDeniedMessage();
			GoBackTo_MainMenu();
		}

		ShowFindClientScreen();
		GoBackTo_MainMenu();
		break;

	case enMainMenuOption::eTransaction:

		if (!CheckAccessPermission(enSystemPermissions::pTranseaction))
		{
			ShowAccessDeniedMessage();
			GoBackTo_MainMenu();
		}

		ShowTransaction_Menu();
		break;

	case enMainMenuOption::eManageUsers:

		if (!CheckAccessPermission(enSystemPermissions::pManageUser))
		{
			ShowAccessDeniedMessage();
			GoBackTo_MainMenu();
		}

		ShowManageUsers_Menu();
		break;

	case enMainMenuOption::Logout:
		Login();
		break;


	}

}


void Show_MainMenu()
{
	system("cls");
	cout << Line(40) << "\n";
	cout << Tab(1) << "Main Menu Screen.\n";
	cout << Line(40) << "\n";
	cout << Tab(1) << "[1] Clients List.\n";
	cout << Tab(1) << "[2] Add New Clients.\n";
	cout << Tab(1) << "[3] Delete Client.\n";
	cout << Tab(1) << "[4] Update Client Info.\n";
	cout << Tab(1) << "[5] Find Client.\n";
	cout << Tab(1) << "[6] Transaction.\n";
	cout << Tab(1) << "[7] Manage Users.\n";
	cout << Tab(1) << "[8] Logout.\n";
	cout << Line(40) << endl;

	PerformMainMenuOption((enMainMenuOption)ReadMainMenuOption());
}


void DisplayHeader_LoginScreen()
{
	cout << Line(30, '_') << "\n";
	cout << Tab(1) << "Login Screen\n";
	cout << Line(30, '_') << "\n";
}


bool LoadUserInfo(string UserName,string Password)
{
	return FindUserByUserNameAndPassword(UserName, Password, CurrentUser);
}


void Login()
{
	bool LoginFaild = false;
	string Username, Password;

	do
	{
		system("cls");
		DisplayHeader_LoginScreen();

		if (LoginFaild)
			cout << "\nInvalid Username/Password!";

		cout << "\nEnter Username: ";
		getline(cin >> ws, Username);

		cout << "Enter Password: ";
		cin >> Password;


		LoginFaild = !LoadUserInfo(Username,Password);


	} while (LoginFaild);

	Show_MainMenu();

}


int main()
{

	Login();

	return 0;

}