#include<iostream>
using std::cin;
using std::cout;
using std::endl;

class Fraction;
Fraction operator*(const Fraction left, const Fraction right);

class Fraction			//Описываем простую дробь
{//объявили переменные
	int integer;		//целая часть
	int numerator;		//числитель
	int denominator;	//знаменатель
public:
	//теперь с помощью get-метода можем получать значения
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	//с помощью set-методов мы можем задавать значения

	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//CONSTRUCTORS

	Fraction() //Конструктор по умолчанию
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Fraction(int integer) //Конструктор с одним параметром
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator) //Конструктор с дробной частью
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "ConstructorWithTwoParametres:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator) //конструктор со всеми параметрами
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)		//Конструктор копирования, который принимает константную ссылку на объект
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction() //Деструктор
	{
		cout << "Destructor:\t" << this << endl;
	}

	//OPERATORS
//Первым идет оператор присваивания
//он возвращает точную копию существующего объекта
	
	Fraction operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this; //опертатор присвоить ВСЕГДА возвращает разыменованный this
	}

	Fraction& operator*=(const Fraction& other)	//присваивание после умножения (left становится результатом)
	{
		return *this;
	}

	//METHODS
	Fraction& to_proper()		//Переводит в правильную дробь - выделяет целую часть
	{
		integer += numerator / denominator; //находим целую часть
		numerator %= denominator;			//находим остаток от деления
		return *this;
	}
	Fraction& to_improper()		//Переводит в неправильную дробь - интегрурет целую часть в числитель
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	void reduce()			//сокращает дробь
	{
		to_improper();
	}
	Fraction& reverse()	//переворачивает дробь
	{
		to_improper();				//перевели в неправильную дробь
		int buffer = numerator;		//создали буфер, в буфер поместили значение числителя
		numerator = denominator;	//значение числителя помещаем в знаменатель
		denominator = buffer;		//знаменатель помещаем в буффер
		return *this;				
	}
	void print()
	{
		if (integer)cout << integer;	//если есть целая часть - выводим её на экран
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << " /" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();	
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		cout << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}

Fraction operator*(Fraction left, Fraction right)	//передаем по значению, 
													//тогда автоматически left и right становятся буферами
													//поскольку они копируются в функцию при её вызове 
{
	left.to_improper();
	right.to_improper();
	//Fraction result			//решение через конструктор
	//(
	//	left.get_numerator() * right.get_numerator(),
	//	left.get_denominator() * right.get_denominator()
	//);
	///*result.set_numerator(left.get_numerator() * right.get_numerator());			//решение через set'еры
	//result.set_denominator(left.get_denominator() * right.get_denominator());*/
	//result.to_proper();	//переводим дробь в правильную
	//return result;

	//Явно вызываем конструктор прямо в return'е
	//этот конструктор вызывает временный безымянный объект,
	//который return сраху же возвращает на место вызова
	return Fraction
	(left.get_numerator() * right.get_numerator(),
	left.get_denominator() * right.get_denominator()
	).to_proper(); //мы можем сделать так, если только в методе to_proper 
	//заменим void на Fraction&, при этом будет в методе требовать вывод
	//а вывод там - return *this
}
Fraction operator/(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();
	right.reverse();

	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();*/

	////// ИЛИ ////////

	return left * right.reverse();	//Оператор * делает все преобразования 
}




//#define CONSTRUCTORS_CHECK
#define OSTREAM_CHECK
void main()
{
	setlocale(LC_ALL, "ru");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;			//Конструктор по умолчанию
	A.print();

	Fraction B = 5;		//Single-Argument Constructor - конструктор с одним параметром
	B.print();

	Fraction C(1, 2); //если здесь написать порядок 0,1,2, то выведется дробь 1/2
	//так как наш порядок чисел представляет собой следующее:
	//0 - integer, 1 - numerator, 2 - denominator
	C.print();

	Fraction D(2, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OSTREAM_CHECK
	Fraction A(14, 4);
	A.to_proper();
	//A.print();
	cout << A << endl;
	A.to_improper();
	//A.print();
	cout << A << endl;
#endif // OSTREAM_CHECK

	int a = 2;
	int b = 3;
	int c = a * b;

	Fraction A(1, 2, 3);
	Fraction B(4, 5, 6);
	Fraction C = A * B;
	Fraction D = A / B;
	C.print();
	D.print();

	A *= B;
	
}