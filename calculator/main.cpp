#pragma warning(disable : 4996)

#include<iostream>
#include<cstring>
#include<cmath>
#include<stack>

using namespace std;

int power(int a, int b) {
	int n=1;
	if (b < 0) throw runtime_error("Negative exponent not supported!");
	if (b == 0) return 1;
	else 
		while(b!=0){
			if (b % 2 == 1)
				n *= a, b--;
			else {
				b /= 2;
				a *= a;
			}
		}
	return n;
}

bool iscifra(char n) {
	if (n >= 48 && n <= 57) return 1;
	return 0;
}

int operatii(int a, int b, char oper) {
	switch (oper) {
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		if (b == 0) throw runtime_error("Division by zero!");
		return a / b;
		break;
	case '^':
		return power(a, b);
		break;
	default:
		throw runtime_error("Unknoun operator!");
		break;
	}
}

int ordinea_operatiilor(char x) {
	if (x == '+' || x == '-') return 1;
	if (x == '*' || x == '/') return 2;
	if (x == '^') return 3;
	return 0;
}

void evaluare_exp(char *s) {
	stack <char> operatori;
	stack <int> numere;

	int len = strlen(s);
	bool aux = 0;

	for (int i = 0; i < len; i++) {
		if (s[i] == ' ') continue;
		if (s[i] == '-' && s[i + 1] == '('){
			aux = 1;
			continue;
		}
		if (iscifra(s[i]) || (s[i] == '-' && (i == 0 || s[i - 1] == '(' || strchr("+-*/", s[i - 1])))) {
			int nr = 0, semn=1;
			if (s[i] == '-') {
				semn = -1;
				i++;
			}
			while (i < len && iscifra(s[i])) {
				nr = nr * 10 + (s[i] - 48);
				i++;
			}
			numere.push(nr*semn);
			i--;
		}
		if (s[i] == '(')
			operatori.push('(');
		if (s[i] == ')') {
			while (!operatori.empty() && operatori.top() != '(') {  
				int nr2 = numere.top();
				numere.pop();
				int nr1 = numere.top();
				numere.pop();
				char oper = operatori.top(); operatori.pop();
				if (aux) {
					aux = 0;
					numere.push(-1*operatii(nr1, nr2, oper));
				}
				else
					numere.push(operatii(nr1, nr2, oper));
				operatori.pop();
			}
		}
		if (strchr("+-*/^", s[i])) {
			while (!operatori.empty() && ordinea_operatiilor(operatori.top()) >= ordinea_operatiilor(s[i])) {
				int b = numere.top(); numere.pop();
				int a = numere.top(); numere.pop();
				char oper = operatori.top(); operatori.pop();
				numere.push(operatii(a, b, oper));
			}
			operatori.push(s[i]);
		}

	}
	
	while (!operatori.empty()) {
		int b = numere.top(); 
		numere.pop();
		int a = numere.top(); 
		numere.pop();
		char oper = operatori.top(); 
		operatori.pop();
		numere.push(operatii(a, b, oper));
	}


	cout << numere.top() << '\n';
}

int main(int argc, char* argv[]) {
	if (argc != 1)
		evaluare_exp(argv[1]);
	else {
		char s[1001];
		while (true) {
			cout << "> ";
			cin.getline(s, 1000);
			if (strcmp(s, "exit") == 0)
				break;
			if(strcmp(s, "")!=0)
				evaluare_exp(s);
		}
	}
	return 0;
}