#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
//template<class T> no dio tiempo :c
using namespace std;
union valorObtenido;
struct Datos; 
Datos evaluarOperacion(vector<Datos> datos); 
vector<Datos> conversion (vector<string> tokens); 
vector<string> token(string line); 
void leerArchivo(); 
int menu();
int main(int argc, char** argv) {
	int op = menu();
	while(op != 2){
		switch(op){
			case 1:{
				leerArchivo();
				break;
			}
			default: {
				cout<<"Opcion invalida"<< endl;
				menu();
				break;
			}
		}
		op = menu();
	}
	return 0;
}
int menu(){
	int opcion = 0;
	cout<<"********** Menu **********"<<endl;
	cout<<"* 1. Abrir archivo       *"<<endl;
	cout<<"* 2. Salir               *"<<endl;
	cout<<"**************************"<<endl;
	cout<<"Elija una opcion: "<<endl;
	cin>> opcion;
	return opcion;
}
union valorObtenido {
	unsigned int datoV;
	int datoObs;
	float datoF;
	char operador;
};
struct Datos {
	char tipoDatos;
	valorObtenido valor;
};
Datos evaluarOperacion(vector<Datos> datos) {
	Datos datosR;
	Datos datosObtenidos;
	datosR = datos.at(0);
	if(datosR.tipoDatos == 'I') {
		stack<int> pilaI;
		for(int i = 0; i < datos.size(); i++) {
			Datos data2 = datos.at(i);
			if(data2.tipoDatos == 'I'){
				pilaI.push(data2.valor.datoObs);
				cout<<data2.valor.datoObs<<" ";
			}
			if(data2.tipoDatos == 'O') {
				int num1 = pilaI.top();
				pilaI.pop();
				int num2 = pilaI.top();
				pilaI.pop();
				int num3;
				if(data2.valor.operador == '*'){
					num3 = num1 * num2;
				}
				if(data2.valor.operador == '/'){
					num3 = num1 / num2;
				}
				if(data2.valor.operador == '+'){
					num3=num1+num2;
				}
				if(data2.valor.operador == '-'){
					num3 = num1 - num2;
				}
				pilaI.push(num3);				
			}
		}
		datosObtenidos.valor.datoObs = pilaI.top();
		datosObtenidos.valor.operador = 'I';
	}
	if(datosR.tipoDatos == 'F') {
		stack<float> pilaF;
		for(int i = 0; i < datos.size(); i++) {
			Datos data3 = datos.at(i);
			if(data3.tipoDatos == 'F'){
				pilaF.push(data3.valor.datoObs);
				cout<<data3.valor.datoObs<<" ";
			}
			if(data3.tipoDatos == 'O') {
				float num1 = pilaF.top();
				pilaF.pop();
				float num2 = pilaF.top();
				pilaF.pop();
				float num3;
				if(data3.valor.operador == '*'){
					num3 = num1 * num2;
				}
				if(data3.valor.operador == '/'){
					num3 = num1 / num2;
				}
				if(data3.valor.operador == '+'){
					num3 = num1 + num2;
				}
				if(data3.valor.operador == '-'){
					num3 = num1 - num2;
				}
				pilaF.push(num3);				
			}
		}
		datosObtenidos.valor.datoObs = pilaF.top();
		datosObtenidos.valor.operador = 'F';
	}
	if(datosR.tipoDatos == 'B') {
		stack<unsigned int > pilaB;
		for(int i = 0; i < datos.size(); i++) {
			Datos data4 = datos.at(i);
			if(data4.tipoDatos == 'B'){
				pilaB.push(data4.valor.datoObs);
				cout << data4.valor.datoObs<<" ";
			}
			if(data4.tipoDatos == 'O') {
				unsigned int num1 = pilaB.top();
				pilaB.pop();
				unsigned int num2 = pilaB.top();
				pilaB.pop();
				unsigned int num3;
				if(data4.valor.operador == '*'){
					num3 = num1 & num2;
				}
				if(data4.valor.operador == '+'){
					num3 = num1 | num2;
				}
				pilaB.push(num3);				
			}
		}
		datosObtenidos.valor.datoObs = pilaB.top();
		datosObtenidos.valor.operador = 'B';
	}
	return datosObtenidos;
}
vector<Datos> conversion (vector<string> tokens) {
	vector<Datos> datos;
	if(tokens.at(0) == "I") {
		for(int i = 1; i<tokens.size(); i++) {
			Datos obj1;
			char tipo = 'I';
			if(tokens.at(i) == "*" || tokens.at(i) == "/" || tokens.at(i) == "+" || tokens.at(i) == "-") {
				char tipo = 'O';
				obj1.valor.operador = tokens.at(i)[0];
			}
			if(tokens.at(i) != "*" && tokens.at(i) != "/" && tokens.at(i) != "+"&&tokens.at(i) != "-") {
				obj1.valor.datoObs = stoi(tokens.at(i));
			}
			obj1.tipoDatos = tipo;
			datos.push_back(obj1);
		}
	} else if(tokens.at(0) == "F") {
		for(int i = 1; i<tokens.size(); i++) {
			Datos obj2;
			char tipo='F';
			if(tokens.at(i )== "*" || tokens.at(i) == "/" || tokens.at(i) == "+" || tokens.at(i) == "-") {
				char tipo = 'O';
				obj2.valor.operador = tokens.at(i)[0];
			}
			if(tokens.at(i) != "*" &&tokens.at(i) != "/" &&tokens.at(i) != "+" &&tokens.at(i) != "-") {
				obj2.valor.datoF = atof(tokens.at(i).c_str());
			}
			obj2.tipoDatos = tipo;
			datos.push_back(obj2);
		}
	} else if(tokens.at(0) == "B") {
		for(int i = 1; i<tokens.size(); i++) {
			Datos obj3;
			char tipo='B';
			if(tokens.at(i) == "*" || tokens.at(i) == "/" || tokens.at(i)=="+" || tokens.at(i) == "-") {
				char tipo = 'O';
				obj3.valor.operador = tokens.at(i)[0];
			}
			if(tokens.at(i) != "*" && tokens.at(i) != "/" && tokens.at(i) != "+" && tokens.at(i) != "-") {
				unsigned long temp = stoul(tokens.at(i),nullptr,10);
				obj3.valor.datoV = temp;
			}
			obj3.tipoDatos = tipo;
			datos.push_back(obj3);
		}
	}
	return datos;
}
vector<string> token(string line) {
	vector<string> tokens;
	string temp = "";
	for(int i = 0; i < line.size(); i++) {
		if(line.at(i) != ',') {
			temp += line.at(i);
		} else {
			tokens.push_back(temp);
			temp = "";
		}
	}
	if(temp != "") {
		tokens.push_back(temp);
	}
	return tokens;
}
void leerArchivo() {
	string linea = "";
	ifstream archivoTXT ("archivo.txt", ios::in);
	while (getline(archivoTXT, linea)) {
		vector<string> tokens = token(linea);
		for(int i = 0; i < tokens.size(); i++) {
			cout<<tokens.at(i)+" ";
		}
		cout<<endl;
		vector<Datos> datos = conversion(tokens);
		Datos data = evaluarOperacion(datos);
		cout<<"Respuesta: "<<data.valor.datoObs<<endl;
	}
	archivoTXT.close();
}