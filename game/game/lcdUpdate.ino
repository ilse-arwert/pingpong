
// game title
void lcdPong(){
  lcd.setCursor(2, 0);
  lcd.print("Light Pong  ");
}

// print scores
void lcdUpdate(){
  lcd.setCursor(3, 1);
  lcd.print(wPlayer);
  lcd.setCursor(7, 1);
  lcd.print("-");
  lcd.setCursor(11, 1);
  lcd.print(ePlayer);
}

// blue is west
// red is east

void lcdBlue(){
  lcd.setCursor(2, 0);
  lcd.print("Blue scores!");
}

void lcdRed(){
  lcd.setCursor(2, 0);
  lcd.print("Red scores! ");
}
