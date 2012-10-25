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
            Welcome to the Phoenix Legion resource value comparison tool.  This tool is intended for our players to be able to compare the value of each ore from 
        </p>
        <?php
            $resources = new Resources();
            $resources->loadResources();
            
            $resources->display();
        ?>
        
    </body>
</html>
