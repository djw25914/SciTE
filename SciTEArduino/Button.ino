/*
 * Button handling vs selectables (
 
 */
void handleButtonPress(button pressed)
{
    if (currentAction == none) // We're in a menu, behave normally.
    {
        if (pressed == up){ //Move cursor up one position
            if (minor(currentSelection) >= 0){//If minor digit is >= 0, decrement it
                currentSelection--;
                updateDisplay();
            }}
        if (pressed = down){ //Move cursor down one position
            if (in(currentSelection+1)){
                currentSelection++;
                updateDisplay();
            }}
        //ignore left and right presses
        if (pressed = back){ //Move up a level
            if (currentSelection > 10){
                currentSelection %= 10;
                updateDisplay();
            }}
        //Enter handling is more delicate ...
        if (pressed = enter){
            
        
    }
    }
}