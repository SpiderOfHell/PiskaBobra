#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
enum commands
{
	ERROR = -1,
	EXIT = 1,
	CD = 2,
	HELP = 3,
	LS = 4,
	TOCHKATOCHKA = 5,
	SLESH = 6

};
int getCommandCode(const string& command)
{
	if (command == "cd")
		return CD;
	if (command == "exit")
		return EXIT;
	if (command == "help")
		return HELP;
	if (command == "ls")
		return LS;
	if (command == "..")
		return TOCHKATOCHKA;
	if (command[0] == '/')
		return SLESH;
	return	ERROR;
}
/*class cmdpath
{
	string path;
	string* father;
	vector<string*>children;
public:
	cmdpath(string*father, string path, vector<string*> newchildren)
	{
		this->father = father;
		this->path = path;
		for (auto p : newchildren)
		{
			children.push_back(p);
		}
	}
	string getpath()
	{
		return path;
	}
	string* getfather()
	{
		return father;
	}
	void setpath(string newpath)
	{
		path = newpath;
	}
	bool setfather(string* newfather)
	{
		if(father!=nullptr)
		{
			father = newfather;
			return true;
		}
		return false;
	}
	void addchild(string*& child)
	{
		if (children[0] == nullptr)
		{
			children[0]->erase();
		}
		children.push_back(child);
	}
	string* getchild(int i)
	{
		if(!children.empty() && i<children.size())
			return children[i];
		return nullptr;
	}
	int sizechildren()
	{
		return children.size();
	}
};*/
int main()
{
	setlocale(0, "");
	/*string* kdw=nullptr;
	string pat = "ejje/fefe";
	vector<string*>vec;
	vec.push_back(kdw);
	string ko = "fefe";
	string* jh = &ko;
	vec.push_back(jh);
	cmdpath test1(kdw,pat,vec);*/
	string command, name = "Persona";
	vector<string> line;
	vector<int> kostil;
	cout << "��� ������ ������ ������� ������� help\n";
	while (true)
	{
		cout << name << ">";
		if (cin.eof())
		{
			return 1;
		}
		if (!getline(cin, command) || command.empty())
		{
			continue;
		}
		istringstream input(command);
		string podcommand;
		while (input >> podcommand)
		{
			line.push_back(podcommand);
		}
		kostil.push_back(getCommandCode(line[0]));
		if (!line.empty())
		{
			line.erase(line.begin());
			switch (kostil[0])
			{
			case CD:
				kostil.erase(kostil.begin());
				cout << name << ">" << "������� ������� cd � �����������:\n";
				for (auto p : line)
				{
					cout << "\t" << p << "\n";
				}
				cout << "����� ���������� ����: " << line.size() << "\n";
				/*for (auto p : line)
				{
					kostil.push_back(getCommandCode(p));
				}
				if (kostil.size() == 0)
				{
					cout << "���������:\n/home/user � ������� � ���������� /home/user\n"
						<< "..� ������� �� ������� ���� � �������� ����������\n"
						<< "~ � ������� � �������� ���������� �������� ������������\n"
						<< "- � ������� � ���������� ������� ����������\n";
					break;
				}
				for(int i=0;i<kostil.size();i++)
				{
					switch (kostil[i])
					{
					case SLESH:
						if (kostil.size()!=1)
						{
							cout << "�� ������� �������� ����, " << line[0]<<" ";
							for (auto p : line)
							{
								if (p == line[0])
									continue;
								cout << p << " ";
							}
							cout << "�� �������� �������� ����\n";
							kostil.clear();
							break;
						}
						cout << "�������\n";
						break;
					case TOCHKATOCHKA:
						cout << "��������\n";
						break;
					default:
						cout << "������, ����������� �������� " << line[i] << "\n";
						i = kostil.size();
						break;
					}
				}*/
				break;
			case EXIT:
				exit(0);
				break;
			case HELP:
				cout << "�������� ��������� - ���� ��� ����� ���������\n";
				break;
			case LS:
				kostil.erase(kostil.begin());
				cout << name << ">" << "������� ������� ls � �����������:\n";
				for (auto p : line)
				{
					cout << "\t" << p << "\n";
				}
				cout << "����� ���������� ����: " << line.size() << "\n";
				/*cout << "���������:\n-a - ����������� ����� ����������� ����������\n"
					<<"-A - ����������� ���� ������, ����� �������\n"
					<<"--author � ��������� ���������� �� ������\n"
					<<"-b � ����� ����� �����, ���� ���� � ��� ���������� ��������� �������, ������� �� ����� ��� ������.\n";*/
				break;
			default:
				cout << "������! �������� �� �������!\n��� ������ ������ �������������� 'help'\n";
				break;
			}
		}
		line.clear();
		kostil.clear();
	}
}