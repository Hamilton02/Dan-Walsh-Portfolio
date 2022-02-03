<!-- 
	Author: Dan Walsh
	Date Start: 11/15/2021
	Date End:

	Title: All the Music One Album at a Time
	Purpose: I am trying to listen to every album created, but I need to record everyone and this will serve as my record. This will be more complicated than it really needs to be but I want to use php to record everything in a file and make one txt file for every album and have it work as a database.

	THINGS TO ADD:
	Search bar
	Filtering
	Collapsable Notes Section
	Spotify Linking
	Better String breakdown
	Reading each file into an object based array
	Admin function to create a txt

	-->

	<!DOCTYPE html>
	<html>

		<head>
			<link rel="stylesheet" type="text/css" href="atmoaaat.css">
			<title>ATM O AAA T</title>	
		</head>

		<body>

			<h1>All the Music One Album At A Time</h1>

			<table class="entryTable">
				<tr>
					<th>Album</th>
					<th>Artist</th>
					<th>Date</th>
					<th>Genre</th>
					<th>Rating</th>
				</tr>

			<?php

				include 'albumEntry.php';

				$albums = glob("albums/*.txt");

				foreach($albums as $albumEntry){

					$longStr = file_get_contents($albumEntry);
					$base = basename($albumEntry);

					$albumObject = new albumEntry($longStr, $base);
					$albumObject->displayAlbum();
						
				}

			?>

			</table>
		</body>


	</html>