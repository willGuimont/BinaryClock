#ifdef F_CPU
#undef F_CPU
#define F_CPU 8000000UL
#endif

#define TOP_LEFT       7
#define TOP_RIGHT     10
#define BOTTOM_LEFT    8
#define BOTTOM_RIGHT   9

#define GROUP_1        5
#define GROUP_2        3
#define GROUP_3        2
#define GROUP_4        1
#define GROUP_5        0

int lastTime = 0;

unsigned char seconds = 0;
unsigned char minutes = 0;
unsigned char hours = 0;
bool pm = false;
unsigned char days = 0;

void setup() 
{
  // put your setup code here, to run once:
  for (int i = 0; i <= 10; ++i)
  {
    if (!(i == 4 || i == 6))
      pinMode(i, OUTPUT);
    if (i <= 5)
      digitalWrite(i, HIGH);
  }
}

void loop() 
{
  int newTime = millis();
  if (abs(newTime - lastTime) >= 1000)
  {
    tick();
    lastTime = newTime;
  }
  show();
}

void flash(char group, char position)
{
  digitalWrite(group, LOW);
  digitalWrite(position, HIGH);
  delay(1);
  digitalWrite(group, HIGH);
  digitalWrite(position, LOW);
}

void tick()
{
  ++seconds;
  if (seconds >= 60)
  {
    seconds = 0;
    ++minutes;
    if (minutes >= 60)
    {
      minutes = 0;
      ++hours;
      if (!pm)
      {
        // AM
        if (hours >= 13)
        {
          hours = 1;
          pm = true;
        }
      }
      else
      {
        if (hours >= 12)
        {
          hours = 0;
          pm = false;
          ++days;
        }
      }
      if (days >= 7)
      {
        days = 0;
      }
    }
  }
}

void show()
{
  // am/pm
  if (pm)
    flash(GROUP_1, BOTTOM_LEFT);
  
  // seconds
  if (seconds & 0b1)
    flash(GROUP_5, BOTTOM_RIGHT);
  if (seconds & 0b10)
    flash(GROUP_5, BOTTOM_LEFT);
  if (seconds & 0b100)
    flash(GROUP_4, BOTTOM_RIGHT);
  if (seconds & 0b1000)
    flash(GROUP_4, BOTTOM_LEFT);
  if (seconds & 0b10000)
    flash(GROUP_3, BOTTOM_RIGHT);
  if (seconds & 0b100000)
    flash(GROUP_3, BOTTOM_LEFT);
  
  // minutes
  if (minutes & 0b1)
    flash(GROUP_5, TOP_RIGHT);
  if (minutes & 0b10)
    flash(GROUP_5, TOP_LEFT);
  if (minutes & 0b100)
    flash(GROUP_4, TOP_RIGHT);
  if (minutes & 0b1000)
    flash(GROUP_4, TOP_LEFT);
  if (minutes & 0b10000)
    flash(GROUP_3, TOP_RIGHT);
  if (minutes & 0b100000)
    flash(GROUP_3, TOP_LEFT);

  // hours
  if (hours & 0b1)
    flash(GROUP_2, TOP_RIGHT);
  if (hours & 0b10)
    flash(GROUP_2, TOP_LEFT);
  if (hours & 0b100)
    flash(GROUP_1, TOP_RIGHT);
  if (hours & 0b1000)
    flash(GROUP_1, TOP_LEFT);

  // day
  if (days & 0b1)
    flash(GROUP_2, BOTTOM_RIGHT);
  if (days & 0b10)
    flash(GROUP_2, BOTTOM_LEFT);
  if (days & 0b100)
    flash(GROUP_1, BOTTOM_RIGHT);
}

