#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <windows.h>;
using namespace std;
enum commands //����
{
	_ERROR = -1,
	EXIT = 1,
	CD = 2,
	HELP = 3,
	LS = 4,
	TOCHKATOCHKA = 5,
	SLESH = 6,
	RUN = 7
};
int getCommandCode(const string& command)//���������� ��� ������
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
	if (command == "run")
		return RUN;
	return _ERROR;
}
void executeScript(const string& path, const string& name)//��������� �����
{
	ifstream f(path);
	if (!f.is_open())
	{
		cout << "������ �������� �������: " << path << endl;
		return;
	}
	string line;
	while (getline(f, line))//���������� ������
	{
		string comment;
		size_t pos = line.find("//");//���������� � ������ �����������
		if (pos != string::npos)//���� ���������� �����������
		{
			comment = line.substr(pos + 2);//������ ������������ � ��������� ������
			line = line.substr(0, pos);//�������� ����������� �� ������
		}
		if (line.empty() && comment.empty())//���� ������ ���, �� ���� ��������
			continue;
		cout << name << ">" << line;
		if (!comment.empty())//���� ����������� ��� �����, �� ��������� �� ����� ����� ��������
			cout << " //" << comment;
		cout << endl;
		istringstream input(line);//������ ����������
		vector<string> parts;
		string token;
		while (input >> token)
			parts.push_back(token);
		if (parts.empty())//���� ���������� �� ����, �� ��� �����������
		{
			if (!comment.empty())
				cout << "�����������: " << comment << endl;
			continue;
		}//�� ������ �������� ��� �� ������� ��� �������� ��������� ����������
		int code = getCommandCode(parts[0]);//��� ��� �������, ��� ��� �� ���������� ��� ������� ��� �������
		parts.erase(parts.begin());//�������� ���� ��������, ����� �� ���������� �������� ��� ������� ���������� ������ ���������
		switch (code)
		{
		case CD:
			cout << name << ">������� ������� cd � �����������:\n";
			for (auto& p : parts) cout << "\t" << p << "\n";
			if (!comment.empty())
				cout << "�����������: " << comment << "\n";
			cout << "����� ���������� ����: " << parts.size() << "\n";
			break;
		case LS:
			cout << name << ">������� ������� ls � �����������:\n";
			for (auto& p : parts) cout << "\t" << p << "\n";
			if (!comment.empty())
				cout << "�����������: " << comment << "\n";
			cout << "����� ���������� ����: " << parts.size() << "\n";
			break;
		case HELP:
			cout << "�������� ��������� - ���� ��� ����� ���������\n";
			if (!comment.empty())
				cout << "�����������: " << comment << "\n";
			break;
		case EXIT:
			exit(0);
		case RUN:
			if (parts.empty())
			{
				cout << "������: �� ������ ���� � �������\n";
				break;
			}
			executeScript(parts[0], name);
			break;
		default:
			cout << "������! �������� �� �������!\n";
			if (!comment.empty())
				cout << "�����������: " << comment << "\n";
			break;
		}
	}
}
int main(int argc, char* argv[])//����
{
	setlocale(0, "");
	const string absPath = filesystem::current_path().string() + "\\bfhe.exe";//������� ����������� ���� � ����� �����
	const string absScriptPath = filesystem::current_path().string() + "\\start.txt";//���������� ��� ���������� �������
	if (argc < 3)//��� �������� ���� ������ ���������� ����� ������������ ����
	{
		cout << "������ ���������� ��� ������\n";
		return 1;
	}
	else if (argc > 3)
	{
		cout << "������ ���������� ��� �����\n";
		return 1;
	}
	string vfsPath = argv[1];
	string scriptPath = argv[2];
	cout << "���������� ����� ����������:\n";
	cout << "���� � VFS: " << vfsPath << "\n";
	cout << "���� � ���������� �������: " << scriptPath << "\n";
	if (vfsPath != absPath)//�������� ���� � ���������
	{
		cout << "������ ������� � ����� VFS. ����������� ������.\n";
		return 1;
	}
	if (scriptPath != absScriptPath)//�������� ���� � �������
	{
		cout << "�������� ���� � ���������� �������\n";
		return 1;
	}
	if (!filesystem::exists(scriptPath))//�� ������ ���������� ��������� ����� ��������� � �������
	{
		cout << "����� ������� ���� ���������� �������, ��� ������� ������ ����\n";
		return 1;
	}
	executeScript(scriptPath, "Persona");//������ ������� ��������� ���������� �������
	vector<string> line;
	vector<int> kostil;
	string command, name = "Persona";
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
				break;
			case RUN:
				if (line.empty())
				{
					cout << "������: �� ������ ���� � �������\n";
					break;
				}
				executeScript(line[0], name);
				break;
			default:
				cout << "������! �������� �� �������!\n��� ������ ������ ������� ������� 'help'\n";
				break;
			}
		}
		line.clear();
		kostil.clear();
	}
}