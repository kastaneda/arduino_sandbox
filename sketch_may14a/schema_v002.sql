ALTER TABLE `sensor`
CHANGE `A6` `A6` INT(4) UNSIGNED NULL,
CHANGE `A7` `A7` INT(4) UNSIGNED NULL;

UPDATE `sensor` SET A6=NULL, A7=NULL WHERE board_id=1;
