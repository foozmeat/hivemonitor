void comment(String msg) {
    Serial.println(String("### " + msg));
}

void addKVPair(String key, float value) {
  char buf[12];
  char *v = dtostrf(value, 8, 5, buf);

  output = output + '"' + key + '"' + ':' + v;
  output = output + ','; 
}

void sendOutput() {
 
   // remove the trailing comma
   output = output.substring(0,output.length() - 2);
   
   output = output + '}';
   
   Serial.println(output);
   output = "{";
  
}
