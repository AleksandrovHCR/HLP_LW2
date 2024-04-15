#include<iostream>
#include <fstream>
#include <string>
using namespace std;
class test {
	int Len = 0;
	string* varibles;
	
public:
	~test() {
		delete[]varibles;
		
	}
	bool triple_correct(string code) {
		int this_point=0, qt = 0,tz=0;
		while (code[this_point] != '\0') {
			if (code[this_point] == '?' || code[this_point] == ':')
				qt++;
			if (code[this_point] == ';')
				tz++;
			this_point++;
		}
		if (qt == 2 && tz==1)
			return true;
		else
			return false;
	}
	void varible_count(int lenght) {
		Len += lenght;
	}
	void establish_the_array() {
		varibles = new string[Len];
		Len = 0;
	}
	void varibles_reader(string code) {
		int  This_point = Len;
		int S_point, t_point;
		if (code.rfind("int") != -1)
			S_point = code.rfind("int") + 3;
		if (code.rfind("char") != -1)
			S_point = code.rfind("char") + 4;
		if (code.rfind("bool") != -1)
			S_point = code.rfind("bool") + 4;
		if (code.rfind("float") != -1)
			S_point = code.rfind("float") + 5;
		t_point = S_point;
		int temp = 0;
		while (code[t_point] != '\0') {
			if (code[t_point] == ' ') {
				while (code[t_point] == ' ')
					t_point++;
				S_point = t_point;
			}

			if ((code[t_point] == ',' or code[t_point] == ';' ) and t_point != S_point) {
				if (temp != 0)
					varibles[This_point].assign(code, S_point, temp - S_point);
				else
					varibles[This_point].assign(code, S_point, t_point - S_point);
				This_point++;
				S_point = t_point + 1;
				temp = 0;
			}
			if (code[t_point] == '=')
				temp = t_point;
			t_point++;
		}
		Len = This_point;
		//no passes
		/*temp = PC;
		while (temp < Len) {
			bool doit = false;
			while (varibles[temp].find(' ') != -1 || varibles[temp][This_point] != '\0') {
				if (varibles[temp].find(' ') == 0)
					doit = true;
				if (doit)
					varibles[temp][This_point] = varibles[temp][This_point + 1];

				if (varibles[temp].find(' ') == This_point || varibles[temp].find('\0') == This_point) {
					varibles[temp].erase(This_point, varibles[temp].find('\0'));
					This_point = 0;
					break;
				}
				This_point++;
			}

			temp++;
		}
		PC = This_point;*/
	}
	void New_var(string code) {
		int S_point, t_point;
		if (code.rfind("int") != -1) 
			S_point = code.rfind("int") + 3;
		if (code.rfind("char") != -1)
			S_point = code.rfind("char") + 4;
		if (code.rfind("bool") != -1)
			S_point = code.rfind("bool") + 4;
		if (code.rfind("float") != -1)
			S_point = code.rfind("float") + 5;
		while (true) {
			if (code[S_point] != 32 && code[S_point] != 61)
				break;
			S_point++;
		}
		t_point = S_point;
		while (true) {
			if (code[t_point] == 32 || code[t_point] == 61 || code[t_point] == '\0') {
				break;
			}
			t_point++;
		}
		varibles[Len].assign(code, S_point, t_point - S_point);
		Len++;
	}
	void arr_test() {
		for (int i = 0; i < Len; i++) {
			if (varibles[i].find("[") != -1 && varibles[i].rfind("]") != -1 && (varibles[i].find("[") < varibles[i].rfind("]"))) {
				int x = 0;
				while (varibles[i][x] != '\0') {
					if (varibles[i][x] == '['){
						int tmp = x;
						while (true) {
							if (varibles[i][x] == ']' || varibles[i][x] == '\0')
								break;
							x++;
						}
						if (varibles[i][x] == '\0') {
							varibles[i].erase();
							break;
						}
						if (varibles[i][x] == ']') {
							bool tr = false;
							for (int f = 0; f < 10; f++) {
								if (varibles[i].find(f + 48, tmp) != -1) {
									tr = true;
									break;
								}
							}
							if (tr == true) {
								tmp += 1;
								varibles[i].erase(tmp,varibles[i].length()-tmp);
								x = tmp - 1;
							}
							else
								varibles[i].erase();
						}
					}
					if (varibles[i][x] != '\0')
						x++;
					else
						break;
				}
			}
		}
	}
	//Тест правой части
	bool LP_test(string code) {
		string temp, op1[]{"+","*","-","/","%"};
		int Var = 0, pos = 0;
		temp.assign(code, 0, code.find("="));
		if (code.find("int") != -1 or code.find("float") != -1 or code.find("bool") != -1 or code.find("char") != -1) {
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1)
					Var++;
			}
			if (Var == 0)
				New_var(temp);
		}
		Var = 0;
		for (int i = 0; i < Len; i++) {
			if (temp.find(varibles[i]) != -1) {
				Var++;
				pos = temp.find(varibles[i]);
			}

		}

		if (temp.find("*(") != -1 && temp.find(")") != -1 && Var > 0)
			return true;
		else {
			if (Var == 1) {
				for (int i = 0; i < Len; i++) {
					if ((temp.find(op1[i]) != -1 && temp.find(op1[i])>pos) || (temp.find(op1[i]) != -1 && temp.find(op1[i]) < pos && op1[i]!="*")) {
						return false;
					}
				}
				return true;
			}
			if (Var > 1 && (temp.find("[") != -1 && temp.find("]") != -1 && temp.find("[") < temp.find("]"))) {
				for (int i = 0; i < Len; i++) {
					if ((temp.find(op1[i]) != -1 && temp.find(op1[i]) > pos) || (temp.find(op1[i]) != -1 && temp.find(op1[i]) < pos && op1[i] != "*")) {
						return false;
					}
				}
				return true;
			}
			else
				return false;

		}
	}
	//Тест левой части
	void brakets(string code, int pos_of_eq) {
		bool Brak = false;
		if (code.find("(", pos_of_eq) != -1 && code.rfind(")") != -1 ) {
			printf("\033[3;44;30mСкобки: присутствуют\033[0m\n");
			Brak = true;
			int x = 0, y = code.length(), BC_1 = 0, BC_2 = 0;
			while (x < code.length() || y>0) {
				if (code[x] == '(')
					BC_1++;
				if (code[y] == ')')
					BC_2++;
				if(x < code.length())
					x++;
				if(y>0)
				y--;
			}
			if(BC_1==BC_2)
				printf("\033[3;44;30mСкобки: Корректны\033[0m\n");
			else
				printf("\033[3;41;30mСкобки: Требуется корректировка!\033[0m\n");

		}
		if((code.find("(", pos_of_eq) == -1) && (code.rfind(")", pos_of_eq) == -1))
			printf("\033[3;44;30mСкобки: отсутствуют\033[0m\n");
		bool tmp = Brak;
		Brak=tern_p1(code, Brak, pos_of_eq);
		Brak ? printf("\033[3;44;30mПервая часть тернарного оператора: корректна\033[0m\n") : printf("\033[3;41;30mПервая часть тернарного оператора: требуется коррекция кода!\033[0m\n");
		Brak = tern_p2(code,tmp);
		Brak ? printf("\033[3;44;30mВторая часть тернарного оператора: корректна\033[0m\n") : printf("\033[3;41;30mВторая часть тернарного оператора: требуется коррекция кода!\033[0m\n");
		Brak = tern_p3(code, tmp);
		Brak ? printf("\033[3;44;30mТретья часть тернарного оператора: корректна\033[0m\n") : printf("\033[3;41;30mТретья часть тернарного оператора: требуется коррекция кода!\033[0m\n");
	}
	//= ?
	bool tern_p1(string code, bool brakets, int pos_of_eq) {
		string temp, op[]{"==",">","<","<=",">=","!="};
		//скобки
		if (brakets) {
			if(code.find("(")!= code.find("(")-1 || code.find("(") != code.find("(") + 1)
			temp.assign(code, code.find("("), code.find("?") - code.find("("));
			else
				temp.assign(code, code.find("(")+1, code.find("?") - code.find("("));
		}
			
		else 
			temp.assign(code, pos_of_eq+1, code.find("?") - pos_of_eq);
	
		/////////////////////////
		int varcount = 0;
		int pos=-1;
		int op_count=0;
		int cifcount = 0;
		for (int i = 0; i < Len; i++) {
			if (temp.find(varibles[i]) != -1)
				varcount++;
		}
		for (int i = 0; i < 7; i++) {
			if (temp.find(op[i]) != -1) {
				pos = temp.find(op[i]);
				break;
			}
		}
		for (int i = 0; i < 7; i++) {
			if (temp.find(op[i]) != -1) {
				op_count++;
			}
		}
		for (int i = 0; i < 10; i++) {
			if (temp.find(i+48) != -1) {
				cifcount++;
				break;
			}
		}
		for (int i = 0; i < 10; i++) {
			if (temp.rfind(i + 48) != -1) {
				cifcount++;
				break;
			}
		}
		if (temp.find("=") != -1 && temp.find("==") == -1 && temp.find("!=") == -1 && temp.find("<=") == -1 && temp.find(">=") == -1)
			return false;
		if ((varcount >= 1 ||cifcount==2) && pos!=-1 && op_count<4) {
			bool t = false, t1=false;
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1 && temp.find(varibles[i])<pos)
					t= true;
			}
			for (int i = 0; i < Len; i++) {
				if (temp.rfind(varibles[i]) != -1 && temp.rfind(varibles[i]) > pos)
					t1= true;
			}

			for (int i = 0; i < 10; i++) {
				if (temp.find(i+48) != -1 && temp.find(i+48) < pos)
					t = true;
			}
			for (int i = 0; i < 10; i++) {
				if (temp.rfind(i + 48) != -1 && temp.rfind(i + 48) > pos)
					t1 = true;
			}


			if (t == t1)
				return true;
			else
				return false;

		}
		else {
			//проверка на ++ --
			if (temp.find("++") != -1 || temp.find("--") != -1)
				return false;
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1 && temp.find("+") == -1 && temp.find("-") == -1 && temp.find("/") == -1 && temp.find("*") == -1 && temp.find("%") == -1)
					return true;
			}



			for (int i = 0; i < 10; i++) {
				if (temp.find(i + 48) != -1 && op_count==0)
					return true;
			}
			if ((temp.find("true") != -1 || temp.find("false") != -1)&& op_count==0)
				return true;
			else
				return false;
		}
	}
	//? :
	bool tern_p2(string code,int brakets) {
		string temp, op1[]{ "+","-","*","%","=","/" }, op2[]{ "++","--" };
		int op_count = 0, oc = 0, pos;
		temp.assign(code, code.find("?"), code.find(":") - code.find("?"));
		for (int i = 0; i < 6; i++) {
			if (temp.find(op1[i]) != -1) {
				op_count++;
				pos = temp.find(op1[i]);
			}
		}
		////////////////////////////////////////////////
		for (int i = 0; i < 2; i++) {
			if (temp.find(op2[i]) != -1)
				oc++;
		}
		////////////////////////////////////////////////
		if (op_count == 0 && oc == 0) {
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1)
					return true;
			}
			for (int i = 0; i < 10; i++) {
				if (temp.find(i + 48) != -1)
					return true;
			}
			return false;
		}
		if (oc >0 && op_count >= 1) {
			int temp_pos;
			temp_pos = temp.find("++") != -1 ? temp.find("++") : temp.find("--");
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1 && (temp.find(varibles[i]) < temp_pos || temp.find(varibles[i]) > temp_pos))
					return true;
			}
		}
		else {
			if (!operator_test(temp))
				return false;
			else
				return true;
		}
		/*else {
			bool t = false, t1 = false;
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) < pos)
					t = true;
			}
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) > pos)
					t1 = true;
			}

			for (int i = 0; i < 10; i++) {
				if (temp.find(i + 48) != -1 && temp.find(i + 48) < pos)
					t = true;
			}
			for (int i = 0; i < 10; i++) {
				if (temp.find(i + 48) != -1 && temp.find(i + 48) > pos)
					t1 = true;
			}


			if (t == t1)
				return true;
			else {

						for (int i = 0; i < Len; i++) {
							if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) > pos) {
								t = true;

							}
						}
						for (int i = 0; i < Len; i++) {
							if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) < pos) {
								t1 = true;

							}
						}

						for (int i = 0; i < 10; i++) {
							if (temp.find(i + 48) != -1 && temp.find(i + 48) > pos)
								t = true;
						}
						for (int i = 0; i < 10; i++) {
							if (temp.find(i + 48) != -1 && temp.find(i + 48) < pos)
								t1 = true;
						}

			}

				if (t == t1)
					return true;
				else
					return false;
			}/**/
			return false;
		}
	//: ;
	bool tern_p3(string code, bool brakets) {
		string temp, op1[]{ "+","-","*","%","=","/" }, op2[]{ "++","--" };
		//brakets ? temp.assign(code, code.find(":"), code.rfind(")") - code.find(":")) : temp.assign(code, code.find(":"), code.rfind(";") - code.find(":"));
		temp.assign(code, code.find(":"), code.rfind(";") - code.find(":"));
		int op_count = 0, oc = 0, pos;

		for (int i = 0; i < 6; i++) {
			if (temp.find(op1[i]) != -1) {
				op_count++;
				pos = temp.find(op1[i]);
			}
		}
		for (int i = 0; i < 2; i++) {
			if (temp.find(op2[i]) != -1)
				oc++;
		}
		if (op_count == 0 && oc == 0) {
			bool cor = false;
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1)
					return true;
			}
			for (int i = 0; i < 10; i++) {
				if (temp.find(i + 48) != -1)
					return true;
			}
			return false;
		}
		if (oc > 0 && op_count >= 1) {
			int temp_pos;
			temp_pos = temp.find("++") != -1 ? temp.find("++") : temp.find("--");
			for (int i = 0; i < Len; i++) {
				if (temp.find(varibles[i]) != -1 && (temp.find(varibles[i]) < temp_pos || temp.find(varibles[i]) > temp_pos))
					return true;
			}
		}
		else {
			if (!operator_test(temp))
				return false;
			else
				return true;
			/*else {
				bool t = false, t1 = false;
				for (int i = 0; i < Len; i++) {
					if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) < pos)
						t = true;


				}
				for (int i = 0; i < Len; i++) {
					if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) > pos)
						t1 = true;

				}

				for (int i = 0; i < 10; i++) {
					if (temp.find(i + 48) != -1 && temp.find(i + 48) < pos )
						t = true;
				}
				for (int i = 0; i < 10; i++) {
					if (temp.find(i + 48) != -1 && temp.find(i + 48) > pos)
						t1 = true;
				}


				if (t == t1)
					return true;
				else {
					bool var = false;
					for (int i = 0; i < Len; i++) {
						if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) > pos) {
							t = true;
							var = true;
						}

					}
					for (int i = 0; i < Len; i++) {
						if (temp.find(varibles[i]) != -1 && temp.find(varibles[i]) < pos) {
							t1 = true;
							var = true;
						}
					}

					for (int i = 0; i < 10; i++) {
						if (temp.find(i + 48) != -1 && temp.find(i + 48) > pos)
							t = true;
					}
					for (int i = 0; i < 10; i++) {
						if (temp.find(i + 48) != -1 && temp.find(i + 48) < pos)
							t1 = true;
					}

					if (var == false &&(t1 || t)) {
						for (int i = 0; i < 27; i++) {
							if (temp.find(i + 65) != -1 || temp.find(i + 97) != -1 )
								return false;
						}

					}






				}
				if (t == t1)
					return true;
				else
					return false;
			}/**/
			return false;
		}
	}

	bool operator_test(string code) {
		int op=0;//позиция
		int pos_sop=0, pos_eop;//позиции операторов
		string temp;
		bool is_frst = true;
		while (true) {
			
			if (code[op]=='+' || code[op] == '-' || code[op] == '/' || code[op] == '*' || code[op] == '%' || code[op] == ';' || code[op] == '\0') {
				pos_eop = op;
				bool wrd = true;;
				if (is_frst) {
					for (int i = 0; i < Len; i++) {
						if (code.rfind(varibles[i], op)!=-1) {
							is_frst = false;
							break;
						}
					}
					for (int i = 0; i < 10; i++) {
						if (code.rfind(i+48, op) != -1) {
							for (int j = 0; j < 27; j++) {
								if ((code.rfind(j + 65, op) != -1) || (code.rfind(j + 97, op) != -1))
									return false;
							}
							wrd = false;
							is_frst = false;
							break;
						}
					}
					if (wrd) {
						for (int j = 0; j < 27; j++) {
							if ((code.rfind(j + 65, op) != -1) || (code.rfind(j + 97, op) != -1))
								return false;
						}
					}
					pos_sop = pos_eop;
					is_frst = false;

				}
				else {
					if (part_tester(temp.assign(code, pos_sop + 1, pos_eop - pos_sop - 1)))
						pos_sop = pos_eop;
					else
						return false;
				}
			}
			if (code[op] != '\0')
				op++;
			else
				break;
		}
		return true;
	}
	bool part_tester(string code) {
		int t_pos = 0;
		for (int i = 0; i < Len; i++) {
			if (code.find(varibles[i])!=-1) 
				return true;
		}
		if (code == "true" || code == "false")
			return true;
		for (int i = 0; i < 10; i++) {
			if (code.find(i + 48) != -1)
				return true;
		}
		while (code[t_pos] != '\0') {
			if (code[t_pos] < 48 || code[t_pos]>57)
				return false;
			t_pos++;
		}
		
		return false;
	}
};
void from_file() {
	int SIZE = 0;
	test Test;
	char filename[150];
	string code;
	ifstream vac;
	cout << "Введите название файла для считывания кода:";
	cin >> filename;
	vac.open(filename);
	if (vac.is_open()) {
		while (getline(vac, code)) {
			if ((code.rfind("int") != -1 or code.rfind("float") != -1 or code.rfind("bool") != -1 or code.rfind("char") != -1))
				Test.varible_count(code.length());
		}
		vac.close();
		ifstream vac;
		vac.open(filename);
		Test.establish_the_array();
		while (getline(vac, code)) {
			if (((code.rfind("int") != -1 or code.rfind("float") != -1 or code.rfind("bool") != -1 or code.rfind("char") != -1) and code.rfind("()") == -1) && (code.find('?') == -1 && code.find(':') == -1))
				Test.varibles_reader(code);
		}
		Test.arr_test();
		vac.close();
		vac.open(filename);
		bool Ts, T1=false;
		while (getline(vac, code)) {
			if (code.find('=') != -1 && code.find('?') != -1 && code.find(':') != -1) {
				T1 = true;
				cout << code << endl;
				if (code.rfind(";\0") == -1)
					printf("\033[3;41;30mОшибка: Нет символа ';'!\033[0m\n");
				else {
					if (Test.triple_correct(code) == true) {
						Ts = Test.LP_test(code);
						Ts ? printf("\033[3;44;30mЛевая часть: корректна\033[0m\n") : printf("\033[3;41;30mЛевая часть: требуется корректировка кода!\033[0m\n");
						Test.brakets(code, code.find("="));
					}
					else
						printf("\033[3;41;30mОшибка: Некорректный синтаксис тернарного оператора или слишком много символов ';'!\033[0m\n");
				}
			}
		}
		if (!T1)
			printf("\033[3;41;30mНет операторов присвоения с тернарным оператором в правой части!\033[0m\n");
	}
	else
		printf("\033[3;41;30mОшибка. Файл не найден.\033[0m\n");

}
int main() {
	setlocale(LC_ALL, "Ru");
	from_file();
	return 0;
}