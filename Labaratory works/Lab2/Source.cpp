#include <iostream>
#include <deque>
#include <string>
using namespace std;
#define endl cout << "\n";

class Logic_function
{
public:

	void print_array(const bool(&Array)[5][16])
	{
		for (int i = 0; i < bit_depth + 1; i++)
		{
			if (i == bit_depth) cout << "Fi: ";
			else cout << "X" << i + 1 << ": ";


			for (int j = 0; j < numbr_of_column; j++)
			{
				cout << Array[i][j];
			}
			endl
		}
	}

	static void print_deque(const deque<char>& dq)
	{
		for (auto i : dq)
		{
			cout << i;
		}
		endl
	}

	void analysis_input(const deque<int>& function, bool second_task, int numbr)
	{
		SDNF_rez = "";
		SKNF_rez = "";
		deque<bool> container;
		int j = -1, num = 0, count = 0;
		bool num_have_in_column = false;
		container.clear();
		int default_column_size = 16, default_strings_size = 5;
		for (int i = 0; i < default_strings_size; i++)
		{
			for (int j = 0; j < default_column_size; j++)
			{
				spreadsheet_truth[i][j] = false;
			}
		}


		if (second_task)
		{
			int position = 8;
			numbr_of_column = 8;
			bit_depth = 3;
			while (numbr >= 1)  //convert max number to know how many colmn and sityations
			{
				position--;
				if (numbr % 2 == 1) count++;
				spreadsheet_truth[3][position] = (numbr % 2);
				numbr /= 2;

			}

		}

		else
		{
			int max_num = 0;
			for (auto i : function)
			{
				if (max_num < i) max_num = i;
			}


			while (max_num >= 1)
			{
				bit_depth++;                     //convert max number to know how many colmn and sityations
				max_num /= 2;
			}
			numbr_of_column = pow(2, bit_depth);
		}



		for (int i = 0; i < numbr_of_column; i++)
		{
			j++;
			num_have_in_column = false;
			num = i;

			if (!second_task)
			{
				for (int q = 0; q < function.size(); q++)
				{
					if (function[q] == num) num_have_in_column = true;
				}
			}

			while (num >= 1)
			{
				container.push_front(num % 2);
				num /= 2;
			}

			if (container.size() < bit_depth)
			{
				while (container.size() != bit_depth)
				{
					container.push_front(0);
				}
			}

			for (int s = 0; s < bit_depth; s++)
			{
				spreadsheet_truth[s][j] = container[s];
				if (num_have_in_column) spreadsheet_truth[bit_depth][j] = true;
			}
			container.clear();
		}
		print_array(spreadsheet_truth);
		endl
			SDNF_and_SKNF();
	}

	void analysis_input_logical_form(deque<char>& logical_fucntion)
	{
		int X = 0, Y = 0, Z = 0, num_i = 0;
		deque<char> preparing_function;
		bool reverse = false;
		SDNF_rez = "";
		SKNF_rez = "";
		deque<bool> container, container_result;
		int j = -1, num = 0, count = 0;
		bool num_1_in_column = false, note_reversive = false;
		container.clear();
		int number_of_brackets = 0;
		preparing_function.clear();
		numbr_of_column = 8;
		bit_depth = 3;
		int default_column_size = 16, default_strings_size = 5;
		int bit_size_container = 8;

		for (int i = 0; i < logical_fucntion.size(); i++)
		{

			if (logical_fucntion[i] == '!' && logical_fucntion[i + 1] == '(')
			{

				for (int j = i; j < logical_fucntion.size(); j++)
				{
					if (logical_fucntion[j] == '!' && logical_fucntion[j + 1] == '(' && j != 0 && logical_fucntion[0] == '!' && logical_fucntion[1] == '(')
					{
						number_of_brackets++;
						preparing_function.push_back(logical_fucntion[j + 2]);
						preparing_function.push_back(logical_fucntion[j + 3]);
						preparing_function.push_back(logical_fucntion[j + 4]);
						j += 4;
					}
					else if (logical_fucntion[j] == '(') number_of_brackets++;
					else if (logical_fucntion[j] == '!' && (logical_fucntion[j + 1] == 'X' || logical_fucntion[j + 1] == 'Y' || logical_fucntion[j + 1] == 'Z')) preparing_function.push_back(logical_fucntion[j]);
					else if (logical_fucntion[j] == 'X' || logical_fucntion[j] == 'Y' || logical_fucntion[j] == 'Z')
					{
						if (logical_fucntion[j] == 'X') preparing_function.push_back('R');
						else if (logical_fucntion[j] == 'Y') preparing_function.push_back('F');
						else preparing_function.push_back('L');
					}
					else if (logical_fucntion[j] == '+') preparing_function.push_back('*');
					else if (logical_fucntion[j] == '*') preparing_function.push_back('+');
					if (logical_fucntion[j] == ')' && number_of_brackets == 0)
					{
						count = j;
						break;
					}
					else if (logical_fucntion[j + 1] == ')') number_of_brackets--;

				}
				i = count;//break;
			}

			else if (logical_fucntion[i] == '(')
			{
				for (int j = i; j < logical_fucntion.size(); j++)
				{
					if (logical_fucntion[j] == '(') number_of_brackets++;
					else if (logical_fucntion[j] == '!' && (logical_fucntion[j + 1] == 'X' || logical_fucntion[j + 1] == 'Y' || logical_fucntion[j + 1] == 'Z'))
					{
						if (logical_fucntion[j + 1] == 'X') preparing_function.push_back('R');
						else if (logical_fucntion[j + 1] == 'Y') preparing_function.push_back('F');
						else preparing_function.push_back('L');
						j += 1;
					}
					else if (logical_fucntion[j] == 'X' || logical_fucntion[j] == 'Y' || logical_fucntion[j] == 'Z') preparing_function.push_back(logical_fucntion[j]);
					else if (logical_fucntion[j] == '+' || logical_fucntion[j] == '*') preparing_function.push_back(logical_fucntion[j]);
					if (logical_fucntion[j] == ')' && number_of_brackets == 0)
					{
						count = j;
						break;
					}
					else if (logical_fucntion[j + 1] == ')') number_of_brackets--;
				}
				i = count;//break;
			}

			else if (logical_fucntion[i] == '!')
			{
				if (logical_fucntion[i] == '!' && (logical_fucntion[i + 1] == 'X' || logical_fucntion[i + 1] == 'Y' || logical_fucntion[i + 1] == 'Z'))
				{
					if (logical_fucntion[i + 1] == 'X') preparing_function.push_back('R');
					else if (logical_fucntion[i + 1] == 'Y') preparing_function.push_back('F');
					else preparing_function.push_back('L');
					i += 1;
				}

			}
			else preparing_function.push_back(logical_fucntion[i]);
		}

		//print_deque(preparing_function);

		for (int i = 0; i < default_strings_size; i++)
		{
			for (int j = 0; j < default_column_size; j++)
			{
				spreadsheet_truth[i][j] = false;
			}
		}

		for (int i = 0; i < numbr_of_column; i++)
		{
			j++;

			num = i;

			while (num >= 1)
			{
				container.push_front(num % 2);
				num /= 2;
			}

			if (container.size() < bit_depth)
			{
				while (container.size() != bit_depth)
				{
					container.push_front(0);
				}
			}

			for (int s = 0; s < bit_depth; s++)
			{
				spreadsheet_truth[s][j] = container[s];

			}
			container.clear();
		}


		container_result = processing(preparing_function);
		for (int i = 0; i < bit_size_container; i++)
		{
			if (container_result[i] == 1) num_i += pow(2, 8 - (i + 1));
			spreadsheet_truth[bit_depth][i] = container_result[i];

		}

		print_array(spreadsheet_truth);
		endl
			//minimization_method_Cvain_Mak_Klaski();

		endl
			SDNF_and_SKNF();
		endl
			cout << "Index = " << num_i;
		endl
	}

	void SDNF_and_SKNF()
	{
		bool SDNF_trigger = false, last_in = false;
		int count_SDNF = 1, count_SKNF = 1;
		for (int i = 0; i < numbr_of_column; i++)
		{
			if (spreadsheet_truth[bit_depth][i] == 1) number_of_terms_SDNF++;
			else number_of_terms_SKNF++;
		}

		for (int j = 0; j < numbr_of_column; j++)
		{
			SDNF_trigger = false;

			if (spreadsheet_truth[bit_depth][j] == 1) SDNF_trigger = true;

			for (int i = 0; i < bit_depth; i++)
			{
				if (SDNF_trigger)
				{
					if (i == 0) SDNF_rez += " (";
					if (i == 0 && spreadsheet_truth[i][j] == 0) SDNF_rez += "!X1 *";
					else if (i == 1 && spreadsheet_truth[i][j] == 0) SDNF_rez += " !X2 *";
					else if (i == 2 && spreadsheet_truth[i][j] == 0) SDNF_rez += " !X3";
					else if (i == 3 && spreadsheet_truth[i][j] == 0) SDNF_rez += " * !X4";
					else if (i == 0) SDNF_rez += "X1 *";
					else if (i == 1) SDNF_rez += " X2 *";
					else if (i == 2) SDNF_rez += " X3";
					else if (i == 3) SDNF_rez += " * X4";
					if (i == bit_depth - 1) SDNF_rez += ") ";
					if (count_SDNF != number_of_terms_SDNF && i == bit_depth - 1)
					{
						SDNF_rez += " + ";
						count_SDNF++;
					}
				}

				else
				{
					if (i == 0) SKNF_rez += " (";
					if (i == 0 && spreadsheet_truth[i][j] == 1) SKNF_rez += "!X1 + ";
					else if (i == 1 && spreadsheet_truth[i][j] == 1) SKNF_rez += "!X2 + ";
					else if (i == 2 && spreadsheet_truth[i][j] == 1) SKNF_rez += "!X3";
					else if (i == 3 && spreadsheet_truth[i][j] == 1) SKNF_rez += " + !X4";
					else if (i == 0) SKNF_rez += "X1 + ";
					else if (i == 1) SKNF_rez += "X2 + ";
					else if (i == 2) SKNF_rez += "X3";
					else if (i == 3) SKNF_rez += " + X4";
					if (i == bit_depth - 1) SKNF_rez += ") ";
					if (count_SKNF != number_of_terms_SKNF && i == bit_depth - 1)
					{
						SKNF_rez += " * ";
						count_SKNF++;
					}
				}
			}
		}
		cout << "SDNF form: " << SDNF_rez << "\n";
		cout << "SKNF form: " << SKNF_rez << "\n";
	}

	deque<bool> processing(deque<char> dq)
	{
		deque<bool>  result_container;
		bool X, Y, Z, reverse = false;
		int str = 0;
		for (int i = 0; i < dq.size(); i++)
		{
			if (dq[i] == 'X' && dq[i + 1] == '+' && dq[i + 2] == 'X' || dq[i] == 'R' && dq[i + 1] == '+' && dq[i + 2] == 'X' || dq[i] == 'R' && dq[i + 1] == '+' && dq[i + 2] == 'R' || dq[i] == 'X' && dq[i + 1] == '+' && dq[i + 2] == 'R')
			{
				for (int column = 0; column < numbr_of_column; column++)
				{
					X = spreadsheet_truth[str][column];
					if (dq[i] == 'R') X = !X;
					result_container.push_back(X + X);
				}
				i += 2;
			}

			else if (dq[i] == 'X' && dq[i + 1] == '*' && dq[i + 2] == 'X' || dq[i] == 'R' && dq[i + 1] == '*' && dq[i + 2] == 'X' || dq[i] == 'R' && dq[i + 1] == '*' && dq[i + 2] == 'R' || dq[i] == 'X' && dq[i + 1] == '*' && dq[i + 2] == 'R')
			{
				for (int column = 0; column < numbr_of_column; column++)
				{
					X = spreadsheet_truth[str][column];
					if (dq[i] == 'R') X = !X;
					result_container.push_back(X * X);
				}
				i += 2;
			}
			else if (dq[i] == 'X' && dq[i + 1] == '+' && dq[i + 2] == 'Y' || dq[i] == 'R' && dq[i + 1] == '+' && dq[i + 2] == 'Y' || dq[i] == 'R' && dq[i + 1] == '+' && dq[i + 2] == 'F' || dq[i] == 'X' && dq[i + 1] == '+' && dq[i + 2] == 'F')
			{
				for (int column = 0; column < numbr_of_column; column++)
				{

					X = spreadsheet_truth[str][column];
					if (dq[i] == 'R') X = !X;
					Y = spreadsheet_truth[str + 1][column];
					if (dq[i + 2] == 'F') Y = !Y;
					result_container.push_back(X + Y);
				}
			}
			else if (dq[i] == 'X' && dq[i + 1] == '+' && dq[i + 2] == 'Z' || dq[i] == 'R' && dq[i + 1] == '+' && dq[i + 2] == 'Z' || dq[i] == 'R' && dq[i + 1] == '+' && dq[i + 2] == 'L' || dq[i] == 'X' && dq[i + 1] == '+' && dq[i + 2] == 'L')
			{
				for (int column = 0; column < numbr_of_column; column++)
				{
					X = spreadsheet_truth[str][column];
					if (dq[i] == 'R') X = !X;
					Z = spreadsheet_truth[str + 2][column];
					if (dq[i + 2] == 'Z') Z = !Z;
					result_container.push_back(X + Z);
				}
			}
			else if (dq[i] == 'X' && dq[i + 1] == '*' && dq[i + 2] == 'Y' || dq[i] == 'R' && dq[i + 1] == '*' && dq[i + 2] == 'Y' || dq[i] == 'R' && dq[i + 1] == '*' && dq[i + 2] == 'F' || dq[i] == 'X' && dq[i + 1] == '*' && dq[i + 2] == 'F')
			{
				for (int column = 0; column < numbr_of_column; column++)
				{
					X = spreadsheet_truth[str][column];
					if (dq[i] == 'R') X = !X;
					Y = spreadsheet_truth[str + 1][column];
					if (dq[i + 2] == 'F') Y = !Y;
					result_container.push_back(X * Y);
				}
			}
			else if (dq[i] == 'X' && dq[i + 1] == '*' && dq[i + 2] == 'Z' || dq[i] == 'R' && dq[i + 1] == '*' && dq[i + 2] == 'Z' || dq[i] == 'R' && dq[i + 1] == '*' && dq[i + 2] == 'L' || dq[i] == 'X' && dq[i + 1] == '*' && dq[i + 2] == 'L')
			{
				for (int column = 0; column < numbr_of_column; column++)
				{
					X = spreadsheet_truth[str][column];
					if (dq[i] == 'R') X = !X;
					Z = spreadsheet_truth[str + 2][column];
					if (dq[i + 2] == 'L') Z = !Z;
					result_container.push_back(X * Z);
				}
			}


			else if (dq[i] == '+' && dq[i + 1] == 'X' || dq[i] == '+' && dq[i + 1] == 'R')
			{
				for (int j = 0; j < bit_depth; j++)
				{
					X = spreadsheet_truth[str][j];
					result_container[j] = result_container[j] + X;
				}

			}
			else if (dq[i] == '+' && dq[i + 1] == 'Y' || dq[i] == '+' && dq[i + 1] == 'F')
			{

				for (int j = 0; j < bit_depth; j++)
				{
					Y = spreadsheet_truth[str + 1][j];
					if (dq[i + 1] == 'F') Y = !Y;
					result_container[j] = result_container[j] + Y;
				}
			}
			else if (dq[i] == '+' && dq[i + 1] == 'Z' || dq[i] == '+' && dq[i + 1] == 'L')
			{
				for (int j = 0; j < bit_depth; j++)
				{
					Z = spreadsheet_truth[str + 2][j];
					if (dq[i + 1] == 'L') Z = !Z;
					result_container[j] = result_container[j] + Z;
				}
			}
			else if (dq[i] == '*' && dq[i + 1] == 'X' || dq[i] == '*' && dq[i + 1] == 'R')
			{
				for (int j = 0; j < bit_depth; j++)
				{
					X = spreadsheet_truth[str][j];
					if (dq[i + 1] == 'R') X = !X;
					result_container[j] = result_container[j] * X;
				}
			}
			else if (dq[i] == '*' && dq[i + 1] == 'Y' || dq[i] == '*' && dq[i + 1] == 'F')
			{
				for (int j = 0; j < bit_depth; j++)
				{
					Y = spreadsheet_truth[str + 1][j];
					if (dq[i + 1] == 'F') Y = !Y;
					result_container[j] = result_container[j] * Y;
				}
			}
			else if (dq[i] == '*' && dq[i + 1] == 'Z' || dq[i] == '*' && dq[i + 1] == 'L')
			{
				for (int j = 0; j < bit_depth; j++)
				{
					Z = spreadsheet_truth[str + 2][j];
					if (dq[i + 1] == 'L') Z = !Z;
					result_container[j] = result_container[j] * Z;
				}
			}
		}


		return result_container;
	}

	string get_SDNF_rez() { return SDNF_rez; }

	string get_SKNF_rez() { return SKNF_rez; }

private:
	
	int bit_depth = 0;
	int numbr_of_column = 0;
	int number_of_terms_SDNF = 0;
	int number_of_terms_SKNF = 0;
	string SDNF_rez = "";
	string SKNF_rez = "";
	string TDNF_rez = "";
	string TKNF_rez = "";
	static const int number_of_strings = 5;
	static const int number_of_columns = 16;
	bool spreadsheet_truth[number_of_strings][number_of_columns];

};

void main()
{
	deque<char> analyzing_function;
	int choose, max_number_input = 256, numbr_of_input = 100;
	deque<int> function;
	static const int null = 0;
	static const int max_number_input_user = 15;
	bool reset = true, checker = false, second_task = false;
	Logic_function exmpl;
	while (reset)
	{
		second_task = false;
		cout << "Input function one from 3 forms:\n";
		cout << "1: F(0,1,3,7,8,9,11,15)\n";
		cout << "2: F(X1, X2, X3, Xn)\n";
		cout << "3: F(!X + Y * Z)\n";
		cout << "0: Complete program\n";
		cin >> choose;
		if (choose == 2)
		{
			choose--;
			second_task = true;
		}
		switch (choose)
		{
		case 0:
		{
			reset = false;
			break;
		}
		case 1:
		{
			try
			{
				checker = false;
				int j = 0;
				int num = 0;
				if (second_task)
				{
					checker = true;
					cout << "Input i function: ";
					cin >> num;
					if (num >= max_number_input_user) throw 2;

				}
				else
				{
					function.clear();
					int num = 0, size = 0;
					cout << "Input size function: ";
					cin >> size;
					if (!(size >= null && size <= max_number_input)) throw 2;
					cout << "Input function: ";

					for (int i = 0; i < size; i++)
					{
						cin >> num;
						function.push_back(num);
						if (!(num >= null && num <= max_number_input)) throw 2;
					}

				}

				exmpl.analysis_input(function, checker, num);
			}

			catch (int error)
			{
				if (error == 2) cout << "Uncorrect unput!\n";
			}
			break;
		}
		case 3:
		{
			try {
				analyzing_function.clear();
				char symbol = 0;
				int number_of_breckets = 0;
				cout << "Input function, for stopping input tape (#): ";
				for (int i = 0; i < numbr_of_input; i++)
				{
					cin >> symbol;
					if (symbol == '#') break;
					if (symbol == '(') number_of_breckets++;
					if (symbol != 'X' && symbol != 'Y' && symbol != 'Z' && symbol != '(' && symbol != ')' && symbol != '*' && symbol != '+' && symbol != '!') throw 1;
					else if (symbol == ')') number_of_breckets--;
					
					analyzing_function.push_back(symbol);
				}
				if (number_of_breckets != 0) throw 1;
				exmpl.analysis_input_logical_form(analyzing_function);
			}
			catch (int error)
			{
				if (error == 1) cout << "Uncorrect unput!\n";
			}
			break;
		}

		default:
		{
			cout << "No such this case!\n";
			break;
		}
		}
		system("pause");
		system("cls");
	}
}
