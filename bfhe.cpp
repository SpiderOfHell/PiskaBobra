#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <windows.h>;
using namespace std;
enum commands //энум
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
int getCommandCode(const string& command)//костыльное для свичей
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
void executeScript(const string& path, const string& name)//обработка файла
{
	ifstream f(path);
	if (!f.is_open())
	{
		cout << "Ошибка открытия скрипта: " << path << endl;
		return;
	}
	string line;
	while (getline(f, line))//построчное чтение
	{
		string comment;
		size_t pos = line.find("//");//нахождение в строке комментария
		if (pos != string::npos)//если существует комментарий
		{
			comment = line.substr(pos + 2);//чтение коммментария с удалением слешей
			line = line.substr(0, pos);//удаление комментария из строки
		}
		if (line.empty() && comment.empty())//если ничего нет, то скоп итерации
			continue;
		cout << name << ">" << line;
		if (!comment.empty())//если комментарий был задан, то выводится на экран после комманды
			cout << " //" << comment;
		cout << endl;
		istringstream input(line);//парсер аргументов
		vector<string> parts;
		string token;
		while (input >> token)
			parts.push_back(token);
		if (parts.empty())//если аргументов не было, но был комментарий
		{
			if (!comment.empty())
				cout << "Комментарий: " << comment << endl;
			continue;
		}//не забыть заменить код на костыль при создании обработки аргументов
		int code = getCommandCode(parts[0]);//тут без костыля, так как он изначально был немного для другого
		parts.erase(parts.begin());//удаление кода комманды, чтобы не вызывалась повторно при будущем добавлении логики обработки
		switch (code)
		{
		case CD:
			cout << name << ">Вызвана команда cd с аргументами:\n";
			for (auto& p : parts) cout << "\t" << p << "\n";
			if (!comment.empty())
				cout << "Комментарий: " << comment << "\n";
			cout << "Всего аргументов было: " << parts.size() << "\n";
			break;
		case LS:
			cout << name << ">Вызвана команда ls с аргументами:\n";
			for (auto& p : parts) cout << "\t" << p << "\n";
			if (!comment.empty())
				cout << "Комментарий: " << comment << "\n";
			cout << "Всего аргументов было: " << parts.size() << "\n";
			break;
		case HELP:
			cout << "Спасение утопающих - дело рук самих утопающих\n";
			if (!comment.empty())
				cout << "Комментарий: " << comment << "\n";
			break;
		case EXIT:
			exit(0);
		case RUN:
			if (parts.empty())
			{
				cout << "Ошибка: не указан путь к скрипту\n";
				break;
			}
			executeScript(parts[0], name);
			break;
		default:
			cout << "Ошибка! комманда не найдена!\n";
			if (!comment.empty())
				cout << "Комментарий: " << comment << "\n";
			break;
		}
	}
}
int main(int argc, char* argv[])//мэйн
{
	setlocale(0, "");
	const string absPath = filesystem::current_path().string() + "\\bfhe.exe";//костыль абсолютного путя к файлу проги
	const string absScriptPath = filesystem::current_path().string() + "\\start.txt";//аналогично для стартового скрипта
	if (argc < 3)//при неподаче всех нужных аргументов будет утешительный приз
	{
		cout << "Больше аргументов дай лэээээ\n";
		return 1;
	}
	else if (argc > 3)
	{
		cout << "Меньше аргументов дай лээээ\n";
		return 1;
	}
	string vfsPath = argv[1];
	string scriptPath = argv[2];
	cout << "Отладочный вывод параметров:\n";
	cout << "Путь к VFS: " << vfsPath << "\n";
	cout << "Путь к стартовому скрипту: " << scriptPath << "\n";
	if (vfsPath != absPath)//проверка путя к экзешнику
	{
		cout << "Ошибка доступа к файлу VFS. Прекращение работы.\n";
		return 1;
	}
	if (scriptPath != absScriptPath)//проверка путя к скрипту
	{
		cout << "Неверный путь к стартовому скрипту\n";
		return 1;
	}
	if (!filesystem::exists(scriptPath))//на случай проблемной прокладки между монитором и креслом
	{
		cout << "Верни обратно файл стартового скрипта, его удалять нельзя было\n";
		return 1;
	}
	executeScript(scriptPath, "Persona");//запуск функции обработки стартового скрипта
	vector<string> line;
	vector<int> kostil;
	string command, name = "Persona";
	cout << "Для вывода списка комманд введите help\n";
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
				cout << name << ">" << "Вызвана команда cd с аргументами:\n";
				for (auto p : line)
				{
					cout << "\t" << p << "\n";
				}
				cout << "Всего аргументов было: " << line.size() << "\n";
				break;
			case EXIT:
				exit(0);
				break;
			case HELP:
				cout << "Спасение утопающих - дело рук самих утопающих\n";
				break;
			case LS:
				kostil.erase(kostil.begin());
				cout << name << ">" << "Вызвана команда ls с аргументами:\n";
				for (auto p : line)
				{
					cout << "\t" << p << "\n";
				}
				cout << "Всего аргументов было: " << line.size() << "\n";
				break;
			case RUN:
				if (line.empty())
				{
					cout << "Ошибка: не указан путь к скрипту\n";
					break;
				}
				executeScript(line[0], name);
				break;
			default:
				cout << "Ошибка! комманда не найдена!\nДля вывода списка комманд введите 'help'\n";
				break;
			}
		}
		line.clear();
		kostil.clear();
	}
}