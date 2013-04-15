<?php
$server = @$argv[1];
$port = intval(@$argv[2]);
$password = trim(@$argv[3]);
$command = implode(" ", array_slice($argv, 4));

if (!$server)
{
	echo "No server specified!";
	exit(1);
}

if (!$port)
{
	echo "No port specified!";
	exit(1);
}

if (!$password)
{
	echo "No password specified!";
	exit(1);
}

if (!$command)
{
	echo "No command specified!";
	exit(1);
}

$socket = fsockopen("udp://" . $server, $port, $errorNo, $errorString, 2);
if (!$socket)
{
	echo "Unable to connect to server '" . $server . ":" . $port . "'!";
	exit(1);
}

socket_set_timeout($socket, 2);

$pingData = "1337";

$packet = "SAMP";
$packet .= chr(strtok($server, "."));
$packet .= chr(strtok("."));
$packet .= chr(strtok("."));
$packet .= chr(strtok("."));
$packet .= chr($port & 0xFF);
$packet .= chr($port >> 8 & 0xFF);
$packet .= "p" . $pingData;

fwrite($socket, $packet);

if (fread($socket, 10))
{
	if (fread($socket, 5) != "p" . $pingData)
	{
		echo "Invalid response from server!";
		exit(1);
	}
}
else
{
	echo "Invalid response from server!";
	exit(1);
}

$packet = "SAMP";
$packet .= chr(strtok($server, "."));
$packet .= chr(strtok("."));
$packet .= chr(strtok("."));
$packet .= chr(strtok("."));
$packet .= chr($port & 0xFF);
$packet .= chr($port >> 8 & 0xFF);
$packet .= "x";

$packet .= chr(strlen($password) & 0xFF);
$packet .= chr(strlen($password) >> 8 & 0xFF);
$packet .= $password;
$packet .= chr(strlen($command) & 0xFF);
$packet .= chr(strlen($command) >> 8 & 0xFF);
$packet .= $command;

fwrite($socket, $packet);

$microTime = microtime(true) + 1;
while (microtime(true) < $microTime)
{
	$line = substr(fread($socket, 128), 13);
	
	if (strlen($line))
	{
		echo $line . "\n";
	}
	else
	{
		break;
	}
}
?>