#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>

using namespace std;

int Prioridad(char Operador)
{
    if (Operador == '+' || Operador == '-') return 1;
    if (Operador == '*' || Operador == '/') return 2;
    if (Operador == '^') return 3;
    return 0;
}

double AplicarOperacion(double a, double b, char Operador)
{
    switch (Operador)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
            {
                cout << "Error: Division entre cero.\n";
                return 0;
            }
            return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

int main()
{
    string Expresion;

    cout << "Evaluador de Expresion Aritmetica\n\n";
    cout << "Ingrese la expresion (ejemplo: 3+4*2): ";
    cin >> Expresion;

    stack<double> Valores;
    stack<char> Operadores;

    for (int i = 0; i < Expresion.length(); i++)
    {
        if (isdigit(Expresion[i]))
        {
            double Numero = 0;

            while (i < Expresion.length() && isdigit(Expresion[i]))
            {
                Numero = Numero * 10 + (Expresion[i] - '0');
                i++;
            }

            Valores.push(Numero);
            i--;
        }

        else if (Expresion[i] == '(')
        {
            Operadores.push(Expresion[i]);
        }

        else if (Expresion[i] == ')')
        {
            while (!Operadores.empty() && Operadores.top() != '(')
            {
                double b = Valores.top(); Valores.pop();
                double a = Valores.top(); Valores.pop();
                char op = Operadores.top(); Operadores.pop();

                Valores.push(AplicarOperacion(a, b, op));
            }

            if (!Operadores.empty())
                Operadores.pop();
        }

        else
        {
            while (!Operadores.empty() &&
                   Prioridad(Operadores.top()) >= Prioridad(Expresion[i]))
            {
                double b = Valores.top(); Valores.pop();
                double a = Valores.top(); Valores.pop();
                char op = Operadores.top(); Operadores.pop();

                Valores.push(AplicarOperacion(a, b, op));
            }

            Operadores.push(Expresion[i]);
        }
    }

    while (!Operadores.empty())
    {
        double b = Valores.top(); Valores.pop();
        double a = Valores.top(); Valores.pop();
        char op = Operadores.top(); Operadores.pop();

        Valores.push(AplicarOperacion(a, b, op));
    }

    cout << "\nResultado: " << Valores.top() << "\n";

    return 0;
}