function preload()
{

	
}

function setup() 
{
	createCanvas(windowWidth , windowHeight );
	print("Window Width : " + windowWidth);
	print("Window Height : " + windowHeight);
	background(0);
}

function draw() 
{
	background(color('hsla(160, 100%, 50%, 0.5)'));
	textSize(300);
	textStyle()
	text('ELECZOO', windowWidth / 2 - 300 * 2.5, windowHeight / 2 + 100 );
}

