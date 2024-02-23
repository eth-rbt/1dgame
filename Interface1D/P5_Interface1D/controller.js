
// This is where your state machines and game logic lives


class Controller {

    // This is the state we start with.


    constructor() {
        this.gameState = "play";
        this.flag=true;
       
    }
    
    // This is called from draw() in sketch.js with every frame
    update() {

        // STATE MACHINE ////////////////////////////////////////////////
        // This is where your game logic lives
        /////////////////////////////////////////////////////////////////
        switch(this.gameState) {

            // This is the main game state, where the playing actually happens
            case "play":

                // clear screen at frame rate so we always start fresh      
                display.clear();

                for(let i = 0; i < 5; i++){
                    display.setPixeld(i,p1.arr[i])
                }
                for(let i = 10; i < 15; i++){
                    display.setPixeld(i,p2.arr[i-10])
                }
                console.log(p2.level)
            
                // show all players in the right place, by adding them to display buffer

                
                // check if player has caught target
                if (compareArrays(p1.arr,p2.arr) && this.flag)  {
                    this.flag=false;
                    keypressallow=false;
                    this.gameState='mid'
                    setTimeout(() => {
                        this.gameState = "change"; 
                        this.flag=true;
                        keypressallow=true
                    },500);
                    this.level++;      // increment score
                       // go to COLLISION state
                }

                if (millis()-newstarttime > 20000){
                    this.gameState = "explode"; 
                }
                
                // check if other player has caught target        
                break;

            // This state is used to play an animation, after a target has been caught by a player 
            case "change":
                
                 // clear screen at frame rate so we always start fresh      
                 display.clear();

                // play explosion animation one frame at a time.
                // first figure out what frame to show
                let frameToShow = collisionAnimation.currentFrame();    // this grabs number of current frame and increments it 
                
                // then grab every pixel of frame and put it into the display buffer
                for(let i = 0; i < collisionAnimation.pixels; i++) {
                    display.setPixel(i,collisionAnimation.animation[frameToShow][i]);                    
                }

                //check if animation is done and we should move on to another state
                if (frameToShow == collisionAnimation.animation.length-1)  {
                    p1.levelup();
                    p2.levelup();
                    newstarttime=millis(); //new level start time
                    blinkingStarted=false;
                    this.gameState = "play";    // back to play state
                } 

                break;

            // Game is over. Show winner and clean everything up so we can start a new game.
            case "explode":       
            
                display.setAllPixels(color(255,0,0));                    

                break;

            // Not used, it's here just for code compliance
            default:
                break;
        }
    }
}

function compareArrays(array1, array2) {
    // Check if arrays have different lengths
    if (array1.length !== array2.length) {
      return false;
    }
  
    // Iterate through each element of the arrays
    for (let i = 0; i < array1.length; i++) {
      // If corresponding elements are different, return false
      if (array1[i] !== array2[i]) {
        return false;
      }
    }
  
    // If all elements are the same, return true
    return true;
  }

const behaviors = {
    //Nothing
    'x':(player, index) => {
        player.arr[index] = player.arr[index] 
      },

    //increase by one, 0-3
    'a': (player, index) => {
      player.arr[index] = (player.arr[index] + 1) % 4;
    },

    //increase by one, 3-6
    'a1': (player, index) => {
        player.arr[index] = ((player.arr[index] + 2) % 4 )+3;
        console.log(player.arr)
    },

    'a2': (player, index) => {
        player.arr[index] = (player.arr[index] + 1) % 2;
    },

    //increase by 2 through all 10
    'b': (player, index) => {
      player.arr[index] = (player.arr[index] + 2) % 10; // Example of a different increment
    },

    //change all pixels 
    'c': (player, index) => {
        for(let i=0; i<5; i++) {
            player.arr[i] = (player.arr[i] + 1) % 4;
        }
    },

    'd': (player, index) => {
        player.arr.unshift(player.arr.pop());
    },

    'e': (player, index) => {
        updateNeighbors(player.arr, index, 2);
    },

    'f': (player, index) => {
        player.arr.reverse();
    },



  };
function keyPressed(){
    serialkeyPressed(key)
}


function serialkeyPressed(key) {
    if (keypressallow){
        const keysP1 = ['Q', 'W', 'E', 'R', 'T'];
        const keysP2 = ['Y', 'U', 'I', 'O', 'P'];
        const keyUpper = key.toUpperCase(); // Normalize key to handle lowercase input
        let player, keyIndex, actArray;

        // Determine if the key is for p1 or p2
        if (keysP1.includes(keyUpper)) {
            player = p1;
            keyIndex = keysP1.indexOf(keyUpper);
            actArray = p1.act;
        } else if (keysP2.includes(keyUpper)) { // ';' does not have uppercase
            player = p2;
            keyIndex = keysP2.indexOf(keyUpper);
            actArray = p2.act;
        }

        // Execute action if the key is found for either player
        if (player && actArray) {
            const mode = actArray[keyIndex]; // Get mode from the appropriate act array
            if (behaviors[mode]) {
            const action = behaviors[mode]; // Assuming all increments are 1 for simplicity, adjust as needed
            action(player, keyIndex); // Execute the action for the corresponding key and player
            }
        }

        // Example reset logic for key 'R', affecting both players
        if (keyUpper === 'Z') {
            if (controller.gameState!='explode'){
                p1.resetlevel();
                p2.resetlevel();
                controller.gameState = "play";
            }

            if (controller.gameState=='explode'){
                p1.resetlevel(); //restart
                p2.resetlevel(); //restart
                newstarttime=millis(); //new level start time
                blinkingStarted=false;
                controller.gameState = "play";
            }

            // Reset other game elements as needed
        }
    }
}

function updateNeighbors(arr, index, mod) {
    // Check if the index is valid
    if (index < 0 || index >= arr.length) {
      return; // Exit the function if the index is not valid
    }
    arr[index] = (arr[index]+1)%mod;
    // Update the previous element if it exists
    if (index - 1 >= 0) {
      arr[index - 1] = (arr[index - 1]+1)%mod;
    }
    
    // Update the next element if it exists
    if (index + 1 < arr.length) {
      arr[index + 1] = (arr[index + 1]+1)%mod ;
    }
  }


