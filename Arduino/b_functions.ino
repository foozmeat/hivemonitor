char* p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  return tmp;
}

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

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}



