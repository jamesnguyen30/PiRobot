var speed = 255;
var FORWARD_CODE = "forward" 
var BACKWARD_CODE = "backward" 
var ROTATE_LEFT = "rotateLeft" 
var ROTATE_RIGHT = "rotateRight" 

function forward(){
	$.post("/control", { control_code: FORWARD_CODE })
}
	
function backward(){
	$.post("/control", { control_code: BACKWARD_CODE })
}

function rotateRight(){
	$.post("/control", { control_code: ROTATE_RIGHT })
}

function rotateLeft(){
	$.post("/control", { control_code: ROTATE_LEFT })
}

window.onload = ()=>{
	
}


