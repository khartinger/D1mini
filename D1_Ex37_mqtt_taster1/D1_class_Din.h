//_____D1_class_Din.h_________________________170402-170402_____
// D1 mini class for digital input e.g. a button. 
//    Default is D3 (=GPIO0)
#ifndef D1_CLASS_DIN_H
#define D1_CLASS_DIN_H

class Din {
private:
 void setup(int num);
 int din_num;
 int din_old;
 int last_edge;
 
public:
 Din();
 Din(int num);
 int  get(void);
 bool isPressed(void);
 bool is_falling_edge(void);
 bool is_rising_edge(void);
};

//_____constructor (default button is D3)_______________________
Din::Din() { setup(D3); }

//_____constructor with button number (=GPIO)___________________
Din::Din(int num) { setup(num); }

//_____setup io_________________________________________________
void Din::setup(int num)
{
 din_num=num;                     // set input number
 pinMode(din_num, INPUT);         // set io to input
 din_old=this->get();             // get first value
 last_edge=0;                     // 0=no, 1=rising, 2=falling
}

//_____get input value__________________________________________
int Din::get(void) {
 int val_ = digitalRead(din_num);
 if((val_==1)&&(din_old==0)) last_edge=1;
 if((val_==0)&&(din_old==1)) last_edge=2;
 din_old=val_;
 return val_;
}

//_____get input value and return true, if button pressed (0V)__
bool Din::isPressed(void) {
 if(this->get()==0) return true;
 return false;
}

//_____detect button pressed____________________________________
bool Din::is_falling_edge(void)
{
 this->get();
 if(last_edge==2) { last_edge=0; return true; }
 return false;
}

//_____detect button released___________________________________
bool Din::is_rising_edge(void)
{
 this->get();
 if(last_edge==1) { last_edge=0; return true; }
 return false;
}
#endif
