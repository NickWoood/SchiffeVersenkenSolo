#include "field.h"
#include <iostream>

using namespace std;

field::field(int size)
{
	cout << "erstelle Feld der größe " << size << "\n\n" << endl;
	array = new int*[size];
	for (int h = 0; h < size; h++) {
		array[h] = new int[size];
		length++;
		for (int w = 0; w < size; w++)
		{
			array[h][w] = 0;
		}
	}
}

void field::print()
{
	/*
	Die "Umrisse" der Tabelle passen sich zwar noch nicht der größe des Felders an,
	allerdings werden diese spätestens beim einfügen der Sprites auch nicht mehr benötigt.
	*/

	cout << "Size is " << length << "\n\n" << endl;
	cout << "\t  A B C D E F G H I J \n\t _____________________\n";
	for (int h = 0; h <length; h++) {
		cout << h + 1 << "\t| ";
		for (int w = 0; w < length; w++)
		{
			cout << array[h][w] << " ";
			if (w == length - 1)
				cout << "|";
		}
		cout << "\n";
	}
	cout << "\t|_____________________|\n";
	cout << flush;
}

int field::getEntry(int x, int y)
{
	for (int h = 0; h <length; h++) {
		for (int w = 0; w < length; w++)
		{
			if (x - 1 == w && y - 1 == h)
				return array[h][w];
		}
	}
	return -1;
}

bool field::isInserted(int thing)
{
	for (int h = 0; h <length; h++) {
		for (int w = 0; w < length; w++)
		{
			if (array[h][w] == thing)
				return true;
		}
	}
	return false;
}

void field::insert(int value, int x, int y)
{
	for (int h = 0; h <length; h++) {
		for (int w = 0; w < length; w++)
		{
			if (x - 1 == w && y - 1 == h)
				array[h][w] = value;
		}
	}
}
