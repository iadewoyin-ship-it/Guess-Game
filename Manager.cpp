class Manager : public Person
{
private:
	int regNo;
	string name;
	int at_line;

public:
	//object to gamer class
	Gamer *gamer;
	// constructor should initialise name and registration number using arguments
	Manager(const string &name, int regNo) : Person(name){
		this->name = name;
		this->regNo = regNo;

		gamer = new Gamer();
	}
	Manager(){};

	// method to return registration number
	int getRegNo() const;

	//to reset game settings
	void resetGame(){
		easy_min = 0;
		easy_max = 10;

		medium_min = 0;
		medium_max = 100;

		hard_min = 0;
		hard_max = 1000;

		//to clear player records from gamer.txt file
		std::ofstream ofs;
		ofs.open("gamer.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		//to clear Manager records from ManagerRecord.txt file
		ofs.open("managers.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();

		cout << "\nGame Reset Operation Completed.";
	}

	//to change game level settings
	void changeLevel(){

		int choice;
		cout << "\n1) To change easy level range\n2) To change medium level range\n3) To change Hard level range";
		cout << "\nEnter your choice: ";
		cin >> choice;
		int range;
		switch (choice)
		{
		case 1:
			cout << "\nEnter Easy level minimum range: ";
			cin >> range;
			easy_min = range;
			cout << "\nEnter Easy level maximum range: ";
			cin >> range;
			easy_max = range;
			cout << "\nEasy Level settings updated!!";
			break;
		case 2:
			cout << "\nEnter Medium level minimum range: ";
			cin >> range;
			medium_min = range;
			cout << "\nEnter Medium level maximum range: ";
			cin >> range;
			medium_max = range;
			cout << "\nMedium Level settings updated!!";
			break;
		case 3:
			cout << "\nEnter Hard level minimum range: ";
			cin >> range;
			hard_min = range;
			cout << "\nEnter Hard level maximum range: ";
			cin >> range;
			hard_max = range;
			cout << "\nHard Level settings updated!!";
			break;
		default:
			cout << "\nInvalid Inputs!!";
			break;
		}
	}

	//function to check manager existence from managers.txt file
	bool isManagerFound(int reg_no){
		ifstream file;
		int line_no = 0;
		file.open("managers.txt");
		if (file.fail()){
			cout << "\nFailed to open file managers.txt!!";
			exit(1);
		}
		string line;
		int no = 0;
		while (getline(file, line)){
			line_no++;
			stringstream ss(line);
			string str = line;
			while (getline(ss, line, ',')){
				no = stoi(line);
				if (no == reg_no){
					this->at_line = line_no;
					int count = 0;
					stringstream ss(str);
					while (getline(ss, str, ',')){
						if (count == 0)
							this->regNo = stoi(str);
						else if (count == 1)
							this->name = str;
						break;
						count++;
					}
				}
				return true;
			}
			break;
		}

		file.close();
		return false;
	}

	//display manager menu
	void displayMangerMenu(){
		cout << "\n\n1) Reset Game (this will destroy existing data)\n2) Change game levels\n3) Change security key\n4)"
			<< " Add another manager\n5) Go to Main Menu \n6) Exit game";
		cout << "\nEnter your choice(1-6): ";
	}

	void saveManagerData(){
		ofstream file;
		file.open("managers.txt", ios::app);
		if (file.fail()){
			cout << "\nFile not found gamer.txt !!";
			exit(1);
		}
		file << this->regNo << "," << this->name << endl;
		cout << "\nManager Data saved successfully!!" << endl;
		file.close();
	}

	//change security key
	void changeSecurityKey(){
		int key = 0;
		if (security_key!= -1){
			cout << "\nEnter existing security key: ";
			cin >> key;
			if (key == security_key){
				cout << "\nEnter new security key: ";
				cin >> key;
				else if (key != security_key)
				{
					cout << "\nEnter existing security key"/* code */
				}
				else
				security_key = key;
				cout << "\nSecurity Key changed successfully!!";
				return;
			}
			else
				cout << "\nInvalid security key, key cannot be chnaged!!";
		}
		cout << "\nEnter new security key: ";
		cin >> key;
		security_key = key;
		cout << "\nSecurity Key changed successfully!!";

	}

	void addAnotherManager(){
		int reg_no;
		string name;

		ofstream file;
		file.open("managers.txt", ios::app);
		if (file.fail())
		{
			cout << "\nFile opening failed ManagerRecord.txt !!";
			exit(1);
		}
		cout << "\nEnter Manager registration number: ";
		cin >> reg_no;
		if (isManagerFound(reg_no))
		{
			cout << "\nManager already exist!!";
			return;
		}
		cout << "\nEnter Manager Name: ";
		cin >> name;
		file << reg_no << "," << name << endl;
		cout << "\nManager Data saved successfully!!" << endl;
	}

};
