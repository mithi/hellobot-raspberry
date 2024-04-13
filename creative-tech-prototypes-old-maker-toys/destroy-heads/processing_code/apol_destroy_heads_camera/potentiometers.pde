import processing.serial.*;

class AnalogReadings{
  String port_name; 
  int values[] = {2, 0, 0, 0, 75, 0, 0, 0};
  Serial my_port;
  
  AnalogReadings(Serial _my_port){
    my_port = _my_port; 
  }
  
  void update(){
    if( my_port.available() > 0){
      
      String val = my_port.readStringUntil('\n');
      
      if (val != null){

        int temp_val[] = int(split(val, ','));
        
        if (temp_val.length >= 8){
          values = temp_val;
        }
      }
    }
  }
  
  int[] get_values(){
    return values;
  }
}