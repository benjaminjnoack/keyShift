//keyShift.ino
#define STAR 2
#define SEVEN 3
#define FOUR 4
#define ONE 5
#define ZERO 6
#define EIGHT 7
#define FIVE 8
#define TWO 9
#define HASH 10
#define NINE 11
#define SIX 12
#define THREE 13

#define CLOCK 14	// SH_CP 	11
#define LATCH 15	// ST_CP 	12
#define DATA 16 	// DS 		14

#define DEBOUNCE 250

void shiftByte(byte key);

int pins[] = {STAR, SEVEN, FOUR, ONE, ZERO, EIGHT, FIVE, TWO, HASH, NINE, SIX, THREE};
byte keys[] = {B11101110, B11100000, B01100110, B01100000, B11111100, B11111110, B10110110, B11011010, B01101110, B11100110, B00111110, B11110010};

void setup() 
{
	int i;
	for (i = 0; i <= 12; ++i)
		pinMode(pins[i], INPUT);

	pinMode(LATCH, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	pinMode(DATA, OUTPUT);

	shiftByte(B00000000);
}

void loop() 
{
	int i;

	for (i = 0; i < 12; ++i) {
		if (digitalRead(pins[i])) {
			shiftByte(keys[i]);
			delay(DEBOUNCE);
		}
	}
}

void shiftByte(byte key)
{
	int i;
	
	digitalWrite(LATCH, LOW);
	
	for (i = 7; i >= 0; i--){
	    digitalWrite(DATA, !!(key & (1 << i)));
	    //shift 1, starting at index 0, left up to a max of index 7. 
	    //Take the boolean equivalant of anding with the key at that index.
	    digitalWrite(CLOCK, HIGH);
	    digitalWrite(CLOCK, LOW);
	}
	
	digitalWrite(LATCH, HIGH);
}
