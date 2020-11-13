let gVelX = 10;
let gVelY = 10;
let gXPos = 500;
let gYPos = 500;
let gRadius = 100;


function preload()
{

}

function setup() 
{
	createCanvas(windowWidth , windowHeight );
	print("Window Width : " + windowWidth);
	print("Window Height : " + windowHeight);
	frameRate(100);
	background(0);
}

function draw() 
{
	background(0);

	gXPos += gVelX;
	gYPos += gVelY;

	if(gXPos > (windowWidth - gRadius / 2) || gXPos < gRadius / 2 ){gVelX *= -1;}
	if(gYPos > (windowHeight - gRadius / 2) || gYPos < gRadius / 2 ){gVelY*= -1;}

	circle(gXPos, gYPos, gRadius);
}

