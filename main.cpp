/*
 * main.cpp
 *
 *  Created on: 04.04.2017
 *      Author: Filip
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#define NDEBUG
#include <cassert>

using namespace std;

struct element
{
	element * prev;
	element * next;
	int value;

	element(int _value)
	{
		value = _value;
		next = NULL;
		prev = NULL;
	}
};


class List
{
	element * head;
	element * tail;

public:
	List()
	{
		head = NULL;
		tail = NULL;
	}

	void addToList(int _value)
	{
		assert(new element(_value));
		element *newElement = new element(_value);
		element *temp = head;

		if(!head && !tail)
		{
			head = newElement;
			tail = newElement;
		}
		else if(_value<=head->value)
		{
			head->prev = newElement;
			newElement->next = head;
			head = newElement;
		}
		else
		{
			while((temp->next != NULL) && (temp->next->value<=_value))
			{
				temp = temp->next;
			}

			if(temp->next == NULL)
			{
				tail->next = newElement;
				newElement->prev = tail;
				tail = newElement;
			}

			else
			{
				newElement->next = temp->next;
				temp->next->prev = newElement;
				newElement->prev = temp;
				temp->next = newElement;
			}

		}
	}

	void showListLeftToRight()
	{
		element * temp = head;

		cout << "Elementy na liœcie od lewej do prawej: ";
		while(temp)
		{
			cout << temp->value << " ";
			temp = temp->next;
		}

		cout << endl;
	}

	void showListRightToLeft()
	{
		element * temp = tail;

		cout << "Elementy na liœcie od prawej do lewej: ";
		while(temp)
		{
			cout << temp->value << " ";
			temp = temp->prev;
		}

		cout << endl;

	}

	void removeAllElements()
	{
		while(tail->prev)
		{
			tail = tail->prev;
			delete(tail->next);
		}
		delete(tail);
		head = tail = NULL;
		cout << "Usuniêto elementy na liœcie" << endl;
	}
};

int ignoreWhiteMarks(istream& in)
{
	int howMany = 0;
	while (in.peek() == 10 || in.peek() == 32)
		in.ignore();
	return howMany;
}

void readFromFileAndAddToList(int min, int max, string file)
{
	int value;
	char what;
	string str;

	assert(new filebuf());
	filebuf* fb = new filebuf();

	List lista;
	const char *cstr = file.c_str();

	assert(fb->open(cstr, ios::in));
	fb->open(cstr, ios::in);
	istream plik(fb);

		while (!plik.eof()) {
			ignoreWhiteMarks(plik);
			what = plik.peek(); //podgl¹damy co jest w strumieniu
			if (isdigit(what)) {
				plik >> value;
//				cout << "Liczba: " << value << endl;
				assert(value >= min && value <= max);
				if (value >= min && value <= max)
				{
					lista.addToList(value);
				}
			}
			else
			{
				plik >> str;
				cout << "Nie liczba: " << str << ";" << endl;
			}
		}
		fb->close();
		lista.showListLeftToRight();
		lista.showListRightToLeft();
		lista.removeAllElements();
		lista.showListLeftToRight();
}

template<class T>
T stringToValue(string str)
{
    istringstream iss(str);
    T value;
    iss>> value;
    return value;
}

int main(int argc, char *argv[])
{
	int min = stringToValue<int>(argv[1]);
	int max = stringToValue<int>(argv[2]);

	readFromFileAndAddToList(min, max, argv[3]);

}


