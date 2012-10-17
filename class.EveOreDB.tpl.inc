<?php

class EveOreDB {
	private $_connection;
	// Store the single instance.
	private static $_instance;
	
	/**
	 * Get an instance of the Database.
	 * @return Database
	 */
	public static function getInstance() {
	 if (!self::$_instance) {
		 self::$_instance = new self();
	 }
	 return self::$_instance;
	}
	
	/**
	* Constructor
	*/
	public function __construct() {
		$this->_connection = new MySQLi('localhost', 'mysql_user', 'mysql_password', 'mysql_database');
		//Error handling
		if (mysqli_connect_error()) {
			trigger_error('Failed to connect to MySQL: ' . mysqli_connect_error(), E_USER_ERROR);
		}
	}
	
	/**
	 * Emplty clone magic method to prevent duplication
	 */
	public function __clone() {}
	
	/**
	 * Get the MySQLi Connection
	 */
	public function getConnection() {
		return $this->_connection;
	}
}
