<?php

class State {
	// Constructor
	public function __construct($name) {
		$this->setName($name);
	}
	
	// Name
	private $name;
	
	private function setName($name) {
		$this->name = $name;
	}
	
	// Reg updates
	private $regUpdates;
	
	public function addRegUpdate($regTo, $regFrom) {
		if (!$this->updateExists($regTo)) {
			$this->regUpdates[] = {"to" -> $regTo, "from" -> $regFrom};
		}
	}
	
	public function getRegUpdate($regTo) {
		for ($i = 0; $i < count($this->regUpdates); $i++) {
			if ($this->regUpdates[$i]["to"] == $regTo) {
				return $this->regUpdates[$i]["from"];
			}
		}
		
		return 0;
	}
	
	private function updateExists($regTo) {
		if ($this->getRegUpdate($regTo) == 0) {
			return TRUE;
		}
		
		return FALSE;
	}
}

?>