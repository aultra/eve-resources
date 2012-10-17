<link href="css/resources.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="jquery-1.8.1.min.js"></script>
<script type="text/javascript" src="popup.js"></script>

<?php

/**
 * The class that holds all of the resources from the database
 *
 * @author jrandrew
 */
class Resources {

    private $_resources = array();
    private $_resource_name_index = array();
    private $_resource_id_index = array();
    private $_markets = array (30000142 => 'jita', 30002659 => 'dodixie', 30002510 => 'rens', 30002053 => 'hek', 30002187 => 'amarr');
    private $_isloaded = FALSE;
    
    /**
     * Function to turn an associative array into a string.
     * @param array $arr
     * @return string
     */
    public function implodeAssoc($arr) { 
             $glue='~';
             $keys=array_keys($arr); 
             $values=array_values($arr); 

             return(implode($glue,$keys).$glue.implode($glue,$values)); 
    }

    /**
     * Function to turn a string into an associative array.
     * @param string $str
     * @return array
     */
    public function explodeAssoc($str) { 
             $glue='~';
             $arr=explode($glue,$str); 

             $size=count($arr); 

             for ($i=0; $i < $size/2; $i++) 
                             $out[$arr[$i]]=$arr[$i+($size/2)]; 

             return($out); 
    } 
    
    /**
     * Function to add a resource to the index and array.
     * @param array $resource_array
     */
    public function addResource($resource_array) {
        if (empty($resource_array['yields'])) {
            $yields = NULL;
        } else {
            $yields = $this->explodeAssoc($resource_array['yields']);
        }
        
        $sumAllBuy =  ($resource_array['jitaBuy'] + 
                    $resource_array['dodixieBuy'] + 
                    $resource_array['amarrBuy'] + 
                    $resource_array['rensBuy'] + 
                    $resource_array['hekBuy']);
        $countAllBuy = (($resource_array['jitaBuy']>0?1:0) +
                     ($resource_array['dodixieBuy']>0?1:0) +
                     ($resource_array['amarrBuy']>0?1:0) +
                     ($resource_array['rensBuy']>0?1:0) +
                     ($resource_array['hekBuy']>0?1:0)
                    );
        if ($countAllBuy==0) {
            $countAllBuy=1;
        }
        
        $this->_resources[$resource_array['type']][$resource_array['group']][$resource_array['order']] = array(
            'id' => $resource_array['id'],
            'name' => $resource_array['name'],
            'volume' => $resource_array['volume'],
            'batch' => $resource_array['batch'],
            'yields' => $yields,
            'jita' => array ('buy' => $resource_array['jitaBuy'], 'sell' => $resource_array['jitaSell']),
            'dodixie' => array ('buy' => $resource_array['dodixieBuy'], 'sell' => $resource_array['dodixieSell']),
            'amarr' => array ('buy' => $resource_array['amarrBuy'], 'sell' => $resource_array['amarrSell']),
            'rens' => array ('buy' => $resource_array['rensBuy'], 'sell' => $resource_array['rensSell']),
            'hek' => array ('buy' => $resource_array['hekBuy'], 'sell' => $resource_array['hekSell']),
            'corpbuy' => round($sumAllBuy/$countAllBuy,2)
        );
        $this->_resource_id_index[(int)$resource_array['id']] = 
                                &$this->_resources[$resource_array['type']][$resource_array['group']][$resource_array['order']];
        $this->_resource_name_index[strtolower($resource_array['name'])] = 
                                &$this->_resources[$resource_array['type']][$resource_array['group']][$resource_array['order']];
        
    }
    
    /**
     * This function loads all the resources from the MySQL database.
     */
    public function loadResources() {
        $eveOreDB = EveOreDB::getInstance();
        
        $eveOre = $eveOreDB->getConnection();
        
        $query = "SELECT * FROM resources;";
        
        $result = $eveOre->query($query);
        
        while ($row = $result->fetch_assoc()) {
            $this->addResource($row);
        }
        
        $this->isloaded = TRUE;
    }
    
    /**
     * This function is to save all changes to the resources array to the database.
     */
    public function saveResources() {
        $eveOreDB = EveOreDB::getInstance();
        
        $eveOre = $eveOreDB->getConnection();
        
        foreach($this->_resource_id_index as $resource_id => $resource_array) {
           $query  = "UPDATE resources ";
           $query .= "SET jitaBuy=".$resource_array['jita']['buy'].", jitaSell=".$resource_array['jita']['sell'].", ";
           $query .= "dodixieBuy=".$resource_array['dodixie']['buy'].", dodixieSell=".$resource_array['dodixie']['sell'].", ";
           $query .= "amarrBuy=".$resource_array['amarr']['buy'].", amarrSell=".$resource_array['amarr']['sell'].", ";
           $query .= "rensBuy=".$resource_array['rens']['buy'].", rensSell=".$resource_array['rens']['sell'].", ";
           $query .= "hekBuy=".$resource_array['hek']['buy'].",     hekSell=".$resource_array['hek']['sell']." ";
           $query .= "WHERE id=".$resource_id;
           
           $eveOre->query($query);
        }
    }
    
    /**
     * Function to get prices from the EVE Marketdata website.
     */
    public function updateResources() {
        if(!$this->isloaded) $this->loadResources ();
       
        $items = implode(',', array_keys($this->_resource_id_index));
        $systems = array_keys($this->_markets);
        
        
        
        $query = "http://api.eve-marketdata.com/api/item_prices2.json";
        $query_fields = array (
            'char_name' => 'Azam Azara',
            'type_ids' => $items,
            'solarsystem_ids' => $systems,
            'buysell' => 'a'
        );
        
        $html = new HttpRequest($query);
        $html->setQueryData($query_fields);
        
        $result = $html->send()->getBody();
        
        $json_data = json_decode($result,TRUE);
        
        foreach ($json_data['emd']['result'] as $row) {
            $data = $row['row'];
            $system = $this->_markets[$data['solarsystemID']];
            
            switch ($data['buysell']) {
                case 'b':
                    $buysell = 'buy';
                    break;
                case 's':
                    $buysell = 'sell';
                    break;
                default:
                    $buysell='Unknown';
            }
            $this->_resource_id_index[(int)$data['typeID']][$system][$buysell] = $data['price'];
        }
        $this->saveResources();
        $this->loadResources();
    }
    
    /**
     * Returns the market value of a resource
     * @param array $resource
     * @param boolean $refined
     * @return array
     */
    public function getRefinedValues($resource) {
        if (is_array($resource)) {
            if (!is_null($resource['yields'])) {
                $resource_values = array();
                
                foreach ($resource['yields'] as $key => $quantity) {
                    foreach ($this->_markets as $market_id => $market) {
                        $mineral = $this->_resource_name_index[strtolower($key)];

                        $resource_values[$market]['buy'] =+ round(($quantity * $mineral[$market]['buy'])/$resource['batch'],2);
                        $resource_values[$market]['sell'] =+ round(($quantity * $mineral[$market]['sell'])/$resource['batch'],2);
                    }
                    $resource_values['corpbuy'] =+ round(($quantity * $mineral['corpbuy'])/$resource['batch'],2);
                }
                
                return $resource_values;
            }
        }
        return NULL;
    }
    
    /**
     * This function will display a table for a specific resource group.
     * @param array $group
     * @return string
     */
    public function displayResourceType($type) {
        echo '<table class="resourceType">';
        foreach ($type as $resourceGroup_id => $resourceGroup) {
            echo '<tr id="'.$resourceGroup_id.'">';
            $this->displayResourceGroup($resourceGroup);
            echo '</tr>';
        }
        echo '</table>';
    }
    
    /**
     * This function displays each of the various groups of the resource type.
     * @param array $resourceGroup
     */
    public function displayResourceGroup($resourceGroup) {
        foreach($resourceGroup as $resource_id => $resource) {
            echo '<td id="'.$resource_id.'" class="resourceCell">';
            $this->displayResourceCell($resource);
            echo '</td>';
        }
    }
    
    public function displayMineralResourceCell($resource){
        echo '<table id="'.$resource['id'].'" class="resourceCellTable">';
            echo '<tr>'.
                    '<th colspan="5">'. $resource['name'].'</th>'.
                 '</tr>';
            echo '<tr>'.
                    '<th><!--Intentionally left blank--></th>'.
                    '<th>Buy</th>'.
                    '<th>Sell</th>'.
                 '</tr>';
            echo '<tr>'.
                    '<td>Phoenix</td>'.
                    '<td>'.round($resource['corpbuy']*.95, 2).'</td>'.
                    '<td style="background-color=black;"><!--Intentionally left blank--></td>'.
                 '</tr>';
            foreach ($this->_markets as $market_id => $market_name) {
                echo '<tr>'.
                        '<td>'.ucwords($market_name).'</td>'.
                        '<td>'.$resource[$market_name]['buy'].'</td>'.
                        '<td>'.$resource[$market_name]['sell'].'</td>'.
                     '</tr>';
            }
        echo '</table>';
    }
    
    /**
     * This function returns the html for the table cell for a resource.
     * @param array $resource
     * @return string 
     */
    public function displayResourceCell($resource) {
        if (is_null($resource['yields'])) $this->displayMineralResourceCell ($resource);
        else {
            $refinedValues = $this->getRefinedValues($resource);
            echo '<table id="'.$resource['id'].'" class="resourceCellTable">';
                echo '<tr>'.
                        '<th colspan="5">'. $resource['name'].'</th>'.
                     '</tr>';
                echo '<tr>'.
                        '<th><!--Intentionally left blank--></th>'.
                        '<th colspan="2">Raw Ore</th>'.
                        '<th colspan="2">Refined</th>'.
                     '</tr>';
                echo '<tr>'.
                        '<th><!--Intentionally left blank--></th>'.
                        '<th>Buy</th>'.
                        '<th>Sell</th>'.
                        '<th>Buy</th>'.
                        '<th>Sell</th>'.
                     '</tr>';
                echo '<tr>'.
                        '<td>Phoenix</td>'.
                        '<td>'.$resource['corpbuy'].'</td>'.
                        '<td style="background-color: black;"><!--Intentionally left blank--></td>'.
                        '<td>'. $refinedValues['corpbuy'] .'</td>'.
                        '<td style="background-color: black;"><!--Intentionally left blank--></td>'.
                     '</tr>';
                foreach ($this->_markets as $market_id => $market_name) {
                    echo '<tr>'.
                            '<td>'.ucwords($market_name).'</td>'.
                            '<td>'.$resource[$market_name]['buy'].'</td>'.
                            '<td>'.$resource[$market_name]['sell'].'</td>'.
                            '<td>'.$refinedValues[$market_name]['buy'].'</td>'.
                            '<td>'.$refinedValues[$market_name]['sell'].'</td>'.
                         '</tr>';
                }
            echo '</table>';
        }
    }
    
    public function display() {
        echo '<table id="resourcesTable">';
        foreach ($this->_resources as $type_id => $type) {
            echo '<tr id="'.$type_id.'"><td>';
            $this->displayResourceType($type);
            echo '</td></tr>';
        }
        echo '</table>';
    }
}

?>
