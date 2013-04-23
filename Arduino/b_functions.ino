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

void addKVPair(String key, float value) 
{
  Serial.print("{\"");
  Serial.print(key);
  Serial.print("\":");
  Serial.print(value);
  Serial.println("}");
}

float celToFar(float Tc)
{
  float Tf = (9/5) * Tc + 32;
  return Tf;
}

float paToInMg (float pa)
{
  return pa * 0.000295299830714;
}

float paToMB (float pa)
{
  return pa * 0.01;
}

