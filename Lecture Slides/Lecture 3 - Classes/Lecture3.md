# Classes and Objects
## Why do we need it? We already know structs!

Imagine you had this code:

```cpp
struct Date{
  int month;
  int day;
  int year;
};
```

You create a Date object:

```cpp
Date d;
d.month = 13;
```

When we do this data integrity is lost. We can not protect our information.

**Exercise time (2mins):** A scenario where Financial Institutions use struct and the CATASTROPHE that entails.

```cpp
Date d;
int month = 13;
if(month>0 && month<13)
  d.month = month;
```

**Only if you are updating it**, you have control over how the date is updated.

Now we will learn how to create instances where control over member variables is handled within the object itself.



# Classes

Just like structs, a class is a template (**think blueprint**). This "Object-Factory" helps us create instances of itself called **Objects**.

## Class Features

1. Complex Type
2. Functions included in class definitions, called methods control access to member variables.
3. Variables and methods can be public or private.
  - **public** - can be accessed outside the class.
  - **private** - can only be accessed by class methods. Example, a private variable can be viewed in the main function directly.
4. Constructor is called to create an instance of a class. Destructor is used to destroy a class (free memory).
5. A class has many more features, however these are the fundamental features that a programmer must always remember.

# Class Example

Now we will **create a class Date** with **three private members**, month, day and year. All integers.

The **Constructor** takes three arguments. One each for month, day and year. We will also be using a public method to print month, day and year.

```cpp
class Date{
	private:
		int month;
		int day;
		int year;
	public:
		Date(int m, int d, int y){
			month = m;
			day = d;
			year = y;
		}
		void printDate(){
			cout<<month<<" "<<day<<" "<<year<<endl;
		}
		void setMonth(int m){
			if(m > 0 and m < 13){
				month = m;
			}else{
				cout<<"Month out of Range"<<endl;
			}
		}
};
```

Now we will look at how to use the Date class.

```cpp
int main(){
	Date d(1, 1, 2018);


	//This will generate an error because month is private.
	cout<<d.month;


	//Also generates an error for same reason, month is private.
	d.month = 5

  //main() does not have the right to see anything private in Date.
}
```

## Then how do we update private member variables?

We need to create public methods that controls access.

Add the following code snippet to the class.

```cpp
void setMonth(int m){
  if(m>0 && m<13){
    month = m;
  }else{
    cout<<"Out of range!";
    //See how we handled this like a Boss!
    😎
  }
}
```

We make the following changes in main()

```cpp
int main(){
	Date d(31, 8, 2018);

	d.setMonth(13);//Month will not be updated
	d.setMonth(12);//Month will be updated
	d.printDate();//helps display private attributes
}
```
