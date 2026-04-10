// These are all pin numbers
const int rgbLEDRed = 9; 
const int rgbLEDGreen = 10;
const int rgbLEDBlue = 11;

const int buzzer = 3;

const int ledYellowTeam = 4;
const int buttonYellowTeam = 5;

const int ledGreenTeam = 6;
const int buttonGreenTeam = 7;

int yellowTeamButtonPressed = 0;
int yellowTeamScore = 0;

int greenTeamButtonPressed = 0;
int greenTeamScore = 0;

int tick = 0;

// End of pin numbers
String ledColor; 
bool buttonPressed = false;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(rgbLEDRed, OUTPUT);
  pinMode(rgbLEDGreen, OUTPUT);
  pinMode(rgbLEDBlue, OUTPUT);
  pinMode(ledYellowTeam, OUTPUT); 
  pinMode(ledGreenTeam, OUTPUT);

  pinMode(buzzer, OUTPUT);
  noTone(buzzer);

  pinMode (buttonYellowTeam, INPUT);
  pinMode (buttonGreenTeam, INPUT);
  
}

void RGB(int Red, int Green, int Blue){
  analogWrite (rgbLEDRed, Red);
  analogWrite (rgbLEDGreen, Green);
  analogWrite (rgbLEDBlue, Blue);
}

void switchLight(int delaySecs){
  int randomNum = random(3);
  if (randomNum == 1 || randomNum == 2) {
    RGB(0, 255, 0);
    tone(buzzer, 2000,1000);
    ledColor = "Green";
  } else if (randomNum == 0) {
    RGB(255, 0, 0);
    tone(buzzer, 1500, 1000);
    ledColor = "Red";
  } 
  delay(delaySecs*1000);
}

int buttonDetection (String Color){
  yellowTeamButtonPressed = digitalRead(buttonYellowTeam);
  greenTeamButtonPressed = digitalRead(buttonGreenTeam);
  while (greenTeamButtonPressed == 0 && yellowTeamButtonPressed == 0) {
    tick = tick + 1;

    yellowTeamButtonPressed = digitalRead(buttonYellowTeam);
    greenTeamButtonPressed = digitalRead(buttonGreenTeam);

    if (yellowTeamButtonPressed == 1) {
      if (Color == "Green"){
        yellowTeamScore = yellowTeamScore + 1;
        digitalWrite(ledYellowTeam, HIGH);
        break;
      }else if (Color == "Red"){
        yellowTeamScore = yellowTeamScore - 1;
        tone(buzzer, 1200, 1000);
        
      }
    }
    
    if (greenTeamButtonPressed == 1) {
        if(Color == "Green"){
          greenTeamScore = greenTeamScore + 1;
          digitalWrite(ledGreenTeam, HIGH);
          break;
        }else if (Color == "Red"){
          greenTeamScore = greenTeamScore - 1;
          tone(buzzer, 1200, 1000);
        }
    }
    
    if (tick >= 50) {
      Serial.println("Continuing to Next Round...");
      break;
    } else if (tick % 49 == 1) {
      Serial.println("Waiting...");
    }

    delay(100);
  }
  
}
 
void StartGame(int rounds){
  int currentRound = 1;
  yellowTeamScore = 0;
  greenTeamScore = 0;
  RGB(0, 0, 0);

  while (currentRound <= rounds) {
    ledColor = "";
    digitalWrite(ledYellowTeam, LOW);
    digitalWrite(ledGreenTeam, LOW);

    int randomTime = random(3000) + 2001;
    tick = 0;

    Serial.print("--Round "); Serial.print(currentRound); Serial.println("--");
    tone(buzzer,1000,1000);
    delay(randomTime);
    
    switchLight(0.5);
    buttonDetection(ledColor);
    delay(100);
    
    
    yellowTeamButtonPressed = digitalRead(buttonYellowTeam);
    greenTeamButtonPressed = digitalRead(buttonGreenTeam);
    while (greenTeamButtonPressed == 1 || yellowTeamButtonPressed == 1) {
      yellowTeamButtonPressed = digitalRead(buttonYellowTeam);
      greenTeamButtonPressed = digitalRead(buttonGreenTeam);
      Serial.println("Waiting for players to lift fingers from buttons...");
      delay(100);
    }
    RGB(0, 0, 0);
    delay(3000);
    currentRound = currentRound + 1;
 }

  Serial.println("---SCORES---");
  Serial.print("Yellow: "); Serial.println(yellowTeamScore);
  Serial.print("Green: "); Serial.println(greenTeamScore);

  if (greenTeamScore > yellowTeamScore) {
    for (int i=0; i<3; i++) {
    RGB(0, 255, 0);
    tone(buzzer, 2000,500);
    delay(500);
    RGB(0, 0, 0);
    delay(500);
    }
  
  } else if (yellowTeamScore > greenTeamScore) {
    for (int i=0; i<3; i++) {
    RGB(255, 220, 50);
    tone(buzzer, 2000,500);
    delay(500);
    RGB(0, 0, 0);
    delay(500);
    
    }
  } else {
    for (int i=0; i<3; i++) {
    RGB(255, 0, 0);
    tone(buzzer, 2000,500);
    delay(500);
    RGB(0, 0, 0);
    delay(500);
    
    }
  }

  delay(4000);
}


void loop() {
  // put your main code here, to run repeatedly:
  StartGame(5);
  RGB(0, 0, 255);
  tone(buzzer, 1700, 4000);
  delay(5000);
}