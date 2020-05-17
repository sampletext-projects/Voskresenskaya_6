#include <iostream>
#include <conio.h>

using namespace std;

class Bit_string
{
protected:
	char* data_; //указатель на начало
	int length_; //длина

public:

	//конструктор по умолчанию
	Bit_string()
	{
		data_ = new char[100];
		length_ = 0;
	}

	//конструктор с параметрами
	Bit_string(int number)
	{
		data_ = new char[100];
		write_number(number);
	}

	//функция записи числа в класс
	virtual void write_number(int number)
	{
		int digits = 0;
		while (number > 0)
		{
			int digit = number % 2; //получаем двоичную цифру
			data_[digits] = digit; //записываем её в массив
			number /= 2; //делим число на 2(отбрасываем двоичную цифру)
			digits++; //увеличиваем количество цифр
		}
		length_ = digits;
	}

	//функция конвертации в число
	virtual int as_int()
	{
		int sum = 0;
		for (int i = 0; i < length_; ++i)
		{
			int number = (int)data_[i];

			//т.к. number либо 0 либо 1, то после умножения на 2 получим либо 0 либо 2, таким образом удовлетворяя условиям перевода систем
			sum += pow(number * 2, i);
		}
		return sum;
	}

	//функция вывода в стандартный поток
	virtual void print_to_cout()
	{
		for (int i = length_ - 1; i >= 0; --i)
		{
			cout << (int)data_[i]; //посимвольно в обратном порядке отправляем на печать
		}
	}
};

//наследуемый класс деньги
class Money : public Bit_string
{
	long rub_; //рубли
	unsigned char kop_; //копейки
public:
	//конструктор по умолчанию
	Money()
	{
		rub_ = 0;
		kop_ = 0;
	}

	//конструктор с параметрами
	Money(int rub, int kop)
	{
		rub_ = rub;
		kop_ = kop;
	}

	//перегрузка функции конвертации в число
	int as_int() override
	{
		return rub_ * 100 + kop_;
	}

	//перегрузка функции записи числа
	void write_number(int number) override
	{
		rub_ = number / 100;
		kop_ = number % 100;
	}

	//перегрузка функции вывода
	void print_to_cout() override
	{
		if (rub_ < 10)
		{
			cout << 0; //если рублей только на 1 цифру, выводим дополнительный 0
		}
		cout << rub_ << "р ";
		if ((int)kop_ < 10)
		{
			cout << 0; //если копеек только на 1 цифру, выводим дополнительный 0
		}
		cout << (int)kop_ << "к";
	}
};

void main()
{
	setlocale(LC_ALL, "russian");
	Bit_string* bits = new Bit_string(127);
	cout << "Bit_String::print_to_cout: ";
	bits->print_to_cout(); //вызов метода
	cout << "\nBit_String::as_int: ";
	cout << "\n = " << bits->as_int() << "\n"; //вызов ещё одного метода

	Money* m = new Money(100, 30);
	cout << "Money::print_to_cout: ";
	m->print_to_cout(); //вызов перегрузки метода
	cout << "\nMoney::as_int: ";
	cout << "\n = " << m->as_int() << " коп.\n"; //вызов перегрузки ещё одного метода

	system("pause");
}
