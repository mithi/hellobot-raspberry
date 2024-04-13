void scroll_text(String text, int orientation){
  const int default_orientation = 0;
  const int wait = 80;
  const int height = 7;
  int x = (text.length())*height;
  
  matrix.setRotation(orientation);
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(LED_ON); 
  
  for (int i=height; i>=-x; i--) {
    matrix.clear();
    matrix.setCursor(i,0);
    matrix.print(text);
    matrix.writeDisplay();
    delay(wait);
  }  
  
  matrix.clear();
  matrix.setRotation(default_orientation);
}

void display_animation(const uint8_t *bitmap1, const uint8_t *bitmap2,
  const uint8_t *bitmap3, const uint8_t *bitmap4, int repetitions){
                      
  for(int i = 0; i < repetitions; i++){
    display_bitmap(bitmap1);
    display_bitmap(bitmap2);
    display_bitmap(bitmap3);
    display_bitmap(bitmap4);
  }
}

void display_bitmap(const uint8_t *bitmap){
  const int wait_time = 200;
  matrix.drawBitmap(0, 0, bitmap, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(wait_time);
  matrix.clear(); 
}


