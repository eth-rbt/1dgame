/* /////////////////////////////////////

  4.043 / 4.044 Design Studio: Interaction Intelligence
  February 9, 2024
  Marcelo Coelho

*/ /////////////////////////////////////


let displaySize = 15;   // how many pixels are visible in the game
let pixelSize = 50;     // how big each 'pixel' looks on screen

let p1;    // Adding 2 players to the game
let p2;
let target;       // and one target for players to catch.

let display;      // Aggregates our final visual output before showing it on the screen

let controller;   // This is where the state machine and game logic lives

let collisionAnimation;   // Where we store and manage the collision animation

let score;        // Where we keep track of score and winner
let keypressallow=true;

let blinkingLayer;
let angle = 0; // Initial angle for the sine wave
let startTime; // When the blinking should start
let increasingSpeedPhase; // Duration of the increasing speed phase
let blinkingStarted = false;
let initialFrequency = 0.0002; // Initial frequency of the sine wave
let frequency; // Current frequency, which will change over time
let newstarttime;
let startlevel=0;

function setup() {

  createCanvas((displaySize*pixelSize), pixelSize);     // dynamically sets canvas size

  display = new Display(displaySize, pixelSize);        //Initializing the display
  newstarttime=millis();
  startTime = millis() + 3000; // Start blinking after 10 seconds
  increasingSpeedPhase = 15000; // 10 seconds after blinking starts, for the next 10 seconds, increase speed
  frequency = initialFrequency;

  p1 = new Player(0,startlevel, displaySize);   // num, start level, display size
  p2 = new Player(1,startlevel, displaySize);   // num, start level, display size

  //target = new Player(color(255,255,0), parseInt(random(0,displaySize)), displaySize);    // Initializing target using the Player class 

  collisionAnimation = new Animation();     // Initializing animation

  controller = new Controller();            // Initializing controller
  blinkingLayer = createGraphics((displaySize*pixelSize), pixelSize);

}

function draw() {

  // start with a blank screen
  background(0, 0, 0);    

  // Runs state machine at determined framerate
  controller.update();

  // After we've updated our states, we show the current one 
  display.show();

  if (controller.gameState=='play'){
    startTime=newstarttime+3000;
    //blinking layer
    if (!blinkingStarted && millis() > startTime) {
      blinkingStarted = true;
    }

    if (blinkingStarted) {
      let currentTime = millis();
      // Adjust frequency based on how much time has passed since blinking started
      if (currentTime < startTime + increasingSpeedPhase) {
        let progress = (currentTime - startTime) / (increasingSpeedPhase - 3000);
        frequency = initialFrequency + progress * (0.008 - initialFrequency); // Increase frequency up to 0.5
      } else {
        frequency = 0.008; // Keep frequency constant after it reaches 0.5
      }

      // Update the transparency based on a sine wave with changing frequency
      let transparency = map(sin(frequency * (currentTime - startTime)), -1, 1, 0, 125);
    
      // Prepare the blinking layer
      blinkingLayer.clear(); // Clear the blinking layer
      blinkingLayer.fill(0, transparency); // Set the fill color with the calculated transparency
      blinkingLayer.rect(0, 0, (displaySize*pixelSize), pixelSize); // Cover the entire layer
    
      // Draw the blinking layer on top of the main canvas
    
      image(blinkingLayer, 0, 0);
    }
    
  }

  

}


