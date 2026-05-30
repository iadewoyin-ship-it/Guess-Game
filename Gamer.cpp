#include <string>

using namespace std;

class Gamer : public Person
{

private:
	int regNo;
	string name;
	//associated level of difficulty 
	string difficulty;
	float score;
	int at_line;

public:

	//public default constructor
	Gamer(){
	
		this->setScore(0);
		this->setDifficulty("Nan");

		easy_min = 0;
		easy_max = 10;

		medium_min = 0;
		medium_max = 100;

		hard_min = 0;
		hard_max = 1000;

		security_key = -1;
		at_line = -1;
	};

	// constructor should initialise name and registration number using arguments
	// and initialise score map to be empty
	Gamer(string name, int regNo) :Person(name){
		this->name = name;
		this->regNo = regNo;
		at_line = -1;
	}

	

	//play game method
	void playGame(){
		int rand_num = 0;
		int input = 0;
		string diff_level = "";
		if (this->difficulty.compare("easy") == 0){
			rand_num = rand() % easy_max + easy_min;
			diff_level = "Easy";
			cout << "\nYou have to Guess a Number between 0 and 10";
		}
		else if (this->difficulty.compare("medium") == 0){
			rand_num = rand() % medium_max + medium_min;
			diff_level = "Medium";
			cout << "\nYou have to Guess a Number between 0 and 100";
		}
		else{
			rand_num = rand() % hard_max + hard_min;
			diff_level = "Hard";
			cout << "\nYou have to Guess a Number between 0 and 1000";
		}
		cout << "\nYour Difficulty Level is " << diff_level;
		while (true){
			cout << "\n\nEnter your Guess: ";
			cin >> input;
			if (input == rand_num){
				cout << "\nGreat, you win!!";
				score++;
				cout << "\nYour score is: " << score;
				break;
			}
			else if (input < rand_num)
				cout << "\nEnter a greater number than " << input;
			else if (input>rand_num)
				cout << "\nEnter a smaller number than " << input;
		}
	}

	// method to return registration number
	int getRegNo() {
		return this->regNo;
	};

	//get difficulty
	string getDifficulty(){
		return this->difficulty;
	}

	//set difficulty
	void setDifficulty(string d){
		this->difficulty = d;
	}
	//set score 
	void setScore(float score){
		this->score = score;
	}
	//get score 
	int getScore(){
		return this->score;
	}
	// method to add the score to the map
	// if a score for the module is already present it should be overwritten
	void addScore(float score, string difficulty);

	// method to retrieve the score
	// should throw NoScoreException if gamer has no score yet
	// it should display the score based on the levels of difficulty the gamer player
	float getHighestScore(string difficulty) const;

	//set name
	void setName(string name){
		this->name = name;
	}
	//get name
	string getName(){
		return this->name;
	}
	//set reg no
	void setRegNo(int reg_no){
		this->regNo = reg_no;
	}
	
	//to display game menu
	void displayGameMenu(){
		cout << "\n\n1) Play Game\n2) Your Statistics\n3) Display top 10\n4) Go to Main Menu\n5) Exit & Save" << endl;
		cout << "\nEnter Your choice (1-5): ";
	}
	static void setSecurityKey(int key);
	static int getSecurityKey();
	//function to check gamer existence from gamer.txt file
	bool isPlayerFound(int reg_no){
		ifstream file;
		int line_no = 0;
		file.open("gamer.txt");
		if (file.fail()){
			cout << "\nFailed to open file gamer.txt!!";
			exit(1);
		}
		string line;
		int no = 0;
		while (getline(file, line)){
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
							this->setRegNo(stoi(str));
						else if (count == 1)
							this->setName(str);
						else if (count == 2)
							this->setScore(stof(str));
						else{
							this->setDifficulty(str);
							break;
						}
						count++;
					}
					return true;
				}
				break;
			}
			line_no++;
		}
		file.close();
		return false;
	}
	//display player statistics
	void displayStatistics(){
		cout << "\nPlayer Registration Number: " << this->getRegNo();
		cout << "\n\nPlayer Name: " << this->getName();
		cout << "\n\nPlayer Score: " << this->getScore();
		cout << "\n\nPlayer Difficulty Level: " << this->getDifficulty() << endl;
	}

	//function to display top 10
	void displayTopTen(){
		ifstream file;
		int line_no = 0;
		file.open("gamer.txt");
		if (file.fail()){
			cout << "\nNo record to display yet!!";
			return;
		}
		string line;
		int no = 0;
		int scoreArr[1000];
		while (getline(file, line)){
			stringstream ss(line);
			string str = line;
			while (getline(ss, line, ',')){
				scoreArr[line_no] = stoi(line);
				line_no++;
				break;
			}
		}
		file.close();
		int n = sizeof(scoreArr) / sizeof(scoreArr[0]);
		sort(scoreArr, scoreArr + n);

		int counter_back = line_no - 1;
		cout << "\nTop scores: ";
		for (int i = 0; i < line_no; i++){
			cout << "\nNo#" << (i + 1) << ": " << scoreArr[counter_back];
			counter_back--;
		}
	}

	//save gamer data to gamer.txt file
	void saveGamerData(){
		int count_lines = 0;
		ifstream file_read;
		string lines[1000];
		ofstream file_write;
		file_write.open("gamer.txt", ios::app);
		file_read.open("gamer.txt");
		if (file_read.fail() || file_write.fail()){
			cout << "\nFile not found gamer.txt !!";
			exit(1);
		}

		if (at_line != -1){
			string line = "";
			while (getline(file_read, line)){
				lines[count_lines] = line;
				count_lines++;
			}
			file_read.close();
			//to clear player records from gamer.txt file
			std::ofstream ofs;
			ofs.open("gamer.txt", std::ofstream::out | std::ofstream::trunc);
			ofs.close();
			for (int i = 0; i < count_lines; i++){
				if (i ==at_line){
					file_write << this->getRegNo() << "," << this->getName() << ","
						<< this->getScore() << "," << this->getDifficulty() << endl;
				}
				else
					file_write << lines[i] << endl;
			}
		}
		else{
			file_write << this->getRegNo() << "," << this->getName() << ","
				<< this->getScore() << "," << this->getDifficulty() << endl;
		}
		cout << "\nPlayer Data saved successfully!!" << endl;
		file_write.close();
	}

	//validate security key
	bool isValidPlayer(){
		int key = 0;
		if (security_key != -1){
			cout << "\nEnter Security key to display player data: ";
			cin >> key;
			if (security_key != key){
				cout << "\nSecurity key not matched!!";
				return false;
			}
			else
				return true;
		}
		return true;
	}
};
