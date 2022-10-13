#include <iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Cuentas{
	private:
		char name[20];
		char lastname[20];
		int numeroCuenta;
		int clave;
		float saldoTotal;
		float auxSaldo;
		bool encontrado;		
	public:
		void leerDatos();
		void mostrarDatos();
		void crearUsuario();
		void verDatos();
		void borrarUsuario();
		void retirar();
		void ingresar();
		void modificaciones();
		void salir();
		void buscar();
		void menu();
};
void Cuentas::menu(){
	int opcion;
	do{
		cout<<endl<<"\t----------Menu de opciones----------"<<endl;
		cout<<"\t1-. Crear Usuario"<<endl;
		cout<<"\t2-. Leer Usuario"<<endl;
		cout<<"\t3-. Borrar Usuario"<<endl;
		cout<<"\t4-. Ingresar o Retirar dinero"<<endl;
		cout<<"\t5-. Salir del Sistema"<<endl;
		cin>>opcion;
		switch(opcion){
			case 1:
				crearUsuario();
			break;
			case 2:
				buscar();
			break;
			case 3:
				borrarUsuario();
			break;	
			case 4:
				modificaciones();
			break;
			case 5:
				salir();
			break;
			default:cout<<"¡Opcion Incorrecta!"<<endl;	
		}
	}while(opcion!=5);
}
void Cuentas::leerDatos()
{
	cout<<"\n\tIngrese su Nombre: ";
	cin>>name;
	cout<<"\n\tIngrese su apellido: ";
	cin>>lastname;
	cout<<"\n\tIngrese el saldo: ";
	cin>>saldoTotal;
	srand((unsigned)time(0));
	numeroCuenta=rand();
	cout<<"\n\tSu numero de Cuenta es: "<<numeroCuenta;
	cout<<endl;
}
void Cuentas::mostrarDatos()
{
	cout<<"\t-------------------------------"<<endl;
	cout<<"\tNumero de Cuenta: "<<numeroCuenta<<endl;
	cout<<"\tNombre y Apellido: "<<name<<" "<<lastname<<endl;
	cout<<"\tSaldo Total: $"<<saldoTotal<<endl;
	cout<<"\t-------------------------------"<<endl;
}
void Cuentas::crearUsuario()
{
	ofstream escritura;
	ifstream consulta;
	encontrado=false;
	int auxClave;
	escritura.open("record.txt",ios::out|ios::app);
	consulta.open("record.txt",ios::in);
	if(escritura.is_open() && consulta.is_open()){
		cout<<"Ingresa la clave del Usuario: ";
		cin>>auxClave;
		consulta>>clave;
		while(!consulta.eof()){
			consulta>>name>>lastname>>numeroCuenta>>saldoTotal;
			if(clave==auxClave){
				cout<<"Ya existe un registro con esta clave"<<endl;
				encontrado=true;
				break;
			}
			consulta>>clave;
		}
		if(encontrado==false){
		leerDatos();
		mostrarDatos();
		escritura<<endl<<auxClave<<" "<<name<<" "<<lastname<<" "<<numeroCuenta<<" "<<saldoTotal;
		}	
	}else{
		cout<<"Error, el Archivo No se Pudo Abrir o No ha sido Creado"<<endl;
	}
	escritura.close();
	consulta.close();
}
void Cuentas::verDatos(){
	ifstream lectura;
	lectura.open("record.txt",ios::binary|ios::in);
	if(lectura.is_open()){
		cout<<"\t------------DATOS DEL USUARIO------------"<<endl;
		cout<<"\t_____________________________________________"<<endl;
		lectura>>clave;
		while(!lectura.eof()){
			lectura>>name>>lastname>>numeroCuenta>>saldoTotal;
			cout<<"\tNombre: "<<name<<" "<<lastname<<endl;
			cout<<"\tNumero de cuenta: "<<numeroCuenta<<endl;
			cout<<"\tSaldo total: "<<saldoTotal<<"$"<<endl;
			lectura>>clave;
			cout<<"\t_____________________________________________"<<endl;
		}	
	}else{
		cout<<"Error, el Archivo No se Pudo Abrir, No ha sido creado"<<endl;
	}
	lectura.close();
}
void Cuentas::buscar(){
    ifstream lectura;//Creamos la variable de tipo lectura
    lectura.open("record.txt",ios::out|ios::in);//Abrimos el archivo
    //validando la apertura del archivo
    encontrado=false;
    int auxClave;
    if(lectura.is_open()){
        cout<<"\tIngresa la Clave del Usuario: ";
        cin>>auxClave;
        lectura>>clave;//lectura adelantada

        while(!lectura.eof()){
            lectura>>name>>lastname>>numeroCuenta>>saldoTotal;//leyendo los campos del registro
            //Comparar cada registro para ver si es encontrado
            if(auxClave==clave){
                cout<<"\t______________________________"<<endl;
                cout<<"\tNombre: "<<name<<" "<<lastname<<endl;
                cout<<"\tNumero de Cuenta: "<<numeroCuenta<<endl;
                cout<<"\tSaldo total: "<<saldoTotal<<endl;
                cout<<"\t______________________________"<<endl;
                encontrado=true;
            }
            lectura>>clave;//lectura adelantada
        }
        if(encontrado==false){
            cout<<"No hay registros con la Clave "<<auxClave<<endl;
        }
    }else{
        cout<<"No se pudoAbrir el Archivo, aun no ha sido Creado"<<endl;
    }
    //cerrando el archivo
    lectura.close();	
}
void Cuentas::retirar(){
	int op=0;
	do{
		cout<<"\tCuanto dinero desea retirar: \n";cin>>auxSaldo;
		if(auxSaldo>saldoTotal){
			cout<<"No tienes ese dinero. Tienes: "<<saldoTotal<<endl;
		}else{
			saldoTotal-=auxSaldo;
		cout<<"\tYa se retiro el dinero en su cuenta\n";
		cout<<"\tDesea retirar mas dinero? si(1)\no(0)\n";cin>>op;
		}	
	}while(op==1);
}
void Cuentas::ingresar(){
	int op=0;
	do{
		cout<<"\tCuanto dinero desea ingresar: \n";cin>>auxSaldo;
		saldoTotal+=auxSaldo;
		cout<<"\tYa se ingreso el dinero en su cuenta\n";
		cout<<"\tDesea ingresar mas dinero? si(1)\no(0)\n";cin>>op;
	}while(op==1);
}
void Cuentas::modificaciones(){
	ofstream aux;
	ifstream lectura;
	encontrado=false;
	int auxClave=0;
	int opcion=0;
	aux.open("auxiliar.txt",ios::out);
	lectura.open("record.txt",ios::in);
	if(aux.is_open() && lectura.is_open()){
		cout<<"\tUsuario ingresa tu clave: ";cin>>auxClave;
		lectura>>clave;
		while(!lectura.eof()){
			lectura>>name>>lastname>>numeroCuenta>>saldoTotal;
			if(auxClave==clave){
				encontrado=true;
				cout<<"\t______________________________"<<endl;
                cout<<"\tNombre: "<<name<<" "<<lastname<<endl;
                cout<<"\tNumero de Cuenta: "<<numeroCuenta<<endl;
                cout<<"\tSaldo total: "<<saldoTotal<<endl;
                cout<<"\t______________________________"<<endl;
                cout<<"\t"<<name<<" "<<lastname<<" Desea ingresar(1) o retirar dinero(0)\n";
                cin>>opcion;
                if(opcion==1){
                	ingresar();
                	cout<<"\tSaldo modificado\n";
				}else{
					retirar();
					cout<<"\tSaldo modificado\n";
				}
                aux<<endl<<clave<<" "<<name<<" "<<lastname<<" "<<numeroCuenta<<" "<<saldoTotal;
			}else{
				aux<<endl<<clave<<" "<<name<<" "<<lastname<<" "<<numeroCuenta<<" "<<saldoTotal;
			}
			lectura>>clave;
		}
	}else{
		cout<<"No se pudoAbrir el Archivo, aun no ha sido Creado"<<endl;
	}
	if(encontrado==false){
		cout<<"No se encontro ningun registro con clave "<<auxClave<<endl;
	}
	aux.close();
	lectura.close();
	remove("record.txt");
	rename("auxiliar.txt","record.txt");
}
void Cuentas::borrarUsuario(){
    ofstream aux;
    ifstream lectura;
    encontrado=false;
    int auxClave=0;
    aux.open("auxiliar.txt",ios::out);
    lectura.open("record.txt",ios::in);
    if(aux.is_open() && lectura.is_open()){
        cout<<"Usuario ingresa tu clave: \n";
        cin>>auxClave;
        lectura>>clave;
        while(!lectura.eof()){
            lectura>>name>>lastname>>numeroCuenta>>saldoTotal;
            if(auxClave==clave){
                encontrado=true;
                cout<<"Registro Eliminado"<<endl;
            }else{
                aux<<endl<<clave<<" "<<name<<" "<<lastname<<" "<<numeroCuenta<<" "<<saldoTotal;
            }
            lectura>>clave;
        }
    }else{
        cout<<"No se pudoAbrir el Archivo o aun no ha sido Creado"<<endl;
    }
    if(encontrado==false){
        cout<<"No se encontro ningun registro con clave "<<auxClave<<endl;
    }
    aux.close();
    lectura.close();
    remove("record.txt");
    rename("auxiliar.txt","record.txt");
}
void Cuentas::salir(){
	cout<<"Programa finalizado"<<endl;
}
int main(){
	Cuentas var;	
	var.menu();
	return 0;
}

