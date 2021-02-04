const int POMP_PIN = 7;
const int MOIST_SENSOR_PIN = A0;
const int LEVEL_SENSOR_PIN = A1;
float sensorValue = 0;
int minimumMoist = 50;
bool isTankEmpty = false;

// You can have up to 10 menu items in the menuItems[] array below without having to change the base programming at all. Name them however you'd like. Beyond 10 items, you will have to add additional "cases" in the switch/case
// section of the operateMainMenu() function below. You will also have to add additional void functions (i.e. menuItem11, menuItem12, etc.) to the program.
String menuItems[] = {"HOME", "SETTINGS"};

// Navigation button variables
int readKey;
int savedDistance = 0;

// Humidity value for menu
float Hmt_Set_Value = 0;
float Hmt_Get_Value = 0;

// Menu control variables
int menuPage = 0;
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int cursorPosition = 0;

// Creates 3 custom characters for the menu display
byte downArrow[8] = {
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};

byte upArrow[8] = {
  0b00100, //   *
  0b01110, //  ***
  0b10101, // * * *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100  //   *
};

byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

#include <Wire.h>
#include <LiquidCrystal.h>

// Setting the LCD shields pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // Initializes serial communication
  Serial.begin(9600);

  // Initializes and clears the LCD screen
lcd.begin(16, 2);
lcd.clear();

// Creates the byte for the 3 custom characters
lcd.createChar(0, menuCursor);
lcd.createChar(1, upArrow);
lcd.createChar(2, downArrow);
}

void loop() {

	// MENU
	mainMenuDraw();
	drawCursor();
	operateMainMenu();
	// #####
  
  if (isWateringNeeded()) {
    Serial.println("Need watering");
    letsPump();
  }

  if (isRefillNeeded()) {
    Serial.println("Need tank refill");
    isTankEmpty = true;
  }

  Serial.println("Hugo suck dicks");

  delay(5000);
}

bool isWateringNeeded() {
  
  // 1023 max dry, 180 max wet, less is moister (44% in void, 95% in water)
    sensorValue = analogRead(MOIST_SENSOR_PIN) - 180; 
    sensorValue = 100 - (sensorValue * 0.118623962); 

    Serial.print("Moist at : ");
    Serial.print(analogRead(MOIST_SENSOR_PIN));
    Serial.print("/");
    Serial.print(sensorValue);
    Serial.println("%");

    return sensorValue < minimumMoist;
}

void letsPump() {
  digitalWrite(POMP_PIN, HIGH);   // turn on pump
  delay(5000);                    // wait 5 sec
  digitalWrite(POMP_PIN, LOW);    // turn off pump                               
}

bool isRefillNeeded() {
  sensorValue = analogRead(LEVEL_SENSOR_PIN);

  Serial.println("Water level :");
  Serial.println(sensorValue);

  // Sensor value is between 400 and 200 (even dried, still displaying 200)
  return sensorValue < 200;
}

/*
		MENU
*/

// This function will generate the 2 menu items that can fit on the screen. They will change as you scroll through your menu. Up and down arrows will indicate your current menu position.
void mainMenuDraw() {
  Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}

// When called, this function will erase the current cursor and redraw it based on the cursorPosition and menuPage variables.
void drawCursor() {
  for (int x = 0; x < 2; x++) {     // Erases current cursor
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  // The menu is set up to be progressive (menuPage 0 = Item 1 & Item 2, menuPage 1 = Item 2 & Item 3, menuPage 2 = Item 3 & Item 4), so
  // in order to determine where the cursor should be you need to see if you are at an odd or even menu page and an odd or even cursor position.
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is even and the cursor position is even that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is even and the cursor position is odd that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is odd and the cursor position is even that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is odd and the cursor position is odd that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

void operateMainMenu() {
  int activeButton = 0;
  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 0: // When button returns as 0 there is no action taken
        break;
      case 1:  // This case will execute if the "forward" button is pressed
        button = 0;
        switch (cursorPosition) { // The case that is selected here is dependent on which menu page you are on and where the cursor is.
          case 0:
            menuItem1();
            break;
          case 1:
            menuItem2();
            break;
        }
        activeButton = 1;
        mainMenuDraw();
        drawCursor();
        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        }
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }
        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
    }
  }
}

// If there are common usage instructions on more than 1 of your menu items you can call this function from the sub
// menus to make things a little more simplified. If you don't have common instructions or verbage on multiple menus
// I would just delete this void. You must also delete the drawInstructions()function calls from your sub menu functions.
void drawInstructions() {
  lcd.setCursor(0, 1); // Set cursor to the bottom line
  lcd.print("Use ");
  lcd.write(byte(1)); // Up arrow
  lcd.print("/");
  lcd.write(byte(2)); // Down arrow
  lcd.print(" buttons");
}

// This function is called whenever a button press is evaluated. The LCD shield works by observing a voltage drop across the buttons all hooked up to A0.
int evaluateButton(int x) {
  int result = 0;
  if (x < 50) {
    result = 1; // right
  } else if (x < 195) {
    result = 2; // up
  } else if (x < 380) {
    result = 3; // down
  } else if (x < 555) {
    result = 4; // left
  } else if (x < 790) {
    result = 5; // select
  }
  return result;
}

void menuItem1() { // Function executes when you select the Yellow item from main menu
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HOME");
  lcd.setCursor(0, 1);
  lcd.print("HMT ATM: " + String(Hmt_Get_Value) + "%");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 5:  // This case will execute if the select button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}

void menuItem2() { // Function executes when you select the Green item from main menu
  int activeButton = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SETTINGS");
  lcd.setCursor(0, 1);
  lcd.print("HMT VALUE: " + String(Hmt_Set_Value) + "%");

  while (activeButton == 0) {
    int button;
    readKey = analogRead(0);
    button = evaluateButton(readKey);
    switch (button) {
      case 1: // This case will execute if the right button is pressed
        Hmt_Set_Value++;
        lcd.setCursor(0, 1);
        lcd.print("HMT VALUE: " + String(Hmt_Set_Value) + "%");
        break;
      case 4: // This case will execute if the left button is pressed
        Hmt_Set_Value--;
        lcd.setCursor(0, 1);
        lcd.print("HMT VALUE: " + String(Hmt_Set_Value) + "%");
    }
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(0);
    }
    button = evaluateButton(readKey);
    switch (button) {
      case 5:  // This case will execute if the select button is pressed
        button = 0;
        activeButton = 1;
        break;
    }
  }
}
