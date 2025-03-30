
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const string ClienstFileName = "Clients.txt";


enum enMainMenuOption
{

	eClientsList = 1, eAddNewClients = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5,     eTransaction = 6,
	eExit = 7

};


enum enTranseactionMenuOption
{
	eDeposit = 1,
	eWithDraw = 2,
	eTotalBalances = 3,
	eMainMenu = 4 


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


vector<stClientData> LoadDataFromFileToVector(string);


void ShowMainMenu();


void ShowTransactionMenu();


vector<stClientData> vClients = LoadDataFromFileToVector(ClienstFileName);


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
	cout << "\nEnter your Option? [1 to 7]...";
	cin >> Option;

	while (cin.fail() || Option < 1 || Option >7)
	{

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input please Enter Avalide Option: ";
		cin >> Option;

	}


	return Option;

}


void GoBackToMainMenu()
{

	cout << "\nEnter Any key to go back to Main Menu...";
	system("pause>0");
	ShowMainMenu();

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


vector<stClientData> LoadDataFromFileToVector(string FileName)
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


void PrintClientRecord(stClientData Client)
{

	cout << left << "| " << setw(14) << Client.AccountNumber
		<< " | " << setw(8) << Client.PINCode
		<< " | " << setw(20) << Client.ClientName
		<< " | " << setw(12) << Client.PhoneNumber
		<< " | " << setw(15) << Client.AccountBalance << " |\n";

	cout << Line(85, '-') << endl;

}


void ShowClientsListScreen()
{

	DisplayHeaderClientsListScreen();

	for (stClientData& Cl : vClients)
		PrintClientRecord(Cl);

}


void ShowHeaderAddNewClientScreen()
{

	cout << Line(40, '-') << "\n";
	cout << Tab(1) << "Add New Client Screen\n";
	cout << Line(40, '-') << "\n";
	cout << "\nAdding New Client:\n\n";

}


bool FindClientByAccountNumber(string AccountNumber)
{

	for (stClientData& Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
			return true;

	return false;
}


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

//Overloding
bool FindClientByPINCode(string PinCode)
{

	for (stClientData& Cl : vClients)
		if (Cl.PINCode == PinCode)
			return true;

	return false;
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


string ConvertRecordToDataline(stClientData Client, string Seperetor = "#//#")
{

	string DataLine;

	DataLine += Client.AccountNumber + Seperetor
		+ Client.PINCode + Seperetor
		+ Client.ClientName + Seperetor
		+ Client.PhoneNumber + Seperetor
		+ to_string(Client.AccountBalance);

	return DataLine;

}


void AddClient()
{

	fstream ClientsFile;

	ClientsFile.open(ClienstFileName, ios::out | ios::app);

	if (ClientsFile.is_open())
	{

		ClientsFile << ConvertRecordToDataline(ReadNewClientData()) << endl;


		ClientsFile.close();

	}
	//Refresh vector
	vClients = LoadDataFromFileToVector(ClienstFileName);

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
	ShowHeaderAddNewClientScreen();
	AddNewClients();

}


void DispalyHeaderDeleteClientScreen()
{

	cout << Line(40, '-') << "\n";
	cout << Tab(1) << "Delete Client Number\n";
	cout << Line(40, '-') << "\n";


}


string ReadAccountNumber()
{
	string AccountNumber;
	cout << "\nEnter Account Number: ";
	cin >> AccountNumber;
	return AccountNumber;
}


bool PutMarkForDeleteClient(string AccountNumber)
{

	for (stClientData& Cl : vClients)
		if (Cl.AccountNumber == AccountNumber)
		{
			Cl.DeleteMark = true;
			return true;
		}
	return false;
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


void SaveDataToFile(string FileName)
{

	fstream ClientsFile;
	ClientsFile.open(ClienstFileName, ios::out);

	if (ClientsFile.is_open())
	{

		for (stClientData& Cl : vClients)
			if (Cl.DeleteMark != true)
				ClientsFile << ConvertRecordToDataline(Cl) << endl;


		ClientsFile.close();

	}
	vClients = LoadDataFromFileToVector(ClienstFileName);

}

//We use it Inside DeleteClientByAccountNumber Function -> Before Definition
void ShowDeleteClientScreen();


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
			PutMarkForDeleteClient(AccountNumber);
			SaveDataToFile(ClienstFileName);

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

	DispalyHeaderDeleteClientScreen();
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber);


}


void DispalyHeaderUpdateClientScreen()
{
	cout << Line(40) << "\n";
	cout << Tab(1) << "Update Client Screen\n";
	cout << Line(40) << "\n";

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

			SaveDataToFile(ClienstFileName);
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

	DispalyHeaderUpdateClientScreen();
	UpdateClients();


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
			SaveDataToFile(ClienstFileName);
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


void GobackTotranseactionMenu()
{
	cout << "\nEnter any key to go back to Transeaction Menu\n";
	system("pause>0");
	ShowTransactionMenu();

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
		<< " | " << setw(11) << Client.AccountBalance  << " | " << endl;
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


			DepositAmountToClientBalanceByAccountNumber(AccountNumber,Amount *-1);
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
		GobackTotranseactionMenu();
		break;

	case enTranseactionMenuOption::eWithDraw:
		ShowWithDrawScreen();
		GobackTotranseactionMenu();
		break;


	case enTranseactionMenuOption::eTotalBalances:
		ShowClientsBalancesScreen();
		GobackTotranseactionMenu();
		break;

	case enTranseactionMenuOption::eMainMenu:
		ShowMainMenu();
		break;



	}

}



void ShowTransactionMenu()
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


void PerformMainMenuOption(enMainMenuOption Option)
{
	system("cls");
	switch (Option)
	{
	case enMainMenuOption::eClientsList:
		ShowClientsListScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eAddNewClients:
		ShowAddNewClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eDeleteClient:
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eUpdateClient:
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eFindClient:
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eTransaction:
		ShowTransactionMenu();
		break;

	case enMainMenuOption::eExit:
		ShowEndScreen();
		break;


	}

}


void ShowMainMenu()
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
	cout << Tab(1) << "[7] Exit.\n";
	cout << Line(40) << endl;

	PerformMainMenuOption((enMainMenuOption)ReadMainMenuOption());
}


int main()
{

	ShowMainMenu();

	

	return 0;

}


