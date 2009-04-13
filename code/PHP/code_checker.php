<?php

/*
 * Check the GEZEL pairings for and return register contents for every clockcycle.
 */
 
// Variables
$states = [];
$newstate = [];
$output = [];

// Read code file & save all lines specifying a state.
$fp = fopen("wrapper-pairing.fdl", "r");

while (!feof($fp)) {
	$line = fread($fg, 2048);
	
	if (ereg_match("@[a-z0-9\-]\t", $line)) {
		$states[] = $line;
	}
}

fclose($fp);

// Read file specifying the names of each variable after a calculation.
$fp = fopen("regs-contents.txt", "r");

while (!feof($fp)) {
	$line = fread($fg, 2048);
	
	$splitted = split($line, ";");
	$newstate[] = {0 -> $splitted[0], 1 -> $splitted[1]};
}

fclose($fp);

// Detect all registers (sfg's starting with 'update_')
// Calculate new state at every state

// Calculate the output states

// Set start state
$output[] = {}

?>