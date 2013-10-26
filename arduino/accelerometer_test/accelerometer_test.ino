
int x_accel;
int y_accel;
int z_accel;

int X_ACCEL_PIN = A0;
int Y_ACCEL_PIN = A1;
int Z_ACCEL_PIN = A2;

void setup() {
  pinMode(X_ACCEL_PIN, INPUT);
  pinMode(Y_ACCEL_PIN, INPUT);
  pinMode(Z_ACCEL_PIN, INPUT);
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop() {
  x_accel = analogRead(X_ACCEL_PIN);
  y_accel = analogRead(Y_ACCEL_PIN);
  z_accel = analogRead(Z_ACCEL_PIN);
  
  Serial.print("X: ");
  Serial.print(x_accel);
  Serial.print(", Y: ");
  Serial.print(y_accel);
  Serial.print(", Z: ");
  Serial.print(z_accel);
  Serial.println("");
  
  delay(100);
}
