#include <iostream>

using namespace std;

/*
 * We need to design a generic class that is used to count objects.
 */

/*
 * In the below method we create a counter class which has a static
 * variable , this class member is embedded in other 2 user's class
 * Widget and Widget2.
 *
 * The counter keeps going up when we instantiate objects of Widget
 * and Widget2.
 *
 * However since the variable in Counter class is static this just keeps
 * incrementing and hence our example fails.
 *
 * We have done Widget w1,w2,w3 and Widget2 w4,w5 , hence we need to get
 * counts of 3 and 2 however we end up with count of 5 in both scenarios.
 */

/* Control which method we want to test */
//#define NORMAL_COUNTER_CLASS
//#define INHERITANCE_METHOD
//#define EMBED_METHOD

#define TEMPLATE_COUNTER_CLASS
//#define TEMPLATE_EMBED_CLASS
#define TEMPLATE_INHERITANCE_CLASS

#ifdef NORMAL_COUNTER_CLASS
/*
 * Faulty method , but still highlights certain concepts
 */
class Counter {

public:
    int x;

    Counter() 
    {
      cout <<"In counter...." << endl;
      count++;
    }

    Counter (const Counter &w) { count++;}

    ~Counter() 
    { 
      cout <<"Destroying counter...." << endl;
      count--;
    }

    static int how_many (void) 
    {
        return count;
    }

private:
    static int count;
};
int Counter::count = 0;
#endif  /* NORMAL_COUNTER_CLASS */


#ifdef EMBED_METHOD
class Widget {

public:
    Widget() 
    {
        cout <<"In widget...." <<endl;
    }

    ~Widget()
    {
        cout <<"Destroying widget..." << endl;
    }

    static int how_many() 
    {
        return Counter::how_many();
    }

private:
    Counter c;
};

class Widget2 {

public:
    Widget2() 
    {
        cout <<"In widget2...." <<endl;
    }

    ~Widget2()
    {
        cout <<"Destroying widget2..." << endl;
    }

    static int how_many() 
    {
        return Counter::how_many();
    }

private:
    Counter c;
};
#endif /* EMBED_METHOD */

#ifdef INHERITANCE_METHOD
class Widget: public Counter {

public:
    Widget() 
    {
        cout <<"In widget...." <<endl;
    }

    ~Widget()
    {
        cout <<"Destroying widget..." << endl;
    }

    static int how_many() { return Counter::how_many();}
};

class Widget2: public Counter {

public:
    Widget2() 
    {
        cout <<"In widget2...." <<endl;
    }

    ~Widget2()
    {
        cout <<"Destroying widget2..." << endl;
    }

    static int how_many() { return Counter::how_many();}

};
#endif /* INHERITANCE_METHOD */

/*
 * This is the correct method in which we create the code that needs
 * to be re-used namely the counter class code as a template.
 *
 * Now we can instantiate this template inside our respective classes
 * (Widget and Widget2) either by embedding a member or by inheritance.
 *
 * Both work fine but have different implications with respect to space
 */
#ifdef TEMPLATE_COUNTER_CLASS
/*
 * Make the counter class as a template
 */

template<typename T>
class Counter {

public:
    int x;

    Counter() 
    {
      cout <<"In counter...." << endl;
      count++;
    }

    Counter (const Counter &w) { count++;}

    ~Counter() 
    { 
      cout <<"Destroying counter...." << endl;
      count--;
    }

    static int how_many (void) 
    {
        return count;
    }

private:
    static int count;
};

template<typename T>
int Counter<T>::count = 0;
#endif /* TEMPLATE_COUNTER_CLASS */

#ifdef TEMPLATE_EMBED_CLASS
class Widget {

public:
    Widget() 
    {
        cout <<"In widget...." <<endl;
    }

    ~Widget()
    {
        cout <<"Destroying widget..." << endl;
    }

    static int how_many() 
    {
        return Counter<Widget>::how_many();
    }

private:
    Counter<Widget> c;
};

class Widget2 {

public:
    Widget2() 
    {
        cout <<"In widget2...." <<endl;
    }

    ~Widget2()
    {
        cout <<"Destroying widget2..." << endl;
    }

    static int how_many() 
    {
        return Counter<Widget2>::how_many();
    }

private:
    Counter<Widget2> c;
};
#endif /* TEMPLATE_EMBED_CLASS*/

#ifdef TEMPLATE_INHERITANCE_CLASS
class Widget: public Counter<Widget> {

public:
    Widget() 
    {
        cout <<"In widget...." <<endl;
    }

    ~Widget()
    {
        cout <<"Destroying widget..." << endl;
    }
};

class Widget2: public Counter<Widget2> {

public:
    Widget2() 
    {
        cout <<"In widget2...." <<endl;
    }

    ~Widget2()
    {
        cout <<"Destroying widget2..." << endl;
    }

};
#endif /* TEMPLATE_INHERITANCE_CLASS */


int main (void)
{
    Widget w1,w2,w3;
    Widget2 w4,w5;
    cout <<"Hello" << endl;

    cout << "Widget count::" << Widget::how_many() << endl;
    cout << "Widget2 count::" << Widget2::how_many() << endl;
}
