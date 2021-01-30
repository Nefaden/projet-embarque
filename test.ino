/* / LCD Keypad Shield

#include <LiquidCrystal.h>

// Création de l'objet lcd (avec les différents ports numériques qu'il utilise)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Variables
int lcd_key = 0;
int adc_key_in = 0;

int Button_State_Value = 0;
float Hmt_Set_Value = 0;
float Hmt_Get_Value = 0;
String Menu_Name = " ";

// Constantes
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

void setup()
{
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 Menu_Name = "HOME";
 lcd.print(Menu_Name);
 lcd.setCursor(0,1);
 lcd.print("HMT ATM: " + String(Hmt_Get_Value) + "%");
}
 
void loop()
{
 lcd_key = read_LCD_buttons();
 
 switch (lcd_key)
 {
   // TODO : Encadrer les variables pour que ça aille de 0 à 100
   case btnUP:
     {
       Button_State_Value++;
       break;
     }
   case btnDOWN:
     {
       Button_State_Value--;
       break;
     }
   case btnSELECT:
     {
        lcd.clear();
        ChangeSettings(Hmt_Set_Value);
        lcd.print("HMT SET: " + String(Hmt_Set_Value) + "%");
        delay(500);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(Menu_Name);
        lcd.setCursor(0,1);
        lcd.print("HMT ATM: " + String(Hmt_Get_Value) + "%");
        break;
     }
 }

 switch (Button_State_Value)    // Action effectuées par les boutons haut et bas pour changer les menus
 // TODO : bloqué les variables pour que ça swap entre 0 et 1 
 {
    case 1:
    {
      lcd.clear();
      lcd.setCursor(0,0);
      Menu_Name = "SETTINGS";
      lcd.print(Menu_Name);
      break;
    }
    case 2:
    {
      lcd.clear();
      lcd.setCursor(0,0);
      Menu_Name = "HOME";
      lcd.print(Menu_Name);
      break;
    }
 }
}

int ChangeSettings(float Hmt_Set_Value) {
  if (lcd_key = btnRIGHT) {
    Hmt_Set_Value = Hmt_Set_Value + 0.1;
  } else if (lcd_key = btnLEFT) {
    Hmt_Set_Value = Hmt_Set_Value - 0.1;
  }  
  return Hmt_Set_Value;
}

// Fonction de lecture des touches
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);   // Lecture du port analogique

 // Les valeurs qui suivent doivent être adaptées au shield
 if (adc_key_in > 1000) return btnNONE;   // En principe 1023 quand aucune touche n'est pressée
 if (adc_key_in < 50)   return btnRIGHT;     // 0
 if (adc_key_in < 195)  return btnUP;        // 99
 if (adc_key_in < 380)  return btnDOWN;      // 255
 if (adc_key_in < 555)  return btnLEFT;      // 409
 if (adc_key_in < 790)  return btnSELECT;    // 640

 return btnNONE;
}
*/
