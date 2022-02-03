<DOCTYPE html>
<html>
	<head>
		<title>Photos</title>
		<link rel="stylesheet" href="photoStyle.css" type="text/css">
	</head>

	<body>

			<ul>	
				<h1>My Photos</h1>
				<?php 
					$photos = glob("photos/*.{jpeg,jpg, gif, png}", GLOB_BRACE);
					foreach($photos as $filename){
						$strPrint = basename($filename);
						$strFileSize = round(filesize($filename) * .001);
						echo "<li><h5><a href=\"$filename\">$strPrint</a> ($strFileSize KB)</h5></li>";

					}

				?>

			</ul>

	</body>

</html>