<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Phoenix Legion Resources Calculator</title>
        <?php
            require_once('includes/class.Resources.inc');
            require_once('includes/class.EveOreDB.inc');
        ?>
    </head>
    <body>
        <?php
            $resources = new Resources();
            $resources->loadResources();
            
            $resources->display();
        ?>
        
    </body>
</html>
