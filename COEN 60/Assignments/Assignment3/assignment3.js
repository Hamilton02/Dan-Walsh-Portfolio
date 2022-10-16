var name = window.prompt("Please enter your name") + "";

	var rockThrow = 0;
	var paperThrow = 0;
	var scissorThrow = 0;

var results = "";
var wins = 0, loses = 0, ties = 0;


function play(){
	var rand = Math.floor(Math.random() * 3);

	var userThrow = document.getElementsByName('userThrow');

	compare(userThrow, rand);


}

function compare(yourInput, computerGen){
	document.getElementById('welcome').innerHTML = name + ", Welcome to Rock, Paper, Scissors"
	var compThrow = computerGen;
	var compThrowStr = "";

	switch(compThrow){
		case 0:
			compThrowStr = "Rock";
			break;
		case 1:
			compThrowStr = "Paper";
			break;
		case 2:
			compThrowStr = "Scissors";
			break;
	}


	var userNum = yourInput;

	for(var i = 0; i < userThrow.length; i++){
		if(userThrow[i].checked){
			userNum = userThrow[i].value;
			break;
		}
	}



	if(userNum == 0){
		rockThrow += 1;
	}else if(userNum == 1){
		paperThrow += 1;
	}else{
		scissorThrow+= 1;
	}

	document.getElementById('rocks').innerHTML = rockThrow;
	document.getElementById('papers').innerHTML = paperThrow;
	document.getElementById('scis').innerHTML = scissorThrow;




	document.getElementById('computerThrow').innerHTML = compThrowStr;
	
	

	switch(true){
		case userNum == null:
			window.alert("Please select an option");
			break;
		case userNum == compThrow:
			results = results + "<span style=\"background:#FFB81C\">Tie </span>";
			ties+= 1;
			document.getElementById('result').innerHTML = "<span style=\"background:#FFB81C\">Tie</span>";
			break;
		case userNum == 2 && compThrow == 0:
			results = results + "<span style=\"background:#BD3039\">Loss </span>";
			document.getElementById('result').innerHTML = "<span style=\"background:#BD3039\">Loss </span>";
			loses += 1;
			break;
		case userNum == 0 && compThrow == 2:
			results = results + "<span style=\"background:#007A33\">Win </span>";
			document.getElementById('result').innerHTML = "<span style=\"background:#007A33\">Win </span>";
			wins+= 1;
			break;
		case userNum > compThrow:
			results = results + "<span style=\"background:#007A33\">Win </span>";
			document.getElementById('result').innerHTML = "<span style=\"background:#007A33\">Win </span>";
			wins += 1;
			break;
		case userNum < compThrow:
			results = results + "<span style=\"background:#BD3039\">Loss </span>";
			document.getElementById('result').innerHTML = "<span style=\"background:#BD3039\">Loss </span>";
			loses += 1;
			break;
	}

	document.getElementById('history').innerHTML = results;	
	document.getElementById('wins').innerHTML = wins;
	document.getElementById('loses').innerHTML = loses;
	document.getElementById('ties').innerHTML = ties;
	
}