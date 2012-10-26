<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Phoenix Legion Resources Value Comparison</title>
        <?php
            require_once('includes/class.Resources.inc');
            require_once('includes/class.EveOreDB.inc');
        ?>
    </head>
    <body>
        <h1>Phoenix Legion Resources Value Comparison</h1>
        
        <p>
            Welcome to the Phoenix Legion resource value comparison tool.  This tool is intended for our players to be able to compare the value of each ore from station to station,
            as well as give a value that the corporation will purchase ore from our members.  Prices for corp value are per unit and are an average of the 5 major trade hubs.  This is
            to simplify creating corporate sell contracts.  Prices for station values are calculated in a per m3 basis to give a comparison of the relative value of each ore.
        </p>
        <?php
            $resources = new Resources();
            
            $resources->display();
        ?>
        
    </body>
</html>
