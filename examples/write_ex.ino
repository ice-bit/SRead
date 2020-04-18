String output;
void setup() {
    Serial.begin(9600);
}

void loop() {
    if(Serial.available() > 0) {
        output = Serial.readString();
        Serial.print("new message: ");
        Serial.println(output);
    }
}