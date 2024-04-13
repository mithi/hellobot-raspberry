void initialize_clock(){
  rtc.begin(); // initialize RTC 24H format
  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);
  rtc.setAlarmTime(alarm_hours, alarm_minutes, alarm_seconds);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  rtc.attachInterrupt(alarm_match);  
}

String get_month_name(int x){
  String month_name[] = {String("jan"), String("feb"), String("mar"),
                       String("apr"), String("may"), String("jun"),
                       String("jul"), String("aug"), String("sep"),
                       String("oct"), String("nov"), String("dec"),};
  return month_name[x];
}
