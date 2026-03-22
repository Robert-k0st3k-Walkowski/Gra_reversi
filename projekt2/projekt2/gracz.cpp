#include"gracz.h"
#include<iostream>

using namespace std;

gracz::gracz(stan s, Plansza* p) : symbol(s), plansza(p) {}; // Konstruktor klasy "gracz" oraz przypisanie wartoœci odpowiednim polom tej klasy

void gracz::ruch(Plansza* p) // Definicja metody "ruch" dla klasy "gracz"
{
	cout << "To jest ruch gracza.\n";
}

stan gracz::PobierzSymbol() // Definicja metody "PobierzSymbol" dla klasy "gracz"
{
	return symbol;
}

Plansza* gracz::PobierzPlansze() // Definicja metody "PobierzPlansze" dla klasy "gracz"
{
	return plansza;
}