<link href="css/resources.css" rel="stylesheet" type="text/css" />

<script type="text/javascript" src="js/jquery-1.8.1.min.js"></script>
<script type="text/javascript" src="js/popup.js"></script>

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
     * Construct function to automatically load new data into the class object.
     */
    function __construct() {
        $this->loadResources();
    }
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
        
        if ($resource_array['order']==1) $this->_resources[$resource_array['type']][$resource_array['group']]['name'] = $resource_array['name'];
        $this->_resources[$resource_array['type']][$resource_array['group']]['resources'][$resource_array['order']] = array(
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
                                &$this->_resources[$resource_array['type']][$resource_array['group']]['resources'][$resource_array['order']];
        $this->_resource_name_index[strtolower($resource_array['name'])] = 
                                &$this->_resources[$resource_array['type']][$resource_array['group']]['resources'][$resource_array['order']];
        
    }
    
    /**
     * This function loads all the resources from the MySQL database.
     */
    public function loadResources($allowupdate=TRUE) {
        $eveOreDB = EveOreDB::getInstance();
        
        $eveOre = $eveOreDB->getConnection();
        
        $query = "SELECT * FROM resources;";
        
        $result = $eveOre->query($query);
        
        while ($row = $result->fetch_assoc()) {
            $this->addResource($row);
        }
        
        $this->isloaded = TRUE;
        if ((!file_exists('last_updated') || (filemtime('last_updated') < (time()-3600))) && $allowupdate) {
            echo "<!-- Updating database -->";
            $this->updateResources();
        } else {
            echo "<!-- Database last updated ".round((time()-filemtime('last_updated'))/60)." minutes ago. -->";
        }
        //echo "<!-- ".print_r($this->_resources, TRUE)."-->";
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
        $systems = implode(',', array_keys($this->_markets));
        
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
        touch('last_updated');

        $this->saveResources();
        $this->loadResources(FALSE);
    }
    
    /**
     * Returns the market value of a resource
     * @param array $resource
     * @param boolean $refined
     * @return array
     */
    public function getVolumeValues($resource, $volume = 1) {
        $resource_values = array(
            'raw' => NULL, 
            'refined' => NULL
        );
        foreach ($this->_markets as $market_id => $market) {
            $resource_values['raw'][$market] = array(
                'buy' => round(($resource[$market]['buy']*($volume/$resource['volume'])), 2), 
                'sell' => round(($resource[$market]['sell']*($volume/$resource['volume'])), 2)
            );
            if (!is_null($resource['yields'])) {
                $resource_values['refined'][$market] = array('buy'=>0, 'sell'=>0);
            }
        }
        $resource_values['raw']['corpbuy']=round($resource['corpbuy']/**($volume/$resource['volume'])*/,2);
        if (!is_null($resource['yields'])) {
            $resource_values['refined']['corpbuy']=0;

            foreach ($resource['yields'] as $key => $quantity) {
                foreach ($this->_markets as $market_id => $market) {
                    $mineral = $this->_resource_name_index[strtolower($key)];
                    $resource_values['refined'][$market]['buy'] += round(($quantity * $mineral[$market]['buy'])/$resource['batch']*($volume/$resource['volume']),2);
                    $resource_values['refined'][$market]['sell'] += round(($quantity * $mineral[$market]['sell'])/$resource['batch']*($volume/$resource['volume']),2);
                }
                $resource_values['refined'] ['corpbuy'] += round((($quantity * $mineral['corpbuy'])/$resource['batch'])*0.95/**($volume/$resource['volume'])*/,2);
            }
        }
        return $resource_values;
    }
    
    /**
     * This function will display a table for a specific resource group.
     * @param array $group
     * @return string
     */
    public function displayResourceGroups($groups) {
        foreach ($groups as $group_id => $group) {
            if ($group_id != -1) {
                echo "<div id=\"{$group['name']}-group-title\" class=\"group-title\">{$group['name']}s</div>\n";
                echo "<div id=\"{$group['name']}-resources\" class=\"group-resources\">\n";
            }
            echo "<span id=\"{$group['name']}-left-column\" class=\"left-column".($group_id == -1 ? ' short-left-column' : '')."\">\n";
                echo "<div class=\"phoenix-line\">Phoenix (ea)</div>";
                foreach ($this->_markets as $market_id => $market) {
                    echo "<div>".ucwords($market)." ".($group_id != -1 ? '(m3)' : '(ea)')."</div>";
                }
            echo "</span>\n";
            foreach($group['resources'] as $resource_id => $resource) {
                $this->displayResourceCell($resource);
            }
            if ($group_id != -1) echo "</div>\n";
        }
    }
    
    /**
     * This function returns the html for the table cell for a resource.
     * @param array $resource
     * @return string 
     */
    public function displayResourceCell($resource) {
        if (!is_null($resource['yields'])) {
            $values = $this->getVolumeValues($resource);
        } else {
            $values = $this->getVolumeValues($resource, $resource['volume']);
        }
        echo '<span id="'.$resource['id'].'" class="resourceCell '.(!is_null($values['refined']) ? "refineable" : "unrefineable")."\">\n";
            echo "<div class=\"resource-title\">{$resource['name']}</div>\n";
            if (!is_null($resource['yields'])) echo '<div class="resource-column-head">'.
                    '<span>Raw Ore</span>'.
                    '<span class="solid-left-border">Refined</span>'.
                 "</div>\n";
            echo '<div class="buy-sell-line">'.
                    '<span>Buy</span>'.
                    '<span class="dotted-left-border">Sell</span>'.
                    (!is_null($values['refined']) ? 
                    '<span class="solid-left-border">Buy</span>'.
                    '<span class="dotted-left-border">Sell</span>' : '').
                 "</div>\n";
            echo '<div class="values-row phoenix-line">'.
                    '<span>'.money_format('%#4.2n', $values['raw']['corpbuy']).'</span>'.
                    '<span class="dotted-left-border"><!-- Empty --></span>'.
                    (!is_null($values['refined']) ? 
                    '<span class="solid-left-border">'.money_format("%#4.2n", $values['refined']['corpbuy']).'</span>' : '').
                    '<span class="dotted-left-border"></span>'.
                 "</div>\n";
            foreach ($this->_markets as $market_id => $market_name) {
                echo '<div class="values-row">'.
                        '<span>'.money_format("%#4.2n", $values['raw'][$market_name]['buy']).'</span>'.
                        '<span class="dotted-left-border">'.money_format("%#4.2n", $values['raw'][$market_name]['sell']).'</span>'.
                        (!is_null($values['refined']) ? 
                        '<span class="solid-left-border">'.money_format("%#4.2n", $values['refined'][$market_name]['buy']).'</span>'.
                        '<span class="dotted-left-border">'.money_format("%#4.2n", $values['refined'][$market_name]['sell']).'</span>' : '').
                     "</div>\n";
            }
        echo "</span>\n";
    }
    
    public function display() {
        foreach ($this->_resources as $type => $groups) {
            echo "<div id=\"{$type}-title\" class=\"type-title\">{$type}</div>\n";
            echo "<div id=\"'{$type}'-groups\" class=\"type-groups\">\n";
                $this->displayResourceGroups($groups);
            echo "</div>\n";
        }
    }
}

?>
